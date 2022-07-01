#include <memory>

#include "detection/detection_engine.h"
#include "inspector.hpp"
#include "module.hpp"

#include <iostream>

using namespace snort;
using namespace Defender;

static Module *mod_ctor() { return new ModuleConf; }

static void mod_dtor(Module *module) { delete module; }

static Inspector *heu_ctor(Module *module)
{
  ModuleConf *Module{ dynamic_cast<ModuleConf *>(module) };
  auto inspector{ new InspectorConf(Module->get_config(), Module) };

  Module->setInspector(inspector);
  return inspector;
}

static void heu_dtor(Inspector *inspector) { delete inspector; }

static const InspectApi heuristic_api = {
  { PT_INSPECTOR,
    sizeof(InspectApi),
    INSAPI_VERSION,
    0,
    API_RESERVED,
    API_OPTIONS,
    Defender::ModuleConf::getName().data(),
    Defender::ModuleConf::getHelp().data(),
    mod_ctor,
    mod_dtor },
  IT_NETWORK,
  PROTO_BIT__ALL,
  nullptr,// buffers
  nullptr,// service
  nullptr,// pinit
  nullptr,// pterm
  nullptr,// tinit
  nullptr,// tterm
  heu_ctor,
  heu_dtor,
  nullptr,// ssn
  nullptr,// reset
};

SO_PUBLIC const BaseApi *snort_plugins[] = { &heuristic_api.base, nullptr };
