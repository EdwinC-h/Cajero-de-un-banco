#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <wchar.h> 
#include <locale.h>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Cuenta{
	
	string numeroCuenta;
	string nombre;
	string usuario;
	string pin;
	string tipo;
	double dinero = 0;
	
};

//Apartado para la creacion de las cuentas
string generarNumeroCuenta(){
	
	srand(time(0));
	int numero = 100000 + rand() % 900000;
	return to_string(numero);
	 
}

void guardarCuentaEnArchivo(const Cuenta& cuenta) {
    ofstream archivo("cuentas.txt", ios::app);
    if (archivo.is_open()) {
        archivo<<cuenta.numeroCuenta<<","<<cuenta.nombre<<","<<cuenta.usuario<<","<<cuenta.pin<<","<<cuenta.tipo<<","<<cuenta.dinero<<endl;
    	archivo.close();
    	cout<<"Te registraste con exito.";
		cout<<"Tu numero de cuenta asignado es: "<<cuenta.numeroCuenta<<endl;  
	} else {
        cout << "No se pudo guardo la cuenta." << endl;
    }
}

Cuenta crearCuenta(){
	Cuenta nueva;
	
	cin.ignore();
	cout << "===Registro de Cuenta==="<<endl;
	cout<<"Ingreses sus nombres completos: "<<endl;getline(cin,nueva.nombre); 
	cout<<"Ingrese el nombre del usuario: "<<endl;getline(cin,nueva.usuario);
	cout<<"Ingreses el pin de 4 digitos: "<<endl;getline(cin,nueva.pin);
	cout<<"Ingrese el tipo de cuenta(ahorros/corriente): "<<endl;getline(cin,nueva.tipo);
	nueva.numeroCuenta = generarNumeroCuenta();
	
	return nueva;
}

void ejecutarRegistro(){
	Cuenta nueva = crearCuenta();
	guardarCuentaEnArchivo(nueva);
	
}

//Funciones para el inicio de sesion
bool logear(Cuenta &cuentaActiva){
	ifstream archivo("cuentas.txt");
	string linea;
	string nombreCuenta, contraseña;
	
	cin.ignore();
	cout<<"=== Iniciar Sesion ==="<<endl;
	cout<<"Usuario: ";getline(cin,nombreCuenta);
	cout<<"Contraseña: ";cin>>contraseña;
	

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string plata;
        Cuenta cuenta;

        getline(ss, cuenta.numeroCuenta, ',');
        getline(ss, cuenta.nombre, ',');
        getline(ss, cuenta.usuario, ',');
        getline(ss, cuenta.pin, ',');
        getline(ss, cuenta.tipo, ',');
        getline(ss, plata);

        cuenta.dinero = stod(plata);

        if (cuenta.usuario == nombreCuenta and cuenta.pin == contraseña) {
            cuentaActiva = cuenta;
            return true;
        }
    }
    return false;
}

void actualizarDatos(const Cuenta &cuenta){
	ifstream leerArchivo("cuentas.txt");
	ofstream temporal("temp.txt");
	
	string linea;
	while(getline(leerArchivo, linea)){
		stringstream ss(linea);
		string plata;
		Cuenta cuenta;
		
		getline(ss, cuenta.numeroCuenta, ',');
        getline(ss, cuenta.nombre, ',');
        getline(ss, cuenta.usuario, ',');
        getline(ss, cuenta.pin, ',');
        getline(ss, cuenta.tipo, ',');
        getline(ss, plata);

        cuenta.dinero = stod(plata);
        
        if (cuenta.numeroCuenta == cuenta.numeroCuenta) {
		    temporal<<cuenta.numeroCuenta<< "," <<cuenta.nombre<< "," <<cuenta.usuario << ","<< cuenta.pin << "," << cuenta.tipo << "," << cuenta.dinero << endl;
		}else{
		    temporal<<linea<<endl;
		}
	}
		
    leerArchivo.close();
    temporal.close();
    remove("cuentas.txt");
    rename("temp.txt", "cuentas.txt");
}



