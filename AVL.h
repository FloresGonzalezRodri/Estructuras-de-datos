//Libreria arbol binario de busqueda balanceado
//autor: Flores Gonzalez Rodrigo
//lenguaje: C

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

//Ver representacion jerarquica de un arbol
//praiz: puntero a la raiz del nodo
//profundidad: altura del nodo raiz
void ver(Nodo* praiz,int profundidad)
{
	if(praiz)
	{
		for(int i=0;i<profundidad;i++)
			printf(" ");
		printf("-%i %i\n", praiz->dato,praiz->altura);
		if(!praiz->pizq && praiz->pder)
			printf("\n");
		ver(praiz->pizq,profundidad+1);
		ver(praiz->pder,profundidad+1);
	}
}

int altura(Nodo* pnodo)
{
	return pnodo?pnodo->altura:0;
}

//Establecer altura de un nodo
//ppnodo: puntero doble al nodo
void altura2(Nodo** ppnodo)
{
	Nodo* pnodo=*ppnodo;
	if(pnodo)
	{
		
		altura2(&(pnodo->pizq));
		altura2(&(pnodo->pder));
		int altura_izq=altura(pnodo->pizq);
		int altura_der=altura(pnodo->pder);
		pnodo->altura=(altura_izq>altura_der?altura_izq:altura_der)+1;
	}
}

//rotarcion izquierda izquierda de nodo desbalanceado
//pdesbalanceado: puntero al nodo desbalanceado
void rotarIzqIzq(Nodo** pdesbalanceado)
{
	Nodo* desbalanceado=*pdesbalanceado;
	Nodo* desbalanceado_izq=desbalanceado->pizq;
	desbalanceado->pizq=desbalanceado_izq->pder;
	desbalanceado_izq->pder=desbalanceado;
	*pdesbalanceado=desbalanceado_izq;
}

//rotarcion izquierda derecha de nodo desbalanceado
//pdesbalanceado: puntero al nodo desbalanceado
void rotarIzqDer(Nodo** pdesbalanceado)
{
	Nodo* desbalanceado=*pdesbalanceado;
	Nodo* olddes_izq=desbalanceado->pizq;	
	desbalanceado->pizq=olddes_izq->pder;
	olddes_izq->pder=desbalanceado->pizq->pizq;
	desbalanceado->pizq->pizq=olddes_izq;
	rotarIzqIzq(pdesbalanceado);
}

//rotarcion derecha derecha de nodo desbalanceado
//pdesbalanceado: puntero al nodo desbalanceado
void rotarDerDer(Nodo** pdesbalanceado)
{
	Nodo* desbalanceado=*pdesbalanceado;
	Nodo* desbalanceado_der=desbalanceado->pder;
	desbalanceado->pder=desbalanceado_der->pizq;
	desbalanceado_der->pizq=desbalanceado;	
	*pdesbalanceado=desbalanceado_der;
}

//rotarcion derecha izquierda de nodo desbalanceado
//pdesbalanceado: puntero al nodo desbalanceado
void rotarDerIzq(Nodo** pdesbalanceado)
{	
	Nodo* desbalanceado=*pdesbalanceado;
	Nodo* olddes_der=desbalanceado->pder;	
	desbalanceado->pder=olddes_der->pizq;
	olddes_der->pizq=desbalanceado->pder->pder;
	desbalanceado->pder->pder=olddes_der;
	rotarDerDer(pdesbalanceado);
}

void borrar1(Nodo** ppborrar,Nodo* psig)
{
	Nodo* pborrar=*ppborrar; 
	*ppborrar=psig;	
	free(pborrar);
}

Nodo** sucesorInorder(Nodo** ppraiz)
{
	(*ppraiz)->pder?sucesorInorder(&((*ppraiz)->pder)):ppraiz;
}

