#include "AdminMenu.h"
#include "AddUser.h"
#include "ReporteMatriz.h"

#include <iostream>

// Definir códigos de colores
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"

void mostrarMenuAdmin()
{
    int opcion;

    do
    {

        std::cout << BLUE << "------------------ Menu Administrador ------------------" << RESET << std::endl;
        std::cout << RESET << "1. Registrar Usuario" << std::endl;
        std::cout << "2. Reporte Matriz Dispersa" << std::endl;
        std::cout << "3. Reporte Activos Disponibles de un Departamento" << std::endl;
        std::cout << "4. Reporte Activos Disponibles de una Empresa" << std::endl;
        std::cout << "5. Reporte Transacciones" << std::endl;
        std::cout << "6. Reporte activos de un usuario" << std::endl;
        std::cout << "7. Activos rentados por un usuario" << std::endl;
        std::cout << "8. Ordenar transacciones" << std::endl;
        std::cout << "9. Salir" << RESET << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            add_user();

            break;
        case 2:
            std::cout << GREEN << "Reporte Matriz Dispersa" << RESET << std::endl;

            reporte_matriz();

            break;
        case 3:
            std::cout << GREEN << "Reporte Activos Disponibles de un Departamento" << RESET << std::endl;
            break;
        case 4:
            std::cout << GREEN << "Reporte Activos Disponibles de una Empresa" << RESET << std::endl;
            break;
        case 5:
            std::cout << GREEN << "Reporte Transacciones" << RESET << std::endl;
            break;
        case 6:
            std::cout << GREEN << "Reporte activos de un usuario" << RESET << std::endl;
            break;
        case 7:
            std::cout << GREEN << "Activos rentados por un usuario" << RESET << std::endl;
            break;
        case 8:
            std::cout << GREEN << "Ordenar transacciones" << RESET << std::endl;
            break;
        case 9:
            std::cout << GREEN << "Saliendo del menu..." << RESET << std::endl;
            break;
        default:
            std::cout << RED << "Opcion invalida. Intente de nuevo." << RESET << std::endl;
            break;
        }
    } while (opcion != 9);
}