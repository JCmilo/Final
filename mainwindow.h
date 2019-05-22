#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <sqlite3.h>
#include<QtSql>
#include<QFileInfo>


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void CrearBD();
     void guardar_datos();
     void verificar();


private slots:
     void on_cmdRegistrar_clicked();

     void on_pushButton_clicked();

private:
    string path;
    sqlite3 *database;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
