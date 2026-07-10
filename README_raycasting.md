# cub3D

A raycasting-based 3D game engine inspired by Wolfenstein 3D, built with C and MiniLibX. This project implements the DDA (Digital Differential Analyzer) raycasting algorithm as described in [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html).

## Features

**Mandatory:**
- First-person perspective using raycasting (DDA algorithm)
- 4 directional wall textures (N/S/E/W) loaded from XPM files
- Solid-color floor and ceiling
- Map parsing from `.cub` files with validation (closed map, valid chars, player spawn)
- Smooth player movement (WASD) and rotation (arrow keys)
- Collision detection with `COLLISION_MARGIN` wall sliding
- Clean memory management — 0 bytes lost (verified by valgrind)

**Bonus:**
- Animated sprite objects with multiple XPM frames
- Depth-sorted transparent sprite rendering (painter's algorithm + z-buffer)
- Animated doors that open/close (press `E`)
- Interactive mouse-look (hidden pointer, relative motion)
- Minimap overlay showing walls, doors, and player position
- Door-aware collision (closed doors block, open doors pass)

## How Raycasting Works

### Overview

For each of the 1280 vertical strips on screen (`WIDTH`), the engine casts one ray from the player's position into the scene. The ray travels across the 2D grid map cell by cell until it hits a wall. The distance to that wall determines how tall the column should be drawn — closer walls appear taller, mimicking perspective.

### 1. Camera and Ray Setup (`ft_raycasting.c`)

```c
camera_x = 2.0f * col / (float)WIDTH - 1.0f;
ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
```

The player has a **direction vector** (`dir_x`, `dir_y`) and a **camera plane** (`plane_x`, `plane_y`) perpendicular to it. The camera plane represents the screen width in world space — its length defines the field of view (~60°). For each column, `camera_x` maps the pixel column to a value between -1 and 1, and the ray direction is a linear combination of the direction vector and the camera plane. This creates a fan of rays spanning the FOV.

### 2. DDA Initialization (`ft_raycasting_init.c`)

**Delta calculation:**
```c
if (dir_x == 0) delta_x = 1e30;
else delta_x = fabs(1.0 / dir_x);
```

`delta_x` and `delta_y` represent how far the ray must travel along each axis to cross one full grid cell. A ray pointing nearly horizontally has a large `delta_y` (many vertical steps to cross one cell) and vice versa.

**Step and initial side distance:**
```c
if (dir_x < 0) {
    step_x = -1;
    side_x = (player_x - map_x) * delta_x;
} else {
    step_x = 1;
    side_x = (map_x + 1.0 - player_x) * delta_x;
}
```

`step_x`/`step_y` track which direction the ray moves on the grid. `side_x`/`side_y` store the distance along the ray to the **next vertical/horizontal grid line**. For example, if the ray goes left (`dir_x < 0`), the distance to the next vertical line on the left is `(player_x - map_x) * delta_x` — the fractional offset to the previous integer boundary, scaled by `delta_x`.

### 3. DDA Traversal (`ft_raycasting_perform_dda`)

```c
while (hit == 0) {
    if (side_x < side_y) {
        side_x += delta_x;
        map_x += step_x;
        side = 0;  // hit a vertical wall
    } else {
        side_y += delta_y;
        map_y += step_y;
        side = 1;  // hit a horizontal wall
    }
    if (is_wall(map_x, map_y)) hit = 1;
}
```

The DDA loop advances the ray by jumping from grid line to grid line. At each iteration, it picks the closer of the two next intersections (vertical or horizontal) by comparing `side_x` and `side_y`. The chosen axis gets its `side_` accumulator advanced by the corresponding `delta_`, and the map position moves one cell in that direction. When the visited cell is a wall (`'1'` in the map), the loop terminates.

`side` records which type of wall face was hit — 0 for vertical (east/west-facing), 1 for horizontal (north/south-facing). This determines the texture orientation and shading.

### 4. Perpendicular Distance and Wall Height (`ft_raycasting_calc_wall_height`)

```c
if (side == 0)
    perp_dist = (side_x - delta_x);
else
    perp_dist = (side_y - delta_y);
```

The distance used is **perpendicular** to the camera plane, not Euclidean. This prevents the fisheye effect. The formula subtracts `delta_x`/`delta_y` because `side_x` was already incremented past the wall for the next iteration — the actual distance to the wall is the value *before* the overshoot.

```c
wall_height = (int)(HEIGHT / perp_dist);
draw_start = -wall_height / 2 + HEIGHT / 2;
draw_end = wall_height / 2 + HEIGHT / 2;
```

The wall's screen height is inversely proportional to its distance. The `draw_start`/`draw_end` define the vertical span of this column, clamped to screen bounds.

### 5. Wall X-Coordinate and Texture Mapping (`ft_raycasting_calc_wall_x`)

```c
if (side == 0)
    wall_x = player.y + perp_dist * dir_y;
else
    wall_x = player.x + perp_dist * dir_x;
wall_x -= floor(wall_x);
```

`wall_x` is the exact point on the wall where the ray hit, in world coordinates. Taking the fractional part gives a value in [0, 1) that maps horizontally across the wall texture. This is then scaled to the texture width:

```c
tex_x = (int)(wall_x * tex->width);
```

The `side` and direction are also used to flip the texture horizontally when needed, so that west-facing walls don't appear mirrored compared to east-facing ones.

**Texture step for vertical drawing:**
```c
step = (float)tex->height / wall_height;
tex_pos = (draw_start - HEIGHT / 2 + wall_height / 2) * step;
```

The texture is stretched or squished to fit the wall's screen height. The `step` is the ratio of texture pixels to screen pixels. `tex_pos` tracks the current vertical texture coordinate as we iterate through each screen pixel from `draw_start` to `draw_end`.

### 6. Drawing Pipeline (`ft_raycasting_draw_column`)

```c
void ft_raycasting_draw_column(t_game *game, int col) {
    draw_ceiling(game, col);   // fills from y=0 to draw_start
    draw_wall(game, col);       // fills from draw_start to draw_end
    draw_floor(game, col);      // fills from draw_end to HEIGHT
}
```

Each column is drawn top-to-bottom in three passes:

- **Ceiling**: solid color (from `.cub` file) from y=0 to `draw_start`
- **Wall**: textured column using the computed `tex_x` and step-based `tex_y`, with darkening on north/south-facing walls (`color >> 1` & `0x7F7F7F`)
- **Floor**: solid color from `draw_end` to `HEIGHT`

### 7. Sprite Rendering (`ft_sprites_render.c`) — Bonus

Sprites are drawn after all wall columns, using the `z_buffer` for depth testing.

**Transform to camera space:**
```c
spr_x = sp->x - player.x;
spr_y = sp->y - player.y;
inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
transform_x = inv_det * (dir_y * spr_x - dir_x * spr_y);
transform_y = inv_det * (-plane_y * spr_x + plane_x * spr_y);
```

This is the inverse of the camera basis matrix. It transforms the sprite's world position into a coordinate system where `transform_y` is the depth perpendicular to the camera plane (used for sorting and z-buffer comparison) and `transform_x` is the horizontal offset on screen.

**Screen position and size:**
```c
screen_x = (int)((WIDTH / 2) * (1 + transform_x / transform_y));
height = abs((int)(HEIGHT / transform_y));
raw_start_x = -height / 2 + screen_x;
raw_start_y = -height / 2 + HEIGHT / 2;
```

`screen_x` is the horizontal screen position (perspective divide). `height` is the sprite's screen size (inverse depth scaling). The raw bounds are then clamped to screen edges.

**Texture mapping in draw_stripe:**
```c
tex_x = (int)((stripe - raw_start_x) * tex->width / height);
step = (float)tex->height / height;
tex_pos = (start_y - raw_start_y) * step;
```

The sprite texture is mapped using the same step-based approach as walls: `tex_x` is derived from the horizontal position within the sprite column, and `tex_y` advances by `step` for each screen pixel row. Black pixels (color & 0x00FFFFFF == 0) are treated as transparent and skipped.

**Animation system (`ft_sprites_state.c`):**
Each sprite has multiple texture frames. `update_animation` cycles through them at 0.2s intervals. Before rendering, sprites are sorted by distance (bubble sort, descending) so distant sprites render first — the painter's algorithm combined with the per-pixel z-buffer check handles overlaps.

### 8. Doors (`ft_doors_logic.c`) — Bonus

Doors have four states: `DOOR_CLOSED`, `DOOR_OPENING`, `DOOR_OPEN`, `DOOR_CLOSING`. The player presses `E` to toggle a door within `DOOR_INTERACT_DIST` (0.6 cells), validated by a dot product check to ensure the player faces the door.

During the DDA traversal, if the ray hits a `'D'` cell and the door is not fully open, it records the door pointer in `ray.hit_door` and treats it as a wall hit. In the drawing code, the door's `progress` (0 = closed, 1 = fully open) is used to adjust `wall_x`, effectively shrinking the visible portion of the door frame as it slides open:

```c
if (hit_door && hit_door->progress > 0.0f) {
    p = hit_door->progress;
    if (wall_x < p) { tex_x = -1; return; }  // gap: skip drawing
    wall_x = (wall_x - p) / (1.0f - p);       // remap to visible portion
}
```

The gap created by the door opening reveals the floor/ceiling behind it — the drawing pipeline handles this by checking `if (wall_x < progress)` and drawing floor instead of wall.

### 9. Minimap — Bonus

A simple 2D overhead view rendered at a fixed position:
```c
draw_pos.x = MAP_OFFSET_X + (x * MAP_TILE);
draw_pos.y = MAP_OFFSET_Y + (y * MAP_TILE);
```

Each map cell is drawn as a colored rectangle: white for walls, yellow for doors, dark gray for empty space. The player is drawn as a red square at integer map position.

### 10. Player Movement and Collision

**Rotation** applies a 2D rotation matrix to both `dir` and `plane` vectors (the whole camera basis), keeping the FOV intact. **Translation** adds `dir * MOVE_SPEED` for forward/backward and `plane * MOVE_SPEED` for strafing.

**Collision** checks a 3x3 grid of points around the player's intended position, offset by `COLLISION_MARGIN` (0.15 cells). If any of those 9 points lands on a blocked tile (`'1'` or closed door), that axis movement is rejected. The X and Y axes are checked independently, enabling wall sliding — the player can move parallel to a wall even when pressing diagonally into it.

## Project Structure

```
includes/
├── cub3d.h          # Main header — forward declarations and includes
├── defines.h        # All constants (screen size, speeds, colors, keycodes)
├── structs.h        # All data structures (t_game, t_player, t_ray, etc.)
├── raycating.h      # Raycasting function prototypes
├── sprites.h        # Sprite rendering prototypes + t_spr_draw helper struct
├── parser.h         # Map/configuration parsing prototypes
├── player.h         # Player input/movement prototypes
├── textures.h       # Texture loading/sampling prototypes
├── graphics.h       # Pixel/clear drawing prototypes
├── doors.h          # Door logic prototypes
└── libft.h          # Libft header

srcs/
├── main.c                    # Entry point, mlx_loop, draw loop
├── init/init.c               # ft_init_game — initialize MLX, load textures
├── player/
│   ├── player.c              # Movement + collision (mandatory)
│   └── input.c               # Key press/release handlers
├── raycasting/
│   ├── ft_raycasting.c       # Main raycasting loop (1280 rays per frame)
│   ├── ft_raycasting_init.c  # Ray struct setup, delta/step/side calc
│   ├── ft_raycasting_dda.c   # DDA traversal, wall distance, wall_x
│   └── ft_raycasting_draw.c  # Column drawing (ceiling, wall, floor)
├── parser/
│   ├── parser_main.c         # Parse orchestrator
│   ├── parser_elements.c     # Parse texture paths and colors
│   ├── parser_texture.c      # Texture path validation
│   ├── parser_map.c          # Map grid reading
│   ├── parser_map_utils.c    # Map line helpers (strip_newline, etc.)
│   ├── parser_player.c       # Player spawn position/direction
│   ├── parser_color.c        # RGB color parsing
│   ├── parser_validate.c     # Map character & closure validation
│   └── parser_validate_utils.c # Boundary/neighbor/overhang checks
├── textures/ft_textures.c     # Load, sample, select wall textures
├── graphics/draw_utils.c      # put_pixel, clear_image
├── error/ft_free_game.c       # Full cleanup (map, textures, mlx)
└── exit/ft_exit_game.c        # Window close handler

srcs_bonus/                   # Same structure with additions:
├── main.c                    # Adds mouse motion hook, mouse hide
├── player/
│   ├── ft_player_move.c      # Movement (same logic as mandatory)
│   ├── ft_player_collision.c # Collision with door awareness
│   └── input.c               # Adds E key for door interaction
├── sprites/
│   ├── ft_sprites_render.c   # Sprite transform, draw, z-buffer
│   ├── ft_sprites_state.c    # Animation, distance, sorting
│   └── ft_sprites_memory.c   # Load animation frames, free sprites
├── doors/
│   ├── ft_doors_logic.c      # Door state machine, interaction, update
│   └── ft_free_doors.c       # Free door textures and door_map
├── minimap/ft_minimap.c      # 2D overhead minimap drawing
├── parser/
│   ├── parser_sprites.c      # Sprite config parsing from .cub
│   ├── parser_doors.c        # Door positions from map 'D' tiles
│   └── ...                   # Same as mandatory, with bonus extensions
└── error/ft_free_game.c      # Extended cleanup (sprites, doors, z_buffer)
```

## Usage

```bash
# Build mandatory version
make

# Build bonus version
make bonus

# Run
./cub3D maps/mapa.cub
./cub3D_bonus maps/bonus/gamer.cub
```

**Controls:**
| Key | Action |
|-----|--------|
| W / S | Move forward / backward |
| A / D | Strafe left / right |
| ← / → | Rotate left / right |
| Mouse | Look around (bonus only) |
| E | Open / close door (bonus only) |
| ESC / Q | Quit |

**Debug targets:**
```bash
make debug              # Build mandatory with -fsanitize=address
make debug_bonus        # Build bonus with -fsanitize=address
make valgrind ARGS="maps/mapa.cub"           # Valgrind mandatory
make valgrind_bonus ARGS="maps/bonus/gamer.cub"  # Valgrind bonus
```

## Configuration (.cub file format)

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
WE ./path/to/west_texture.xpm
EA ./path/to/east_texture.xpm
F 220,100,100     # Floor color (RGB)
C 100,200,200     # Ceiling color (RGB)

111111
100001
100N01    # N = player spawn facing north
100001
111111
```

**Bonus extensions:**
- `D` on the map defines a door tile
- `SPR <path> <frame_count>` defines sprite animation frames from numbered XPMs (e.g., `path0.xpm`, `path1.xpm`, ...)

The parser validates that the map is fully enclosed by walls, has exactly one player spawn, and contains no invalid characters.

## Technical Choices

- **DDA over grid traversal**: DDA produces the same result as a naive step-by-step ray march but converges faster by jumping directly to grid lines. It also naturally avoids the "overshoot" problem of fixed-step methods.
- **Perpendicular distance**: Using the distance along the camera plane (not Euclidean distance to the hit point) prevents fisheye distortion. The formula `perp_dist = side_x - delta_x` recovers the distance to the wall before the DDA overshot past it.
- **Wall_x from intersection point**: Instead of estimating, the exact world-space hit coordinate is computed using the player position, ray direction, and perpendicular distance. This eliminates texture wobble when the player moves.
- **Step-based texture sampling**: Both walls and sprites use `step = tex_height / screen_height` to map texture rows to screen rows. This avoids off-by-one errors and ensures correct vertical stretching regardless of wall height.
- **No perp_dist clamp**: Removing the distance clamp prevents texture stretching artifacts on very close walls.
- **COLLISION_MARGIN = 0.15**: The player's collision volume has a 0.15-cell margin checked in a 3x3 pattern, enabling smooth wall sliding without getting stuck on corners.
- **Sprite sorting + z-buffer**: Sprites are sorted by distance (painter's algorithm) for correct inter-sprite ordering, while the z-buffer handles per-column visibility against walls. This dual approach handles all common overlapping cases correctly.
- **Norm compliance**: Every function respects the 42 Norm (25 lines max, 4 params max, no `for`/`do...while`/`switch`, specific comment style).

## Resources

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — The primary reference for the DDA algorithm, texture mapping, and sprite rendering
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) — MLX function reference
