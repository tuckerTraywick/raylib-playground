#include <raylib.h>

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 500;
	const char title[] = "Circle Demo";
	const float circleRadius = 100;

	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("This is a circle:", 50, screenHeight/2 - circleRadius*2, 80, RED);
		DrawCircle(screenWidth/2, screenHeight/2, circleRadius, RED);
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}
