#include "model.hpp"

#include "mlpack/core.hpp"
#include "mlpack/core/cv/k_fold_cv.hpp"
#include "mlpack/core/cv/metrics/accuracy.hpp"
#include "mlpack/core/cv/metrics/f1.hpp"
#include "mlpack/core/cv/metrics/precision.hpp"
#include "mlpack/core/cv/metrics/recall.hpp"
#include "mlpack/methods/decision_tree/random_dimension_select.hpp"
#include "mlpack/methods/random_forest/random_forest.hpp"
#include <filesystem>
#include <iostream>

using namespace arma;
using namespace mlpack;
using namespace mlpack::tree;
using namespace mlpack::cv;

// static RandomForest<GiniGain, RandomDimensionSelect> m_randomForest;

Model::Model() = default;
Model::~Model() = default;

void Model::load()
{
  auto path = std::filesystem::current_path();
  path += "/mymodel.xml";
  std::cout << path << std::endl;
  RandomForest<GiniGain, RandomDimensionSelect> rf;

  mlpack::data::Load(path, "model", rf);
  // mlpack::data::Load("mymodel.xml", "model", m_randomForest);
}