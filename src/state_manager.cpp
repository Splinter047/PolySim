#include "../include/state_manager.h"

StateManager::StateManager(Scene &scene)
	: scene(scene), current_state(Editor_State::Idle), selected_poly(nullptr),
	  is_dragging(false), drag_offset{0, 0}
{
}

/**
 * @brief Calls appropriate input handler
 */
void StateManager::handleInput()
{
	switch (current_state)
	{
		case Editor_State::Idle: handleIdle(); break;
		case Editor_State::Drawing: handleDrawing(); break;
		case Editor_State::Controller: handleController(); break;
	}
}

/**
 * @brief Handles input accordingly to the idle state
 */
void StateManager::handleIdle()
{
	if (IsKeyReleased(KEY_TAB))
	{
		current_state = Editor_State::Controller;
		selected_poly = nullptr;
		is_dragging = false;
		return;
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		pen_tool.startNewPolygon(GetMousePosition());
		current_state = Editor_State::Drawing;
	}
}

/**
 * @brief Polls for user input and calls the relevant pen tool methods
 */
void StateManager::handleDrawing()
{
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		pen_tool.tryAddVertex(GetMousePosition());

	if (IsKeyReleased(KEY_BACKSPACE))
		if (pen_tool.removeLastVertex()) current_state = Editor_State::Idle;

	if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		Polygon *new_polygon = pen_tool.completePolygon();
		if (new_polygon != nullptr) { scene.addObject(new_polygon); }

		current_state = Editor_State::Idle;
	}

	if (IsKeyReleased(KEY_DELETE))
	{
		pen_tool.cancel();
		current_state = Editor_State::Idle;
	}
}

/**
 * @brief Calls draw for existing polygons and current preview if using pen tool
 */
void StateManager::draw() const
{
	scene.draw();

	if (current_state == Editor_State::Drawing) { pen_tool.drawPreview(); }

	if (current_state == Editor_State::Controller && selected_poly)
	{
		Vector2 handle = selected_poly->transform.position;
		DrawCircleLines(handle.x, handle.y, 14.0f, RED);
	}
}

Editor_State StateManager::getCurrentState() const { return current_state; }

/**
 * @brief Handler for controller which allows us to manipulate existing
 * polygons, such as dragging, rotating, etc.
 */
void StateManager::handleController()
{
	if (IsKeyReleased(KEY_TAB))
	{
		current_state = Editor_State::Idle;
		selected_poly = nullptr;
		is_dragging = false;
		return;
	}

	Vector2 mouse_pos = GetMousePosition();

	// Select polygon on click
	if (!is_dragging && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		for (int i = 0; i < scene.getObjects().size(); ++i)
		{
			Vector2 handle = scene.getObjects()[i]->transform.position;
			if (CheckCollisionPointCircle(mouse_pos, handle, 30.0f))
			{
				selected_poly = scene.getObjects()[i];
				drag_offset = {mouse_pos.x - handle.x, mouse_pos.y - handle.y};
				is_dragging = true;
				break;
			}
		}
	}

	// Drag selected polygon
	if (is_dragging && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selected_poly)
	{
		Vector2 new_pos = {mouse_pos.x - drag_offset.x,
						   mouse_pos.y - drag_offset.y};
		selected_poly->force.setStatic(true);
		selected_poly->transform.position = new_pos;
	}

	// Release polygon
	if (is_dragging && IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		is_dragging = false;
		selected_poly->force.setStatic(false);
	}

	// Rotate using Q and E
	if (selected_poly && IsKeyPressed(KEY_E))
		selected_poly->transform.rotation += 15.0f;

	if (selected_poly && IsKeyPressed(KEY_Q))
		selected_poly->transform.rotation -= 15.0f;

	// Scale using [ and ]
	if (selected_poly && IsKeyPressed(KEY_LEFT_BRACKET))
		selected_poly->transform.scale = {
				selected_poly->transform.scale.x - 0.1f,
				selected_poly->transform.scale.y - 0.1f};

	if (selected_poly && IsKeyPressed(KEY_RIGHT_BRACKET))
		selected_poly->transform.scale = {
				selected_poly->transform.scale.x + 0.1f,
				selected_poly->transform.scale.y + 0.1f};
}
