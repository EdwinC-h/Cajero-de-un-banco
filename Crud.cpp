#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

struct Cuenta {
    string numeroCuenta;
    string nombre;
    string usuario;
    string pin;
    string tipo;
	double saldo;
};



void consultarSaldo(Cuenta cuenta) {
    cout << "Saldo actual: $" << cuenta.saldo << endl;
}


void depositar(Cuenta &cuenta, double deposito) {
    if (deposito > 0) {
        cuenta.saldo += deposito;
        cout << "Deposito exitoso. Nuevo saldo: $" << cuenta.saldo << endl;

        ofstream archivo("movimientos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Deposito ==> " << cuenta.numeroCuenta << "=" << deposito << endl;
            archivo.close();
        } else {
            cout<< "No se pudo registrar el movimiento." << endl;
        }
    } else {
        cout << "Monto invalido." << endl;
    }
}


void retirar(Cuenta &cuenta, float monto) {
    if (monto > 0 && monto <= cuenta.saldo) {
        cuenta.saldo -= monto;
        cout << "Retiro exitoso. Nuevo saldo: $" << cuenta.saldo << endl;

        ofstream archivo("movimientos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Retiro|" << cuenta.numeroCuenta << "|" << monto << endl;
            archivo.close();
        } else {
            cerr << "No se pudo registrar el movimiento." << endl;
        }
    } else {
        cout << "Fondos insuficientes o monto invalido." << endl;
    }
}
int main() {
    // Cuenta de prueba (normalmente vendría desde el login)
    Cuenta miCuenta = {"123456", "Juan Sebastian", "500.0"};
    int opcion;
    float monto;
 
    do {
        cout << "\n--- MENU DE OPERACIONES ---" << endl;
        cout << "1. Consultar saldo" << endl;
        cout << "2. Depositar" << endl;
        cout << "3. Retirar" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                consultarSaldo(miCuenta);
                break;
            case 2:
                cout << "Ingrese monto a depositar: ";
                cin >> monto;
                depositar(miCuenta, monto);
                break;
            case 3:
                cout << "Ingrese monto a retirar: ";
                cin >> monto;
                retirar(miCuenta, monto);
                break;
            case 4:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }

    } while(opcion != 4);

    return 0;
}
