#pragma once

#include "framework/module.h"
#include "inspector.hpp"
#include "profiler/profiler.h"
#include <memory>
#include <string_view>

class Config;

namespace snort
{
class Inspector;
}

namespace Detector
{
class InspectorConf;
class ModuleConf : public snort::Module
{
public:
	ModuleConf();
	~ModuleConf() override;

	bool set( const char*, snort::Value&, snort::SnortConfig* ) override;
	bool begin( const char*, int, snort::SnortConfig* ) override;
	bool end( const char*, int, snort::SnortConfig* ) override;

	void incrementPacketCounter();

	std::shared_ptr< Config > get_config() const;

	const PegInfo* get_pegs() const override;
	PegCount* get_counts() const override;

	unsigned get_gid() const override;

	const snort::RuleMap* get_rules() const override;
	snort::ProfileStats* get_profile() const override;

	Usage get_usage() const override;

	void setInspector( InspectorConf* );

	static std::string_view getName();
	static std::string_view getHelp();

private:
	std::shared_ptr< Config > m_config;
	InspectorConf* m_inspector{ nullptr };

	static constexpr std::string_view s_name{ "detector" };
	static constexpr std::string_view s_help{ "detection based on machine learning" };

	static constexpr unsigned s_id{ 456U };
};
} // namespace Detector