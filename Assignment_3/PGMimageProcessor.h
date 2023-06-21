#ifndef _PGMimageProcessor_h
#define _PGMimageProcessor_h

#include "ConnectedComponents.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include <memory>
#include <queue>
#include <utility>


namespace NYMTYR001
{
    
    //need to read in a PGM image and apply a connected component analysis to that image
    class PGMimageProcessor
    {   
        private:
            int height;//Image height
            int width;//Image width
            int maxVal;//Maximum value for pixels
            std::string fileName;//File name
            std::unique_ptr<unsigned char*[]> array; //Unique Pointer storing pointer to pointer for image pixels
            std::vector<std::unique_ptr<ConnectedComponents>> components;

        public:
            //friend ConnectedComponents;
            //Big 6
            PGMimageProcessor(void);//Default no argument constructor
            ~PGMimageProcessor();//Destructor
            PGMimageProcessor (std::string fileName,const int width,const int height, std::unique_ptr<unsigned char*[]> array);//Custom constructor
            PGMimageProcessor(const PGMimageProcessor& pgmImgProcCopyConstr);//Copy constructor
            PGMimageProcessor(PGMimageProcessor &&pgmImgProcMovConstr);//Move constructor
            PGMimageProcessor& operator=(const PGMimageProcessor& rhs);//Copy assignment operator
            PGMimageProcessor& operator=(PGMimageProcessor&& rhs);//Move Assignment Operator 

            void readFile(std::string fileName);//Readfile method

            //Setter Methods
            void setFileName(std::string fileName);//Setting file name
            void setWidth(int w);//set width
            void setHeight(int h);//set height


            //Getter methods
            int getHeight();//get height
            int getWidth();//get width
            std::string getFileName();//get fileName
            int getMaxVal();//get maximum value of pixels
            std::unique_ptr<unsigned char*[]>& getArray();

           std::vector<std::unique_ptr<ConnectedComponents>>& getComp();//return comp in vector

            /* process the input image to extract all the connected components,
            based on the supplied threshold (0...255) and excluding any components
            of less than the minValidSize. The final number of components that
            you store in your container (after discarding undersized one)
            must be returned.
            */
            int extractComponents(unsigned char threshold, int minValidSize);
            
            /* iterate - with an iterator - though your container of connected
            components and filter out (remove) all the components which do not
            obey the size criteria pass as arguments. The number remaining
            after this operation should be returned.
            */
            int filterComponentsBySize(int minSize, int maxSize);
            /* create a new PGM file which contains all current components
            (255=component pixel, 0 otherwise) and write this to outFileName as a
            valid PGM. the return value indicates success of operation
            */
            bool writeComponents(const std::string & outFileName);

            // return number of components
            int getComponentCount(void) const;

            // return number of pixels in largest component
            int getLargestSize(void) const;

            // return number of pixels in smallest component
            int getSmallestSize(void) const;


            /* print the data for a component to std::cout
            see ConnectedComponent class;
            print out to std::cout: component ID, number of pixels
            */
            void printComponentData(const ConnectedComponents & theComponent) const;
    };
}

#endif