# SodiumGD — Mod Tối Ưu Hiệu Năng Mạnh Nhất Cho Geometry Dash (Geode)

**SodiumGD** là mod Geode tối ưu hoá rendering, shader, particle, object và culling cho Geometry Dash — lấy cảm hứng từ **Sodium** trong Minecraft.

## Tính năng tối ưu hoá

| Nhóm tối ưu | Cơ chế hoạt động | Tác động FPS |
|---|---|---|
| **Zero-Overhead Config Cache** | Toàn bộ cài đặt được cache trong struct C++ thuần (không tra cứu map/setting mỗi frame) | Giảm overhead CPU về ~0 |
| **Bypass Level Shaders (`ShaderLayer`)** | Bỏ qua bước render vào FBO off-screen và các fragment shader 2.2 nặng | Rất cao (đặc biệt các màn 2.2 nhiều shader) |
| **Disable Object Glow** | Tắt toàn bộ lớp glow additive (`m_hasNoGlow = true`) gây overdraw GPU | Rất cao |
| **Ultra-LDM & Strip Decorations** | Chặn object High-Detail hoặc toàn bộ object trang trí (`GameObjectType::Decoration`) ngay từ lúc load `PlayLayer::addObject` mà **giữ nguyên 100% vật lý, hitbox, trigger, portal, orb, pad** | Cực cao (giảm RAM + CPU + GPU) |
| **Particle Throttling / Disable** | Giới hạn số hạt (`Reduced`) hoặc tắt hoàn toàn mô phỏng CPU & vẽ GPU của `CCParticleSystem` khi đang chơi | Cao |
| **Aggressive Node Culling** | Bỏ qua sớm các `CCNode` ẩn hoặc `scale == 0` trước khi tính ma trận OpenGL | Trung bình – Cao |
| **Hide BG / Middleground / Ground** | Ẩn lớp nền và mặt đất để triệt tiêu full-screen overdraw | Trung bình |
| **Auto-Purge Unused Textures** | Tự động giải phóng texture OpenGL không dùng sau khi thoát màn (`PlayLayer::onQuit`) | Giảm giật/lag do tràn RAM |
| **Windows High Priority** | Nâng ưu tiên tiến trình GD lên `HIGH_PRIORITY_CLASS` trên Windows | Giảm tụt FPS bất chợt (micro-stutter) |
| **FPS & Frame-Time HUD** | Hiển thị FPS & frame-time (ms) gọn nhẹ, chỉ cập nhật 4 lần/giây | Gần như 0% CPU |

## Các Preset nhanh trong Geode Settings

- **Balanced** *(mặc định)*: Tắt Glow + Bypass Shader + Ultra-LDM + Giảm Particle + Fast Culling. Tăng FPS mạnh nhưng vẫn giữ thẩm mỹ màn chơi.
- **Performance**: Thêm tắt hiệu ứng enter/exit object, tắt toàn bộ Particle và Player Glow/Trail.
- **Extreme**: Chế độ "Khoai Tây / Layout" — xoá toàn bộ object trang trí, ẩn BG/Ground để đạt FPS tối đa.
- **Custom**: Tự tuỳ chỉnh từng công tắc riêng lẻ.

---

## Cách Build ra file `.geode`

### Cách 1: Build tự động trên GitHub (Không cần cài Visual Studio hay Geode SDK trên máy)
1. Push thư mục `SodiumGD` này lên một repository GitHub mới.
2. Vào tab **Actions** → workflow **Build SodiumGD** sẽ tự động build file `.geode` cho cả **Windows, Android (32/64-bit), macOS và iOS**.
3. Tải file `sodium.gd-optimizer.geode` trong mục **Artifacts** về và chép vào thư mục `geode/mods/` của Geometry Dash.

### Cách 2: Build trực tiếp trên Windows
1. Cài **Visual Studio 2022** (chọn workload *Desktop development with C++*), **CMake**, và **Geode CLI** (https://docs.geode-sdk.org/getting-started/installation).
2. Cài Geode SDK:
   ```powershell
   geode sdk install
   ```
3. Mở terminal trong thư mục `SodiumGD` và chạy:
   ```powershell
   geode build
   ```
4. File `.geode` sẽ tự động được đóng gói (và copy thẳng vào thư mục mod của Geometry Dash nếu đã cấu hình đường dẫn game trong Geode CLI).
