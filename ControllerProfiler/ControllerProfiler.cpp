#include <iostream>
#include <map>
#include <string>
#include <SDL.h>
using namespace std;

#undef main 
int main()
{
	SDL_Event event;
	SDL_Renderer* renderer;
	SDL_Window* window;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Init(SDL_INIT_JOYSTICK);
	
	SDL_Joystick* js = SDL_JoystickOpen(0);
	if (!js)
	{
		cout << "No controller connected." << endl;
		exit(1);
	}
	SDL_JoystickEventState(SDL_ENABLE);

	window = SDL_CreateWindow("ControllerProfiler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 300, 100, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	cout << "(Keep small window on top to get input.)" << endl;
	cout << SDL_JoystickName(js) << endl;


	map<Uint8, string> hats = {
		{SDL_HAT_UP, "up"},
		{SDL_HAT_RIGHT, "right"},
		{SDL_HAT_DOWN, "down"},
		{SDL_HAT_LEFT, "left"},
		{SDL_HAT_RIGHTUP, "right up"},
		{SDL_HAT_RIGHTDOWN, "right down"},
		{SDL_HAT_LEFTUP, "left up"},
		{SDL_HAT_LEFTDOWN, "left down"}

	};

	while (true)
	{
		const Uint8* keystate = SDL_GetKeyboardState(NULL);

		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				exit(0);
		}

		// buttons
		for (int i = 0; i < SDL_JoystickNumButtons(js); i++)
		{
			if (SDL_JoystickGetButton(js, i))
			{
				cout << "Button " << i + 1 << endl;
				SDL_Delay(100);
			}
		}

		// axis 
		/*
		for (int i = 0; i < SDL_JoystickNumAxes(js); i++)
		{
			int state = SDL_JoystickGetAxisInitialState(js, i, NULL);
			if (SDL_JoystickGetAxis(js, i) != state)
			{
				cout << "Axis " << i+1 << " " << SDL_JoystickGetAxis(js, i) << endl;
				SDL_Delay(100);
			}
		}
		*/

		// hats
		for (int i = 0; i < SDL_JoystickNumHats(js); i++)
		{
			if (SDL_JoystickGetHat(js, i))
			{
				cout << "Hat " << i+1 << " " << hats[SDL_JoystickGetHat(js, i)] << endl;
				SDL_Delay(100);
			}
		}




		SDL_RenderPresent(renderer);

	}
	return 0;
}
