#include "../Config.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/ShaderLayer.hpp>

using namespace geode::prelude;

class $modify(SodiumShaderLayer, ShaderLayer) {
    void visit() {
        auto const& cfg = SodiumConfig::get();
        if (cfg.bypassShaders && cfg.inPlayLayer) {
            // Bypass ShaderLayer's off-screen FBO render-to-texture pass and full-screen
            // post-processing shaders; render children directly to the main framebuffer.
            CCLayer::visit();
            return;
        }

        ShaderLayer::visit();
    }
};
