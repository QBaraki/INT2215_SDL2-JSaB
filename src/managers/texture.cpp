#include "texture.h"

#include <iostream>

#include <SDL2/SDL.h>

#ifdef NDEBUG
#define cerr \
  if (0)     \
  std::cerr
#else
using std::cerr;
#endif  // NDEBUG

void mTexture::Destroy() {
  for (auto& p : textures) {
    CloseImage(p.second);
  }
}

void mTexture::CloseImage(const std::string& path) {
  if (!textures.count(path) || textures[path] == nullptr) {
    cerr << "mTexture::CloseImage(): Skipped closing the texture with path " << path << " since it's not loaded yet!\n";
    return;
  }
  cerr << "mTexture::CloseImage(): Closing the texture with path " << path << "... ";
  CloseImage(textures[path]);
}

void mTexture::CloseImage(SDL_Texture* &texture) {
  SDL_DestroyTexture(texture);
  cerr << "mTexture::CloseImage(): Closed texture from address " << texture << '\n';
  texture = nullptr;
}

SDL_Texture* mTexture::LoadImage(SDL_Renderer* renderer, const std::string& path) {
  if (textures.count(path) && textures[path] != nullptr) {
    cerr << "mTexture::LoadImage(): Image with path " << path << " already loaded. Returning the address " << textures[path] << '\n';
    return textures[path];
  }
  SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
  if (texture == nullptr) {
    throw std::runtime_error("mTexture::LoadImage(): Load image " + std::string(path) + " failed!. SDL error: " + IMG_GetError());
    return nullptr;
  }
  cerr << "mTexture::LoadImage(): Loaded image " << path << " with address " << texture << '\n';
  textures[path] = texture;
  return texture;
}

#undef cerr