
#ifndef AVL_H
#define AVL_H
#include <stdio.h>
#include <stdlib.h>

typedef struct _Nodo
{
	struct _Nodo *pder, *pizq;
	int dato;
	int altura;
}Nodo;

Nodo* nuevo(int dato)
{
	Nodo* pnuevo=(Nodo*)malloc(sizeof(Nodo));
	if(pnuevo)
	{
		pnuevo->dato=dato;
		pnuevo->pizq=pnuevo->pder=NULL;	
		pnuevo->altura=1;
	}
	return pnuevo;
}



void insertar(Nodo** ppraiz, int dato)
{
	if(*ppraiz)
	{
		if(dato<(*ppraiz)->dato)
			insertar(&((*ppraiz)->pizq),dato);
		else
			insertar(&((*ppraiz)->pder),dato);
		int izq_alt=(*ppraiz)->pizq->altura;
		int der_alt=(*ppraiz)->pder->altura;
		(*ppraiz)->altura=(izq_alt<der_alt?der_alt+1:izq_alt+1);
	}
			
	else
		*ppraiz=nuevo(dato);
}

#endif

