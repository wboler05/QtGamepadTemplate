#ifndef GAMEPADSTATE_H
#define GAMEPADSTATE_H

#include <cinttypes>

class GamepadState
{
public:

    // Joystick Definition
    struct JoyStick {
        int16_t xAxis = 0;
        int16_t yAxis = 0;
        bool pressed=false;
    };

    GamepadState();
    void updateButtonPress(const uint32_t & btn);

    // Player Buttons
    bool m_pad_a = false;
    bool m_pad_b = false;
    bool m_pad_x = false;
    bool m_pad_y = false;

    // Shoulder Buttons
    bool m_rShoulder = false;
    bool m_lShoulder = false;

    // Trigger Buttons
    uint8_t m_rTrigger = 0;
    uint8_t m_lTrigger = 0;

    // Directional Buttons
    bool m_pad_up = false;
    bool m_pad_down = false;
    bool m_pad_left = false;
    bool m_pad_right = false;

    // Meta Buttons
    bool m_pad_start = false;
    bool m_pad_back = false;

    // Joysticks
    JoyStick m_lThumb;
    JoyStick m_rThumb;

};

#endif // GAMEPADSTATE_H
