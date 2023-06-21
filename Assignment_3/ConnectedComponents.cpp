#include "ConnectedComponents.h"

int NYMTYR001::ConnectedComponents::next=-1;
//Get pixels method
int NYMTYR001::ConnectedComponents::getPixels()const{
    return numPixels;
}

//Get id method
int NYMTYR001::ConnectedComponents::getId()const{
    
    return compNum;
}

//Get coordinates method
std::vector<std::pair<int,int> > NYMTYR001::ConnectedComponents::getCoordinates()const
{
    return pixelPairs;
}

//Set pixels
void NYMTYR001::ConnectedComponents::setPixels(int pixels){
    numPixels=pixels;
}

//Set id
void NYMTYR001::ConnectedComponents::setId(int id){
    compNum=id;
}

//Set coordinates
void NYMTYR001::ConnectedComponents::setCoordinates(std::pair <int,int> coords){
    pixelPairs.push_back(coords);
    //Increment number of pixels
    ++numPixels;
}

//Big 6 Implementation

//Copy assignment operator
NYMTYR001::ConnectedComponents& NYMTYR001::ConnectedComponents::operator=(const ConnectedComponents& rhs) 
{
    if (this != &rhs) 
    {
        numPixels = rhs.numPixels;
        compNum = rhs.compNum;
        pixelPairs = rhs.pixelPairs;
    }
    return *this;
}

//Destructor
NYMTYR001::ConnectedComponents::~ConnectedComponents()=default;

//Move assignment operator
NYMTYR001::ConnectedComponents& NYMTYR001::ConnectedComponents::operator=(ConnectedComponents&& rhs) {
    if (this != &rhs) {
        numPixels = rhs.numPixels;
        compNum = rhs.compNum;
        pixelPairs = rhs.pixelPairs;
        rhs.numPixels = 0;
        rhs.compNum = 0;
        rhs.pixelPairs.clear();
    }
    return *this;
}

//Move constructor
NYMTYR001::ConnectedComponents::ConnectedComponents(ConnectedComponents &&connCompMovConstr)
    : numPixels(connCompMovConstr.numPixels), compNum(connCompMovConstr.compNum), pixelPairs(connCompMovConstr.pixelPairs) {
    connCompMovConstr.numPixels = 0;
    connCompMovConstr.compNum = 0;
    connCompMovConstr.pixelPairs.clear();
}

//Copy constructor
NYMTYR001::ConnectedComponents::ConnectedComponents(const ConnectedComponents& connCompCopyConstr)
    : numPixels(connCompCopyConstr.numPixels), compNum(next++), pixelPairs(connCompCopyConstr.pixelPairs) {}

//Custom constructor
NYMTYR001::ConnectedComponents::ConnectedComponents(std::vector<std::pair<int,int>> pixelPairs, int pixels)
    : numPixels(pixels), compNum(next++), pixelPairs(pixelPairs) {}

//Default constructor
NYMTYR001::ConnectedComponents::ConnectedComponents()
    : numPixels(0), compNum(next++) {}