void borrar2(Nodo** ppborrar)
{
	Nodo** ppmin=sucesorInorder(&((*ppborrar)->pizq));
	(*ppborrar)->dato=(*ppmin)->dato;
	if((*ppmin)->pder)
		borrar1(ppmin,(*ppmin)->pder);
	else
		borrar1(ppmin,NULL);
}

//borrar un nodo
//praiz: puntero a la raiz
//dato: dato que contiene el nodo a borrar
void borrar(Nodo* praiz, int dato)
{
	Nodo** ppborrar=buscar(&praiz,dato);
	if(ppborrar)
	{
		if((*ppborrar)->pizq)
			if((*ppborrar)->pder)
			{
				borrar2(ppborrar);
				altura2(ppraiz);
			}
			
			else
				borrar1(ppborrar,(*ppborrar)->pizq);		
		else
			if((*ppborrar)->pder)
				borrar1(ppborrar,(*ppborrar)->pder);
			else
				borrar1(ppborrar,NULL);				
	}
}


void borrar(Nodo** ppraiz, int dato)
{
	Nodo* praiz=*ppraiz;
	if(*ppraiz)
	{		
		if(dato==(*ppraiz)->dato)
		{
			if((*ppraiz)->pizq)
				if((*ppraiz)->pder)
					borrar2(ppraiz);
				else
					borrar1(ppraiz,(*ppraiz)->pizq);		
			else
				if((*ppraiz)->pder)
					borrar1(ppraiz,(*ppraiz)->pder);
				else
					borrar1(ppraiz,NULL);				
		}
		else if(dato<(*ppraiz)->dato)
			borrar(&((*ppraiz)->pizq),dato);		
		else 
			borrar(&((*ppraiz)->pder),dato);
		int izq_alt=altura(praiz->pizq);
		int der_alt=altura(praiz->pder);
		if(abs(der_alt-izq_alt)==2)
			if(dato<praiz->dato)
			{
				dato<praiz->pizq->dato?rotarIzqIzq(ppraiz):rotarIzqDer(ppraiz);
				altura2(ppraiz);
			}
			else
			{
				dato<praiz->pizq->dato?rotarDerDer(ppraiz):rotarDerIzq(ppraiz);
				altura2(ppraiz);
			}								
		else
			praiz->altura=(der_alt<izq_alt?izq_alt:der_alt)+1;
	}
}

void insertar(Nodo** ppraiz, int dato)
{
	Nodo* praiz=*ppraiz;
	if(praiz)
	{
		if(dato<praiz->dato)
		{
			insertar(&(praiz->pizq),dato);
			int izq_alt=altura(praiz->pizq);
			int der_alt=altura(praiz->pder);
			if(izq_alt<der_alt)
			{				
				if(der_alt-izq_alt==2)
				{
					dato<praiz->pizq->dato?rotarIzqIzq(ppraiz):rotarIzqDer(ppraiz);
					altura2(ppraiz);
				}
					
				else
					praiz->altura=der_alt+1;
			}
			else
			{				
				if(izq_alt-der_alt==2)
				{
					dato<praiz->pizq->dato?rotarIzqIzq(ppraiz):rotarIzqDer(ppraiz);
					altura2(ppraiz);
				}
					
				else
					praiz->altura=izq_alt+1;
			}
		}			
		else
		{
			insertar(&(praiz->pder),dato);
			int izq_alt=altura(praiz->pizq);
			int der_alt=altura(praiz->pder);
			if(izq_alt<der_alt)
			{
				
				if(der_alt-izq_alt==2)
				{
					dato<praiz->pizq->dato?rotarDerIzq(ppraiz):rotarDerDer(ppraiz);
					altura2(ppraiz);
				}
					
				else
				praiz->altura=der_alt+1;
			}
			else
			{				
				if(izq_alt-der_alt==2)
				{
					dato<praiz->pizq->dato?rotarDerIzq(ppraiz):rotarDerDer(ppraiz);
					altura2(ppraiz);
				}
					
				else
					praiz->altura=izq_alt+1;
			}
		}
	}
	else
		*ppraiz=nuevo(dato);
}

#endif
