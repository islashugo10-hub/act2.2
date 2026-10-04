
/*
 * Integrantes:
 * Jaime Hugo Islas Trujillo - A01821293
 * Francisco Xavier Olivos Barranco - A01820288
 *
 * Actividad: Listas ligadas simples en C++
 * Operaciones: reverse, equals y concat
 *
 * Complejidad:
 * reverse : O(n) tiempo, O(1) espacio adicional.
 * equals  : O(min(n,m)) tiempo, O(1) espacio adicional.
 * concat  : O(n+m) tiempo, O(m) espacio adicional.
 */

#include <iostream>
using namespace std;

/*
 * Nodo de una lista simplemente ligada.
 */
struct Nodo {
    int dato;
    Nodo* sig;

    Nodo(int d) : dato(d), sig(nullptr) {}
};

/*
 * reverse
 *
 * Descripción : Invierte el orden de los elementos de una lista ligada.
 *               La lista original se modifica.
 *
 * Entrada     : Apuntador al inicio de la lista.
 *
 * Salida      : Apuntador al inicio de la lista invertida.
 *
 * Precondición: La lista debe ser una lista ligada válida.
 *
 * Postcondición: La lista queda invertida y sigue siendo una lista válida.
 *
 * Complejidad : O(n) tiempo y O(1) espacio adicional.
 */
Nodo* reverse(Nodo* cabeza) {
    Nodo* previo = nullptr;
    Nodo* actual = cabeza;

    while (actual != nullptr) {
        Nodo* siguiente = actual->sig;  // Guarda el siguiente nodo.
        actual->sig = previo;           // Invierte el enlace.
        previo = actual;
        actual = siguiente;
    }

    return previo;  // Regresa la nueva cabeza.
}

/*
 * equals
 *
 * Descripción : Determina si dos listas ligadas contienen los mismos
 *               elementos en el mismo orden y tienen la misma longitud.
 *
 * Entrada     : Dos apuntadores a listas ligadas válidas.
 *
 * Salida      : true si las listas son iguales; false en caso contrario.
 *
 * Precondición: Ambas listas deben ser listas ligadas válidas.
 *
 * Postcondición: Las dos listas permanecen sin modificaciones.
 *
 * Complejidad : O(min(n,m)) tiempo y O(1) espacio adicional.
 */
bool equals(Nodo* a, Nodo* b) {
    while (a != nullptr && b != nullptr) {
        if (a->dato != b->dato) {
            return false;
        }

        a = a->sig;
        b = b->sig;
    }

    // Ambas listas deben terminar al mismo tiempo.
    return a == nullptr && b == nullptr;
}

/*
 * concat
 *
 * Descripción : Concatena la primera lista con la segunda lista.
 *
 * Entrada     : Dos apuntadores a listas ligadas válidas.
 *               La primera lista se recibe por referencia para poder
 *               actualizarla cuando esté vacía.
 *
 * Salida      : No regresa ningún valor.
 *
 * Precondición: Ambas listas deben ser listas ligadas válidas.
 *
 * Postcondición: La primera lista contiene sus elementos originales
 *                seguidos de copias de los elementos de la segunda lista.
 *                La segunda lista no se modifica.
 *
 * Complejidad : O(n+m) tiempo y O(m) espacio adicional,
 *               donde n es el tamaño de la primera lista y
 *               m es el tamaño de la segunda lista.
 */
void concat(Nodo*& lista1, Nodo* lista2) {
    Nodo* cola = nullptr;

    // Busca el último nodo de la primera lista.
    if (lista1 != nullptr) {
        cola = lista1;

        while (cola->sig != nullptr) {
            cola = cola->sig;
        }
    }

    // Copia los nodos de la segunda lista.
    for (Nodo* p = lista2; p != nullptr; p = p->sig) {
        Nodo* nuevo = new Nodo(p->dato);

        if (cola == nullptr) {
            lista1 = nuevo;  // La primera lista estaba vacía.
        } else {
            cola->sig = nuevo;
        }

        cola = nuevo;
    }
}

/*
 * leerLista
 *
 * Descripción : Lee una cantidad determinada de enteros y construye
 *               una lista ligada conservando el orden de entrada.
 *
 * Entrada     : La cantidad de elementos que tendrá la lista.
 *
 * Salida      : Apuntador al inicio de la lista construida.
 *
 * Precondición: La cantidad debe ser un entero mayor o igual a cero.
 *
 * Postcondición: Se construye una lista ligada con la cantidad indicada
 *                de elementos.
 *
 * Complejidad : O(n) tiempo y O(n) espacio para almacenar los nodos.
 */
Nodo* leerLista(int cantidad) {
    Nodo* cabeza = nullptr;
    Nodo* cola = nullptr;

    for (int i = 0; i < cantidad; i++) {
        int x;
        cin >> x;

        Nodo* nuevo = new Nodo(x);

        if (cabeza == nullptr) {
            cabeza = nuevo;
        } else {
            cola->sig = nuevo;
        }

        cola = nuevo;
    }

    return cabeza;
}

/*
 * imprimir
 *
 * Descripción : Imprime todos los elementos de la lista, uno por línea.
 *
 * Entrada     : Apuntador al inicio de la lista.
 *
 * Salida      : Los elementos de la lista en la salida estándar.
 *
 * Complejidad : O(n) tiempo y O(1) espacio adicional.
 */
void imprimir(Nodo* cabeza) {
    for (Nodo* p = cabeza; p != nullptr; p = p->sig) {
        cout << p->dato << "\n";
    }
}

/*
 * liberar
 *
 * Descripción : Libera la memoria utilizada por todos los nodos de la lista.
 *
 * Entrada     : Apuntador al inicio de la lista.
 *
 * Salida      : No regresa ningún valor.
 *
 * Postcondición: Todos los nodos de la lista han sido eliminados.
 *
 * Complejidad : O(n) tiempo y O(1) espacio adicional.
 */
void liberar(Nodo* cabeza) {
    while (cabeza != nullptr) {
        Nodo* tmp = cabeza;
        cabeza = cabeza->sig;
        delete tmp;
    }
}

int main() {
    int m, n;

    // Lee y construye la primera lista.
    cin >> m;
    Nodo* lista1 = leerLista(m);

    // Lee y construye la segunda lista.
    cin >> n;
    Nodo* lista2 = leerLista(n);

    // Invierte ambas listas.
    lista1 = reverse(lista1);
    lista2 = reverse(lista2);

    // Imprime las listas invertidas.
    imprimir(lista1);
    imprimir(lista2);

    // Compara las listas antes de realizar la concatenación.
    bool iguales = equals(lista1, lista2);

    // Concatena la lista 1 al final de la lista 2.
    concat(lista2, lista1);

    // Imprime la lista resultante.
    imprimir(lista2);

    // Imprime el resultado de la comparación.
    cout << (iguales ? "true" : "false") << "\n";

    // Libera la memoria utilizada por ambas listas.
    liberar(lista1);
    liberar(lista2);

    return 0;
}