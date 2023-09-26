#include <raylib.h>

int main(void) {
	const int screenWidth = 1000;
	const int screenHeight = 800;
	const char title[] = "Circle Demo";
	const float circleRadius = 100;

	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawCircle(screenWidth/2, screenHeight/2, circleRadius, RED);
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}
