#include <raylib.h>

typedef struct {
	int x, y;
} Vector;

typedef struct {
	int x, y;
	int width, height;
} PongRectangle;

const int screenWidth = 800, screenHeight = 500;
const int paddleWidth = 20, paddleHeight = 130;
const int borderWidth = 10;
const int playerSpeed = 5;
const int aiSpeed = 5;
const int aiRange = screenWidth/6;
const int ballWidth = 20;
PongRectangle paddles[2];
PongRectangle ball;
Vector ballVelocity;
int scores[2];

void resetBall() {
	ball = (PongRectangle) {(screenWidth - ballWidth)/2, (screenHeight - ballWidth)/2, ballWidth, ballWidth};
	ballVelocity = (Vector) {4, GetRandomValue(-8, 8)};
}

void resetPaddles() {
	paddles[0] = (PongRectangle) {0, (screenHeight - paddleHeight)/2, paddleWidth, paddleHeight};
	paddles[1] = (PongRectangle) {screenWidth - paddleWidth, (screenHeight - paddleHeight)/2, paddleWidth, paddleHeight};
}

bool rectanglesOverlap(PongRectangle a, PongRectangle b) {
	return !(
		a.x > b.x + b.width
		|| b.x > a.x + a.width
		|| a.y > b.y + b.height
		|| b.y > a.y + a.height
	);
}

void drawCenteredText(const char *text, int x, int y, int fontSize, Color color) {
	int textWidth = MeasureText(text, fontSize);
	DrawText(text, x - textWidth/2, y - fontSize/2, fontSize, color);
}

int main(void) {
	resetBall();
	resetPaddles();

	InitWindow(screenWidth, screenHeight, "Pong");
	SetTargetFPS(60);

	bool ballWasHit = false;
	while (!WindowShouldClose()) {
		// Handle input.
		int paddleVelocity = 0;
		if (paddles[1].y > 0 && IsKeyDown(KEY_UP)) {
			paddles[1].y -= playerSpeed;
			paddleVelocity = -playerSpeed/1.5;
		} else if (paddles[1].y + paddles[1].height < screenHeight && IsKeyDown(KEY_DOWN)) {
			paddles[1].y += playerSpeed;
			paddleVelocity = playerSpeed/1.5;
		}

		// Detect collision.
		if (ball.x + ball.width <= 0) {
			++scores[0];
			resetBall();
		} else if (ball.x >= screenWidth) {
			++scores[1];
			resetBall();
		} else if (!ballWasHit && (rectanglesOverlap(ball, paddles[0]) || rectanglesOverlap(ball, paddles[1]))) {
			ballVelocity.x = -ballVelocity.x;
			ballVelocity.y += paddleVelocity;
			ballWasHit = true;
		}


		// Update ball.		
		if (ball.y <= 0 || ball.y + ball.width >= screenHeight) {
			ballVelocity.y = -ballVelocity.y;
		}

		ball.x += ballVelocity.x;
		ball.y += ballVelocity.y;

		if (ballWasHit && ball.x > paddleWidth && ball.x + ball.width < screenWidth - paddleWidth) {
			ballWasHit = false;
		}

		// Handle ai.
		if (ball.x < aiRange && ball.y < paddles[0].y)
			paddles[0].y -= playerSpeed;
		else if (ball.x < aiRange && ball.y + ballWidth/2 > paddles[0].y + paddleHeight)
			paddles[0].y += playerSpeed;

		// Draw.
		BeginDrawing();
			ClearBackground(BLACK);
			drawCenteredText(TextFormat("%i", scores[0]), screenWidth*0.75, 50, 80, GRAY);
			drawCenteredText(TextFormat("%i", scores[1]), screenWidth*0.25, 50, 80, GRAY);
			DrawRectangle((screenWidth - borderWidth)/2, 0, borderWidth, screenHeight, GRAY);
			for (int i = 0; i < 2; ++i)
				DrawRectangle(paddles[i].x, paddles[i].y, paddles[i].width, paddles[i].height, WHITE);
			DrawRectangle(ball.x, ball.y, ball.width, ball.height, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
