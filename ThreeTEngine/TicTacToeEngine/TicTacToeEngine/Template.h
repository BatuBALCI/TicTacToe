#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <iostream>

#define classExport __declspec(dllexport)


using namespace std;
namespace Tamplate
{
	class classExport BaseGame
	{
	public:
		//This map holds the parameters 
		unordered_map<wstring, shared_ptr<BaseGame>> gameParams;

		void addParameter(wstring Tag, shared_ptr<BaseGame> obj);

		template <typename T>
		T getParameter(wstring Tag) {
			return gameParams.find(Tag)->second;
		}

	};
}