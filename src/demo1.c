// REALLY OLD CODE!!!! DO NOT JUDGE
#include "raylib.h"
#include <math.h>
#include <signal.h>

#define NUMBER_OF_RAY 2
#define NUMBER_OF_SEG 6

typedef struct {
	Vector2 firstPoint;
	Vector2 secondPoint;
} segment;

typedef struct {
	Vector2 firstPoint;
	Vector2 secondPoint;
} ray;

bool lineLine(ray r, segment s, Vector2 intersecPoint) {
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
		intersecPoint.x = x1 + (uA * (x2-x1));
		intersecPoint.y = y1 + (uA * (y2-y1));
        // optionally, draw a circle where the lines meet
		DrawCircleV(intersecPoint, 5, RED);
		return true;
	}
	return false;
}

Vector2 closestVec(Vector2 ori, Vector2 v2, Vector2 intersec) {
	int cmp1 = 0;
	int cmp2 = 0;

	cmp1 = fabsf(ori.x - v2.x) + fabsf(ori.y - v2.y);
	cmp2 = fabsf(ori.x - intersec.x) + fabsf(ori.y - intersec.y);

	return (cmp1 >= cmp2) ? intersec : v2;
}

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

	ray r[NUMBER_OF_RAY];

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting 2D Line");

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		bool intersect = false;
	    Vector2 intersecPoint;
		r[0] = (ray) {
            .firstPoint = GetMousePosition(),
		    .secondPoint = (Vector2) {
                .x = r[0].firstPoint.x + 1000,
                .y = r[0].firstPoint.y 
            }
        };
		r[1] = (ray) {
            .firstPoint = GetMousePosition(),
		    .secondPoint = (Vector2) {
                .x = 0,
                .y = 0
            }
        };

		for (int i = 0; i < NUMBER_OF_RAY; i++) {
			for (int j = 0; j < NUMBER_OF_SEG; j++) {
				intersect = lineLine(r[i], seg[j], intersecPoint);
				if (intersect) {
					r[i].secondPoint = closestVec(r[i].firstPoint, r[i].secondPoint, intersecPoint);
                } else {
				    r[i].secondPoint = intersecPoint;
                }
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);

			for (int i = 0; i < NUMBER_OF_SEG; i++)
				DrawLineV(seg[i].firstPoint, seg[i].secondPoint, WHITE);
			for (int i = 0; i < NUMBER_OF_RAY; i++)
				DrawLineV(r[i].firstPoint, r[i].secondPoint, WHITE);

		EndDrawing();
	}
}
