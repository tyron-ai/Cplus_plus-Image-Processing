Welcome to my assignment:
The files in this folder are as follows:

Assignment1.pdf- The pdf containing the assignment instructions

makefile-   Use to automate the build and compilation process. To simply compile type "make".
            To run the program type "make run" in which will invoke the "./driver" command.
            
    
tags.h-     This is the header file containing function and variable declarations used out through the program wrapped in my namespace NYMTYR001

tags.cpp-   This file contains the implementation for all the methods as aforementioned in the header file.
            The methods are as follows and their purposes:

            1. void readFileAndParse(std::string fileName); //Method to read in file and parse text.
            2. void printTags(void); //This method prints all tags identified by the program to the console
            3. void writeTagstoFile(void); //This method writes the tags to a file named NYMTYR001_output.txt.
            4. void listTag(std::string tag); //This method lists the data associated with a specific tag given by the user 


tagdriver.cpp-  This file contains the main method which invokes functions from the tags.cpp through a menu driven interface for the user.