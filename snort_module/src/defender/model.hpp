#pragma once
#include <mlpack/core/math/ccov.hpp>

class Model final
{
public:
  explicit Model();
  ~Model();

  void load();
  bool predict(const arma::mat &data);
  bool isModelLoaded() const;

private:
  bool modelLoaded{ false };
};