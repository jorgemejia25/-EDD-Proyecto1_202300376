#include <iostream>
#include "../classes/MatrizDispersa.h"
#include "../classes/Usuario.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

bool add_user()
{
    std::string nombre, password, empresa, departamento;

    std::cout << BLUE << "-------------------- Registrar Usuario --------------------" << RESET << std::endl;
    std::cout << "" << std::endl;

    // Solicitar datos al usuario
    std::cout << "Ingrese el nombre del usuario: ";
    std::cin.ignore(); // Limpiar el búfer de entrada
    std::getline(std::cin, nombre);
    std::cout << "Ingrese la contraseña: ";
    std::getline(std::cin, password);
    std::cout << "Ingrese el empresa: ";
    std::getline(std::cin, empresa);
    std::cout << "Ingrese la departamento: ";
    std::getline(std::cin, departamento);

    std::cout << "" << std::endl;
    std::cout << BLUE << "--------------------------------------------------------" << RESET << std::endl;

    auto matriz = MatrizDispersa::obtenerInstancia();
    // Validar que no existan campos vacíos

    auto usuarioExistente = matriz->buscarUsuarioPorNombre(nombre, departamento, empresa);

    if (nombre.empty() || password.empty() || empresa.empty() || departamento.empty())
    {
        std::cout << RED << "Error: Todos los campos son obligatorios." << RESET << std::endl;
        return false;
    }

    // Verificar si el usuario existe
    if (usuarioExistente)
    {
        std::cout << RED << "Error: El usuario ya existe." << RESET << std::endl;
        return false;
    }

    // Crear y registrar el usuario
    auto usuario = std::make_shared<Usuario>(nombre, password);
    matriz->insertar(empresa, departamento, usuario);
    std::cout << GREEN << "Usuario registrado exitosamente." << RESET << std::endl;
    return true;
}