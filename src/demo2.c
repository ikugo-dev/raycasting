#include "raylib.h"
#include <math.h>

void drawRays(Vector2 mouse_pos);
void drawMap();

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
    const int SCREEN_SIZE = 1000;
    InitWindow(SCREEN_SIZE, SCREEN_SIZE, "2D Raycasting");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        Vector2 mouse_position = GetMousePosition();

        BeginDrawing();
        ClearBackground(BLACK);

            drawRays(mouse_position);
            drawMap();
            DrawCircleV(mouse_position, 5, RED);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

void drawRays(Vector2 mouse_position) {
    static const int RAY_NUMBER = 360;
    for (float i = 0; i <= 360; i += ((float)360 / RAY_NUMBER)) {
        Vector2 ray_hit = mouse_position;
        while (arena[(int)ray_hit.x / 100][(int)ray_hit.y / 100] == false) {
            ray_hit.x += cos(i * (M_PI / 180));
            ray_hit.y += sin(i * (M_PI / 180));
        }
        DrawLineV(mouse_position, ray_hit, YELLOW);
    }
}

void drawMap() {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (arena[i][j])
                DrawRectangle(i * 100, j * 100, 100, 100, GRAY);
}
