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
  LoadSound("on-hit", "assets/sfx/on_hit.ogg");
  LoadSound("died", "assets/sfx/died.ogg");
}

void mAudio::Destroy() {
  for (auto& p : sound_map) {
    Mix_FreeChunk(p.second);
  }
  sound_map.clear();
  Mix_Quit();
}

bool mAudio::LoadSound(const std::string& id, const char* filename) {
  Mix_Chunk* sound = Mix_LoadWAV(filename);
  if (!sound) {
    cerr << "Failed to load sound " << filename << ". Error: " << Mix_GetError() << std::endl;
    return false;
  }
  cerr << "mAudio::LoadSound(): Loaded sound " << filename << " on ID " << id << '\n';
  sound_map[id] = sound;
  return true;
}

bool mAudio::PlaySound(const char* id) {
  if (sound_map.find(id) != sound_map.end()) {
    Mix_PlayChannel(-1, sound_map[id], 0);
    return true;
  }
  return false;
}

#undef cerr