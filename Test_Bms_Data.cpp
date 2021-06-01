#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "Tx/dataBmsTx.h"

TEST_CASE("Check_1") 
{
 REQUIRE(dataBmsMain() == OK_STATUS);
}
