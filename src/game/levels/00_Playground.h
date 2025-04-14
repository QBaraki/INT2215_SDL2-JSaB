#pragma once

#include <SDL2/SDL_mixer.h>

#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

#include "common.h"
#include "game/entities/level_object.h"
#include "game/entities/bullet/saw.h"
#include "game/entities/bullet/bubble.h"
#include "game/entities/bullet/block.h"
#include "game/entities/bullet/circle.h"

#define SZ(a) (int)(a.size())

namespace PlaygroundLevel {

int GetRando(std::mt19937 &rng, int L, int R, int prev, int diff) {
  int x;
  while (true) {
    x = std::uniform_int_distribution<int>(L, R)(rng);
    if (std::abs(x - prev) >= diff)
      break;
    std::cerr << (x - prev) << ' ' << diff << '\n';
  }
  return x;
}

bool LoadLevel(SDL_Renderer* renderer, std::vector<LevelObject*> &object, Mix_Music* &music_player) {
  // Load objects
  int sz;
  std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

/*
  // Section 1: Saw
  object.push_back(new Saw(renderer, 0.790, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 1.440, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 2.090, 50, 1260, 310, {-0.27, 0}));
  object.push_back(new Saw(renderer, 2.530, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 3.180, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 4.250, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 4.900, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 5.600, 50, 1260, 310, {-0.27, 0}));
  object.push_back(new Saw(renderer, 5.985, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 6.640, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 6.850, 50, 1260, 140, {-0.27, 0}));
  object.push_back(new Saw(renderer, 7.180, 50, 1260, 500, {-0.27, 0}));
  object.push_back(new Saw(renderer, 7.505, 50, 1260, 140, {-0.27, 0}));
  for (int rep = 1; rep < 2; ++rep) {  // used to be 6
    for (int i = 0; i < 13; ++i) {
      object.push_back(new Saw(renderer, object[i]->GetStartTime() + rep * 6.935, 50, object[i]->position.x, object[i]->position.y, {-0.27, 0}));
    }
  }

  // Section 2: Bubble
  for (int rep = 0; rep < 20; ++rep) {
    object.push_back(new Bubble(renderer, 8.155 + rep * 1.732, 40, 1160, 70));
    object.push_back(new Bubble(renderer, 9.021 + rep * 1.732, 40, 1160, 630));
  }

  sz = SZ(object);

  // Section 3: Lines
  for (int rep = 0; rep < 2; ++rep) {
    object.push_back(new Block(renderer, 14.850 + rep * 6.93, 0.75f, 0.5f, {950, 0}, {1000, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 15.500 + rep * 6.93, 0.75f, 0.5f, {850, 0}, { 900, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 16.583 + rep * 6.93, 0.75f, 0.5f, {750, 0}, { 800, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 17.235 + rep * 6.93, 0.75f, 0.5f, {650, 0}, { 700, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 17.455 + rep * 6.93, 0.75f, 0.5f, {550, 0}, { 600, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 18.320 + rep * 6.93, 0.75f, 0.5f, {450, 0}, { 500, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 18.970 + rep * 6.93, 0.75f, 0.5f, {350, 0}, { 400, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 20.053 + rep * 6.93, 0.75f, 0.5f, {250, 0}, { 300, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 20.705 + rep * 6.93, 0.75f, 0.5f, {150, 0}, { 200, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 21.025 + rep * 6.93, 0.75f, 0.5f, { 50, 0}, { 100, WINDOW_HEIGHT}));
  }

  // Section 4: Horizontal and Vertical lines

  for (int rep = 0; rep < 2; ++rep) {
    // Horizontal
    object.push_back(new Block(renderer, 28.500 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {200, 0}, {240, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 28.500 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {600, 0}, {640, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 28.500 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {1000, 0}, {1040, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 29.148 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {400, 0}, {440, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 29.148 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {800, 0}, {840, WINDOW_HEIGHT}));
    // Vertical
    object.push_back(new Block(renderer, 30.230 + rep * 3.445, 0.75, -31.53 - rep * 3.445, {0, 340}, {WINDOW_WIDTH, 380}));
    object.push_back(new Block(renderer, 30.880 + rep * 3.445, 0.75, -31.53 - rep * 3.445, {0, 140}, {WINDOW_WIDTH, 180}));
    object.push_back(new Block(renderer, 30.880 + rep * 3.445, 0.75, -31.53 - rep * 3.445, {0, 540}, {WINDOW_WIDTH, 580}));
  }
*/
  
  // Section 5: Horizontal line and circles

  for (int rep = 0; rep < 2; ++rep) {
    double x = 99999, y = 99999;
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 35.427 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 35.427 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 36.078 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 36.078 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));

    x = GetRando(rng, 200, WINDOW_WIDTH - 200, x, 400);
    y = GetRando(rng, 80, WINDOW_HEIGHT - 80, y, 150);
    object.push_back(new Circle(renderer, 36.725 + rep * 3.445, 0.85f, 0.1f, {x, y}, 300, 2.0f));
    x = GetRando(rng, 200, WINDOW_WIDTH - 200, x, 400);
    y = GetRando(rng, 80, WINDOW_HEIGHT - 80, y, 150);
    object.push_back(new Circle(renderer, 36.824 + rep * 3.445, 0.949f, 0.1f, {x, y}, 300, 2.0f));
    x = GetRando(rng, 200, WINDOW_WIDTH - 200, x, 400);
    y = GetRando(rng, 80, WINDOW_HEIGHT - 80, y, 150);
    object.push_back(new Circle(renderer, 36.924 + rep * 3.445, 1.049f, 0.1f, {x, y}, 300, 2.0f));
    x = GetRando(rng, 200, WINDOW_WIDTH - 200, x, 400);
    y = GetRando(rng, 80, WINDOW_HEIGHT - 80, y, 150);
    object.push_back(new Circle(renderer, 37.049 + rep * 3.445, 1.174f, 0.1f, {x, y}, 300, 2.0f));

    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 37.135 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 37.135 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 37.810 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 37.810 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
  }

  // Push spawning objects
  std::vector<LevelObject*> pending;
  for (LevelObject* o : object) {
    std::vector<LevelObject*> spawned = o->Spawn();
    for (auto it : spawned) {
      pending.push_back(it);
    }
  }
  for (auto o : pending) {
    object.push_back(o);
  }

  std::sort(object.begin(), object.end(), [](LevelObject* lhs, LevelObject* rhs) {
      return lhs->GetStartTime() < rhs->GetStartTime();
    });

  // Load music
  music_player = Mix_LoadMUS("assets/musics/mus_corrupted_cut.ogg");
  if (music_player == nullptr) {
    throw std::runtime_error("PlaygroundLevel::LoadLevel(): Failed to load music! SDL error: " + std::string(Mix_GetError()));
    return false;
  }
  return true;
}

}  // namespace PlaygroundLevel

#undef SZ(a)