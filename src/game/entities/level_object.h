#ifndef LEVEL_OBJECT
#define LEVEL_OBJECT

#include "geometry/vec2d.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class LevelObject {
 protected:
  SDL_Texture* texture;
  SDL_Rect rect;  // destination rect to render.
  Vec2d position;
  double start_time;

 public:
  LevelObject(SDL_Renderer* renderer, double start_time_, int w, int h);
  ~LevelObject();
  void SetRect(int x, int y, int w, int h);
  SDL_Rect GetRect();
  bool LoadImage(SDL_Renderer* renderer, const char* path);
  virtual void Draw() = 0;
};

#endif  // !LEVEL_OBJECT