#include "game.h"

#include "common.h"
#include "manager/audio.h"
#include "manager/time.h"

#include "utils/window_utils.h"
#include "utils/log_utils.h"
#include "game/level.h"

#include <stdexcept>
#include <thread>
#include <chrono>

Game::Game() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    throw std::runtime_error("Failed to initialize SDL. SDL error: " + std::string(SDL_GetError()));
  }
  window = SDL_CreateWindow("Ponging", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    throw std::runtime_error("Failed to create SDL window. SDL error: " + std::string(SDL_GetError()));
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    throw std::runtime_error("Failed to create SDL renderer window. SDL error: " + std::string(SDL_GetError()));
  }
  WindowUtils::Center(window);
  audio::Init();
  level = nullptr;
  running = true;
}


Game::~Game() {
  SDL_DestroyWindow(window);
  window = nullptr;
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  SDL_Quit();
}

void Game::InitGameLoop() {
  // start a new thread to do FixedUpdate()
  std::thread fixed_update_thread([&](void) {
      while (running) {
        auto frame_start_time = std::chrono::high_resolution_clock::now();
        FixedUpdate();
        auto frame_stop_time = std::chrono::high_resolution_clock::now();
        my_time::delta_time = std::chrono::duration<float, std::chrono::milliseconds::period>(frame_stop_time - frame_start_time).count();
        if (FIXED_UPDATE_TIME_STEP > my_time::delta_time) {
          std::this_thread::sleep_for(std::chrono::milliseconds(FIXED_UPDATE_TIME_STEP - (int)my_time::fixed_delta_time));
          frame_stop_time = std::chrono::high_resolution_clock::now();
          my_time::delta_time = std::chrono::duration<float, std::chrono::milliseconds::period>(frame_stop_time - frame_start_time).count();
        }
      }
    });

  level = new Level(renderer);
  // auto logger = LogUtils::thread_status(&status);
  float frame_time = 1000.0f / MAX_FPS;
  while (running) {
    SDL_Event event;
    auto frame_start_time = std::chrono::high_resolution_clock::now();
    while (SDL_PollEvent(&event)) {
      EventHandler(event);
    }

    Update();
    Render();

    auto frame_stop_time = std::chrono::high_resolution_clock::now();

    my_time::delta_time = std::chrono::duration<float, std::chrono::milliseconds::period>(frame_stop_time - frame_start_time).count();
    if (frame_time > my_time::delta_time) {
      SDL_Delay(uint32_t(frame_time - my_time::delta_time));
      frame_stop_time = std::chrono::high_resolution_clock::now();
      my_time::delta_time = std::chrono::duration<float, std::chrono::milliseconds::period>(frame_stop_time - frame_start_time).count();
    }
  }
  fixed_update_thread.join();
}

void Game::StopGameLoop() {
  running = false;
}

void Game::EventHandler(SDL_Event& event) {
  if (event.type == SDL_QUIT) {
    running = false;
  }
}

void Game::Update() {}

void Game::FixedUpdate() {}

void Game::Render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  level->RenderLevel(my_time::delta_time);

  SDL_RenderPresent(renderer);
}