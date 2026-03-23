#ifndef ENTRYPOINT_SCHEMAEXPORT_HPP
#define ENTRYPOINT_SCHEMAEXPORT_HPP

struct BaseModeDefinition;

namespace SchemaExportMode
{
    void run(const std::shared_ptr<const BaseModeDefinition>& defs);
}

#endif // ENTRYPOINT_HPP
