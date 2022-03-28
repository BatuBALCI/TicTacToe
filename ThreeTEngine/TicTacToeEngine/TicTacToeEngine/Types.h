#pragma once
#include "Template.h"

namespace Types
{
	class classExport BooleanGame : public Tamplate::BaseGame
	{
	public:
		BooleanGame() : value(false) {}
		BooleanGame(bool value) : value(value) {
		}
		// Copy constructor
		BooleanGame(const BooleanGame& copyBool) : value(copyBool.value) {
		}
		BooleanGame(BooleanGame&& moveBool) noexcept : value(moveBool.value) {
			moveBool.value = false;
		}

		bool getValue() 
		{
			return value;
		}
	private:
		bool value;
	};

	class classExport IntegarGame : public Tamplate::BaseGame
	{
	public:
		IntegarGame() : value(0) {}
		IntegarGame(int value) : value(value) {}
		// Copy constructor
		IntegarGame(const IntegarGame& copyBool) : value(copyBool.value) {}
		IntegarGame(IntegarGame&& moveBool) noexcept : value(moveBool.value) {
			moveBool.value = 0;
		}

		int getValue()
		{
			return value;
		}
	private:
		int value;
	};

	class classExport DoubleGame : public Tamplate::BaseGame
	{
	public:
		DoubleGame() : value(0.0) {}
		DoubleGame(double value) : value(value) {}
		// Copy constructor
		DoubleGame(const DoubleGame& copyBool) : value(copyBool.value) {}
		DoubleGame(DoubleGame&& moveBool) noexcept : value(moveBool.value) {
			moveBool.value = 0.0;
		}

		double getValue()
		{
			return value;
		}
	private:
		double value;
	};

	class classExport StringGame : public Tamplate::BaseGame
	{
	public:
		StringGame() : value(L"") {}
		StringGame(wstring value) : value(value) {}
		// Copy constructor
		StringGame(const StringGame& copyBool) : value(copyBool.value) {}
		StringGame(StringGame&& moveBool) noexcept : value(moveBool.value) {
			moveBool.value.empty();
		}

		wstring getValue()
		{
			return value;
		}
	private:
		wstring value;
	};

}
