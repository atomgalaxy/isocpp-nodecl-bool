#include <iostream>

namespace example {
  struct A {
      friend std::ostream& operator<<(std::ostream& o, A const& x) noexcept;
    private:
      int x_ = 0;
  };

  // public streaming operator
  std::ostream& operator<<(std::ostream& o, A const& x) noexcept {
    return o << "A(" << x.x_ << ")";
  }

 struct B {
    // public streaming operator, but ADL-only.
    friend std::ostream& operator<<(std::ostream& o, B const& x) noexcept {
      return o << "B(" << x.x_ << ")";
    }
   private:
     int x_ = 0;
 };
} // namespace example

int main()
{
  // You can take the address of operator<<
  using StreamA = std::ostream&(*)(std::ostream&, example::A const&);
  using StreamB = std::ostream&(*)(std::ostream&, example::B const&);
  StreamA stream_a = example::operator<<;
  StreamB stream_b = example::operator<<;
}
