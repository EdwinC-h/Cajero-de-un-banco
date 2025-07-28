#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registro.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_RegistrarCuenta_clicked()
{
    Registro *ventanaRegistro = new Registro();
    ventanaRegistro->show();
    this->hide();
}

void MainWindow::on_IniciarSesion_clicked()
{

}

void MainWindow::on_Salir1_clicked()
{

}

