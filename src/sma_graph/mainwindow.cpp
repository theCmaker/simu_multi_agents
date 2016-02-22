#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qtimer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timerEvent()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::timerEvent()
{
    if (ui->displayer->play()) {
        ui->displayer->refresh();
    } else {
        timer->stop();
    }
}

void MainWindow::show()
{
    QMainWindow::show();
    ui->displayer->display_world();
}

