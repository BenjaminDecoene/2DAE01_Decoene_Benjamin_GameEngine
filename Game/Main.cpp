#include "Minigin.h"
#include "BubbleBobble.h"
//#include <vld.h>

int main(int, char*[]) {
	dae::Minigin engine;

	const auto pGame = new BubbleBobble();

	engine.Init();
	engine.Run();
	
	delete pGame;
    return 0;
}