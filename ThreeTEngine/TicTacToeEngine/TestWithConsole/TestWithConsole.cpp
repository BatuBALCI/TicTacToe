#include "../TicTacToeEngine/Player.h"
#include <vector>

int main()
{
	auto name = Types::StringGame(L"Batu");
	auto starter = Types::IntegarGame(1);

	auto obj = Player::Player(name, starter);
}