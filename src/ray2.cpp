#include "raylib.h"
#include <cmath>

#define NUMBER_OF_RAY 2
#define NUMBER_OF_SEG 6

typedef struct segment
{
	Vector2 firstPoint;
	Vector2 secondPoint;
	void Init(float fpx, float fpy, float spx, float spy)
	{
		firstPoint = Vector2{fpx, fpy};
		secondPoint = Vector2{spx, spy};
	}
} segment;

typedef struct ray
{
	Vector2 firstPoint;
	Vector2 secondPoint;

} ray;

static inline bool lineLine(ray &r, segment &s, Vector2 &intersecPoint)
{
	float x1 = r.firstPoint.x
	,y1 = r.firstPoint.y
	,x2 = r.secondPoint.x
	,y2 = r.secondPoint.y
	,x3 = s.firstPoint.x
	,y3 = s.firstPoint.y
	,x4 = s.secondPoint.x
	,y4 = s.secondPoint.y;

	// calculate the direction of the lines
	float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
	float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		// optionally, draw a circle where the lines meet
		intersecPoint.x = x1 + (uA * (x2-x1));
		intersecPoint.y = y1 + (uA * (y2-y1));
		DrawCircleV(intersecPoint, 5, RED);
		return true;
	}
	return false;
}

static inline Vector2 closestVec(Vector2 ori, Vector2 v2, Vector2 intersec)
{
	int cmp1 = 0;
	int cmp2 = 0;

	cmp1 = std::abs(ori.x - v2.x) + std::abs(ori.y - v2.y);
	cmp2 = std::abs(ori.x - intersec.x) + std::abs(ori.y - intersec.y);

	return ((cmp1 >= cmp2) ? intersec : v2);
}

int main()
{
	int w = 1080;
	int h = 720;
	Vector2 intersecPoint;
	bool inter = false;

	segment seg[NUMBER_OF_SEG];
	seg[0].Init(70,70,130,600);
	seg[1].Init(70,70,230,450);
	seg[2].Init(270,400,50,350);
	seg[3].Init(650,70,950,300);
	seg[4].Init(600,600,880,300);
	seg[5].Init(500,100,600,700);

	ray r[NUMBER_OF_RAY];

	InitWindow(w, h, "Raycasting 2D Line");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		inter = false;
		r[0].firstPoint = GetMousePosition();
		r[0].secondPoint.x = r[0].firstPoint.x + std::cos(20 *PI/180) * w;
		r[0].secondPoint.y = r[0].firstPoint.y + std::sin(20 *PI/180) * w;
		r[1].firstPoint = GetMousePosition();
		r[1].secondPoint.x = r[1].firstPoint.x + std::cos(-20 *PI/180) * w;
		r[1].secondPoint.y = r[1].firstPoint.y + std::sin(-20 *PI/180) * w;
		for (unsigned int i = 0; i < NUMBER_OF_RAY; i++)
		{
			for (unsigned int j = 0; j < NUMBER_OF_SEG; j++)
				{
					if ((inter = lineLine(r[i], seg[j], intersecPoint)))
					{
						if (inter)
							r[i].secondPoint = closestVec(r[i].firstPoint, r[i].secondPoint, intersecPoint);
						else
							r[i].secondPoint = intersecPoint;
					}
				}
		}

		BeginDrawing();

			ClearBackground(BLACK);

			for (unsigned int i = 0; i < NUMBER_OF_SEG; i++)
				DrawLine(seg[i].firstPoint.x, seg[i].firstPoint.y, seg[i].secondPoint.x, seg[i].secondPoint.y, RAYWHITE);
			for (unsigned int i = 0; i < NUMBER_OF_RAY; i++)
				DrawLine(r[i].firstPoint.x, r[i].firstPoint.y, r[i].secondPoint.x, r[i].secondPoint.y, Fade(RAYWHITE, 0.8f));


		EndDrawing();
	}
}