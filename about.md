# SodiumGD

**SodiumGD** is an all-in-one, ultra-lightweight performance optimization mod for Geometry Dash (Geode), inspired by **Sodium** for Minecraft.

## Key Optimizations
- **Zero-Overhead Config Cache**: All settings are cached in plain C++ fields (no per-frame map lookups).
- **ShaderLayer FBO Bypass**: Skips expensive 2.2 off-screen render-to-texture shader passes.
- **Glow & Overdraw Removal**: Strips additive glow layers and optional BG/Middleground/Ground overdraw.
- **Ultra-LDM & Decoration Stripping**: Prevents high-detail or decorative objects from ever entering `PlayLayer` without breaking gameplay physics.
- **Particle Throttling & Disabling**: Caps or completely skips CPU-heavy `CCParticleSystem` updates and draws during gameplay.
- **Aggressive Node Culling**: Short-circuits invisible or zero-scale nodes before OpenGL matrix transforms.
- **Auto Texture Purge & Windows Priority Boost**: Keeps RAM usage clean and frame times consistent.
- **One-Click Presets**: Switch effortlessly between `Balanced`, `Performance`, `Extreme`, and `Custom`.
