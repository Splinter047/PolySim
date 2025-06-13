#include "../include/state_manager.h"

StateManager::StateManager(Scene &scene)
	: scene(scene), current_state(Editor_State::Idle) {
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
	}
}

/**
 * @brief Handles input accordingly to the idle state
 */
void StateManager::handleIdle()
{
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
}

Editor_State StateManager::getCurrentState() const { return current_state; }
