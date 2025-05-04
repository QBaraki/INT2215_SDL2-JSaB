#ifndef END_SCREEN_H
#define END_SCREEN_H

#include "behaviours/mono_behaviour.h"

class EndScreen : public MonoBehaviour {
  SDL_Texture* texture;

 public:
  EndScreen(SDL_Renderer* renderer_);
  ~EndScreen();
  void OnKeyDown(SDL_Event& event) override;
  void Update() override;
  //void FixedUpdate() override;
  void Render() override;
};

#endif  //!END_SCREEN_H