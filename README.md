# Just Shapes and Beats clone in SDL2 for INT2215

- **Name**: Bùi Thanh Quang
- **ID**: 24022826
- **Game type**: Bullet hell
- **Score target**: `9.5 - 10.0`

Just Shapes & Beats is an action rhythm video game developed and published by a Canadian indie team "Berzerk Studio".
In the game, players control a colored shape and dodge pink shapes that move to the beat of background music.

I have recreated the first tutorial level ("Corrupted" by Danimal Cannon & Zef) in the game with my interpretation, using [C++](https://en.wikipedia.org/wiki/C++) and [SDL2](https://www.libsdl.org/) for rendering and audio.

Demo link: [YouTube video](https://youtu.be/g5tNeI9mOIs).

## How to run

### Prerequisite

- CMake (version 3.1 or higher)
- vcpkg

### Build and run

Assuming you're in the root directory of the project, run these commands:

```sh
# Build CMake files.
$ cmake -B out -S . -DVCPKG_TARGET=x64-mingw-dynamic -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake

# Build
$ cmake --build out
```

The executable should be compiled in a subfolder in `bin/`.

## How to play

You need to avoid getting hit from pink obstacles, and initially has 4 hitpoints.

You can move with arrow keys and dash with spacebar.
When dashes, the player gains a brief period of invincibility, allowing going through obstacles without harm.

Each obstacles has different ways to harm the player, and will be introduced throughout the level.

You win when you passed all obstacles!

## About graphic and source code

### Graphic

All graphics are hand-drawn using [Affinity Photos 2](https://affinity.serif.com/en-us/photo/).

### Source code

The source code has been structured and implemented from scratch (with the exception of SDL2 library) in Object-Oriented-Programming approach.

Folder structure:
```
├───app
├───assets  <------------- Graphic and audio
│   ├───bullets  <-------- Graphic for bullet objects
│   ├───player  <---------      ...for player
│   ├───UI  <-------------      ...for user interface
│   └───musics  <--------- Audio for the levels
└───src
    ├───behaviours  <----- Base class for almost every object
    ├───game
    │   ├───entities  <--- Entities' implementation
    │   │   └───bullet  <-  ...for bullet objects
    │   ├───levels  <----- Stored level
    │   └───scenes  <----- Stored game scene (menu, level)
    ├───geometry  <------- Geometry library (2D vector)
    ├───managers  <------- To manage texture, audio, ... ingame
    └───utils  <---------- Utilites files
```
