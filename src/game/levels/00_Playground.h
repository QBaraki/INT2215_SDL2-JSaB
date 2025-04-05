#pragma once

#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

#include "game/entities/level_object.h"
#include "game/entities/bullet/saw.h"
#include "game/entities/bullet/bubble.h"

namespace PlaygroundLevel {

bool LoadLevel(SDL_Renderer* renderer, std::vector<LevelObject*> &object, Mix_Music* &music_player) {
  // Load objects
  object.push_back(new Saw(renderer, 0.790, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 1.440, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 2.090, 50, 1260, 310, {-0.27, 0}));
  object.push_back(new Saw(renderer, 2.530, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 3.180, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 4.250, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 4.900, 50, 1260, 385,{-0.27, 0}));
  object.push_back(new Saw(renderer, 5.600, 50, 1260, 310, {-0.27, 0}));
  object.push_back(new Saw(renderer, 5.985, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 6.640, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 6.850, 50, 1260, 140, {-0.27, 0}));
  object.push_back(new Saw(renderer, 7.180, 50, 1260, 500, {-0.27, 0}));
  object.push_back(new Saw(renderer, 7.505, 50, 1260, 140, {-0.27, 0}));

  for (int rep = 1; rep < 6; ++rep) {
    for (int i = 0; i < 13; ++i) {
      object.push_back(new Saw(renderer, object[i]->GetStartTime() + rep * 6.935, 50, object[i]->position.x, object[i]->position.y, {-0.22, 0}));
    }
  }

  for (int rep = 0; rep < 20; ++rep) {
    object.push_back(new Bubble(renderer, 8.155 + rep * 1.732, 40, 1160, 70));
    object.push_back(new Bubble(renderer, 9.021 + rep * 1.732, 40, 1160, 630));
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
  music_player = Mix_LoadMUS("assets/musics/00_playground/mus_corrupted.ogg");
  if (music_player == nullptr) {
    throw std::runtime_error("PlaygroundLevel::LoadLevel(): Failed to load music! SDL error: " + std::string(Mix_GetError()));
    return false;
  }
  return true;
}

}  // namespace PlaygroundLevel