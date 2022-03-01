#include<stdio.h>
#include<stdlib.h>

struct nodo {
    int id;
	char nombre[30];
    struct nodo *sig;
};

struct nodo *primero=NULL;

int menu(){
	int option=0;
	printf("\t\tMENU\n\n");
	printf("1. Insertar nodo en la %cltima posici%cn de la lista.\n", 163, 162);
	printf("2. Insertar nuevo nodo en cualquier posici%cn de la lista.\n", 162);
	printf("3. Insertar una persona antes de otra usando id.\n");
	printf("4. Eliminar nodo de una posici%cn de la lista indicada por el usuario.\n", 162);
	printf("5. Mostrar toda la lista.\n");
	printf("6. Salir.\n\n");
	printf("Ingrese la opci%cn a realizar: ", 162);
	scanf("%d", &option);
	return option;
}

void agregarNodoNuevo(struct nodo *primero)
{
        struct nodo *nuevo;
        nuevo=(struct nodo*)malloc(sizeof(struct nodo));
        printf("Ingrese su id: ");
        scanf("%d",&nuevo->id);
        fflush(stdin);
        printf("Ingrese su nombre: ");
        gets(nuevo->nombre);
        if (primero == NULL)
        {
            nuevo->sig = NULL;
            primero = nuevo;
        }
        else
        {
            struct nodo *temp = primero;
            while (temp->sig != NULL)
            {
                temp = temp->sig;
            }
            temp->sig = nuevo;
            nuevo->sig = NULL;
        }
}
void agregarNodoPos(struct nodo *primero);

void agregarNodoId(struct nodo *primero);

void eliminarNodo(struct nodo *primero);

void imprimirNodo(struct nodo *primero)
{
    struct nodo *temp = primero;
    printf("Contenido de la lista...\n");
    while (temp != NULL)
    {
        printf("Codigo: %i\n",temp->id);
        printf("Nombre: %s\n",temp->nombre);
 		printf("\n");      
        temp = temp->sig;
    }
    printf("%p", primero->sig);
    printf("\n");
}

int main(){
    int op=0;
	do{
		op=menu();
		switch(op){
	   	case 1:
		   agregarNodoNuevo(primero);
		   break;
	   	case 2:
		   agregarNodoPos(primero);
		   break;
	   	case 3:
		   agregarNodoId(primero);
		   break;
	   	case 4:
		   eliminarNodo(primero);
		   break;
		case 5:
			imprimirNodo(primero);
			break;
		case 6:
			printf("\nHasta luego.");
			break;
	   }	
	}while(op!=6);
	return 0;
}
