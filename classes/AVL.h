// AVL.h
#ifndef AVL_H
#define AVL_H

#include "Activo.h"
#include <ostream>
#include <string>
#include <memory>

/**
 * @brief Implementación de un árbol AVL para gestionar activos
 * 
 * Esta clase implementa un árbol binario de búsqueda balanceado (AVL)
 * que mantiene automáticamente el equilibrio durante las operaciones
 * de inserción y eliminación.
 */
class AVL
{
private:
    /**
     * @brief Estructura del nodo del árbol AVL
     */
    struct Nodo
    {
        Activo activo;                  ///< Datos del activo almacenado
        std::shared_ptr<Nodo> izquierdo; ///< Puntero al hijo izquierdo
        std::shared_ptr<Nodo> derecho;   ///< Puntero al hijo derecho
        int altura;                      ///< Altura del nodo en el árbol

        /**
         * @brief Constructor del nodo
         * @param _activo Activo a almacenar en el nodo
         */
        Nodo(const Activo &_activo)
            : activo(_activo), izquierdo(nullptr), derecho(nullptr), altura(1) {}
    };

    std::shared_ptr<Nodo> raiz; ///< Raíz del árbol AVL

    // Métodos auxiliares privados
    /**
     * @brief Obtiene la altura de un nodo
     * @param nodo Nodo a consultar
     * @return Altura del nodo, 0 si es nullptr
     */
    int getAltura(std::shared_ptr<Nodo> nodo);

    /**
     * @brief Calcula el factor de balance de un nodo
     * @param nodo Nodo a evaluar
     * @return Factor de balance
     */
    int getBalance(std::shared_ptr<Nodo> nodo);

    /**
     * @brief Realiza una rotación hacia la derecha
     * @param y Nodo sobre el que se realiza la rotación
     * @return Nuevo nodo raíz después de la rotación
     */
    std::shared_ptr<Nodo> rotacionDerecha(std::shared_ptr<Nodo> y);

    /**
     * @brief Realiza una rotación hacia la izquierda
     * @param x Nodo sobre el que se realiza la rotación
     * @return Nuevo nodo raíz después de la rotación
     */
    std::shared_ptr<Nodo> rotacionIzquierda(std::shared_ptr<Nodo> x);

    /**
     * @brief Inserta recursivamente un activo en el árbol
     * @param nodo Nodo actual
     * @param activo Activo a insertar
     * @return Nuevo nodo raíz del subárbol
     */
    std::shared_ptr<Nodo> insertarRec(std::shared_ptr<Nodo> nodo, const Activo &activo);

    /**
     * @brief Busca recursivamente un activo por su ID
     * @param nodo Nodo actual
     * @param id ID del activo a buscar
     * @return Nodo encontrado o nullptr
     */
    std::shared_ptr<Nodo> buscarRec(std::shared_ptr<Nodo> nodo, const std::string &id);

    /**
     * @brief Recorre el árbol en inorden de forma recursiva
     * @param nodo Nodo actual
     */
    void inordenRec(std::shared_ptr<Nodo> nodo) const;

    /**
     * @brief Genera la representación DOT del árbol recursivamente
     * @param out Stream de salida
     * @param nodo Nodo actual
     */
    void generarDotRecursivo(std::ostream &out, std::shared_ptr<Nodo> nodo) const;

    /**
     * @brief Elimina recursivamente un nodo por su ID
     * @param nodo Nodo actual
     * @param id ID del activo a eliminar
     * @return Nuevo nodo raíz del subárbol
     */
    std::shared_ptr<Nodo> eliminarRec(std::shared_ptr<Nodo> nodo, const std::string &id);

    /**
     * @brief Obtiene el nodo con el valor mínimo en un subárbol
     * @param nodo Raíz del subárbol
     * @return Nodo con el valor mínimo
     */
    std::shared_ptr<Nodo> getNodoMinimo(std::shared_ptr<Nodo> nodo);

    /**
     * @brief Fusiona recursivamente los nodos de otro árbol
     * @param nodo Nodo actual del árbol a fusionar
     */
    void fusionarRec(std::shared_ptr<Nodo> nodo);

public:
    /**
     * @brief Constructor por defecto
     */
    AVL() : raiz(nullptr) {}

    /**
     * @brief Inserta un nuevo activo en el árbol
     * @param activo Activo a insertar
     */
    void insertar(const Activo &activo);

    /**
     * @brief Busca un activo por su ID
     * @param id ID del activo a buscar
     * @return Puntero al activo encontrado o nullptr si no existe
     */
    Activo *buscar(const std::string &id);

    /**
     * @brief Elimina un activo del árbol
     * @param id ID del activo a eliminar
     */
    void eliminar(const std::string &id);

    /**
     * @brief Realiza un recorrido inorden del árbol
     */
    void inorden() const;

    /**
     * @brief Verifica si el árbol está vacío
     * @return true si está vacío, false en caso contrario
     */
    bool estaVacio() const { return raiz == nullptr; }

    /**
     * @brief Genera la representación DOT del árbol
     * @param out Stream de salida donde se escribirá el código DOT
     */
    void generarDot(std::ostream &out) const;

    /**
     * @brief Fusiona otro árbol AVL con este
     * @param arbol Árbol a fusionar
     */
    void fusionar(AVL &arbol);
};

#endif