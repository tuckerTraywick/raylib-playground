#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 500;
const int borderWidth = 0;
const int paddleWidth = 20;
const int paddleHeight = 200;
const int paddleSpeed = 5;
const int ballLength = 20;
int player1X;
int player1Y;
int player2X;
int player2Y;
int player1Score;
int player2Score;
int ballX;
int ballY;
int ballVelocityX;
int ballVelocityY;

bool rectanglesOverlap(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2) {
	// TODO
	return false;
}

void drawCenteredText(const char *text, int posX, int posY, int fontSize, Color color) {
	int textWidth = MeasureText(text, fontSize);
	DrawText(text, posX - textWidth/2, posY - fontSize/2, fontSize, color);
}

void resetPlayers() {
	player1X = screenWidth - paddleWidth - borderWidth;
	player1Y = (screenHeight - paddleHeight)/2;
	player2X = borderWidth;
	player2Y = (screenHeight - paddleHeight)/2;
}

void resetBall() {
	ballX = (screenWidth - ballLength)/2;
	ballY = (screenHeight - ballLength)/2;
	ballVelocityX = 4;
	ballVelocityY = 0;
}

int main(void) {
	resetPlayers();
	resetBall();
	
	InitWindow(screenWidth, screenHeight, "Pong");
	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		// Draw
		BeginDrawing();
			ClearBackground(BLACK);
			drawCenteredText(TextFormat("%i", player1Score), screenWidth*0.75, 50, 80, WHITE);
			drawCenteredText(TextFormat("%i", player2Score), screenWidth*0.25, 50, 80, WHITE);
			DrawRectangle(player1X, player1Y, paddleWidth, paddleHeight, RED);
			DrawRectangle(player2X, player2Y, paddleWidth, paddleHeight, WHITE);
			DrawRectangle(ballX, ballY, ballLength, ballLength, WHITE);
		EndDrawing();

		// Update
		int paddleDirection = 0;
		if (player1Y > 0 && IsKeyDown(KEY_UP)) {
			paddleDirection = -1;
			player1Y -= paddleSpeed;
			if (player1Y < 0)
				player1Y = 0;
		} else if (player1Y + paddleHeight < screenHeight && IsKeyDown(KEY_DOWN)) {
			paddleDirection = 1;
			player1Y += paddleSpeed;
			if (player1Y > screenHeight - paddleHeight)
				player1Y = screenHeight - paddleHeight;
		}

		ballX += ballVelocityX;
		ballY += ballVelocityY;

		if (ballX + ballLength >= screenWidth - paddleWidth && ballY >= player1Y && ballY + ballLength <= player1Y + paddleHeight) {
			// Player 1 deflects the ball.
			ballVelocityX = -ballVelocityX;
			ballVelocityY += paddleDirection*paddleSpeed*0.5;
		} else if (ballX <= paddleWidth && ballY >= player2Y && ballY + ballLength <= player2Y + paddleHeight) {
			// Player 2 deflects the ball.
			ballVelocityX = -ballVelocityX;
		} else if (ballX <= 0) {
			// Player 1 scores.
			player1Score += 1;
			resetBall();
		} else if (ballX + ballLength >= screenWidth) {
			// Player 2 scores.
			player2Score += 1;
			resetBall();
		} else if (ballY <= 0) {
			// Ball hits top of screen.
			ballY = 0;
			ballVelocityY = -ballVelocityY;
		} else if (ballY + ballLength >= screenHeight) {
			ballY = screenHeight - ballLength;
			ballVelocityY = -ballVelocityY;
		}
	}

	CloseWindow();
	return 0;
}
