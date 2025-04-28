#include "main_menu.h"

#include <SDL2/SDL.h>

#include "common.h"
#include "managers/texture.h"
#include "managers/scene.h"

#include "game/scenes/level.h"

MainMenu::MainMenu(SDL_Renderer* renderer_) : MonoBehaviour(renderer_) {
  background_texture = mTexture::LoadImage(renderer, "assets/UI/menu_background.png");
}

MainMenu::~MainMenu() {
  ;
}

void MainMenu::OnKeyDown(SDL_Event& event) {
  if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
    mScene::stack.emplace(new Level(renderer));
  }
}

void MainMenu::Update() {
  ;
}

void MainMenu::Render() {
  SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderCopy(renderer, background_texture, nullptr, &rect);
}