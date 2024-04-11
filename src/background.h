#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "textureManager.h"
#include <vector>

using namespace std;

class background : LTexture
{
public:
    bool init(short int id);

    void free();

    void render();

    void update(float delta);

private:
    position posBackground;
};

#endif