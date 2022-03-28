#pragma once
#include <unordered_map>
#include <memory>
#include <iostream>
#include <string>

#define classExport __declspec(dllexport)

using namespace std;

namespace Types
{
	class classExport BooleanGame
	{
	public:
		BooleanGame() : value(false) {}
		BooleanGame(bool value) : value(value) {
		}
		// Copy constructor
		BooleanGame(const BooleanGame& copyBool) : value(copyBool.value) {
		}

		bool getValue() 
		{
			return value;
		}
	private:
		bool value;
	};

	class classExport IntegarGame
	{
	public:
		IntegarGame() : value(0) {}
		IntegarGame(int value) : value(value) {}
		// Copy constructor
		IntegarGame(const IntegarGame& copyBool) : value(copyBool.value) {}

		int getValue()
		{
			return value;
		}
	private:
		int value;
	};

	class classExport DoubleGame
	{
	public:
		DoubleGame() : value(0.0) {}
		DoubleGame(double value) : value(value) {}
		// Copy constructor
		DoubleGame(const DoubleGame& copyBool) : value(copyBool.value) {}

		double getValue()
		{
			return value;
		}
	private:
		double value;
	};

	class classExport StringGame
	{
	public:
		StringGame() : value(L"") {}
		StringGame(wstring value) : value(value) {}
		// Copy constructor
		StringGame(const StringGame& copyBool) : value(copyBool.value) {}

		wstring getValue()
		{
			return value;
		}
	private:
		wstring value;
	};

}
