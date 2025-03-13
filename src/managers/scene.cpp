#include "scene.h"

void my_scene::Init(SDL_Renderer* renderer_) {
  renderer = renderer_;
}

void my_scene::Pop() {
  if (stack.empty()) {
    return;
  }
  delete stack.top();
  stack.pop();
}

void my_scene::Update() {
  if (stack.empty()) {
    return;
  }
  stack.top()->Update();
}

//void my_scene::FixedUpdate() {
//  if (stack.empty()) {
//    return;
//  }
//  stack.top()->FixedUpdate();
//}

void my_scene::Render() {
  if (stack.empty()) {
    return;
  }
  stack.top()->Render();
}

void my_scene::EventHandler(SDL_Event& event) {
  if (stack.empty()) {
    return;
  }
  stack.top()->EventHandler(event);
}