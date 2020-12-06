#pragma once
#include <SDL2/SDL.h>
#include <exception>
#include <string>
#include "SDLException.h"

class Window
{
public:
    Window(int width, int height, SDL_Color color);
    ~Window();
    SDL_Window* getWindowObject() const;
    SDL_Surface* getSurface() const;
    SDL_Renderer* getRenderer() const;
    void update();
private:
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurf = nullptr;
    SDL_Renderer* renderer = nullptr;
    int WIDTH, HEIGHT;
};

