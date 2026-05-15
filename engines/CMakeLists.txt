cmake_minimum_required(VERSION 3.16)

# ============================================================================ #
# language definition

project(MonSta-Engine LANGUAGES
    CXX
    VERSION 0.1
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================================================ #
# source file definitions

# ---------------------------------------------------------------------------- #
# Engine Base

add_library(Engine-Base STATIC
    engine-base/base/clientapi.cpp

    engine-base/base/errors.hpp                                     engine-base/base/errors.cpp
    engine-base/base/errorbuffer.hpp                                engine-base/base/errorbuffer.cpp
    engine-base/base/globals.hpp                                    engine-base/base/globals.cpp
    engine-base/base/stringutils.hpp                                engine-base/base/stringutils.cpp

    engine-base/services/csvservice.hpp                             engine-base/services/csvservice.cpp
    engine-base/services/errorservice.hpp                           engine-base/services/errorservice.cpp
    engine-base/services/fileservice.hpp                            engine-base/services/fileservice.cpp
    engine-base/services/jsonservice.hpp
    engine-base/services/jsonservice/jsonwrapper.hpp                engine-base/services/jsonservice/jsonwrapper.cpp
    engine-base/services/jsonservice/jsonservice_database.hpp       engine-base/services/jsonservice/jsonservice_database.cpp
    engine-base/services/jsonservice/jsonservice_itemaccess.hpp     engine-base/services/jsonservice/jsonservice_itemaccess.cpp
    engine-base/services/jsonservice/jsonservice_schemabuilder.hpp  engine-base/services/jsonservice/jsonservice_schemabuilder.cpp
    engine-base/services/jsonservice/schemabuilder_wrapper.hpp      engine-base/services/jsonservice/schemabuilder_wrapper.cpp
    engine-base/services/loggerservice.hpp                          engine-base/services/loggerservice.cpp
    engine-base/services/memoryservice.hpp                          engine-base/services/memoryservice.cpp
    engine-base/services/rngservice.hpp                             engine-base/services/rngservice.cpp
    engine-base/services/services.hpp                               engine-base/services/services.cpp
    engine-base/services/versionservice.hpp                         engine-base/services/versionservice.cpp
)

target_include_directories(Engine-Base
    PRIVATE api
    PRIVATE engine-base
)

target_link_libraries(Engine-Base
    Api-Headers
)

set_target_properties(Engine-Base PROPERTIES POSITION_INDEPENDENT_CODE ON)

# ---------------------------------------------------------------------------- #
# Gen 1 Engine

add_library(Engine-Gen1 SHARED
    engine-gen1/clientapi.cpp

    engine-gen1/shared/schemavalidationconstants.hpp                engine-gen1/shared/schemavalidationconstants.cpp

    engine-gen1/shared/defs/experiencegroup.hpp                     engine-gen1/shared/defs/experiencegroup.cpp
    engine-gen1/shared/defs/hpamount.hpp                            engine-gen1/shared/defs/hpamount.cpp
    engine-gen1/shared/defs/mechanicsdefinition.hpp
    engine-gen1/shared/defs/optionprobabilitylist.hpp               engine-gen1/shared/defs/optionprobabilitylist.cpp
    engine-gen1/shared/defs/pokemondatabaseentry.hpp
    engine-gen1/shared/defs/pokemondefition.hpp
    engine-gen1/shared/defs/statuscondition.hpp                     engine-gen1/shared/defs/statuscondition.cpp
    engine-gen1/shared/defs/stat.hpp                                engine-gen1/shared/defs/stat.cpp
    engine-gen1/shared/defs/statstage.hpp                           engine-gen1/shared/defs/statstage.cpp
    engine-gen1/shared/defs/target.hpp                              engine-gen1/shared/defs/target.cpp
    engine-gen1/shared/defs/teamdefinition.hpp
    engine-gen1/shared/defs/typeinfo.hpp                            engine-gen1/shared/defs/typeinfo.cpp

    engine-gen1/shared/registry/pokemondatabase.hpp                 engine-gen1/shared/registry/pokemondatabase.cpp
    engine-gen1/shared/registry/registry.hpp                        engine-gen1/shared/registry/registry.cpp
    engine-gen1/shared/registry/setup.hpp                           engine-gen1/shared/registry/setup.cpp
    engine-gen1/shared/registry/typechart.hpp                       engine-gen1/shared/registry/typechart.cpp

    engine-gen1/shared/registry/effects/abstracteffecthandler.hpp   engine-gen1/shared/registry/effects/abstracteffecthandler.cpp
    engine-gen1/shared/registry/effects/accumulateandpayback.hpp        engine-gen1/shared/registry/effects/accumulateandpayback.cpp
    engine-gen1/shared/registry/effects/drain.hpp                   engine-gen1/shared/registry/effects/drain.cpp
    engine-gen1/shared/registry/effects/effecthandlerdescriptor.hpp
    engine-gen1/shared/registry/effects/multihit.hpp                engine-gen1/shared/registry/effects/multihit.cpp
    engine-gen1/shared/registry/effects/repeatmove.hpp              engine-gen1/shared/registry/effects/repeatmove.cpp
    engine-gen1/shared/registry/effects/requirecharge.hpp           engine-gen1/shared/registry/effects/requirecharge.cpp
    engine-gen1/shared/registry/effects/stage.hpp                   engine-gen1/shared/registry/effects/stage.cpp
    engine-gen1/shared/registry/effects/trap.hpp                    engine-gen1/shared/registry/effects/trap.cpp

    engine-gen1/shared/registry/moves/move.hpp                      engine-gen1/shared/registry/moves/move.cpp
    engine-gen1/shared/registry/moves/secondaryeffect.hpp

    engine-gen1/simulationmode/arena/damagecalculator.hpp           engine-gen1/simulationmode/arena/damagecalculator.cpp
    engine-gen1/simulationmode/arena/pokemoninstance.hpp            engine-gen1/simulationmode/arena/pokemoninstance.cpp
    engine-gen1/simulationmode/arena/scene.hpp                      engine-gen1/simulationmode/arena/scene.cpp

    engine-gen1/simulationmode/setup/mechanicsdefinitionsetup.hpp   engine-gen1/simulationmode/setup/mechanicsdefinitionsetup.cpp
    engine-gen1/simulationmode/setup/pokemondefinitionsetup.hpp     engine-gen1/simulationmode/setup/pokemondefinitionsetup.cpp
    engine-gen1/simulationmode/setup/setuperrorhandling.hpp         engine-gen1/simulationmode/setup/setuperrorhandling.cpp
    engine-gen1/simulationmode/setup/teamdefinitionsetup.hpp        engine-gen1/simulationmode/setup/teamdefinitionsetup.cpp
    engine-gen1/simulationmode/setup/typedefinitionsetup.hpp        engine-gen1/simulationmode/setup/typedefinitionsetup.cpp

    engine-gen1/simulationmode/simulationmode.hpp                   engine-gen1/simulationmode/simulationmode.cpp

    engine-gen1/templatesmode/allowedvalueswriter.hpp               engine-gen1/templatesmode/allowedvalueswriter.cpp
    engine-gen1/templatesmode/csvtemplateswriter.hpp                engine-gen1/templatesmode/csvtemplateswriter.cpp
    engine-gen1/templatesmode/jsontemplateswriter.hpp               engine-gen1/templatesmode/jsontemplateswriter.cpp
    engine-gen1/templatesmode/strategyfilewriter.hpp                engine-gen1/templatesmode/strategyfilewriter.cpp
    engine-gen1/templatesmode/templatesmode.hpp                     engine-gen1/templatesmode/templatesmode.cpp
)

target_link_libraries(Engine-Gen1 PUBLIC
    Engine-Base
    Api-Headers
)

target_include_directories(Engine-Gen1
    PRIVATE engine-gen1
    PRIVATE engine-base
    PRIVATE api
)
