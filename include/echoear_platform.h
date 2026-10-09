#pragma once
#include <functional>

namespace echoear {
// No ESP-IDF, LVGL or Xiaozhi types cross this boundary.
struct BoardProfile {
    const char* display_name;
    int rotation;  // LVGL-compatible quarter turns: 0, 1, 2, 3.
    bool device_aec;
    bool sound_direction;
    int sd_clock, sd_command, sd_data;
};
class Host {
public:
    virtual ~Host() = default;
    virtual const BoardProfile& Profile() const = 0;
    virtual void Schedule(std::function<void()> callback) = 0;
    virtual void EnableVoice(bool enabled) = 0;
    virtual int Volume() const = 0;
    virtual int Brightness() const = 0;
    virtual void SetVolume(int value) = 0;
    virtual void SetBrightness(int value) = 0;
};
// Provided by the firmware integration, never by the portable component.
Host& GetHost();
}  // namespace echoear
