#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <vector>

#include "behaviours/mono_behaviour.h"
#include "game/entities/level_object.h"
#include "game/entities/player.h"

class Level : public MonoBehaviour {
  Player* player;
  bool level_loaded;
  std::vector<LevelObject*> objects;
  Mix_Music* music_player;

 public:
  Level(SDL_Renderer* renderer_);
  ~Level();
  void EventHandler(SDL_Event& event) override;
  void Update() override;
  void Render() override;
};

#endif  // !LEVEL_H