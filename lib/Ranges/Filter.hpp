#pragma once
#include "Concepts.hpp"

template <typename Func>
class filter {
 public:
  Func func_;
  filter(Func func) : func_(func) {}
};

template <Adapter U, typename T, typename Func>
class Filter {
 private:
  template <typename Iter>
  class Iterator {
   private:
    Iter data_;
    Func func_;
    Iter end_;
    Iter rend_;

   public:
    Iterator(Iter data, Func func, Iter end, Iter rend)
        : data_(data), func_(func), end_(end), rend_(rend) {
      --rend_;
    }

    auto operator++() {
      ++data_;
      while (data_ != end_ && !func_(*data_)) ++data_;
      return data_;
    }

    auto operator--() {
      --data_;
      while (data_ != rend_ && !func_(*data_)) --data_;
      return data_;
    }

    T operator*() { return *data_; }

    bool operator==(Iterator<Iter> other) const { return data_ == other.data_; }
  };

  Iterator<typename U::iterator> begin_;
  Iterator<typename U::iterator> end_;
  Func func_;

 public:
  using value_type = T;
  using iterator = Iterator<typename U::iterator>;

  Filter(const U& conteiner, filter<Func> filter)
      : begin_(const_cast<U&>(conteiner).begin(), filter.func_,
               const_cast<U&>(conteiner).end(),
               const_cast<U&>(conteiner).begin()),
        end_(const_cast<U&>(conteiner).end(), filter.func_,
             const_cast<U&>(conteiner).end(),
             const_cast<U&>(conteiner).begin()),
        func_(filter.func_) {}

  auto begin() {
    while (begin_ != end_ && !func_(*begin_)) ++begin_;
    return begin_;
  }

  auto end() const { return end_; }
};

template <Adapter U, typename Func>
  requires invocable<Func, typename U::value_type>
Filter<U, typename U::value_type, Func> operator|(const U& conteiner,
                                                  filter<Func> filter) {
  return Filter<U, typename U::value_type, Func>(conteiner, filter);
}