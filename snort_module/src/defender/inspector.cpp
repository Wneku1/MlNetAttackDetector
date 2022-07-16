#include "inspector.hpp"
#include "config.hpp"
#include "module.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <math.h>
#include <string>

#include "log/messages.h"

using namespace snort;
using namespace Defender;

//-------------------------------------------------------------------------
// implementation stuff
//-------------------------------------------------------------------------
void InspectorConf::showConfig() const
{
  ConfigLogger::log_option("defender");
  if (m_config) { ConfigLogger::log_list("", std::string(*m_config).c_str()); }
}

//-------------------------------------------------------------------------
// class stuff
//-------------------------------------------------------------------------
InspectorConf::InspectorConf(const std::shared_ptr<Config> &config, ModuleConf *module)
  : m_config(config), m_module(module)
{}

InspectorConf::~InspectorConf() = default;

void InspectorConf::show(const SnortConfig *) const { showConfig(); }

bool InspectorConf::validate(const Packet *packet) const { return packet->flow; }

std::string InspectorConf::getClientIp(const Packet *packet) const
{
  char clientIp[INET6_ADDRSTRLEN];
  packet->flow->client_ip.ntop(clientIp, sizeof(clientIp));

  return clientIp;
}

std::string InspectorConf::getServerIp(const Packet *packet) const
{
  char serverIp[INET6_ADDRSTRLEN];
  packet->flow->server_ip.ntop(serverIp, sizeof(serverIp));

  return serverIp;
}

PegCount InspectorConf::getPacketsCount() const { return *m_module->get_counts(); }

void InspectorConf::resetFeatureExtractor() { m_featuresExtractor = FeaturesExtractor(); }

void InspectorConf::printSomeInfo(Packet *packet)
{
  const auto clientIp{ getClientIp(packet) };
  const auto serverIp{ getServerIp(packet) };
  const auto ipv4SrcValue{ packet->ptrs.ip_api.get_src()->get_ip4_value() };
  const auto ipv4DstValue{ packet->ptrs.ip_api.get_dst()->get_ip4_value() };
  const auto clientPort{ packet->flow->client_port };
  const auto serverPort{ packet->flow->server_port };

  LogMessage("[Client IP]%s\n", clientIp.c_str());
  LogMessage("[Server IP]%s\n", serverIp.c_str());
  LogMessage("[IPv4 source]%d\n", ipv4SrcValue);
  LogMessage("[IPv4 destination]%d\n", ipv4DstValue);
  LogMessage("[Client port]%d\n", clientPort);
  LogMessage("[Server port]%d\n", serverPort);
}

void InspectorConf::eval(Packet *packet)
{
  if (!m_initStaus) {
    LogMessage("Hola amigos\n");
    m_model.load();
    m_initStaus = true;
  }

  m_module->incrementPacketCounter();

  if (!validate(packet)) { return; }

  printSomeInfo(packet);

  m_featuresExtractor.updateFromFlowStats(packet->flow->flowstats);

  m_featuresExtractor.printDataToPredict();
  m_model.predict(m_featuresExtractor.getDataToPredict());

  resetFeatureExtractor();
  std::cout << "\n\n" << std::endl;


  // m_featuresExtractor.updatePayloadSize(packet->dsize);
  // m_featuresExtractor.updateAvgPacketLen(packet->pktlen, getPacketsCount());

  // const auto clientIp{ getClientIp(packet) };
  // const auto serverIp{ getServerIp(packet) };
  // const auto ipv4SrcValue{ packet->ptrs.ip_api.get_src()->get_ip4_value() };
  // const auto ipv4DstValue{ packet->ptrs.ip_api.get_dst()->get_ip4_value() };
  // const auto timeStamp{ m_featuresExtractor->getFlowDurationUs() };// to jest czas od rozpoczęcia analizy
  // const auto payloadSize{ m_featuresExtractor.getPayloadSize() };
  // const auto avgPktLen{ m_featuresExtractor.getAvgPacketLen() };

  // LogMessage( "[ClientIP]%s\n", clientIp.c_str() );
  // LogMessage( "[ServerIP]%s\n", serverIp.c_str() );
  // LogMessage( "[PacketLen]%d\n", packet->pktlen );
  // LogMessage( "[FlowStatTimeSec]%ld\n", packet->flow->flowstats.start_time.tv_sec );
  // LogMessage( "[FlowLatency]%ld\n", packet->flow->flowstats.total_flow_latency );
  // LogMessage( "[FlowBytesClient]%ld\n", packet->flow->flowstats.client_bytes );
  // LogMessage( "[FlowPktsClient]%ld\n", packet->flow->flowstats.client_pkts );

  // https://ask.wireshark.org/question/969/what-is-epoch-time-in-wireshark/
  // LogMessage("[FlowStatTimeUsec]%ld.%ld\n",
  //   packet->flow->flowstats.start_time.tv_sec,
  //   packet->flow->flowstats.start_time.tv_usec);// Czyli to jest czas od 01.01.1970

  // if( packet->flow->flowstats.start_time.tv_sec != 1654630708 )
  // {
  // 	LogMessage( "[DifferenceTime][FlowStatTimeSec]%ld\n", packet->flow->flowstats.start_time.tv_usec );
  // }

  // if (packet->pkth->pktlen != packet->pktlen) {
  //   // Czyli to jest to samo w sumie.
  //   LogMessage("[Difference]");
  //   LogMessage("[PacketLen]%d\n", packet->pktlen);
  //   LogMessage("[PacketPkthLen]%d\n", packet->pkth->pktlen);
  // }

  // LogMessage( "[IPv4SrcValue]%d\n", ipv4SrcValue );
  // LogMessage( "[IPv4DstValue]%d\n", ipv4DstValue );
  // LogMessage( "[m_featuresExtractorTimeStamp]%ld\n", timeStamp ); // fl_dur
  // LogMessage( "[m_featuresExtractorPayloadSize]%d\n", payloadSize ); // dsize
  // LogMessage( "[m_featuresExtractorAvgPktLen]%f\n", avgPktLen ); // pkt_size_avg
}
