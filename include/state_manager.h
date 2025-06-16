#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "pen_tool.h"
#include "scene.h"

/**
 * Defines possible states/modes of our tool
 */
enum class Editor_State
{
	Idle,
	Drawing,
	Controller
};

/**
 * @brief Responsible for switching and activating the appropriate states and
 * accordingly render out the scebe
 */
class StateManager
{
private:
	Scene &scene;
	Pen_Tool pen_tool;
	Editor_State current_state;

	Polygon* selected_poly;
	bool is_dragging;
	Vector2 drag_offset;

	void handleIdle();
	void handleDrawing();
	void handleController();

public:
	explicit StateManager(Scene &scene);

	void handleInput();
	void draw() const;
	Editor_State getCurrentState() const;
};

#endif
