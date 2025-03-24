#pragma once

#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "game/entities/level_object.h"
#include "game/entities/bullet/saw.h"
#include "game/entities/bullet/bubble.h"

namespace PlaygroundLevel {

bool LoadLevel(SDL_Renderer* renderer, std::vector<LevelObject*> &object, Mix_Music* &music_player, bool &is_looped) {
  // Load objects
  object.push_back(new Saw(renderer, 0.00, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 0.66, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 1.31, 50, 1260, 310, {-0.22, 0}));
  object.push_back(new Bubble(renderer, 1.40, 35, 1000, 300));
  object.push_back(new Saw(renderer, 1.75, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 2.40, 50, 1260, 385, {-0.22, 0}));

  object.push_back(new Bubble(renderer, 2.60, 35, 1000, 100));

  object.push_back(new Saw(renderer, 3.48, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 4.13, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 4.78, 50, 1260, 310, {-0.22, 0}));
  object.push_back(new Saw(renderer, 5.21, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Bubble(renderer, 5.40, 35, 1000, 660));
  object.push_back(new Saw(renderer, 5.86, 50, 1260, 385, {-0.22, 0}));
  object.push_back(new Saw(renderer, 6.08, 50, 1260, 140, {-0.22, 0}));
  object.push_back(new Saw(renderer, 6.40, 50, 1260, 500, {-0.22, 0}));
  object.push_back(new Saw(renderer, 6.72, 50, 1260, 140, {-0.22, 0}));
  object.push_back(new Bubble(renderer, 6.80, 35, 1000, 230));
  object.push_back(new Bubble(renderer, 7.00, 35, 1000, 350));

  // Validate objects
  for (std::size_t i = 1; i < (int)object.size(); ++i) {
    if (object[i]->GetStartTime() < object[i - 1]->GetStartTime()) {
      std::cout << "Playground::LoadLevel(): Level failed to load as the object is NOT sorted! (index " << i <<  ")\n";
      return false;
    }
  }

  // Load music
  music_player = Mix_LoadMUS("assets/musics/00_playground/mus_corrupted_section_01.ogg");
  if (music_player == nullptr) {
    throw std::runtime_error("PlaygroundLevel::LoadLevel(): Failed to load music! SDL error: " + std::string(Mix_GetError()));
    return false;
  }
  is_looped = true;
  return true;
}

}  // namespace PlaygroundLevel