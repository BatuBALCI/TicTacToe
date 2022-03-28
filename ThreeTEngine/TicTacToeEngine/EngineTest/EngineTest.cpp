#include "pch.h"
#include "CppUnitTest.h"
#include "../TicTacToeEngine/Player.h"
#include "../TicTacToeEngine/Game.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTest
{
	TEST_CLASS(EngineTest)
	{
	public:
		
		TEST_METHOD(CreateAndDeletePlayerObject)
		{
			auto name = Types::StringGame(L"Batu");
			auto starter = Types::IntegarGame(1);

			auto obj = Player::Player(name, starter);
			obj.~Player();
		}
		TEST_METHOD(CreateAndDeleteGameObject)
		{
			auto obj = Game::Game();
			obj.~Game();
		}
		TEST_METHOD(TryGameObjectMethods)
		{
			auto obj = Game::Game();
			obj.RestartGame();
			auto name = Types::StringGame(L"Batu");
			auto starter = Types::IntegarGame(1);
			obj.player1->SetName(name);
			obj.player1->SetType(starter);

			obj.player2->SetName(name);
			obj.player2->SetType(starter);

			auto name1 = obj.player1->GetName().getValue();
			auto type1 = obj.player1->GetType().getValue();

			auto name2 = obj.player2->GetName().getValue();
			auto type2 = obj.player2->GetType().getValue();
		}
		TEST_METHOD(TryPlayerObject)
		{
			auto name = Types::StringGame(L"Batu");
			auto starter = Types::IntegarGame(1);

			auto obj = Player::Player(name, starter);
		}
	};
}
