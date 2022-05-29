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
	constexpr auto firstArgument{ 1 };
	mat dataset;
	bool loaded = mlpack::data::Load( argv[ firstArgument ], dataset );
	if( !loaded )
	{
		return -1;
	}

	// Row< size_t > labels;
	// labels = conv_to< Row< size_t > >::from( dataset.row( dataset.n_rows - 1 )
	// );
	dataset.print();
	// Row< size_t > labels = conv_to< Row< size_t > >::from( dataset.row(
	// dataset.n_rows - 1 ) ); std::cout << labels.at( 0 ); dataset.print();
	// dataset.shed_row( dataset.n_rows - 1 );
	// dataset.save( "qwe.csv", auto_detect );
	// dataset.shed_row( dataset.n_rows - 1 );

	// const size_t numClasses		 = 2;
	// const size_t minimumLeafSize = 5;
	// const size_t numTrees		 = 10;
	// RandomForest< GiniGain, RandomDimensionSelect > rf;
	// rf = RandomForest< GiniGain, RandomDimensionSelect >( dataset, labels,
	// numClasses, numTrees, minimumLeafSize );

	// Row< size_t > predictions;
	// rf.Classify( dataset, predictions );
	// const size_t correct = arma::accu( predictions == labels );
	// cout << "\nTraining Accuracy: " << ( double( correct ) / double(
	// labels.n_elem ) ) << "\n";

	return 0;
}