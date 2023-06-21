#include "frames.h"

//Setting frame height
void NYMTYR001::FrameSequence::setFrameHeight(int fH)
{
    frameHeight=fH;
}

//Setting frame width
void NYMTYR001::FrameSequence::setFrameWidth(int fW)
{
    frameWidth=fW;
}

//No argument default constructor
NYMTYR001::FrameSequence::FrameSequence(void)
{   
    this->height=height;
    this->width=width;
    this->maxVal=maxVal;
    this->array=array;
    this->imageSequence=imageSequence;
    this->frameHeight=frameHeight;
    this->frameWidth=frameWidth;
}

//Class Destructor
NYMTYR001::FrameSequence::~FrameSequence()
{
    //Deallocating array memory
	for(int i=0;i<height;i++)
	{
		delete[] array[i];
	}
	delete [] array;
    //deleteArray(array);

    //Deleting allocated memory in the Image Sequence Vector for each 2D array frame
    for(int j=0;j<imageSequence.size();j++)
    {
        for(int i=0;i<frameHeight;i++)
        {
            delete[] imageSequence[j][i];
        }
        delete[] imageSequence[j];
    }
    imageSequence.clear();
}

//Method to read in file and store pixel data in 2D unsigned char ** array
void NYMTYR001::FrameSequence::readFile(std::string fileName)
{
    std::vector<std::string> fileContent; //this vector is to store comments and file format

    std::string fileFormat=""; //String storing file format

    std::string comments="";//String storing comments

    std::vector<int> dimensions;//vector storing height and width

    //Reading in file in binary mode
    std::ifstream file(fileName,std::ios::binary);

    //Checking if no error associaated with file
    if(!file || (!file.is_open()))
    {
        std::cout<<"There was an error with this file:"<<fileName<<"\n";
        //Exit program
        exit(1);
    }

    //Getline with file format
    std::getline(file>>std::ws,fileFormat);
   // std::cout<<"File format: "<<fileFormat<<"\n";

    //Checking if comments exist
    do
    {
        std::getline(file>>std::ws,comments);
        if(comments[0]=='#')
        {
            //It is a comment
            fileContent.push_back(comments);
        }
        else{
            break;
        }
    }while(true);

    //Getting width and height
    // Tokenizing string
    std::stringstream strS(comments);
    std::string strToken;

    while(std::getline(strS,strToken,' '))
    {
        dimensions.push_back(std::stoi(strToken));
        strToken="";
    }

     width=dimensions[0];
     height=dimensions[1];
    
    

  /*/ int index=comments.find(' ');
   fr.width=std::stoi(comments.substr(0,index));
   fr.height=std::stoi(comments.substr(index+1,comments.length()));
   */
   
    //std::cout<<"Width: "<<width<<"\n";
    //std::cout<<"Height: "<<height<<"\n";
    std::string maxValue;
    std::getline(file>>std::ws,maxValue);
    maxVal=std::stoi(maxValue);
    //std::cout<<"Max Value: "<<maxVal<<"\n";

   //Creating and allocating memory for the array
	array=new unsigned char*[height];
	for(int i=0;i<height;i++)
	{
		array[i]=new unsigned char[width];
	}

    int pixError=0;//Value keeping track of all pixels with errors
    std::string pixelLines;
    std::vector<unsigned char> vecP;//Vector storing pixels
    //Storing pixels in 2D array
	for(int i=0;i<height;i++)
	{
		// std::getline(file,pixelLines);
		// std::stringstream ss(pixelLines);
		for(int j=0;j<width;j++)
		{
            unsigned char p;
            file.read((char*)&p,1);
			array[i][j]=p;
            vecP.push_back(p);

            //Checking if pixel values within range
            if(static_cast<int>((array[i][j]))>maxVal && static_cast<int>((array[i][j]))<0 )
            {
                pixError++;
            }
		}
    }

    // Print out the values for the array
   /* for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout <<static_cast<int>((array[i][j])) << " ";
        }
        std::cout << '\n';
    }*/

    //Check if file format is correct and pixel values below maximum value
    if(fileFormat!="P5"|| pixError>0)
    {
        std::cout<<"This is not a valid PGM file.\n";
        exit(1);
    } 

    //Check if all values were read
    if(vecP.size()!=height*width)
    {
        std::cout<<"Not all pixels from the file were read.\n";
    }
    else{
        std::cout<<"All pixels were read successfully.\n";
        std::cout<<"Image file read successfully..\n";
    }
    
}

