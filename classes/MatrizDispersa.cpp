/**
 * @file MatrizDispersa.cpp
 * @brief Implementación de una matriz dispersa para gestionar usuarios en empresas y departamentos
 *
 * Esta clase implementa una matriz dispersa que permite organizar usuarios
 * en una estructura bidimensional donde las filas representan empresas y
 * las columnas representan departamentos. Utiliza el patrón Singleton.
 */

#include "MatrizDispersa.h"
#include <iostream>

// Inicializar la instancia estática a nullptr
std::shared_ptr<MatrizDispersa> MatrizDispersa::instancia = nullptr;

// Constructor de Nodo
Nodo::Nodo(const std::shared_ptr<Usuario> &usuario)
    : usuario(usuario), izquierda(nullptr), derecha(nullptr),
      arriba(nullptr), abajo(nullptr), adelante(nullptr), atras(nullptr) {}

/**
 * @brief Constructor de la clase NodoCabecera
 * @param nombre Identificador del nodo cabecera (empresa o departamento)
 */
NodoCabecera::NodoCabecera(const std::string &nombre)
    : nombre(nombre), siguiente(nullptr), primerNodo(nullptr) {}

/**
 * @brief Constructor privado de MatrizDispersa (patrón Singleton)
 */
MatrizDispersa::MatrizDispersa() : primerFila(nullptr), primerColumna(nullptr) {}

/**
 * @brief Obtiene la instancia única de la matriz dispersa
 * @return Puntero compartido a la instancia única
 */
std::shared_ptr<MatrizDispersa> MatrizDispersa::obtenerInstancia()
{
    if (instancia == nullptr)
    {
        instancia = std::shared_ptr<MatrizDispersa>(new MatrizDispersa());
    }
    return instancia;
}

/**
 * @brief Inserta un usuario en la matriz dispersa.
 *
 * @param empresa Nombre del empresa.
 * @param departamento Nombre de la departamento.
 * @param usuario Puntero compartido al usuario a insertar.
 */
void MatrizDispersa::insertar(const std::string &empresa, const std::string &departamento,
                              const std::shared_ptr<Usuario> &usuario)
{
    // Asignar un id al usuario
    static int idCounter = 0;
    usuario->id = idCounter++;

    auto nuevoNodo = std::make_shared<Nodo>(usuario);

    Nodo *nodoExistente = buscarNodoEnPosicionPorDepartamentoEmpresa(empresa, departamento);
    if (nodoExistente)
    {
        auto actual = nodoExistente;
        while (actual->adelante.get() != nullptr)
        {
            actual = actual->adelante.get();
        }
        actual->adelante = nuevoNodo;
        nuevoNodo->atras = actual->adelante;
        return;
    }

    auto actualFila = primerFila;
    std::shared_ptr<NodoCabecera> filaAnterior = nullptr;

    while (actualFila && actualFila->nombre < empresa)
    {
        filaAnterior = actualFila;
        actualFila = actualFila->siguiente;
    }

    if (!actualFila || actualFila->nombre != empresa)
    {
        auto nuevaFila = std::make_shared<NodoCabecera>(empresa);
        if (filaAnterior)
        {
            nuevaFila->siguiente = actualFila;
            filaAnterior->siguiente = nuevaFila;
        }
        else
        {
            nuevaFila->siguiente = primerFila;
            primerFila = nuevaFila;
        }
        actualFila = nuevaFila;
    }

    // 2. Insertar columna (departamento) ordenadamente
    auto actualColumna = primerColumna;
    std::shared_ptr<NodoCabecera> columnaAnterior = nullptr;

    while (actualColumna && actualColumna->nombre < departamento)
    {
        columnaAnterior = actualColumna;
        actualColumna = actualColumna->siguiente;
    }

    if (!actualColumna || actualColumna->nombre != departamento)
    {
        auto nuevaColumna = std::make_shared<NodoCabecera>(departamento);
        if (columnaAnterior)
        {
            nuevaColumna->siguiente = actualColumna;
            columnaAnterior->siguiente = nuevaColumna;
        }
        else
        {
            nuevaColumna->siguiente = primerColumna;
            primerColumna = nuevaColumna;
        }
        actualColumna = nuevaColumna;
    }

    // 3. Insertar el nuevo nodo en la fila (ordenado por ID)
    auto actualNodoFila = actualFila->primerNodo;
    std::shared_ptr<Nodo> anteriorFila = nullptr;

    while (actualNodoFila && actualNodoFila->usuario->id < usuario->id)
    {
        anteriorFila = actualNodoFila;
        actualNodoFila = actualNodoFila->derecha;
    }

    // Conectar horizontalmente
    if (!anteriorFila)
    {
        nuevoNodo->derecha = actualFila->primerNodo;
        if (actualFila->primerNodo)
            actualFila->primerNodo->izquierda = nuevoNodo;
        actualFila->primerNodo = nuevoNodo;
    }
    else
    {
        nuevoNodo->derecha = anteriorFila->derecha;
        nuevoNodo->izquierda = anteriorFila;
        anteriorFila->derecha = nuevoNodo;
        if (nuevoNodo->derecha)
            nuevoNodo->derecha->izquierda = nuevoNodo;
    }

    // 4. Insertar el nuevo nodo en la columna (ordenado por empresa)
    auto actualNodoColumna = actualColumna->primerNodo;
    std::shared_ptr<Nodo> anteriorColumna = nullptr;

    while (actualNodoColumna &&
           buscarFilaPorNodo(actualNodoColumna)->nombre < empresa)
    {
        anteriorColumna = actualNodoColumna;
        actualNodoColumna = actualNodoColumna->abajo;
    }

    // Conectar verticalmente
    if (!anteriorColumna)
    {
        nuevoNodo->abajo = actualColumna->primerNodo;
        if (actualColumna->primerNodo)
            actualColumna->primerNodo->arriba = nuevoNodo;
        actualColumna->primerNodo = nuevoNodo;
    }
    else
    {
        nuevoNodo->abajo = anteriorColumna->abajo;
        nuevoNodo->arriba = anteriorColumna;
        anteriorColumna->abajo = nuevoNodo;
        if (nuevoNodo->abajo)
            nuevoNodo->abajo->arriba = nuevoNodo;
    }
}

