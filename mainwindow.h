#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamepadserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void catchGamepadState(const GamepadState & gps, const int & playerId);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
