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
 * @param departamento Nombre del departamento.
 * @param empresa Nombre de la empresa.
 * @param usuario Puntero compartido al usuario a insertar.
 */
void MatrizDispersa::insertar(const std::string &departamento, const std::string &empresa,
                              const std::shared_ptr<Usuario> &usuario)
{
    // Crear o encontrar la fila (departamento)
    auto actualFila = primerFila;
    std::shared_ptr<NodoCabecera> filaAnterior = nullptr;
    while (actualFila && actualFila->nombre != departamento)
    {
        filaAnterior = actualFila;
        actualFila = actualFila->siguiente;
    }
    if (!actualFila)
    {
        actualFila = std::make_shared<NodoCabecera>(departamento);
        if (filaAnterior)
            filaAnterior->siguiente = actualFila;
        else
            primerFila = actualFila;
    }

    // Crear o encontrar la columna (empresa)
    auto actualColumna = primerColumna;
    std::shared_ptr<NodoCabecera> columnaAnterior = nullptr;
    while (actualColumna && actualColumna->nombre != empresa)
    {
        columnaAnterior = actualColumna;
        actualColumna = actualColumna->siguiente;
    }
    if (!actualColumna)
    {
        actualColumna = std::make_shared<NodoCabecera>(empresa);
        if (columnaAnterior)
            columnaAnterior->siguiente = actualColumna;
        else
            primerColumna = actualColumna;
    }

    // Crear el nodo para almacenar la persona
    auto nuevoNodo = std::make_shared<Nodo>(usuario);

    // Insertar en la fila (horizontalmente)
    auto actual = actualFila->primerNodo;
    std::shared_ptr<Nodo> anterior = nullptr;
    while (actual)
    {
        if (actual->usuario->Nombre == usuario->Nombre)
        {
            // Insertar en el nodo de adelante
            while (actual->adelante)
                actual = actual->adelante;
            actual->adelante = nuevoNodo;
            nuevoNodo->atras = actual;
            return;
        }
        anterior = actual;
        actual = actual->derecha;
    }
    if (anterior)
    {
        anterior->derecha = nuevoNodo;
        nuevoNodo->izquierda = anterior;
    }
    else
        actualFila->primerNodo = nuevoNodo;

    // Insertar en la columna (verticalmente)
    actual = actualColumna->primerNodo;
    anterior = nullptr;
    while (actual)
    {
        if (actual->usuario->Nombre == usuario->Nombre)
        {
            // Insertar en el nodo de adelante
            while (actual->adelante)
                actual = actual->adelante;
            actual->adelante = nuevoNodo;
            nuevoNodo->atras = actual;
            return;
        }
        anterior = actual;
        actual = actual->abajo;
    }
    if (anterior)
    {
        anterior->abajo = nuevoNodo;
        nuevoNodo->arriba = anterior;
    }
    else
        actualColumna->primerNodo = nuevoNodo;
}

/**
 * @brief Muestra la matriz dispersa en la consola.
 */
void MatrizDispersa::mostrar()
{
    if (!primerFila || !primerColumna)
    {
        std::cout << "Matriz vacia" << std::endl;
        return;
    }

    // Imprimir encabezado
    std::cout << "DEPARTAMENTO";
    auto colActual = primerColumna;
    while (colActual)
    {
        std::cout << " | " << colActual->nombre;
        colActual = colActual->siguiente;
    }
    std::cout << std::endl;

    // Imprimir línea separadora
    std::cout << "-----------";
    colActual = primerColumna;
    while (colActual)
    {
        std::cout << "-+--------";
        colActual = colActual->siguiente;
    }
    std::cout << std::endl;

    // Imprimir contenido
    auto filaActual = primerFila;
    while (filaActual)
    {
        std::cout << filaActual->nombre;

        colActual = primerColumna;
        while (colActual)
        {
            std::cout << " | ";

            // Buscar si hay un nodo en esta posición
            bool encontrado = false;
            auto nodoFila = filaActual->primerNodo;
            while (nodoFila)
            {
                auto nodoCol = colActual->primerNodo;
                while (nodoCol)
                {
                    if (nodoFila == nodoCol)
                    {
                        std::cout << nodoFila->usuario->Nombre;
                        encontrado = true;
                        break;
                    }
                    nodoCol = nodoCol->abajo;
                }
                if (encontrado)
                    break;
                nodoFila = nodoFila->derecha;
            }

            if (!encontrado)
            {
                std::cout << "        "; // Espacio en blanco para posiciones vacías
            }

            colActual = colActual->siguiente;
        }
        std::cout << std::endl;
        filaActual = filaActual->siguiente;
    }
}