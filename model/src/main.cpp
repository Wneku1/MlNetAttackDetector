#include "mlpack/core.hpp"
#include "mlpack/core/cv/k_fold_cv.hpp"
#include "mlpack/core/cv/metrics/accuracy.hpp"
#include "mlpack/core/cv/metrics/f1.hpp"
#include "mlpack/core/cv/metrics/precision.hpp"
#include "mlpack/core/cv/metrics/recall.hpp"
#include "mlpack/methods/decision_tree/random_dimension_select.hpp"
#include "mlpack/methods/random_forest/random_forest.hpp"
#include <iostream>

using namespace arma;
using namespace mlpack;
using namespace mlpack::tree;
using namespace mlpack::cv;

mat loadData( const std::string& path )
{
	mat data;
	bool isLoaded = mlpack::data::Load( path, data );
	assert( isLoaded );
	return data;
}

Row< size_t > convertToRow( mat data )
{
	return conv_to< Row< size_t > >::from( data.row( data.n_rows - 1 ) );
}

void predict( const RandomForest< GiniGain, RandomDimensionSelect >& rf, const mat& data, const Row< size_t >& label )
{
	Row< size_t > trainPredictions;
	rf.Classify( data, trainPredictions );
	const size_t correctTrain = arma::accu( trainPredictions == label );
	cout << "accuracy: " << ( double( correctTrain ) / double( label.n_elem ) ) << "\n";
}

int main( int argc, char* argv[] )
{
	mat X_train{ loadData( "X_train.csv" ) };
	mat X_test{ loadData( "X_test.csv" ) };
	mat y_test{ loadData( "y_test.csv" ) };
	mat y_train{ loadData( "y_train.csv" ) };

	Row< size_t > y_trainToModel{ convertToRow( y_train ) };
	Row< size_t > y_testToModel{ convertToRow( y_test ) };

	constexpr size_t numClasses{ 2U };
	constexpr size_t minimumLeafSize{ 5U };
	constexpr size_t numTrees{ 10U };
	RandomForest< GiniGain, RandomDimensionSelect > rf{ RandomForest< GiniGain, RandomDimensionSelect >(
		X_train, y_trainToModel, numClasses, numTrees, minimumLeafSize ) };

	cout << "\nTraining ";
	predict( rf, X_train, y_trainToModel );

	cout << "\nTest ";
	predict( rf, X_train, y_trainToModel );

	mat allDataset{ loadData( "allDatasetToTest.csv" ) };
	mat allLabels{ loadData( "allDatasetLabels.csv" ) };
	Row< size_t > labelsAllDataset{ convertToRow( allLabels ) };

	cout << "\nAll dataset ";
	predict( rf, allDataset, labelsAllDataset );

	return 0;
}