#ifndef LEVEL_OBJECT
#define LEVEL_OBJECT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "geometry/vec2d.h"
#include "behaviours/mono_behaviour.h"

class LevelObject : public MonoBehaviour {
 protected:
  double start_time;
  SDL_Texture* texture;
  SDL_Rect rect;  // destination rect to render.
  Vec2d position;

 public:

  LevelObject(SDL_Renderer* renderer_);
  ~LevelObject();
  void SetRect(int x, int y, int w, int h);
  SDL_Rect GetRect();
  double GetStartTime();
  bool LoadImage(SDL_Renderer* renderer, const char* path);

  /**
    This function should return `true` if:
    - Out of screen dimension
    - Not needed anymore
   */
  virtual bool IsOutOfScreen() = 0;

  // Make a copy of the object in a new address
  virtual LevelObject* Clone() = 0;
};

#endif  // !LEVEL_OBJECT