//Method to deAllocate memory for dynamic memory
void NYMTYR001::FrameSequence::deleteArray(unsigned char ** array)

{
    //Deallocating array memory
	for(int i=0;i<height;i++)
	{
		delete[] array[i];
	}
	delete [] array;
}

//Method extracting frames from 2D array
void NYMTYR001::FrameSequence::extractFrames( int x1,int y1,int x2,int y2,int frameWidth,int frameHeight)
{
    //Check if frame dimensions are within large image dimensions
    int frameDimension= frameHeight*frameWidth;
    int imageDimension=width*height;

    if(frameDimension>imageDimension)//Error as it is out of scope
    {
        std::cout<<"The frame dimensions surpass that of the image itself.\n";
        exit(1);
    }
    //Calculating the distance between the two frames 
    int xx1,yy1,xx2,yy2;
    xx1=x1+(frameWidth/2);
    //std::cout<<xx1<<"\n";
    yy1=y1+(frameHeight/2);
    //std::cout<<yy1<<"\n";
    xx2=x2+(frameWidth/2);
    //std::cout<<xx2<<"\n";
    yy2=y2+(frameHeight/2);
    //std::cout<<yy2<<"\n";
    int difX=xx2-xx1;
    //std::cout<<difX<<"\n";
    int dify=yy2-yy1;
    //std::cout<<dify<<"\n";
    double nf=sqrt(pow(difX,2)+pow(dify,2));
    //Distance
    int numFrames=static_cast<int>(nf);
    int xD=x2-x1;
    // std::cout<<xD<<"xd\n";
    int yD=y2-y1;
    //std::cout<<yD<<"yd\n";
    //std::cout<<"Number of frames: "<<nf<<"\n";

    //Calculating y and x step per frame
    float yStep=(float)numFrames/(float)yD;
    //std::cout<<yStep<<"\n";
    float xStep=(float)numFrames/(float)xD;
    //std::cout<<xStep<<"\n";
    
    //Lets account for different cases
    //Moving diagnal with both x and y increasing
    if(x2>x1 && y2>y1){
        for(float x=x1, y=y1; x<x2 &&  y<y2; x+=xStep, y+=yStep )
        {
            int w=round(x);
            int h=round(y);

            //Initialize 2D array storing frame pixels dynamically
            unsigned char ** frameArray;
            frameArray=new unsigned char*[frameHeight];
            for(int i=0;i<frameHeight;i++)
            {
                frameArray[i]=new unsigned char[frameWidth];
                for(int j=0;j<frameWidth;j++)
                {
                    int ax=w+j;//Increasing width
                    int ay=h+i;//Increasing height

                    if(ax>=0 && ay>=0 && ax<width && ay<height)
                    {
                        frameArray[i][j]=array[ay][ax];
                    }
                } 
            }       
            imageSequence.push_back(frameArray);
        }
    }
  
    //Reverse diagnol with both x and y decreasing
    else if(x1>x2 && y1>y2)
    {
        //Calculating y and x step per frame
        float yStep=(float)numFrames/(float)(yD*-1);
        //std::cout<<yStep<<"\n";
        float xStep=(float)numFrames/(float)(xD*-1);
        //std::cout<<xStep<<"\n";
        
        for(float x=x1, y=y1; x>x2 &&  y>y2; x-=xStep, y-=yStep )
        {
            int w=round(x);
            int h=round(y);

            // Initialize 2D array storing frame pixels dynamically
            unsigned char ** frameArray;
            frameArray=new unsigned char*[frameHeight];
            for(int i=0;i<frameHeight;i++)
            {
                frameArray[i]=new unsigned char[frameWidth];
                for(int j=0;j<frameWidth;j++)
                {
                    int ax=w+j;//Adjusting width
                    int ay=h+i;//Adjusting height
                    if(ax>=0 && ay>=0 && ax<width && ay<height)
                    {
                        frameArray[i][j]=array[ay][ax];
                    }
                }
            }    
            imageSequence.push_back(frameArray);
        }
    }
    
    //Horizontal movement only x changing
    else if(x2>x1 && y1==y2)
    {
        for(float x=x1, y=y1;  x<x2  ; x+=xStep )
        {
            int w=round(x);
            int h=round(y);

            // Initialize 2D array storing frame pixels dynamically
            unsigned char ** frameArray;
            frameArray=new unsigned char*[frameHeight];
            for(int i=0;i<frameHeight;i++)
            {
                frameArray[i]=new unsigned char[frameWidth];
                for(int j=0;j<frameWidth;j++)
                {
                    int ax=w+j;//Increasing width
                    int ay=h;
                    if(ax>=0 && h>=0  && ax<width && ay<height)
                    {
                        frameArray[i][j]=array[h][ax];
                    }
                }
            }    
            imageSequence.push_back(frameArray);
         }

    }

    //Reverse horizontal movement with x only changing but decreasing
    else if(x2<x1 && y1==y2)
    {
        for(float x=x1, y=y1;  x<x2  ; x-=xStep )
        {
            int w=round(x);
            int h=round(y);

            // Initialize 2D array storing frame pixels dynamically
            unsigned char ** frameArray;
            frameArray=new unsigned char*[frameHeight];
            for(int i=0;i<frameHeight;i++)
            {
                frameArray[i]=new unsigned char[frameWidth];
                for(int j=0;j<frameWidth;j++)
                {
                    int ax=w-j;//Decreasing width
                    int ay=h;
                    if(ax>=0 && h>=0  && ax<width && ay<height)
                    {
                        frameArray[i][j]=array[h][ax];
                    }
                }
            }    
            imageSequence.push_back(frameArray);
         }

    }
    
    //Case where only y is changing in +ve direction that is going down
    else if(y2>y1 && x1==x2)
    {
        for(float x=x1, y=y1;  y2>y  ; y+=yStep )
        {
            int w=round(x);
            int h=round(y);

            // Initialize 2D array storing frame pixels dynamically
            unsigned char ** frameArray;
            frameArray=new unsigned char*[frameHeight];
            for(int i=0;i<frameHeight;i++)
            {
                frameArray[i]=new unsigned char[frameWidth];
                for(int j=0;j<frameWidth;j++)
                {
                    int ay=h+i;//Increasing width
                    int ax=w;

                    if(ay>=0 && w>=0 && ax<width && ay<height)
                    {
                        frameArray[i][j]=array[ay][w];
                    }
                }
            }    
            imageSequence.push_back(frameArray);
         }

    }
    
    //Case where only y is changing in -ve direction that is going up
    else if(y1>y2 && x1==x2)
    {
        for(float x=x1, y=y1;  y>y2   ;   y-=yStep )
        {
            int w=round(x);
            int h=round(y);
            //Initialize 2D array storing frame pixels dynamically
            unsigned char ** frameArray;
            frameArray=new unsigned char*[frameHeight];
            for(int i=0;i<frameHeight;i++)
            {
                frameArray[i]=new unsigned char[frameWidth];
                for(int j=0;j<frameWidth;j++)
                {
                    int ay=h-i;//Decreasing y
                    int ax=w;
                    if(w>=0 && ay>=0  && ax<width && ay<height)
                    {
                        frameArray[i][j]=array[ay][w];
                    }
                }
            }    
            imageSequence.push_back(frameArray);
        }
    }

   /*for(int i=0;i<imageSequence.size();i++)
    {
    for(int j=0;j<frameHeight;j++)
        {
            for(int k=0;k<frameWidth;k++)
            {
                std::cout<<static_cast<int>(imageSequence[i][j][k]);
            }
        }
    }*/
    //DeAllocating object memory --Can't do this because need to later use the frames
    //deleteArray(array);    
}

