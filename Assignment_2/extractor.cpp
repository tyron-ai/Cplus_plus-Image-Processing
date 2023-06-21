#include "frames.h"
 /*

    ./extractor myLargeImage.pgm -t 0 10 5000 5000 -s 640 480 -w invert invseq -w none sequence2

    //flags -t -s -w

    -t <int> <int> <int> <int> # x1 y1 x2 y2 (begin & end origin pixel coords,for frame trajectory)

    -s <int> <int>             # <width> <height> (size of small frame in pixels)

    -w <string> <string>       # write frames with <operation> <name>

    */

int main(int argc,char* argv[])
{ 
    NYMTYR001::FrameSequence fr; 
   
   //Declaring variables
    std::string fileName;
    int x1,y1,x2,y2,frameWidth,frameHeight;
    std::string operation,fileName1,fileName2,operation2;

    //Reading command line arguments
    if(argc<13)
    {
        std::cerr<<"Kindly enter correct arguments.\n";
        exit(1);
    }
    else if(argc==16)
    {
        fileName=argv[1];
        x1=std::stoi(argv[3]);
        y1=std::stoi(argv[4]);
        x2=std::stoi(argv[5]);
        y2=std::stoi(argv[6]);
        frameWidth=std::stoi(argv[8]);
        frameHeight=std::stoi(argv[9]);
        operation=argv[11];
        fileName1=argv[12];
        operation2=argv[14];
        fileName2=argv[15];
        fr.readFile(fileName);
        
        /*
            Testing if correct arguments
            std::cout<<"Filename:"<<fileName<<
                        "\nbeginning x1: "<<x1<<
                        "\nbeginning y1: "<<y1<<
                        "\nEnding x2: "<<x2<<
                        "\nEnding y2: "<<y2<<
                        "\nFrame width: "<<frameWidth<<
                        "\nFrame height: "<<frameHeight<<
                        "\noperation 1: "<<operation<<
                        "\nFile name 1 :"<<fileName1<<
                        "\noperation 2 :"<<operation2<<
                        "\nFile name 2 :"<<fileName2<<"\n";
        */

        //Setting dimensions
        fr.setFrameHeight(frameHeight);
        fr.setFrameWidth(frameWidth);

        //Extracting frames
        fr.extractFrames(x1,y1,x2,y2,frameWidth,frameHeight);
        //fr.getVectorSize();

        //Writing PGM frames to file
        fr.writePGMstoFile(fileName1,operation,frameHeight,frameWidth);

        //Using FFMPEG to create video
        /*std::string vidCmd="ffmpeg -i "+ fileName1 + "-%04d.pgm -c:v libx264 -pix_fmt yuv420p "+ fileName1 + ".mp4";
        std::system(vidCmd.c_str());*/

        
        fr.writePGMstoFile(fileName2,operation2,frameHeight,frameWidth);
        /*std::string vidCmd="ffmpeg -i "+ fileName2 + "-%04d.pgm -c:v libx264 -pix_fmt yuv420p "+ fileName2 + ".mp4";
        std::system(vidCmd.c_str());*/
    }
    else if(argc==13)
    {
        fileName=argv[1];
        x1=std::stoi(argv[3]);
        y1=std::stoi(argv[4]);
        x2=std::stoi(argv[5]);
        y2=std::stoi(argv[6]);
        frameWidth=std::stoi(argv[8]);
        frameHeight=std::stoi(argv[9]);
        operation=argv[11];
        fileName1=argv[12];
        fr.readFile(fileName);
        
        /*
            Testing if correct arguments
            std::cout<<"Filename:"<<fileName<<
                        "\nbeginning x1: "<<x1<<
                        "\nbeginning y1: "<<y1<<
                        "\nEnding x2: "<<x2<<
                        "\nEnding y2: "<<y2<<
                        "\nFrame width: "<<frameWidth<<
                        "\nFrame height: "<<frameHeight<<
                        "\noperation 1: "<<operation<<
                        "\nFile name 1 :"<<fileName1<<
                        "\noperation 2 :"<<operation2<<
                        "\nFile name 2 :"<<fileName2<<"\n";
        */

        //Setting dimensions
        fr.setFrameHeight(frameHeight);
        fr.setFrameWidth(frameWidth);

        //Extracting frames
        fr.extractFrames(x1,y1,x2,y2,frameWidth,frameHeight);
        //fr.getVectorSize();

        //Writing PGM frames to file
        fr.writePGMstoFile(fileName1,operation,frameHeight,frameWidth);

        //Using FFMPEG to create video
        /*std::string vidCmd="ffmpeg -i "+ fileName1 + "-%04d.pgm -c:v libx264 -pix_fmt yuv420p "+ fileName1 + ".mp4";
        std::system(vidCmd.c_str());*/
    }
    else{std::cout<<"Invalid arguments.\n"; exit(1);}

    //Calling class destructor
    //fr.~FrameSequence();

}