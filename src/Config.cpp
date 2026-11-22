#include "Config.hpp"

#include <Geode/Geode.hpp>
#include <Geode/loader/SettingV3.hpp>

#ifdef GEODE_IS_WINDOWS
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
#endif

using namespace geode::prelude;

SodiumConfig& SodiumConfig::get() {
    static SodiumConfig instance;
    return instance;
}

static ParticleMode parseParticleMode(std::string const& mode) {
    if (mode == "Disabled") return ParticleMode::Disabled;
    if (mode == "Reduced") return ParticleMode::Reduced;
    return ParticleMode::Vanilla;
}

void SodiumConfig::reloadFromMod() {
    auto* mod = Mod::get();
    if (!mod) return;

    auto preset = mod->getSettingValue<std::string>("preset");

    // Always read HUD & system preferences directly
    autoPurgeTextures = mod->getSettingValue<bool>("auto-purge-textures");
    highProcessPriority = mod->getSettingValue<bool>("high-process-priority");
    showFpsHud = mod->getSettingValue<bool>("show-fps-hud");
    particleCap = static_cast<int>(mod->getSettingValue<int64_t>("particle-cap"));

    if (preset == "Balanced") {
        noGlow = true;
        bypassShaders = true;
        fastCulling = true;
        noObjectEffects = false;
        hideBgGround = false;
        ultraLdm = true;
        stripDecorations = false;
        particleMode = ParticleMode::Reduced;
        noPlayerParticles = true;
        noPlayerGlow = false;
    } else if (preset == "Performance") {
        noGlow = true;
        bypassShaders = true;
        fastCulling = true;
        noObjectEffects = true;
        hideBgGround = false;
        ultraLdm = true;
        stripDecorations = false;
        particleMode = ParticleMode::Disabled;
        noPlayerParticles = true;
        noPlayerGlow = true;
    } else if (preset == "Extreme") {
        noGlow = true;
        bypassShaders = true;
        fastCulling = true;
        noObjectEffects = true;
        hideBgGround = true;
        ultraLdm = true;
        stripDecorations = true;
        particleMode = ParticleMode::Disabled;
        noPlayerParticles = true;
        noPlayerGlow = true;
    } else {
        // Custom
        noGlow = mod->getSettingValue<bool>("no-glow");
        bypassShaders = mod->getSettingValue<bool>("bypass-shaders");
        fastCulling = mod->getSettingValue<bool>("fast-culling");
        noObjectEffects = mod->getSettingValue<bool>("no-object-effects");
        hideBgGround = mod->getSettingValue<bool>("hide-bg-ground");
        ultraLdm = mod->getSettingValue<bool>("ultra-ldm");
        stripDecorations = mod->getSettingValue<bool>("strip-decorations");
        particleMode = parseParticleMode(mod->getSettingValue<std::string>("particle-mode"));
        noPlayerParticles = mod->getSettingValue<bool>("no-player-particles");
        noPlayerGlow = mod->getSettingValue<bool>("no-player-glow");
    }

    applyProcessPriority();
}

void SodiumConfig::applyProcessPriority() {
#ifdef GEODE_IS_WINDOWS
    DWORD targetClass = highProcessPriority ? HIGH_PRIORITY_CLASS : NORMAL_PRIORITY_CLASS;
    SetPriorityClass(GetCurrentProcess(), targetClass);
#endif
}
