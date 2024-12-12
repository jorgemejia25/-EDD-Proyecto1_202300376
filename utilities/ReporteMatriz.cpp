#include "../classes/MatrizDispersa.h"
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <cstring>
#include <errno.h>

/**
 * @brief Implementación de la generación de reportes de la matriz dispersa
 * 
 * Esta función realiza las siguientes operaciones:
 * 1. Obtiene la instancia de la matriz dispersa
 * 2. Crea el directorio '../reportes' si no existe
 * 3. Genera un archivo DOT con la estructura de la matriz
 * 4. Convierte el archivo DOT a PNG usando Graphviz
 * 
 * @note Requiere que Graphviz esté instalado en el sistema
 * @throws Puede generar errores si no se pueden crear directorios o archivos
 */
void reporte_matriz()
{
    // Obtener instancia singleton de la matriz
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

        // Generar contenido DOT utilizando el método de la matriz dispersa
        matriz->generarDot(archivo);
        archivo.close();

        // Convertir archivo DOT a PNG usando Graphviz
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