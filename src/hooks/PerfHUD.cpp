#include "../Config.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <fmt/format.h>

using namespace geode::prelude;

class $modify(SodiumPerfHudPlayLayer, PlayLayer) {
    struct Fields {
        CCLabelBMFont* fpsLabel = nullptr;
        float accumTime = 0.f;
        int frameCount = 0;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            return false;
        }

        auto winSize = CCDirector::sharedDirector()->getWinSize();
        auto* label = CCLabelBMFont::create("SodiumGD | -- FPS", "chatFont.fnt");
        if (label) {
            label->setID("sodium-fps-hud"_spr);
            label->setAnchorPoint({0.f, 1.f});
            label->setPosition({6.f, winSize.height - 6.f});
            label->setScale(0.55f);
            label->setOpacity(185);
            label->setZOrder(9999);
            label->setVisible(SodiumConfig::get().showFpsHud);
            this->addChild(label);
            m_fields->fpsLabel = label;
        }

        return true;
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);

        auto* label = m_fields->fpsLabel;
        if (!label) return;

        bool const shouldShow = SodiumConfig::get().showFpsHud;
        if (label->isVisible() != shouldShow) {
            label->setVisible(shouldShow);
        }
        if (!shouldShow) return;

        m_fields->accumTime += dt;
        m_fields->frameCount++;

        // Update text only 4 times per second so the HUD itself has near-zero overhead.
        if (m_fields->accumTime >= 0.25f) {
            float const avgDt = m_fields->accumTime / static_cast<float>(m_fields->frameCount);
            int const fps = avgDt > 0.0001f ? static_cast<int>(1.0f / avgDt + 0.5f) : 0;
            float const ms = avgDt * 1000.0f;

            label->setString(fmt::format("SodiumGD | {} FPS ({:.1f} ms)", fps, ms).c_str());

            m_fields->accumTime = 0.f;
            m_fields->frameCount = 0;
        }
    }
};
