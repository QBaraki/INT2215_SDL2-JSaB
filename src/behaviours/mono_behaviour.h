#ifndef MONO_BEHAVIOUR_H
#define MONO_BEHAVIOUR_H

#include <SDL2/SDL_h.>

class MonoBehaviour {
 protected:
  const SDL_Renderer* renderer;

 public:
  MonoBehaviour(const SDL_Renderer* renderer_);
  ~MonoBehaviour();

  virtual void Update();
  virtual void FixedUpdate();
  virtual void Render();
  virtual void EventHandler(SDL_event& event);
  virtual void OnKeyUp(SDL_event& event);
  virtual void OnKeyDown(SDL_event& event);
};

#endif  //!MONO_BEHAVIOUR_H