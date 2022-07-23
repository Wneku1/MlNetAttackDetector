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
  if (m_config) {
    ConfigLogger::log_list("", std::string(*m_config).c_str());
  }
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

PegCount InspectorConf::getPacketsCount() const { return m_module->getTotalPacketCount(); }

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

  if (!m_model.isModelLoaded()) {
    return;
  }

  if (!validate(packet)) {
    return;
  }

  m_module->incrementPacketCounter();


  printSomeInfo(packet);

  m_packetLengthCollector.update(packet, getPacketsCount());

  m_featuresExtractor.update(packet->flow->flowstats);
  m_featuresExtractor.update(m_packetLengthCollector);

  m_featuresExtractor.printDataToPredict();

  auto isAttack = m_model.predict(m_featuresExtractor.getDataToPredict());

  if (isAttack) {
    m_module->incrementPredictedAttack();
  } else {
    m_module->incrementPredictedNormal();
  }

  resetFeatureExtractor();
  std::cout << "\n\n" << std::endl;
}
