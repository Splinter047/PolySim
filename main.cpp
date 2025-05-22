// Import raylib and raygui
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// Set global constants
constexpr int SCREEN_WDITH = 800;
constexpr int SCREEN_HEIGHT = 450;

// Programs entry point
int main()
{
	// Create window with the specified resolution and title
	InitWindow(SCREEN_WDITH, SCREEN_HEIGHT, "PolySim");

	// Tick rate for our program
	SetTargetFPS(60);

	// Main event loop
	while (!WindowShouldClose())
	{
		// Start drawing to our window
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("PolySim Menu", SCREEN_WDITH/2 - 150, SCREEN_HEIGHT/2 - 50, 50, DARKPURPLE);

		EndDrawing();
	}

	// Close the window
	CloseWindow();
}
