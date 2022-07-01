#pragma once

#include <cstdint>
#include <memory>
#include <sys/time.h>
#include <vector>

namespace Extractor {
class Features final
{
public:
  explicit Features();
  ~Features();

  void setStartTime(timeval TimeStamp);
  timeval getStartTime();
  timeval getFlowDuration(timeval pktTimeStamp);
  int getPayloadSize();
  void setPayloadSize(uint16_t dsize);
  float getAvgPacketLen();
  void setAvgPacketLen(uint32_t pktLen, uint32_t total_packets);
  void setPktLenStd(const timeval flowLength);

private:
  void setFirstFlowDuration();
  double standardDev(std::vector<double> const &func);

  timeval startTime;
  timeval flowDuration;

  float avgPktSlen;
  uint16_t payloadSize;

  // Standard deviation
  std::vector<timeval> flowLengths;
};

}// namespace Extractor