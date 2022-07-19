#include "module.hpp"
#include "config.hpp"
#include "framework/parameter.h"
#include "inspector.hpp"

#include "detection/detection_engine.h"
#include <cstddef>

struct DefenderStats
{
  PegCount total_packets{};
  PegCount predicted_attack{};
  PegCount predicted_normal{};
};

static THREAD_LOCAL DefenderStats s_stats;
static THREAD_LOCAL snort::ProfileStats PerfStats;

using namespace snort;

namespace Defender {
static constexpr RuleMap s_rules[] = { { 1, "Jeszcze jak" }, { 0, nullptr } };

const PegInfo defender_pegs[]{ { CountType::SUM, "packets", "counted packets" },
  { CountType::SUM, "predicted_attack", "counted attack packets" },
  { CountType::SUM, "predicted_normal", "counted normal packets" },
  { CountType::END, nullptr, nullptr } };

static const Parameter params[] = { { "start", Parameter::PT_REAL, nullptr, nullptr, "start" },
  { nullptr, Parameter::PT_MAX, nullptr, nullptr, nullptr } };


Defender::ModuleConf::ModuleConf()
  : Module(s_name.data(), s_help.data(), Defender::params), m_config(std::make_shared<Config>())
{}

ModuleConf::~ModuleConf() = default;

const RuleMap *ModuleConf::get_rules() const { return s_rules; }

ProfileStats *ModuleConf::get_profile() const { return &PerfStats; }

bool ModuleConf::set(const char *rawString, Value &value, SnortConfig *config) { return true; }

bool ModuleConf::begin(const char *, int, SnortConfig *) { return true; }

bool ModuleConf::end(const char *, int, SnortConfig *) { return true; }

PegCount ModuleConf::getTotalPacketCount() const { return s_stats.total_packets; }

void ModuleConf::incrementPacketCounter() { ++s_stats.total_packets; }

void ModuleConf::incrementPredictedAttack() { ++s_stats.predicted_attack; }

void ModuleConf::incrementPredictedNormal() { ++s_stats.predicted_normal; }

std::shared_ptr<Defender::Config> ModuleConf::get_config() const { return m_config; }

const PegInfo *ModuleConf::get_pegs() const { return defender_pegs; }

PegCount *ModuleConf::get_counts() const { return reinterpret_cast<PegCount *>(&s_stats); }

unsigned ModuleConf::get_gid() const { return s_id; }

ModuleConf::Usage ModuleConf::get_usage() const { return INSPECT; }

void ModuleConf::setInspector(InspectorConf *Defender) { m_inspector = Defender; }

std::string_view ModuleConf::getName() { return s_name; }

std::string_view ModuleConf::getHelp() { return s_help; }
}// namespace Defender