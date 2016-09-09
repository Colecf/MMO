#!/bin/sh

# using cross compiler from here:
# http://crossgcc.rts-software.org/doku.php?id=start

# DOES NOT WORK

/usr/local/gcc-4.8.0-qt-4.8.4-for-mingw32/win32-gcc/bin/i586-mingw32-g++ -std=gnu++0x -I/usr/local/gcc-4.8.0-qt-4.8.4-for-mingw32/win32-gcc/include -L/usr/local/gcc-4.8.0-qt-4.8.4-for-mingw32/win32-gcc/lib -static-libgcc -lmingw32 -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -lSDL2main -lSDL2 -lSDL2_net -lSDL2_image -lSDL2_ttf -mwindows -o MMO.exe FPSCounter.cpp Player.cpp ResourcePath.cpp ColeTileset.cpp ColeTexture.cpp StrToInt.cpp NetworkManager.cpp RenderManager.cpp RealMain.cpp MainMenu.cpp GameScene.cpp ColeFontManager.cpp ColeTextBox.cpp main.cpp ColeScene.cpp OtherPlayer.cpp