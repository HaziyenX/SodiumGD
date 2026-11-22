#include "../Config.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/CCParticleSystem.hpp>
#include <Geode/modify/CCParticleSystemQuad.hpp>
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

class $modify(SodiumParticleSystem, CCParticleSystem) {
    void update(float dt) {
        auto const& cfg = SodiumConfig::get();
        if (!cfg.inPlayLayer || cfg.particleMode == ParticleMode::Vanilla) {
            CCParticleSystem::update(dt);
            return;
        }

        if (cfg.particleMode == ParticleMode::Disabled) {
            // Completely skip CPU-side particle physics and emitter updates during gameplay.
            if (m_uParticleCount > 0) {
                m_uParticleCount = 0;
            }
            return;
        }

        // Reduced mode: cap active particles per system to bound CPU/GPU cost.
        unsigned int const cap = static_cast<unsigned int>(cfg.particleCap > 0 ? cfg.particleCap : 1);
        if (m_uParticleCount > cap) {
            m_uParticleCount = cap;
        }

        CCParticleSystem::update(dt);
    }
};

class $modify(SodiumParticleSystemQuad, CCParticleSystemQuad) {
    void draw() {
        auto const& cfg = SodiumConfig::get();
        if (cfg.inPlayLayer && cfg.particleMode == ParticleMode::Disabled) {
            // Skip OpenGL vertex upload & draw call completely.
            return;
        }

        CCParticleSystemQuad::draw();
    }
};

class $modify(SodiumPlayerObject, PlayerObject) {
    void activateStreak() {
        if (SodiumConfig::get().noPlayerGlow) {
            return;
        }
        PlayerObject::activateStreak();
    }

    void updateGlowColor() {
        PlayerObject::updateGlowColor();
        if (SodiumConfig::get().noPlayerGlow && m_iconGlow) {
            m_iconGlow->setVisible(false);
        }
    }

    void update(float dt) {
        PlayerObject::update(dt);

        auto const& cfg = SodiumConfig::get();
        if (cfg.noPlayerParticles) {
            if (m_playerGroundParticles) m_playerGroundParticles->setVisible(false);
            if (m_trailingParticles) m_trailingParticles->setVisible(false);
            if (m_shipClickParticles) m_shipClickParticles->setVisible(false);
            if (m_vehicleGroundParticles) m_vehicleGroundParticles->setVisible(false);
            if (m_ufoClickParticles) m_ufoClickParticles->setVisible(false);
            if (m_robotBurstParticles) m_robotBurstParticles->setVisible(false);
            if (m_dashParticles) m_dashParticles->setVisible(false);
            if (m_swingBurstParticles1) m_swingBurstParticles1->setVisible(false);
            if (m_swingBurstParticles2) m_swingBurstParticles2->setVisible(false);
            if (m_landParticles0) m_landParticles0->setVisible(false);
            if (m_landParticles1) m_landParticles1->setVisible(false);
        }

        if (cfg.noPlayerGlow) {
            if (m_iconGlow) m_iconGlow->setVisible(false);
            if (m_regularTrail) m_regularTrail->setVisible(false);
        }
    }
};
