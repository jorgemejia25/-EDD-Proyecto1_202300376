#include "CircleDoubleLinkedList.h"
#include "AVL.h"
#include <iostream>

// Inicializar la instancia estática
CircleDoubleLinkedList *CircleDoubleLinkedList::instance = nullptr;

// Implementar método getInstance
CircleDoubleLinkedList *CircleDoubleLinkedList::getInstance()
{
    if (instance == nullptr)
    {
        instance = new CircleDoubleLinkedList();
    }
    return instance;
}

CircleDoubleLinkedList::CircleDoubleLinkedList()
{
    this->head = nullptr;
    this->size = 0;
}

CircleDoubleLinkedList::~CircleDoubleLinkedList()
{
    if (isEmpty())
        return;

    Node *current = head;
    do
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    } while (current != head);
}

void CircleDoubleLinkedList::insertTransaction(Transaction *transaction)
{
    Node *newNode = new Node(transaction);

    if (isEmpty())
    {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else
    {
        Node *last = head->prev;
        newNode->next = head;
        newNode->prev = last;
        last->next = newNode;
        head->prev = newNode;
    }
    size++;
}

void CircleDoubleLinkedList::deleteTransaction(std::string id)
{
    if (isEmpty())
        return;

    Node *current = head;
    do
    {
        if (current->data->getId() == id)
        {
            if (size == 1)
            {
                delete head;
                head = nullptr;
            }
            else
            {
                if (current == head)
                {
                    head = head->next;
                }
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            size--;
            return;
        }
        current = current->next;
    } while (current != head);
}

Transaction *CircleDoubleLinkedList::searchTransaction(std::string id)
{
    if (isEmpty())
        return nullptr;

    Node *current = head;
    do
    {
        if (current->data->getAsset()->getId() == id)
        {
            return current->data;
        }
        current = current->next;
    } while (current != head);

    return nullptr;
}

bool CircleDoubleLinkedList::isEmpty()
{
    return head == nullptr;
}

int CircleDoubleLinkedList::getSize()
{
    return size;
}

void CircleDoubleLinkedList::print()
{
    if (isEmpty())
    {
        std::cout << "Lista vacía" << std::endl;
        return;
    }

    Node *current = head;
    do
    {
        std::cout << "ID: " << current->data->getId() << std::endl;
        current = current->next;
    } while (current != head);
}

void CircleDoubleLinkedList::printActiveTransactions(int userId)
{
    if (isEmpty())
    {
        std::cout << "Lista vacía" << std::endl;
        return;
    }

    Node *current = head;
    bool foundActive = false;
    do
    {
        if (current->data->getStatus() && current->data->getUser()->id == userId)
        {
            std::cout << "ID Activo: " << current->data->getAsset()->getId() << std::endl;
            std::cout << "Usuario: " << current->data->getUser()->Nombre << std::endl;
            std::cout << "Activo: " << current->data->getAsset()->getNombre() << std::endl;
            std::cout << "Dias: " << current->data->getDays() << std::endl;
            std::cout << "" << std::endl;
            foundActive = true;
        }
        current = current->next;
    } while (current != head);

    if (!foundActive)
    {
        std::cout << "No hay transacciones activas para el usuario con ID: " << userId << std::endl;
    }
}

void CircleDoubleLinkedList::printInactiveTransactions(int userId)
{
    if (isEmpty())
    {
        std::cout << "Lista vacía" << std::endl;
        return;
    }

    Node *current = head;
    bool foundInactive = false;
    do
    {
        if (!current->data->getStatus() && current->data->getUser()->id == userId)
        {
            std::cout << "ID Activo: " << current->data->getId() << std::endl;
            std::cout << "Activo: " << current->data->getAsset()->getNombre() << std::endl;
            std::cout << "Dias: " << current->data->getDays() << std::endl;
            std::cout << "Max Días: " << current->data->getAsset()->getMaxDias() << std::endl;
            std::cout << "" << std::endl;
            foundInactive = true;
        }
        current = current->next;
    } while (current != head);

    if (!foundInactive)
    {
        std::cout << "No hay devoluciones para el usuario con ID: " << userId << std::endl;
    }
}

void CircleDoubleLinkedList::printTransactionDetails(std::string id)
{
    Transaction *transaction = searchTransaction(id);
    if (transaction != nullptr)
    {
        std::cout << "=== Detalles de la Transacción ===" << std::endl;
        std::cout << "ID Activo: " << transaction->getId() << std::endl;
        std::cout << "Usuario: " << transaction->getUser()->Nombre << std::endl;
        std::cout << "ID Usuario: " << transaction->getUser()->id << std::endl;
        std::cout << "Activo: " << transaction->getAsset()->getNombre() << std::endl;
        std::cout << "Estado: " << (transaction->getStatus() ? "Activo" : "Devuelto") << std::endl;
        std::cout << "===============================" << std::endl;
    }
    else
    {
        std::cout << "No se encontró la transacción con ID: " << id << std::endl;
    }
}

void CircleDoubleLinkedList::printMyTransactions(int userId)
{
    if (isEmpty())
    {
        std::cout << "Lista vacía" << std::endl;
        return;
    }

    Node *current = head;
    bool foundTransaction = false;

    do
    {
        if (current->data->getAsset()->getIdUsuario() == userId && current->data->getStatus())
        {
            std::cout << "ID Activo: " << current->data->getAsset()->getId() << std::endl;
            std::cout << "Usuario: " << current->data->getUser()->Nombre << std::endl;
            std::cout << "Activo: " << current->data->getAsset()->getNombre() << std::endl;
            std::cout << "Max Días: " << current->data->getAsset()->getMaxDias() << std::endl;
            std::cout << "Dias: " << current->data->getDays() << std::endl;
            std::cout << "Estado: " << (current->data->getStatus() ? "Activo" : "Devuelto") << std::endl;

            std::cout << "------------------------" << std::endl;
            foundTransaction = true;
        }
        current = current->next;
    } while (current != head);

    if (!foundTransaction)
    {
        std::cout << "No hay transacciones con tu usuario. " << userId << std::endl;
    }
}

void CircleDoubleLinkedList::generarDot(std::ostream &out)
{
    out << "digraph G {\n";
    out << "    node [shape=box, style=filled, fillcolor=lightblue];\n";
    out << "    \n\n";

    if (isEmpty())
    {
        out << "}\n";
        return;
    }

    Node *current = head;
    do
    {
        if (current->data->getStatus())
        {
            out << "    \"" << current->data->getId() << "\" [label=\""
                << current->data->getAsset()->getNombre() << "\\n"
                << "Usuario: " << current->data->getUser()->Nombre << "\\n"
                << "Dias: " << current->data->getDays() << "\\n"
                << "Estado: " << (current->data->getStatus() ? "Activo" : "Devuelto")
                << "\"];\n";
            if (current->next->data->getStatus())
            {
                out << "    \"" << current->data->getId() << "\" -> \"" << current->next->data->getId() << "\" [constraint=false];\n";
                out << "    \"" << current->next->data->getId() << "\" -> \"" << current->data->getId() << "\" [constraint=false];\n";
            }
        }
        current = current->next;
    } while (current != head);

    out << "}\n";
}

AVL *CircleDoubleLinkedList::getRentedAssets(int userId)
{
    AVL *rentedAssets = new AVL();
    if (isEmpty())
    {
        return rentedAssets;
    }

    Node *current = head;
    do
    {
        if (current->data->getUser()->id == userId && current->data->getStatus())
        {
            rentedAssets->insertar(*current->data->getAsset());
        }
        current = current->next;
    } while (current != head);

    return rentedAssets;
}

void CircleDoubleLinkedList::ordenarTransacciones(bool desc)
{
    if (isEmpty())
    {
        std::cout << "No hay transacciones para ordenar" << std::endl;
        return;
    }

    Node *current = head;
    Node *index = nullptr;
    Transaction *temp = nullptr;

    if (desc)
    {
        do
        {
            index = current->next;
            while (index != head)
            {
                if (current->data->getId() < index->data->getId())
                {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        } while (current->next != head);
    }
    else
    {
        do
        {
            index = current->next;
            while (index != head)
            {
                if (current->data->getId() > index->data->getId())
                {
                    temp = current->data;
                    current->data = index->data;
                    index->data = temp;
                }
                index = index->next;
            }
            current = current->next;
        } while (current->next != head);
    }
}