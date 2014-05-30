//
//  ColeTileset.cpp
//  MMO
//
//  Created by Cole Faust on 12/28/13.
//  Copyright (c) 2013 Cole Faust. All rights reserved.
//

#include "ColeTileset.h"
#include <fstream>
#include "StrToInt.h"

std::shared_ptr<ColeTileset> ColeTileset::loadedSet;

int find_xth_of(std::string s, char c, int count)
{
    int result = 0;
    for (int i=0; i<count; i++) {
        result += s.find(c)+1;
        s = s.substr(s.find(c)+1);
    }
    return result-1;
}

ColeTileset::ColeTileset(std::string path) : ColeTexture(path+".png")
{
    std::ifstream file((path+".txt").c_str());
    std::string line;
    int width, height = 0;
    bool customSize = true;
    while (file.good())
    {
        getline(file, line);
        if(line == "" || line.at(0) == '#') continue;
        
        std::string name = line.substr(0, line.find(' '));
        
        if (name == "universalsize")
        {
            unsigned long lastSpace = line.find_last_of(' ');
            height = strToInt(line.substr(lastSpace+1));
            unsigned long secondToLastSpace = line.find_last_of(' ', lastSpace);
            width = strToInt(line.substr(secondToLastSpace+1, lastSpace-(secondToLastSpace+1)));
            customSize = false;
            continue;
        } else if (name == "customsize")
        {
            customSize = true;
            continue;
        }
        
        unsigned long secondSpace = find_xth_of(line, ' ', 2);
        unsigned long thirdSpace = find_xth_of(line, ' ', 3);
        unsigned long fourthSpace = find_xth_of(line, ' ', 4);
        unsigned long fithSpace = find_xth_of(line, ' ', 5);
        
        int x = strToInt(line.substr(secondSpace+1, thirdSpace-(secondSpace+1)));
        int y;
        
        if (customSize)
        {
            y = strToInt(line.substr(thirdSpace+1, fourthSpace-(thirdSpace+1)));
            width = strToInt(line.substr(fourthSpace+1, fithSpace-(fourthSpace+1)));
            height = strToInt(line.substr(fithSpace));
        } else {
            y = strToInt(line.substr(thirdSpace+1));
        }
        //std::cout << name << " = " << x << " " << y << " " << width << " " << height << std::endl;
        SDL_Rect rect = {x, y, width, height};
        tileNames[name] = rect;
    }
}

void ColeTileset::renderTile(int x, int y, std::string tileName)
{
    ColeTexture::render(x, y, tileNames[tileName]);
}