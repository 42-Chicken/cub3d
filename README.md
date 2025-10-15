# cub3D

> Wolfenstein-inspired raycaster written in C for 42. Reads a `.cub` config, projects the maze with textured walls, and layers HUD, entities, and gameplay systems on top of MiniLibX.

---

# One Line Execution
```bash
git clone git@github.com:42-Chicken/cub3d.git && cd cub3d && make &&./cub3d maps/valids/light_city.cub
```

## Overview

`cub3D` is a compact game engine that turns a 2D grid into a pseudo-3D maze. It parses configuration files, validates the map, builds the world state, and renders a first-person view with textured walls, floors, and sky. On top of the core raycasting loop the project adds menus, HUD overlays, interactable entities (doors, pickups, enemies), mouse and keyboard controls, and an optional A* pathfinding layer for smarter NPCs.

**Highlights**
- Textured raycasting with per-column DDA.
- Animated HUD, minimap, pause/options menus, and weapon hand.
- Entity system handling static props, doors, collectible money, projectiles, and AI soldiers.
- Optional threaded loader and logging utilities to keep the main loop smooth.

---

## Tech Stack

- **Language:** ISO C (42 Norm compliant, compiled with `clang`).
- **Graphics:** [MiniLibX Linux](https://harm-smits.github.io/42docs/libs/minilibx) (`libX11`, `libXext`, `libm`, `z`).
- **Utility library:** `libs/ft_libc` (custom libc-style helpers).
- **Build system:** `Makefile` with optimized `-O3 -flto` flags and incremental object cache.
- **OS targets:** Linux (X11). Porting to macOS requires adjusting the MLX variant and linker flags.

---

## Architecture & Implementation

### Rendering pipeline
1. Build a camera ray for each column based on the player pose and FOV.
2. Run DDA to march the ray through the map grid until a wall or door is hit.
3. Compute perpendicular distance to avoid fisheye distortion and derive the projected wall height.
4. Sample the correct texture column, blend with floor/sky, and draw the pixel strip into an off-screen buffer.
5. Copy the buffer to the MiniLibX window; overlay HUD elements and weapon sprites.

### Core subsystems
- **Parsing (`src/parsing/`)**  
  Validates `.cub` files (texture paths, RGB colors), constructs the map matrix, and populates the initial player spawn and entity descriptors.
- **Gameplay & controls (`src/game/`)**  
  Handles WASD/arrow input, mouse look, collision, entity updates, door logic, enemy AI, and minimap rendering.
- **HUD (`src/game/hud/`)**  
  Draws stats, timers, menus, loading screen, and weapon animations using bitmap fonts loaded from `src/fonts/`.
- **Textures & assets (`src/game/textures/`, `assets/`)**  
  Loads XPM sprites for walls, props, and the skybox; exposes helpers for multi-textured entities.
- **Threads & logs (`src/threads/`, `src/logs/`)**  
  Optional background loader prints progress while assets initialize, keeping startup responsive.
- **Utility layer (`src/utils/`)**  
  Custom allocators (`balloc`), vector math, string helpers, and rendering primitives.

The engine keeps most state inside a single `t_cub3d` structure, passed through initialization, MLX setup, and the main loop (`src/loop.c`). Average FPS is printed on shutdown to help track performance regressions.

---

## Repository Layout

```
assets/          # textures, maps, fonts, HUD images
includes/        # public headers (cub3d.h, structs, constants)
libs/            # ft_libc and minilibx-linux (cloned on demand)
maps/            # subject-compliant sample maps
objects/         # build artifacts (created by make)
src/             # engine sources: parsing, raycaster, HUD, entities, AI
Makefile
README.md
```

---

## Getting Started

### Prerequisites
- A Linux environment with X11 development packages (`build-essential`, `libx11-dev`, `libxext-dev`, `zlib1g-dev`, `libm`).  
- `clang`, `make`, and Git.  
- Network access during the first build so the `Makefile` can clone `minilibx-linux` and `ft_libc` if they are missing.

### Clone
```bash
git clone git@github.com:42-Chicken/cub3d.git
cd cub3d
```

### Build
```bash
# Compile everything (assets and external libs are fetched automatically if absent)
make

# Clean intermediate objects / binaries
make clean
make fclean

# Full rebuild
make re

# Development helpers (valgrind run with a sample map)
make dev
```

### Run
```bash
# Launch with any valid .cub map
./cub3d maps/valids/map.cub

# Use your own map
./cub3d path/to/your_map.cub
```

Run the binary from the project root so relative texture paths resolve correctly. While in-game you can pause, tweak settings, or inspect the minimap depending on the compiled features.

---

## `.cub` Map Format (Quick Reference)

```
NO assets/textures/wall_north.xpm
SO assets/textures/wall_south.xpm
WE assets/textures/wall_west.xpm
EA assets/textures/wall_east.xpm

F 120,120,120       # floor color (RGB 0-255)
C 210,210,255       # ceiling color

1111111111
10N0000001
1000203001
1000000001
1111111111
```

- One player spawn (`N`, `S`, `E`, or `W`).
- Map closed by walls (`1`) and padded with spaces outside.
- Optional entity markers (`2`, `3`, etc.) map to in-game props defined in `src/game/entities/`.

---

## Controls (default)
- `W / A / S / D` - Move and strafe.
- `Arrow Left / Arrow Right` or mouse - Rotate camera.
- `E` - Interact with doors and menus.
- `Space` - Fire current weapon.
- `Esc` - Leave the game (also accessible in pause menu).

---

## Troubleshooting
- **Window opens but nothing draws**  
  Verify the `.cub` file paths and ensure textures exist and are readable.
- **Player slips through walls**  
  Check the map is fully enclosed and run the validator inside `src/parsing/map_checks*.c`.
- **Linker errors about X11**  
  Install `libx11-dev libxext-dev libm-dev zlib1g-dev` (package names may vary by distro).
- **Segfault during load**  
  Run `make dev` to launch under Valgrind with verbose logging; inspect the output in `logs/`.

---

## License

This repository accompanies the 42 curriculum. Unless otherwise noted, the code is shared under the repository's default license; third-party textures and fonts in `assets/` retain their original licenses.
