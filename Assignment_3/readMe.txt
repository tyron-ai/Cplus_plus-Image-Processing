The files contained in this folder are as follows:

makefile-   Use to automate the build and compilation process. To simply compile type "make all".
            To run the program type "make run"
            To run the tests type "make test" 

PGMimageProcessor.h-   This is the header file for the PGMimageProcessor class containing function and variable declarations used out through the program wrapped in my namespace NYMTYR001

ConnectedComponents.h-   This is the header file for the ConnectedComponents class containing function and variable declarations used out through the program wrapped in my namespace NYMTYR001


PGMimageProcessor.cpp- This file contains the implementation for all the methods as aforementioned in the header file.
            The methods are as follows and their purposes:
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

ConnectedComponents.cpp- This file contains the implementation for all the methods as aforementioned in the header file.
            The methods and purposes are as follows:
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

testing.cpp- This file contains test cases for my methods in the different classes. It uses the catch.hpp file also located
             in this directory.
 
findcomp.cpp-  This file contains the main method which invokes functions from the PGMimageProcessor.cpp.