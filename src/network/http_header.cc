#include "http_header.h"

#include <iostream>
#include <map>
#include <sstream>

namespace ztl {
namespace {

const std::map<std::string, HttpHeaderKey> kHttpHeaderKeyMapping {
  { "Accept", HttpHeaderKey::ACCEPT },
  { "Cookie", HttpHeaderKey::COOKIE },
  { "Host", HttpHeaderKey::HOST },
  { "Keep-Alive", HttpHeaderKey::KEEP_ALIVE },
  { "User-Agent", HttpHeaderKey::USER_AGENT },
};

class HttpHeaderImpl : public HttpHeader {
 public:
  bool ParseFrom(const std::string& str) override {
    std::istringstream resp(str);
    std::string line;
    std::string::size_type index, end;
    while (std::getline(resp, line) && line != "\r") {
      index = line.find(':', 0);
      end = line.find('\r', 0);
      if (index == std::string::npos || end == std::string::npos ||
          end - index <= 1) {
        std::cerr << "Error: the HTTP header cannot be parsed." << std::endl;
        return false;
      }
      std::string key = line.substr(0, index);
      std::string value = line.substr(index + 2, end - index - 2);
      SetByStr(key, value);
    }
    return true;
  }

  bool SetByStr(const std::string& key, const std::string& value) override {
    auto it = kHttpHeaderKeyMapping.find(key);
    if (it != kHttpHeaderKeyMapping.end()) {
      Set(it->second, value);
      return true;
    } else {
      return false;
    }
  }

  void Set(HttpHeaderKey key, const std::string& value) override {
    map_.emplace(key, value);
  }
 
  bool GetByStr(const std::string& key, std::string* value) override {
    auto it = kHttpHeaderKeyMapping.find(key);
    if (it != kHttpHeaderKeyMapping.end()) {
      return Get(it->second, value);
      return true;
    } else {
      return false;
    }
  }

  bool Get(HttpHeaderKey key, std::string* value) override {
    auto it = map_.find(key);
    if (it == map_.end()) {
      return false;
    } else {
      *value = it->second;
      return true;
    }
  }

 private:
  std::map<HttpHeaderKey, std::string> map_;
};

}  // namespace

std::unique_ptr<HttpHeader> NewHttpHeader() {
  return std::unique_ptr<HttpHeader>(new HttpHeaderImpl);
}

}  // namespace ztl
