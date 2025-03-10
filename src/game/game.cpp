#include "game.h"

#include "common.h"
#include "utils/window_utils.h"
#include "utils/log_utils.h"
#include "game/level.h"

#include <stdexcept>
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
  Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}


Game::~Game() {
  SDL_DestroyWindow(window);
  window = nullptr;
  SDL_DestroyRenderer(renderer);
  renderer = nullptr;
  SDL_Quit();
}

void Game::InitGameLoop() {
  bool running = true;
  Level* level = new Level(renderer);
  // auto logger = LogUtils::thread_status(&status);
  while (running) {
    SDL_Event event;
    auto frame_start_time = std::chrono::high_resolution_clock::now();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }
      level->InputHandler(&event);
    }
    SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 255);
    SDL_RenderClear(renderer);
    
    level->RenderLevel(status.delta_time);

    SDL_RenderPresent(renderer);
    auto frame_stop_time = std::chrono::high_resolution_clock::now();
    status.delta_time = std::chrono::duration<float, std::chrono::milliseconds::period>(frame_stop_time - frame_start_time).count();
  }
}