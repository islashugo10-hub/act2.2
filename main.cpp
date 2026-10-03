/*
 * Actividad: Listas ligadas simples en C++
 * Operaciones: reverse, equals, concat
 *
 * Complejidad (n = tamaño de la lista 1, m = tamaño de la lista 2):
 *   - insertarFinal : O(1) usando el puntero a la cola (se maneja en leerLista)
 *   - reverse       : O(n) tiempo, O(1) espacio extra
 *   - equals        : O(min(n, m)) tiempo, O(1) espacio extra
 *   - concat        : O(n + m) tiempo (recorre la primera para hallar la cola
 *                     y copia los m nodos de la segunda), O(m) espacio extra
 */

#include <iostream>
using namespace std;

// Nodo de una lista simplemente ligada
struct Nodo {
    int dato;
    Nodo* sig;
    Nodo(int d) : dato(d), sig(nullptr) {}
};

/*
 * reverse
 * Descripción : Invierte la lista ligada (la lista original se modifica).
 * Entrada     : Apuntador al inicio de la lista a invertir.
 * Salida      : Apuntador al inicio de la nueva lista (reordenada).
 * Precondición: Una lista ligada válida.
 * Postcondición: Una lista ligada válida (la lista recibida ya no existe como
 *               estaba, solo persiste la nueva lista).
 * Complejidad : O(n)
 */
Nodo* reverse(Nodo* cabeza) {
    Nodo* previo = nullptr;
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->sig;  // guardar el resto de la lista
        actual->sig = previo;           // invertir el enlace
        previo = actual;
        actual = siguiente;
    }
    return previo;  // nueva cabeza
}

/*
 * equals
 * Descripción : Revisa si dos listas ligadas tienen el mismo contenido.
 * Entrada     : Dos apuntadores a listas ligadas válidas.
 * Salida      : true / false
 * Precondición: Dos listas ligadas válidas.
 * Postcondición: Dos listas ligadas válidas (no se modifican).
 * Complejidad : O(min(n, m))
 */
bool equals(Nodo* a, Nodo* b) {
    while (a != nullptr && b != nullptr) {
        if (a->dato != b->dato) return false;
        a = a->sig;
        b = b->sig;
    }
    return a == nullptr && b == nullptr;  // ambas deben terminar a la vez
}

/*
 * concat
 * Descripción : Concatena lista1 + lista2.
 * Entrada     : Dos apuntadores a listas ligadas válidas (lista1 por referencia
 *               para poder actualizarla si estaba vacía).
 * Salida      : Nada.
 * Precondición: Las dos listas ligadas son válidas.
 * Postcondición: La primera lista contiene los elementos que contenía
 *               originalmente más los elementos de la otra lista. La segunda
 *               lista no se modifica (se copian sus nodos para que las listas
 *               no compartan memoria).
 * Complejidad : O(n + m)
 */
void concat(Nodo*& lista1, Nodo* lista2) {
    Nodo* cola = nullptr;
    if (lista1 != nullptr) {
        cola = lista1;
        while (cola->sig != nullptr) cola = cola->sig;  // buscar el último nodo
    }
    for (Nodo* p = lista2; p != nullptr; p = p->sig) {
        Nodo* nuevo = new Nodo(p->dato);
        if (cola == nullptr) lista1 = nuevo;  // lista1 estaba vacía
        else cola->sig = nuevo;
        cola = nuevo;
    }
}

// Lee  el dato cantidad enteros y construye la lista en el mismo orden )
Nodo* leerLista(int cantidad) {
    Nodo* cabeza = nullptr;
    Nodo* cola = nullptr;
    for (int i = 0; i < cantidad; i++) {
        int x;
        cin >> x;
        Nodo* nuevo = new Nodo(x);
        if (cabeza == nullptr) cabeza = nuevo;
        else cola->sig = nuevo;
        cola = nuevo;
    }
    return cabeza;
}

// Imprime un dato por línea
void imprimir(Nodo* cabeza) {
    for (Nodo* p = cabeza; p != nullptr; p = p->sig)
        cout << p->dato << "\n";
}

// Libera la memoria de la lista
void liberar(Nodo* cabeza) {
    while (cabeza != nullptr) {
        Nodo* tmp = cabeza;
        cabeza = cabeza->sig;
        delete tmp;
    }
}

int main() {
    int m, n;

    cin >> m;
    Nodo* lista1 = leerLista(m);
    cin >> n;
    Nodo* lista2 = leerLista(n);

    lista1 = reverse(lista1);   // reversed list 1
    lista2 = reverse(lista2);   // reversed list 2

    imprimir(lista1);
    imprimir(lista2);

    bool iguales = equals(lista1, lista2);  // se evalúa antes de modificar lista2

    concat(lista2, lista1);     // reversed list 2 + reversed list 1
    imprimir(lista2);

    cout << (iguales ? "true" : "false") << "\n";

    liberar(lista1);
    liberar(lista2);
    return 0;
}