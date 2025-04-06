#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include <memory>
#include <stack>

#include "behaviours/mono_behaviour.h"

namespace mScene {

inline SDL_Renderer* renderer = nullptr;
inline std::stack<MonoBehaviour*> stack;

void Init(SDL_Renderer* renderer_);
void Pop();
void Update();
void FixedUpdate();
void Render();
void EventHandler(SDL_Event& event);
void Free();

}  // namespace my_scene

#endif  // !SCENE_H