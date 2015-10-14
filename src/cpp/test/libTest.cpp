#include "gtest/gtest.h"
#include "../performance/systemStat.h"
#include <iostream>
#include "../url/url_parser.h"
#include "../url/url_parser.hpp"
#include "../cryptography/aesCrypto.h"

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


TEST(LibTest, AESCryptoTest) {
  AESCrypto aes;
  string key = "1234567890123456";

  string result = aes.encryptECBWithBase64("texttoencrypt123", key);
  ASSERT_EQ("dPDIFb0I1ET8c8rZCM/tUQ==", result);

  string decoded = aes.decryptECBWithBase64(result, key);
  ASSERT_EQ("texttoencrypt123", decoded);

  key = "xuoTT1QEX1b4g/KN";

  result = aes.encryptECBWithBase64("texttoencrypt", key);
  ASSERT_EQ("wWCfaFR92nCTQyrnTv3LEw==", result);
  decoded = aes.decryptECBWithBase64(result, key);
  ASSERT_EQ("texttoencrypt", decoded);

  key = "xuoTT1QEX1b4g/KN";

  result = aes.encryptECBWithBase64("90:b1:1c:9d:71:8b", key);
  ASSERT_EQ("+IL43BP6u4xUvWFOY4KjWdJW7NOoG4sSaNf8p44vbIE=", result);
  decoded = aes.decryptECBWithBase64(result, key);
  ASSERT_EQ("90:b1:1c:9d:71:8b", decoded);


}