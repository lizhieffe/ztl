#ifndef ZTL_NETWORK_HTTP_LINE
#define ZTL_NETWORK_HTTP_LINE

#include <memory>
#include <string>
#include <unordered_map>

namespace ztl {

enum class HttpMethod {
  GET,
  POST,
};

class HttpLine {
 public:
  ~HttpLine() {}

  virtual HttpMethod GetMethod() const = 0;
  virtual std::string GetMethodStr() const = 0;
  virtual std::string GetUri() const = 0;
  virtual std::unordered_map<std::string, std::string>
  GetParams() const = 0;
};

std::unique_ptr<HttpLine> NewHttpLine(const std::string& str);

}  // ztl

#endif  // ZTL_NETWORK_HTTP_LINE
