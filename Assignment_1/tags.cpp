#include "tags.h"

 std::vector<std::string> fileContents;//Vector storing each line in file
 std::vector<NYMTYR001::TagStruct> tagStruct;//Vector storing tagStruct contents

 std::vector<std::string> Alltags;  //Vector storing all tags

void NYMTYR001::readFileAndParse(std::string fileName)

{
std::ifstream file(fileName);//Openning file passed by user
std::string line;

if(file.is_open())//checking if file is open successfully
{
    while(std::getline(file>>std::ws,line))
    {
        fileContents.push_back(line);//Adding lines to contents vector
    }
}
else
{
    std::cout<<"There was an error openning the file..\n";
}

/*
//Check if fileCOntents correctly read
for(int i=0;i<fileContents.size();i++)
{
    std::cout<<fileContents[i]<<"\n";
}*/

file.close(); //Closing file

std::cout<<"File successfully read and parsed.";

}

void NYMTYR001::printTags(void)
{
    
    char opTag='>';// Opening tag character
    char clTag='/';//Closing character tag
    int opTagPos;//Position of opening tag
    int clTagPos;//Positing of closing tag
    int initialN=1;

    

    std::vector<std::string> tags;  //Vector storing final tags
    std::vector<std::string> tagText;//vector storing tagText
    std::vector<int> numPairs; //Vector storing number of pairs

    std::string tagN;
    std::string txt;

    //Getting each string line in the vector and parsing it to determine the Tag and text
        for(int i=0;i<fileContents.size();i++)
        {
            std::string vecLine;//String storing each line in vector
            //std::cout<<i<<" line"<<fileContents[i]<<"\n";
            vecLine=fileContents[i];
            
            opTagPos=vecLine.find(opTag);
            clTagPos=vecLine.find(clTag)-1;

            int dif=clTagPos-opTagPos;

            tagN=vecLine.substr(1,opTagPos-1);
            txt=vecLine.substr(opTagPos+1,dif-1);

            /*Checking if correct output
            std::cout<<"TAG NAME:"<<tagN<<"\n";
            std::cout<<"TAG TEXT:"<<txt<<"\n";
            */

           //Now add tags and text to vector

           /*std::string ln=tagN+","+std::to_string(initialN)+","+txt;

           tags.push_back(ln);*/

            //Inserting first tag
            bool put=true;
           if(tags.size()==0 && tagText.size()==0 && numPairs.size()==0)
           {
            tags.push_back(tagN);
            numPairs.push_back(1);
            tagText.push_back(txt);
           }
           else
           {
            for(int i=0;i<tags.size();i++)
            {
                //If tag Already exists increment counter and append
                if(tagN==tags[i])
                {
                    put=false;
                    numPairs[i]=numPairs[i]+1;
                    tagText[i]=tagText[i]+":"+txt;
                }
            }
            if(put==true)
            {
            tags.push_back(tagN);
            numPairs.push_back(1);
            tagText.push_back(txt);
            }
           }
        }
        //Now get all data in all 3 tags
           for(int i=0;i<tags.size();i++)
           {
            std::string tg=tags[i];
            int nP=numPairs[i];
            std::string tgTxt=tagText[i];
            NYMTYR001::TagStruct tagSt;
            tagSt.tagName=tg;
            tagSt.numPairs=nP;
            tagSt.text=tgTxt;
            //Adding tags to vector Struct
            tagStruct.push_back(tagSt);
            std::string finTag="\"";
            finTag+=tg+"\","+std::to_string(nP)+",\""+tgTxt+"\"";
            Alltags.push_back(finTag);           
           }
        /* for(int i=0;i<Alltags.size();i++)
            {
                std::cout<<Alltags[i]<<"\n";
            }
        */
            //Pringting tags in struct to console
        for(const auto& ty:tagStruct)
        {
            std::cout<<"\""<<ty.tagName<<"\""<<"\n";         
        }
}

void NYMTYR001::writeTagstoFile(void)
    {
        //Creating an ouput stream
        //Creating and openning the file
        std::ofstream outfile("NYMTYR001_output.txt");

        //First need to check if file was openned successfully

        if(outfile.is_open())
        {
            for(int i=0;i<Alltags.size();i++)
            {
                outfile<<Alltags[i]+"\n";
            }

            //closing the file
            outfile.close();

            std::cout<<"Contents successfully written to file..\nCheck file named NYMTYR001_output.txt.\n";
        }

        //Else error creating and opening file
        else{
            std::cout<<"There was an error creating and openning the file...\n";
        }
    }

void NYMTYR001::listTag(std::string tag)
    {
        //LoopiNg through all elements in the vector struct
        bool found=false;
        for(const auto& ty:tagStruct)
        {
            //checking if tag passed exists
            if(tag==ty.tagName)
            {
                found=true; 
                std::cout<<"The associated tag:\""<<tag<<"\" has the following text:\n\n";
                std::cout<<"\""<<ty.text<<"\"";
                break;
            }
        }

        //if not found tell user
        if(found==false)
            {
            
                std::cout<<"The associated tag:\""<<tag<<"\" does not exist in the struct\n";
            }
    }




