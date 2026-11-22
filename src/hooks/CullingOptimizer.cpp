#include "../Config.hpp"

#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>

using namespace geode::prelude;

class $modify(SodiumNodeCulling, CCNode) {
    void visit() {
        auto const& cfg = SodiumConfig::get();
        if (cfg.fastCulling) {
            // Fast-path early exit before Cocos2d-x pushes OpenGL matrix stack,
            // computes affine transforms, and traverses child lists.
            if (!m_bVisible) {
                return;
            }
            if (m_fScaleX == 0.f || m_fScaleY == 0.f) {
                return;
            }
        }

        CCNode::visit();
    }
};
