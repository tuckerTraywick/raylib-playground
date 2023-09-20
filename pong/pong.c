#include <raylib.h>

void drawPaddle(int x, int y, int width, int height, Color color) {
	DrawRectangle(x, y, width, height, color);
}

int main(void) {
	const char title[] = "Pong";
	const int paddleWidth = 20;
	const int paddleHeight = 100;
	//const Vector2 paddleSize = {20.0, 100.0};
	const int paddleSpeed = 5.0;
	const int borderWidth = 10.0;
	const int screenWidth = 800;
	const int screenHeight = 500;
	
	int player1X = screenWidth - paddleWidth - borderWidth;
	int player1Y = (screenHeight - paddleHeight) * 0.5;
	int player2X = borderWidth;
	int player2Y = (screenHeight - paddleHeight) * 0.5;
	//Vector2 player1Position = {screenWidth - paddleSize.x - borderWidth, (screenHeight - paddleSize.y) * 0.5};
	//Vector2 player2Position = {borderWidth, (screenHeight - paddleSize.y) * 0.5};

	InitWindow(screenWidth, screenHeight, title);
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		// Update
		if (player1Y > 0 && IsKeyDown(KEY_UP)) {
			player1Y -= paddleSpeed;
			if (player1Y < 0) player1Y = 0;
		} else if (player1Y + paddleHeight < screenHeight && IsKeyDown(KEY_DOWN)) {
			player1Y += paddleSpeed;
			if (player1Y > screenHeight - paddleHeight) player1Y = screenHeight - paddleHeight;
		}

		// Draw
		BeginDrawing();
			ClearBackground(BLACK);
			drawPaddle(player1X, player1Y, paddleWidth, paddleHeight, RED);
			drawPaddle(player2X, player2Y, paddleWidth, paddleHeight, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
