#include "Player.h"


Player::Player::Player() : name(L""), type(0)
{
};

Player::Player::Player(Types::StringGame name, Types::IntegarGame type) : name(name), type(type)
{
}

Player::Player::~Player()
{
}

Types::StringGame Player::Player::GetName()
{
	return name;
}

Types::IntegarGame Player::Player::GetType()
{
	return type;
}

void Player::Player::SetName(const Types::StringGame& name)
{
	this->name = name;
}

void Player::Player::SetType(const Types::IntegarGame& type)
{
	this->type = type;
}