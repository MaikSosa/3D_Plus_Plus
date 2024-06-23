//
// Created by mike on 6/21/2024.
//
#include <SDL.h>
#include <vector>

class Screen {
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;

public:Screen() //Creating the window to display the render figure
    {
        //Constructor
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(
                640*2,480*2,0,&window,&renderer);
        SDL_RenderSetScale(renderer,2,2);
    }

void pixel(float x, float y)
    {
        points.emplace_back(x,y);
    }

void show()
    {
        //Set the background black
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);

        Uint32 currentTime = SDL_GetTicks();
        // Declare a variable to track the last time color was changed
        Uint32 lastColorChangeTime = 0;

        // Define the interval between color changes (milliseconds)
        Uint32 colorChangeInterval = 10000; // Change color every 10 second
        if (currentTime - lastColorChangeTime >= colorChangeInterval) {
            // Generate a new random color
            Uint8 r = (Uint8)(rand() % 256);
            Uint8 g = (Uint8)(rand() % 256);
            Uint8 b = (Uint8)(rand() % 256);
            Uint8 a = 255;

            // Set the drawing color
            SDL_SetRenderDrawColor(renderer, r, g, b, a);

            // Update last color change time
            lastColorChangeTime = currentTime;
            SDL_Delay(30);
        }

        for (auto &point: points) {
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }
        SDL_RenderPresent(renderer);

    }

void clear()
    {
        points.clear();
    }

void input()
   {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                SDL_Quit();
                exit(0);
            }
        }
    }
};
