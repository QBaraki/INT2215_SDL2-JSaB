#ifndef MONO_BEHAVIOUR_H
#define MONO_BEHAVIOUR_H

#include <SDL2/SDL.h>

class MonoBehaviour {
 protected:
  SDL_Renderer* const renderer;

 public:
  MonoBehaviour(SDL_Renderer* const renderer_);
  virtual ~MonoBehaviour();

  virtual void Update();
  //virtual void FixedUpdate();
  virtual void Render();
  virtual void EventHandler(SDL_Event& event);
  virtual void OnKeyUp(SDL_Event& event);
  virtual void OnKeyDown(SDL_Event& event);
};

#endif  //!MONO_BEHAVIOUR_H