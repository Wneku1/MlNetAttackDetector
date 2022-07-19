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
  double m_fwd_iat_mean{};
  double m_bwd_iat_mean{};
  double m_pkt_len_mean{};
  double m_pkt_size_avg{};
  double m_fwd_byts_avg{};
  double m_bwd_byts_avg{};
  double m_active_mean{};
  double m_idle_mean{};
  double m_flow_iat_mean{};
};
