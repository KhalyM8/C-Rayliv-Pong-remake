#include "raylib.h"
#include <cmath>

struct Ball {
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw() {

		DrawCircle((int)x, (int)y, radius, WHITE);
	}

};

struct Paddle {
	float x, y;
	float speed;
	float width, height;

	Rectangle GetRect() {
		return Rectangle{ x - width / 2,y - height / 2, 10, 100 };
	}

	void Draw() {
		DrawRectangleRec(GetRect(), WHITE);
	}
};


int main() {
	InitWindow(800, 600, "Pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = GetScreenWidth() / 2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speed = 500;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50;
	rightPaddle.y = GetScreenHeight() / 2;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speed = 500;

	const char* winnerText = nullptr;

	float rightPoints = 0.0f;
	float leftPoints = 0.0f;

	while (!WindowShouldClose()) {

		float delta = GetFrameTime();

		ball.x += ball.speedX * delta;
		ball.y += ball.speedY * delta;

		if (leftPaddle.y <= -50) {
			leftPaddle.y = GetScreenHeight();
		}
		if (leftPaddle.y >= GetScreenWidth()) {
			leftPaddle.y = -25;
		}
		if (rightPaddle.y <= -50) {
			rightPaddle.y = GetScreenHeight();
		}
		if (rightPaddle.y >= GetScreenWidth()) {
			rightPaddle.y = -25;
		}

		if (ball.y > GetScreenHeight()) {
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		}

		if (ball.y < 0) {
			ball.y = 0;
			ball.speedY *= -1;
		}

		if (IsKeyDown(KEY_W)) {
			if (!winnerText) {
				leftPaddle.y -= leftPaddle.speed * delta;
			}
		}
		if (IsKeyDown(KEY_S)) {
			if (!winnerText) {
				leftPaddle.y += leftPaddle.speed * delta;
			}

		}
		if (IsKeyDown(KEY_UP)) {
			if (!winnerText) {
				rightPaddle.y -= rightPaddle.speed * delta;
			}

		}
		if (IsKeyDown(KEY_DOWN)) {
			if (!winnerText) {
				rightPaddle.y += rightPaddle.speed * delta;
			}

		}

		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, leftPaddle.GetRect())) {
			if (ball.speedX < 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height/2)* ball.speedX;
			}

		}
		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, rightPaddle.GetRect())) {
			if (ball.speedX > 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
			}
		}


		if (ball.x < 0) {
			winnerText = "Right Player Wins";
		}
		if (ball.x > GetScreenWidth()) {
			winnerText = "Left Player Wins";
		}
		if (winnerText && IsKeyPressed(KEY_SPACE)) {
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			leftPaddle.y = GetScreenHeight() / 2;
			rightPaddle.y = GetScreenHeight() / 2;
			winnerText = nullptr;
		}


		BeginDrawing();
		ClearBackground(BLACK);

		ball.Draw();
		leftPaddle.Draw();
		rightPaddle.Draw();

		if (winnerText) {
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth()/2 - textWidth/2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		}

		DrawText(TextFormat("%i - %i", leftPoints, rightPoints), GetScreenWidth() / 2 + -10 - 20, 50, 30, GREEN);

		DrawFPS(0,0);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}