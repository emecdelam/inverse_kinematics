#include "kin.h"

Arm* init_arm(Vector3 start){
    Arm* arm = (Arm*) malloc(sizeof(Arm));
    arm->links = malloc(sizeof(Link) * LINK_NUMBER);
    arm->n_links = 0;
    for (int i = 0 ; i < LINK_NUMBER; i++){
        Link l = (Link){(Vector3){0.0, i, 0.0}, (Vector3){0.0, i+1, 0.0}, LINK_SIZE};
        arm->links[i] = l;
        arm->n_links++;   
    }
    arm->anchor = start;
    return arm;
}
void free_arm(Arm* arm){
    free(arm->links);
    free(arm);
}
void fabrik(Arm* arm, Vector3 target){
    for (int i = 0; i < ITERATIONS; i++){
        backward_kinematics(arm, target);
        forward_kinematics(arm);
    }
}
void backward_kinematics(Arm* arm, Vector3 target) {
    arm->links[arm->n_links - 1].end = target;
    for (int i = arm->n_links - 1; i > 0; i--) {
        Link* curr = &arm->links[i];
        Vector3 dir = Vector3Subtract(curr->start, curr->end);
        Vector3 norm = Vector3Normalize(dir);
        curr->start = Vector3Add(curr->end, Vector3Scale(norm, curr->length));
        arm->links[i - 1].end = curr->start;
    }
}

void forward_kinematics(Arm* arm) {
    arm->links[0].start = arm->anchor;
    for (int i = 0; i < arm->n_links; i++) {
        Link* curr = &arm->links[i];
        Vector3 dir = Vector3Subtract(curr->end, curr->start);
        Vector3 norm = Vector3Normalize(dir);
        curr->end = Vector3Add(curr->start, Vector3Scale(norm, curr->length));
        if (i < arm->n_links - 1) {
            arm->links[i + 1].start = curr->end;
        }
    }
}


void render(Arm* arm){
    for (int i = 0; i < arm->n_links; i++){
        Vector3 start = arm->links[i].start;
        Vector3 end = arm->links[i].end;
        DrawSphere(start,JOINT_RADIUS, WHITE);
        DrawCylinderEx(start, end, LINK_RADIUS, LINK_RADIUS, LINK_SEGMENT, WHITE);
    }
}