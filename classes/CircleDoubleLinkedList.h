#ifndef CIRCLE_DOUBLE_LINKED_LIST_H
#define CIRCLE_DOUBLE_LINKED_LIST_H

#include "Transaction.h"
#include "AVL.h"

class Node
{
public:
    Transaction *data;
    Node *next;
    Node *prev;

    Node(Transaction *transaction)
    {
        this->data = transaction;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

class CircleDoubleLinkedList
{
private:
    Node *head;
    int size;
    static CircleDoubleLinkedList *instance;

    // Constructor privado
    CircleDoubleLinkedList();

    // Prevenir copia
    CircleDoubleLinkedList(const CircleDoubleLinkedList &) = delete;
    CircleDoubleLinkedList &operator=(const CircleDoubleLinkedList &) = delete;

public:
    // Destructor público
    ~CircleDoubleLinkedList();

    // Método estático para obtener instancia
    static CircleDoubleLinkedList *getInstance();

    void insertTransaction(Transaction *transaction);
    void deleteTransaction(std::string id);
    Transaction *searchTransaction(std::string id);
    bool isEmpty();
    int getSize();
    void print();
    void printActiveTransactions(int userId);
    void printInactiveTransactions(int userId);
    void printMyTransactions(int userId);
    void printTransactionDetails(std::string id); // Nuevo método
    void generarDot(std::ostream &out);
    void ordenarTransacciones(bool desc); // Nuevo método
    AVL *getRentedAssets(int userId);
};

#endif
