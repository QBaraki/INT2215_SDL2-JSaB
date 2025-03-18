#include "scene.h"

void mScene::Init(SDL_Renderer* renderer_) {
  renderer = renderer_;
}

void mScene::Pop() {
  if (stack.empty()) {
    return;
  }
  delete stack.top();
  stack.pop();
}

void mScene::Update() {
  if (stack.empty()) {
    return;
  }
  stack.top()->Update();
}

//void mScene::FixedUpdate() {
//  if (stack.empty()) {
//    return;
//  }
//  stack.top()->FixedUpdate();
//}

void mScene::Render() {
  if (stack.empty()) {
    return;
  }
  stack.top()->Render();
}

void mScene::EventHandler(SDL_Event& event) {
  if (stack.empty()) {
    return;
  }
  stack.top()->EventHandler(event);
}

void mScene::Free() {
  while (!stack.empty()) {
    delete stack.top();
    stack.pop();
  }
}