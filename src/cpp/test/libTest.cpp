#include "gtest/gtest.h"
#include "../performance/systemStat.h"
#include <iostream>
#include "../url/url_parser.h"
#include "../url/url_parser.hpp"

using namespace std;

TEST(LibTest, CPUUsageTest) {
  SystemStat stat;
  int value = stat.getCPUUsage();

  cout << "cpu usage is " << value << endl;

  ASSERT_TRUE(value > 0);
}

TEST(LibTest, UrlParserTest){
  using namespace http;
  
  string uri = string("http://www.sina.com");
  struct url url = ParseHttpUrl(uri);
  
  string host(url.host);
  ASSERT_EQ("www.sina.com", host);

  uri = string("www.sina.com/1");
  url = ParseHttpUrl(uri);

  host = (url.host);
  ASSERT_EQ("www.sina.com", host);

  uri = string("www.sina.com/1\n");
  url = ParseHttpUrl(uri);

  host = (url.host);
  ASSERT_EQ("www.sina.com", host);

  uri = string("www.sina.com/1\n");
  url = ParseHttpUrl(uri);

  ASSERT_EQ("sina.com", url.domain);
}
