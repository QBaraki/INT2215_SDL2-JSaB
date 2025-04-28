#include <SDL2/SDL.h>

#include "game/game.h"

#include <iostream>

int main(int argc, char* argv[]) {
  Game game;
  try {
    game.InitGameLoop();
  } catch (std::runtime_error& err) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "An error occurred", err.what(), NULL);
    return -1;
  }
  return 0;
}