#include "Game.h"

Game::Game()
{
	std::vector<unsigned short> vec1 = { 0, 0, 0 };
	std::vector<unsigned short> vec2 = { 0, 0, 0 };
	std::vector<unsigned short> vec3 = { 0, 0, 0 };

	table.push_back(vec1);
	table.push_back(vec2);
	table.push_back(vec3);

	player1 = new Player::Player();
	player2 = new Player::Player();
}

void Game::InitGame() 
{
	std::vector<unsigned short> vec1 = { 0, 0, 0 };
	std::vector<unsigned short> vec2 = { 0, 0, 0 };
	std::vector<unsigned short> vec3 = { 0, 0, 0 };

	table.push_back(vec1);
	table.push_back(vec2);
	table.push_back(vec3);

	player1 = new Player::Player();
	player2 = new Player::Player();
}


bool Game::IsUpdatable(unsigned int xPos, unsigned int yPos) 
{
	if (table.at(xPos).at(yPos) != 0)
		return false;
	return true;
}

// This method update the game table for every turn.
void Game::updateGame(unsigned int xPos, unsigned int yPos, unsigned short type) 
{
	table.at(xPos).at(yPos) = type;
	if (decideWinner(xPos, yPos, type))
		isWinner = true;
}

// This method checks whether the game has winner or not by looking at the updated positions and the type.
bool Game::decideWinner(unsigned int xPos, unsigned int yPos, unsigned short type)
{
	bool isWonC = true;
	bool isWonR = true;
	bool isWonCR = true;
	bool isWonRC = true;

	for (int i = 0; i < 3; i++)
	{
		if (table.at(xPos).at(i) != type)
			isWonR = false;
		if (table.at(i).at(yPos) != type)
			isWonC = false;
		if (xPos == yPos)
		{
			if (table.at(i).at(i) != type)
				isWonCR = false;
		}
		else
			isWonCR = false;
		if ((xPos + yPos) == 2)
		{
			if (table.at(2-i).at(i) != type)
				isWonRC = false;
		}
		else
			isWonRC = false;
	}
	if (isWonCR || isWonR || isWonC || isWonRC)
		return true;
	else
		return false;
}

void Game::FindOffset(std::vector<std::pair<float, float>>& offsetPairs, float xLoc, float yLoc, float width, float height, unsigned short& xPos, unsigned short& yPos)
{
	float xOffset;
	float yOffset;

	if (xLoc / width < 0.333333) {
		xOffset = -0.666666f;
		xPos = 0;
	}
	else if (xLoc / width < 0.6666666) {
		xOffset = 0.0f;
		xPos = 1;
	}
	else {
		xOffset = 0.666666f;
		xPos = 2;
	}

	if (yLoc / height < 0.333333) {
		yOffset = 0.666666f;
		yPos = 0;
	}
	else if (yLoc / height < 0.6666666) {
		yOffset = 0.0f;
		yPos = 1;
	}
	else {
		yOffset = -0.666666f;
		yPos = 2;
	}

	std::pair<float, float> pairs(xOffset, yOffset);
	offsetPairs.push_back(pairs);
}

// A lambda function to update the x and y positions according to the mouse clicks.
void Game::UpdatePositions(unsigned int type, int width, int height, float mouseXLocation, float mouseYLocation)
{
	unsigned short xPos;
	unsigned short yPos;
	if (mouseXLocation != previousXLocation || mouseYLocation != previousYLocation)
	{
		previousXLocation = mouseXLocation;
		previousYLocation = mouseYLocation;
		if (type == 1) {
			this->FindOffset(offsetPairX, previousXLocation, previousYLocation, width, height, xPos, yPos);
			if (!this->IsUpdatable(xPos, yPos)) {
				offsetPairX.pop_back();
				return;
			}
		}
		else if (type == 2) {
			this->FindOffset(offsetPairO, previousXLocation, previousYLocation, width, height, xPos, yPos);
			if (!this->IsUpdatable(xPos, yPos)) {
				offsetPairO.pop_back();
				return;
			}
		}
		this->updateGame(xPos, yPos, type);
	}
}

void Game::RestartGame()
{
	this->~Game();
	this->InitGame();
}

bool Game::IsWinner()
{
	return isWinner;
}

std::vector<std::pair<float, float>> Game::GetOffsetPairX()
{
	return offsetPairX;
}
std::vector<std::pair<float, float>> Game::GetOffsetPairO()
{
	return offsetPairO;
}

void Game::ClearTable()
{
	table.clear();
	offsetPairX.clear();
	offsetPairO.clear();
	isWinner = false;
	delete player1;
	delete player2;
}


Game::~Game()
{
	ClearTable();
}