#include "registro.h"
#include "ui_registro.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Registro::Registro(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Registro)
{
    ui->setupUi(this);
}

Registro::~Registro()
{
    delete ui;
}

void Registro::on_pushButton_clicked()
{
    if (ui->txtNombre->text().isEmpty() ||
        ui->txtUsuario->text().isEmpty() ||
        ui->txtPin->text().isEmpty() ||
        ui->txtTipo->text().isEmpty())
    {
        QMessageBox::warning(this, "Campos incompletos", "Por favor, completa todos los campos antes de continuar.");
        return;
    }
    struct Cuenta {
        QString numeroCuenta;
        QString nombre;
        QString usuario;
        QString pin;
        QString tipo;
        double dinero = 0;
    };

    Cuenta nueva;
    nueva.nombre = ui->txtNombre->text();
    nueva.usuario = ui->txtUsuario->text();
    nueva.pin = ui->txtPin->text();
    nueva.tipo = ui->txtTipo->text();
    nueva.numeroCuenta = QString::number(100000 + rand() % 900000);

    QFile archivo("cuentas.txt");
    if (archivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&archivo);
        out << nueva.numeroCuenta << ","<< nueva.nombre << ","
            << nueva.usuario << ","<< nueva.pin << ","<< nueva.tipo << ","<< nueva.dinero << "\n";
        archivo.close();

        ui->Resultado->setText("¡Registro exitoso! Número de cuenta: " + nueva.numeroCuenta);
        ui->recuerda->setText("Recuerda este número para futuras transacciones.");
        QMessageBox::information(this, "Cuenta creada", "Tu cuenta se ha guardado correctamente.");
        this->close();
    } else {
        QMessageBox::warning(this, "Error", "No se pudo guardar la cuenta.");
    }
}


