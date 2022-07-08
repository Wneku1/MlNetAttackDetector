#pragma once
#include <mlpack/core/math/ccov.hpp>

class Model final
{
public:
  Model();
  ~Model();

  void load();
  void predict(const arma::mat &data);
};