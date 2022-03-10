#include <iostream>
#include <mlpack/core.hpp>
#include <string_view>

void loadAndPrintData( std::string_view pathToDataset )
{
	using namespace mlpack;
	arma::mat data;
	data::Load( pathToDataset.data(), data, true );
	data.print();
}

int main( int argc, char* argv[] )
{
	constexpr auto firstArgument{ 1 };
	const auto pathToDataset{ argv[ firstArgument ] };
	loadAndPrintData( pathToDataset );
	return 0;
}