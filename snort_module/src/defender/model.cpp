#include "model.hpp"

#include "mlpack/core.hpp"
#include "mlpack/methods/decision_tree/random_dimension_select.hpp"
#include "mlpack/methods/random_forest/random_forest.hpp"
#include <filesystem>

Model::Model() = default;
Model::~Model() = default;

using namespace mlpack;
using namespace mlpack::tree;

static RandomForest<GiniGain, RandomDimensionSelect> m_randomForest;

void Model::load()
{
  const std::filesystem::path pathToModel{ "../model/model.xml" };
  std::cout << std::filesystem::current_path() << std::endl;

  if (!std::filesystem::exists(pathToModel)) {
    std::cout << pathToModel << " doesn't exists" << std::endl;
    modelLoaded = false;
  }

  bool isLoaded = mlpack::data::Load(pathToModel, "my_model", m_randomForest);

  if (isLoaded) {
    std::cout << "Model loaded" << std::endl;
    modelLoaded = true;
  } else {
    std::cout << "Something is not yes with model.xml" << std::endl;
    modelLoaded = false;
  }
}

bool Model::predict(const arma::mat &data)
{
  if (!modelLoaded) {
    return 0;
  }

  using namespace arma;

  Row<size_t> predictions;
  mat probabilities;
  m_randomForest.Classify(data, predictions, probabilities);

  const auto result = predictions.at(0);
  std::cout << "\nClassification result: " << result << " , Probabilities: " << probabilities.at(0) << "/"
            << probabilities.at(1) << std::endl;
  return static_cast<bool>(result);
}

bool Model::isModelLoaded() const { return modelLoaded; }