#include "MatrizDispersa.h"
#include <iostream>

// Inicializar la instancia estática a nullptr
std::shared_ptr<MatrizDispersa> MatrizDispersa::instancia = nullptr;

// Constructor de Nodo
Nodo::Nodo(const std::shared_ptr<Usuario> &usuario)
    : usuario(usuario), izquierda(nullptr), derecha(nullptr),
      arriba(nullptr), abajo(nullptr), adelante(nullptr), atras(nullptr) {}

// Constructor de NodoCabecera
NodoCabecera::NodoCabecera(const std::string &nombre)
    : nombre(nombre), siguiente(nullptr), primerNodo(nullptr) {}

// Constructor privado de MatrizDispersa
MatrizDispersa::MatrizDispersa() : primerFila(nullptr), primerColumna(nullptr) {}

// Función estática para obtener la instancia única
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

    // Crear o encontrar la fila (empresa)
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
        nuevaFila->siguiente = actualFila;
        if (filaAnterior)
            filaAnterior->siguiente = nuevaFila;
        else
            primerFila = nuevaFila;
        actualFila = nuevaFila;
    }

    // Crear o encontrar la columna (departamento)
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
        nuevaColumna->siguiente = actualColumna;
        if (columnaAnterior)
            columnaAnterior->siguiente = nuevaColumna;
        else
            primerColumna = nuevaColumna;
        actualColumna = nuevaColumna;
    }

    // Crear el nodo para almacenar la persona

    // Insertar en la fila (horizontalmente)
    auto actual = actualFila->primerNodo;
    std::shared_ptr<Nodo> anterior = nullptr;
    while (actual && actual->usuario->id < usuario->id) // Cambio de Nombre a id
    {
        anterior = actual;
        actual = actual->derecha;
    }
    if (!anterior)
    {
        nuevoNodo->derecha = actual;
        if (actual)
            actual->izquierda = nuevoNodo;
        actualFila->primerNodo = nuevoNodo;
    }
    else
    {
        nuevoNodo->derecha = actual;
        nuevoNodo->izquierda = anterior;
        anterior->derecha = nuevoNodo;
        if (actual)
            actual->izquierda = nuevoNodo;
    }

    // Insertar en la columna (verticalmente)
    actual = actualColumna->primerNodo;
    anterior = nullptr;
    bool insertado = false;

    // Buscar la posición correcta dentro de la columna actual y el empresa correspondiente
    while (actual)
    {
        // Verificar si estamos en el empresa correcto
        auto nodoFila = actualFila->primerNodo;
        while (nodoFila)
        {
            if (nodoFila == actual)
            {
                // Estamos en el empresa correcto, insertar aquí
                nuevoNodo->abajo = actual;
                nuevoNodo->arriba = anterior;
                if (anterior)
                {
                    anterior->abajo = nuevoNodo;
                }
                else
                {
                    actualColumna->primerNodo = nuevoNodo;
                }
                if (actual)
                {
                    actual->arriba = nuevoNodo;
                }
                insertado = true;
                break;
            }
            nodoFila = nodoFila->derecha;
        }
        if (insertado)
            break;

        anterior = actual;
        actual = actual->abajo;
    }

    // Si no se insertó en ninguna posición intermedia, agregar al final
    if (!insertado)
    {
        if (anterior)
        {
            anterior->abajo = nuevoNodo;
            nuevoNodo->arriba = anterior;
        }
        else
        {
            actualColumna->primerNodo = nuevoNodo;
        }
    }
}

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