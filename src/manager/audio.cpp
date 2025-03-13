#include "audio.h"

#include <iostream>
#include <stdexcept>

void my_audio::Init() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    throw std::runtime_error("Failed to initialize SDL_mixer. Error: " + std::string(Mix_GetError()));
  }
}

void my_audio::Destroy() {
  Mix_Quit();
}