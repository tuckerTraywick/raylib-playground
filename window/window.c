#include <raylib.h>

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 500;
	const char title[] = "Window Demo";

	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}
