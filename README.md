_This project has been created as part of the 42 curriculum by ruiferna._

# cub3D

## Description

cub3D is a raycasting engine inspired by the world-famous Wolfenstein 3D
(1992), widely considered the first true First Person Shooter in video game
history. The project explores the ray-casting technique to render a dynamic
3D-like view of a maze from a first-person perspective, using only a 2D map
as input.

The engine reads a scene description file (`.cub`) that specifies wall
textures for each cardinal direction (North, South, East, West), floor and
ceiling colors in RGB, and a 2D map of the maze with the player's spawn
position and orientation. It then renders the scene in real-time using the
miniLibX graphics library, allowing the player to navigate the maze with
WASD movement and arrow-key rotation.

## Instructions

### Prerequisites

- `libXext`, `libX11`, `libm` (Linux X11 libraries)
- miniLibX (included in the repository)

```bash
sudo apt-get install libxext-dev libx11-dev
```

### Compilation

| Rule     | Description                                            |
|----------|--------------------------------------------------------|
| `make`   | Compiles the project and produces the `cub3D` binary.  |
| `all`    | Same as `make`.                                        |
| `bonus`  | Same as `make` (bonus features integrated).            |
| `clean`  | Removes object files.                                  |
| `fclean` | Removes object files and the `cub3D` binary.           |
| `re`     | Runs `fclean` then `all`.                              |
| `norm`   | Runs `norminette` on all project source files.         |

```bash
make
```

### Execution

```bash
./cub3D maps/valid_minimal.cub
```

### Scene File Format (`.cub`)

```
NO ./path_to_north_texture
SO ./path_to_south_texture
WE ./path_to_west_texture
EA ./path_to_east_texture
F 220,100,0
C 225,30,0
1111111
1000001
100N001
1000001
1111111
```

- `NO`, `SO`, `WE`, `EA` — texture paths for each wall direction.
- `F` — floor color `R,G,B` (each in [0, 255]).
- `C` — ceiling color `R,G,B` (each in [0, 255]).
- Map chars: `1`=wall, `0`=empty, `N/S/E/W`=spawn, ` `=void, `D`=door (bonus).

### Controls

| Key              | Action                        |
|------------------|-------------------------------|
| `W` / `S`        | Move forward / backward.      |
| `A` / `D`        | Strafe left / right.          |
| `Left` / `Right` | Rotate the view.              |
| `Mouse`          | Rotate the view (bonus).      |
| `E`              | Open/close door (bonus).      |
| `ESC`            | Close window and exit.        |
| Red cross (X)    | Close window and exit.        |

## Bonus Features

1. **Minimap** — a 2D top-down minimap in the top-left corner showing
   walls (white), floor (gray), doors (green), and the player (red dot).
2. **Doors** — place `D` in the map to create a door. Press `E` near a
   door to toggle it open/closed. Open doors show as `O` in the map.
3. **Mouse rotation** — move the mouse left/right to rotate the view.
4. **Animated sprites** — place `2` in the map and declare a sprite
   texture with `SP <base>`; the engine loads `<base>01.xpm..10.xpm`
   and cycles through them.

> Wall collisions are part of the mandatory build (always on).

## Resources

### Classic References

- **Lode's Computer Graphics Tutorial — Raycasting**
  https://lodev.org/cgtutor/raycasting.html
- **Wolfenstein 3D (1992) — id Software**
- **miniLibX** — 42 graphics library
- **42 Norminette** v3.3.55

### AI Usage

AI was used for: parser architecture, edge case identification, norminette
compliance formatting, test scaffolding, and raycasting algorithm
implementation. All code was reviewed, tested, and understood by the student.

## Project Structure

```
cub3D/
├── Makefile
├── README.md
├── includes/cub3d.h
├── src/
│   ├── main.c
│   ├── error/error.c
│   ├── parser/         (10 files — .cub parsing)
│   ├── utils/free_utils.c
│   ├── graphics/       (6 files — mlx, hooks, textures, pixel)
│   ├── raycaster/      (2 files — DDA raycasting)
│   ├── player/         (3 files — movement, rotation, collisions)
│   └── bonus/          (3 files — minimap, doors, mouse)
├── maps/               (test .cub files)
├── assets/             (4 wall textures .xpm)
├── libft/              (personal C library)
├── ft_printf/          (personal printf)
├── get_next_line/      (personal GNL)
└── minilibx-linux/     (42 graphics library)
```
