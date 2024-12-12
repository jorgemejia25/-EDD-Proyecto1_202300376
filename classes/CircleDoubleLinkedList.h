#ifndef CIRCLE_DOUBLE_LINKED_LIST_H
#define CIRCLE_DOUBLE_LINKED_LIST_H

#include "Transaction.h"
#include "AVL.h"

/**
 * @brief Clase que representa un nodo en la lista circular doblemente enlazada
 */
class Node
{
public:
    Transaction *data;     // Datos de la transacción
    Node *next;           // Puntero al siguiente nodo
    Node *prev;           // Puntero al nodo anterior

    /**
     * @brief Constructor del nodo
     * @param transaction Puntero a la transacción a almacenar
     */
    Node(Transaction *transaction)
    {
        this->data = transaction;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

/**
 * @brief Lista circular doblemente enlazada implementada como Singleton
 */
class CircleDoubleLinkedList
{
private:
    Node *head;          // Puntero al primer nodo de la lista
    int size;           // Tamaño actual de la lista
    static CircleDoubleLinkedList *instance;  // Instancia única del Singleton

    /**
     * @brief Constructor privado (patrón Singleton)
     */
    CircleDoubleLinkedList();

    // Prevenir copia
    CircleDoubleLinkedList(const CircleDoubleLinkedList &) = delete;
    CircleDoubleLinkedList &operator=(const CircleDoubleLinkedList &) = delete;

public:
    /**
     * @brief Destructor de la lista
     */
    ~CircleDoubleLinkedList();

    /**
     * @brief Obtiene la instancia única de la lista
     * @return Puntero a la instancia de la lista
     */
    static CircleDoubleLinkedList *getInstance();

    /**
     * @brief Inserta una nueva transacción en la lista
     * @param transaction Puntero a la transacción a insertar
     */
    void insertTransaction(Transaction *transaction);

    /**
     * @brief Elimina una transacción de la lista
     * @param id ID de la transacción a eliminar
     */
    void deleteTransaction(std::string id);

    /**
     * @brief Busca una transacción en la lista
     * @param id ID de la transacción a buscar
     * @return Puntero a la transacción encontrada o nullptr si no existe
     */
    Transaction *searchTransaction(std::string id);

    /**
     * @brief Verifica si la lista está vacía
     * @return true si está vacía, false en caso contrario
     */
    bool isEmpty();

    /**
     * @brief Obtiene el tamaño actual de la lista
     * @return Número de elementos en la lista
     */
    int getSize();

    /**
     * @brief Imprime todas las transacciones de la lista
     */
    void print();

    /**
     * @brief Imprime las transacciones activas de un usuario
     * @param userId ID del usuario
     */
    void printActiveTransactions(int userId);

    /**
     * @brief Imprime las transacciones inactivas de un usuario
     * @param userId ID del usuario
     */
    void printInactiveTransactions(int userId);

    /**
     * @brief Imprime todas las transacciones de un usuario
     * @param userId ID del usuario
     */
    void printMyTransactions(int userId);

    /**
     * @brief Imprime los detalles de una transacción específica
     * @param id ID de la transacción
     */
    void printTransactionDetails(std::string id);

    /**
     * @brief Genera la representación DOT de la lista
     * @param out Stream de salida donde se escribirá el DOT
     */
    void generarDot(std::ostream &out);

    /**
     * @brief Ordena las transacciones
     * @param desc true para orden descendente, false para ascendente
     */
    void ordenarTransacciones(bool desc);

    /**
     * @brief Obtiene los activos rentados por un usuario
     * @param userId ID del usuario
     * @return Árbol AVL con los activos rentados
     */
    AVL *getRentedAssets(int userId);
};

#endif
