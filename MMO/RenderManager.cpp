//
//  RenderManager.cpp
//  MMO
//
//  Created by Cole Faust on 12/19/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#include "RenderManager.h"
#include <SDL2_image/SDL_image.h>

SDL_Surface* RenderManager::loadSurface( std::string path )
{
    if (screen == NULL)
        return NULL;
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.substr(path.find_last_of('/')).c_str(), IMG_GetError() );
        return NULL;
	}
	else
	{
		optimizedSurface = SDL_ConvertSurface( loadedSurface, screen->format, NULL );
        SDL_FreeSurface( loadedSurface );
		if( optimizedSurface == NULL )
		{
			printf( "Unable to optimize image %s! SDL Error: %s\n", path.substr(path.find_last_of('/')).c_str(), SDL_GetError() );
            return NULL;
		}
	}
    
	return optimizedSurface;
}

void RenderManager::updateScreen()
{
    SDL_UpdateWindowSurface(window);
}

void RenderManager::init(SDL_Window *window)
{
    this->window = window;
    this->screen = SDL_GetWindowSurface(window);
}

void RenderManager::cleanup()
{
    SDL_DestroyWindow(window);
    SDL_FreeSurface(screen);
}