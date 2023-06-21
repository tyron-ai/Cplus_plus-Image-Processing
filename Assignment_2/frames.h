#ifndef _frames_h
#define _frames_h

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>

namespace NYMTYR001{
    //Class Frame Sequence storing each extracted frame
    class FrameSequence
    {
        private:
            int height;//Image height
            int width;//Image width
            int maxVal;//Maximum value for pixels
            int frameHeight;//Height of frame
            int frameWidth;//Width of frame
            unsigned char ** array; //Array storing pointer to pointer for image pixels
            std::vector<unsigned char **> imageSequence; //store each extracted frame image where each element of the vector stores a pointer to a dynamically allocated 2D image frame
        
        public:
            void extractFrames( int x1,int y1,int x2,int y2,int frameWidth,int frameHeight);//Function to extract frames
            void deleteArray(unsigned char ** array);//Deallocating mmeory allocated
            void readFile(std::string fileName);// Method to read in file.
            FrameSequence(void);//No argument class sonstructor
            ~FrameSequence();//Class destructor
            void getVectorSize();//Get size of vectors
            // void invert(); //Method where each pixel value v become 255-v
            //void reverse(); //Method to reverse output (write frames out from last to first)
            //void reinvert(); //Method to reverse and invert output
            void writePGMstoFile(std::string outFile,std::string operation,int frameHeight,int frameWidth);//This method writes the PGM frames to a file
            void setFrameHeight(int fH);//Method to set frame height
            void setFrameWidth(int fW); //method to set framewidth 
    };
}
#endif