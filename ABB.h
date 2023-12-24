/*
autor: Flores Gonzalez Rodrigo
Descripcion: Libreria de arboles binarios de busqueda
Lenguaje: C
*/

#ifndef ABB.h
#define ABB.h
#include <stdio.h>
#include <stdlib.h>

typedef struct _Nodo
{
	struct _Nodo *pder, *pizq;
	int dato;
}Nodo;

Nodo* nuevo(int dato)
{
	Nodo* pnuevo=(Nodo*)malloc(sizeof(Nodo));
	if(pnuevo)
	{
		pnuevo->dato=dato;
		pnuevo->pizq=pnuevo->pder=NULL;	
	}
	return pnuevo;
}

//Imprimir la representacion preorden del arbol
//praiz: puntero a la raiz del arbol
void preorden(Nodo* praiz)
{
	if(praiz)
	{
		printf("%i ", praiz->dato);
		preorden(praiz->pizq);
		preorden(praiz->pder);
	}
}

//Imprimir la representacion jerarquica del arbol
//praiz: puntero a la raiz del arbol
//produndidad: altura de la raiz
void ver(Nodo* praiz,int profundidad)
{
	if(praiz)
	{
		for(int i=0;i<profundidad;i++)
			printf(" ");
		printf("-%i\n", praiz->dato);
		if(!praiz->pizq && praiz->pder)
			printf("\n");
		ver(praiz->pizq,profundidad+1);
		ver(praiz->pder,profundidad+1);
	}
}

//Imprimir la representacion indorden del arbol
//praiz: puntero a la raiz del arbol
void inorden(Nodo* praiz)
{
	if(praiz)
	{		
		inorden(praiz->pizq);
		printf("%i ", praiz->dato);
		inorden(praiz->pder);
	}
}

//Imprimir la representacion postorden del arbol
//praiz: puntero a la raiz del arbol
void postorden(Nodo* praiz)
{
	if(praiz)
	{		
		postorden(praiz->pizq);
		postorden(praiz->pder);
		printf("%i ", praiz->dato);
	}
}

//Insertar un nodo en el arbol
//praiz: puntero a la raiz del arbol
//dato: entero a insertar
void insertar(Nodo** ppraiz, int dato)
{
	if(*ppraiz)
		if(dato<(*ppraiz)->dato)
			insertar(&((*ppraiz)->pizq),dato);
		else
			insertar(&((*ppraiz)->pder),dato);	
	else
		*ppraiz=nuevo(dato);
}

//Retornar puntero al nodo que contiene determinado dato
//praiz: puntero a la raiz del arbol
//dato: dato a buscar
Nodo** buscar(Nodo** ppraiz, int dato)
{
	if(*ppraiz)
	{		
		if(dato==(*ppraiz)->dato)
			return ppraiz;
		else if(dato<(*ppraiz)->dato)
			return buscar(&((*ppraiz)->pizq),dato);		
		else 
			return buscar(&((*ppraiz)->pder),dato); 			
	}
	return NULL;
} 

//Retornar la altura de un nodo
//nodo: puntero al nodo
int altura(Nodo* pnodo)
{
	if(pnodo)
	{
		int altura_izq=altura(pnodo->pizq);
		int altura_der=altura(pnodo->pder);
		return (altura_izq>altura_der?altura_izq:altura_der)+1;
	}	
	return 0;
}

Nodo** sucesorInorder(Nodo** ppraiz)
{
	(*ppraiz)->pder?sucesorInorder(&((*ppraiz)->pder)):ppraiz;
}

//borrar un nodo que no tiene mas de 1 hijo
void borrar1(Nodo** ppborrar,Nodo* psig)
{
	Nodo* pborrar=*ppborrar; 
	*ppborrar=psig;	
	free(pborrar);
}

//borrar un nodo que tiene 2 hijos
void borrar2(Nodo** ppborrar)
{
	Nodo** ppmin=sucesorInorder(&((*ppborrar)->pizq));
	(*ppborrar)->dato=(*ppmin)->dato;
	if((*ppmin)->pder)
		borrar1(ppmin,(*ppmin)->pder);
	else
		borrar1(ppmin,NULL);
}

//borar un nodo dado el dato que contiene
//praiz: puntero a la raiz
//dato: dato que contiene el nodo a borrar
void borrar(Nodo* praiz, int dato)
{
	Nodo** ppborrar=buscar(&praiz,dato);
	if(ppborrar)
	{
		if((*ppborrar)->pizq)
			if((*ppborrar)->pder)
				borrar2(ppborrar);
			else
				borrar1(ppborrar,(*ppborrar)->pizq);		
		else
			if((*ppborrar)->pder)
				borrar1(ppborrar,(*ppborrar)->pder);
			else
				borrar1(ppborrar,NULL);				
	}
}

#endif
