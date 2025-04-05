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
  object.push_back(new Saw(renderer, 0.00, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 0.66, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 1.31, 50, 1260, 310, {-0.22, 0}));
  object.push_back(new Bubble(renderer, 1.40, 35, 1000, 300));
  object.push_back(new Saw(renderer, 1.75, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 2.40, 50, 1260, 385, {-0.22, 0}));

  object.push_back(new Bubble(renderer, 2.60, 35, 1000, 100));
  object.push_back(new Bubble(renderer, 2.60, 35, 600, 300));

  object.push_back(new Saw(renderer, 3.48, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 4.13, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 4.78, 50, 1260, 310, {-0.22, 0}));
  object.push_back(new Saw(renderer, 5.21, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Bubble(renderer, 5.40, 35, 1000, 660));
  object.push_back(new Saw(renderer, 5.86, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 6.08, 50, 1260, 140, {-0.22, 0}));
  object.push_back(new Saw(renderer, 6.40, 50, 1260, 500, {-0.22, 0}));
  object.push_back(new Saw(renderer, 6.72, 50, 1260, 140, {-0.22, 0}));

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