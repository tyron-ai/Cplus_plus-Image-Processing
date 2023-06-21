#include "PGMimageProcessor.h"
//Set fileName method
void NYMTYR001::PGMimageProcessor::setFileName(std::string fN)
{
    fileName=fN;
}

//Set height method
void NYMTYR001::PGMimageProcessor::setHeight(int h)
{
    height=h;
}

//Set width method
void NYMTYR001::PGMimageProcessor::setWidth(int w)
{
    width=w;
}

//Get fileName method
std::string NYMTYR001::PGMimageProcessor::getFileName(){
    return this->fileName;
}

//Get height method
int NYMTYR001::PGMimageProcessor::getHeight()
{
    return height;
}

//Get height method
int NYMTYR001::PGMimageProcessor::getMaxVal()
{
    return maxVal;
}


//Get Width method
int NYMTYR001::PGMimageProcessor::getWidth()
{
    return width;
}

//Get Array Method
std::unique_ptr<unsigned char*[]>& NYMTYR001::PGMimageProcessor::getArray()
{
    return array;
}

//Readfile method
void NYMTYR001::PGMimageProcessor::readFile(std::string fileName)
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
        else
        {
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
	array = std::make_unique<unsigned char*[]>(height);
    for(int i = 0; i < height; i++)
    {
        array[i] = std::make_unique<unsigned char[]>(width).release();
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
    /*for (int i = 0; i < height; i++) {
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

//Extracting the components
int NYMTYR001::PGMimageProcessor::extractComponents(unsigned char threshold, int minValidSize)
{
    //Looping through 2D array
    for(int i=1;i<height-1;i++)
    {
        for (int j=1;j<width-1;j++)
        {
            //Accesing each pixel row by row
            if((array[i][j])>=threshold)
            {
                //It is a component
                std::unique_ptr<ConnectedComponents> comp (new ConnectedComponents());

                //Queue for visited components
                std::queue<std::pair<int,int>> visited;
                visited.push(std::make_pair(i,j));

                //While the queue is not empty do this
                while (!visited.empty()) 
                {
                    // Creating a temporary variable for the pair
                    std::pair<int, int> pix = visited.front();
                    //Adding to component
                    (*comp).setCoordinates(pix);

                    //Setting visited to zero
                    array[pix.first][pix.second] = 0;

                    //Remove from queue
                    visited.pop();

                    // Checking if meeting criteria then add to queue for N E W S
                    //Checking if still within boundaries
                   if (pix.second + 1 < width && array[pix.first][pix.second + 1] >= threshold) 
                    {
                        visited.push(std::make_pair(pix.first, pix.second + 1));
                        //Set to 0 since visited
                        array[pix.first][pix.second + 1] = 0;
                    }

                    //Checking if still within boundaries
                    if (pix.second - 1 >= 0 && array[pix.first][pix.second - 1] >= threshold) 
                    {
                        visited.push(std::make_pair(pix.first, pix.second - 1));
                        //Set to 0 since visited
                        array[pix.first][pix.second - 1] = 0;
                    }

                    //Checking if still within boundaries
                    if (pix.first - 1 >= 0 && array[pix.first - 1][pix.second] >= threshold) 
                    {
                        visited.push(std::make_pair(pix.first - 1, pix.second));
                        //Set to 0 since visited
                        array[pix.first - 1][pix.second] = 0;
                    }

                    //Checking if still within boundaries
                    if (pix.first + 1 < height && array[pix.first + 1][pix.second] >= threshold) 
                    {
                        visited.push(std::make_pair(pix.first + 1, pix.second));
                        //Set to 0 since visited
                        array[pix.first + 1][pix.second] = 0;
                    }
                }

                //Checking if the final Connected component is greater than the minimum valid size then add to the components vector
                if ((*comp).getPixels() > minValidSize) 
                {

                    //Checking if the final Connected component is greater than the minimum valid size then add to the components vector
                    if((*comp).getPixels()>minValidSize)
                    {
                        components.push_back(std::move(comp));
                    }
                    
                }
            }
        }
    }
    //bool visited=false;
    //std::cout<<components.size()<<"\n";
    return components.size();
}

//Filter components
int NYMTYR001::PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize)
{
    //Iterator to loop through the components
    auto i = components.begin();

    // Looping through the components
    while (i != components.end()) 
    {
        // Check if the component size is within the specified range
        if (!((*i)->getPixels() > minSize && (*i)->getPixels() < maxSize)) {
            // If the component size is not within the range, erase it from the vector
            i = components.erase(i);
        }
        else {
            // If the component size is within the range move to the next component
            i++;
        }
    }   

    return components.size();

}

//Write components
bool NYMTYR001::PGMimageProcessor::writeComponents(const std::string & outFileName)
{
   std::vector<unsigned char> vals(height * width, 0);

    for (const auto& component : components) 
    {
        const std::vector<std::pair<int, int>>& comp = component->getCoordinates();

        for (const auto& coord : comp) 
        {
            vals[coord.first * width + coord.second] = 255;
        }
    }

    std::ofstream outFIle(outFileName, std::ios::binary);
    if (!outFIle) 
    {
        std::cout << "Unable to open file:"<<outFileName<<"\n";
        return false;
    }

    outFIle<< "P5" <<"\n";
    outFIle<< "#NYMTYR001 Assignment 3" <<"\n";
    outFIle<< width << " " << height <<"\n";
    outFIle<< 255 <<"\n";
    outFIle.write(reinterpret_cast<const char*>(vals.data()), vals.size());
    outFIle.close();

    return true; 
}

//Return number of components
int NYMTYR001::PGMimageProcessor::getComponentCount(void) const
{
    return components.size();
}

//Return number of pixels in largest component
int NYMTYR001::PGMimageProcessor::getLargestSize(void) const
{
    //Initializing the maximum size to an invalid value
    int largest = -1;

    //Looping through the components
    for (const auto& component : components) {
        //Checking if the component size is greater than the current maximum size
        if (component->getPixels() > largest) {
            //If greater update
            largest = component->getPixels();
        }
    }

    //Returning the maximum size
    return largest;
}

// return number of pixels in smallest component
int NYMTYR001::PGMimageProcessor::getSmallestSize(void) const
{
    // Initializing the minimum size to an invalid value
    int smallest = -1;

    // Loop through the components
    for (const auto& component : components) {
        // Checking if the component size is less than the current minimum size
        if (smallest == -1 || component->getPixels() < smallest) {
            //If smaller update
            smallest = component->getPixels();
        }
    }

    //Returning the smallest
    return smallest;
}

/* print the data for a component to std::cout
see ConnectedComponent class;
print out to std::cout: component ID, number of pixels
*/
void NYMTYR001::PGMimageProcessor::printComponentData(const ConnectedComponents & theComponent) const
{
    
    std::stringstream ss;
    //ss << "Component ID is:" << theComponent.getId() << ", Component pixels are:" << theComponent.getPixels() <<"\n";
    ss << "Component ID:" << theComponent.getId() <<"..done\n";
    std::cout << ss.str();

}

std::vector<std::unique_ptr<NYMTYR001::ConnectedComponents>>& NYMTYR001::PGMimageProcessor::getComp()
{
    return components;
}


//Big 6 implementattion

//Default Constructor
NYMTYR001::PGMimageProcessor::PGMimageProcessor(void) : height(0), width(0), maxVal(0), fileName(""), array(nullptr), components() {}

//Destructor
NYMTYR001::PGMimageProcessor::~PGMimageProcessor()
{
    height = 0;
    width = 0;
    maxVal = 0;
    fileName = "";
    array.reset();
    components.clear();
}

//Custom constructor
NYMTYR001::PGMimageProcessor::PGMimageProcessor(std::string fileName, const int width, const int height, std::unique_ptr<unsigned char*[]> array) : height(height), width(width), fileName(fileName), maxVal(0), array(new unsigned char*[height]), components()
{
    //Creating and allocating memory for the array
	array = std::make_unique<unsigned char*[]>(height);
    for(int i = 0; i < height; i++)
    {
        array[i] = std::make_unique<unsigned char[]>(width).release();
    }
}

//Copy constructor
NYMTYR001::PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor &pgmImgProcCopyConstr) : height(pgmImgProcCopyConstr.height), width(pgmImgProcCopyConstr.width), maxVal(pgmImgProcCopyConstr.maxVal), fileName(pgmImgProcCopyConstr.fileName), array(new unsigned char*[pgmImgProcCopyConstr.height]), components()
{
    // Copy pixel data to array
    for (int i = 0; i < pgmImgProcCopyConstr.height; i++)
    {
        array = std::make_unique<unsigned char*[]>(height);
        for (int j = 0; j < pgmImgProcCopyConstr.width; j++)
        {
            this->array[i][j] = pgmImgProcCopyConstr.array[i][j];
        }
    }

    // Copy components
    for (const auto &comp : pgmImgProcCopyConstr.components)
    {
        components.push_back(std::make_unique<ConnectedComponents>(*comp));
    }
}

//Move constructor
NYMTYR001::PGMimageProcessor::PGMimageProcessor(PGMimageProcessor &&pgmImgProcMovConstr) : height(pgmImgProcMovConstr.height), width(pgmImgProcMovConstr.width), maxVal(pgmImgProcMovConstr.maxVal), fileName(std::move(pgmImgProcMovConstr.fileName)), array(std::move(pgmImgProcMovConstr.array)), components(std::move(pgmImgProcMovConstr.components))
{
    pgmImgProcMovConstr.height = 0;
    pgmImgProcMovConstr.width = 0;
    pgmImgProcMovConstr.maxVal = 0;
}

//Copy assignment operator
NYMTYR001::PGMimageProcessor& NYMTYR001::PGMimageProcessor::operator=(const PGMimageProcessor& rhs)
{
    if (this == &rhs) 
    { // check for self assignment
        return *this;
    }
    height = rhs.height;
    width = rhs.width;
    maxVal = rhs.maxVal;
    fileName = rhs.fileName;

    array = std::make_unique<unsigned char*[]>(height);
    for(int i = 0; i < height; i++)
    {
        array[i] = std::make_unique<unsigned char[]>(width).release();
         for (int j = 0; j < width; j++)
        {
            this->array[i][j] = rhs.array[i][j];
        }
    }
    
    components.clear();
    for (const auto& component : rhs.components) {
        components.push_back(std::make_unique<ConnectedComponents>(*component));
    }
    return *this;
}

//Move Assignment Operator 
NYMTYR001::PGMimageProcessor& NYMTYR001::PGMimageProcessor::operator=(PGMimageProcessor&& rhs)
{
     if (this != &rhs)//Checking self assignment
    {
        height = rhs.height;
        width = rhs.width;
        maxVal = rhs.maxVal;
        fileName = std::move(rhs.fileName);
        array = std::move(rhs.array);
        components = std::move(rhs.components);
    }
    return *this;
}