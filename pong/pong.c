#include <raylib.h>

const int screenWidth = 800, screenHeight = 500;
const int paddleWidth = 20, paddleHeight = 130;
const int ballWidth = 20;
const int borderWidth = 10;
const int playerSpeed = 5;
const int aiSpeed = 5;
const int aiRange = screenWidth/5;
const Vector2 ballStartingSpeed = {7, 8};
const int maxBallVelocity = 12;
const int maxScore = 5;

Rectangle paddles[2];
Rectangle ball;
Vector2 ballVelocity;
int scores[2];
int state = 0;

bool rectanglesOverlap(Rectangle a, Rectangle b) {
	return !(
		a.x > b.x + b.width
		|| b.x > a.x + a.width
		|| a.y > b.y + b.height
		|| b.y > a.y + a.height
	);
}

void resetBall() {
	ball = (Rectangle) {(screenWidth - ballWidth)/2, (screenHeight - ballWidth)/2, ballWidth, ballWidth};
	ballVelocity = (Vector2) {ballStartingSpeed.x, GetRandomValue(-ballStartingSpeed.y, ballStartingSpeed.y)};
}

void resetGame() {
	resetBall();
	scores[0] = 0;
	scores[1] = 0;
	paddles[0] = (Rectangle) {0, (screenHeight - paddleHeight)/2, paddleWidth, paddleHeight};
	paddles[1] = (Rectangle) {screenWidth - paddleWidth, (screenHeight - paddleHeight)/2, paddleWidth, paddleHeight};
}

void deflectBall(int paddleVelocity) {
	ballVelocity.x = -ballVelocity.x;
	ballVelocity.y += paddleVelocity;
	if (ballVelocity.y > maxBallVelocity) ballVelocity.y = maxBallVelocity;
	if (ballVelocity.y < -maxBallVelocity) ballVelocity.y = -maxBallVelocity;
}

void drawCenteredText(const char *text, int x, int y, int fontSize, Color color) {
	int textWidth = MeasureText(text, fontSize);
	DrawText(text, x - textWidth/2, y - fontSize/2, fontSize, color);
}

void showWelcomeScreen() {
	BeginDrawing();
		ClearBackground(BLACK);
		drawCenteredText("PONG", screenWidth/2, screenHeight/2 - 60, 70, WHITE);
		drawCenteredText(TextFormat("First player to %i points wins.", maxScore), screenWidth/2, screenHeight/2 + 30, 30, WHITE);
		drawCenteredText("Click or press any key to start.", screenWidth/2, screenHeight/2 + 60, 30, WHITE);
	EndDrawing();

	state = GetKeyPressed() || IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void update() {
	bool mouseControls = true;

	// Handle input.
	int paddleVelocity = 0;
	if (mouseControls) {
		paddleVelocity = GetMouseDelta().y/2.5;
		paddles[1].y = GetMouseY() - paddleHeight/2;
		if (paddles[1].y < 0) paddles[1].y = 0;
		if (paddles[1].y > screenHeight - paddleHeight) paddles[1].y = screenHeight - paddleHeight;
	} else if (paddles[1].y > 0 && IsKeyDown(KEY_UP)) {
		paddles[1].y -= playerSpeed;
		paddleVelocity = -playerSpeed/1.5;
	} else if (paddles[1].y + paddles[1].height < screenHeight && IsKeyDown(KEY_DOWN)) {
		paddles[1].y += playerSpeed;
		paddleVelocity = playerSpeed/1.5;
	}

	// Detect collision.
	if (ball.x + ball.width <= 0) {
		++scores[1];
		resetBall();
	} else if (ball.x >= screenWidth) {
		++scores[0];
		resetBall();
	} else if (rectanglesOverlap(ball, paddles[0])) {
		deflectBall(paddleVelocity);
		ball.x = paddleWidth + 1;
	} else if (rectanglesOverlap(ball, paddles[1])) {
		deflectBall(paddleVelocity);
		ball.x = screenWidth - paddleWidth - ballWidth - 1;
	}

	// Handle win conditions.
	if (scores[0] >= maxScore) {
		state = 2;  // AI won.
	} else if (scores[1] >= maxScore) {
		state = 3; // Player won.
	}

	// Update ball.		
	if (ball.y <= 0 || ball.y + ball.width >= screenHeight) {
		ballVelocity.y = -ballVelocity.y;
	}

	ball.x += ballVelocity.x;
	ball.y += ballVelocity.y;

	// Handle ai.
	if (ball.x < aiRange && ball.y < paddles[0].y)
		paddles[0].y -= playerSpeed;
	else if (ball.x < aiRange && ball.y + ballWidth/2 > paddles[0].y + paddleHeight)
		paddles[0].y += playerSpeed;

	// Draw.
	BeginDrawing();
		ClearBackground(BLACK);
		drawCenteredText(TextFormat("%i", scores[0]), screenWidth*0.25, 50, 80, GRAY);
		drawCenteredText(TextFormat("%i", scores[1]), screenWidth*0.75, 50, 80, GRAY);
		DrawRectangle((screenWidth - borderWidth)/2, 0, borderWidth, screenHeight, GRAY);
		for (int i = 0; i < 2; ++i)
			DrawRectangle(paddles[i].x, paddles[i].y, paddles[i].width, paddles[i].height, WHITE);
		DrawRectangle(ball.x, ball.y, ball.width, ball.height, WHITE);
	EndDrawing();
}

void showWinScreen() {
	BeginDrawing();
		ClearBackground(BLACK);
		if (state == 2) {
			drawCenteredText("YOU LOSE!", screenWidth/2, screenHeight/2 - 70, 70, WHITE);
		} else if (state == 3) {
			drawCenteredText("YOU WIN!", screenWidth/2, screenHeight/2 - 70, 70, WHITE);
		}
		drawCenteredText("Click or press any key to play again.", screenWidth/2, screenHeight/2, 30, WHITE);
	EndDrawing();

	if (GetKeyPressed() || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		resetGame();
		state = 1;
	}
}

int main(void) {
	resetGame();

	InitWindow(screenWidth, screenHeight, "Pong");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		switch (state) {
			case 0:
				showWelcomeScreen();
				break;
			case 1:
				update();
				break;
			case 2:
			case 3:
				showWinScreen();
				break;
		}
	}

	CloseWindow();
	return 0;
}
