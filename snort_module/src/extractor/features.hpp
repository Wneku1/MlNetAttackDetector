#pragma once

#include <bits/types/struct_timeval.h>
#include <cstdint>
#include <memory>
#include <vector>

namespace Extractor
{
class TimeStamp;
class Features
{
public:
	Features();
	~Features();

	void setStartTime( struct timeval TimeStamp );
	timeval getStartTime();
	timeval getFlowDuration( struct timeval pktTimeStamp );

	int getForwardPacketsPerSecond();
	void setForwardPacketsPerSecond();

	int getTotalPacketsInForwardDir();
	void setTotalPacketsInForwardDir();

	int getPayloadSize();
	void setPayloadSize( uint16_t dsize );

	int getAltSize();
	void setAltSize();

	int getNumberOfBackwardDirection();
	void setNumberOfBackwardDirection();

	int getFlowPacketsRate();
	void setFlowPacketsRate();

	int getPacketsInBackwardDirection();
	void setPacketsInBackwardDirection();

	int getMinimumInterarrivalPacketTime();
	void setMinimumInterarrivalPacketTime();

	int getFlowByteRate();
	void setFlowByteRate();

	int getActiveAverage();
	void setActiveAverage();

	int getMeantimeBackward();
	void setMeantimeBackward();

	int getIdleAverage();
	void setIdleAverage();

	int getMeantimeForward();
	void setMeantimeForward();

	int getSubflowForwardBytes();
	void setSubflowForwardBytes();

	int getSubflowBackwardBytes();
	void setSubflowBackwardBytes();

	float getAvgPacketLen();
	void setAvgPacketLen( uint32_t pktLen, uint32_t total_packets );

	int getAvgTimeBettwenFlows();
	void setAvgTimeBettwenFlows();

	void setPktLenStd( const timeval flowLength );
	double getPktLenStd();

	// Dodac te o Standard Deviation albo klase do tego ogarnąc bedzie lepiej chyba

private:
	struct timeval startTime;
	struct timeval flowDuration;

	float avgPktSlen;
	uint16_t payloadSize;

	// Standard deviation
	std::vector< struct timeval > flowLengths;

	void setFirstFlowDuration();
	double standardDev( std::vector< double > const& func );
};

} // namespace Extractor