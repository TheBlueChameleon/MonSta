#ifndef EXPERIENCEGROUP_HPP
#define EXPERIENCEGROUP_HPP

#include <string_view>

namespace MetaDefinition
{
    constexpr auto FAST        = "Fast";
    constexpr auto MEDIUM_FAST = "Medium Fast";
    constexpr auto MEDIUM_SLOW = "Medium Slow";
    constexpr auto SLOW        = "Slow";

    enum class ExperienceGroup { FAST, MEDIUM_FAST, MEDIUM_SLOW, SLOW };

    ExperienceGroup getExperienceGroupFromName(const std::string_view name);
    std::string_view getExperienceGroupName(const ExperienceGroup experienceGroup);

} // namespace MetaDefinition

#endif // EXPERIENCEGROUP_HPP
