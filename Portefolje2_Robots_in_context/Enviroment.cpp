#include "Enviroment.h"



Enviroment::Enviroment(Image* img)
{
	inputMap = img;
	brushfireMap = img->copyFlip(false,false);
	waveNodeMap = img->copyFlip(false, false);
}

void Enviroment::brushFireError()
{
    bool changedPixel = false;
    do
    {
        changedPixel = false;
        for (int i = 0; i < brushfireMap->getWidth(); i++)
        {
            for (int j = 0; j < brushfireMap->getHeight(); j++)
            {
                if (brushfireMap->getPixelValuei(i, j, 0) != 0)
                {
                    //check neighbors if different from 255
                    if (differentNeighbors(i, j))
                    {
                        //Set value smallest neighbor + 1
                        int value = smallestNeighbor(i, j) + 1;
                        brushfireMap->setPixel8U(i, j, value);

                        changedPixel = true;
                    }
                }
            }
        }

    } while (changedPixel);
}

void Enviroment::brushFire()
{
    list<pixel> neighbors;

    for (int i = 0; i < brushfireMap->getWidth(); i++)
    {
        for (int j = 0; j < brushfireMap->getHeight(); j++)
        {
            int pixelValue = brushfireMap->getPixelValuei(i, j, 0);
            if (pixelValue == 0)
            {

                for (auto item : getAllNeighbors(i, j))
                {
                    if (brushfireMap->getPixelValuei(item.x, item.y, 0) == 255)
                    {
                        neighbors.push_back(item);
                    }
                }
            }
        }
    }

    // Run though neighbors
    while (neighbors.size() != 0)
    {
        //pop first
        pixel item = neighbors.front();
        neighbors.pop_front();
        
        int value = smallestNeighbor(item.x, item.y)+1;
        brushfireMap->setPixel8U(item.x, item.y, value);

        //New neighbors
        list<pixel> allNeighbors = getAllNeighbors(item.x, item.y);

        for (auto neigh : allNeighbors)
        {
            if (brushfireMap->getPixelValuei(neigh.x, neigh.y, 0) == 255)
            {                
                //If element already is in queue don't add it again.
                auto it = find_if(begin(neighbors), end(neighbors), 
                    [neigh](const pixel & m) -> bool { return m.x == neigh.x && m.y == neigh.y; });
                
                if (it == end(neighbors))
                    neighbors.push_back(neigh);
            }
        }
    }
}

list<pixel> Enviroment::wavesMeet()
{
    list<pixel> wavesMeet;

    for (int i = 0; i < brushfireMap->getWidth(); i++)
    {
        for (int j = 0; j < brushfireMap->getHeight(); j++)
        {
            //check for bigger neighbours
            int val = brushfireMap->getPixelValuei(i, j, 0);
            
            if (val != 0 && !hasLargerNeighbor(i, j, val))
            {
                pixel point(i, j);
                wavesMeet.push_back(point);
            }
        }
    }

    cout << "waves points: " << wavesMeet.size() << endl;

    for (auto p : wavesMeet)
    {
        //brushfireMap->setPixel8U(p.x, p.y, 255);
        waveNodeMap->setPixel8U(p.x, p.y, 100);
    }

    return wavesMeet;
}

bool Enviroment::hasLargerNeighbor(int x, int y, int val)
{
    for (int i = x - 1; i <= x + 1; i++)
    {
        if ((i >= 0 && i < brushfireMap->getWidth()))
        {
            if (brushfireMap->getPixelValuei(i, y, 0) > val)
                return true;
        }
    }

    for (int j = y - 1; j <= y + 1; j++)
    {
        if (j >= 0 && j < brushfireMap->getHeight())
        {
            if (brushfireMap->getPixelValuei(x, j, 0) > val)
                return true;
        }
    }
    
    return false;
}

bool Enviroment::hasLargerNeighbor8(int x, int y, int val)
{
    for (int i = (x - 1); i <= (x + 1); i++)
    {
        for (int j = (y - 1); j <= (y + 1); j++)
        {
            //check for outof bounds
            if ((i >= 0 && i < brushfireMap->getWidth()) && (j >= 0 && j < brushfireMap->getHeight()))
            {
                if (brushfireMap->getPixelValuei(i, j, 0) > val)
                    return true;
            }
        }
    }

    return false;
}

bool Enviroment::comparePixels(pixel a, pixel b)
{
    if (a.x == b.x && a.y == b.y)
        return true;
    else
        return false;
}

list<pixel> Enviroment::getAllNeighbors(int orgX, int orgY)
{
    list<pixel> neighbors;
    for (int i = (orgX - 1); i <= (orgX + 1); i++)
    {
        for (int j = (orgY - 1); j <= (orgY + 1); j++)
        {
            //check for outof bounds
            if ((i >= 0 && i < brushfireMap->getWidth()) && (j >= 0 && j < brushfireMap->getHeight()))
            {
                pixel point(i,j);             

                neighbors.push_back(point);
            }
        }
    }
    return neighbors;
}

bool Enviroment::whiteLeft()
{
    for (int i = 0; i < brushfireMap->getWidth(); i++)
    {
        for (int j = 0; j < brushfireMap->getHeight(); j++)
        {
            if (brushfireMap->getPixelValuei(i, j, 0) == 255)
            {
                return true;
            }
        }
    }   
    return false;
}

bool Enviroment::differentNeighbors(int x, int y)
{
    for (int i = (x - 1); i <= (x + 1); i++)
    {
        for (int j = (y - 1); j <= (y + 1); j++)
        {
            if (brushfireMap->getPixelValuei(i, j, 0) != 255)
                return true;
        }
    }
    return false;
}

int Enviroment::smallestNeighbor(int x, int y)
{
    int smallest = -1;
    for (int i = (x - 1); i <= (x + 1); i++)
    {
        for (int j = y - 1; j <= (y + 1); j++)
        {
            int posValue = brushfireMap->getPixelValuei(i, j, 0);

            if (smallest == -1 || posValue < smallest)
                smallest = posValue;
        }
    }

    return smallest;
}

void Enviroment::print()
{
    for (int i = 0; i < brushfireMap->getHeight(); i++)
    {
        for (int j = 0; j < brushfireMap->getWidth(); j++)
        {
            int posValue = brushfireMap->getPixelValuei(j, i, 0);
            if (posValue < 10)
                cout << "0" << posValue << ",";
            else
                cout << posValue << ",";
        }
        cout << endl;
    }
}

void Enviroment::saveInternMaps()
{
    //Saves wavesMap and other saved maps to their output files. 
	brushfireMap->saveAsPGM("brushFireMap.pgm");
    waveNodeMap->saveAsPGM("waveNodeMap.pgm");
    inputMap->saveAsPGM("inputImage.pgm");
}

Enviroment::~Enviroment()
{
    //Clean up
    delete inputMap;
    delete waveNodeMap;
	delete brushfireMap;
}
