#include "texture.h"

#include <iostream>

#include <SDL2/SDL.h>

void mTexture::Destroy() {
  for (auto& p : textures) {
    CloseImage(p.second);
  }
}

void mTexture::CloseImage(const std::string& path) {
  if (!textures.count(path)) {
    std::cout << "mTexture::LoadImage(): Skipped closing the texture with path " << path << " since it's not loaded yet!\n";
    return;
  }
  std::cout << "mTexture::LoadImage(): Closing the texture with path " << path << "... ";
  CloseImage(textures[path]);
}

void mTexture::CloseImage(SDL_Texture* &texture) {
  std::cout << "mTexture::LoadImage(): Closed texture from address " << texture << '\n';
  SDL_DestroyTexture(texture);
  texture = nullptr;
}

SDL_Texture* mTexture::LoadImage(SDL_Renderer* renderer, const std::string& path) {
  if (textures.count(path)) {
    std::cout << "mTexture::LoadImage(): Image with path " << path << " already loaded. Returning the address " << textures[path] << '\n';
    return textures[path];
  }
  SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
  if (texture == nullptr) {
    throw std::runtime_error("mTexture::LoadImage(): Load image " + std::string(path) + " failed!. SDL error: " + IMG_GetError());
    return nullptr;
  }
  std::cout << "mTexture::LoadImage(): Loaded image " << path << " with address " << texture << '\n';
  textures[path] = texture;
  return texture;
}