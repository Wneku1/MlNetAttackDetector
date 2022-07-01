#include "module.hpp"
#include "config.hpp"
#include "framework/parameter.h"
#include "inspector.hpp"

#include "detection/detection_engine.h"
#include <cstddef>

static THREAD_LOCAL SimpleStats _stats;
static THREAD_LOCAL snort::ProfileStats PerfStats;

using namespace snort;
using namespace Defender;

namespace Defender {
static constexpr RuleMap s_rules[] = { { 1, "Jeszcze jak" }, { 0, nullptr } };

static const Parameter params[] = { { "start", Parameter::PT_REAL, nullptr, nullptr, "start" },
  { nullptr, Parameter::PT_MAX, nullptr, nullptr, nullptr } };
}// namespace Defender

Defender::ModuleConf::ModuleConf()
  : Module(s_name.data(), s_help.data(), Defender::params), m_config(std::make_shared<Config>())
{}

ModuleConf::~ModuleConf() = default;

const RuleMap *ModuleConf::get_rules() const { return s_rules; }

ProfileStats *ModuleConf::get_profile() const { return &PerfStats; }

bool ModuleConf::set(const char *rawString, Value &value, SnortConfig *config) { return true; }

bool ModuleConf::begin(const char *, int, SnortConfig *) { return true; }

bool ModuleConf::end(const char *, int, SnortConfig *) { return true; }

void ModuleConf::incrementPacketCounter() { ++_stats.total_packets; }

std::shared_ptr<Defender::Config> ModuleConf::get_config() const { return m_config; }

const PegInfo *ModuleConf::get_pegs() const { return simple_pegs; }

PegCount *ModuleConf::get_counts() const { return &_stats.total_packets; }

unsigned ModuleConf::get_gid() const { return s_id; }

ModuleConf::Usage ModuleConf::get_usage() const { return INSPECT; }

void ModuleConf::setInspector(InspectorConf *Defender) { m_inspector = Defender; }

std::string_view ModuleConf::getName() { return s_name; }

std::string_view ModuleConf::getHelp() { return s_help; }