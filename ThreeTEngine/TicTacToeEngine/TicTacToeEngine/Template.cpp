#include "Template.h"

void Tamplate::BaseGame::addParameter(wstring Tag, shared_ptr<Tamplate::BaseGame> obj) {
	gameParams[Tag] = obj;
}