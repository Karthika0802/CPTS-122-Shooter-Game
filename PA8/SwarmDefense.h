#ifndef SWARM_DEFENSE_H
#define SWARM_DEFENSE_H

#include "Screen.h"
#include "MoveableRectangle.h"
#include "TextComponent.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>
#include <random>
#include <queue>
#include <cmath>
#include <iostream>
#include "Enemy.h"
#include "GhostAnimation.h"
#include "ShopModal.h"

/// <summary>
/// Forward declaration of screen manager.
/// </summary>
class ScreenManager;

/// <summary>
/// The screen holding the swarm defense game.
/// </summary>
class SwarmDefense : public Screen
{
public:
	/// <summary>
	/// Initializes several critical internal members.
	/// </summary>
	/// <param name="vm">The video mode that will render this screen.</param>
	/// <param name="mp">Whether the game is in multiplayer mode.</param>
	/// <param name="manager">The parent screen manager that has this screen as a member as well as the callback functions.</param>
	/// <param name="sendEnemiesCallback">The callback function to send enemies to the player connected on the network.</param>
	/// <param name="getEnemiesCallback">The callback function to get the enemies sent by the player connected on the network.</param>
	SwarmDefense(
		sf::VideoMode vm,
		bool mp,
		ScreenManager* manager,
		void(ScreenManager::* sendEnemiesCallback)(sf::Uint16 numberOfEnemies),
		sf::Uint16(ScreenManager::* getEnemiesCallback)()
		);

	~SwarmDefense();

	/// <summary>
	/// Draw this screen to the window.
	/// </summary>
	/// <param name="window">The window to draw to.</param>
	void drawTo(sf::RenderWindow& window);

	/// <summary>
	/// Processes the user's keyboard input.
	/// </summary>
	void processKeyboardInput();

	/// <summary>
	/// Process the current mouse position.
	/// </summary>
	/// <param name="mouseWindowPosition">The current mouse position.</param>
	void processMousePosition(sf::Vector2i mouseWindowPosition);

	/// <summary>
	/// Returns true if the user wants to exit the current screen.
	/// </summary>
	/// <returns>True if the user wants to exit the current screen.</returns>
	bool shouldExitGame();

	/// <summary>
	/// Handles the events generated by the window.
	/// </summary>
	/// <param name="window">The window generating the events.</param>
	void handleEvents(sf::RenderWindow& window);

	/// <summary>
	/// Updates the internal state of this screen.
	/// </summary>
	void updateState();

	/// <summary>
	/// Purchases an item and decreases from the available coins.
	/// </summary>
	/// <param name="Price">The price of the current item.</param>
	void purchase(int Price);
	

private:
	/// <summary>
	/// The ID of the next enemy to be created. Incremented each time an enemy is created.
	/// </summary>
	int currentEnemyId;

	/// <summary>
	/// A pointer to the rectangle containing the user's base.
	/// </summary>
	MoveableRectangle* playerBase;

	/// <summary>
	/// The video mode that will render this screen.
	/// </summary>
	sf::VideoMode videoMode;

	/// <summary>
	/// Is set to true when the user wants to exit the current screen.
	/// </summary>
	bool shouldGoBackToMainMenu;

	/// <summary>
	/// A list of pointers to enemies currently alive.
	/// </summary>
	std::list<Enemy*> enemies;

	/// <summary>
	/// Generates a new enemy and adds it to the list.
	/// </summary>
	void generateEnemy();

	/// <summary>
	/// A queue containing the IDs of the enemies to be destroyed.
	/// </summary>
	std::queue<int> enemiesToDestroy;

	/// <summary>
	/// The number of enemies that have collided with the player's base.
	/// </summary>
	int enemiesCollided;

	/// <summary>
	/// A pointer to the text component that displays the score.
	/// </summary>
	TextComponent* displayedScore;

	/// <summary>
	/// A pointer to the text component that displays the player's health.
	/// </summary>
	TextComponent* displayedHealth;

	/// <summary>
	/// A pointer to the text component that displays the coins earned by the user.
	/// </summary>
	TextComponent* displayedCoins;

	/// <summary>
	/// The player's current score.
	/// </summary>
	unsigned int score;

	/// <summary>
	/// The player's current coins.
	/// </summary>
	unsigned int coins;

	/// <summary>
	/// The player's current health.
	/// </summary>
	unsigned short int health;

	/// <summary>
	/// Destroy all enemies in the queue.
	/// </summary>
	void destroyEnemies();

	/// <summary>
	/// Check for any collisions between the enemies and the player's base.
	/// </summary>
	void checkForCollisions();

	/// <summary>
	/// Is true when the player loses all of their health.
	/// </summary>
	bool isGameOver;

	/// <summary>
	/// Is true when the player entered this game in multiplayer mode.
	/// </summary>
	bool isMultiplayer;

	/// <summary>
	/// A pointer to the screen manager that has this screen as a member as well as the callback functions.
	/// </summary>
	ScreenManager* parentManager;

	/// <summary>
	/// The callback function for sending enemies to the player connected on the network.
	/// </summary>
	void(ScreenManager::* onSendEnemies)(sf::Uint16 numberOfEnemies);

	/// <summary>
	/// The callback function for getting the number of enemies sent by the player on the network.
	/// </summary>
	sf::Uint16(ScreenManager::* onGetEnemies)();

	/// <summary>
	/// The unit of distance calculated on construction as a portion of the current screen dimensions.
	/// </summary>
	float unitOfDistance;

	/// <summary>
	/// The distance travelled since the last iteration, calculated using time, velocity, and unit of distance based on screen size.
	/// </summary>
	/// <returns>A number representing the units of distance travelled, where units of distance are based on screen size.</returns>
	float distanceTravelled();

	/// <summary>
	/// A clock to track the time between iterations to ensure movements are time based and not processor speed based.
	/// </summary>
	sf::Clock clock;

	/// <summary>
	/// The time elapsed since the last iteration in microseconds.
	/// </summary>
	sf::Time timeElapsed;

	/// <summary>
	/// The texture containing the castle image.
	/// </summary>
	sf::Texture castleTexture;

	/// <summary>
	/// An array of textures containing the images for the different ghost frames.
	/// </summary>
	sf::Texture ghostTextures[14];

	/// <summary>
	/// The modal that will display the shop.
	/// </summary>
	ShopModal* shopModal;

	//Audio
	sf::Music music;
	sf::SoundBuffer Hit;
	sf::SoundBuffer Explosion;
	sf::SoundBuffer Lose;
	sf::Sound sound; //To hold various soundbuffers
	bool isGameOverMusic = false;//Stores whether or not game over music is playing
};

#endif // !SWARM_DEFENSE_H
