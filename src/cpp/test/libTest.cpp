#include "gtest/gtest.h"
#include "../performance/systemStat.h"
#include <iostream>
#include "../url/url_parser.h"

using namespace std;

TEST(LibTest, CPUUsageTest) {
  SystemStat stat;
  int value = stat.getCPUUsage();

  cout << "cpu usage is " << value << endl;

  ASSERT_TRUE(value > 0);
}

TEST(LibTest, UrlParserTest){
  struct parsed_url* url = parse_url("http://www.sina.com");
  
  ASSERT_FALSE(NULL == url);

  string host(url->host);
  ASSERT_EQ("www.sina.com", host);


  url = parse_url("http://www.sina.com/1");

  ASSERT_FALSE(NULL == url);

  host = (url->host);
  ASSERT_EQ("www.sina.com", host);

  url = parse_url("http://www.sina.com/abc/");

  ASSERT_FALSE(NULL == url);

  host = (url->host);
  ASSERT_EQ("www.sina.com", host);
}
