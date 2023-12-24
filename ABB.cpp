#include "ABB.h"
#include <stdio.h>
/*
Flores Gonzalez Rodrigo
Insertar, ver y borrar datos de un arbol de busqueda binario
*/

main()
{
	char opcion;
	int dato;
	Nodo* praiz=NULL;
	do
	{	
		printf("a. Insertar un nodo\n");
		printf("b. Borrar un nodo\n");
		printf("c. Ver representacion inorden\n");
		printf("d. Ver representacion preorden\n");
		printf("e. Ver representacion postorden\n");
		printf("f. Ver representacion jerarquica\n");
		printf("g. Salir\n");
		printf("opcion: ");
		scanf("%c",&opcion);
		switch(opcion)
		{
			case 'a':			
				printf("dato: ");
				scanf("%i",&dato);				
				insertar(&praiz,dato);
				system("pause");
				break;
			case 'b':
				printf("dato: ");
				scanf("%i",&dato);				
				borrar(praiz,dato);
				system("pause");
				break;
		    case 'c':
				inorden(praiz);
				printf("\n");
				system("pause");
				break;
			case 'd':
				preorden(praiz);
				printf("\n");
				system("pause");				
				break;
			case 'e':
				postorden(praiz);
				printf("\n");
				system("pause");
				break;
			case 'f':
				ver(praiz,altura(praiz));
				system("pause");
				break;
		}
		
		system("cls");
		
	}while(opcion!='g')
}
