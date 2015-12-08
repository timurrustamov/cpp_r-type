#include					<iostream>
#include					"System/window.h"
#include					"GameEngine/OnLevel.h"

int							main()
{
	Window					window("R-Type");
	OnLevel					gameplay;

	window.attachGameplay(dynamic_cast<IGameplay *>(&gameplay));
	try
	{
		window.launchWindow();
		while (window.isOpen())
		{
			window.callGameplay();
		}
	}
	catch (const RTypeException &err)
	{
		std::cerr << err.what() << std::endl;
		return (1);
	}
	return (0);
}