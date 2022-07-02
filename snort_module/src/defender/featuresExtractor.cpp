#include "featuresExtractor.hpp"
#include <numeric>

FeaturesExtractor::FeaturesExtractor() = default;

FeaturesExtractor::~FeaturesExtractor() = default;

void FeaturesExtractor::updatePayloadSize(uint16_t dsize)
{
  assert(dsize > 0U);
  m_payloadSize = dsize;
}

void FeaturesExtractor::updateAvgPacketLen(uint32_t pktLen, uint32_t total_packets)
{
  // Explain https://math.stackexchange.com/questions/106313/regular-average-calculated-accumulatively
  assert(total_packets > 0U);
  float newAvgPacketLen = m_avgPktSlen * (total_packets - 1U);// if(total_packets == 1) ????
  newAvgPacketLen += pktLen;
  newAvgPacketLen /= total_packets;

  m_avgPktSlen = newAvgPacketLen;
}
