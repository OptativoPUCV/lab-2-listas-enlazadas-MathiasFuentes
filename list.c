#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* L = (List*)malloc(sizeof(List));
    if (L == NULL) exit(1);
    L->head = NULL;
    L->tail = NULL;
    L->current = NULL;
    return L;
}

void * firstList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return list->head->data;
}

void * nextList(List * list) {
    if (list->head == NULL || list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    while(list->current->next != NULL){
        list->current = list->current->next;
    }
    list->tail = list->current;
    return list->current->data;
}

void * prevList(List * list) {
    if (list->head == NULL || list->current == NULL) return NULL;
    if (list->current == list->head) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node* newNode = createNode(data);

    if (list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
    }
    else{
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if (list->head == NULL || list->current == NULL) return;
    Node* newNode = createNode(data);
    if (list->tail == list->current){
        list->current->next = newNode;
        newNode->prev = list->current;
        list->tail = newNode;
    }
    else {
        newNode->next = list->current->next;
        newNode->prev = list->current;
        list->current->next->prev = newNode;
        list->current->next = newNode;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}
/*
6. Programe la función `void* popCurrent(List * list)`, la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el **dato** del nodo eliminado.
> **Nota**: El current debe quedar apuntando al nodo siguiente del eliminado.
*/
void * popCurrent(List * list) {
    if (list->head == NULL || list->current == NULL) return NULL;

    void* value = list->current->data;
    Node* elim = list->current;

    // Si el current es el último, debe moverse antes de eliminar
    if (list->current == list->tail) {
        list->current = NULL;  // No hay un siguiente nodo disponible
    } else {
        list->current = list->current->next;  // Avanza antes de eliminar
    }

    // Caso: único nodo en la lista
    if (list->head == list->tail) {
        list->head = list->tail = NULL;
    }
    // Caso: eliminar la cabeza
    else if (elim == list->head) {
        list->head = elim->next;
        if (list->head) list->head->prev = NULL;
    }
    // Caso: eliminar la cola
    else if (elim == list->tail) {
        list->tail = elim->prev;
        if (list->tail) list->tail->next = NULL;
    }
    // Caso: nodo intermedio
    else {
        elim->prev->next = elim->next;
        elim->next->prev = elim->prev;
    }

    free(elim);
    return value;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}