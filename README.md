# cube3D
The project is a group effort. Its functionality is divided into two parts: "parser" and "renderer". Therefore, the project contains two header files, each including all the necessary structures and functions for the respective part. The "parser" part fills in the required data from a .cub file into its structure, which is then transferred into the "renderer" structure using a set of "converter" functions. This ensures maximum independence in the development of each part.

The project consists of several main components:
- Parser
- Converter
- Controls
- Rendering

## Parser
The parser takes the path to a .cub file, analyzes it, checks for correctness, and fills the necessary structures with data.

## Controls
The control block consists of three parts:
- Keyboard input handling
- Recalculation of player coordinates and direction based on input (move forward/backward, strafe left/right, rotate left/right)
- Program exit (ESC)

### Input Handling
Input handling is managed by three functions:
- `key_press`
- `key_release`
- `close_win`
These functions record the state of the received keycode into an array. If the ESC keycode is received, the program terminates.

### Recalculation of Player Coordinates and Direction

## Rendering
### General Provisions
1. The physical size of a map cell is 1. Therefore, all formulas that compute real coordinates involve fractional parts. This is important!
2. `dir_x/dir_y` is a normalized (length 1) player direction vector (POV). The double values of `dir_x` and `dir_y` represent the offset of the vector’s end relative to its start.
3. `plane_x/plane_y` is the camera plane vector. It is always perpendicular to the player's direction and has a length proportional to the field of view (FOV). The double values of `plane_x` and `plane_y` define the direction and width of the camera plane vector.
4. The variable `camera_x` ranges from -1 to 1 for each step across the screen width (e.g., 1280 values). The greater the screen width, the more rays are cast.
5. For each value of `camera_x`, `ray_dir` is computed as an offset for the ray relative to the player's direction (`dir`), considering the FOV (`plane_x`). This results in a set of 1280 rays from the extreme left to the extreme right, passing through 0. The variables `ray_dir_x` and `ray_dir_y` hold the offset (end) of the current ray vector.

### DDA (Digital Differential Analyzer)
Three key parameter sets are used for the algorithm: `delta_dist`, `step`, and `side_dist`.
1. `delta_dist_x` gives the distance the ray must travel to pass through a cell horizontally (between two vertical sides of a cell). The more vertical the ray, the longer this distance will be. `delta_dist_y` gives the distance for vertical passage (between two horizontal sides of a cell).
2. `step_x` and `step_y` determine which neighboring cell to move to based on the current ray direction:
   - `ray_dir_x < 0` → `step_x = -1`
   - `ray_dir_x > 0` → `step_x = +1`
   - `ray_dir_y < 0` → `step_y = -1`
   - `ray_dir_y > 0` → `step_y = +1`
3. `side_dist_x` and `side_dist_y` are the distances from the player to the last intersection with a vertical side of a cell (x) or a horizontal side (y).

The key part: how the algorithm works as a whole. Initially, `side_dist_x` and `side_dist_y` are calculated as distances to the nearest vertical and horizontal cell sides. The smaller one is selected (e.g., `side_dist_x`), and `delta_dist_x` is added to reach the next vertical side. Now, most likely, `side_dist_x` will exceed the initial `side_dist_y`, so we return to `side_dist_y`, adding `delta_dist_y` to move to the next horizontal side. At each step, we check if the cell is a wall (1) or empty (0). Once we hit a wall, the goal is reached. To get the distance from the player to the wall side, we "roll back" one step. The final distance is stored in `perp_wall_dist`.

### Drawing a Single Vertical Stripe of the Screen
Knowing the distance to the wall and the projection height, we can calculate the wall height. After that, we compute the coordinates for the "start" and "end" of the wall stripe (`draw_start` and `draw_end`). Pixels below `draw_start` are colored as the floor, and those above `draw_end` as the ceiling. Between these points, we draw a stripe from a texture. First, we determine where the ray hit the wall (a value between 0 and 1, since the cell width is 1). Then we determine which column of pixels from the texture corresponds to this coordinate and copy these pixels from the texture into the window buffer, considering scaling.

### Drawing the Full Frame
We sequentially move from one ray to another, applying the DDA algorithm to find wall intersections and drawing the corresponding vertical one-pixel-wide stripes in the window buffer.

## Functionality
`main` creates and initializes the parser structure and fills it with data from the `.cub` file after validation. Then, it initializes the renderer structure and converts the data from the parser into it. After that, functions for input handling and the main loop are set up, and the main loop is started. All core operations are performed in the `render` function, which is executed in the main loop. It retrieves the current time to adjust movement speed, recalculates the player's position and direction based on input, renders the window, and updates it on the screen.
