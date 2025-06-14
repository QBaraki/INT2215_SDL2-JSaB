#include "pause_menu.h"

#include <SDL2/SDL.h>

#include "common.h"
#include "managers/scene.h"
#include "managers/texture.h"

#include "game/scenes/level.h"

PauseMenu::PauseMenu(SDL_Renderer* renderer_) : MonoBehaviour(renderer_) {
  Mix_PauseMusic();
  background_texture = mTexture::LoadImage(renderer, "assets/UI/pause_screen.png");
  background = nullptr;
}
PauseMenu::PauseMenu(SDL_Renderer* renderer_, MonoBehaviour* background_) : PauseMenu(renderer_) {
  background_texture = mTexture::LoadImage(renderer, "assets/UI/pause_screen.png");
  background = background_;
}

PauseMenu::~PauseMenu() {
  Mix_ResumeMusic();
}

void PauseMenu::OnKeyDown(SDL_Event& event) {
  if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
    mScene::Pop();
    return;
  }
  if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
    mScene::Pop();
    mScene::Pop();
    return;
  }
  if (event.key.keysym.scancode == SDL_SCANCODE_R) {
    Level* new_level = new Level(renderer);
    mScene::Pop();
    mScene::Pop();
    mScene::stack.emplace(new_level);
    return;
  }
}

void PauseMenu::Update() {
  ;
}

void PauseMenu::Render() {
  background->Render();
  SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderCopy(renderer, background_texture, nullptr, &rect);
}