#ifndef LEVEL_OBJECT
#define LEVEL_OBJECT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "geometry/vec2d.h"
#include "behaviours/mono_behaviour.h"

class LevelObject : public MonoBehaviour {
 protected:
  SDL_Texture* texture;
  SDL_Rect rect;  // destination rect to render.
  Vec2d position;

 public:
  double start_time;

  LevelObject(SDL_Renderer* renderer_);
  ~LevelObject();
  void SetRect(int x, int y, int w, int h);
  SDL_Rect GetRect();
  double GetStartTime();
  bool LoadImage(SDL_Renderer* renderer, const char* path);
  virtual LevelObject* Clone() = 0;
};

#endif  // !LEVEL_OBJECT