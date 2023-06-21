#include "tags.h"


int main(int argc,char* argv[])
{
     std::string fileName;
    /*if(argc>2)
    {
        std::cout<<"Incorrect number of arguments passed.\n";
        exit(0);
    }
    else
    {
        fileName=argv[1];
    }*/
   
    
    char input;
    std::string theTag;
   


    //Menu section
    while(true)
    {
        std::cout<<"\n\n";
        std::cout<<"Kindly enter an option (r,p,d,l) or q to quit and press return\n";
        std::cout<<"1. ‘r’ (read and parse a specified input file) \n";
        std::cout<<"2. ‘p’ (print all tags - this will list all the tags in arbitrary order, to cout)\n";
        std::cout<<"3. ‘d’ (dump/write tags and data to a file called tag.txt – see below)\n";
        std::cout<<"4. ‘l’ (list/print tag data for given tag to cout)\n";
        std::cout<<"5. ‘q’ (quit - terminate the input loop and exit the program)\n";

        std::cin>>input;


        switch(input)
        {
            case 'r':
            std::cout<<"\n\n";
            std::cout<<"Kindly enter file name:\n";
            std::cin>>fileName;//Storing filename 
            NYMTYR001::readFileAndParse(fileName);
            std::cout<<"\n\n";
            break;

            case 'p':
            std::cout<<"The tags are:\n";
            NYMTYR001::printTags();
            std::cout<<"\n\n";
            break;

            case 'd':
            std::cout<<"\n\n";
            NYMTYR001::writeTagstoFile();
            std::cout<<"\n\n";
            break;

            //In this case the user inputs their desired tag choice they would like to view
            case 'l':
            std::cout<<"\n\n";
            std::cout<<"Kindly enter the tag name: \n";
            std::cin>>theTag;
            NYMTYR001::listTag(theTag);
            std::cout<<"\n\n";
            break;

            case 'q':
            std::cout<<"\n\n";
            std::cout<<"Thank you for using the application..\n";
            exit(0);    
            break;

            default:
            std::cout<<"\n\n";
            std::cout<<"You entered an invalid input.. \n";
        }
    }


}