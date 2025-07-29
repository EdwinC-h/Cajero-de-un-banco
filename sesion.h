#ifndef SESION_H
#define SESION_H

#include <QDialog>

namespace Ui {
class Sesion;
}

class Sesion : public QDialog
{
    Q_OBJECT

public:
    explicit Sesion(QWidget *parent = nullptr);
    ~Sesion();

private slots:
    void on_btnIngresar_clicked();

    void on_Consultar_clicked();

    void on_Depositar_clicked();

    void on_Retirar_clicked();

    void on_CambiarPin_clicked();

    void on_Salir_clicked();

private:
    Ui::Sesion *ui;
    QString pin;
    double saldo;
    double actualSaldo;
    QString cuentaUsuario;
    QString pinGuardado;
};
#endif // SESION_H
