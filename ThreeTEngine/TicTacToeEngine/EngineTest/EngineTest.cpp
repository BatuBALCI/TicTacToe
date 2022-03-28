#include "pch.h"
#include "CppUnitTest.h"
#include "../TicTacToeEngine/Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTest
{
	TEST_CLASS(EngineTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			auto name = make_shared<Types::StringGame>(L"Batu");;
			auto starter = make_shared<Types::BooleanGame>(true);

			auto obj = Player::Player(name, starter);
		}
	};
}
