#ifndef _tags_h
#define _tags_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>


namespace NYMTYR001
{
    struct TagStruct
    {
        std::string tagName;
        int numPairs;
        std::string text;
    };

    void readFileAndParse(std::string fileName); //Method to read in file

   // void readAndParse(std::vector<std::string>); //Method to read and parse tags
   
    void printTags(void); //This method prints all tags identified by the program to the console

    void writeTagstoFile(void); //This method writes the tags to a file named NYMTYR001_output.txt.

    void listTag(std::string tag); //This method lists the data associated with a specific tag given by the user

}

#endif