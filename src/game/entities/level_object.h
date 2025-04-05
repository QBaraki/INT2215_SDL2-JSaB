#ifndef LEVEL_OBJECT
#define LEVEL_OBJECT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

#include "geometry/vec2d.h"
#include "behaviours/mono_behaviour.h"
#include "game/entities/player.h"

class LevelObject : public MonoBehaviour {
 protected:
  SDL_Texture* texture;
  double start_time;
  SDL_Rect rect;  // destination rect to render.

 public:
  Vec2d position;

  LevelObject(SDL_Renderer* renderer_);
  ~LevelObject();
  void SetRect(int x, int y, int w, int h);
  SDL_Rect GetRect();
  double GetStartTime();

  // This function should return `true` when collide with the player
  virtual bool IsCollided(Player* target) = 0;

  // This function should return `true` if it is out of screen dimension
  virtual bool IsOutOfScreen() = 0;

  // This function should return `true` when it's *should* be destroyed
  virtual bool IsDestroyed();

  // Return some objects when destroyed
  virtual std::vector<LevelObject*> Spawn();

  // Make a copy of the object in a new address
  virtual LevelObject* Clone() = 0;
};

#endif  // !LEVEL_OBJECT