std::shared_ptr<NodoCabecera> MatrizDispersa::buscarFilaPorNodo(std::shared_ptr<Nodo> nodo)
{
    auto fila = primerFila;
    while (fila)
    {
        auto actual = fila->primerNodo;
        while (actual)
        {
            if (actual == nodo)
                return fila;
            actual = actual->derecha;
        }
        fila = fila->siguiente;
    }
    return nullptr;
}

/**
 * @brief Genera una representación gráfica de la matriz en formato DOT
 * @param out Stream de salida donde se escribirá el código DOT
 */
void MatrizDispersa::generarDot(std::ostream &out)
{
    const auto NODE_STYLE = R"(width=1.5; style=filled)";

    // 1. Escribir encabezado del grafo
    escribirEncabezado(out, NODE_STYLE);

    // 2. Procesar filas y columnas
    std::string connectionsFilas = procesarFilas(out, NODE_STYLE);
    auto [connectionsColumnas, subgraphColumnas] = procesarColumnas(out, NODE_STYLE);

    // 3. Generar nodos
    generarNodos(out, NODE_STYLE);

    // 4. Escribir todas las conexiones y subgrafos
    out << "\n"
        << connectionsFilas << connectionsColumnas << subgraphColumnas << "}\n";
}

void MatrizDispersa::escribirEncabezado(std::ostream &out, const std::string &NODE_STYLE)
{
    out << R"(digraph MatrizDispersa {
    node [shape=box, fontname="Arial"];
    )";
    out << R"(    Mt [label="Usuarios"; )" << NODE_STYLE << R"(; fillcolor=cornsilk; group=0];
    Mt -> F0;
    Mt -> C0;
    )";
}

std::string MatrizDispersa::procesarFilas(std::ostream &out, const std::string &NODE_STYLE)
{
    std::string connectionsFilas;
    auto filaActual = primerFila;
    int numFilaActual = 0;
    out << "// Filas\n";

    while (filaActual)
    {
        out << "    F" << numFilaActual
            << R"( [label=")" << filaActual->nombre << R"("; )"
            << NODE_STYLE << R"(; fillcolor=lightblue; group=0];
    )";

        if (filaActual->siguiente)
        {
            connectionsFilas += "    F" + std::to_string(numFilaActual) + " -> F" + std::to_string(numFilaActual + 1) + ";\n";
        }

        if (filaActual->primerNodo) // Conectar con la columna
        {
            connectionsFilas += "    F" + std::to_string(numFilaActual) + " -> " + std::to_string(filaActual->primerNodo->usuario->id) + ";\n";
            connectionsFilas += "    " + std::to_string(filaActual->primerNodo->usuario->id) + " -> F" + std::to_string(numFilaActual) + ";\n";
        }

        filaActual = filaActual->siguiente;
        numFilaActual++;
    }

    return connectionsFilas;
}

