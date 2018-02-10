#include "gamepadserver.h"

#include <Windows.h>
#include <Xinput.h>

#include <QDebug>
#include <QTimer>

GamepadServer * GamepadServer::s_instance = nullptr;

// Local declarations
namespace GamepadServerLocal {
    void prepareStateToSend(GamepadState & gps, const XINPUT_STATE & xState);
    void updateButtonPress(GamepadState & gps, const uint32_t & btn);
    void setButton(bool & gamePadButtonState, const uint32_t & btn, const uint32_t & expectedValue);
    void updateAnalogs(GamepadState & gps, const XINPUT_GAMEPAD & xStatePad);
}

// Member defintions
GamepadServer::GamepadServer()
{
    QTimer * gameServerTimer = new QTimer(this);
    connect(gameServerTimer, SIGNAL(timeout()), this, SLOT(readState()));
    gameServerTimer->start(UPDATE_PERIOD_MS);
}

void GamepadServer::readState() {

    DWORD dwResult;
    for (DWORD i=0; i < XUSER_MAX_COUNT; i++) {
        XINPUT_STATE state;
        ZeroMemory( & state, sizeof(XINPUT_STATE));

        dwResult = XInputGetState(i, &state);
        if (dwResult == ERROR_SUCCESS) {
            //qDebug () << "Controller is connected.";
            GamepadState gps;
            GamepadServerLocal::prepareStateToSend(gps, state);
            emit stateUpdate(gps, i);
        } else {
            // Ignore everything in life... //
        }
    }
}


// Local Definitions

namespace GamepadServerLocal {

    void prepareStateToSend(GamepadState & gps, const XINPUT_STATE & xState) {
        updateButtonPress(gps, xState.Gamepad.wButtons);
        updateAnalogs(gps, xState.Gamepad);
    }

    void updateButtonPress(GamepadState & gps, const uint32_t & btn)
    {
        setButton(gps.m_pad_a, btn, XINPUT_GAMEPAD_A);
        setButton(gps.m_pad_b, btn, XINPUT_GAMEPAD_B);
        setButton(gps.m_pad_x, btn, XINPUT_GAMEPAD_X);
        setButton(gps.m_pad_y, btn, XINPUT_GAMEPAD_Y);
        setButton(gps.m_pad_up, btn, XINPUT_GAMEPAD_DPAD_UP);
        setButton(gps.m_pad_down, btn, XINPUT_GAMEPAD_DPAD_DOWN);
        setButton(gps.m_pad_left, btn, XINPUT_GAMEPAD_DPAD_LEFT);
        setButton(gps.m_pad_right, btn, XINPUT_GAMEPAD_DPAD_RIGHT);
        setButton(gps.m_pad_start, btn, XINPUT_GAMEPAD_START);
        setButton(gps.m_pad_back, btn, XINPUT_GAMEPAD_BACK);
        setButton(gps.m_lThumb.pressed, btn, XINPUT_GAMEPAD_LEFT_THUMB);
        setButton(gps.m_rThumb.pressed, btn, XINPUT_GAMEPAD_RIGHT_THUMB);
        setButton(gps.m_lShoulder, btn, XINPUT_GAMEPAD_LEFT_SHOULDER);
        setButton(gps.m_rShoulder, btn, XINPUT_GAMEPAD_RIGHT_SHOULDER);
    }

    void setButton(bool & gamePadButtonState, const uint32_t & btn, const uint32_t & expectedValue) {
        if ((btn & expectedValue) == expectedValue) {
            gamePadButtonState = true;
        } else {
            gamePadButtonState = false;
        }
    }

    void updateAnalogs(GamepadState & gps, const XINPUT_GAMEPAD & xStatePad) {
        gps.m_lTrigger = xStatePad.bLeftTrigger;
        gps.m_rTrigger = xStatePad.bRightTrigger;
        gps.m_lThumb.xAxis = xStatePad.sThumbLX;
        gps.m_lThumb.yAxis = xStatePad.sThumbLY;
        gps.m_rThumb.xAxis = xStatePad.sThumbRX;
        gps.m_rThumb.yAxis = xStatePad.sThumbRY;
    }

}
