// Import raylib and raygui
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "../include/vector.h"

// Set global constants
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 600;

// Programs entry point
int main()
{
	// setenv("WAYLAND_APP_ID", "raylib", 1);
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);

	// Create window with the specified resolution and title
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PolySim");

	// Tick rate for our program
	SetTargetFPS(60);

	Vector<int> position(2, 100);
	Vector<int> position2(2, 0);
	float rotation = 0.0f;

	// Main event loop
	while (!WindowShouldClose())
	{
		if(IsWindowResized())
		{
			SCREEN_WIDTH = GetScreenWidth();
			SCREEN_HEIGHT = GetScreenHeight();
		}

		position2[0] = GetMousePosition().x;
		position2[1] = GetMousePosition().y;

		rotation += 0.2f;
		// Start drawing to our window
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawLine(position[0],position[1],position2[0],position2[1],RED);

		EndDrawing();
	}

	// Close the window
	CloseWindow();
}
