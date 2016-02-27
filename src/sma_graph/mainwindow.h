#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/*!
 * \brief Fenêtre principale
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void show();
    ~MainWindow();

private:
    Ui::MainWindow *ui; //!< Interface utilisateur, contient les différents objets et la structure.
};

#endif // MAINWINDOW_H
