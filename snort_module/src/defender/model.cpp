#include "model.hpp"

#include "mlpack/core.hpp"
#include "mlpack/methods/decision_tree/random_dimension_select.hpp"
#include "mlpack/methods/random_forest/random_forest.hpp"

using namespace mlpack;
using namespace mlpack::tree;

Model::Model() = default;
Model::~Model() = default;

static RandomForest<GiniGain, RandomDimensionSelect> m_randomForest;

void Model::load() { data::Load("model.xml", "model", m_randomForest); }

void Model::predict(const arma::mat &data)
{
  using namespace arma;

  Row<size_t> predictions;
  mat probabilities;
  m_randomForest.Classify(data, predictions, probabilities);
  const auto result = predictions.at(0);
  std::cout << "\nClassification result: " << result << " , Probabilities: " << probabilities.at(0) << "/"
       << probabilities.at(1) << std::endl;;
}