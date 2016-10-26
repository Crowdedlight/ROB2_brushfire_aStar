#pragma once
#include "Image.hpp"
#include <iostream>
#include <list>
#include <algorithm>

using namespace rw::sensor;
using namespace std;

struct pixel {
    pixel(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int x;
    int y;
};

class Enviroment
{
public:
    Enviroment(Image * image);

    void brushFire();
    list<pixel> wavesMeet();

    void print();

    void brushFireError();

    void saveInternMaps();


    ~Enviroment();

private:
    Image* map;
    Image* inputMap;
    Image* waveNodeMap;

    list<pixel> getAllNeighbors(int x, int y);
    bool differentNeighbors(int i, int j);
    int smallestNeighbor(int x, int y);
    bool whiteLeft();
    bool comparePixels(pixel a, pixel b);
    bool hasLargerNeighbor(int x, int y, int val);
    bool hasLargerNeighbor8(int x, int y, int val);

};

