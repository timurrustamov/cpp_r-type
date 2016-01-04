#include					<iostream>
#include					"System/window.h"
#include					"GameEngine/GameData.h"
#include					"Editor/OnEditor.h"

#include					"System/Animation.h"
#include					"System/ResourcesBank.h"

int							main()
{
	Window					window("R-Type");
	OnEditor				editor(&window.window);

	try
	{
		srand(time(NULL));
		window.attachGameplay(dynamic_cast<IGameplay *>(&editor));
		window.resizeWindow(EDITOR_WIDTH, EDITOR_HEIGHT);

		window.launchWindow();
		while (window.isOpen())
		{
			window.callGameplay();
			window.draw(editor);
		}
	}
	catch (const RTypeException &err)
	{
		std::cerr << "RType Editor Exception: " << err.what() << std::endl;
		system("pause");
		return (1);
	}
	catch (const std::exception &err)
	{
		std::cerr << "RType Editor std::exception: " << err.what() << std::endl;
		system("pause");
		return (1);
	}
	return (0);
}