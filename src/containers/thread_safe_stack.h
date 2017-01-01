// Not finished yet.
#include <memory>
#include <mutex>

namespace ztl {

template <typename T>
class ThreadSafeStack {
 public:
  ThreadSafeStack()
    : dummy_bottom_(Node::NewDummyNode()),
      top_(nullptr) {}

  ~ThreadSafeStack() {}

  ThreadSafeStack(const ThreadSafeStack&) = delete;
  ThreadSafeStack& operator=(const ThreadSafeStack&) = delete;

  // Pushes the |new_value| to the stack.
  void Push(T new_value) {
  }

  // Tries to pop the top item in the stack. If the stack is emptry, returns
  // null.
  std::unique_ptr<T> TryPop();

  // Tries to pop the top item in the stack. If the stack is emptry, waits until
  // the item is available and returns it.
  std::unique_ptr<T> WaitAndPop();

private:
  struct Node {
    Node(T value) : value(std::move(value)) {}

    static std::unique_ptr<Node> NewDummyNode() {
      return std::unique_ptr<Node>();
    }

    T value;
    std::unique_ptr<Node> next;

   private:
    Node() {}
  };

  std::unique_ptr<Node> dummy_bottom_;
  Node* top_;
};

}  // namespace ztl
