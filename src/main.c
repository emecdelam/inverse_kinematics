#include "cons.h"
#include "controls/keys.c"
#include "controls/display.c"
#include "physics/step.c"
#include "physics/kin.c"

int main() {
    log_info("Starting program");
    
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Cloth Sim");
    log_info("Window created");
    
    SetTargetFPS(60);
    log_info("Raylib Version: %s", RAYLIB_VERSION);
    

    // -- Inits
    Camera3D* camera = init_camera();
    Arm* arm = init_arm();


    float time = 0.0;
    int step;
    // -- Main game loop
    log_info("Entering main loop");
    while (!WindowShouldClose()) {
        
        // -- Key press
        handle_key();

        // -- Physics
        float dt = GetFrameTime();
        if (dt > 0.016f) dt = 0.016f;
        time += dt;

        // Calculate a 2D circle in x-y plane, z=0
        Vector3 target;
        target.x = 2.0 * cosf(1.0 * time) * sinf(0.5 * time);
        target.y = 2.0 * fabs(cosf(0.5 * time));
        target.z = 2.0 * sinf(1.0 * time);;

        // -- Step
        step = check_step(time);
        fabrik(arm, target);

        // -- Drawing
        BeginDrawing();
            ClearBackground((Color){ 50, 50, 50, 255 });


            // -- Draw
            BeginMode3D(*camera);
                DrawPlane((Vector3){0, 0, 0}, (Vector2){2*BORDER, 2*BORDER}, GRAY);
                render(arm);
                DrawSphere(target, 0.1, RED);
            EndMode3D();

            // -- Display
            handle_display(camera, step);
        EndDrawing();
    }

    // -- Cleanup
    log_info("Cleaning up...");
    free_arm(arm);
    CloseWindow();    
    return 0;
}    
