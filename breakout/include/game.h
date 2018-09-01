#ifndef ENGINE_UBER_H
#define ENGINE_UBER_H

#include "engine.h"

/**
 * Represents the current state of the game
 */
enum class GameState
{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	/**
	 * Constructor/Destructor
	 * Initialize the game by giving a width and height (corresponding to the resolution you want to play the game in)
	 */
	Game(GLuint width, GLuint height);
	~Game();

	/**
	 * Initialize game state (load all shaders/textures/levels)
	 */
	 void Init();

	 /**
	  * Game Loop
	  */
	  void ProcessInput(float delta_time);
	  void Update(float delta_time);
	  void Render();
private:
	// Game state
	GameState state;
	GLboolean keys[1024];
	GLuint	  width, height;
};


#endif //ENGINE_UBER_H
