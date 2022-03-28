#pragma once
#include "Types.h"
#include <deque>

namespace Player
{
	class classExport Player : public Tamplate::BaseGame
	{
	public:
		deque<pair<int, int>> points;

		Player();
		Player(shared_ptr<Types::StringGame> name, shared_ptr < Types::BooleanGame> starter);
		Player(const Player& copyObj);
		Player(Player&& moveObj);
		~Player();
	private:
		Types::StringGame* name;
		Types::BooleanGame* starter;
	};
}