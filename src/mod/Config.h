
#pragma once

#include <string>
#include <string_view>

#include <pl/Config.hpp>

namespace medusas_gaze {

struct ModConfig {
    int version = 1;
    bool enabled = true;
    std::string message = "Medusa's Gaze is ready!";
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace medusas_gaze

template <> struct pl::config::Schema<medusas_gaze::ModConfig> {
    static constexpr std::string_view title = "Medusa's Gaze Config";
    static constexpr std::string_view description = {};

    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};
        if (name == "enabled")
            return {.title = "Enabled", .description = "Turns Medusa's Gaze on or off."};
        if (name == "message")
            return {.title = "Message", .description = "Message displayed by the mod."};
        return {};
    }
};
