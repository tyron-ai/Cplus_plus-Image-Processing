#include "PGMimageProcessor.h"
#include "ConnectedComponents.h"

int main(int argc,char* argv[])
{

    /*
    -s <int> <int> (-s min max) ; set the minimum and maximum valid components size [min default = 3, max = image width*img height i.e. unlimited]

    -t <int> set the threshold for component detection (default=128, limit to [0. . . 255])

    -p print out all the component data (entries do not have to be sorted) as well as the totalcomponent number and the sizes of the smallest and largest components.

    -w <outPGMfile> write out all retained components (as foreground/background pixels)to a new PGM file, <outPGMfile>

    ./extractor myLargeImage.pgm -s 3 5000 -t 5000 -w sample -p

    */
    NYMTYR001::PGMimageProcessor pgm;
    NYMTYR001::ConnectedComponents cc;
  
    std::string fileName,outputFileName;
    int minCompSize=3,maxCompSize,threshold;
    
    //std::cout<<"File name is: "<<fileName<<"\n";
   

    if(argc<10)
    {
        std::cerr<<"Kindly enter correct arguments.\n";
        exit(1);
    }
    else 
    {
        fileName=argv[1];
        minCompSize=std::stoi(argv[3]);
        maxCompSize=std::stoi(argv[4]);
        threshold=std::stoi(argv[6]);
        outputFileName=(argv[8]);

        /*std::cout<<"Filename:"<<fileName<<
                    "\nminComp: "<<minCompSize<<
                    "\nmaxComp: "<<maxCompSize<<
                    "\nthreshold: "<<threshold<<
                    "\noutputFile: "<<outputFileName<<"\n";
        */
       
        //Getting width

        pgm.setFileName(fileName);
        pgm.readFile(fileName);

        int width=pgm.getWidth();
        //std::cout<<"Width:"<<width<<"\n";
        //Getting height
        int height=pgm.getHeight();
        //std::cout<<"height:"<<height<<"\n";

        int size=height*width;
        //std::cout<<"size:"<<size<<"\n";

        //Setting min component size to default 3 if less than 3 and not greater than max
        if(minCompSize<3||minCompSize>size)
        {
            minCompSize=3;
        }

        //Setting maxComp size to size of image if outside rage
        if(maxCompSize>size|| maxCompSize<0)
        {
            maxCompSize=size;
        }

        //Setting threshold to default if outside recommended values
        if(threshold<0 || threshold>255)
        {
            threshold=128; //setting threshold to default value in case incorrect
        }
        
        pgm.extractComponents(threshold,minCompSize);
        pgm.filterComponentsBySize(minCompSize,maxCompSize);

        pgm.writeComponents(outputFileName);

        //std::cout<<argv[9]<<"\n";
        //Pringting component data

        for(int i=0;i<pgm.getComponentCount();i++)
        {
            cc.setId(i);
            pgm.printComponentData(cc);
        }
        
        std::cout<<"Total component number:"<<pgm.getComponentCount()<<"\n";
        std::cout<<"Largest component size:"<<pgm.getLargestSize()<<"\n";
        std::cout<<"Smallest component size:"<<pgm.getSmallestSize()<<"\n";
    
    }
}