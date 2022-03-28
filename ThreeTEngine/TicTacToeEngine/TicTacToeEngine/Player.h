#pragma once
#include "Types.h"
#include <deque>

namespace Player
{
	class classExport Player
	{
	public:
		deque<pair<int, int>> points;

		Player();
		Player(Types::StringGame name, Types::IntegarGame starter);
		~Player();
		Types::IntegarGame GetType();
		Types::StringGame GetName();
		void SetName(const Types::StringGame& name);
		void SetType(const Types::IntegarGame& type);
	private:
		Types::StringGame name;
		Types::IntegarGame type;
	};
}