//Method to write pgms to individual file 
void NYMTYR001::FrameSequence::writePGMstoFile(std::string fileName1, std::string operation,int frameHeight,int frameWidth)
{
    //Both inverting and reversing
    if(operation=="reinvert")
    {
        for(int i=imageSequence.size();i>0;i--)
        {
            unsigned char** chPtrptr=imageSequence[i];

            //checking if memory request for 2D frame succeeds
            if(chPtrptr!=nullptr)
            {
                std::string fileName=fileName1;
                //Creating output file name
                if(i<10){
                fileName=fileName+"-000"+std::to_string(i)+".pgm";}
                else if(i>9 && i<100){
                fileName=fileName+"-00"+std::to_string(i)+".pgm";}
                else if(i>99 && i<1000){
                fileName=fileName+"-0"+std::to_string(i)+".pgm";}
                else if(i>999 && i<9999){
                fileName=fileName+"-"+std::to_string(i)+".pgm";}

                std::ofstream outPutFile(fileName);
                if(outPutFile.is_open())
                {
                    //outPutFile <<"Author: Nyambe Tyron NYMTYR001\n";
                    outPutFile <<"P5\n"; 
                    outPutFile <<frameWidth << " " << frameHeight<<"\n"; 
                    outPutFile <<maxVal<<"\n";
                    
                }
                outPutFile.close();

                //Opening in binary
                outPutFile.open(fileName,std::ios::binary| std::ios::app);
                //Checking if file open
                if(outPutFile.is_open())
                {
                    for(int k=0;k<frameHeight;k++)
                    {
                        for(int j=0;j<frameWidth;j++)
                        {
                            //Inverting
                            unsigned char pixel=255-imageSequence[i][k][j];
                            outPutFile.write(reinterpret_cast<const char *>(&(pixel)),1);
                        }
                    }
                    //Closing file
                    outPutFile.close();
                }
                else //write black pixel value
                {
                    unsigned char pixel = 0;
                    outPutFile.write(reinterpret_cast<const char *>(&(pixel)),1);
                    std::cout<<"Error with frame "<<i<<" in Image Sequence vector.\n";
                }

            }
            
            
        }
    }
    //Start from end of image sequence to beginning
    else if(operation=="reverse")
    {
        for(int i=imageSequence.size();i>0;i--)
        {
            unsigned char** chPtrptr=imageSequence[i];
            //checking if memory request for 2D frame succeeds
            if(chPtrptr!=nullptr)
            {
                std::string fileName=fileName1;
                //Creating output file name
                if(i<10){
                fileName=fileName+"-000"+std::to_string(i)+".pgm";}
                else if(i>9 && i<100){
                fileName=fileName+"-00"+std::to_string(i)+".pgm";}
                else if(i>99 && i<1000){
                fileName=fileName+"-0"+std::to_string(i)+".pgm";}
                else if(i>999 && i<9999){
                fileName=fileName+"-"+std::to_string(i)+".pgm";}

                std::ofstream outPutFile(fileName);
                if(outPutFile.is_open())
                {
                    //outPutFile <<"Author: Nyambe Tyron NYMTYR001\n";
                    outPutFile <<"P5\n"; 
                    outPutFile <<frameWidth << " " << frameHeight<<"\n"; 
                    outPutFile <<maxVal<<"\n";
                    outPutFile.close();
                }
                

                //Opening in binary
                outPutFile.open(fileName,std::ios::binary| std::ios::app);
                //Checking if file open
                if(outPutFile.is_open())
                {
                    for(int k=0;k<frameHeight;k++)
                    {
                        for(int j=0;j<frameWidth;j++)
                        {
                            outPutFile.write(reinterpret_cast<const char *>(&imageSequence[i][k][j]),1);
                        }
                    }
                    //Closing file
                    outPutFile.close();
                }
                else //write black pixel value
                {
                    unsigned char pixel = 0;
                    outPutFile.write(reinterpret_cast<const char *>(&(pixel)),1);
                    std::cout<<"Error with frame "<<i<<" in Image Sequence vector.\n";
                }
            }      
        }
    }
    //Loop for each frame in imageSequence vector
    else
    {   
        if(operation=="none")
        {
            for(int i=0;i<imageSequence.size();i++)
            {
                unsigned char** chPtrptr=imageSequence[i];
                //checking if memory request for 2D frame succeeds
                if(chPtrptr!=nullptr)
                {
                    std::string fileName=fileName1;
                    //Creating output file name
                    if(i<10)
                    {fileName=fileName+"-000"+std::to_string(i)+".pgm";}
                    else if(i>9 && i<100){fileName=fileName+"-00"+std::to_string(i)+".pgm";}
                    else if(i>99 && i<1000){fileName=fileName+"-0"+std::to_string(i)+".pgm";}
                    else if(i>999 && i<9999){fileName=fileName+"-"+std::to_string(i)+".pgm";}
                    
                    std::ofstream outPutFile(fileName);
                    if(outPutFile.is_open())
                    {
                        //outPutFile <<"Author: Nyambe Tyron NYMTYR001\n";
                        outPutFile <<"P5\n"; 
                        outPutFile <<frameWidth << " " << frameHeight<<"\n"; 
                        outPutFile <<maxVal<<"\n";
                        outPutFile.close();
                    }  
                    //Opening in binary
                    outPutFile.open(fileName,std::ios::binary| std::ios::app);
                    //Checking if file open
                    if(outPutFile.is_open())
                    {
                        for(int k=0;k<frameHeight;k++)
                        {
                            for(int j=0;j<frameWidth;j++)
                            {
                                outPutFile.write(reinterpret_cast<const char *>(&imageSequence[i][k][j]),1);
                            }
                        }
                        //Closing file
                        outPutFile.close();
                    }
                    else //write black pixel value
                    {
                    unsigned char pixel = 0;
                    outPutFile.write(reinterpret_cast<const char *>(&(pixel)),1);
                    std::cout<<"Error with frame "<<i<<" in Image Sequence vector.\n";
                    }
                }
            }
        }    
        else if(operation=="invert")
            {
                for(int i=0;i<imageSequence.size();i++)
                {
                    unsigned char** chPtrptr=imageSequence[i];
                    //checking if memory request for 2D frame succeeds
                    if(chPtrptr!=nullptr)
                    {
                        std::string fileName=fileName1;
                        //Creating output file name
                        if(i<10)
                        {fileName=fileName+"-000"+std::to_string(i)+".pgm";}
                        else if(i>9 && i<100){fileName=fileName+"-00"+std::to_string(i)+".pgm";}
                        else if(i>99 && i<1000){fileName=fileName+"-0"+std::to_string(i)+".pgm";}
                        else if(i>999 && i<9999){fileName=fileName+"-"+std::to_string(i)+".pgm";}
                        
                        std::ofstream outPutFile(fileName);
                        if(outPutFile.is_open())
                        {
                            //outPutFile <<"Author: Nyambe Tyron NYMTYR001\n";
                            outPutFile <<"P5\n"; 
                            outPutFile <<frameWidth << " " << frameHeight<<"\n"; 
                            outPutFile <<maxVal<<"\n";
                            outPutFile.close();
                        }
                        //Opening in binary
                        outPutFile.open(fileName,std::ios::binary| std::ios::app);
                        //Checking if file open
                        if(outPutFile.is_open())
                        {
                            for(int k=0;k<frameHeight;k++)
                            {
                                for(int j=0;j<frameWidth;j++)
                                {
                                    unsigned char pixel=255-imageSequence[i][k][j];
                                    outPutFile.write(reinterpret_cast<const char *>(&(pixel)),1);
                                }
                            }
                            //Closing file
                            outPutFile.close();
                        }
                            else //write black pixel value
                        {
                            unsigned char pixel = 0;
                            outPutFile.write(reinterpret_cast<const char *>(&(pixel)),1);
                            std::cout<<"Error with frame "<<i<<" in Image Sequence vector.\n";
                        }
                    }     

                    }
                }
            }        
       }   

//Method to get imageSequence vector size and desired image pixel
 void NYMTYR001::FrameSequence::getVectorSize()
 {
    std::cout<<imageSequence.size()<<"\n";
    std::cout<<static_cast<int>(imageSequence[0][3][4]);
 }