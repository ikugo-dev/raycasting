// REALLY OLD CODE!!!! DO NOT JUDGE
#include "raylib.h"
#include <math.h>

#define NEUTRAL (Vector2){0,0}
#define NUMBER_OF_SEG 6

typedef struct {
	Vector2 firstPoint;
	Vector2 secondPoint;
} segment;

typedef struct {
	Vector2 firstPoint;
	Vector2 secondPoint;
} ray;

void checkIntersection(ray r, segment s);

int main(void) {
	const int SCREEN_WIDTH = 1080;
	const int SCREEN_HEIGHT = 720;

	segment seg[NUMBER_OF_SEG];
	seg[0] = (segment){{70,70},  {130,600}};
	seg[1] = (segment){{70,70},  {230,450}};
	seg[2] = (segment){{270,400},{50,350} };
	seg[3] = (segment){{650,70}, {950,300}};
	seg[4] = (segment){{600,600},{880,300}};
	seg[5] = (segment){{500,100},{600,700}};


	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting 2D Line");

	SetTargetFPS(60);

    while (!WindowShouldClose()) {
	    ray r = (ray) {
            .firstPoint = GetMousePosition(),
			.secondPoint = NEUTRAL
        };

		for (int i = 0; i < NUMBER_OF_SEG; i++) {
			checkIntersection(r, seg[i]);
		}

		BeginDrawing();
		ClearBackground(BLACK);

			for (int i = 0; i < NUMBER_OF_SEG; i++)
				DrawLineV(seg[i].firstPoint, seg[i].secondPoint, WHITE);
			DrawLineV(r.firstPoint, NEUTRAL, WHITE);

		EndDrawing();
	}
}

void checkIntersection(ray r, segment s) {
	float x1 = r.firstPoint.x;
	float y1 = r.firstPoint.y;
	float x2 = r.secondPoint.x;
	float y2 = r.secondPoint.y;
	float x3 = s.firstPoint.x;
	float y3 = s.firstPoint.y;
	float x4 = s.secondPoint.x;
	float y4 = s.secondPoint.y;

	// calculate the direction of the lines
	float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
	float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
        Vector2 intersectPoint = {
		    .x = x1 + (uA * (x2-x1)),
		    .y = y1 + (uA * (y2-y1))
        };
		DrawCircleV(intersectPoint, 5, RED);
	}
}

Vector2 closestVec(Vector2 ori, Vector2 v2, Vector2 intersec) {
	float cmp1 = fabsf(ori.x - v2.x) + fabsf(ori.y - v2.y);
	float cmp2 = fabsf(ori.x - intersec.x) + fabsf(ori.y - intersec.y);

	return (cmp1 >= cmp2) ? intersec : v2;
}
