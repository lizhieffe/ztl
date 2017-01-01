#include "gtest/gtest.h"

#include "network/http_header_test.cc"

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}
