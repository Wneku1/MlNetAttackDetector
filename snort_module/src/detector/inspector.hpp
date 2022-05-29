#pragma once

#include "module.hpp"
#include <memory>

#include <detection/detection_engine.h>
#include <snort/framework/counts.h>

class Config;

namespace Detector
{
class ModuleConf;
class InspectorConf : public snort::Inspector
{
public:
	InspectorConf( const std::shared_ptr< Config >&, ModuleConf* );
	virtual ~InspectorConf();

	void show( const snort::SnortConfig* ) const override;
	void eval( snort::Packet* ) override;

private:
	void showConfig() const;

	void printAttackInfo() const;

	std::string getClientIp( const snort::Packet* packet ) const;
	std::string getServerIp( const snort::Packet* packet ) const;
	PegCount getPacketsCount() const;
	bool validate( const snort::Packet* packet ) const;

	std::shared_ptr< Config > m_config;
	Detector::ModuleConf* m_module{ nullptr };
	bool m_initStaus{ false };
};
} // namespace Detector