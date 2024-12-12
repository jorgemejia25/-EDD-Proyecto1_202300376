#include <iostream>
#include "../classes/MatrizDispersa.h"
#include "../classes/Usuario.h"

// Definición de códigos de color para la consola
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

/**
 * @brief Función para agregar un nuevo usuario al sistema
 * @details Solicita al usuario ingresar nombre, contraseña, empresa y departamento
 *          Valida que no existan campos vacíos y que el usuario no esté duplicado
 * @return bool - true si el usuario fue agregado exitosamente, false en caso contrario
 */
bool add_user()
{
    // Variables para almacenar los datos del usuario
    std::string nombre, password, empresa, departamento;

    // Interfaz de usuario para ingreso de datos
    std::cout << BLUE << "-------------------- Registrar Usuario --------------------" << RESET << std::endl;
    std::cout << "" << std::endl;

    // Solicitar y capturar datos del usuario
    std::cout << "Ingrese el nombre del usuario: ";
    std::cin.ignore(); // Limpiar el búfer para evitar problemas con getline
    std::getline(std::cin, nombre);
    std::cout << "Ingrese la contraseña: ";
    std::getline(std::cin, password);
    std::cout << "Ingrese el empresa: ";
    std::getline(std::cin, empresa);
    std::cout << "Ingrese la departamento: ";
    std::getline(std::cin, departamento);

    std::cout << "" << std::endl;
    std::cout << BLUE << "--------------------------------------------------------" << RESET << std::endl;

    // Obtener la instancia única de la matriz dispersa
    auto matriz = MatrizDispersa::obtenerInstancia();

    // Verificar si el usuario ya existe en el sistema
    auto usuarioExistente = matriz->buscarUsuarioPorNombre(nombre, departamento, empresa);

    // Validación de campos vacíos
    if (nombre.empty() || password.empty() || empresa.empty() || departamento.empty())
    {
        std::cout << RED << "Error: Todos los campos son obligatorios." << RESET << std::endl;
        return false;
    }

    // Validación de usuario duplicado
    if (usuarioExistente)
    {
        std::cout << RED << "Error: El usuario ya existe." << RESET << std::endl;
        return false;
    }

    // Crear nuevo usuario y agregarlo a la matriz
    auto usuario = std::make_shared<Usuario>(nombre, password);
    matriz->insertar(empresa, departamento, usuario);
    std::cout << GREEN << "Usuario registrado exitosamente." << RESET << std::endl;
    return true;
}