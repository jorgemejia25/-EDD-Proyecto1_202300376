// FILE: utilities/Login.cpp
#include "Login.h"
#include <iostream>
#include <string>
#include "AdminMenu.h"
#include "UserMenu.h"
#include <limits>
#include "../classes/MatrizDispersa.h"

// Definir códigos de colores para la interfaz de usuario
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"

/**
 * @brief Función principal de inicio de sesión del sistema
 * 
 * Gestiona el proceso de autenticación de usuarios, permitiendo:
 * - Acceso como administrador con credenciales predeterminadas
 * - Acceso como usuario regular validando contra la matriz dispersa
 * 
 * El flujo de la función es:
 * 1. Solicita credenciales al usuario (usuario, contraseña, empresa, departamento)
 * 2. Verifica si es el administrador (user=admin, password=admin)
 * 3. Si no es admin, busca el usuario en la matriz dispersa
 * 4. Redirige al menú correspondiente según el tipo de usuario
 */
void login()
{
    std::string user, password, empresa, departamento;

    std::cout << BLUE << "-------------------- Iniciar sesión --------------------" << RESET << std::endl;

    // Solicitar credenciales al usuario
    std::cout << "Ingrese el usuario: ";
    std::getline(std::cin, user);

    std::cout << "Ingrese la contraseña: ";
    std::getline(std::cin, password);

    std::cout << "Ingrese la empresa: ";
    std::getline(std::cin, empresa);

    std::cout << "Ingrese el departamento: ";
    std::getline(std::cin, departamento);

    std::cout << BLUE << "--------------------------------------------------------" << RESET << std::endl;

    // Verificación de credenciales de administrador
    // El admin no requiere empresa ni departamento
    if (user == "admin" && password == "admin" && empresa.empty() && departamento.empty())
    {
        std::cout << GREEN << "Bienvenido, administrador." << RESET << std::endl;
        mostrarMenuAdmin();
    }
    else
    {
        // Obtener la instancia singleton de la matriz dispersa
        auto matriz = MatrizDispersa::obtenerInstancia();

        // Buscar el usuario en la matriz por nombre, departamento y empresa
        auto usuarioExistente = matriz->buscarUsuarioPorNombre(user, departamento, empresa);

        // Verificar credenciales del usuario regular
        if (usuarioExistente && usuarioExistente->Password == password)
        {
            std::cout << GREEN << "Bienvenido, " << user << "." << RESET << std::endl;
            mostrarMenuUsuario(usuarioExistente);
        }
        else
        {
            std::cout << RED << "Usuario o contraseña incorrectos." << RESET << std::endl;
            login(); // Recursión en caso de credenciales inválidas
        }
    }

    // Limpiar el búfer de entrada y volver a mostrar el login
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    login();
}