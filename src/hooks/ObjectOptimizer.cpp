#include "../Config.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(SodiumObjectPlayLayer, PlayLayer) {
    struct Fields {
        size_t strippedObjects = 0;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        auto& cfg = SodiumConfig::get();
        cfg.inPlayLayer = true;
        m_fields->strippedObjects = 0;

        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) {
            cfg.inPlayLayer = false;
            return false;
        }

        if (cfg.hideBgGround) {
            if (m_background) m_background->setVisible(false);
            if (m_groundLayer) m_groundLayer->setVisible(false);
            if (m_groundLayer2) m_groundLayer2->setVisible(false);
            if (m_middleground) m_middleground->setVisible(false);
        }

        if (m_fields->strippedObjects > 0) {
            log::debug("SodiumGD stripped {} decorative/high-detail objects", m_fields->strippedObjects);
        }

        return true;
    }

    void addObject(GameObject* obj) {
        if (!obj) {
            PlayLayer::addObject(obj);
            return;
        }

        auto const& cfg = SodiumConfig::get();

        // Only ever strip pure decorative objects (never EffectGameObject / triggers, portals,
        // orbs, pads, hazards, slopes, or solids) so gameplay physics remain 100% identical.
        bool const isPureDecoration =
            (obj->m_objectType == GameObjectType::Decoration) &&
            (typeinfo_cast<EffectGameObject*>(obj) == nullptr);

        if (isPureDecoration) {
            if (cfg.stripDecorations || (cfg.ultraLdm && obj->m_isHighDetail)) {
                m_fields->strippedObjects++;
                return;
            }
        }

        if (cfg.noGlow) {
            obj->m_hasNoGlow = true;
        }

        if (cfg.noObjectEffects) {
            obj->m_hasNoEffects = true;
        }

        PlayLayer::addObject(obj);
    }

    void onQuit() {
        auto& cfg = SodiumConfig::get();
        cfg.inPlayLayer = false;

        PlayLayer::onQuit();

        if (cfg.autoPurgeTextures) {
            if (auto* cache = CCTextureCache::sharedTextureCache()) {
                cache->removeUnusedTextures();
            }
        }
    }
};
