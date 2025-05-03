#pragma once

#include <SDL2/SDL_mixer.h>

#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

#include "common.h"
#include "game/entities/level_object.h"
#include "game/entities/bullet/saw.h"
#include "game/entities/bullet/bubble.h"
#include "game/entities/bullet/block.h"
#include "game/entities/bullet/circle.h"

#define SZ(a) (int)(a.size())

namespace PlaygroundLevel {

inline int GetRando(std::mt19937 &rng, int L, int R, int prev, int diff) {
  int x;
  while (true) {
    x = std::uniform_int_distribution<int>(L, R)(rng);
    if (std::abs(x - prev) >= diff)
      break;
    // std::cerr << (x - prev) << ' ' << diff << '\n';
  }
  return x;
}

inline bool LoadLevel(SDL_Renderer* renderer, std::vector<LevelObject*> &object, Mix_Music* &music_player) {
  // Load objects
  int sz;
  std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

  // Section 1: Saw
  object.push_back(new Saw(renderer, 0.790, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 1.440, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 2.090, 50, 1260, 310, {-0.27, 0}));
  object.push_back(new Saw(renderer, 2.530, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 3.180, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 4.250, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 4.900, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 5.600, 50, 1260, 310, {-0.27, 0}));
  object.push_back(new Saw(renderer, 5.985, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 6.640, 50, 1260, 385, {-0.27, 0}));
  object.push_back(new Saw(renderer, 6.850, 50, 1260, 140, {-0.27, 0}));
  object.push_back(new Saw(renderer, 7.180, 50, 1260, 500, {-0.27, 0}));
  object.push_back(new Saw(renderer, 7.505, 50, 1260, 140, {-0.27, 0}));
  for (int rep = 1; rep < 2; ++rep) {  // used to be 6
    for (int i = 0; i < 13; ++i) {
      object.push_back(new Saw(renderer, object[i]->GetStartTime() + rep * 6.935, 50, object[i]->position.x, object[i]->position.y, {-0.27, 0}));
    }
  }

  // Section 2: Bubble
  for (int rep = 0; rep < 20; ++rep) {
    object.push_back(new Bubble(renderer, 8.155 + rep * 1.732, 40, 1160, 70));
    object.push_back(new Bubble(renderer, 9.021 + rep * 1.732, 40, 1160, 630));
  }

  sz = SZ(object);

  // Section 3: Lines
  for (int rep = 0; rep < 2; ++rep) {
    object.push_back(new Block(renderer, 14.850 + rep * 6.93, 0.75f, 0.5f, {950, 0}, {1000, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 15.500 + rep * 6.93, 0.75f, 0.5f, {850, 0}, { 900, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 16.583 + rep * 6.93, 0.75f, 0.5f, {750, 0}, { 800, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 17.235 + rep * 6.93, 0.75f, 0.5f, {650, 0}, { 700, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 17.455 + rep * 6.93, 0.75f, 0.5f, {550, 0}, { 600, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 18.320 + rep * 6.93, 0.75f, 0.5f, {450, 0}, { 500, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 18.970 + rep * 6.93, 0.75f, 0.5f, {350, 0}, { 400, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 20.053 + rep * 6.93, 0.75f, 0.5f, {250, 0}, { 300, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 20.705 + rep * 6.93, 0.75f, 0.5f, {150, 0}, { 200, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 21.025 + rep * 6.93, 0.75f, 0.5f, { 50, 0}, { 100, WINDOW_HEIGHT}));
  }

  // Section 4: Horizontal and Vertical lines

  for (int rep = 0; rep < 2; ++rep) {
    // Horizontal
    object.push_back(new Block(renderer, 28.500 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {200, 0}, {240, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 28.500 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {600, 0}, {640, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 28.500 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {1000, 0}, {1040, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 29.148 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {400, 0}, {440, WINDOW_HEIGHT}));
    object.push_back(new Block(renderer, 29.148 + rep * 3.455, 0.75, -29.8f - rep * 3.455, {800, 0}, {840, WINDOW_HEIGHT}));
    // Vertical
    object.push_back(new Block(renderer, 30.230 + rep * 3.445, 0.75, -31.53 - rep * 3.445, {0, 340}, {WINDOW_WIDTH, 380}));
    object.push_back(new Block(renderer, 30.880 + rep * 3.445, 0.75, -31.53 - rep * 3.445, {0, 140}, {WINDOW_WIDTH, 180}));
    object.push_back(new Block(renderer, 30.880 + rep * 3.445, 0.75, -31.53 - rep * 3.445, {0, 540}, {WINDOW_WIDTH, 580}));
  }
  
  // Section 5: Horizontal line and circles

  for (int rep = 0; rep < 2; ++rep) {
    // I gotta say, this is one of the worst code I have ever written.
    double x = 99999, y = 99999;
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 35.427 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 35.427 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 36.078 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 36.078 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));

    x = GetRando(rng, 200, WINDOW_WIDTH - 200, x, 400);
    y = GetRando(rng, 80, WINDOW_HEIGHT - 80, y, 150);
    object.push_back(new Circle(renderer, 36.725 + rep * 3.445, 1.85f, 0.1f, {x, y}, 300, 2.0f));
    x = GetRando(rng, 200, WINDOW_WIDTH - 200, x, 400);
    y = GetRando(rng, 80, WINDOW_HEIGHT - 80, y, 150);
    object.push_back(new Circle(renderer, 36.824 + rep * 3.445, 1.949f, 0.1f, {x, y}, 300, 2.0f));
    x = GetRando(rng, 200, WINDOW_WIDTH - 200, x, 400);
    y = GetRando(rng, 80, WINDOW_HEIGHT - 80, y, 150);
    object.push_back(new Circle(renderer, 36.924 + rep * 3.445, 2.049f, 0.1f, {x, y}, 300, 2.0f));
    x = GetRando(rng, 200, WINDOW_WIDTH - 200, x, 400);
    y = GetRando(rng, 80, WINDOW_HEIGHT - 80, y, 150);
    object.push_back(new Circle(renderer, 37.049 + rep * 3.445, 2.174f, 0.1f, {x, y}, 300, 2.0f));

    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 37.135 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 37.135 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 37.810 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
    y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
    object.push_back(new Block(renderer, 37.810 + rep * 3.445, 0.75f, 0.65f, {0, y}, {WINDOW_WIDTH, y + 40}));
  }

  // Section 6: Chaining

  // Lasers
  double pos1 = 640;
  double pos2 = 640;
  float laser_width = 10;
  double timer[14] = {42.348, 43.0f, 44.082f, 44.734f, 45.816f, 46.467f, 47.549f, 48.196f, 49.293f, 49.93f, 51.017f, 51.665f, 52.732f, 53.392f};

  // Bubbles
  object.push_back(new Bubble(renderer, 42.8, 40, 1160, 630));
  object.push_back(new Bubble(renderer, 44.566, 40, 70, 630));
  object.push_back(new Bubble(renderer, 46.332, 40, 120, 90));
  object.push_back(new Bubble(renderer, 48.098, 40, 1160, 90));

  object.push_back(new Bubble(renderer, 49.664, 40, 1160, 630));
  object.push_back(new Bubble(renderer, 51.43, 40, 70, 630));
  object.push_back(new Bubble(renderer, 53.196, 40, 120, 90));
  object.push_back(new Bubble(renderer, 54.962, 40, 1160, 90));

  for (int i = 0; i < 14; ++i) {
    object.push_back(new Block(renderer, timer[i], 0.6f, 0.5f, {600, 0}, {680, WINDOW_HEIGHT}));
    for (int rep = 0; i % 2 == 0 && rep < 76; ++rep) {
      object.push_back(new Block(renderer, timer[i], 0.3f, 0.1f, {pos1, 0}, {pos1 + (laser_width - 2), WINDOW_HEIGHT}));
      object.push_back(new Block(renderer, timer[i], 0.3f, 0.1f, {pos2 - (laser_width - 2), 0}, {pos2, WINDOW_HEIGHT}));
      pos1 -= laser_width;
      pos2 += laser_width;
      timer[i] += 0.05f;
    }
    pos1 = 640;
    pos2 = 640;
  }
  object.push_back(new Block(renderer, 54.244, 0.6f, 0.5f, {600, 0}, {680, WINDOW_HEIGHT}));
  object.push_back(new Block(renderer, 54.896, 0.6f, 0.5f, {600, 0}, {680, WINDOW_HEIGHT}));

  // Section 7: Saw line and Circle
  for (int rep = 0; rep < 5; ++rep) {
    for (int i = 0; rep != 4 && i < 15; ++i) {
      object.push_back(new Saw(renderer, 56.202 + rep * 3.461, 50, 1260, i * 48, {-0.18, 0}));
      object.push_back(new Saw(renderer, 56.202 + rep * 3.461, 50, 1260, i * 48, {-0.36, 0}));
      object.push_back(new Saw(renderer, 56.626 + rep * 3.461, 50, 1260, i * 48, {-0.55, 0}));
    }
    if (rep != 4) {
      object.push_back(new Block(renderer, 56.202 + rep * 3.461, 0.0f, 0.35f, {1250, 0}, {1280, 720}));
      object.push_back(new Block(renderer, 56.626 + rep * 3.461, 0.0f, 0.35f, {1250, 0}, {1280, 720}));
    }
    if (rep > 1) {
      for (int i = 0; i < 7; ++i) {
        object.push_back(new Circle(renderer, 63.994 + (rep - 2) * 3.461, 0.82f, 0.66f, {80 + i * 186.0f, 80}, 80, 1.0f));
        object.push_back(new Circle(renderer, 63.994 + (rep - 2) * 3.461, 0.82f, 0.66f, {80 + i * 186.0f, 640}, 80, 1.0f));

        // Chain
        if (rep != 4) {
          object.push_back(new Circle(renderer, 64.800 + (rep - 2) * 3.461 + i * 0.17f, 0.0f, 0.5f, {80 + i * 186.0f, 640}, 80, 1.2f));
          object.push_back(new Circle(renderer, 64.800 + (rep - 2) * 3.461 + i * 0.17f, 0.0f, 0.5f, {80 + i * 186.0f, 80}, 80, 1.2f));
        }
      }
    }
  }

  // Section 8: Music's building up, Circles pushing player into middle
  // Corners
  object.push_back(new Circle(renderer, 70.800, 0.0f, 11.3f, {0, 0}, 10, 0.6f));
  object.push_back(new Circle(renderer, 70.800, 0.0f, 11.3f, {0, WINDOW_HEIGHT}, 10, 0.6f));
  object.push_back(new Circle(renderer, 70.800, 0.0f, 11.3f, {WINDOW_WIDTH, 0}, 10, 0.6f));
  object.push_back(new Circle(renderer, 70.800, 0.0f, 11.3f, {WINDOW_WIDTH, WINDOW_HEIGHT}, 10, 0.6f));
  // Middle
  object.push_back(new Circle(renderer, 70.800, 0.0f, 11.3f, {WINDOW_WIDTH / 2, -200}, 10, 0.6f));                 // top
  object.push_back(new Circle(renderer, 70.800, 0.0f, 11.3f, {WINDOW_WIDTH / 2, WINDOW_HEIGHT + 200}, 10, 0.6f));  // bottom

  // PULSATING
  // Corners
  object.push_back(new Circle(renderer, 82.113, 0.0f, 0.32f, {0, 0}, 400, 0.25));
  object.push_back(new Circle(renderer, 82.613, 0.0f, 0.32f, {0, 0}, 400, 0.25));
  object.push_back(new Circle(renderer, 83.013, 0.0f, 0.6f, {0, 0}, 400, 0.6f));

  object.push_back(new Circle(renderer, 82.113 + 0.05, 0.0f, 0.32f, {WINDOW_WIDTH, 0}, 400, 0.25));
  object.push_back(new Circle(renderer, 82.613 + 0.05, 0.0f, 0.32f, {WINDOW_WIDTH, 0}, 400, 0.25));
  object.push_back(new Circle(renderer, 83.013 + 0.05, 0.0f, 0.55f, {WINDOW_WIDTH, 0}, 400, 0.6f));

  object.push_back(new Circle(renderer, 82.113 + 0.075, 0.0f, 0.32f, {WINDOW_WIDTH, WINDOW_HEIGHT}, 400, 0.25));
  object.push_back(new Circle(renderer, 82.613 + 0.075, 0.0f, 0.32f, {WINDOW_WIDTH, WINDOW_HEIGHT}, 400, 0.25));
  object.push_back(new Circle(renderer, 83.013 + 0.075, 0.0f, 0.525f, {WINDOW_WIDTH, WINDOW_HEIGHT}, 400, 0.6f));

  object.push_back(new Circle(renderer, 82.113 + 0.1, 0.0f, 0.32f, {0, WINDOW_HEIGHT}, 400, 0.25));
  object.push_back(new Circle(renderer, 82.613 + 0.1, 0.0f, 0.32f, {0, WINDOW_HEIGHT}, 400, 0.25));
  object.push_back(new Circle(renderer, 83.013 + 0.1, 0.0f, 0.5f, {0, WINDOW_HEIGHT}, 400, 0.6f));

  // Middle top
  object.push_back(new Circle(renderer, 82.113 + 0.125, 0.0f, 0.32f, {WINDOW_WIDTH / 2, -200}, 400, 0.25));
  object.push_back(new Circle(renderer, 82.613 + 0.125, 0.0f, 0.32f, {WINDOW_WIDTH / 2, -200}, 400, 0.25));
  object.push_back(new Circle(renderer, 83.013 + 0.125, 0.0f, 0.475f, {WINDOW_WIDTH / 2, -200}, 400, 0.6f));
  // Middle bottom
  object.push_back(new Circle(renderer, 82.113 + 0.15, 0.0f, 0.32f, {WINDOW_WIDTH / 2, WINDOW_HEIGHT + 200}, 400, 0.25));
  object.push_back(new Circle(renderer, 82.613 + 0.15, 0.0f, 0.32f, {WINDOW_WIDTH / 2, WINDOW_HEIGHT + 200}, 400, 0.25));
  object.push_back(new Circle(renderer, 83.013 + 0.15, 0.0f, 0.45f, {WINDOW_WIDTH / 2, WINDOW_HEIGHT + 200}, 400, 0.6f));

  // Section 9: Final
  // Last saw chain
  for (int i = 0; i < 16; ++i) {
    object.push_back(new Saw(renderer, 111.600f, 50, 1260, i * 48, {-0.18f, 0}));
  }
  double start_beat = 83.9f, diff_beat = 0.43f;
  int rep = -1;
  int prev_y_circle = 0, circle_type = 0, saw_type = 0;
  for (double cur_beat = start_beat; cur_beat <= 112.0f; cur_beat += diff_beat) {
    rep++;

    // Circle chain
    if (rep % 3 == 0) {
      int y = GetRando(rng, 100, 1180, prev_y_circle, 300);
      prev_y_circle = y;
      if (circle_type) {
        for (int i = 7; i >= 0; --i) {
          object.push_back(new Circle(renderer, cur_beat + (7 - i) * 0.1f, 0.5f, 0.3f, {(double)y, 120.0f * i}, 60, 1.2f));
        }
      } else {
        for (int i = 0; i <= 7; ++i) {
          object.push_back(new Circle(renderer, cur_beat + i * 0.1f, 0.5f, 0.3f, {(double)y, 120.0f * i}, 60, 1.2f));
        }
      }
      circle_type ^= 1;
    }

    // Saw chain (and 2 lazer in the top and bottom)
    if (rep % 4 == 0) {
      for (int i = saw_type ? 14 : 0; cur_beat <= 110.0f && (saw_type ? i >= 8 : i <= 6); (saw_type ? --i : ++i)) {
        int y = i * 48;
        object.push_back(new Saw(renderer, cur_beat, 50, 1260, y, {-0.36, 0}));
      }
      saw_type ^= 1;
      object.push_back(new Block(renderer, cur_beat, 0.5, 1.35f, {0, 0}, {WINDOW_WIDTH, 30}));
      object.push_back(new Block(renderer, cur_beat, 0.5, 1.35f, {0, 690}, {WINDOW_WIDTH, WINDOW_HEIGHT}));
    }

    // Bubble spam
    if (cur_beat <= 111.2f && rep % 2 != 0) {
      int y = GetRando(rng, 100, 620, 0, 0);
      object.push_back(new Bubble(renderer, cur_beat, 40, 1160, y));
    }

    // Laser spam
    double ly = 99999, lx = 99999;

    if (cur_beat <= 111.2f) {
      // Triple laser every 4 beats
      if (rep % 4 == 0) {
        int m = 99999;
        m = GetRando(rng, 10, 80, m, 80);
        if (m > 50) {
          ly = GetRando(rng, 30, WINDOW_HEIGHT - 50, ly, 80);
          object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, {0, ly}, {WINDOW_WIDTH, ly + 30}));
          lx = GetRando(rng, 10, WINDOW_WIDTH - 50, lx, 80);
          object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, {lx, 0}, {lx + 30, WINDOW_HEIGHT}));
          lx = GetRando(rng, 10, WINDOW_WIDTH - 50, lx, 80);
          object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, {lx, 0}, {lx + 30, WINDOW_HEIGHT}));
        } else {
          ly = GetRando(rng, 30, WINDOW_HEIGHT - 50, ly, 80);
          object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, {0, ly}, {WINDOW_WIDTH, ly + 30}));
          ly = GetRando(rng, 30, WINDOW_HEIGHT - 50, ly, 80);
          object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, {0, ly}, {WINDOW_WIDTH, ly + 30}));
          lx = GetRando(rng, 10, WINDOW_WIDTH - 50, lx, 80);
          object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, {lx, 0}, {lx + 30, WINDOW_HEIGHT}));
        }
        // y = GetRando(rng, 10, WINDOW_HEIGHT - 50, y, 80);
        // object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, { 0, y }, { WINDOW_WIDTH, y + 30 }));
      } else if (rep % 2 == 0) {  // Horizontal laser
        ly = GetRando(rng, 30, WINDOW_HEIGHT - 50, ly, 80);
        object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, {0, ly}, {WINDOW_WIDTH, ly + 30}));
        ly = GetRando(rng, 30, WINDOW_HEIGHT - 50, ly, 80);
        object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, {0, ly}, {WINDOW_WIDTH, ly + 30}));
      } else {  // Vertical laser
        lx = GetRando(rng, 10, WINDOW_WIDTH - 50, lx, 80);
        object.push_back(new Block(renderer, cur_beat, 0.5, 0.5f, {lx, 0}, {lx + 30, WINDOW_HEIGHT}));
      }
    }
  }

  // Push spawning objects
  std::vector<LevelObject*> pending;
  for (LevelObject* o : object) {
    std::vector<LevelObject*> spawned = o->Spawn();
    for (auto it : spawned) {
      pending.push_back(it);
    }
  }
  for (auto o : pending) {
    object.push_back(o);
  }

  std::sort(object.begin(), object.end(), [](LevelObject* lhs, LevelObject* rhs) {
      return lhs->GetStartTime() < rhs->GetStartTime();
    });

  // Load music
  music_player = Mix_LoadMUS("assets/musics/mus_corrupted_cut.ogg");
  if (music_player == nullptr) {
    throw std::runtime_error("PlaygroundLevel::LoadLevel(): Failed to load music! SDL error: " + std::string(Mix_GetError()));
    return false;
  }
  return true;
}

}  // namespace PlaygroundLevel

#undef SZ(a)