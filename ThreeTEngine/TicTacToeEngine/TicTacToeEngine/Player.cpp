#include "Player.h"

Player::Player::Player() : name(nullptr), starter(nullptr)
{
};

Player::Player::Player(shared_ptr<Types::StringGame> name, shared_ptr < Types::BooleanGame> starter) : name(name.get()), starter(starter.get())
{
	addParameter(L"name", name);
	addParameter(L"starter", starter);
}

Player::Player::Player(const Player& copyObj) : name(copyObj.name), starter(copyObj.starter)
{
}

Player::Player::Player(Player&& moveObj) 
{
	name = moveObj.name;
	starter = moveObj.starter;

	moveObj.name = nullptr;
	moveObj.starter = nullptr;
}

Player::Player::~Player()
{
}