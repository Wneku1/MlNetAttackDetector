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

using Model = RandomForest<GiniGain, RandomDimensionSelect>;

mat loadData(const std::filesystem::path &path)
{
  mat data;
  bool isLoaded = mlpack::data::Load(path, data);
  assert(isLoaded);
  return data;
}

Row<size_t> convertToRow(mat data) { return conv_to<Row<size_t>>::from(data.row(data.n_rows - 1)); }

void predict(const Model &model, const mat &data, const Row<size_t> &label)
{
  Row<size_t> predictions;
  model.Classify(data, predictions);
  const size_t correctTrain = arma::accu(predictions == label);
  cout << "accuracy: " << (double(correctTrain) / double(label.n_elem)) << "\n";
}

void trainModel(const mat &dataTrain, const Row<size_t> &labelTrain, Model &model)
{
  constexpr size_t numClasses{ 9U };
  constexpr size_t numTrees{ 100U };
  constexpr size_t minimumLeafSize{ 4U };
  constexpr double minimumGainSplit{ 1e-7 };
  constexpr size_t maximumDepth{ 6U };

  model = Model(dataTrain, labelTrain, numClasses, numTrees, minimumLeafSize, minimumGainSplit, maximumDepth);
}

void saveModel(const std::filesystem::path &pathToSave, const Model &model)
{
  if (!std::filesystem::exists(pathToSave)) { std::filesystem::create_directory(pathToSave); }

  mlpack::data::Save(pathToSave / "model.xml", "model", model, false);

  std::cout << "Model has been saved." << std::endl;
}

void loadModel(const std::filesystem::path &pathToModel, Model &model)
{
  bool isLoaded = mlpack::data::Load(pathToModel, "model", model);
  assert(isLoaded);

  std::cout << "Model has been loaded." << std::endl;
}

enum class Option : int { CreateSave, LoadPredict };

int main(int argc, char *argv[])
{
  constexpr auto argOption{ 1U };
  constexpr auto argXdata{ 2U };
  constexpr auto argyData{ 3U };

  Option option{ static_cast<Option>(std::stoi(argv[argOption])) };

  const std::filesystem::path pathToDatasets{ "../datasets" };
  mat X_train{ loadData(pathToDatasets / argv[argXdata]) };
  mat y_train{ loadData(pathToDatasets / argv[argyData]) };
  Row<size_t> y_trainToModel{ convertToRow(y_train) };

  Model model;

  switch (option) {
  case Option::CreateSave: {
    const std::filesystem::path pathToSaveModel{ "../output" };
    trainModel(X_train, y_trainToModel, model);
    saveModel(pathToSaveModel, model);
    break;
  }
  case Option::LoadPredict: {
    const std::filesystem::path pathToModel{ "../output/model.xml" };
    loadModel(pathToModel, model);
    break;
  }
  default:
    return 0;
  }

  cout << "\nTraining ";
  predict(model, X_train, y_trainToModel);

  mat X_test{ loadData(pathToDatasets / "X_test.csv") };
  mat y_test{ loadData(pathToDatasets / "y_test.csv") };
  Row<size_t> y_testToModel{ convertToRow(y_test) };

  cout << "\nTest ";
  predict(model, X_test, y_testToModel);

  return 0;
}