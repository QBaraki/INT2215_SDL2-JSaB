#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "behaviours/mono_behaviour.h"

class PauseMenu : public MonoBehaviour {
  SDL_Texture* background_texture;
  MonoBehaviour* background;

 public:
  PauseMenu(SDL_Renderer* renderer_);
  PauseMenu(SDL_Renderer* renderer_, MonoBehaviour* background_);
  ~PauseMenu();
  void OnKeyDown(SDL_Event& event) override;
  void Update() override;
  //void FixedUpdate() override;
  void Render() override;
};

#endif  // PAUSE_MENU_H