#include "http_line.hh"

#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

namespace ztl {
namespace {

std::vector<std::string> SplitByChar(std::string str, char c) {
  std::stringstream ss(str);
  std::string segment;
  std::vector<std::string> segment_list;
  while (std::getline(ss, segment, c)) {
    segment_list.push_back(segment);
  }
  return segment_list;
}

class HttpLineImpl : public HttpLine {
 public:
  HttpLineImpl(const std::string& str) {
    // Handle two cases: 1. end with \r\n, 2. end without it
    std::size_t end = str.find("\r\n");
    if (end == std::string::npos) {
      end = str.size();
    }
    std::vector<std::string> split = SplitByChar(str.substr(0, end), ' ');
    if (split.size() != 3) {
      FailConstructor(str);
      return;
    }

    if (split[0] == "GET") {
      http_method_ = HttpMethod::GET;
    } else {
      // TODO: parse other methods.
      http_method_ = HttpMethod::POST;
    }

    std::vector<std::string> uri_and_params = SplitByChar(split[1], '?');
    if (uri_and_params.size() == 0 || uri_and_params[0].find('/') != 0) {
      FailConstructor(str);
      return;
    }
    uri_ = uri_and_params[0].substr(1, uri_and_params[0].size() - 1);
    for (size_t i = 1; i < uri_and_params.size(); ++i) {
      const auto& kv = uri_and_params[i];
      size_t index = kv.find('=');
      if (index == std::string::npos || index == 0) {
        FailConstructor(str);
        return;
      }
      params_.emplace(kv.substr(0, index),
                      kv.substr(index + 1, kv.size() - index - 1));
    }
  }

  HttpMethod GetMethod() const override {
    return http_method_;
  }

  std::string GetMethodStr() const override {
    if (http_method_ == HttpMethod::GET) {
      return "GET";
    } else {
      return "POST";
    }
  }

  std::string GetUri() const override {
    return uri_;
  }

  std::unordered_map<std::string, std::string> GetParams() const override {
    return params_;
  }

 private:
  void FailConstructor(const std::string& str) {
    std::cerr << "Error: cannot parse header correctly:" << std::endl;
    std::cerr << str << std::endl;
    parse_failed_ = true;
  }

  HttpMethod http_method_;
  std::string uri_;
  std::unordered_map<std::string, std::string> params_;
  bool parse_failed_ = false;
};

}  // namespace

std::unique_ptr<HttpLine> NewHttpLine(const std::string& str) {
  return std::unique_ptr<HttpLine>(new HttpLineImpl(str));
}

}  // namespace ztl
