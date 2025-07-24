#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Cuenta{
	
	string numeroCuenta;
	string nombre;
	string usuario;
	string pin;
	string tipo;
	double dinero = 0;
	
};


string generarNumeroCuenta(){
	
	srand(time(0));
	int numero = 100000 + rand() % 900000;
	return to_string(numero);
	 
}

void guardarCuentaEnArchivo(const Cuenta& cuenta) {
    ofstream archivo("cuentas.txt", ios::app);
    if (archivo.is_open()) {
        archivo<<cuenta.numeroCuenta<<","<<cuenta.nombre<<","<<cuenta.usuario<<";"<<cuenta.pin<<";"<<cuenta.tipo<<";"<<cuenta.dinero<<endl;
    	archivo.close();
    	cout<<"Te registraste con exito.";
		cout<<"Tu numero de cuenta asignada es: "<<cuenta.numeroCuenta<<endl;  
	} else {
        cout << "No se pudo guardo la cuenta." << endl;
    }
}

Cuenta crearCuenta(){
	Cuenta nueva;
	
	cout << "===Registro de Cuenta==="<<endl;
	cout<<"Ingreses sus nombres completos: "<<endl;getline(cin,nueva.nombre);
	cout<<"Ingrese el nombre del usuario: "<<endl;getline(cin,nueva.usuario);
	cout<<"Ingreses el pin de 4 digitos: "<<endl;getline(cin,nueva.pin);
	cout<<"Ingrese el tipo de cuenta(ahorros/corriente): "<<endl;getline(cin,nueva.tipo);
	nueva.numeroCuenta = generarNumeroCuenta();
	
	return nueva;
}	

int main(){
	
	Cuenta nueva = crearCuenta();
	guardarCuentaEnArchivo(nueva);
	return 0;
	
}
