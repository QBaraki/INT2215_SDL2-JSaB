#include "mono_behaviour.h"

#include <stdexcept>

MonoBehaviour::MonoBehaviour(SDL_Renderer* renderer_) : renderer(renderer_) {
  if (renderer == nullptr) {
    throw std::runtime_error("MonoBehaviour::MonoBehaviour(): renderer cannot be NULL");
  }
}

MonoBehaviour::~MonoBehaviour() {}

void MonoBehaviour::Update() {}

//void MonoBehaviour::FixedUpdate() {}

void MonoBehaviour::Render() {}

void MonoBehaviour::EventHandler(SDL_Event& event) {
  switch (event.type) {
    case SDL_KEYUP:
      OnKeyUp(event);
      break;
    case SDL_KEYDOWN:
      OnKeyDown(event);
      break;
  }
}

void MonoBehaviour::OnKeyUp(SDL_Event& event) {}

void MonoBehaviour::OnKeyDown(SDL_Event& event) {}