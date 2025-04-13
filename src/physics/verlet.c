#include "../cons.h"
#include "cloth.h"

void verlet_point(ClothPoint* point, float dt) {
    if (point->constrained) {
        return;
    }
    Vector3 velocity = Vector3Subtract(point->position, point->old_position);
    point->old_position = point->position;
    point->position = Vector3Add(Vector3Add(point->position, velocity), Vector3Scale(point->acceleration, dt * dt));
}

void verlet_point_solver(Cloth* cloth, float dt) {
    for (int i = 0; i < cloth->n_point; i++) {
        cloth->points[i].acceleration = GRAVITY;
        verlet_point(&cloth->points[i], dt);
    }
}
void verlet_link(Cloth* cloth, ClothLink* link) {
    ClothPoint* x1 = &cloth->points[link->x1];
    ClothPoint* x2 = &cloth->points[link->x2];
    
    Vector3 axis = Vector3Subtract(x1->position, x2->position);
    float length = Vector3Length(axis);
    if (length < 0.0001f) return;
    
    Vector3 n = Vector3Scale(axis, 1.0f/length);
    float delta = link->target - length;
    
    if (x1->constrained && x2->constrained) {
        return;
    } 
    else if (x1->constrained) {
        x2->position = Vector3Subtract(x2->position, Vector3Scale(n, delta));
    }
    else if (x2->constrained) {
        x1->position = Vector3Add(x1->position, Vector3Scale(n, delta));
    }
    else {
        x1->position = Vector3Add(x1->position, Vector3Scale(n, delta * 0.5f));
        x2->position = Vector3Subtract(x2->position, Vector3Scale(n, delta * 0.5f));
    }
}

void update_cloth(Cloth* cloth, float dt) {
    verlet_point_solver(cloth, dt);
    for (int iter = 0; iter < VERLET_ITERATIONS; iter++) {
        for (int i = 0; i < cloth->n_link; i++) {
            verlet_link(cloth, &cloth->links[i]);
            
        }
    }
}