std::pair<std::string, std::string> MatrizDispersa::procesarColumnas(std::ostream &out, const std::string &NODE_STYLE)
{
    std::string connectionsColumnas;
    std::string subgraphColumnas = "\n    {rank=same; Mt";
    auto colActual = primerColumna;
    int numColActual = 0;
    out << "\n// Columnas\n";

    while (colActual)
    {
        out << "    C" << numColActual
            << R"( [label=")" << colActual->nombre << R"("; )"
            << NODE_STYLE << R"(; fillcolor=lightblue; group=)" << numColActual + 1 << "];\n";

        subgraphColumnas += "; C" + std::to_string(numColActual);

        if (colActual->siguiente)
        {
            connectionsColumnas += "    C" + std::to_string(numColActual) + " -> C" + std::to_string(numColActual + 1) + ";\n";
        }

        if (colActual->primerNodo) // Conectar con la fila
        {
            connectionsColumnas += "    C" + std::to_string(numColActual) + " -> " + std::to_string(colActual->primerNodo->usuario->id) + ";\n";
            connectionsColumnas += "    " + std::to_string(colActual->primerNodo->usuario->id) + " -> C" + std::to_string(numColActual) + ";\n";
        }

        colActual = colActual->siguiente;
        numColActual++;
    }

    subgraphColumnas += "};\n";
    return {connectionsColumnas, subgraphColumnas};
}

void MatrizDispersa::generarNodos(std::ostream &out, const std::string &NODE_STYLE)
{

    auto filaActual = primerFila;
    int numFilaActual = 0;

    std::string subgrafosFilas;
    std::string subgrafosColumnas;

    out << "\n// Nodos\n";

    while (filaActual)
    {

        subgrafosFilas += "    {rank=same; F" + std::to_string(numFilaActual);

        auto colActual = primerColumna;
        int numColActual = 0;

        while (colActual)
        {
            // Buscar si hay un nodo en esta posición
            auto nodo = buscarNodoEnPosicion(filaActual->primerNodo, colActual->primerNodo);
            if (nodo)
            {

                std::string nombreCompleto = nodo->usuario->Nombre;

                Nodo *nodoAdelante = nodo->adelante.get();

                while (nodoAdelante)
                {
                    nombreCompleto += "\\n" + nodoAdelante->usuario->Nombre;
                    nodoAdelante = nodoAdelante->adelante.get();
                }

                out << nodo->usuario->id
                    << R"( [label=")" << nombreCompleto << R"("; )"
                    << NODE_STYLE << R"(; fillcolor=lightgreen; group=)" << numColActual + 1 << "];\n";

                if (nodo->derecha)
                {
                    out << nodo->usuario->id << " -> " << nodo->derecha->usuario->id << ";\n";
                    out << nodo->derecha->usuario->id << " -> " << nodo->usuario->id << ";\n";
                }

                if (nodo->abajo)
                {
                    out << nodo->usuario->id << " -> " << nodo->abajo->usuario->id << ";\n";
                    out << nodo->abajo->usuario->id << " -> " << nodo->usuario->id << ";\n";
                }

                subgrafosFilas += "; " + std::to_string(nodo->usuario->id);
            }

            colActual = colActual->siguiente;

            numColActual++;
        }

        subgrafosFilas += "};\n";
        out << subgrafosFilas;

        filaActual = filaActual->siguiente;
        numFilaActual++;
    }
}

/**
 * @brief Busca un nodo en una posición específica de la matriz
 * @param nodoFila Nodo inicial de la fila
 * @param nodoCol Nodo inicial de la columna
 * @return Puntero al nodo encontrado o nullptr si no existe
 */
Nodo *MatrizDispersa::buscarNodoEnPosicion(const std::shared_ptr<Nodo> &nodoFila, const std::shared_ptr<Nodo> &nodoCol)
{
    auto actual = nodoFila;
    while (actual)
    {
        auto actualCol = nodoCol;
        while (actualCol)
        {
            if (actual == actualCol)
                return actual.get();
            actualCol = actualCol->abajo;
        }
        actual = actual->derecha;
    }
    return nullptr;
}

Nodo *MatrizDispersa::buscarNodoEnPosicionPorDepartamentoEmpresa(const std::string &empresa,
                                                                 const std::string &departamento)
{
    auto actualFila = primerFila;
    while (actualFila)
    {
        if (actualFila->nombre == empresa)
        {
            auto actualCol = primerColumna;
            while (actualCol)
            {
                if (actualCol->nombre == departamento)
                {
                    return buscarNodoEnPosicion(actualFila->primerNodo, actualCol->primerNodo);
                }
                actualCol = actualCol->siguiente;
            }
        }
        actualFila = actualFila->siguiente;
    }
    return nullptr;
}

/**
 * @brief Busca un usuario por su nombre en una posición específica
 * @param nombre Nombre del usuario a buscar
 * @param departamento Departamento donde buscar
 * @param empresa Empresa donde buscar
 * @return Puntero al usuario encontrado o nullptr si no existe
 */
