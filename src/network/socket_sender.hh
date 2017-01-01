#ifndef ZTL_NETWORK_SOCKET_SENDER
#define ZTL_NETWORK_SOCKET_SENDER

#include <memory>
#include <string>

namespace ztl {

class SocketSender {
 public:
  virtual ~SocketSender() {}

  virtual bool Send(const std::string& str) = 0;
};

std::unique_ptr<SocketSender> NewSocketSender(int socket_fd);

}  // namespace ztl

#endif // ZTL_NETWORK_SOCKET_SENDER
