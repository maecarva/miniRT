# minirt

> "minirt" Project – École 42 Paris

## Overview

`minirt` is a basic ray tracer that renders 3D scenes from simple scene descriptions. Built as part of the 42 Paris curriculum, this project taught me fundamental principles of computer graphics, such as ray-object intersections, shading, and multi-threaded rendering.

## Key Features

- **Ray Tracing Core:** Calculates ray-sphere, ray-plane, ray-cylinder, and ray-cone intersections.
- **Shading Model:** Implements Phong illumination (ambient, diffuse, specular) for realistic lighting.
- **Texture Mapping:** Applies 2D textures to objects for added visual detail.
- **Multi-threaded Rendering:** Splits the image into segments and renders in parallel to improve performance.
- **Scene Parsing:** Reads `.rt` files defining camera, lights, and objects with validation.
- **Hook System:** Handles user input (keyboard/mouse) for dynamic transformations and workflow.

## Installation

```bash
# Clone the repository
git clone https://github.com/maecarva/miniRT.git
cd minirt/minirt
make
```

## Usage

```bash
# Run the ray tracer with a scene file
./minirt ../scenes/00_single_sphere.rt

# Controls
- W/A/S/D: move camera
- Arrow keys: turn camera
- CTRL: move camera down
- SPACE: move camera up
- Mouse left-click: Simulate a ray and intersect it with scene
```

## Skills Gained

- Developed a **ray tracer** from scratch: ray generation, intersection tests, and pixel coloring.
- Implemented **Phong shading** and **texture mapping** for realistic material rendering.
- Utilized **multi-threading** (`pthread`) to accelerate rendering.
- Parsed and validated a **custom scene file format**.
- Managed graphical output and event hooks using **MiniLibX**.

## Project Structure

```plaintext
minirt/
├── include/               			# Project headers (data structures, constants)
├── libs/                  			# Third-party libraries
│   ├── gnl/               			# get_next_line utility
│   ├── libft/             			# Custom C library (libft)
│   └── minilibx-linux/    			# MiniLibX graphics library
└── src/                   			# Source files
    └── minirt/
        ├── hooks/             		# Input event handlers (keyboard, mouse)
        ├── intersections/      	# Ray-object intersection functions
        ├── mlx_utils/         		# MiniLibX initialization and image buffer
        ├── parsing/           		# .rt file parser
        │   ├── checks/            	# Validation routines for scene elements
        │   └── object_parsers/    	# Parsers for camera, light, objects
        ├── ray/               		# Ray generation and direction calculations
        ├── render/            		# Image rendering routines
        │   └── multi/            	# Multi-threaded rendering logic
        └── utils/             		# Helper functions (vector math, color ops)
```

## Scenes & Textures

- **scenes/**: Directory containing sample `.rt` files to test different configurations.
- **textures/**: Image files used for texture mapping on objects.
