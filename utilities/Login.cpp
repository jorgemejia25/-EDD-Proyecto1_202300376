// FILE: utilities/Login.cpp
#include "Login.h"
#include <iostream>
#include <string>
#include "AdminMenu.h"
#include "UserMenu.h"
#include <limits>
#include "../classes/MatrizDispersa.h"

// Definir códigos de colores
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

void login()
{
    std::string user, password, empresa, departamento;

    std::cout << "\033[34m-------------------- Iniciar sesión --------------------\033[0m" << std::endl;

    // Solicitar datos al usuario
    std::cout << "Ingrese el usuario: ";
    std::getline(std::cin, user);

    std::cout << "Ingrese la contraseña: ";
    std::getline(std::cin, password);

    std::cout << "Ingrese la empresa: ";
    std::getline(std::cin, empresa);

    std::cout << "Ingrese el departamento: ";
    std::getline(std::cin, departamento);

    std::cout << "\033[34m--------------------------------------------------------\033[0m" << std::endl;

    // Verificar si el usuario es administrador
    if (user == "admin" && password == "admin" && empresa.empty() && departamento.empty())
    {
        std::cout << "\033[32mBienvenido, administrador.\033[0m" << std::endl;
        mostrarMenuAdmin();
    }
    else
    {

        auto matriz = MatrizDispersa::obtenerInstancia();

        // crear usuario por defecto
        auto usuario = std::make_shared<Usuario>("j", "1");

        // Insertar en la matriz dispersa
        matriz->insertar("e", "d", usuario);

        // Verificar si el usuario existe
        auto usuarioExistente = matriz->buscarUsuarioPorNombre(user, departamento, empresa);

        if (usuarioExistente && usuarioExistente->Password == password)
        {
            std::cout << "\033[32mBienvenido, " << user << ".\033[0m" << std::endl;

            mostrarMenuUsuario(usuarioExistente);
        }
        else
        {
            std::cout << "\033[31mUsuario o contraseña incorrectos.\033[0m" << std::endl;

            login();
        }
    }

    // Limpiar el búfer de entrada
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    login(); // Volver a llamar a la función
}