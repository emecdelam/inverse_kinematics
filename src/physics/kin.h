#pragma once

#include "../cons.h"

typedef struct ArmLink {
    Vector3 start;
    Vector3 end;
    float length;
} ArmLink;

typedef struct Arm {
    ArmLink* links;
    int n_links;
    Vector3 anchor;
} Arm;

Arm* init_arm();
void free_arm(Arm* arm);
void fabrik(Arm* arm, Vector3 target);
void backward_kinematics(Arm* arm, Vector3 target);
void forward_kinematics(Arm* arm);
void render(Arm* arm);