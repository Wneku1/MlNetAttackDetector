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

int main( int argc, char* argv[] )
{
	mat X_train;
	bool X_trainLoaded = mlpack::data::Load( "X_train.csv", X_train );
	if( !X_trainLoaded )
	{
		return -1;
	}

	mat X_test;
	bool X_testLoaded = mlpack::data::Load( "X_test.csv", X_test );
	if( !X_testLoaded )
	{
		return -1;
	}

	mat y_test;
	bool y_testLoaded = mlpack::data::Load( "y_test.csv", y_test );
	if( !y_testLoaded )
	{
		return -1;
	}

	mat y_train;
	bool y_trainLoaded = mlpack::data::Load( "y_train.csv", y_train );
	if( !y_trainLoaded )
	{
		return -1;
	}

	Row< size_t > labels;
	labels = conv_to< Row< size_t > >::from( y_train.row( y_train.n_rows - 1 ) );

	const size_t numClasses		 = 2;
	const size_t minimumLeafSize = 5;
	const size_t numTrees		 = 10;
	RandomForest< GiniGain, RandomDimensionSelect > rf;
	rf = RandomForest< GiniGain, RandomDimensionSelect >( X_train, labels, numClasses, numTrees, minimumLeafSize );

	Row< size_t > predictions;
	rf.Classify( X_train, predictions );
	const size_t correct = arma::accu( predictions == labels );
	cout << "\nTraining Accuracy: " << ( double( correct ) / double( labels.n_elem ) ) << "\n";

	return 0;
}