#include "audio.h"

#include <iostream>
#include <stdexcept>

#ifdef NDEBUG
#define cerr \
  if (0)     \
  std::cerr
#else
using std::cerr;
#endif  // NDEBUG

void mAudio::Init() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    throw std::runtime_error("Failed to initialize SDL_mixer. Error: " + std::string(Mix_GetError()));
  }
  cerr << "Mixer initialized!\n";
}

void mAudio::Destroy() {
  Mix_Quit();
}