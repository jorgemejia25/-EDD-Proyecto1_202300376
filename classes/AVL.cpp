// AVL.cpp
#include "AVL.h"
#include <algorithm>
#include <iostream>

/**
 * Obtiene la altura de un nodo específico
 * @param nodo Nodo del cual se obtendrá la altura
 * @return Altura del nodo (0 si el nodo es nullptr)
 */
int AVL::getAltura(std::shared_ptr<Nodo> nodo)
{
    if (!nodo)
        return 0;
    return nodo->altura;
}

/**
 * Calcula el factor de balance de un nodo
 * @param nodo Nodo del cual se calculará el balance
 * @return Factor de balance (altura izquierda - altura derecha)
 */
int AVL::getBalance(std::shared_ptr<Nodo> nodo)
{
    if (!nodo)
        return 0;
    return getAltura(nodo->izquierdo) - getAltura(nodo->derecho);
}

/**
 * Realiza una rotación a la derecha sobre el nodo y
 * @param y Nodo sobre el cual se realizará la rotación
 * @return Nuevo nodo raíz después de la rotación
 */
std::shared_ptr<AVL::Nodo> AVL::rotacionDerecha(std::shared_ptr<Nodo> y)
{
    std::shared_ptr<Nodo> x = y->izquierdo;
    std::shared_ptr<Nodo> T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    y->altura = std::max(getAltura(y->izquierdo), getAltura(y->derecho)) + 1;
    x->altura = std::max(getAltura(x->izquierdo), getAltura(x->derecho)) + 1;

    return x;
}

/**
 * Realiza una rotación a la izquierda sobre el nodo x
 * @param x Nodo sobre el cual se realizará la rotación
 * @return Nuevo nodo raíz después de la rotación
 */
std::shared_ptr<AVL::Nodo> AVL::rotacionIzquierda(std::shared_ptr<Nodo> x)
{
    std::shared_ptr<Nodo> y = x->derecho;
    std::shared_ptr<Nodo> T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    x->altura = std::max(getAltura(x->izquierdo), getAltura(x->derecho)) + 1;
    y->altura = std::max(getAltura(y->izquierdo), getAltura(y->derecho)) + 1;

    return y;
}

/**
 * Función recursiva auxiliar para insertar un activo en el árbol
 * @param nodo Nodo actual en la recursión
 * @param activo Activo a insertar
 * @return Nuevo nodo raíz del subárbol modificado
 */
