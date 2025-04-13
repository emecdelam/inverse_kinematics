#pragma once

#include "../cons.h"


Camera3D* init_camera();
void move_camera(Vector3 direction);
void move_target(Vector3 target);
void move_camera_forward(float speed);
void move_camera_strafe(float speed);