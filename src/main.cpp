#include "raylib.h"
#include <math.h>

const bool arena[10][10] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenSize = 1000;
    const int rayNumber = 360;

    InitWindow(screenSize, screenSize, "2D Raycasting");

    SetTargetFPS(60);  // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Vector2 Position;
    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        Position = GetMousePosition();
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        // Ray casting
        for (float i = 0; i <= 360; i += ((float)360 / rayNumber)) {
            Vector2 altPos = Position;
            while (arena[(int)altPos.x / 100][(int)altPos.y / 100] == false) {
                altPos.x += cos(i * (M_PI / 180));
                altPos.y += sin(i * (M_PI / 180));

                // std::sin(90 * (M_PI/180))
            }
            DrawLineV(Position, altPos, YELLOW);
        }

        // Map drawing
        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (arena[i][j])
                    DrawRectangle(i * 100, j * 100, 100, 100, GRAY);

        // Player
        DrawCircleV(Position, 5, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
