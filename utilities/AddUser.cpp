#include <iostream>
#include "../classes/MatrizDispersa.h"
#include "../classes/Usuario.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

void add_user()
{
    std::string nombre, password, departamento, empresa;

    std::cout << BLUE << "-------------------- Registrar Usuario --------------------" << RESET << std::endl;
    std::cout << "" << std::endl;

    // Solicitar datos al usuario
    std::cout << "Ingrese el nombre del usuario: ";
    std::cin.ignore(); // Limpiar el búfer de entrada
    std::getline(std::cin, nombre);
    std::cout << "Ingrese la contraseña: ";
    std::getline(std::cin, password);
    std::cout << "Ingrese el departamento: ";
    std::getline(std::cin, departamento);
    std::cout << "Ingrese la empresa: ";
    std::getline(std::cin, empresa);

    std::cout << "" << std::endl;
    std::cout << BLUE << "--------------------------------------------------------" << RESET << std::endl;

    // Validar que no existan campos vacíos
    if (nombre.empty() || password.empty() || departamento.empty() || empresa.empty())
    {
        std::cout << RED << "Error: Todos los campos son obligatorios." << RESET << std::endl;
        add_user();
    }
    else
    {
        auto matriz = MatrizDispersa::obtenerInstancia();
        auto usuario = std::make_shared<Usuario>(nombre, password);
        matriz->insertar(departamento, empresa, usuario);
        std::cout << GREEN << "Usuario registrado exitosamente." << RESET << std::endl;

        matriz->mostrar();
    }
}