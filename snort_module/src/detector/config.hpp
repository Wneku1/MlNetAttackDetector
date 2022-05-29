#pragma once
#include "parameters_name.hpp"
#include <map>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace snort
{
class Value;
}

/* Main policy configuration */

class Config
{

public:
	Config();
	~Config();

	operator std::string() const;

private:
};
