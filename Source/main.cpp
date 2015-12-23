#include					<iostream>
#include					"System/window.h"
#include					"GameEngine/OnLevel.h"

#include					"System/Animation.h"
#include					"System/ResourcesBank.h"

int							main()
{
	Window					window("R-Type");
	OnLevel					gameplay;
	Level					level("../Data/level1.xml");
	
	try
	{
		gameplay.loadLevel(&level);
		window.attachGameplay(dynamic_cast<IGameplay *>(&gameplay));

		window.launchWindow();
		while (window.isOpen())
		{
			window.callGameplay();
			window.draw(gameplay);
		}
	}
	catch (const RTypeException &err)
	{
		std::cerr << "RType Exception: " << err.what() << std::endl;
		system("pause");
		return (1);
	}
	catch (const std::exception &err)
	{
		std::cerr << "std::exception: " << err.what() << std::endl;
		system("pause");
		return (1);
	}
	return (0);
}