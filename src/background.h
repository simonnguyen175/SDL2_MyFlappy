#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "textureManager.h"
#include <vector>

using namespace std;

class background : LTexture
{
public:
    bool init();

    void free();

    void render();

    void update();

private:
    position posBackground;
};

#endif