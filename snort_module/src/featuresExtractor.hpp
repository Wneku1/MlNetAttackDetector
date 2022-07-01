#pragma once

#include "snort/protocols/packet.h"
#include <cstdint>
#include <memory>
#include <sys/time.h>
#include <vector>

class FeaturesExtractor final
{
public:
  explicit FeaturesExtractor();
  ~FeaturesExtractor();

  void updatePayloadSize(uint16_t dsize);

  void updateAvgPacketLen(uint32_t pktLen, uint32_t total_packets);

private:
  float m_avgPktSlen;
  uint16_t m_payloadSize;
};
