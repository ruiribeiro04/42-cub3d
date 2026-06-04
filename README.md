# Cub3D - A Raycasting Game Engine

*This project has been created as part of the 42 curriculum by vde-maga.*

## Resources

Thanks [v3x3d](https://v3x3d.itch.io/) for the sprites!

The sprites used were [retro-lines](https://v3x3d.itch.io/retro-lines)

---

## 📋 Description

**Cub3D** is a 3D maze explorer built from scratch using raycasting techniques, inspired by the legendary game **Wolfenstein 3D** (1992). This project demonstrates the fundamental principles of raycasting, graphics rendering, and game loop architecture without relying on any 3D graphics library.

The engine renders a first-person perspective of a maze defined in a `.cub` configuration file, featuring:
- Real-time 3D projection using the **Digital Differential Analysis (DDA)** algorithm
- Textured walls with directional mapping (North, South, East, West)
- Smooth player movement and collision detection
- Configurable floor and ceiling colors
- Interactive controls for navigation and rotation

This project serves as an introduction to computational geometry, low-level graphics programming, and game engine architecture.

---

## 🎯 Features

### Core Functionality
- **Raycasting Engine**: Implements the DDA algorithm for efficient wall detection and distance calculation
- **Texture Mapping**: Dynamic texture selection based on wall orientation
- **Player Movement**: Smooth WASD movement with arrow key rotation
- **Collision System**: Multi-point collision detection preventing wall clipping
- **Map Parsing**: Robust `.cub` file parser with comprehensive validation
- **Error Handling**: Detailed error messages for invalid configurations

### Technical Highlights
- **Performance Optimized**: 60 FPS rendering at 1280x720 resolution
- **Memory Safe**: Comprehensive cleanup and leak prevention
- **Modular Design**: Clean separation of concerns across parsing, rendering, and game logic

---

## 🏗️ Architecture

### Project Structure

```
cub3d/
├── includes/          # Header files
│   ├── cub3d.h       # Main header with function prototypes
│   ├── structs.h     # Data structure definitions
│   ├── defines.h     # Constants and macros
│   ├── raycasting.h  # Raycasting-specific declarations
│   ├── parser.h      # Parser function prototypes
│   ├── graphics.h    # Graphics utilities
│   └── textures.h    # Texture management
├── srcs/             # Source files
│   ├── main.c        # Entry point and game loop
│   ├── init.c        # Initialization routines
│   ├── input.c       # Keyboard input handling
│   ├── player.c      # Player movement and collision
│   ├── parser/       # Map and config parsing
│   ├── raycasting/   # Raycasting implementation
│   ├── textures/     # Texture loading and sampling
│   ├── graphics/     # Rendering utilities
│   └── exit/         # Cleanup and error handling
├── libs/             # External libraries
│   └── libft/        # Custom C library
├── maps/             # Example map files
├── textures/         # Wall texture assets
└── Makefile          # Build configuration
```

### Data Structures

#### Game State (`t_game`)
```c
typedef struct s_game
{
    void        *mlx;              // MiniLibX instance
    void        *win;              // Window pointer
    void        *img;              // Image buffer
    char        *data;             // Pixel data pointer
    int         map_width;         // Map dimensions
    int         map_height;
    char        **map;             // 2D map array
    t_player    player;            // Player state
    t_ray       ray;               // Current ray data
    t_texture   tex_north;         // Wall textures
    t_texture   tex_south;
    t_texture   tex_east;
    t_texture   tex_west;
    int         floor_color;       // RGB colors
    int         ceiling_color;
} t_game;
```

#### Player State (`t_player`)
```c
typedef struct s_player
{
    float   x;                     // Position in world space
    float   y;
    float   angle;                 // Viewing direction (radians)
    bool    key_up;                // Movement flags
    bool    key_down;
    bool    key_left;
    bool    key_right;
    bool    left_rotate;           // Rotation flags
    bool    right_rotate;
} t_player;
```

#### Ray Information (`t_ray`)
```c
typedef struct s_ray
{
    float   dir_x;                 // Ray direction vector
    float   dir_y;
    float   delta_x;               // DDA step distances
    float   delta_y;
    float   side_x;                // Distance to next grid line
    float   side_y;
    float   perp_dist;             // Perpendicular wall distance
    int     step_x;                // Direction on grid (-1 or 1)
    int     step_y;
    int     map_x;                 // Current grid position
    int     map_y;
    int     side;                  // Wall orientation (0=X, 1=Y)
    int     wall_height;           // Projected wall height
    int     draw_start;            // Screen column bounds
    int     draw_end;
    float   wall_x;                // Exact hit position [0, 1]
    int     tex_x;                 // Texture column index
} t_ray;
```

---

## 🔬 Implementation Details

### Raycasting Algorithm

The core rendering technique follows these steps:

#### 1. Ray Initialization
```c
void ft_raycasting_init_ray(t_game *game, float angle)
{
    game->ray.dir_x = cos(angle);
    game->ray.dir_y = sin(angle);
    game->ray.map_x = (int)(game->player.x / BLOCK);
    game->ray.map_y = (int)(game->player.y / BLOCK);
    
    // Calculate DDA step distances
    game->ray.delta_x = fabs(1 / game->ray.dir_x);
    game->ray.delta_y = fabs(1 / game->ray.dir_y);
}
```

#### 2. DDA (Digital Differential Analysis)
The DDA algorithm efficiently steps through grid cells until hitting a wall:

```c
void ft_raycasting_perform_dda(t_game *game)
{
    int hit = 0;
    
    while (hit == 0)
    {
        // Step to next grid cell based on shortest distance
        if (game->ray.side_x < game->ray.side_y)
        {
            game->ray.side_x += game->ray.delta_x;
            game->ray.map_x += game->ray.step_x;
            game->ray.side = 0;  // Hit X-side wall
        }
        else
        {
            game->ray.side_y += game->ray.delta_y;
            game->ray.map_y += game->ray.step_y;
            game->ray.side = 1;  // Hit Y-side wall
        }
        
        if (ft_raycasting_is_wall(game, game->ray.map_x, game->ray.map_y))
            hit = 1;
    }
}
```

#### 3. Wall Height Calculation
```c
void ft_raycasting_calc_wall_height(t_game *game, float angle)
{
    // Calculate perpendicular distance to avoid fisheye effect
    if (game->ray.side == 0)
        game->ray.perp_dist = (game->ray.map_x - game->player.x / BLOCK 
                               + (1 - game->ray.step_x) / 2) / game->ray.dir_x;
    else
        game->ray.perp_dist = (game->ray.map_y - game->player.y / BLOCK 
                               + (1 - game->ray.step_y) / 2) / game->ray.dir_y;
    
    // Project wall height onto screen
    game->ray.wall_height = (int)(HEIGHT / (game->ray.perp_dist * BLOCK));
    game->ray.draw_start = (HEIGHT / 2) - (game->ray.wall_height / 2);
    game->ray.draw_end = (HEIGHT / 2) + (game->ray.wall_height / 2);
}
```

### Texture Mapping

#### Texture Selection
```c
t_texture *ft_get_wall_texture(t_game *game)
{
    if (game->ray.side == 0)  // X-side walls
    {
        if (game->ray.step_x < 0)
            return (&game->tex_east);
        else
            return (&game->tex_west);
    }
    else  // Y-side walls
    {
        if (game->ray.step_y < 0)
            return (&game->tex_south);
        else
            return (&game->tex_north);
    }
}
```

#### Texture Sampling
The engine calculates the exact hit position on the wall (`wall_x`) to determine which texture column to sample, then maps screen Y-coordinates to texture Y-coordinates for each pixel.

### Player Movement

#### Collision Detection
```c
static int ft_player_check_collision(t_game *game, float x, float y)
{
    int map_x, map_y;
    
    // Check 3x3 grid around player with margin
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            map_x = (int)((x + i * COLLISION_MARGIN) / BLOCK);
            map_y = (int)((y + j * COLLISION_MARGIN) / BLOCK);
            
            if (game->map[map_y][map_x] == '1')
                return (1);  // Collision detected
        }
    }
    return (0);
}
```

#### Movement System
```c
void ft_player_move(t_game *game)
{
    float cos_a = cos(game->player.angle);
    float sin_a = sin(game->player.angle);
    float new_x, new_y;
    
    // Forward/backward movement
    if (game->player.key_up)
    {
        new_x = game->player.x + cos_a * MOVE_SPEED;
        new_y = game->player.y + sin_a * MOVE_SPEED;
        if (!ft_player_check_collision(game, new_x, new_y))
        {
            game->player.x = new_x;
            game->player.y = new_y;
        }
    }
    
    // Rotation
    if (game->player.left_rotate)
        game->player.angle -= ROTATE_SPEED;
    if (game->player.right_rotate)
        game->player.angle += ROTATE_SPEED;
}
```

### Map Parsing

#### Map File Format (`.cub`)
```
NO textures/north.xpm
SO textures/south.xpm
WE textures/west.xpm
EA textures/east.xpm

F 100,150,200
C 50,50,50

1111111
1000001
10N0001
1000001
1111111
```

**Elements:**
- `NO`, `SO`, `WE`, `EA`: Texture paths for each wall direction
- `F`: Floor color (RGB, 0-255)
- `C`: Ceiling color (RGB, 0-255)
- Map grid: `1` = wall, `0` = empty space, `N/S/E/W` = player spawn

#### Validation Rules
```c
int ft_validate_map_closed(t_game *game)
{
    // 1. Check outer boundaries are walls
    // 2. Validate no empty spaces adjacent to void
    // 3. Ensure single player spawn point
    // 4. Verify all characters are valid (0, 1, N, S, E, W)
}
```

---

## 🚀 Instructions

### Prerequisites

- **OS**: Linux (X11 required)
- **Compiler**: GCC or Clang with C99 support
- **Libraries**: 
  - MiniLibX (included in project)
  - X11 development headers (`libx11-dev`, `libxext-dev`)
  - Math library (`libm`)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/ruiribeiro04/42-cub3d.git
   cd 42-cub3d/cub3d
   ```

2. **Install dependencies** (Debian/Ubuntu)
   ```bash
   sudo apt-get update
   sudo apt-get install gcc make libx11-dev libxext-dev libbsd-dev
   ```

3. **Compile the project**
   ```bash
   make
   ```

   This will:
   - Compile the custom `libft` library
   - Build the MiniLibX library
   - Compile all source files with flags: `-Wall -Wextra -Werror`
   - Generate the `cub3D` executable

### Norminette

```bash
make norminette
```

Runs norminette on `srcs/`, `srcs_bonus/`, and `includes/` with the full default ruleset (norminette v3 ignores `-R` rule-suppression flags — they exist only for v2 backward compatibility). Output is saved to `norminette.log`. The recipe uses `pipefail`, so a non-zero norminette exit fails the `make` target.

### Usage

```bash
./cub3D <map_file.cub>
```

**Example:**
```bash
./cub3D maps/small_square.cub
```

### Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate view left |
| `→` | Rotate view right |
| `ESC` | Exit game |

### Additional Make Commands

```bash
make clean         # Remove object files
make fclean        # Remove objects and executable
make re            # Recompile everything
make debug         # Compile with debug symbols and AddressSanitizer
```

### Creating Custom Maps

1. Create a `.cub` file with the required elements:
   ```
   NO path/to/north_texture.xpm
   SO path/to/south_texture.xpm
   WE path/to/west_texture.xpm
   EA path/to/east_texture.xpm
   
   F 220,100,0
   C 135,206,250
   
   111111
   1N0001
   100001
   111111
   ```

2. **Map Requirements:**
   - Must be surrounded by walls (`1`)
   - Exactly one player spawn point (`N`, `S`, `E`, or `W`)
   - Valid characters: `0` (empty), `1` (wall), `N/S/E/W` (spawn)
   - No gaps in outer walls

3. Run your map:
   ```bash
   ./cub3D your_map.cub
   ```

---

## 📚 Resources

### Classic References

#### Raycasting Theory
- [**Lode's Raycasting Tutorial**](https://lodev.org/cgtutor/raycasting.html) - Comprehensive guide to raycasting fundamentals (primary reference)
- [**Wolfenstein 3D Source Code Review**](https://fabiensanglard.net/wolf3d/) by Fabien Sanglard
- [**Ray-Casting Tutorial for Game Development**](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) by F. Permadi

#### Graphics Programming
- [**Computer Graphics: Principles and Practice**](https://www.amazon.com/Computer-Graphics-Principles-Practice-3rd/dp/0321399528) (3rd Edition) - Foley et al.
- [**MiniLibX Documentation**](https://harm-smits.github.io/42docs/libs/minilibx) - Official 42 graphics library guide

#### Algorithms
- [**Digital Differential Analyzer (DDA)**](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) - Wikipedia article on line drawing algorithm
- [**Bresenham's Line Algorithm**](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) - Alternative grid traversal method

### Documentation
- [**42 Cub3D Subject**](https://cdn.intra.42.fr/pdf/pdf/960/cub3d.en.pdf) - Official project requirements
- [**X11 Programming Manual**](https://tronche.com/gui/x/xlib/) - X Window System reference

### Additional Resources
- [**Game Engine Architecture**](https://www.gameenginebook.com/) by Jason Gregory
- [**3D Math Primer for Graphics and Game Development**](https://gamemath.com/book/) by Fletcher Dunn & Ian Parberry

---

## 🤖 AI Usage

Artificial Intelligence tools were utilized in the following aspects of this project:

### Code Development
- **GitHub Copilot**: Used for autocompletion suggestions and boilerplate code generation, particularly in:
  - Parser validation functions
  - Error handling routines
  - Memory cleanup functions
  
  **Note**: All AI-generated suggestions were thoroughly reviewed, tested, and often modified to meet project requirements and 42 Norm standards.

### Documentation
- **ChatGPT (GPT-4)**: Assisted in:
  - Clarifying raycasting mathematical concepts
  - Debugging complex geometry calculations
  - Generating initial documentation structure (this README)
  
  **Verification**: All technical explanations were cross-referenced with authoritative sources listed above.

### Learning & Research
- **AI-powered search tools**: Used to quickly locate relevant documentation and tutorials on:
  - DDA algorithm optimization
  - MiniLibX function usage
  - Texture mapping techniques

### Scope Limitations
AI was **NOT** used for:
- Core algorithm implementation (raycasting, DDA, collision detection)
- Map parsing logic
- Overall architecture design
- Project-specific problem-solving

All critical code sections were written manually with human understanding of the underlying mathematics and computer graphics principles.

---

## 🎓 Learning Outcomes

This project provided hands-on experience with:
- **Computational Geometry**: Vector mathematics, trigonometry, and spatial algorithms
- **Graphics Programming**: Pixel manipulation, rendering pipelines, and performance optimization
- **Memory Management**: Manual allocation/deallocation, leak prevention, and buffer handling
- **Software Architecture**: Modular design, separation of concerns, and API design
- **Algorithm Implementation**: Translating mathematical concepts into efficient code
- **Debugging Complex Systems**: Tracing visual artifacts back to mathematical errors

---

## 📝 Technical Notes

### Performance Considerations
- **Resolution**: 1280x720 chosen to balance quality and performance
- **FOV**: 60° (π/3 radians) provides natural perspective
- **Block Size**: 64 pixels per map unit for sufficient precision
- **Collision Margin**: 5 pixels prevents wall clipping while maintaining smooth movement

### Known Limitations
- No floor/ceiling textures (solid colors only)
- Static lighting (no shadows or dynamic lights)
- No sprite rendering (enemies, objects)
- Single-level maps only

### Norm Compliance
This project adheres to the **42 Norm**, including:
- Maximum 25 lines per function
- Maximum 5 functions per file
- No more than 4 parameters per function
- Strict formatting and naming conventions

---

## 🏆 Acknowledgments

- **42 School** for the project subject and educational framework
- **Lode Vandevenne** for the exceptional raycasting tutorial
- **id Software** for pioneering the raycasting technique in Wolfenstein 3D
- **42 Porto community** for peer reviews and debugging assistance

---

## 📄 License

This project is part of the 42 School curriculum and is subject to the school's policies. The code is available for educational purposes.

---

**Project Status**: ✅ Complete  
**Grade**: [Pending evaluation]  
**Submission Date**: February 2026

---

*Developed with passion for computer graphics and game engines. Enjoy exploring the maze! 🎮*
