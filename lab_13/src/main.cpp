#include <cstddef>
#include <iostream>
#include <cassert>
#include <array>
#include "my_array.h"

template<typename T, std::size_t N>
void test_core() {
  std::array <T, N> ex; 
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.empty();
  ca.empty();
  a.size();
  ca.size();
  assert(sizeof(a) <= sizeof(ex));
  a.at(0);
  ca.at(0);
  a[0];
  ca[0];
  (void)static_cast<const T &>(a[0]);
  (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.fill(T());

  a[0] = T();
  a[0] = a[0];
  a[0] = ca[0];
}

class NonCopyable {
 public:
  NonCopyable() {}
 private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable);
};

template<std::size_t N>
void test_bool() {
    my_array<bool, N> a, b;
    a.fill(1), b.fill(0);
    const my_array<bool, N> d;
    a[9] = a[0] = a[7] = a[8] = a[6] = 0;
    a[7] = 1;
    b[9] = b[0] = b[4] = 1;
}

int main() {
  test_core<int, 10>();
  test_core<bool, 10>();
  test_core<NonCopyable, 10>();
  test_assign<int, 10>();
  test_assign<bool, 10>();
  my_array<bool, 0> a;
  std::cout << a.size();
  test_bool<10>();
}
