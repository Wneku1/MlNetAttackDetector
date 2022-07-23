#pragma once
#include "packet_length_collector.hpp"
#include <mlpack/core/math/ccov.hpp>

namespace snort {
struct FlowStats;
}// namespace snort

class FeaturesExtractor final
{
public:
  explicit FeaturesExtractor();
  ~FeaturesExtractor();
  arma::mat getDataToPredict();

  void update(const snort::FlowStats &);
  void update(const PacketLengthCollector &);
  void printDataToPredict() const;

private:
  void updateFlowDuration(const snort::FlowStats &);
  void updateFlowBytesSec();
  void updateBytesAvg(const snort::FlowStats &flowStats);

  // forward (source to destination)
  // backward (destination to source)
  double m_flow_duration{};
  double m_tot_fwd_pkts{};
  double m_tot_bwd_pkts{};
  double m_tot_len_fwd_pkts{};
  double m_tot_len_bwd_pkts{};
  double m_fwd_pkt_len_mean{};
  double m_bwd_pkt_len_mean{};
  double m_flow_byts{};
  double m_pkt_len_mean{};
};
