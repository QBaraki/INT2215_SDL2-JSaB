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
  LevelObject();
  ~LevelObject();
  void SetRect(int x, int y, int w, int h);
  SDL_Rect GetRect();
  double GetStartTime();
  bool LoadImage(SDL_Renderer* renderer, const char* path);
  virtual void Update(float delta_time, [[maybe_unused]] float current_time) = 0;
  virtual void Draw(SDL_Renderer* renderer) = 0;
};

#endif  // !LEVEL_OBJECT