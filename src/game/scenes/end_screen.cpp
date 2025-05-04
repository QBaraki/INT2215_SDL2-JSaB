#include "end_screen.h"

#include <SDL2/SDL.h>

#include "common.h"
#include "managers/scene.h"
#include "managers/texture.h"

#include "game/scenes/level.h"

EndScreen::EndScreen(SDL_Renderer* renderer_) : MonoBehaviour(renderer_) {
  texture = mTexture::LoadImage(renderer, "assets/UI/end_screen.png");
}

EndScreen::~EndScreen() {
  ;
}

void EndScreen::OnKeyDown(SDL_Event& event) {
  if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
    mScene::Pop();
    return;
  }
}

void EndScreen::Update() {
  ;
}

void EndScreen::Render() {
  SDL_Rect rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderCopy(renderer, texture, nullptr, &rect);
}