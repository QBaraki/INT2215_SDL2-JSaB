#ifndef TEXTURE_H

#include <string>
#include <map>

#include <SDL2/SDL_image.h>

namespace mTexture {

inline std::map<std::string, SDL_Texture*> textures;

void Destroy();
void CloseImage(const std::string& path);
void CloseImage(SDL_Texture*& texture);
SDL_Texture* LoadImage(SDL_Renderer* renderer, const std::string& path);

}  // namespace mTexture

#endif  // !TEXTURE_H