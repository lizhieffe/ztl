#include "socket_sender.hh"

#include <cstring>
#include <errno.h>
#include <iostream>
#include <netdb.h>
#include <sys/select.h>
#include <sys/socket.h>

namespace ztl {
namespace {

class SocketSenderImpl : public SocketSender {
 public:
  SocketSenderImpl(int socket_fd) : socket_fd_(socket_fd) {}

  bool Send(const std::string& str) override {
    if (socket_fd_ <= 0) {
      std::cerr << "Error: socket file descriptor <= 0." << std::endl;
      return false;
    }

    struct timeval timeout;
    timeout.tv_sec = 3;
    timeout.tv_usec = 0;

    int bytes_sent = 0;

    while (true) {
      fd_set write_fd;
      FD_ZERO(&write_fd);
      FD_SET(socket_fd_, &write_fd);

      int err = select(socket_fd_ + 1, nullptr, &write_fd, nullptr, &timeout);
      if (err < 0) {
        std::cerr << "Socket write fd set is not ready. Error is: "
                  << std::strerror(errno) << std::endl;;
        break;
      } else if (err == 0) { /* timeout */
        continue;
      }

      bytes_sent = send(socket_fd_, str.c_str() + bytes_sent, str.size(), 0);
      if (bytes_sent < 0) {
        // TODO: add retry mechanism if the error is not fatal.
        //if (WSAGetLastError() != WSAWOULDBLOCK()) {
          std::cerr << "Error: connection has problem." << std::endl;
          return false;
        //}
        //n_bytes = 0;
      } else {
        std::cout << "Sent " << bytes_sent << " bytes." << std::endl;
      }

      if ((unsigned long)bytes_sent == str.size()) {
        std::cout << "Successfully sent data to the peer.\n\n" << std::endl;
        return true;
      }
    }
    return false;
  }

 private:
  int socket_fd_;
};

}  // namespace

std::unique_ptr<SocketSender> NewSocketSender(int socket_fd) {
  return std::unique_ptr<SocketSender>(new SocketSenderImpl(socket_fd));
}

}  // namespace ztl
