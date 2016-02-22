#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void show();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int timerId;
    QTimer *timer;

protected slots:
    void timerEvent();
};

#endif // MAINWINDOW_H