//Una vez iniciada la sesion, codigo del CRUD
void consultarSaldo(const Cuenta &cuenta) {
    cout << "Saldo actual: $" << cuenta.dinero << endl;
}

void depositar(Cuenta &cuenta, double deposito) {
    if (deposito > 0) {
        cuenta.dinero += deposito;
        cout << "Su deposito ha sido exitoso." << endl;
		actualizarDatos(cuenta);
        ofstream archivo("movimientos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Depositando ==> " << cuenta.numeroCuenta << "=" << deposito << endl;
            archivo.close();
        } else {
            cout<< "No se registro el movimiento." << endl;
        }
    } else {
        cout << "Monto invalido." << endl;
    }
}

void retirar(Cuenta &cuenta, double monto) { 
    if (monto > 0 and monto <= cuenta.dinero) { 
        cuenta.dinero -= monto;
        actualizarDatos(cuenta);
        cout << "Su retiro ha sido exitoso." << endl;

        ofstream archivo("movimientos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Retirando ==>" << cuenta.numeroCuenta << "=" << monto << endl;
            archivo.close();
        } else {
            cerr << "No se registro el movimiento." << endl;
        }
    } else {
        cout << "Fondos insuficientes o monto invalido." << endl;
    }
}


	

void menuPrincipal(){
	cout << "\n///////////////////////" << endl;
	cout << "BIENVENIDO A BANCO-CARD" <<endl;
	cout << "///////////////////////" <<endl;
	
	cout << "1. Registrarse" << endl;  
	cout << "2. Iniciar Sesion" <<endl; 
	cout << "3. Cambiar PIN" << endl;   
	cout << "4. Salir del sistema" <<endl;
	
}

void menuInicioSesion(){
	
	cout << "\n1. Consultar saldo" <<endl; // funciona bien
	cout << "2. Depositar dinero" <<endl; // funciona bien
	cout << "3. Retirar dinero" <<endl; //funciona bien
	cout << "4. Cerrar sesion"<<endl; 
	
	
}

void ejecutarMenuSesion(Cuenta &cuenta){
	
	int opcion2;
	double monto;
	
	do{
	menuInicioSesion();
	cout << "Ingresa una opcion: "; cin>>opcion2;
	
	switch (opcion2) {
		case 1:
			consultarSaldo(cuenta);
			break;
		case 2:
			cout<<"Ingrese el monto a depositar: " ; cin>>monto;
			depositar(cuenta, monto);
			break;
		case 3:
			cout<<"Ingrese el monto a retirar: " ; cin>>monto;
			retirar(cuenta, monto);
			break;
		case 4:
			cout << "Cerrando Sesion"<<endl;
			break;
		default:
			cout<<"Opcion no valida"<<endl;
	}
	
	} while(opcion2 != 4 ); 
		
	
}


void ejecutar(){
	int opcion;
	Cuenta cuenta;
	do{
	
	menuPrincipal();
	cout<<"Ingrese una de las opciones: "; cin>>opcion;
	
	switch (opcion) {
		case 1:
			ejecutarRegistro();
			break;
		case 2:
			{
				if(logear(cuenta)){
					cout<<"=== BIENVENIDO AL SISTEMA " <<cuenta.usuario<<" ==="<<endl;
					ejecutarMenuSesion(cuenta);
				}else{
					cout<<"Contraseña o usuario incorrectos."<<endl;
				}
			}
			break;
		case 3:
			cout<<"cambiar PIN"<<endl;
			break;
		case 4:
			cout <<"Saliendo del sistema"<<endl;
			break;
		default:
			cout<<"La opcion no es valida"<<endl;
			
		}
	} while(opcion != 4);
}

int main(){
	
	ejecutar();
	
	return 0;
}
