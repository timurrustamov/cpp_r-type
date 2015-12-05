#include					<iostream>
#include					"System/window.h"
#include					"GameEngine/Gameplay.h"

int							main()
{
	Window					window("R-Type");
	Gameplay				gameplay;

	window.attachGameplay(&gameplay);
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