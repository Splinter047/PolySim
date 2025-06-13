#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../include/scene.h"
#include "../include/state_manager.h"

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 800;

int main()
{
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PolySim");
	SetTargetFPS(60);

	Scene canvas;
	StateManager state_manager(canvas);

	while (!WindowShouldClose())
	{
		if (IsWindowResized())
		{
			SCREEN_WIDTH = GetScreenWidth();
			SCREEN_HEIGHT = GetScreenHeight();
		}

		state_manager.handleInput();

		// Drawing
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);

			state_manager.draw();
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
