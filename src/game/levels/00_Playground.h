#pragma once

#include <SDL2/SDL_mixer.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#include "game/entities/level_object.h"
#include "game/entities/bullet/saw.h"

namespace PlaygroundLevel {

bool LoadLevel(SDL_Renderer* renderer, std::vector<LevelObject*> &object, Mix_Music* &music_player, bool &is_looped) {
  // Load objects
  object.push_back(new Saw(renderer, 0.00, 50, 1260, 420, {-0.173, 0}));
  object.push_back(new Saw(renderer, 0.66, 50, 1260, 420, {-0.173, 0}));
  object.push_back(new Saw(renderer, 1.31, 50, 1260, 200, {-0.173, 0}));
  object.push_back(new Saw(renderer, 1.75, 50, 1260, 420, {-0.173, 0}));
  object.push_back(new Saw(renderer, 2.40, 50, 1260, 420, {-0.173, 0}));

  object.push_back(new Saw(renderer, 3.48, 50, 1260, 420, {-0.173, 0}));
  object.push_back(new Saw(renderer, 4.13, 50, 1260, 420, {-0.173, 0}));
  object.push_back(new Saw(renderer, 4.78, 50, 1260, 200, {-0.173, 0}));
  object.push_back(new Saw(renderer, 5.21, 50, 1260, 420, {-0.173, 0}));
  object.push_back(new Saw(renderer, 5.86, 50, 1260, 420, {-0.173, 0}));
  object.push_back(new Saw(renderer, 6.08, 50, 1260, 140, {-0.173, 0}));
  object.push_back(new Saw(renderer, 6.40, 50, 1260, 350, {-0.173, 0}));
  object.push_back(new Saw(renderer, 6.72, 50, 1260, 140, {-0.173, 0}));


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