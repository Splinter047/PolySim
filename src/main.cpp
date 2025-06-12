#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "../include/pen_tool.h"
#include "../include/polygon.h"
#include "raygui.h"

enum class Editor_State
{
	Idle,
	Drawing
};

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 800;

int main()
{
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PolySim");
	SetTargetFPS(60);

	Pen_Tool poly_pen;
	Vector<Polygon *> polygons; // TODO: move to a new scene class
	Editor_State cur_state = Editor_State::Idle;

	while (!WindowShouldClose())
	{
		if (IsWindowResized())
		{
			SCREEN_WIDTH = GetScreenWidth();
			SCREEN_HEIGHT = GetScreenHeight();
		}

		// State management TODO: Extract to new state management class
		switch (cur_state)
		{
			case Editor_State::Idle:
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				{
					poly_pen.startNewPolygon(GetMousePosition());
					cur_state = Editor_State::Drawing;
				}
				break;

			case Editor_State::Drawing:
				if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))

					poly_pen.tryAddVertex(GetMousePosition());

				if (IsKeyPressed(KEY_ENTER) ||
					IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
				{
					Polygon *newPolygon = poly_pen.completePolygon();
					if (newPolygon != nullptr) { polygons.push(newPolygon); }
					cur_state = Editor_State::Idle;
				}

				if (IsKeyReleased(KEY_ESCAPE))
				{
					poly_pen.cancel();
					cur_state = Editor_State::Idle;
				}
				break;
		}

		// Drawing
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);

			// Draw polygons in our scene
			for (int i = 0; i < polygons.size(); i++) { polygons[i]->draw(); }

			// Draw preview when pen tool is active
			if (cur_state == Editor_State::Drawing) { poly_pen.drawPreview(); }
		}
		EndDrawing();
	}

	// Cleanup
	for (int i = 0; i < polygons.size(); i++) { delete polygons[i]; }

	CloseWindow();
	return 0;
}
