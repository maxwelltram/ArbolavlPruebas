#include "AVL.h"
#include "NodoA.h"

void AVL::Insertar(const int dat)
{
    NodoA* padre = NULL;

    cout << "Insertar: " << dat << endl;
    actual = raiz;
    // Buscar el dato en el Arbol, manteniendo un puntero al nodo padre
    while (!Vacio(actual) && dat != actual->dato) {
        padre = actual;
        if (dat > actual->dato) actual = actual->derecho;
        else if (dat < actual->dato) actual = actual->izquierdo;
    }

    // Si se ha encontrado el elemento, regresar sin insertar
    if (!Vacio(actual)) return;
    // Si padre es NULL, entonces el �rbol estaba vacio, el nuevo nodo sera
    // el nodo raiz
    if (Vacio(padre)) raiz = new NodoA(dat);
    // Si el dato es menor que el que contiene el nodo padre, lo insertamos
    // en la rama izquierda
    else if (dat < padre->dato) {
        padre->izquierdo = new NodoA(dat, padre);
        Equilibrar(padre, IZQUIERDO, true);
    }
    // Si el dato es mayor que el que contiene el nodo padre, lo insertamos
    // en la rama derecha
    else if (dat > padre->dato) {
        padre->derecho = new NodoA(dat, padre);
        Equilibrar(padre, DERECHO, true);
    }
}

void AVL::Equilibrar(NodoA* nodo, int rama, bool nuevo)
{
    bool salir = false;

    // Recorrer camino inverso actualizando valores de FE:
    while (nodo && !salir) {
        if (nuevo)
            if (rama == IZQUIERDO) nodo->FE--; // Depende de si añadimos ...
            else                  nodo->FE++;
        else
            if (rama == IZQUIERDO) nodo->FE++; // ... o borramos
            else                  nodo->FE--;
        if (nodo->FE == 0) salir = true; // La altura de las rama que
                                        // empieza en nodo no ha variado,
                                        // salir de Equilibrar
        else if (nodo->FE == -2) { // Rotar a derechas y salir:
            if (nodo->izquierdo->FE == 1) RDD(nodo); // RotaciOn doble
            else RSD(nodo);                         // RotaciOn simple
            salir = true;
        }
        else if (nodo->FE == 2) {  // Rotar a izquierdas y salir:
            if (nodo->derecho->FE == -1) RDI(nodo); // RotaciOn doble
            else RSI(nodo);                        // RotaciOn simple
            salir = true;
        }
        if (nodo->padre)
            if (nodo->padre->derecho == nodo) rama = DERECHO; else rama = IZQUIERDO;
        nodo = nodo->padre; // Calcular FE, siguiente nodo del camino.
    }
}

//ROTACION DOBLE A LA DERECHA
void AVL::RDD(NodoA* nodo)
{
    cout << "RDD" << endl;
    NodoA* Padre = nodo->padre;
    NodoA* P = nodo;
    NodoA* Q = P->izquierdo;
    NodoA* R = Q->derecho;
    NodoA* B = R->izquierdo;
    NodoA* C = R->derecho;

    if (Padre)
        if (Padre->derecho == nodo) Padre->derecho = R;
        else Padre->izquierdo = R;
    else raiz = R;

    // Reconstruir Arbol:
    Q->derecho = B;
    P->izquierdo = C;
    R->izquierdo = Q;
    R->derecho = P;

    // Reasignar padres:
    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = Q;
    if (C) C->padre = P;

    // Ajustar valores de FE:
    switch (R->FE) {
    case -1: Q->FE = 0; P->FE = 1; break;
    case 0:  Q->FE = 0; P->FE = 0; break;
    case 1:  Q->FE = -1; P->FE = 0; break;
    }
    R->FE = 0;
}

//ROTACION DOBLE IZQUIERDA
void AVL::RDI(NodoA* nodo)
{
    cout << "RDI" << endl;
    NodoA* Padre = nodo->padre;
    NodoA* P = nodo;
    NodoA* Q = P->derecho;
    NodoA* R = Q->izquierdo;
    NodoA* B = R->izquierdo;
    NodoA* C = R->derecho;

    if (Padre)
        if (Padre->derecho == nodo) Padre->derecho = R;
        else Padre->izquierdo = R;
    else raiz = R;

    // Reconstruir Arbol:
    P->derecho = B;
    Q->izquierdo = C;
    R->izquierdo = P;
    R->derecho = Q;

    // Reasignar padres:
    R->padre = Padre;
    P->padre = Q->padre = R;
    if (B) B->padre = P;
    if (C) C->padre = Q;

    // Ajustar valores de FE:
    switch (R->FE) {
    case -1: P->FE = 0; Q->FE = 1; break;
    case 0:  P->FE = 0; Q->FE = 0; break;
    case 1:  P->FE = -1; Q->FE = 0; break;
    }
    R->FE = 0;
}

//ROTACION SIMPLE A LA DERECHA

