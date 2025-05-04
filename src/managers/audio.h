#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL_mixer.h>

#include <string>
#include <map>

namespace mAudio {

inline std::map<std::string, Mix_Chunk*> sound_map;

void Init();
void Destroy();
bool LoadSound(const std::string& id, const char* filename);
bool PlaySound(const char* id);

}  // namespace mAudio

#endif  // !AUDIO_H