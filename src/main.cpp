#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "../include/scene.h"
#include "../include/state_manager.h"
#include "../include/file_manager.h"

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 800;

int main()
{
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PolySim");
	SetTargetFPS(60);

	float delta_time = 0.0f;
	Scene canvas;
	canvas.togglePhysics();
	StateManager state_manager(canvas);

	while (!WindowShouldClose())
	{
		if (IsWindowResized())
		{
			SCREEN_WIDTH = GetScreenWidth();
			SCREEN_HEIGHT = GetScreenHeight();
		}

		delta_time = GetFrameTime();
		canvas.update(delta_time);
		state_manager.handleInput();

		// Drawing
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);

			state_manager.draw();

			if (GuiButton(Rectangle(10, 10, 50, 30), "clear"))
				canvas.clear();
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
