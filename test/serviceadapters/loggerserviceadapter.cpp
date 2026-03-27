#include <sstream>
#include <stdexcept>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/ostream_sink.h>

#include "loggerservice/loggerservice.hpp"

#include "loggerserviceadapter.hpp"

namespace LoggerServiceAdapter
{
    std::ostringstream oss;

    void useOnlyTestSink()
    {
        auto& instance = LoggerService::getInstance();
        auto  pattern = instance.getPattern();
        auto  logger = instance.expose();
        logger->sinks().clear();

        auto ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(oss);
        ostream_sink->set_pattern(pattern.c_str());
        logger->sinks().push_back(ostream_sink);
    }

    std::ostringstream& getTestSinkStream()
    {
        return oss;
    }
}
