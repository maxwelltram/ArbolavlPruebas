#pragma once
#include "NodoA.h"
class AVL
{
public:
	enum { IZQUIERDO, DERECHO };
	NodoA* raiz;
	NodoA* actual;
	int contador;
	int altura;

	AVL() : raiz(NULL), actual(NULL) {
	}
	void Insertar(const int dat);
	void Borrar(const int dat);
	bool Buscar(const int dat);
	bool Vacio(NodoA* r) { return r == NULL; }
	bool EsHoja(NodoA* r) { return !r->derecho && !r->izquierdo; }
	void Mostrar(int, int);
	

	void InOrden(void (*func)(int&, int), NodoA* nodo = NULL, bool r = true);
	void PreOrden(void (*func)(int&, int), NodoA* nodo = NULL, bool r = true);
	void PostOrden(void (*func)(int&, int), NodoA* nodo = NULL, bool r = true);


	void Equilibrar(NodoA* nodo, int, bool);
	void RSI(NodoA* nodo);
	void RSD(NodoA* nodo);
	void RDI(NodoA* nodo);
	void RDD(NodoA* nodo);
};

