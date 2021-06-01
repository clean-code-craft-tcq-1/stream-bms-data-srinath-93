#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "Tx/dataBmsTx.h"

TEST_CASE(" Test case to check if data is read and sender sends data ") 
{
 REQUIRE(dataBmsMain() == OK_STATUS);
}

TEST_CASE(" Test case to check if data read is happening and returns ok status ") 
{
 REQUIRE(readBmsData() == OK_STATUS);
}
