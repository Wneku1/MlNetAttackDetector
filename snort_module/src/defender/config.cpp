#include "config.hpp"

using namespace Defender;

Config::Config() = default;
Config::~Config() = default;

Config::operator std::string() const
{
  std::string msg{};
  msg += "{\n hello: 2\n}";
  return msg;
}