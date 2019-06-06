#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int dato;
	nodo *izq;
	nodo *der;
	nodo *padre;
}nodo;

nodo *arbol=NULL;

nodo *crearNodo(int n,nodo *padre){
	nodo *aux=(nodo*)malloc(sizeof(nodo));
	aux->dato=n;
	aux->der=NULL;
	aux->izq=NULL;
	aux->padre=padre;
	return aux;
}

void insertarNodo(nodo *&arbol,int n,nodo *padre){
	if(arbol==NULL){
		nodo *aux = crearNodo(n,padre);
		arbol = aux;
	}
	else{
		int valorRaiz=arbol->dato;
		if(valorRaiz>n){
			insertarNodo(arbol->izq,n,arbol);
		}
		else{
			insertarNodo(arbol->der,n,arbol);
		}
	}
}

void mostrarArbol(nodo *arbol,int contador){
	if(arbol==NULL){
		return;
	}
	else{
		mostrarArbol(arbol->der,contador+1);
		for(int i=0;i<contador;i++){
			printf("   ");
		}
		printf("%i\n",arbol->dato);
		mostrarArbol(arbol->izq,contador+1);
	}
}

bool buscarNodo(nodo *arbol,int n){
	if(arbol==NULL){
		return 0;
	}
	else if(arbol->dato == n){
		return true;
	}
	else if(arbol->dato>n){
		return buscarNodo(arbol->izq,n);
	}
	else{
		return buscarNodo(arbol->der,n);
	}
}

void preOrden(nodo *arbol){ //Recorrido en Profundidad - PreOrden (se muestra la raíz y luego por la izquierda)
	if(arbol==NULL){
		return;
	}
	else{
		printf("%i  ",arbol->dato);
		preOrden(arbol->izq);
		preOrden(arbol->der);
	}
}

void inOrden(nodo *arbol){ //Recorrido en Profundidad - InOrden(por la izquierda y luego la raíz)
	if(arbol==NULL){
		return;
	}
	else{
		inOrden(arbol->izq);
		printf("%i  ",arbol->dato);
		inOrden(arbol->der);
	}

}

void postOrden(nodo *arbol){ //Recorrido en Profundidad - PostOrden(por la izquierda, luego por la derecha y despues la raíz)
	if(arbol==NULL){
		return;
	}
	else{
		postOrden(arbol->izq);
		postOrden(arbol->der);
		printf("%i  ",arbol->dato);
	}
}

nodo *minimo(nodo *arbol){ //Busca el nodo mas izquierdo posible (menor), para reemplazarlo por el nodo eliminado. - Nodos con 2 hijos
	if(arbol==NULL){
		return NULL;
	}
	if(arbol->izq){
		return minimo(arbol->izq);
	}
	else{
		return arbol; 
	}
}

void destruirNodo(nodo *nodo){
	nodo->izq=NULL;
	nodo->der=NULL;
	free(nodo);
}

void reemplazar(nodo *arbol,nodo *aux){
	if(arbol->padre){ //padre apunta al nuevo hijo
		if(arbol->dato==arbol->padre->izq->dato){ //comprobar si es el hijo izq
		arbol->padre->izq=aux;
		}
		else if(arbol->dato==arbol->padre->der->dato){ //comprobar si es el hijo der
			arbol->padre->der=aux;
		}
	}
	if(aux){ //nuevo hijo apunta al padre
		aux->padre = arbol->padre;
	}

}

void eliminarNodo(nodo *nodoEliminar){
	if(nodoEliminar->izq && nodoEliminar->der){ //Si tiene 2 hijos
		nodo *menor = minimo(nodoEliminar->der);
		nodoEliminar->dato=menor->dato;
		eliminarNodo(menor);
	}
	else if(nodoEliminar->izq){ //Si tiene hijo izq
		reemplazar(nodoEliminar,nodoEliminar->izq);
		destruirNodo(nodoEliminar);
	}
	else if(nodoEliminar->der){ //Si tiene hijo der
		reemplazar(nodoEliminar,nodoEliminar->der);
		destruirNodo(nodoEliminar);		
	}
	else{ //No tiene hijos
		reemplazar(nodoEliminar,NULL);
		destruirNodo(nodoEliminar);
	}
}

void eliminar(nodo *arbol,int n){ //busca el nodo
	if(arbol==NULL){
		return;
	}
	else if(n<arbol->dato){
		eliminar(arbol->izq,n);
	}
	else if(n>arbol->dato){
		eliminar(arbol->der,n);
	}
	else{ //Una vez encontrado
		eliminarNodo(arbol);
	}
}

void menu(){
	int valor,opcion,contador=0;
	do{
		system("cls");
		printf("*************************\n");
		printf("1 - Insertar\n");
		printf("2 - Mostrar\n");
		printf("3 - Mostrar en PreOrden\n");
		printf("4 - Mostrar en InOrden\n");
		printf("5 - Mostrar en PostOrden\n");
		printf("6 - Buscar\n");
		printf("7 - Eliminar\n");
		printf("8 - Salir\n");
		printf("*************************\n");
		printf("Opcion: "); scanf("%i",&opcion);	
		fflush(stdin);
		switch (opcion){
			case 1:
				system("cls");
				printf("Ingrese un Valor: "); scanf("%i",&valor);
				insertarNodo(arbol,valor,NULL);
				break;
			
			case 2:
				system("cls");
				printf("Arbol\n\n");
				mostrarArbol(arbol,contador);
				system("pause");
				break;
			
			case 3:
				system("cls");
				printf("Recorrido en PreOrden\n");
				preOrden(arbol);
				system("pause");
				break;

			case 4:
				system("cls");
				printf("Recorrido en InOrden\n");
				inOrden(arbol);
				system("pause");
				break;

			case 5:
				system("cls");
				printf("Recorrido en PostOrden\n");
				postOrden(arbol);
				system("pause");
				break;

			case 6:
				printf("Ingrese Numero a Buscar: "); scanf("%i",&valor);
				if(buscarNodo(arbol,valor)){
					printf("\nDato encontrado\n");
				}
				else{
					printf("\nNo encontrado\n");
				}
				system("pause");
				break;

			case 7:
				do{
					system("cls");
					printf("Ingrese Numero a Eliminar: "); scanf("%i",&valor); fflush(stdin);
					if(!buscarNodo(arbol,valor)){
						printf("\nEl Numero no Existe.\n");
						system("pause"); 
						system("cls");
					}
				} while(!buscarNodo(arbol,valor));
				eliminar(arbol,valor);
				break;

			default:
				system("cls");	
				printf("\nOpcion no Valida\n");
				break;
		}
	}while (opcion!=8);	
}	

int main(){
	menu();
	system("pause");
	return 0;
}
