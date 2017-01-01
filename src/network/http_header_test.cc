#include "http_header.h"

#include <iostream>
#include <string>

#include "gtest/gtest.h"

namespace ztl {
namespace {

const char kHttpHeader[] =
  "Host: fake_host\r\n"
  "User-Agent: fake_user_agent\r\n";

TEST(HttpHeaderTest, ParseSuccessfully) {
  auto http_header = NewHttpHeader();
  ASSERT_TRUE(http_header->ParseFrom(kHttpHeader));

  std::string value;
  EXPECT_TRUE(http_header->GetByStr("Host", &value));
  EXPECT_EQ(value, "fake_host");
  EXPECT_TRUE(http_header->Get(HttpHeaderKey::HOST, &value));
  EXPECT_EQ(value, "fake_host");

  EXPECT_TRUE(http_header->GetByStr("User-Agent", &value));
  EXPECT_EQ(value, "fake_user_agent");

  EXPECT_FALSE(http_header->GetByStr("ddd", &value));

  EXPECT_TRUE(http_header->SetByStr("Cookie", "fake_cookie"));
  EXPECT_TRUE(http_header->GetByStr("Cookie", &value));
  EXPECT_EQ(value, "fake_cookie");
}

const char kMalformatedHttpHeader[] =
  "Host:\r\n"
  "User-Agent: fake_user_agent\r\n";

TEST(HttpHeaderTest, ParseMalformatedHeader) {
  auto http_header = NewHttpHeader();
  ASSERT_FALSE(http_header->ParseFrom(kMalformatedHttpHeader));
}

}  // namespace 
}  // namespace ztl
