#pragma once
#include "../cons.h"

typedef struct Point {
    Vector3 position;
    Vector3 acceleration;
    Vector3 old_position;
    bool constrained;
} ClothPoint;

typedef struct Link {
    int x1;
    int x2;
    float target;
} ClothLink;

typedef struct Cloth {
    int n_point;
    ClothPoint* points;
    int n_link;
    ClothLink* links;
} Cloth;


Cloth* init_cloth(Vector3 position, Vector3 directionx, Vector3 directiony, int n_node_x, int n_node_y);
void draw_cloth(Cloth* cloth);
void free_cloth(Cloth* cloth);