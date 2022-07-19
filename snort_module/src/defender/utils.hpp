#pragma once

template<typename T> T average(auto value, auto size)
{
  T average{};

  if (size > 0) {
    average = static_cast<T>(value) / static_cast<T>(size);
  } else {
    average = {};
  }

  return average;
}