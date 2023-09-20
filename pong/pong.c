#include <raylib.h>

int main(void) {
	const int screenWidth = 800;
	const int screenHeight = 500;
	const char title[] = "Pong";

	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(60);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
	}
	
	CloseWindow();
	return 0;
}
