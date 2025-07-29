#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registro.h"
#include "sesion.h"
#include <QMessageBox>

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
    Sesion *ventanaSesion = new Sesion();
    ventanaSesion->show();this->hide();
}

void MainWindow::on_Salir1_clicked()
{
    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Confirmación",
                                      "¿Estás seguro de que deseas salir?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::Yes) {
        QApplication::quit();
    }
}
