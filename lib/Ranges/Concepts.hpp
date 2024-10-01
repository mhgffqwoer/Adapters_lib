#pragma once
#include <iostream>

using std::invocable;
using std::invoke_result_t;
using std::pair;
using std::same_as;

template <typename T>
concept Adapter = requires(T a) {
  ++a.begin();
  *a.end();
};

template <typename T>
concept RAdapter = requires(T a) {
  ++a.begin();
  *a.end();
  --a.end();
};
