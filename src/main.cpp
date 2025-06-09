// Import raylib and raygui
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

// Set global constants
constexpr int SCREEN_WDITH = 800;
constexpr int SCREEN_HEIGHT = 600;

// Programs entry point
int main()
{
	setenv("WAYLAND_APP_ID", "raylib", 1);
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);

	// Create window with the specified resolution and title
	InitWindow(SCREEN_WDITH, SCREEN_HEIGHT, "PolySim");

	// Tick rate for our program
	SetTargetFPS(60);

	bool showMessageBox = false;

	// Main event loop
	while (!WindowShouldClose())
	{
		// Start drawing to our window
		BeginDrawing();

		ClearBackground(RAYWHITE);
		DrawText("PolySim Menu", SCREEN_WDITH/2 - 150, SCREEN_HEIGHT/2 - 50, 50, DARKPURPLE);

		if (GuiButton((Rectangle){ 24, 24, 120, 30 }, "#191#Show Message")) showMessageBox = true;

		if (showMessageBox)
		{
			int result = GuiMessageBox((Rectangle){ 85, 70, 250, 100 },
				"#191#Message Box", "Hi! This is a message!", "Nice;Cool");

			if (result >= 0) showMessageBox = false;
		}

		EndDrawing();
	}

	// Close the window
	CloseWindow();
}
