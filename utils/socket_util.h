#ifndef ZTL_SOCKET_UTIL
#define ZTL_SOCKET_UTIL

#include <netdb.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

namespace ztl {

// Gets the name of the local machine.
std::string GetHostName();

void PrintAddrInfo(const addrinfo& addr_info);

// Automatically delete the addrinfo when destruction.
class AddrInfoDeleter {
 public:
  AddrInfoDeleter(struct addrinfo* addr_info)
    : addr_info_(addr_info) {}

  ~AddrInfoDeleter() {
    freeaddrinfo(addr_info_);   // free the linked-list
  }

 private:
  struct addrinfo* addr_info_;
};

}  // namespace ztl

#endif  // ZTL_SOCKET_UTIL
