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

        // Convertir archivo a PNG
        int result = system("dot -Tpng reportes/reporte_matriz.dot -o reportes/reporte_matriz.png");
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
}