// AVL.h
#ifndef AVL_H
#define AVL_H

#include "Activo.h"
#include <ostream>
#include <string>
#include <memory>

class AVL
{
private:
    struct Nodo
    {
        Activo activo;
        std::shared_ptr<Nodo> izquierdo;
        std::shared_ptr<Nodo> derecho;
        int altura;

        Nodo(const Activo &_activo)
            : activo(_activo), izquierdo(nullptr), derecho(nullptr), altura(1) {}
    };

    std::shared_ptr<Nodo> raiz;

    // Métodos auxiliares privados
    int getAltura(std::shared_ptr<Nodo> nodo);
    int getBalance(std::shared_ptr<Nodo> nodo);
    std::shared_ptr<Nodo> rotacionDerecha(std::shared_ptr<Nodo> y);
    std::shared_ptr<Nodo> rotacionIzquierda(std::shared_ptr<Nodo> x);
    std::shared_ptr<Nodo> insertarRec(std::shared_ptr<Nodo> nodo, const Activo &activo);
    std::shared_ptr<Nodo> buscarRec(std::shared_ptr<Nodo> nodo, const std::string &id);
    void inordenRec(std::shared_ptr<Nodo> nodo) const;
    void generarDotRecursivo(std::ostream &out, std::shared_ptr<Nodo> nodo) const;
    std::shared_ptr<Nodo> eliminarRec(std::shared_ptr<Nodo> nodo, const std::string &id);
    std::shared_ptr<Nodo> getNodoMinimo(std::shared_ptr<Nodo> nodo);
    void fusionarRec(std::shared_ptr<Nodo> nodo);

public:
    AVL() : raiz(nullptr) {}

    // Operaciones básicas
    void insertar(const Activo &activo);
    Activo *buscar(const std::string &id);
    void eliminar(const std::string &id);
    void inorden() const;
    bool estaVacio() const { return raiz == nullptr; }
    void generarDot(std::ostream &out) const;
    void fusionar(AVL &arbol);
};

#endif