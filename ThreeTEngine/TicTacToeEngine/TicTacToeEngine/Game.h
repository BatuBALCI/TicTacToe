#pragma once
#include <vector>

#include "Player.h"

class classExport Game
{
public:
	Player::Player* player1;
	Player::Player* player2;
	Game();
	void InitGame();
	void updateGame(unsigned int xPos, unsigned int yPos, unsigned short type);
	bool IsUpdatable(unsigned int xPos, unsigned int yPos);
	bool decideWinner(unsigned int xPos, unsigned int yPos, unsigned short type);
	void FindOffset(std::vector<std::pair<float, float>>& offsetPairs, float xLoc, float yLoc, float width, float height, unsigned short& xPos, unsigned short& yPos);
	void UpdatePositions(unsigned int type, int width, int height, float mouseXLocation, float mouseYLocation);
	void RestartGame();
	bool IsWinner();
	std::vector<std::pair<float, float>> GetOffsetPairX();
	std::vector<std::pair<float, float>> GetOffsetPairO();
	void ClearTable();
	~Game();
private:
	std::vector<std::vector<unsigned short>> table;
	bool isWinner = false;
	std::vector<std::pair<float, float>> offsetPairX;
	std::vector<std::pair<float, float>> offsetPairO;
	float previousXLocation;
	float previousYLocation;
};