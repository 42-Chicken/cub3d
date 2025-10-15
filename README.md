# cub3D — A tiny Wolfenstein-style raycaster

> A 42 project that explores ray‑casting by rendering a 3D view of a 2D maze using **C** and **MiniLibX**.

<!-- Optional: drop a demo GIF/screenshot here (e.g., docs/preview.gif) -->

---

## Table of contents

* [Overview](#overview)
* [Tech stack](#tech-stack)
* [Implementation details](#implementation-details)

  * [Ray‑casting pipeline (DDA)](#ray-casting-pipeline-dda)
  * [Subsystems](#subsystems)
* [Project layout](#project-layout)
* [Getting started](#getting-started)

  * [Prerequisites](#prerequisites)
  * [Clone](#clone)
  * [Build](#build)
  * [Run](#run)
* [Map (`.cub`) format](#map-cub-format)
* [Controls](#controls)
* [Troubleshooting](#troubleshooting)
* [Contributing](#contributing)
* [License](#license)

---

## Overview

`cub3D` renders a first‑person view inside a maze by casting rays from the player’s camera to the scene’s walls.
You provide a configuration/map file (`.cub`) that defines textures, colors and a 2D map grid; the engine turns that into a simple, real‑time 3D experience.

Core goals:

* Parse a `.cub` file (textures, colors, map, player spawn)
* Validate the map (closed, valid chars, single spawn)
* Render walls via **ray‑casting** (DDA)
* Draw textured columns with correct perspective
* Handle input & collision
* (Optionally) render sprites, minimap, UI, doors, etc.

---

## Tech stack

* **Language:** C (C99‑ish, 42 Norm)
* **Graphics:** [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx)

  * **macOS:** `-lmlx -framework OpenGL -framework AppKit`
  * **Linux:** `-lmlx -lXext -lX11 -lm` (plus X11 dev packages)
* **Build:** `Makefile` (targets typically: `all`, `clean`, `fclean`, `re`, and sometimes `bonus`)
* **OS:** macOS or Linux (X11)

> ℹ️ Exact targets and library paths may differ in your Makefile; adjust the commands below accordingly.

---

## Implementation details

### Ray‑casting pipeline (DDA)

1. For each vertical screen column, cast a ray from the camera through that column in camera space.
2. Step the ray across the grid using **DDA** until it hits a wall.
3. Compute distance to the hit, then determine the wall slice height by inverse‑distance projection.
4. Sample the correct texture column (based on which face was hit and hit coordinate) and draw the vertical strip.
5. Repeat for all columns to form the frame.

### Subsystems

* **Parser & validator:**

  * Reads `.cub` file: texture paths for `NO/SO/WE/EA`, floor/ceiling colors, then the map.
  * Ensures a single player start (`N/S/E/W`) and a **closed** map (no leaks into the void).
* **Game loop:**

  * Polls events, updates player movement with collision, renders a new frame each tick.
* **Textures:**

  * Loads XPM (or PNG if your MLX variant supports it); computes texture X coordinate from hit point.
* **(Optional) Sprites:**

  * Projected and depth‑sorted using a **z‑buffer** (re‑use column distances).
* **(Optional) Minimap & HUD:**

  * 2D overlay for debugging/navigation.

---

## Project layout

> Your tree may differ slightly; this is the conventional structure.

```
cub3d/
├─ inc/                 # headers (engine, parser, math, mlx glue)
├─ src/
│  ├─ core/             # main, init, loop
│  ├─ render/           # raycasting, dda, textures, sprites, zbuf
│  ├─ parse/            # .cub parsing, validation, errors
│  ├─ game/             # input, movement, collision
│  └─ utils/            # lib-style helpers
├─ assets/
│  ├─ textures/         # .xpm textures (NO/SO/WE/EA, sprites)
│  └─ maps/             # example .cub maps
├─ mlx/                 # MiniLibX (vendored or submodule) [optional]
├─ Makefile
└─ README.md
```

---

## Getting started

### Prerequisites

**macOS**

* Xcode Command Line Tools:

  ```bash
  xcode-select --install
  ```
* MiniLibX: vendored in `mlx/` *or* installed system‑wide (paths must match your Makefile).

**Linux (Debian/Ubuntu)**

```bash
sudo apt update
sudo apt install build-essential libx11-dev libxext-dev
# Some MLX forks also need:
# sudo apt install libbsd-dev libxrandr-dev libxi-dev
```

> If MLX is a submodule, you’ll init it after cloning.

### Clone

```bash
git clone https://github.com/42Chicken/cub3d.git
cd cub3d
# If MiniLibX (or any deps) are submodules:
git submodule update --init --recursive
```

### Build

```bash
# Standard build (adjust if your Makefile uses a different target)
make

# Rebuild from scratch
make re

# Cleanup
make clean    # object files only
make fclean   # binaries + objects

# Optional bonus target if provided by your Makefile
make bonus
```

If you see linker errors about `AppKit`/`OpenGL` on macOS or `X11` on Linux, double‑check the library flags and include/library paths in your `Makefile`.

### Run

```bash
# Basic run with an example map
./cub3D assets/maps/example.cub

# Or (if you built a bonus target)
./cub3D_bonus assets/maps/example_bonus.cub
```

> Replace paths with your actual map files in `assets/maps/`.

---

## Map (`.cub`) format

A typical file looks like:

```
NO assets/textures/wall_north.xpm
SO assets/textures/wall_south.xpm
WE assets/textures/wall_west.xpm
EA assets/textures/wall_east.xpm

F  100,100,100       # floor color (R,G,B)
C  200,200,255       # ceiling color (R,G,B)

/* Map: 1=wall, 0=floor, space=void,
   N/S/E/W = player spawn + facing,
   2 (optional) = sprite/object */
1111111111
1000000001
10N0000001
1000200001
1111111111
```

**Rules:**

* Exactly one player start (`N`, `S`, `E`, or `W`).
* Map must be **closed** by walls (no leaks to spaces outside).
* Only the allowed characters appear.
* All texture paths are valid/readable.
* Colors are valid `0–255` RGB triples.

---

## Controls

* **W / A / S / D** – Move/strafe
* **← / →** or **Q / E** – Rotate view
* **Esc** – Quit
* *(Optional extras if implemented)* **M** minimap, **I** HUD, **O** crosshair, **L** shadows

> The exact bindings depend on your input module; adjust here if you use different keys.

---

## Troubleshooting

* **Black window / nothing renders**
  Check texture paths and map validity; ensure your `dda` hits compute wall orientation and texture X correctly.

* **Weird fisheye / wrong wall heights**
  Use the **perpendicular** distance to the wall (correct the ray length by removing the camera plane component).

* **Gaps at map edges / crashes**
  Your map likely isn’t closed; run a flood‑fill validator from the player position to ensure no leak to the void.

* **Linker errors (macOS)**
  Ensure `-lmlx -framework OpenGL -framework AppKit` and your `mlx` headers/libs paths are correct.

* **Linker errors (Linux)**
  Ensure `-lmlx -lXext -lX11 -lm` and that `libx11-dev libxext-dev` (and optionally `libbsd-dev libxrandr-dev libxi-dev`) are installed.

---

## Contributing

PRs and issues are welcome!
For 42 students, please respect the **Norm** and keep the mandatory vs. bonus parts separate if your subject requires it.

---

## License

This project is part of the 42 curriculum. See the repository’s **LICENSE** file (if present) for details.
Textures and third‑party assets in `assets/` keep their original licenses.
