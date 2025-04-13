#include "cloth.c"
#include "kin.c"
#include "verlet.c"
typedef struct Plant {
    Cloth** cloths;
    int n_cloth;
    Arm* arm;
} Plant;

Plant* init_plant(Vector3 position){
    Plant* plant = malloc(sizeof(Plant));
    Arm* arm = init_arm(position);
    plant->arm = arm;
    plant->cloths = malloc(sizeof(Cloth*) * LINK_NUMBER);
    for (int i = 0; i < LINK_NUMBER; i++){
        Vector3 start = arm->links[i].start;
        Vector3 end = arm->links[i].end;
        Vector3 axis = Vector3Subtract(end, start);
        Vector3 dirx = Vector3Scale(axis, 1.0 / 5.0);
        Vector3 diry = Vector3Scale((Vector3){0, -1, 0}, 1.0 / 5.0);
        Cloth* cloth = init_cloth(start, dirx, diry, 5, 5);
        plant->cloths[i] = cloth;
    }
    plant->n_cloth = LINK_NUMBER;
    return plant;
}

void update_plant(Plant* plant, Vector3 target, float dt){
    fabrik(plant->arm, target);
    for (int i = 0; i < plant->n_cloth; i++){
        Vector3 start = plant->arm->links[i].start;
        Vector3 end = plant->arm->links[i].end;
        Vector3 axis = Vector3Subtract(end, start);
        move_cloth(plant->cloths[i], start, Vector3Scale(axis, 1.0 / 5.0));
        update_cloth(plant->cloths[i], dt);
    }
}

void draw_plant(Plant* plant){
    render(plant->arm);
    for (int i = 0; i < plant->n_cloth; i++){
        draw_cloth(plant->cloths[i]);
    }
}

void free_plant(Plant* plant){
    free_arm(plant->arm);
    for (int i = 0; i < plant->n_cloth; i++){
        free_cloth(plant->cloths[i]);
    }
    free(plant);
}