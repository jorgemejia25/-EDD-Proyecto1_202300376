// FILE: main.cpp
#include <memory>
#include "utilities/Login.h"
#include "utilities/ReporteMatriz.h"
#include "utilities/LoggedUser.h"
#include "classes/MatrizDispersa.h"
#include "classes/Usuario.h"
#include "classes/Activo.h"
#include "classes/AVL.h"
#include <iostream>
#include <fstream>

int main()
{
    // auto matriz = MatrizDispersa::obtenerInstancia();

    // crear usuario por defecto
    // auto usuario = std::make_shared<Usuario>("jorge", "1234");

    // Insertar en la matriz dispersa
    // matriz->insertar("empresa", "departamento", usuario);

    AVL arbol;
    // login();
    // Crear algunos activos
    Activo activo1("Computadora", "Dell XPS 13");
    Activo activo2("Monitor", "LG 27 pulgadas");
    Activo activo3("Teclado", "Logitech G513");
    Activo activo4("Mouse", "Razer DeathAdder");

    // Insertar los activos en el árbol
    arbol.insertar(activo1); // ID generado automáticamente
    arbol.insertar(activo2);
    arbol.insertar(activo3);
    arbol.insertar(activo4);

    arbol.inorden();

    std::ofstream archivo("arbol.dot");
    arbol.generarDot(archivo);
    archivo.close();
}