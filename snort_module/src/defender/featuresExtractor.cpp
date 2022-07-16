#include "featuresExtractor.hpp"
#include "snort/flow/flow.h"
#include <chrono>
#include <ctime>

FeaturesExtractor::FeaturesExtractor() = default;

FeaturesExtractor::~FeaturesExtractor() = default;

void FeaturesExtractor::printDataToPredict() const
{
  std::cout << "m_flow_duration: " << m_flow_duration << std::endl;
  std::cout << "m_tot_fwd_pkts: " << m_tot_fwd_pkts << std::endl;
  std::cout << "m_tot_bwd_pkts: " << m_tot_bwd_pkts << std::endl;
  std::cout << "m_tot_len_fwd_pkts: " << m_tot_len_fwd_pkts << std::endl;
  std::cout << "m_tot_len_bwd_pkts: " << m_tot_len_bwd_pkts << std::endl;
  std::cout << "m_fwd_pkt_len_mean: " << m_fwd_pkt_len_mean << std::endl;
  std::cout << "m_bwd_pkt_len_mean: " << m_bwd_pkt_len_mean << std::endl;
  std::cout << "m_flow_byts: " << m_flow_byts << std::endl;
  std::cout << "m_fwd_iat_mean: " << m_fwd_iat_mean << std::endl;
  std::cout << "m_bwd_iat_mean: " << m_bwd_iat_mean << std::endl;
  std::cout << "m_flow_iat_mean: " << m_flow_iat_mean << std::endl;
  std::cout << "m_pkt_len_mean: " << m_pkt_len_mean << std::endl;
  std::cout << "m_pkt_size_avg: " << m_pkt_size_avg << std::endl;
  std::cout << "m_fwd_byts_avg: " << m_fwd_byts_avg << std::endl;
  std::cout << "m_bwd_byts_avg: " << m_bwd_byts_avg << std::endl;
  std::cout << "m_active_mean: " << m_active_mean << std::endl;
  std::cout << "m_idle_mean: " << m_idle_mean << std::endl;
}

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

  return { m_flow_duration,// v 2458008.0,
    m_tot_fwd_pkts,// v  8.0,
    m_tot_bwd_pkts,// v 7.0,
    m_tot_len_fwd_pkts,// 1148.0,
    m_tot_len_bwd_pkts,// 1581.0,
    m_fwd_pkt_len_mean,// 143.5,
    m_bwd_pkt_len_mean,// 225.8571428571,
    m_flow_byts,// v 1110.2486240891,
    m_fwd_iat_mean,// 175572.0,
    m_bwd_iat_mean,// 351144.0,
    m_flow_iat_mean,// 369637.833333333,
    m_pkt_len_mean,// 170.5625,
    m_pkt_size_avg,// 181.9333333333,
    m_fwd_byts_avg,// v 0.0,
    m_bwd_byts_avg,// v 0.0,
    m_active_mean,// 0.0,
    m_idle_mean };// 0.0,
}

double FeaturesExtractor::calcBytsAvg(const unsigned long &bytes, const unsigned long &packets)
{
  double bytesAvg{};

  if (packets > 0U) {
    bytesAvg = static_cast<double>(bytes) / static_cast<double>(packets);
  } else {
    bytesAvg = 0.0;
  }

  return bytesAvg;
}

void FeaturesExtractor::updateFlowDuration(const snort::FlowStats &flowStats)
{
  time_t now = time(nullptr);
  m_flow_duration = now - flowStats.start_time.tv_sec;
}

void FeaturesExtractor::updateFlowBytesSec()
{
  const auto totalBytes{ m_tot_fwd_pkts + m_tot_bwd_pkts };
  if (m_flow_duration > 0.0) {
    m_flow_byts = totalBytes / m_flow_duration;
  } else {
    m_flow_byts = 0.0;
  }
}

void FeaturesExtractor::updateBytesAvg(const snort::FlowStats &flowStats)
{
  const auto &clientBytes = flowStats.client_bytes;
  const auto &clientPkts = flowStats.client_pkts;

  const auto &serverBytes = flowStats.server_bytes;
  const auto &serverPkts = flowStats.server_pkts;

  m_tot_fwd_pkts = serverPkts;
  m_fwd_byts_avg = calcBytsAvg(serverBytes, serverPkts);

  m_tot_bwd_pkts = clientPkts;
  m_bwd_byts_avg = calcBytsAvg(clientBytes, clientPkts);
}

void FeaturesExtractor::updateFromFlowStats(const snort::FlowStats &flowStats)
{
  updateFlowDuration(flowStats);
  updateBytesAvg(flowStats);
  updateFlowBytesSec();
}