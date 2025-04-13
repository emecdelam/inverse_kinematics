#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <raylib.h>
#include <stdio.h>
#include <float.h>
#include <raylib.h>
#include <raymath.h>
#include "utils/log.h"


// -- Viewport
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// -- Controls
#define MOVEMENT_SPEED 0.1
#define DEBUG 1

// -- Physics
#define STEP_TIME 0.20 // Step time
#define LINK_SIZE 0.5
#define LINK_NUMBER 6
#define ITERATIONS 1

// -- Environment
#define BORDER 4.0
#define BOUNCE 0.5

// -- Render
#define JOINT_RADIUS 0.1
#define LINK_RADIUS 0.05
#define LINK_SEGMENT 16