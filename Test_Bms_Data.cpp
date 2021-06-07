#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "Tx/dataBmsTx.h"

TEST_CASE(" Test case to check if data is read and sender sends data ") 
{
 /* This will stream datas in multiples of 100 */
 int runTimeIpNum_u32 = 50;
 int maxStreamingRange = 100;
 REQUIRE(dataBmsMain((runTimeIpNum_u32-1), maxStreamingRange) == OK_STATUS);
}

TEST_CASE(" Test case to check if user request to halt the read after (100-1) as max count ") 
{
 /* Note: haltBmsRead.txt contains value as 0 in this case, so change in file as 1 and try the test case */
 /* This will stream only 100 datas */
 int runTimeIpNum_u32 = 100;
 int maxStreamingRange = 100;
 REQUIRE(dataBmsMain((runTimeIpNum_u32-1),maxStreamingRange) == OK_STATUS);
}