Usuario *MatrizDispersa::buscarUsuarioPorNombre(const std::string &nombre, const std::string &departamento, const std::string &empresa)
{
    // Buscar nodo empresa
    auto nodo = buscarNodoEnPosicionPorDepartamentoEmpresa(empresa, departamento);

    // Buscar usuario en la lista de nodos
    while (nodo)
    {
        if (nodo->usuario->Nombre == nombre)
            return nodo->usuario.get();
        nodo = nodo->adelante.get();
    }

    return nullptr;
}

/**
 * @brief Muestra los activos de todos los usuarios excepto uno específico
 * @param userId ID del usuario cuyos activos no se mostrarán
 */
void MatrizDispersa::mostrarActivosDeMatriz(
    int userId)
{
    auto filaActual = primerFila;

    while (filaActual)
    {
        auto colActual = primerColumna;

        while (colActual)
        {

            auto nodo = buscarNodoEnPosicion(filaActual->primerNodo, colActual->primerNodo);

            while (nodo)
            {
                if (nodo->usuario->id != userId)
                    nodo->usuario->mostrarActivos();
                nodo = nodo->adelante.get();
            }

            colActual = colActual->siguiente;
        }

        filaActual = filaActual->siguiente;
    }
}

/**
 * @brief Busca un activo específico en toda la matriz
 * @param idActivo Identificador del activo a buscar
 * @return Puntero al activo encontrado o nullptr si no existe
 */
Activo *MatrizDispersa::buscarActivosDeMatriz(const std::string &idActivo)
{
    auto filaActual = primerFila;

    while (filaActual)
    {
        auto colActual = primerColumna;

        while (colActual)
        {

            auto nodo = buscarNodoEnPosicion(filaActual->primerNodo, colActual->primerNodo);

            while (nodo)
            {
                auto activo = nodo->usuario->buscarActivo(idActivo);
                if (activo)
                    return activo;
                nodo = nodo->adelante.get();
            }

            colActual = colActual->siguiente;
        }

        filaActual = filaActual->siguiente;
    }

    return nullptr;
}

/**
 * @brief Genera un árbol AVL con los activos de una empresa específica
 * @param empresa Nombre de la empresa
 * @return Puntero al árbol AVL generado
 */
AVL *MatrizDispersa::arbolAVLEmpresas(const std::string &empresa)
{
    auto actualFila = primerFila;
    AVL *arbol = new AVL();

    std::cout << "Contenido del árbol antes de la fusión:" << std::endl;

    // Recorrer hasta encontrar la fila de la empresa
    while (actualFila)
    {
        if (actualFila->nombre == empresa)
        {
            std::cout << "Empresa encontrada: " << empresa << std::endl;

            // Solo procesar los nodos de esta empresa
            auto actualCol = primerColumna;
            while (actualCol)
            {
                auto nodo = buscarNodoEnPosicion(actualFila->primerNodo, actualCol->primerNodo);

                // Recorrer todos los nodos hacia adelante en esta posición
                while (nodo)
                {
                    if (nodo->usuario && nodo->usuario->activos)
                    {
                        arbol->fusionar(*nodo->usuario->activos);
                    }
                    nodo = nodo->adelante.get();
                }

                actualCol = actualCol->siguiente;
            }
            break; // Una vez procesada la empresa, terminamos
        }
        actualFila = actualFila->siguiente;
    }

    std::cout << "Contenido del árbol resultante:" << std::endl;
    arbol->inorden();

    return arbol;
}

/**
 * @brief Genera un árbol AVL con los activos de un departamento específico
 * @param departamento Nombre del departamento
 * @return Puntero al árbol AVL generado
 */
AVL *MatrizDispersa::arbolAVLDepartamentos(const std::string &departamento)
{
    auto actualCol = primerColumna;
    AVL *arbol = new AVL();

    // Recorrer hasta encontrar la columna del departamento
    while (actualCol)
    {
        if (actualCol->nombre == departamento)
        {
            std::cout << "Departamento encontrado: " << departamento << std::endl;

            // Solo procesar los nodos de este departamento
            auto actualFila = primerFila;
            while (actualFila)
            {
                auto nodo = buscarNodoEnPosicion(actualFila->primerNodo, actualCol->primerNodo);

                // Recorrer todos los nodos hacia adelante en esta posición
                while (nodo)
                {
                    if (nodo->usuario && nodo->usuario->activos)
                    {
                        arbol->fusionar(*nodo->usuario->activos);
                    }
                    nodo = nodo->adelante.get();
                }

                actualFila = actualFila->siguiente;
            }
            break; // Una vez procesado el departamento, terminamos
        }
        actualCol = actualCol->siguiente;
    }

    std::cout << "Contenido del árbol resultante:" << std::endl;
    arbol->inorden();

    return arbol;
}