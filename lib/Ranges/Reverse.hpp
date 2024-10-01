#pragma once
#include "Concepts.hpp"

class reverse {
 public:
  reverse() {}
};

template <Adapter U, typename T>
class Reverse {
 private:
  template <typename Iter>
  class Iterator {
   private:
    Iter data_;

   public:
    Iterator(Iter data) : data_(data) {}

    auto operator++() { return --data_; }

    auto operator--() { return ++data_; }

    T operator*() { return *data_; }

    bool operator==(Iterator<Iter> other) const { return data_ == other.data_; }
  };

  Iterator<typename U::iterator> begin_;
  Iterator<typename U::iterator> end_;

 public:
  using value_type = T;
  using iterator = Iterator<typename U::iterator>;

  Reverse(const U& conteiner)
      : begin_(const_cast<U&>(conteiner).end()),
        end_(const_cast<U&>(conteiner).begin()) {
    ++begin_;
    ++end_;
  }

  auto begin() const { return begin_; }

  auto end() const { return end_; }
};

template <RAdapter U>
Reverse<U, typename U::value_type> operator|(const U& conteiner,
                                             reverse reverse_) {
  return Reverse<U, typename U::value_type>(conteiner);
}