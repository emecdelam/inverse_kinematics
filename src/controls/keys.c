#include "../cons.h"
#include "camera.c"


void handle_key(){

    // -- Movements
    if (IsKeyDown(KEY_RIGHT)) {
        move_camera_strafe(MOVEMENT_SPEED);
    }
    if (IsKeyDown(KEY_LEFT)) {
        move_camera_strafe(-MOVEMENT_SPEED);
    }
    if (IsKeyDown(KEY_PAGE_UP)){
        move_camera((Vector3){0.0, MOVEMENT_SPEED, 0.0});
    }
    if (IsKeyDown(KEY_PAGE_DOWN)){
        move_camera((Vector3){0.0, -MOVEMENT_SPEED, 0.0});
    }
    if (IsKeyDown(KEY_DOWN)) {
        move_camera_forward(MOVEMENT_SPEED);
    }
    if (IsKeyDown(KEY_UP)) {
        move_camera_forward(-MOVEMENT_SPEED);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
        move_target((Vector3){-GetMouseDelta().x*0.05f, -GetMouseDelta().y*0.05f, 0.0f});
    }
}