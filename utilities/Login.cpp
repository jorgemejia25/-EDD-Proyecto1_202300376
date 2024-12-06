// FILE: utilities/Login.cpp
#include "Login.h"
#include <iostream>
#include <string>
#include "AdminMenu.h"

// Definir códigos de colores
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

void login()
{
    std::string user, password, departamento, empresa;

    std::cout << BLUE << "-------------------- Iniciar sesión --------------------" << RESET << std::endl;
    std::cout << "" << std::endl;
    // Solicitar datos al usuario
    std::cout << "Ingrese el usuario: ";
    std::cin.ignore();
    std::getline(std::cin, user);
    std::cout << "Ingrese la contraseña: ";
    std::getline(std::cin, password);
    std::cout << "Ingrese el departamento: ";
    std::getline(std::cin, departamento);
    std::cout << "Ingrese la empresa: ";
    std::getline(std::cin, empresa);

    std::cout << "" << std::endl;
    std::cout << BLUE << "--------------------------------------------------------" << RESET << std::endl;

    // Verificar si el usuario es administrador
    if (user == "admin" && password == "admin" && departamento.empty() && empresa.empty())
    {
        std::cout << GREEN << "Bienvenido, administrador." << RESET << std::endl;

        // Mostrar menú de administrador
        mostrarMenuAdmin();
    }
    else
    {
        std::cout << "Datos ingresados: " << std::endl;
        std::cout << "Usuario: " << user << std::endl;
        std::cout << "Contraseña: " << password << std::endl;
        std::cout << "Departamento: " << departamento << std::endl;
        std::cout << "Empresa: " << empresa << std::endl;
    }

    login();
}