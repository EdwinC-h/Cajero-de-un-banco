#include <iostream>

using namespace std;

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
	
	cout << "\n1. Consultar saldo" <<endl;
	cout << "2. Depositar dinero" <<endl;
	cout << "3. Retirar dinero" <<endl;
	cout << "4. Transferir dinero" <<endl;
	cout << "5. Movimientos transaccionales"<<endl;
	cout << "6. Cerrar sesion"<<endl; 
	
	
}

void ejecutarMenuSesion(){
	int opcion2;
	do{
	menuInicioSesion();
	cout << "Ingresa una opcion: "; cin>>opcion2;
	
	switch (opcion2) {
		case 1:
			cout << "consulta"<<endl;
			break;
		case 2:
			cout << "deposito"<<endl;
			break;
		case 3:
			cout << "retiro"<<endl;
			break;
		case 4:
			cout << "transferir"<<endl;
			break;
		case 5:
			cout << "movimientos"<<endl;
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
			cout <<"registro"<<endl;
			break;
		case 2:
			cout << "\n---------------INGRESASTE AL SISTEMA-----------" <<endl;
			ejecutarMenuSesion();
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
