#include "featuresExtractor.hpp"


FeaturesExtractor::FeaturesExtractor() = default;

FeaturesExtractor::~FeaturesExtractor() = default;

arma::mat FeaturesExtractor::getDataToPredict()
{
  return { m_flow_duration,
    m_tot_fwd_pkts,
    m_tot_bwd_pkts,
    m_tot_len_fwd_pkts,
    m_tot_len_bwd_pkts,
    m_fwd_pkt_len_mean,
    m_bwd_pkt_len_mean,
    m_flow_byts,
    m_fwd_iat_mean,
    m_bwd_iat_mean,
    m_pkt_len_mean,
    m_pkt_size_avg,
    m_fwd_byts_avg,
    m_bwd_byts_avg,
    m_active_mean,
    m_idle_mean };
}