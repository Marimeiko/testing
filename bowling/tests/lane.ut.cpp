#include "catch.hpp"

#include "lane.hpp"

#include <string>

SCENARIO("Lane class constructor takes one string type argument", "[creating lane object]")
{
    GIVEN("Argument as a name of file")
    {
        std::string n = "lane";
        std::string n1 = "lane1.txt";
        std::string n2 = "lane2.doc";
        std::string n3 = "lane3.odt";
        std::string n4 = "lane4.cpp";
        std::string n5 = "";
        std::string n6 = ".txt";

        WHEN("Lane object is creating")
        {
            Lane lane(n);
            Lane lane1(n1);
            Lane lane2(n2);
            Lane lane3(n3);
            Lane lane4(n4);
            Lane lane5(n5);
            Lane lane6(n6);

            THEN("Value laneName_ is equal to filename without extension")
            {
                REQUIRE(lane.getLaneName() == "lane");
                REQUIRE(lane1.getLaneName() == "lane1");
                REQUIRE(lane2.getLaneName() == "lane2");
                REQUIRE(lane3.getLaneName() == "lane3");
                REQUIRE(lane4.getLaneName() == "lane4");
                REQUIRE(lane5.getLaneName() == "");
                REQUIRE(lane6.getLaneName() == "");
            }
        }
    }
}