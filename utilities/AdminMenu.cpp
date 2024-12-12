#include "AdminMenu.h"
#include "AddUser.h"
#include "ReporteMatriz.h"
#include "../classes/AVL.h"
#include "../classes/MatrizDispersa.h"
#include "../classes/CircleDoubleLinkedList.h"
#include "../classes/Usuario.h"

#include <iostream>
#include <fstream>

// Definición de códigos de colores ANSI para la consola
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"

/**
 * @brief Muestra y gestiona el menú principal del administrador
 * 
 * Esta función implementa la interfaz principal del administrador, permitiendo:
 * - Gestión de usuarios
 * - Generación de reportes varios
 * - Gestión de activos
 * - Ordenamiento de transacciones
 */
void mostrarMenuAdmin()
{
    // Inicialización de archivos para reportes
    std::ofstream archivoEmpresa("reportes/reporte_empresa.dot");
    std::ofstream archivoDepartamento("reportes/reporte_departamento.dot");
    std::ofstream archivoTransacciones("reportes/reporte_transacciones.dot");
    std::ofstream archivoActivosUsuario("reportes/reporte_activos_usuario.dot");
    std::ofstream archivoActivosRentados("reportes/reporte_activos_rentados.dot");
    int opcion;

    do
    {
        // Mostrar menú principal
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
        case 1: // Registrar Usuario
            add_user();
            break;

        case 2: // Reporte Matriz Dispersa
            std::cout << GREEN << "Reporte Matriz Dispersa" << RESET << std::endl;
            reporte_matriz();
            break;

        case 3: // Reporte Activos por Departamento
            std::cout << GREEN << "Reporte Activos Disponibles de un Departamento" << RESET << std::endl;
            if (archivoDepartamento.is_open())
            {
                // Solicitar información del departamento
                std::string departamento;
                std::cout << "Ingrese el nombre del departamento: ";
                std::cin.ignore();
                std::getline(std::cin, departamento);

                // Generar y guardar el reporte
                MatrizDispersa::obtenerInstancia()->arbolAVLDepartamentos(departamento)->generarDot(archivoDepartamento);
                archivoDepartamento.close();

                // Convertir a PNG usando GraphViz
                int result = system("dot -Tpng reportes/reporte_departamento.dot -o reportes/reporte_departamento.png");
                if (result != 0)
                {
                    std::cerr << "Error al ejecutar el comando dot. Código de error: " << result << std::endl;
                }
                std::cout << "Reporte generado exitosamente" << std::endl;
            }
            else
            {
                std::cerr << "Error al abrir el archivo para escribir" << std::endl;
            }
            break;

        case 4: // Reporte Activos Disponibles de una Empresa
            std::cout << GREEN << "Reporte Activos Disponibles de una Empresa" << RESET << std::endl;
            if (archivoEmpresa.is_open())
            {
                // Preguntar por la empresa
                std::string empresa;
                std::cout << "Ingrese el nombre de la empresa: ";
                std::cin.ignore();
                std::getline(std::cin, empresa);

                MatrizDispersa::obtenerInstancia()->arbolAVLEmpresas(empresa)->generarDot(archivoEmpresa);
                archivoEmpresa.close();

                // Convertir archivo a PNG
                int result = system("dot -Tpng reportes/reporte_empresa.dot -o reportes/reporte_empresa.png");
                if (result != 0)
                {
                    std::cerr << "Error al ejecutar el comando dot. Código de error: " << result << std::endl;
                }
                std::cout << "Reporte generado exitosamente" << std::endl;
            }
            else
            {
                std::cerr << "Error al abrir el archivo para escribir" << std::endl;
            }
            break;

        case 5: // Reporte Transacciones
            std::cout << GREEN << "Reporte Transacciones" << RESET << std::endl;
            if (archivoTransacciones.is_open())
            {
                CircleDoubleLinkedList::getInstance()->generarDot(archivoTransacciones);
                archivoTransacciones.close();

                // Convertir archivo a PNG
                int result = system("dot -Tpng reportes/reporte_transacciones.dot -o reportes/reporte_transacciones.png");
                if (result != 0)
                {
                    std::cerr << "Error al ejecutar el comando dot. Código de error: " << result << std::endl;
                }
                std::cout << "Reporte generado exitosamente" << std::endl;
            }
            else
            {
                std::cerr << "Error al abrir el archivo para escribir" << std::endl;
            }
            break;

        case 6: // Reporte activos de un usuario
            std::cout << GREEN << "Reporte activos de un usuario" << RESET << std::endl;
            if (archivoActivosUsuario.is_open())
            {
                std::string nombreUsuario;
                std::string departamentoUsuario;
                std::string empresaUsuario;

                std::cout << "Ingrese el nombre del usuario: ";
                std::cin.ignore();
                std::getline(std::cin, nombreUsuario);

                std::cout << "Ingrese el departamento del usuario: ";
                std::getline(std::cin, departamentoUsuario);

                std::cout << "Ingrese la empresa del usuario: ";
                std::getline(std::cin, empresaUsuario);

                auto usuario = MatrizDispersa::obtenerInstancia()->buscarUsuarioPorNombre(nombreUsuario, departamentoUsuario, empresaUsuario);

                if (usuario)
                {
                    usuario->activos->generarDot(archivoActivosUsuario);
                    archivoActivosUsuario.close();

                    // Convertir archivo a PNG
                    int result = system("dot -Tpng reportes/reporte_activos_usuario.dot -o reportes/reporte_activos_usuario.png");
                    if (result != 0)
                    {
                        std::cerr << "Error al ejecutar el comando dot. Código de error: " << result << std::endl;
                    }
                    std::cout << "Reporte generado exitosamente" << std::endl;
                }
                else
                {
                    std::cerr << "Usuario no encontrado" << std::endl;
                }
            }
            else
            {
                std::cerr << "Error al abrir el archivo para escribir" << std::endl;
            }
            break;

        case 7: // Activos rentados por un usuario
            std::cout << GREEN << "Activos rentados por un usuario" << RESET << std::endl;
            if (archivoActivosRentados.is_open())
            {
                std::string nombreUsuario;
                std::string departamentoUsuario;
                std::string empresaUsuario;

                std::cout << "Ingrese el nombre del usuario: ";
                std::cin.ignore();
                std::getline(std::cin, nombreUsuario);

                std::cout << "Ingrese el departamento del usuario: ";
                std::getline(std::cin, departamentoUsuario);

                std::cout << "Ingrese la empresa del usuario: ";
                std::getline(std::cin, empresaUsuario);

                auto usuario = MatrizDispersa::obtenerInstancia()->buscarUsuarioPorNombre(nombreUsuario, departamentoUsuario, empresaUsuario);

                std::cout << "Usuario: " << usuario->Nombre << std::endl;

                if (usuario)
                {
                    CircleDoubleLinkedList::getInstance()->getRentedAssets(usuario->id)->generarDot(archivoActivosRentados);
                    archivoActivosRentados.close();

                    // Convertir archivo a PNG
                    int result = system("dot -Tpng reportes/reporte_activos_rentados.dot -o reportes/reporte_activos_rentados.png");
                }
                else
                {
                    std::cerr << "Usuario no encontrado" << std::endl;
                }
            }
            else
            {
                std::cerr << "Error al abrir el archivo para escribir" << std::endl;
            }
            break;

        case 8: // Ordenar transacciones
            std::cout << GREEN << "Ordenar transacciones" << RESET << std::endl;
            std::cout << "1. Ordenar de forma ascendente" << std::endl;
            std::cout << "2. Ordenar de forma descendente" << std::endl;

            int orden;
            std::cout << "Ingrese una opcion: ";
            std::cin >> orden;

            if (orden == 1)
            {
                CircleDoubleLinkedList::getInstance()->ordenarTransacciones(false);
            }
            else if (orden == 2)
            {
                CircleDoubleLinkedList::getInstance()->ordenarTransacciones(true);
            }
            break;

        case 9: // Salir
            std::cout << GREEN << "Saliendo del menu..." << RESET << std::endl;
            break;

        default: // Opción inválida
            std::cout << RED << "Opcion invalida. Intente de nuevo." << RESET << std::endl;
            break;
        }
    } while (opcion != 9);
}