#include "sesion.h"
#include "ui_sesion.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QDateTime>
#include <QDebug> // para diagnóstico visual

Sesion::Sesion(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::Sesion)
{
    ui->setupUi(this);

    actualSaldo = 0;
    cuentaUsuario = "";
    pinGuardado = "";
}

Sesion::~Sesion()
{
    delete ui;
}

void Sesion::on_btnIngresar_clicked()
{
    QString usuario = ui->txtUsuario->text();
    QString pinIngresado = ui->txtPin->text();

    if (usuario.isEmpty() || pinIngresado.isEmpty()) {
        QMessageBox::warning(this, "Campos vacíos", "Por favor, ingresa tu usuario y PIN.");
        return;
    }
    QFile archivo("cuentas.txt");
    if (!archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo de cuentas.");
        return;
    }

    QTextStream in(&archivo);
    bool valido = false;
    while (!in.atEnd()) {
        QString linea = in.readLine();
        QStringList partes = linea.split(",");
        if (partes.size() >= 6 && partes[2] == usuario && partes[3] == pinIngresado) {
            valido = true;
            actualSaldo = partes[5].toDouble();
            pinGuardado = partes[3];
            cuentaUsuario = partes[0]; // ✅ Asegura que la cuenta esté identificada
            break;
        }
    }
    archivo.close();

    if (valido) {
        ui->stackedWidget->setCurrentIndex(1);
        QMessageBox::information(this, "Bienvenido", "Inicio de sesión exitoso.");
    } else {
        QMessageBox::warning(this, "Error", "Usuario o PIN incorrecto.");
    }
}

void Sesion::on_Consultar_clicked()
{
    QString mensaje = "Tu saldo actual es: $" + QString::number(actualSaldo, 'f', 2);
    QMessageBox::information(this, "Consulta de Saldo", mensaje);
}

void Sesion::on_Depositar_clicked()
{
    bool ok;
    double monto = QInputDialog::getDouble(this, "Depositar",
                                           "¿Cuánto deseas depositar?",
                                           0, 0, 100000, 2, &ok);
    if (!ok || monto <= 0) {
        QMessageBox::warning(this, "Error", "Monto inválido o cancelado.");
        return;
    }

    actualSaldo += monto;

    QMessageBox::information(this, "Depósito exitoso",
                             QString("Se han depositado $%1.\nNuevo saldo: $%2")
                                 .arg(monto, 0, 'f', 2)
                                 .arg(actualSaldo, 0, 'f', 2));

    QFile archivo("cuentas.txt");
    if (!archivo.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    QTextStream inOut(&archivo);
    QString contenido;
    while (!inOut.atEnd()) {
        QString linea = inOut.readLine();
        QStringList partes = linea.split(",");

        if (partes[0] == cuentaUsuario) {
            partes[5] = QString::number(actualSaldo, 'f', 2); // ✅ saldo está en posición 5
        }

        contenido += partes.join(",") + "\n";
    }
    archivo.resize(0);
    inOut << contenido;
    archivo.close();
}

void Sesion::on_Retirar_clicked()
{
    bool ok;
    double monto = QInputDialog::getDouble(this, "Retirar",
                                           "¿Cuánto deseas retirar?",
                                           0, 0, 100000, 2, &ok);
    if (!ok || monto <= 0) {
        QMessageBox::warning(this, "Error", "Monto inválido o cancelado.");
        return;
    }

    if (monto > actualSaldo) {
        QMessageBox::warning(this, "Fondos insuficientes",
                             QString("Tu saldo es $%1, y estás intentando retirar $%2.")
                                 .arg(actualSaldo, 0, 'f', 2)
                                 .arg(monto, 0, 'f', 2));
        return;
    }

    actualSaldo -= monto;

    QMessageBox::information(this, "Retiro exitoso",
                             QString("Retiraste $%1.\nNuevo saldo: $%2")
                                 .arg(monto, 0, 'f', 2)
                                 .arg(actualSaldo, 0, 'f', 2));

    QFile archivo("cuentas.txt");
    if (archivo.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream inOut(&archivo);
        QString contenido;
        while (!inOut.atEnd()) {
            QString linea = inOut.readLine();
            QStringList partes = linea.split(",");

            if (partes[0] == cuentaUsuario) {
                partes[5] = QString::number(actualSaldo, 'f', 2); // ✅ posición del saldo
            }

            contenido += partes.join(",") + "\n";
        }

        archivo.resize(0);
        inOut << contenido;
        archivo.close();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo.");
    }
}

void Sesion::on_CambiarPin_clicked()
{
    bool ok;
    QString pinIngresado = QInputDialog::getText(this, "Verificación",
                                                 "Ingresa tu PIN actual:",
                                                 QLineEdit::Password, "", &ok);

    if (!ok || pinIngresado != pinGuardado) {
        QMessageBox::warning(this, "PIN incorrecto",
                             "El PIN ingresado no coincide con el registrado.");
        return;
    }

    QString nuevoPin = QInputDialog::getText(this, "Nuevo PIN",
                                        "Ingresa tu nuevo PIN (4 dígitos):",
                                        QLineEdit::Normal, "", &ok);

    if (!ok || nuevoPin.length() != 4 || !nuevoPin.toInt()) {
        QMessageBox::warning(this, "Error",
                             "PIN inválido. Debe contener 4 dígitos numéricos.");
        return;
    }

    QFile archivo("cuentas.txt");
    if (archivo.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream inOut(&archivo);
        QString contenido;

        while (!inOut.atEnd()) {
            QString linea = inOut.readLine();
            QStringList partes = linea.split(",");

            qDebug() << "⏳ Original:" << linea;

            if (partes.size() >= 6 && partes[0] == cuentaUsuario) {
                partes[3] = nuevoPin; //
                pinGuardado = nuevoPin;
                qDebug() << "Modificado:" << partes.join(",");
            }

            contenido += partes.join(",") + "\n";
        }

        archivo.resize(0);
        inOut << contenido;
        archivo.close();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo.");
        return;
    }

    QFile mov("movimientos.txt");
    if (mov.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream reg(&mov);
        QString fecha = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
        reg << cuentaUsuario << ",Cambio de PIN," << fecha << "\n";
        mov.close();
    }

    QMessageBox::information(this, "PIN actualizado", "Tu PIN ha sido modificado correctamente.");
    this->close();
    Sesion *sesion = new Sesion();
    sesion->show();
}

void Sesion::on_Salir_clicked()
{
    QMessageBox::information(this, "Cerrar sesión", "Has salido de tu cuenta.");
    this->close();
    Sesion *sesion = new Sesion();
    sesion->show();
}
