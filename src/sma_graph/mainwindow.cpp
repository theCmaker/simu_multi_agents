#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Simulation Multi-Agents");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * \brief Affichage des objets contenus dans la fenêtre
 */
void MainWindow::show()
{
    QMainWindow::show();
    ui->displayer->display_world();
}

