//
//  main.m
//  MMO
//
//  Created by Cole Faust on 12/19/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#include "RealMain.h"
#include "SDL2.h"   // Need to include SDL here to it processes the main function
                    // Otherwise you get Undefined reference to SDL_main

int main(int argc, char * arg[])
{
    return realMain(argc, arg);
}