std::shared_ptr<AVL::Nodo> AVL::insertarRec(std::shared_ptr<Nodo> nodo, const Activo &activo)
{
    if (!nodo)
    {
        return std::make_shared<Nodo>(activo);
    }

    if (activo.getId() < nodo->activo.getId())
        nodo->izquierdo = insertarRec(nodo->izquierdo, activo);
    else if (activo.getId() > nodo->activo.getId())
        nodo->derecho = insertarRec(nodo->derecho, activo);
    else
        return nodo; // No permitir duplicados

    nodo->altura = 1 + std::max(getAltura(nodo->izquierdo), getAltura(nodo->derecho));

    int balance = getBalance(nodo);

    // Casos de rotación
    if (balance > 1 && activo.getId() < nodo->izquierdo->activo.getId())
        return rotacionDerecha(nodo);

    if (balance < -1 && activo.getId() > nodo->derecho->activo.getId())
        return rotacionIzquierda(nodo);

    if (balance > 1 && activo.getId() > nodo->izquierdo->activo.getId())
    {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && activo.getId() < nodo->derecho->activo.getId())
    {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

/**
 * Inserta un nuevo activo en el árbol AVL
 * @param activo Activo a insertar
 */
void AVL::insertar(const Activo &activo)
{
    raiz = insertarRec(raiz, activo);
}

/**
 * Función recursiva auxiliar para buscar un activo por su ID
 * @param nodo Nodo actual en la recursión
 * @param id ID del activo a buscar
 * @return Puntero al nodo encontrado o nullptr si no existe
 */
std::shared_ptr<AVL::Nodo> AVL::buscarRec(std::shared_ptr<Nodo> nodo, const std::string &id)
{
    if (!nodo || nodo->activo.getId() == id)
        return nodo;

    if (id < nodo->activo.getId())
        return buscarRec(nodo->izquierdo, id);

    return buscarRec(nodo->derecho, id);
}

/**
 * Busca un activo por su ID en el árbol
 * @param id ID del activo a buscar
 * @return Puntero al activo encontrado o nullptr si no existe
 */
Activo *AVL::buscar(const std::string &id)
{
    auto nodo = buscarRec(raiz, id);
    return nodo ? &(nodo->activo) : nullptr;
}

/**
 * Recorre el árbol en orden (inorden) de forma recursiva
 * Imprime solo los activos que no están rentados
 * @param nodo Nodo actual en la recursión
 */
void AVL::inordenRec(std::shared_ptr<Nodo> nodo) const
{
    if (nodo)
    {
        inordenRec(nodo->izquierdo);
        if (!nodo->activo.getRentado())
            std::cout << nodo->activo.toString() << "\n\n";
        inordenRec(nodo->derecho);
    }
}

/**
 * Inicia el recorrido inorden del árbol
 */
void AVL::inorden() const
{
    inordenRec(raiz);
}

/**
 * Genera la representación DOT del árbol para visualización
 * @param out Stream de salida donde se escribirá el código DOT
 */
void AVL::generarDot(std::ostream &out) const
{
    out << "digraph G {\n";
    out << "    node [shape=circle, style=filled, fillcolor=lightblue];\n";
    out << "    rankdir=TB;\n\n";

    if (raiz)
    {
        generarDotRecursivo(out, raiz);
    }

    out << "}\n";
}

/**
 * Función auxiliar recursiva para generar el código DOT
 * @param out Stream de salida
 * @param nodo Nodo actual en la recursión
 */
void AVL::generarDotRecursivo(std::ostream &out, std::shared_ptr<Nodo> nodo) const
{
    if (!nodo)
        return;

    // Generar el nodo actual
    out << "    \"" << nodo->activo.getId() << "\" [label=\"ID: "
        << nodo->activo.getId() << "\\n"
        << "Nombre: "
        << nodo->activo.getNombre() << "\\n"
        << "Descripción: "
        << nodo->activo.getDescripcion() << "\\n"
        << "Rentado: "
        << nodo->activo.getRentado()
        << "\"];\n";

    // Generar conexiones con hijos
    if (nodo->izquierdo)
    {
        out << "    \"" << nodo->activo.getId() << "\" -> \""
            << nodo->izquierdo->activo.getId() << "\";\n";
        generarDotRecursivo(out, nodo->izquierdo);
    }

    if (nodo->derecho)
    {
        out << "    \"" << nodo->activo.getId() << "\" -> \""
            << nodo->derecho->activo.getId() << "\";\n";
        generarDotRecursivo(out, nodo->derecho);
    }
}

/**
 * Encuentra el nodo con el valor mínimo en un subárbol
 * @param nodo Raíz del subárbol
 * @return Puntero al nodo con el valor mínimo
 */
std::shared_ptr<AVL::Nodo> AVL::getNodoMinimo(std::shared_ptr<Nodo> nodo)
{
    std::shared_ptr<Nodo> actual = nodo;
    while (actual && actual->izquierdo)
    {
        actual = actual->izquierdo;
    }
    return actual;
}

/**
 * Función recursiva auxiliar para eliminar un nodo del árbol
 * @param nodo Nodo actual en la recursión
 * @param id ID del activo a eliminar
 * @return Nuevo nodo raíz del subárbol modificado
 */
std::shared_ptr<AVL::Nodo> AVL::eliminarRec(std::shared_ptr<Nodo> nodo, const std::string &id)
{
    if (!nodo)
        return nullptr;

    if (id < nodo->activo.getId())
        nodo->izquierdo = eliminarRec(nodo->izquierdo, id);
    else if (id > nodo->activo.getId())
        nodo->derecho = eliminarRec(nodo->derecho, id);
    else
    {
        // Nodo con un hijo o sin hijos
        if (!nodo->izquierdo || !nodo->derecho)
        {
            std::shared_ptr<Nodo> temp = nodo->izquierdo ? nodo->izquierdo : nodo->derecho;
            if (!temp)
            {
                temp = nodo;
                nodo = nullptr;
            }
            else
            {
                *nodo = *temp;
            }
        }
        else
        {
            // Nodo con dos hijos
            std::shared_ptr<Nodo> temp = getNodoMinimo(nodo->derecho);
            nodo->activo = temp->activo;
            nodo->derecho = eliminarRec(nodo->derecho, temp->activo.getId());
        }
    }

    if (!nodo)
        return nullptr;

    // Actualizar altura
    nodo->altura = 1 + std::max(getAltura(nodo->izquierdo), getAltura(nodo->derecho));

    // Verificar balance
    int balance = getBalance(nodo);

    // Casos de rotación
    if (balance > 1 && getBalance(nodo->izquierdo) >= 0)
        return rotacionDerecha(nodo);

    if (balance > 1 && getBalance(nodo->izquierdo) < 0)
    {
        nodo->izquierdo = rotacionIzquierda(nodo->izquierdo);
        return rotacionDerecha(nodo);
    }

    if (balance < -1 && getBalance(nodo->derecho) <= 0)
        return rotacionIzquierda(nodo);

    if (balance < -1 && getBalance(nodo->derecho) > 0)
    {
        nodo->derecho = rotacionDerecha(nodo->derecho);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

/**
 * Elimina un activo del árbol por su ID
 * @param id ID del activo a eliminar
 */
void AVL::eliminar(const std::string &id)
{
    raiz = eliminarRec(raiz, id);
}

/**
 * Función recursiva auxiliar para fusionar dos árboles AVL
 * @param nodo Nodo actual del árbol a fusionar
 */
void AVL::fusionarRec(std::shared_ptr<Nodo> nodo)
{
    if (!nodo)
        return;

    // Insertar el nodo actual en el árbol
    insertar(nodo->activo);

    // Recorrer los subárboles izquierdo y derecho
    fusionarRec(nodo->izquierdo);
    fusionarRec(nodo->derecho);
}

/**
 * Fusiona otro árbol AVL con el árbol actual
 * @param otroArbol Árbol AVL a fusionar con el actual
 */
void AVL::fusionar(AVL &otroArbol)
{
    if (otroArbol.estaVacio())
        return;

    // Recorrer el árbol recibido en orden e insertar cada nodo en el árbol actual
    fusionarRec(otroArbol.raiz);
}