#ifndef GAMEPADSERVER_H
#define GAMEPADSERVER_H

#include <QObject>

#include "gamepadstate.h"

class GamepadServer : public QObject
{
    Q_OBJECT

public:
    static GamepadServer & instance() {
        if (s_instance == nullptr) {
            s_instance = new GamepadServer();
        }
        return *s_instance;
    }

signals:
    void stateUpdate(const GamepadState & gps, const int & player);

protected slots:
    void readState();

private:
    GamepadServer();

    static GamepadServer * s_instance;
};

#endif // GAMEPADSERVER_H
