#pragma once
#include <mlpack/core/math/ccov.hpp>

class FeaturesExtractor final
{
public:
  explicit FeaturesExtractor();
  ~FeaturesExtractor();
  arma::mat getDataToPredict();

private:
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
};
