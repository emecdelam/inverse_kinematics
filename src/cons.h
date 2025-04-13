#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include <stdio.h>
#include <float.h>
#include <raylib.h>
#include <raymath.h>
#include "utils/log.h"
#include "utils/vec.h"

// -- Viewport
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// -- Controls
#define MOVEMENT_SPEED 0.1
#define DEBUG 1

// -- Physics
#define STEP_TIME 0.20 // Step time
#define LINK_SIZE 1
#define LINK_NUMBER 4
#define IV_ITERATIONS 1
#define NODE_SPACING 0.2
#define GRAVITY ((Vector3){0, -9.81, 0})
#define VERLET_ITERATIONS 8

// -- Environment
#define BORDER 4.0
#define BOUNCE 0.5

// -- Render
#define JOINT_RADIUS 0.1
#define LINK_RADIUS 0.05
#define LINK_SEGMENT 16