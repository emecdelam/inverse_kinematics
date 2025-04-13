#include "camera.h"

Camera3D __camera = { 0 };


Camera3D* init_camera(){
    __camera.position = (Vector3){ 4.0f, 4.0f, 4.0f };
    __camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    __camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    __camera.fovy = 45.0f;
    __camera.projection = CAMERA_PERSPECTIVE;
    return &__camera;
}

void move_camera(Vector3 direction){
    __camera.position = Vector3Add(__camera.position, direction);
    __camera.target = Vector3Add(__camera.target, direction);
    UpdateCamera(&__camera, __camera.projection);
}

void move_target(Vector3 target){
    __camera.target = Vector3Add(__camera.target, target);
    UpdateCamera(&__camera, __camera.projection);
}

void move_camera_forward(float speed) {
    Vector3 forward = Vector3Subtract(__camera.target, __camera.position);
    forward = Vector3Normalize(forward);
    move_camera(Vector3Scale(forward, speed));
}

void move_camera_strafe(float speed) {
    Vector3 forward = Vector3Subtract(__camera.target, __camera.position);
    forward = Vector3Normalize(forward);
    Vector3 up = (Vector3){0.0f, 1.0f, 0.0f};
    Vector3 side = Vector3CrossProduct(forward, up);
    side = Vector3Normalize(side);
    move_camera(Vector3Scale(side, speed));
}