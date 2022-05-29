#include "inspector.hpp"
#include "config.hpp"
#include "module.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>

#include "log/messages.h"

using namespace snort;
using namespace Detector;

//-------------------------------------------------------------------------
// implementation stuff
//-------------------------------------------------------------------------
void InspectorConf::showConfig() const
{
	ConfigLogger::log_option( "detector" );
	if( m_config )
	{
		ConfigLogger::log_list( "", std::string( *m_config ).c_str() );
	}
}

//-------------------------------------------------------------------------
// class stuff
//-------------------------------------------------------------------------
InspectorConf::InspectorConf( const std::shared_ptr< Config >& config, ModuleConf* module )
	: m_config( config ), m_module( module )
{
}

InspectorConf::~InspectorConf() = default;

void InspectorConf::show( const SnortConfig* ) const
{
	showConfig();
}

bool InspectorConf::validate( const Packet* packet ) const
{
	if( !packet->flow )
	{
		return false;
	}

	return true;
}

std::string InspectorConf::getClientIp( const Packet* packet ) const
{
	char clientIp[ INET6_ADDRSTRLEN ];
	packet->flow->client_ip.ntop( clientIp, sizeof( clientIp ) );

	return clientIp;
}

std::string InspectorConf::getServerIp( const Packet* packet ) const
{
	char serverIp[ INET6_ADDRSTRLEN ];
	packet->flow->server_ip.ntop( serverIp, sizeof( serverIp ) );

	return serverIp;
}

PegCount InspectorConf::getPacketsCount() const
{
	return *m_module->get_counts();
}

void InspectorConf::printAttackInfo() const {}

void InspectorConf::eval( Packet* packet )
{
	if( !m_initStaus )
	{
		m_initStaus = true;
	}

	m_module->incrementPacketCounter();

	if( !validate( packet ) )
	{
		return;
	}

	const auto clientIp{ getClientIp( packet ) };
}
