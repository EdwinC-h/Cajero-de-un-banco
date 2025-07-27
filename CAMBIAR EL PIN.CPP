void cambiarPin() {
    ifstream archivoOriginal("cuentas.txt");
    ofstream archivoTemporal("temp.txt");
    
    string usuario, pinActual, nuevoPin;
    bool cambiado = false;

    cin.ignore();
    cout << "=== CAMBIO DE PIN ===" << endl;
    cout << "Usuario: "; getline(cin, usuario);
    cout << "PIN actual: "; getline(cin, pinActual);

    string linea;
    while (getline(archivoOriginal, linea)) {
        stringstream ss(linea);
        Cuenta cuenta;
        string plata;
        
        getline(ss, cuenta.numeroCuenta, ',');
        getline(ss, cuenta.nombre, ',');
        getline(ss, cuenta.usuario, ',');
        getline(ss, cuenta.pin, ',');
        getline(ss, cuenta.tipo, ',');
        getline(ss, plata);

        cuenta.dinero = stod(plata);

        if (cuenta.usuario == usuario && cuenta.pin == pinActual) {
            cout << "Ingrese el nuevo PIN: ";
            getline(cin, nuevoPin);
            cuenta.pin = nuevoPin;
            cambiado = true;
        }

        archivoTemporal << cuenta.numeroCuenta << "," << cuenta.nombre << "," << cuenta.usuario << "," << cuenta.pin << "," << cuenta.tipo << "," << cuenta.dinero << endl;
    }

    archivoOriginal.close();
    archivoTemporal.close();
    remove("cuentas.txt");
    rename("temp.txt", "cuentas.txt");

    if (cambiado) {
        cout << "PIN actualizado con éxito." << endl;
    } else {
        cout << "Usuario o PIN incorrecto. No se actualizó nada." << endl;
    }
}
