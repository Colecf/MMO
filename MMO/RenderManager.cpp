//
//  RenderManager.cpp
//  MMO
//
//  Created by Cole Faust on 12/19/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#include "RenderManager.h"
#include <SDL2_image/SDL_image.h>


SDL_Surface* RenderManager::loadSurface(std::string path)
{
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.substr(path.find_last_of('/')).c_str(), IMG_GetError() );
        return NULL;
	}
    
	return loadedSurface;
}
SDL_Texture* RenderManager::loadTexture(std::string path, int* width, int* height)
{
    if (renderer == NULL)
        return NULL;
	SDL_Texture* texture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.substr(path.find_last_of('/')).c_str(), IMG_GetError() );
        return NULL;
	}
	else
	{
        *width = loadedSurface->w;
        *height = loadedSurface->h;
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface( loadedSurface );
		if( texture == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.substr(path.find_last_of('/')).c_str(), SDL_GetError() );
            return NULL;
		}
	}
    
	return texture;
}
SDL_Texture* RenderManager::loadTexture(std::string path)
{
    int w, h;
    return loadTexture(path, &w, &h);
}

SDL_Texture* RenderManager::createTextureFromSurface(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(renderer, surface);
}

SDL_Surface* RenderManager::createSDLSurface(int width, int height)
{
    Uint32 rmask, gmask, bmask, amask;
    
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
    return SDL_CreateRGBSurface(0, width, height, 32, rmask, gmask, bmask, amask);
}

void RenderManager::scaleRenderer(float x, float y)
{
    scaleX = x;
    scaleY = y;
    SDL_RenderSetScale(renderer, x, y);
}
float RenderManager::getScaleX(){return scaleX;}
float RenderManager::getScaleY(){return scaleY;}

void RenderManager::clearScreen(){SDL_RenderClear(renderer);}
void RenderManager::updateScreen(){SDL_RenderPresent(renderer);}

void RenderManager::init(SDL_Window *window)
{
    if(window == NULL)
    {
        std::cout << "Window passed to RenderManager::init() is NULL!" << std::endl;
        return;
    }
    this->window = window;
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        std::cout << "Could not create SDL_Renderer! " << SDL_GetError() << std::endl;
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void RenderManager::cleanup()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

