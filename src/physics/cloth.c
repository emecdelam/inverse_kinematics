#include "cloth.h"
#include <math.h>



int find_point(Cloth* cloth, Vector3 pos, float epsilon) {
    for (int i = 0; i < cloth->n_point; i++) {
        Vector3 p = cloth->points[i].position;
        if (fabsf(p.x - pos.x) < epsilon && 
            fabsf(p.y - pos.y) < epsilon && 
            fabsf(p.z - pos.z) < epsilon) {
            return i;
        }
    }
    return -1;
}

int add_point(Cloth* cloth, Vector3 pos, bool constrained) {
    int idx = find_point(cloth, pos, 0.001f);
    if (idx >= 0) {
        return idx;
    }
    
    cloth->points = (ClothPoint*)realloc(cloth->points, sizeof(ClothPoint) * (cloth->n_point + 1));
    
    ClothPoint p = {
        .position = pos,
        .old_position = pos,
        .acceleration = (Vector3){0.0f, 0.0f, 0.0f},
        .constrained = constrained
    };
    
    
    cloth->points[cloth->n_point] = p;
    return cloth->n_point++;
}


void add_link(Cloth* cloth, Vector3 x1, Vector3 x2, float target, bool constrained) {
    int idx1 = add_point(cloth, x1, constrained);
    int idx2 = add_point(cloth, x2, constrained);
    
    if (idx1 == idx2) {
        return;
    }
    
    for (int i = 0; i < cloth->n_link; i++) {
        if ((cloth->links[i].x1 == idx1 && cloth->links[i].x2 == idx2) ||
            (cloth->links[i].x1 == idx2 && cloth->links[i].x2 == idx1)) {
            return;
        }
    }
    
    cloth->links = (ClothLink*)realloc(cloth->links, sizeof(ClothLink) * (cloth->n_link + 1));
    
    ClothLink l = {.x1 = idx1, .x2 = idx2, .target = target};
    cloth->links[cloth->n_link] = l;
    cloth->n_link++;
}

Cloth* init_cloth(Vector3 position, Vector3 directionx, Vector3 directiony, int n_node_x, int n_node_y){
    Cloth* cloth = (Cloth*)malloc(sizeof(Cloth));
    cloth->n_point = 0;
    cloth->n_link = 0;
    cloth->points = NULL;
    cloth->links = NULL;
    for (int y = 0; y < n_node_y; y++){
        for (int x = 0; x < n_node_x; x++){
            Vector3 x1 = Vector3Add(Vector3Add(position, Vector3Scale(directiony, y)), Vector3Scale(directionx, x));
            if (x != n_node_x -1){
                Vector3 x2 = Vector3Add(Vector3Add(position, Vector3Scale(directiony, y)), Vector3Scale(directionx, x + 1));
                if (y == 0){
                    add_link(cloth, x1, x2, Vector3Length(directionx), true);
                } else {
                    add_link(cloth, x1, x2, Vector3Length(directionx), false);
                }
            }

            if (y == n_node_y -1){continue;}
            Vector3 y2 = Vector3Add(x1, directiony);
            add_link(cloth, x1, y2, Vector3Length(directionx), false);
        }
    }

    return cloth;
}
void move_cloth(Cloth* cloth, Vector3 position, Vector3 directionx){
    int count = 0;
    for (int i = 0; i < cloth->n_point; i++){
        if (cloth->points[i].constrained){
            cloth->points[i].position = Vector3Add(position, Vector3Scale(directionx, count));
            count++;
        }
    }
}
void draw_cloth(Cloth* cloth) {
    for (int i = 0; i < cloth->n_link; i++){
        ClothLink link = cloth->links[i];
        DrawLine3D(cloth->points[link.x1].position, cloth->points[link.x2].position, RAYWHITE);
    }
}

void free_cloth(Cloth* cloth) {
    if (!cloth) return;
    
    if (cloth->points) {
        free(cloth->points);
        cloth->points = NULL;
    }
    
    if (cloth->links) {
        free(cloth->links);
        cloth->links = NULL;
    }
    
    free(cloth);
}
