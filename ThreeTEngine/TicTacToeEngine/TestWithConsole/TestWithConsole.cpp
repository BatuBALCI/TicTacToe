#include "../TicTacToeEngine/Player.h"
#include <vector>

int main()
{
	auto name = make_shared<Types::StringGame>(L"Batu");;
	auto starter = make_shared<Types::BooleanGame>(true);

	auto obj = Player::Player(name, starter);
}