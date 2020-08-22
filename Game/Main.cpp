#include "pch.h"
#include "Minigin.h"
#include "Digger.h"


int main(int, char*[]) {
	dae::Minigin engine;

	const auto pGame = new Digger();

	engine.Init();
	engine.Run();
	
	delete pGame;
    return 0;
}
