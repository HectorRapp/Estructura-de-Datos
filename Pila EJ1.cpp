#include <stdio.h>
#include <stdlib.h>

typedef struct reg{
	char nombre[20];
	char direccion[20];
	int fono;
	char rut[11];
	int sueldo;
	struct nodo *sgte;
}reg;

typedef struct nodo{ 
	reg dato;
	struct nodo *sgte;
}nodo;

void crearPila(nodo *&tope){
	tope=NULL;
}

int pilaVacia(nodo *&tope){
	if(tope==NULL){
		return 1;
	}
	else{
		return 0;
	}
}

int insertar(nodo *&tope,reg elem){
	nodo *aux=(nodo*)malloc(sizeof(nodo));
	if(aux==NULL){
		return 0;
	}
	else{
		aux->dato=elem;
		aux->sgte=tope;
		tope=aux;
		return 1;
	}
}
int sacar (nodo *&tope,reg *des){
    nodo *aux;
    aux=tope;
    tope=aux->sgte;
    *des=aux->dato;
    free(aux);
    return 1;
}
int main(){
	int i,dato,c;
	char res[1];
	nodo *tope;
	crearPila(tope);
	reg valores;
	do{
		printf("Ingrese Nombre: "); fgets(valores.nombre,20,stdin); fflush(stdin);
		printf("Ingrese Direccion: "); fgets(valores.direccion,20,stdin); fflush(stdin);
		printf("Ingrese Telefono: "); scanf("%i",&valores.fono); fflush(stdin);
		printf("Ingrese Rut: "); scanf("%s",&valores.rut); fflush(stdin);
		printf("Ingrese Sueldo: "); scanf("%i",&valores.sueldo); 
		fflush(stdin);
		insertar(tope,valores);
		do{
		printf("Desea continuar? (s/n): ");
		scanf("%c",&res[0]);			
		fflush(stdin);
		} while(res[0]!='s' && res[0]!='n');
	} while(res[0]=='s');
		i=1;
	while(tope!=NULL){
		sacar(tope,&valores);
		printf("Trabajador %i: \n",i);		
		printf("\t Nombre: %s",valores.nombre);
		printf("\t Direccion: %s",valores.direccion);
		printf("\t Telefono: %i\n",valores.fono);
		printf("\t Rut: %s\n",valores.rut); 
		printf("\t Sueldo: %i\n\n",valores.sueldo); 
		i++;
	}
	return 0;
}
