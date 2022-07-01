#pragma once

#include <string>

namespace snort {
class Value;
}

namespace Defender {
class Config final
{
public:
  explicit Config();
  ~Config();

  operator std::string() const;
};

}// namespace Defender
