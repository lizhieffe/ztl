#include "socket_util.h"

#include <iostream>
#include <unistd.h>

namespace ztl {

std::string GetHostName() {
  char host_name[1024];
  if (gethostname(host_name, sizeof host_name) == 0) {
    return host_name;
  } else {
    return "";
  }
}

namespace {

std::string GetAiFamily(int ai_family) {
  std::string name;
  if (ai_family == AF_UNSPEC) {
    name = "AF_UNSPEC";
  } else if (ai_family == AF_INET) {
    name = "IPV4";
  } else if (ai_family == AF_INET6) {
    name = "IPV6";
  } else {
    name = std::to_string(ai_family);
  }
  return name;
}

}  // namespace

void PrintAddrInfo(const addrinfo& addr_info) {
  char addr[1024];
  char service[20];

  getnameinfo(addr_info.ai_addr, sizeof *addr_info.ai_addr, addr, sizeof addr,
              service, sizeof service, 0);
  std::cout << "  address: " << addr << std::endl;
  std::cout << "  service: " << service << std::endl;
  std::cout << "ai_family: " << GetAiFamily(addr_info.ai_family) << std::endl;
}

}  // namespace ztl
