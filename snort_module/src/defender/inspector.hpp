#pragma once

#include "module.hpp"
#include <memory>

#include "featuresExtractor.hpp"
#include "model.hpp"
#include <detection/detection_engine.h>
#include <snort/framework/counts.h>

class Config;

namespace Defender {
class ModuleConf;
class InspectorConf : public snort::Inspector
{
public:
  InspectorConf(const std::shared_ptr<Config> &, ModuleConf *);
  virtual ~InspectorConf();

  void show(const snort::SnortConfig *) const override;
  void eval(snort::Packet *) override;

private:
  void printSomeInfo(snort::Packet *packet);
  void showConfig() const;

  std::string getClientIp(const snort::Packet *packet) const;
  std::string getServerIp(const snort::Packet *packet) const;
  PegCount getPacketsCount() const;
  bool validate(const snort::Packet *packet) const;

  FeaturesExtractor m_featuresExtractor;
  Model m_model;
  std::shared_ptr<Config> m_config;
  Defender::ModuleConf *m_module{ nullptr };
  bool m_initStaus{ false };
};
}// namespace Defender