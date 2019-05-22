#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string>
#include <sstream>
#include <iostream>

#include <QtSql/QSqlQuery>
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* Open database */

    path = "Proyecto_1.db" ;
    int rc;

    rc = sqlite3_open(path.c_str(), &database);

    CrearBD();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CrearBD()
{
    stringstream sqlstream;
    char *zErrMsg = 0;
    int rc;
    sqlstream << "CREATE TABLE IF NOT EXISTS datos (id_dato INTEGER PRIMARY KEY NOT NULL,";
    sqlstream << "nombre TEXT NOT NULL,apellido TEXT NOT NULL,";
    sqlstream << "documento INTEGER NOT NULL,fecha_n INTEGER NOT NULL);";

    /* Execute SQL statement */
    rc = sqlite3_exec(database, sqlstream.str().c_str(), 0, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    }
       sqlstream.str("");
       sqlstream << "CREATE TABLE IF NOT EXISTS ingreso (usuario TEXT NOT NULL,";
       sqlstream << "contraseña TEXT NOT NULL); ";


       /* Execute SQL statement */
       rc = sqlite3_exec(database, sqlstream.str().c_str(), 0, 0, &zErrMsg);

       if( rc != SQLITE_OK ){
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
       }

       sqlstream.str("");

       sqlstream << "CREATE TABLE IF NOT EXISTS estados (n INTEGER PRIMARY KEY NOT NULL, ";
       sqlstream << "fecha INTEGER NOT NULL, hora INTEGER NOT NULL, ";
       sqlstream << "usuario TEXT NOT NULL);";

       /* Execute SQL statement */
       rc = sqlite3_exec(database, sqlstream.str().c_str(), 0, 0, &zErrMsg);

       if( rc != SQLITE_OK ){
          fprintf(stderr, "SQL error: %s\n", zErrMsg);
          sqlite3_free(zErrMsg);
       }

}

void MainWindow::guardar_datos()
{

   stringstream sqlstream;
       int rc;
       char *zErrMsg = 0;
     string uname,lastnm,ruser,rpsw;
       int date,doc;

       uname =ui->cmdNombre->text().toStdString();
       lastnm =ui->cmdApellido->text().toStdString();
       doc =ui->cmdDocumento->text().toInt();
       date =ui->cmdFecha->text().toInt();
       ruser =ui->cmdregusu->text().toStdString();
       rpsw =ui->cmdregcont->text().toStdString();


       /* Create SQL statement */
                 sqlstream << "INSERT INTO datos(nombre ,apellido ,documento,";
                 sqlstream << " fecha_n) VALUES ( " ;
                 sqlstream << "'"+uname+"'"  <<  ",";
                 sqlstream << "'"+lastnm +"'"<<  ",";
                 sqlstream << doc    <<  ",";
                 sqlstream << date  <<  ");";

           cout <<date;
           sqlstream << "INSERT INTO ingreso(usuario, contraseña) VALUES (";
           sqlstream <<"'"+ ruser+"'" <<  ",";
           sqlstream <<"'"+rpsw+ "'"<< "); " ;



           string sql( sqlstream.str() );
           /* Execute SQL statement */
           rc = sqlite3_exec(database, sql.c_str(), 0, 0, &zErrMsg);
           if( rc != SQLITE_OK ){
              fprintf(stderr, "SQL error: %s\n", zErrMsg);
              sqlite3_free(zErrMsg);
              //return false;
           }



}



void MainWindow::verificar()
{  stringstream sqlstream;
   string uname, pssw;
   char *zErrMsg = 0;
    uname=ui->cmdingusu->text().toStdString();
    pssw=ui->cmdingcont->text().toStdString();
    int rc;
    string uing;
    rc = sqlite3_open("Proyecto_1.db", &database);
    sqlstream << "SELECT usuario ";
    sqlstream << "FROM ingreso WHERE usuario ='"+uname+"' and contraseña='"+pssw+"';";

    /* Execute SQL statement */

    rc = sqlite3_exec(database, sqlstream.str().c_str(),0, & uing , &zErrMsg);

    if( rc != SQLITE_OK ){
       fprintf(stderr, "SQL error: %s\n", zErrMsg);
       sqlite3_free(zErrMsg);
    } else{fprintf(stderr,"select realizado", zErrMsg);}
 cout << uing<<"lol";




}




void MainWindow::on_cmdRegistrar_clicked()
{
    guardar_datos();

}


void MainWindow::on_pushButton_clicked()
{
    verificar();
}
