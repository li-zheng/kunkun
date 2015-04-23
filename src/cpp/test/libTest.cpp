#include "gtest/gtest.h"
#include "../performance/systemStat.h"
#include <iostream>

using namespace std;

TEST(LibTest, CPUUsageTest) {
  SystemStat stat;
  int value = stat.getCPUUsage();

  cout << "cpu usage is " << value << endl;

  ASSERT_TRUE(value > 0);
}
