#include <iostream>
#include "Image.hpp"
#include "PPMLoader.hpp"
#include <vector>
#include <cmath>
#include "Enviroment.h"
#include <math.h>



using namespace rw::sensor;
using namespace rw::loaders;


int main(int argc) { 
    std::string filename("testout.pgm");
    std::cout << "loading image..." << std::endl;
    Image* img = PPMLoader::load(filename);

    // do stuff here
	int channel = 0; // allways 0 on grayscale image

    std::cout << "Image loaded" << std::endl;

    Enviroment env(img);

    std::cout << "Running Brushfire..." << std::endl;

    //env.brushFire();
    //env.print();

    list<pixel> wavesMeet = env.wavesMeet();

    std::cout << std::endl << "saving image..." << std::endl;
    // save image
    img->saveAsPGM("testout2.pgm");
        
    // cleanup
    delete img;

    system("pause");
}
