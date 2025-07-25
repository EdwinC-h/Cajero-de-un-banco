#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <wchar.h> //wchar.h y locale.h nose sirven para leer los caracteres especiales en consola, en el archivo principal ya le agrego el codigo
#include <locale.h>

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

void guardarCuentaEnArchivo(const Cuenta& cuenta) {//aqui creo que no hay observaciones
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
	cout<<"Ingreses sus nombres completos: "<<endl;getline(cin,nueva.nombre); //aqui tengo un problema, ejecuta para que veas que es
	cout<<"Ingrese el nombre del usuario: "<<endl;getline(cin,nueva.usuario);//se salta la linea de ingresar nombres a esta linea.
	cout<<"Ingreses el pin de 4 digitos: "<<endl;getline(cin,nueva.pin);
	cout<<"Ingrese el tipo de cuenta(ahorros/corriente): "<<endl;getline(cin,nueva.tipo);
	nueva.numeroCuenta = generarNumeroCuenta();
	
	return nueva;
}

void ejecutarRegistro(){
	Cuenta nueva = crearCuenta();
	guardarCuentaEnArchivo(nueva);
}

//Una vez iniciada la sesion, codigo del CRUD
void consultarSaldo(Cuenta cuenta) {
    cout << "Saldo actual: $" << cuenta.dinero << endl;
}

void depositar(Cuenta &cuenta, double deposito) {
    if (deposito > 0) {
        cuenta.dinero += deposito;
        cout << "Su deposito ha sido exitoso." << endl;

        ofstream archivo("movimientos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Deposito ==> " << cuenta.numeroCuenta << "=" << deposito << endl;
            archivo.close();
        } else {
            cout<< "No se registro el movimiento." << endl;
        }
    } else {
        cout << "Monto invalido." << endl;
    }
}

void retirar(Cuenta &cuenta, double monto) {
    if (monto > 0 and monto <= cuenta.dinero) { //borre el && por "and", esq me manejo mas asi
        cuenta.dinero -= monto;
        cout << "Su retiro ha sido exitoso." << endl;

        ofstream archivo("movimientos.txt", ios::app);
        if (archivo.is_open()) {
            archivo << "Retiro|" << cuenta.numeroCuenta << "|" << monto << endl;
            archivo.close();
        } else {
            cerr << "No se registro el movimiento." << endl;
        }
    } else {
        cout << "Fondos insuficientes o monto invalido." << endl;
    }
}

//agrego la categoria de transferir, puesto que un cajero de banco actualmente es asi 
bool transferir(Cuenta &origen, const string &destino, double monto){ //necesito que me atuden viendo si esta funcion de transferir funciona bien.
	if (monto <= 0 or monto > origen.dinero){ //aqui igual me manejo mas con "or"
		cout<<"El monto no es valido."<<endl;
		cout<<"Comprueba que dispongas de dinero suficiente"<<endl;
		return false;
	}
	ifstream enArchivo("cuentas.txt");
	ofstream alArchivo("temp.txt"); //investiguen, pero trata de crear un archivo temporal para guardar datos ahi y luego estos datos pasan a "cuentas.txt"
	string linea;
	bool usuarioEncontrado = false;
	
	while(getline(enArchivo, linea)){ //esto ya lo tendran que investigar, y lo subimos a la documentacion como parte de investigacion.
		stringstream ss(linea);
		string num, nombre, usuario, pin, tipo, saldo;
		getline(ss, num, ',');
		getline(ss, nombre, ',');
		getline(ss, usuario, ',');
		getline(ss, pin, ',');
		getline(ss, tipo, ',');
		getline(ss, saldo);//aqui el saldo esta en string, por si no entienden como funciona esta linea.
		
		double plata = stod(saldo);//y aqui como sabran lo convierto de string a double
		
		if(num == destino){
			plata += monto;
			usuarioEncontrado = true;
				
		}
		
		if(num == origen.numeroCuenta){
			origen.dinero -= monto;
			alArchivo<<origen.numeroCuenta<<","<<origen.nombre<<","<<origen.usuario<<","<<origen.pin<<","<<origen.tipo<<","<<origen.dinero<<endl;
		}else{
			alArchivo << num << "," << nombre << "," << usuario << "," << pin << "," << tipo << "," << plata << endl;
			}
		}
	enArchivo.close();
	alArchivo.close();
	
	    remove("cuentas.txt");
	    rename("temp.txt", "cuentas.txt");
	
	    if (usuarioEncontrado) {
	        ofstream archivo("movimientos.txt", ios::app);
	        archivo << origen.numeroCuenta << ",transferencia,-" << monto << ",a," << destino << endl;
	        archivo << destino << ",transferencia,+" << monto << ",de," << origen.numeroCuenta << endl;
	        archivo.close();
	        cout << "Transferencia realizada con éxito." << endl;
	        return true;
	    } else {
	        cout << "Cuenta destino no encontrada." << endl;
	        return false;
	    }
	}
	
