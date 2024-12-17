/**
 * @file UserMenu.cpp
 * @brief Implementación del menú de usuario y sus funcionalidades
 */

#include "UserMenu.h"
#include "../classes/Activo.h"
#include "../classes/MatrizDispersa.h"
#include "../classes/Transaction.h"
#include "../classes/CircleDoubleLinkedList.h"
#include <iostream>

// Definición de códigos de color para la interfaz
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"

/**
 * @brief Implementa la funcionalidad completa del menú de usuario
 * @param usuario Puntero al usuario logueado
 *
 * Opciones disponibles:
 * 1. Agregar Activo
 * 2. Eliminar Activo
 * 3. Modificar Activo
 * 4. Rentar Activo
 * 5. Ver Activos Rentados
 * 6. Ver Mis Activos Rentados
 * 7. Devolver Activo
 * 8. Cerrar Sesión
 */
void mostrarMenuUsuario(Usuario *usuario)
{
    int opcion;
    std::string nombre;
    std::string descripcion;
    std::string idActivo;
    int maxDias;
    Activo *activo;
    Activo *activoRentado;
    Transaction *transaccion;
    int dias;

    do
    {
        std::cout << BLUE << "--------------------- Menu Usuario ---------------------" << RESET << std::endl;
        std::cout << RESET << "1. Agregar Activo" << std::endl;
        std::cout << "2. Eliminar Activo" << std::endl;
        std::cout << "3. Modificar Activo" << std::endl;
        std::cout << "4. Rentar Activo" << std::endl;
        std::cout << "5. Activos Rentados por mi" << std::endl;
        std::cout << "6. Mis Activos Rentados" << std::endl;
        std::cout << "7. Devolver activo" << std::endl;
        std::cout << "8. Cerrar Sesión" << RESET << std::endl;
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            std::cout << GREEN << "Agregar Activo" << RESET << std::endl;
            // add_asset();
            std::cout << "Ingrese el nombre del activo: ";
            std::cin.ignore();
            std::getline(std::cin, nombre);

            std::cout << "Ingrese la descripción del activo: ";
            std::getline(std::cin, descripcion);

            std::cout << "Ingrese el número máximo de días a rentar: ";
            std::cin >> maxDias;

            // Crear activo
            activo = new Activo(nombre, descripcion, maxDias);
            activo->setIdUsuario(usuario->id);

            // Agregar activo al usuario
            usuario->agregarActivo(*activo);

            std::cout << GREEN << "Activo agregado exitosamente." << RESET << std::endl;

            break;
        case 2:
            std::cout << GREEN << "Eliminar Activo" << RESET << std::endl;

            usuario->mostrarActivos();

            std::cout << "Ingrese el ID del activo a eliminar: ";

            std::cin.ignore();

            std::getline(std::cin, idActivo);

            activo = usuario->buscarActivo(idActivo);

            if (activo)
            {
                usuario->eliminarActivo(idActivo);
                std::cout << GREEN << "Activo eliminado exitosamente." << RESET << std::endl;
            }
            else
            {
                std::cout << RED << "Activo no encontrado." << RESET << std::endl;
            }

            break;
        case 3:
            std::cout << GREEN << "Modificar Activo" << RESET << std::endl;
            // modify_asset();

            usuario->mostrarActivos();

            std::cout << "Ingrese el ID del activo a modificar: ";

            std::cin.ignore();

            std::getline(std::cin, idActivo);

            activo = usuario->buscarActivo(idActivo);

            if (activo)
            {
                std::cout << "Ingrese el nuevo nombre del activo: ";
                std::getline(std::cin, nombre);

                std::cout << "Ingrese la nueva descripción del activo: ";
                std::getline(std::cin, descripcion);

                activo->setNombre(nombre);
                activo->setDescripcion(descripcion);

                std::cout << GREEN << "Activo modificado exitosamente." << RESET << std::endl;
            }
            else
            {
                std::cout << RED << "Activo no encontrado." << RESET << std::endl;
            }

            break;
        case 4:
            MatrizDispersa::obtenerInstancia()->mostrarActivosDeMatriz(usuario->id);

            std::cout << "Ingrese el ID del activo a rentar: ";
            std::cin.ignore();
            std::getline(std::cin, idActivo);

            activoRentado = MatrizDispersa::obtenerInstancia()->buscarActivosDeMatriz(idActivo);

            std::cout << "Ingrese los días a rentar: ";
            std::cin >> dias;

            if (activoRentado && !activoRentado->getRentado())
            {

                if (dias > activoRentado->getMaxDias())
                {
                    std::cout << RED << "No se puede rentar por más de " << activoRentado->getMaxDias() << " días." << RESET << std::endl;
                    break;
                }

                transaccion = new Transaction(usuario, activoRentado, dias);

                // Agregar transacción a la lista
                CircleDoubleLinkedList::getInstance()->insertTransaction(transaccion);
                activoRentado->setRentado(true);

                std::cout << GREEN << "Activo rentado exitosamente." << RESET << std::endl;
            }
            else
            {
                std::cout << RED << "Activo no encontrado." << RESET << std::endl;
            }

            break;
        case 5:
            std::cout << GREEN << "Activos Rentados por mi" << RESET << std::endl;
            // show_rented_assets();
            CircleDoubleLinkedList::getInstance()->printActiveTransactions(usuario->id);

            break;
        case 6:
            std::cout << GREEN << "Mis Activos Rentados" << RESET << std::endl;
            // show_my_rented_assets();

            CircleDoubleLinkedList::getInstance()->printMyTransactions(usuario->id);

            break;

        case 7:
            std::cout << GREEN << "Devolver activo" << RESET << std::endl;
            // return_asset();
            CircleDoubleLinkedList::getInstance()->printActiveTransactions(usuario->id);

            std::cout << "Ingrese el ID de la transacción a devolver: ";
            std::cin.ignore();
            std::getline(std::cin, idActivo);

            transaccion = CircleDoubleLinkedList::getInstance()->searchTransaction(idActivo);

            if (transaccion)
            {
                transaccion->setStatus(false);
                transaccion->getAsset()->setRentado(false);
            }
            else
            {
                std::cout << RED << "Transacción no encontrada." << RESET << std::endl;
            }

            std::cout << GREEN << "Activo devuelto exitosamente." << RESET << std::endl;

            break;

        case 8:
            std::cout << GREEN << "Cerrando sesión..." << RESET << std::endl;
            break;
        default:
            std::cout << RED << "Opcion invalida. Intente de nuevo." << RESET << std::endl;
            break;
        }
    } while (opcion != 8);
}