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