void mostrarMovimientos(const Cuenta &cuenta) {//aqui mostramos los moviemientos como de la banca movil, si pueden agregar la fecha estaria bien_
    ifstream archivo("movimientos.txt");		//pero deberiamos de igual menera invesitgar como hacerlo para que sea en tiempo real, pero solo si quieren
    string linea;
    bool hayMovimientos = false;

    cout << "\nHistorial de movimientos: "<<endl;

    while (getline(archivo, linea)) {//aqui igual vean si esta bien, porque creo que quedaria mejor hacerlo con un bucle for
        if (linea.find(cuenta.numeroCuenta) != string::npos) {
            cout << "-" << linea << endl;
            hayMovimientos = true;
        }
    }

    if (!hayMovimientos) {
        cout << "No hay movimientos registrados aún." << endl;
    }

    archivo.close();
}

void menuPrincipal(){
	cout << "\n///////////////////////" << endl;
	cout << "BIENVENIDO A BANCO-CARD" <<endl;
	cout << "///////////////////////" <<endl;
	
	//por el momento les señalo que tenemos:
	cout << "1. Registrarse" << endl; //esto ya esta aunque tiene fallas, ayudenme viendo
	cout << "2. Iniciar Sesion" <<endl;//aqui me falta poner el login, osea inicar sesion
										//Ismael ya lo hiciste pero usando vector, y estamos trabajando con struct, porque usamos diferentes tipos de datos.
										//falta hacer de iniciar sesion, tienen que bucar las cuentas en cuentas.txt
	cout << "3. Cambiar PIN" << endl; //esto aun no lo tenemos, pero me dicen si lo hacemos o no, yo digo que si, es algo fundamental para  los olvidones :v
	cout << "4. Salir del sistema" <<endl;
	
}

void menuInicioSesion(){
	
	cout << "\n1. Consultar saldo" <<endl; // funciona bien
	cout << "2. Depositar dinero" <<endl; // funciona bien
	cout << "3. Retirar dinero" <<endl; //funciona bien
	cout << "4. Transferir dinero" <<endl; //debemos solucionar el registro de cuentas para poder comprobar si funciona
	cout << "5. Movimientos transaccionales"<<endl; //igualmente aun queda por comprobar y pulir su funcionamiento
	cout << "6. Cerrar sesion"<<endl; 
	
	
}

void ejecutarMenuSesion(Cuenta &cuenta){
	
	int opcion2;
	double monto;
	string destino;
	
	do{
	menuInicioSesion();
	cout << "Ingresa una opcion: "; cin>>opcion2;

	//por el momento para que revisen lo de login creen una cuenta de prueba con datos quemados
	
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
			cout << "Numero de cuenta destino: ";
            cin >> destino;
            cout << "Ingrese monto a transferir: $";
            cin >> monto;
            transferir(cuenta, destino, monto);
            break;
		case 5:
			mostrarMovimientos(cuenta);
			break;
		case 6:
			cout << "Cerrando Sesion"<<endl;
			break;
		default:
			cout<<"Opcion no valida"<<endl;
	}
	
	} while(opcion2 != 6 ); 
		
	
}


void ejecutar(){
	int opcion;
	
	do{
	
	menuPrincipal();
	cout<<"Ingrese una de las opciones: "; cin>>opcion;
	
	switch (opcion) {
		case 1:
			ejecutarRegistro();
			break;
		case 2:
			cout << "\n---------------INGRESASTE AL SISTEMA-----------" <<endl;
			
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
}//ya nos queda poco para teminar, y si tienen alguna idea para mejorar nuestro codigo base hablen, recuerden que podemos investigar y 
 //usar mas herramientas o bibliotecas. Y ya preparen la plantilla de documentacion 
