#define CATCH_CONFIG_MAIN // This tells catch to provide a main() function.

#include "catch.hpp"
#include "ConnectedComponents.h"
#include "PGMimageProcessor.h"

namespace NYMTYR001
{
   //Test Cases

    //Testing writeComponents method
    TEST_CASE ("Write Components to file Test")
   {
        PGMimageProcessor pg1 , pg2, pg3 ,pg4;

        ///Calling readfile methods
        pg1.readFile("chess.pgm");
        pg2.readFile("chess.pgm");
        pg3.readFile("chess.pgm");
        pg4.readFile("chess.pgm");

        //Calling extract components methods
        pg1.extractComponents(100,7000);
        pg2.extractComponents(80,3000);
        pg3.extractComponents(160,8000);
        pg4.extractComponents(150,1000);

        //Checking if requirements met
        REQUIRE(pg1.writeComponents("test1.pgm") == true);
        REQUIRE(pg2.writeComponents("test2.pgm") == true);
        REQUIRE(pg3.writeComponents("test3.pgm")== true);
        REQUIRE(pg4.writeComponents("test4.pgm")== true);
    } 

    TEST_CASE("Extract Components")
    {
        PGMimageProcessor pg1 , pg2;

        pg1.readFile("chess.pgm");
        pg2.readFile("chess.pgm");

        REQUIRE(pg1.extractComponents(170,500) == 6);
        REQUIRE(pg2.extractComponents(20,300) == 1);
      
    }

    TEST_CASE("Set file name")
    {
        PGMimageProcessor pg1 , pg2;

        pg1.setFileName("chess.pgm");
        pg2.setFileName("chess-thresh.pgm");

        REQUIRE(pg1.getFileName() == "chess.pgm");
        REQUIRE(pg2.getFileName() == "chess-thresh.pgm");
      
    }

    TEST_CASE("Set width")
    {
        PGMimageProcessor pg1 , pg2;

        pg1.setWidth(50);
        pg2.setWidth(1000);

        REQUIRE(pg1.getWidth() == 50);
        REQUIRE(pg2.getWidth() == 1000);
      
    }

    TEST_CASE("Set Height")
    {
        PGMimageProcessor pg1 , pg2;

        pg1.setHeight(20);
        pg2.setHeight(2000);

        REQUIRE(pg1.getHeight() == 20);
        REQUIRE(pg2.getHeight() == 2000);
      
    }


    TEST_CASE("Get file name")
    {
        PGMimageProcessor pg1 , pg2;

        pg1.setFileName("chess.pgm");
        pg2.setFileName("chess-thresh-separate.pgm");

        REQUIRE(pg1.getFileName() == "chess.pgm");
        REQUIRE(pg2.getFileName() == "chess-thresh-separate.pgm");
      
    }

    TEST_CASE("Get width")
    {
        PGMimageProcessor pg1 , pg2;

        pg1.setWidth(99);
        pg2.setWidth(100);

        REQUIRE(pg1.getWidth() == 99);
        REQUIRE(pg2.getWidth() == 100);
      
    }

    TEST_CASE("Get Height")
    {
        PGMimageProcessor pg1 , pg2;

        pg1.setHeight(300);
        pg2.setHeight(5000);

        REQUIRE(pg1.getHeight() == 300);
        REQUIRE(pg2.getHeight() == 5000);
      
    }

      TEST_CASE("Get maxVal test")
    {
        PGMimageProcessor pg1 , pg2;

        ///Calling readfile methods
        pg1.readFile("chess.pgm");
        

        REQUIRE(pg1.getMaxVal() == 255);
        REQUIRE(pg2.getMaxVal() == 0);
      
    }

    TEST_CASE("Get smallest component size")
    {
        PGMimageProcessor pg1 , pg2, pg3 ,pg4;

        ///Calling readfile methods
        pg1.readFile("chess.pgm");
        pg2.readFile("chess.pgm");
        pg3.readFile("chess.pgm");
        pg4.readFile("chess.pgm");

        //Calling extract components methods
        pg1.extractComponents(100,7000);
        pg2.extractComponents(80,3000);
        pg3.extractComponents(160,8000);
        pg4.extractComponents(150,1000);

        REQUIRE(pg1.getSmallestSize()==153468);
        REQUIRE(pg2.getSmallestSize()==153468);
        REQUIRE(pg3.getSmallestSize()==116210);
        REQUIRE(pg4.getSmallestSize()==153463);

    }

