// AVL.cpp
#include "AVL.h"
#include <algorithm>
#include <iostream>

int AVL::getAltura(std::shared_ptr<Nodo> nodo)
{
    if (!nodo)
        return 0;
    return nodo->altura;
}

int AVL::getBalance(std::shared_ptr<Nodo> nodo)
{
    if (!nodo)
        return 0;
    return getAltura(nodo->izquierdo) - getAltura(nodo->derecho);
}

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

void AVL::insertar(const Activo &activo)
{
    raiz = insertarRec(raiz, activo);
}

std::shared_ptr<AVL::Nodo> AVL::buscarRec(std::shared_ptr<Nodo> nodo, const std::string &id)
{
    if (!nodo || nodo->activo.getId() == id)
        return nodo;

    if (id < nodo->activo.getId())
        return buscarRec(nodo->izquierdo, id);

    return buscarRec(nodo->derecho, id);
}

Activo *AVL::buscar(const std::string &id)
{
    auto nodo = buscarRec(raiz, id);
    return nodo ? &(nodo->activo) : nullptr;
}

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

void AVL::inorden() const
{
    inordenRec(raiz);
}

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

void AVL::generarDotRecursivo(std::ostream &out, std::shared_ptr<Nodo> nodo) const
{
    if (!nodo)
        return;

    // Generar el nodo actual
    out << "    \"" << nodo->activo.getId() << "\" [label=\"ID: "
        << nodo->activo.getId() << "\\n"
        << nodo->activo.getNombre() << "\"];\n";

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

std::shared_ptr<AVL::Nodo> AVL::getNodoMinimo(std::shared_ptr<Nodo> nodo)
{
    std::shared_ptr<Nodo> actual = nodo;
    while (actual && actual->izquierdo)
    {
        actual = actual->izquierdo;
    }
    return actual;
}

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

void AVL::eliminar(const std::string &id)
{
    raiz = eliminarRec(raiz, id);
}

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

void AVL::fusionar(AVL &otroArbol)
{
    if (otroArbol.estaVacio())
        return;

    // Recorrer el árbol recibido en orden e insertar cada nodo en el árbol actual
    fusionarRec(otroArbol.raiz);
}