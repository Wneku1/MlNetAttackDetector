#include "featuresExtractor.hpp"


FeaturesExtractor::FeaturesExtractor() = default;

FeaturesExtractor::~FeaturesExtractor() = default;

arma::mat FeaturesExtractor::getDataToPredict()
{
  // return { 2458008.0,
  //   8.0,
  //   7.0,
  //   1148.0,
  //   1581.0,
  //   143.5,
  //   225.8571428571,
  //   1110.2486240891,
  //   175572.0,
  //   351144.0,
  //   369637.833333333,
  //   170.5625,
  //   181.9333333333,
  //   0.0,
  //   0.0,
  //   0.0,
  //   0.0 };// 0 - Bening

  // return { 8877.0,
  //   3.0,
  //   4.0,
  //   250.0,
  //   935.0,
  //   83.33333333,
  //   233.75,
  //   133491.0443,
  //   1479.5,
  //   4193.5,
  //   2958.0,
  //   148.125,
  //   169.2857143,
  //   0.0,
  //   0.0,
  //   0.0,
  //   0.0 };
  // // 1 - Attack

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
    m_flow_iat_mean,
    m_pkt_len_mean,
    m_pkt_size_avg,
    m_fwd_byts_avg,
    m_bwd_byts_avg,
    m_active_mean,
    m_idle_mean };
}