#pragma once
#include "Concepts.hpp"

class values {
 public:
  values() {}
};

template <Adapter U, typename T>
class Values {
 private:
  template <typename Iter>
  class Iterator {
   public:
    Iterator(Iter data) : data_(data) {}

    auto operator++() { return ++data_; }

    auto operator--() { return --data_; }

    T operator*() { return (*data_).second; }

    bool operator==(Iterator<Iter> other) const { return data_ == other.data_; }

   private:
    Iter data_;
  };

  Iterator<typename U::iterator> begin_;
  Iterator<typename U::iterator> end_;

 public:
  using value_type = T;
  using iterator = Iterator<typename U::iterator>;

  Values(const U& conteiner)
      : begin_(const_cast<U&>(conteiner).begin()),
        end_(const_cast<U&>(conteiner).end()) {}

  auto begin() const { return begin_; }

  auto end() const { return end_; }
};

template <RAdapter U>
  requires(same_as<typename U::value_type,
                   pair<const typename U::key_type, typename U::mapped_type>>)
Values<U, typename U::mapped_type> operator|(const U& conteiner,
                                             values values_) {
  return Values<U, typename U::mapped_type>(conteiner);
}