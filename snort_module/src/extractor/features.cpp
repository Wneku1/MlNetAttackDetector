#include "features.hpp"
#include <bits/types/struct_timeval.h>
#include <cmath>
#include <numeric>

using namespace Extractor;

void Features::setFirstFlowDuration()
{
	this->flowDuration.tv_sec  = 0;
	this->flowDuration.tv_usec = 0;
}

// Zmienić żeby działało na timeval
double standardDev( std::vector< double > const& func )
{
	double mean	  = std::reduce( func.begin(), func.end(), 0.0 ) / func.size();
	double sq_sum = std::inner_product(
		func.begin(),
		func.end(),
		func.begin(),
		0.0,
		[]( double const& x, double const& y ) { return x + y; },
		[ mean ]( double const& x, double const& y ) { return ( x - mean ) * ( y - mean ); } );
	return std::sqrt( sq_sum / func.size() );
}

Features::Features() {}

Features::~Features() {}

void Features::setStartTime( struct timeval TimeStamp )
{
	this->startTime = TimeStamp;
	setFirstFlowDuration();
}

timeval Features::getStartTime()
{
	return startTime;
}

// Zrobić klasę timestamp żeby dało się to odejmować
timeval Features::getFlowDuration( struct timeval pktTimeStamp )
{
	struct timeval newflowDuration;
	if( 0 == this->flowDuration.tv_usec && 0 == this->flowDuration.tv_sec )
	{
		return flowDuration;
	}

	newflowDuration.tv_sec	= pktTimeStamp.tv_sec - flowDuration.tv_sec;
	newflowDuration.tv_usec = pktTimeStamp.tv_usec - flowDuration.tv_usec;

	return newflowDuration;
}

int Features::getPayloadSize()
{
	return this->payloadSize;
}
void Features::setPayloadSize( uint16_t dsize )
{
	this->payloadSize = dsize;
}

float Features::getAvgPacketLen()
{
	return this->avgPktSlen;
}

void Features::setAvgPacketLen( uint32_t pktLen, uint32_t total_packets )
{
	// Expalain https://math.stackexchange.com/questions/106313/regular-average-calculated-accumulatively

	float newAvgPacketLen = this->avgPktSlen * ( total_packets - 1 );
	newAvgPacketLen += pktLen;
	newAvgPacketLen /= total_packets;

	this->avgPktSlen = newAvgPacketLen;
}

void setPktLenStd( const timeval flowLength ) {}