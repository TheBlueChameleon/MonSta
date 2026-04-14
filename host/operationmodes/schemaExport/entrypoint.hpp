#ifndef ENTRYPOINT_SCHEMAEXPORT_HPP
#define ENTRYPOINT_SCHEMAEXPORT_HPP

namespace OperationModes
{
    struct SchemaExportModeDefinition;
}

namespace SchemaExportMode
{
void run(const OperationModes::SchemaExportModeDefinition &defs);
}

#endif // ENTRYPOINT_HPP
