#include "UserMenu.h"
#include <iostream>

// Definir códigos de colores
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"

void mostrarMenuUsuario()
{
    int opcion;

    do
    {
        std::cout << BLUE << "-------------------- Menu Usuario --------------------" << RESET << std::endl;
        std::cout << RESET << "1. Agregar Activo" << std::endl;
        std::cout << "2. Eliminar Activo" << std::endl;
        std::cout << "3. Modificar Activo" << std::endl;
        std::cout << "4. Rentar Activo" << std::endl;
        std::cout << "5. Activos Rentados" << std::endl;
        std::cout << "6. Mis Activos Rentados" << std::endl;
        std::cout << "7. Cerrar Sesión" << RESET << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            std::cout << GREEN << "Agregar Activo" << RESET << std::endl;
            // add_asset();
            break;
        case 2:
            std::cout << GREEN << "Eliminar Activo" << RESET << std::endl;
            // delete_asset();
            break;
        case 3:
            std::cout << GREEN << "Modificar Activo" << RESET << std::endl;
            // modify_asset();
            break;
        case 4:
            std::cout << GREEN << "Rentar Activo" << RESET << std::endl;
            // rent_asset();
            break;
        case 5:
            std::cout << GREEN << "Activos Rentados" << RESET << std::endl;
            // show_rented_assets();
            break;
        case 6:
            std::cout << GREEN << "Mis Activos Rentados" << RESET << std::endl;
            // show_my_rented_assets();
            break;
        case 7:
            std::cout << GREEN << "Cerrando sesión..." << RESET << std::endl;
            break;
        default:
            std::cout << RED << "Opcion invalida. Intente de nuevo." << RESET << std::endl;
            break;
        }
    } while (opcion != 7);
}