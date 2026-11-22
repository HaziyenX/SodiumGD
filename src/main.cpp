#include "Config.hpp"

#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>

using namespace geode::prelude;

$on_mod(Loaded) {
    auto& cfg = SodiumConfig::get();
    cfg.reloadFromMod();

    listenForAllSettingChanges([](std::string_view, std::shared_ptr<SettingV3>) {
        SodiumConfig::get().reloadFromMod();
    });

    log::info("SodiumGD initialized (preset: {})", Mod::get()->getSettingValue<std::string>("preset"));
}
