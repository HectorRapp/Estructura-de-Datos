#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int dato;
	nodo *ant;
	nodo *sgte;
}nodo;


/* ---- ---- Prototipos ---- ---- */
void Menu(nodo *&primero,nodo *&ultimo);
/* ---- ---- ---- ---- ---- ---- */

void Insertar(nodo *&primero,nodo *&ultimo){
	nodo* aux=(nodo*)malloc(sizeof(nodo));
	printf("Ingrese Dato: "); scanf("%i",&aux->dato);
	fflush(stdin);	
	if(primero == NULL) {
		primero = aux;
		ultimo = aux;
		primero->sgte = primero;
		primero->ant = ultimo;
	} 
	else {
		ultimo-> sgte = aux;
		aux-> ant = ultimo;
		aux-> sgte = primero;
		ultimo = aux;
		primero-> ant = ultimo;
	}

}

void Mostrar(nodo *&primero){
	nodo* aux=(nodo*)malloc(sizeof(nodo));
	aux=primero;
	if(primero==NULL){
		printf("\nLista Vacia\n");
		system("pause");
	}
	else{
		do{
			printf("%i  ",aux->dato);
			aux=aux->sgte;
		}while(aux!=primero);

		system("pause");
		system("cls");
	}
}

int validarDato(nodo *&primero,nodo *&ultimo,int valor){
	nodo* aux=(nodo*)malloc(sizeof(nodo));
	aux=primero;
	if(primero==NULL){
		printf("\nLista Vacia\n");
		system("pause");
		Menu(primero,ultimo);
	}
	else{
		do{
			if(aux->dato==valor){
				return 1;
			}
			aux=aux->sgte;
		}while(aux!=primero);
	}
	return 0;
}

void Eliminar(nodo *&primero,nodo *&ultimo,int valor){
	nodo* aux=(nodo*)malloc(sizeof(nodo));
	aux=primero;
	nodo* anterior=(nodo*)malloc(sizeof(nodo));
	anterior=NULL;
	bool encontrado=false; //Para que no entre en bucle cuando haya un solo elemento
	if(primero==NULL){
		printf("\nLista Vacia\n");
	}
	else{
		do{
			if(aux->dato==valor){
				if(primero==ultimo){
					primero=NULL;
					ultimo=NULL;
				}
				else if (aux == primero) {
					primero = primero-> sgte ;
					primero-> ant = ultimo;
					ultimo-> sgte = primero;
				}
				else  if (aux == ultimo) {
					ultimo = anterior;
					ultimo-> sgte = primero;
					primero-> ant = ultimo;
				} 
				else {
					anterior-> sgte = aux-> sgte ;
					aux-> sgte -> ant = anterior;
				}
				encontrado=true;
			}
			anterior=aux;
			aux=aux->sgte;
		} while (aux!=primero && encontrado!=true ); 
	}
			
}

void Menu(nodo *&primero,nodo *&ultimo){
	int opcion=-1,num=-1;
	do{
		system("cls");
		printf("Menu\n");
   		printf("----------------\n");
		printf("1 - Ingresar\n");
		printf("2 - Mostrar\n");
		printf("3 - Eliminar\n");
		printf("0 - Salir\n");
		printf("----------------\n");
		printf("Opcion: "); scanf("%i",&opcion); fflush(stdin);
		switch (opcion){
		case 1:
			Insertar(primero,ultimo);
			break;
		case 2:
			Mostrar(primero);
			break;
		case 3:
			do{
				printf("Ingrese dato a eliminar: "); scanf("%i",&num);
				fflush(stdin);
			} while(!validarDato(primero,ultimo,num));
			Eliminar(primero,ultimo,num);
			break;
		case 0:
			printf("\nHasta Luego...\n");
			break;
		default:
			system("cls");
			printf("\nOpcion no valida.\n");
			system("pause");
			break;
		}
	}while(opcion!=0);
}

int main(){	
	nodo *primero=NULL;
	nodo *ultimo=NULL;
	Menu(primero,ultimo);
	return 0;
}
