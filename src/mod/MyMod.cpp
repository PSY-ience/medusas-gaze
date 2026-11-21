
#include "mod/MyMod.h"

#include <filesystem>

#include <pl/Mod.hpp>

namespace medusas_gaze {

MedusasGazeMod &MedusasGazeMod::instance() {
    static MedusasGazeMod instance;
    return instance;
}

MedusasGazeMod::MedusasGazeMod() : mSelf(*ll::mod::NativeMod::current()) {}

bool MedusasGazeMod::load() {
    auto &self = getSelf();
    self.getLogger().debug("Loading Medusa's Gaze...");

    std::error_code ec;
    std::filesystem::create_directories(self.getDataDir(), ec);
    if (ec) {
        self.getLogger().error("Failed to create data directory {}: {}",
                               self.getDataDir().string(), ec.message());
        return false;
    }

    std::filesystem::create_directories(self.getConfigDir(), ec);
    if (ec) {
        self.getLogger().error("Failed to create config directory {}: {}",
                               self.getConfigDir().string(), ec.message());
        return false;
    }

    mConfigFile.emplace();
    if (!mConfigFile->load()) {
        self.getLogger().warn("Failed to load typed config");
        return false;
    }
    mConfig = mConfigFile->value();

    self.getLogger().info("Loaded {} from {}", self.getName(), self.getModDir().string());
    return true;
}


bool MedusasGazeMod::enable() {
    auto &self = getSelf();
    self.getLogger().debug("Enabling Medusa's Gaze...");

    if (!mConfig.enabled) {
        self.getLogger().info("medusas_gaze is disabled by config");
        return true;
    }

    mTickEventLogged = false;

    const bool subscribed = mTickListener.subscribe(
        [this](bedrocktools::events::LocalPlayerTickEvent &event) {
            if (!event.player || mTickEventLogged) {
                return;
            }

            getSelf().getLogger().info(
                "Medusa's Gaze detected the local player tick!"
            );

            mTickEventLogged = true;
        }
    );

    if (!subscribed) {
        self.getLogger().error(
            "Failed to subscribe to BedrockTools player tick event!"
        );
        return false;
    }

    self.getLogger().info("Medusa's Gaze is ready!");
    return true;
}


bool MedusasGazeMod::disable() {
    getSelf().getLogger().debug("Disabling Medusa's Gaze...");
    return true;
    mTickListener.reset();
}

bool MedusasGazeMod::unload() {
    getSelf().getLogger().debug("Unloading Medusa's Gaze...");
    mConfigFile.reset();
    return true;
}

} // namespace medusas_gaze