    TEST_CASE("Get largest component size")
    {
        PGMimageProcessor pg1 , pg2, pg3 ,pg4;

        ///Calling readfile methods
        pg1.readFile("chess.pgm");
        pg2.readFile("chess-thresh.pgm");
        pg3.readFile("chess.pgm");
        pg4.readFile("chess-thresh.pgm");

        //Calling extract components methods
        pg1.extractComponents(100,7000);
        pg2.extractComponents(80,3000);
        pg3.extractComponents(160,8000);
        pg4.extractComponents(150,1000);

        REQUIRE(pg1.getLargestSize()==153468);
        REQUIRE(pg2.getLargestSize()==8028);
        REQUIRE(pg3.getLargestSize()==116210);
        REQUIRE(pg4.getLargestSize()==8028);

    }


    TEST_CASE("Get component count")
    {
        PGMimageProcessor pg1 , pg2, pg3 ,pg4;

        ///Calling readfile methods
        pg1.readFile("chess.pgm");
        pg2.readFile("chess-thresh.pgm");
        pg3.readFile("chess.pgm");
        pg4.readFile("chess-thresh.pgm");

        //Calling extract components methods
        pg1.extractComponents(90,700);
        pg2.extractComponents(80,3000);
        pg3.extractComponents(10,8000);
        pg4.extractComponents(101,1000);

        REQUIRE(pg1.getComponentCount()==1);
        REQUIRE(pg2.getComponentCount()==6);
        REQUIRE(pg3.getComponentCount()==1);
        REQUIRE(pg4.getComponentCount()==6);

    }

    TEST_CASE("Readfile Test")
    {
        PGMimageProcessor pg1 , pg2;

        pg1.readFile("chess.pgm");
        pg2.readFile("chess.pgm");

        REQUIRE(pg1.extractComponents(160,5000) == 1);
        REQUIRE(pg2.extractComponents(59,400) == 1);
      
    }

    TEST_CASE("Filter by size test")
    {
        PGMimageProcessor pg1 , pg2, pg3 ,pg4;

        ///Calling readfile methods
        pg1.readFile("chess.pgm");
        pg2.readFile("chess.pgm");
        pg3.readFile("chess.pgm");
        pg4.readFile("chess.pgm");

        //Calling extract components methods
        pg1.extractComponents(100,7000);
        pg2.extractComponents(80,3000);
        pg3.extractComponents(160,8000);
        pg4.extractComponents(3,5000);

        REQUIRE(pg1.filterComponentsBySize(10,1000)==0);
        REQUIRE(pg2.filterComponentsBySize(3,6000)==0);
        REQUIRE(pg3.filterComponentsBySize(7,4500)==0);
        REQUIRE(pg4.filterComponentsBySize(3,5000)==0);

    }

    TEST_CASE("Get Array Mehtod Test")
    {
        PGMimageProcessor pg1 , pg2, pg3 ,pg4;

        ///Calling readfile methods
        pg1.readFile("chess.pgm");
        pg2.readFile("chess.pgm");
        pg3.readFile("chess.pgm");
        pg4.readFile("chess.pgm");

        //Calling extract components methods
        pg1.extractComponents(160,7000);
        pg2.extractComponents(159,3000);
        pg3.extractComponents(161,8000);
        pg4.extractComponents(100,5000);

        //Checking if arrays are not equal since different
        REQUIRE(pg1.getArray()!=pg2.getArray());
        REQUIRE(pg2.getArray()!=pg4.getArray());
        REQUIRE(pg4.getArray()!=pg3.getArray());
        REQUIRE(pg1.getArray()!=pg3.getArray());
     
    }

    TEST_CASE("Big 6")
    {
        NYMTYR001::PGMimageProcessor pgm;

        SECTION("Default Constructor")
        {
            REQUIRE(pgm.getFileName()=="");
            REQUIRE(pgm.getArray()==nullptr);
            REQUIRE(pgm.getHeight()==0);
            REQUIRE(pgm.getWidth()==0);
            REQUIRE(pgm.getMaxVal()==0);
        }

        SECTION("Destructor")
        {
            REQUIRE(pgm.getFileName()=="");
            REQUIRE(pgm.getArray()==nullptr);
            REQUIRE(pgm.getHeight()==0);
            REQUIRE(pgm.getWidth()==0);
            REQUIRE(pgm.getMaxVal()==0);
        }

        SECTION("Custom Constructor")
        {   
            PGMimageProcessor pgm1("chess.pgm",500,500,nullptr);
            REQUIRE(pgm1.getFileName()=="chess.pgm");
            REQUIRE(pgm1.getHeight()==500);
            REQUIRE(pgm1.getWidth()==500);
            REQUIRE(pgm1.getMaxVal()==0);
        }



        
    }


} // namespace NYMTYR001
