#include "../classes/MatrizDispersa.h"
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <errno.h>

void reporte_matriz()
{
    auto matriz = MatrizDispersa::obtenerInstancia();

    // Crear directorio si no existe
    const char *dir = "../reportes";
    int nError = mkdir(dir, 0777);
    if (nError != 0 && errno != EEXIST)
    {
        std::cerr << "Error al crear el directorio: " << strerror(errno) << std::endl;
        return;
    }

    // Abrir archivo para escritura
    std::ofstream archivo("reportes/reporte_matriz.dot");

    // Verificar si el archivo se abrió correctamente
    if (archivo.is_open())
    {
        std::cout << "Generando reporte..." << std::endl;

        // Generar contenido DOT
        matriz->generarDot(archivo);

        archivo.close();
        std::cout << "Reporte generado exitosamente" << std::endl;
    }
    else
    {
        std::cerr << "Error al abrir el archivo para escribir" << std::endl;
    }
}