#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include <map>

#include "behaviours/mono_behaviour.h"
#include "geometry/vec2d.h"

class Player : public MonoBehaviour {
  std::map<Uint32, Vec2d> direction_map = {
      { SDL_SCANCODE_UP, Vec2d(0, -0.28) },
      { SDL_SCANCODE_LEFT, Vec2d(-0.28, 0) },
      { SDL_SCANCODE_DOWN, Vec2d(0, 0.28) },
      { SDL_SCANCODE_RIGHT, Vec2d(0.28, 0) }
    };

  SDL_Texture* texture;
  SDL_Texture* idle_gif;
  SDL_Rect rect;
  Vec2d velocity;
  float angle;
  int size;
  bool is_moving, play_idle;
  bool dashing;
  int dash_cooldown;
  int buffer_frame;  // offset frame to dash when pressed the spacebar
  double invi_time;
  int idle_frame = 0;
  bool key[SDL_NUM_SCANCODES + 1] = {};

 public:
  int hitpoint;
  Vec2d position;
  Vec2d start_position;

  Player(SDL_Renderer* renderer_, int size_, int x_, int y_);
  ~Player();
  void Update() override;
  //void FixedUpdate() override;
  void Render() override;
  int GetSize() const;
  bool IsInvi() const;
  bool OnHit();
  void OnKeyUp(SDL_Event& event) override;
  void OnKeyDown(SDL_Event& event) override;
};

#endif  //!PLAYER_H