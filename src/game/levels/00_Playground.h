#pragma once

#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "game/entities/level_object.h"
#include "game/entities/bullet/saw.h"

namespace PlaygroundLevel {

bool LoadLevel(SDL_Renderer* renderer, std::vector<LevelObject*>& object, Mix_Music*& music_player) {
  // Load objects
  object.push_back(new Saw(renderer, 0.50, 50, 1280, 300, {-0.15, 0}));
  object.push_back(new Saw(renderer, 1.50, 50, 1280, 500, {-0.15, 0}));
  object.push_back(new Saw(renderer, 2.25, 50, 1280, 200, {-0.15, 0}));
  object.push_back(new Saw(renderer, 4.00, 50, 1280, 200, {-0.15, 0}));
  object.push_back(new Saw(renderer, 5.50, 50, 1280, 300, {-0.15, 0}));
  object.push_back(new Saw(renderer, 6.00, 50, 1280, 350, {-0.15, 0}));

  // Load music
  music_player = Mix_LoadMUS("assets/musics/00_playground/mus_corrupted_section_01.ogg");
  if (music_player == nullptr) {
    throw std::runtime_error("PlaygroundLevel::LoadLevel(): Failed to load music! SDL error: " + std::string(Mix_GetError()));
    return false;
  }
  return true;
}

}  // namespace PlaygroundLevel