#ifndef LEVEL_H
#define LEVEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <list>
#include <vector>

#include "behaviours/mono_behaviour.h"
#include "game/entities/level_object.h"
#include "game/entities/player.h"

class Level : public MonoBehaviour {
  Player* player;
  bool level_loaded, player_died;
  std::size_t objects_count, current_index;
  std::list<LevelObject*> onscreen_objects;
  std::vector<LevelObject*> loaded_objects, pending, preloaded;
  Mix_Music* music;
  double previous_duration;
  double ending_duration;
  SDL_Texture* loading_screen;

 public:
  Level(SDL_Renderer* renderer_);
  ~Level();
  void EventHandler(SDL_Event& event) override;
  void Update() override;
  //void FixedUpdate() override;
  void Render() override;
};

#endif  // !LEVEL_H