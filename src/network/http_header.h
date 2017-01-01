#ifndef ZTL_HTTP_HEADER
#define ZTL_HTTP_HEADER

#include <memory>
#include <string>

namespace ztl {

enum class HttpHeaderKey {
  ACCEPT,
  COOKIE,
  HOST,
  KEEP_ALIVE,
  USER_AGENT,
};

class HttpHeader {
 public:
  virtual bool ParseFrom(const std::string& str) = 0;

  virtual bool SetByStr(const std::string& key, const std::string& value) = 0;
  virtual void Set(HttpHeaderKey key, const std::string& value) = 0;

  virtual bool GetByStr(const std::string& key, std::string* value) = 0;
  virtual bool Get(HttpHeaderKey key, std::string* value) = 0;
};

std::unique_ptr<HttpHeader> NewHttpHeader();

}  // namespace ztl

#endif // ZTL_HTTP_HEADER