void AVL::RSD(NodoA* nodo)
{

    cout << "RSD" << endl;

    NodoA* Padre = nodo->padre;
    NodoA* P = nodo;
    NodoA* Q = P->izquierdo;
    NodoA* B = Q->derecho;

    if (Padre)
        if (Padre->derecho == P) Padre->derecho = Q;
        else Padre->izquierdo = Q;
    else raiz = Q;

    // Reconstruir Arbol:
    P->izquierdo = B;
    Q->derecho = P;

    // Reasignar padres:
    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    // Ajustar valores de FE:
    P->FE = 0;
    Q->FE = 0;
}

//ROTACIONES SIMPLES A LA IZQUIERDA
void AVL::RSI(NodoA* nodo)
{
    cout << "RSI" << endl;
    NodoA* Padre = nodo->padre;
    NodoA* P = nodo;
    NodoA* Q = P->derecho;
    NodoA* B = Q->izquierdo;

    if (Padre)
        if (Padre->derecho == P) Padre->derecho = Q;
        else Padre->izquierdo = Q;
    else raiz = Q;

    // Reconstruir Arbol:
    P->derecho = B;
    Q->izquierdo = P;

    // Reasignar padres:
    P->padre = Q;
    if (B) B->padre = P;
    Q->padre = Padre;

    // Ajustar valores de FE:
    P->FE = 0;
    Q->FE = 0;
}

//ELIMINAR DEL AVL
void AVL::Borrar(const int dat)
{
    NodoA* padre = NULL;
    NodoA* nodo;
    int aux;

    actual = raiz;
    // Mientras sea posible que el valor estE en el Arbol
    while (!Vacio(actual)) {
        if (dat == actual->dato) { // Si el valor estA en el nodo actual
            if (EsHoja(actual)) { // Y si ademAs es un nodo hoja: lo borramos
                if (padre) // Si tiene padre (no es el nodo raiz)
                   // Anulamos el puntero que le hace referencia
                    if (padre->derecho == actual) padre->derecho = NULL;
                    else if (padre->izquierdo == actual) padre->izquierdo = NULL;
                delete actual; // Borrar el nodo
                actual = NULL;
                // El nodo padre del actual puede ser ahora un nodo hoja, por lo tanto su
                // FE es cero, pero debemos seguir el camino a partir de su padre, si existe.
                if ((padre->derecho == actual && padre->FE == 1) ||
                    (padre->izquierdo == actual && padre->FE == -1)) {
                    padre->FE = 0;
                    actual = padre;
                    padre = actual->padre;
                }
                if (padre)
                    if (padre->derecho == actual) Equilibrar(padre, DERECHO, false);
                    else                         Equilibrar(padre, IZQUIERDO, false);
                return;
            }
            else { // Si el valor estA en el nodo actual, pero no es hoja
               // Buscar nodo
                padre = actual;
                // Buscar nodo mAs izquierdo de rama derecha
                if (actual->derecho) {
                    nodo = actual->derecho;
                    while (nodo->izquierdo) {
                        padre = nodo;
                        nodo = nodo->izquierdo;
                    }
                }
                // O buscar nodo mAs derecho de rama izquierda
                else {
                    nodo = actual->izquierdo;
                    while (nodo->derecho) {
                        padre = nodo;
                        nodo = nodo->derecho;
                    }
                }
                // Intercambiar valores de no a borrar u nodo encontrado
                // y continuar, cerrando el bucle. El nodo encontrado no tiene
                // por quE ser un nodo hoja, cerrando el bucle nos aseguramos
                // de que sOlo se eliminan nodos hoja.
                aux = actual->dato;
                actual->dato = nodo->dato;
                nodo->dato = aux;
                actual = nodo;
            }
        }
        else { // TodavIa no hemos encontrado el valor, seguir busc�ndolo
            padre = actual;
            if (dat > actual->dato) actual = actual->derecho;
            else if (dat < actual->dato) actual = actual->izquierdo;
        }
    }
}


void AVL::InOrden(void (*func)(int&, int), NodoA* nodo, bool r)
{
    if (r) nodo = raiz;
    if (nodo->izquierdo) InOrden(func, nodo->izquierdo, false);
    func(nodo->dato, nodo->FE);
    if (nodo->derecho) InOrden(func, nodo->derecho, false);
}

// Recorrido de �rbol en preorden, aplicamos la funciOn func, que tiene
// el prototipo:
// void func(int&, int);
void AVL::PreOrden(void (*func)(int&, int), NodoA* nodo, bool r)
{
    if (r) nodo = raiz;
    func(nodo->dato, nodo->FE);
    if (nodo->izquierdo) PreOrden(func, nodo->izquierdo, false);
    if (nodo->derecho) PreOrden(func, nodo->derecho, false);
}

// Recorrido de Arbol en postorden, aplicamos la funciOn func, que tiene
// el prototipo:
// void func(int&, int);
void AVL::PostOrden(void (*func)(int&, int), NodoA* nodo, bool r)
{
    if (r) nodo = raiz;
    if (nodo->izquierdo) PostOrden(func, nodo->izquierdo, false);
    if (nodo->derecho) PostOrden(func, nodo->derecho, false);
    func(nodo->dato, nodo->FE);
}

