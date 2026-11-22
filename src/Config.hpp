#pragma once

#include <cstdint>
#include <string>

enum class ParticleMode : uint8_t {
    Vanilla = 0,
    Reduced = 1,
    Disabled = 2,
};

struct SodiumConfig {
    // Rendering & Overdraw
    bool noGlow = true;
    bool bypassShaders = true;
    bool fastCulling = true;
    bool noObjectEffects = false;
    bool hideBgGround = false;

    // Level Objects
    bool ultraLdm = true;
    bool stripDecorations = false;

    // Particles & Player
    ParticleMode particleMode = ParticleMode::Reduced;
    int particleCap = 24;
    bool noPlayerParticles = true;
    bool noPlayerGlow = false;

    // System & HUD
    bool autoPurgeTextures = true;
    bool highProcessPriority = true;
    bool showFpsHud = true;

    // Runtime state (avoid calling PlayLayer::get() repeatedly in ultra-hot hooks)
    bool inPlayLayer = false;

    static SodiumConfig& get();
    void reloadFromMod();
    void applyProcessPriority();
};
