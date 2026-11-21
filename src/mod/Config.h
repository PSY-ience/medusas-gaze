
#pragma once

#include <string_view>

#include <pl/Config.hpp>

namespace medusas_gaze {

struct ModConfig {
    int version = 1;

    bool enabled = true;

    float range = 10.0f;

    float transformationDuration = 3.0f;

    bool affectPlayers = false;
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace medusas_gaze

template <> struct pl::config::Schema<medusas_gaze::ModConfig> {
    static constexpr std::string_view title = "Medusa's Gaze Config";
    static constexpr std::string_view description = "Configure Medusa's petrification ability.";

    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};

        if (name == "enabled")
            return {.title = "Enabled", .description = "Turns Medusa's Gaze on or off."};

        if (name == "range")
            return {.title = "Gaze Range", .description = "Maximum petrification distance in blocks."};

        if (name == "transformationDuration")
            return {.title = "Transformation Duration", .description = "Time required to petrify a target, in seconds."};

        if (name == "affectPlayers")
            return {.title = "Affect Players", .description = "Whether player entities can be petrified."};

        return {};
    }
};
