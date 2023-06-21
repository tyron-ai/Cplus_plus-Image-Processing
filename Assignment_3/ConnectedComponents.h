#ifndef _ConnectedComponents_h
#define _ConnectedComponents_h

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>

namespace NYMTYR001{
    
    class ConnectedComponents
    {   
        private:
            int numPixels; //Number of pixels in a component
            int compNum; //Integer identifier for a component
            std::vector< std::pair<int,int>> pixelPairs;; //Pixels in component
            static int next;
        public:
            //Big 6
            ConnectedComponents();//Default constructor
            ConnectedComponents(std::vector<std::pair<int,int>> pixelPairs,int pixels);//Custom constructor
            ConnectedComponents(const ConnectedComponents& connCompCopyConstr);//Copy constructor
            ConnectedComponents(ConnectedComponents &&connCompMovConstr);//Move constructor
            ConnectedComponents& operator=(const ConnectedComponents& rhs);//Copy assignment operator
            ConnectedComponents& operator=(ConnectedComponents&& rhs);//Move Assignment Operator 
            ~ConnectedComponents();//Class destructor

            //Getters
            int getPixels() const;//Get pixels
            int getId() const;//Get comp ID
            std::vector<std::pair<int,int> > getCoordinates() const;//Get coordinates

            //Setters
            void setPixels(int pixels);//Set pixel values
            void setId(int id);//Set ID
            void setCoordinates(std::pair <int,int> coords);//Set coordinates
        
    };
    extern int next;
}
#endif