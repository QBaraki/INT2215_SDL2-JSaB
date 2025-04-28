#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "behaviours/mono_behaviour.h"

class MainMenu : public MonoBehaviour {
  SDL_Texture* background_texture;

 public:
  MainMenu(SDL_Renderer* renderer_);
  ~MainMenu();
  void OnKeyDown(SDL_Event& event) override;
  void Update() override;
  //void FixedUpdate() override;
  void Render() override;
};

#endif  // MAIN_MENU_H