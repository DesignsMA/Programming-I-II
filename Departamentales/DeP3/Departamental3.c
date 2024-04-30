#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h> //Para usar sleep()

typedef struct nodo {
    char uid[8]; //ABC-789\0
	int urgencia, operaciones;
	struct nodo *sig;
}NODO;

/*Recibe un apuntador al primer caracter de una cadena, la modifica y genera un
  codigo de forma ABC-123 donde las letras y numeros son aleatorias en base a la 
  semilla generada por el tiempo, recibe como  parametro un apuntador a un arreglo
  de caracteres de forma &uid[0].
*/
void  uid ( char *uid) {
    int min = 65, max = 90, i = 0;
    printf("\nRegistrando en la lista");
    for(int i = 0; i < 10; i++) 
    {
        usleep(100000); //Pausa por 100000 microsegundos
        printf(".");
    } //pausa de un segundo

    srand(time(NULL));//se genera la semilla
    for(i; i < 3; i++) {
        uid[i] = rand() % (max - min + 1) + min; 
    }
    uid[i] = '-';
    i++;
    for(i; i < 7; i++) {
        uid[i] = rand() % ('9' - '1' + 1) + '1';
    }
}

void imprimeLista(NODO *ap){
	while(ap!=NULL) {
		printf("\nUrgencia: %d | Operaciones: %d | UID: %s", ap->urgencia, ap->operaciones, ap->uid);
		ap=ap->sig;
	}
	printf("\nFin\n\n");
} 
NODO *creaNodo (int urgencia, int operaciones) {
	NODO *nuevo;
	nuevo=(NODO *)malloc(sizeof(NODO));
	if (nuevo != NULL) {
		nuevo->urgencia=urgencia;
        nuevo->operaciones=operaciones;
        //nuevo->uid = (char *)malloc(sizeof(char) * 8);
        uid(&nuevo->uid[0]);
		nuevo->sig=NULL;
	}
	return nuevo;
}

NODO *insertaFinal(NODO *ap, int urgencia, int operaciones) {
	NODO *aux, *nuevo;
	
	nuevo=creaNodo(urgencia,operaciones);
	if (nuevo == NULL) return ap;
	if (ap==NULL) {
		ap=nuevo;
	}
	else {
		aux=ap;
		while(aux->sig != NULL) {
			aux=aux->sig;
		}	
		aux->sig=nuevo;
	}
	return ap;
}

NODO *insertaAlInicio(NODO *ap, int urgencia, int operaciones) {
	NODO *aux, *nuevo;
	
	nuevo=creaNodo(urgencia, operaciones);
	if (nuevo == NULL) return ap;
	aux=ap; //raiz
	ap=nuevo; //nuevo
	nuevo->sig=aux; //nuevo apunta a raiz
	return ap; //se actualiza la raiz
}

NODO *insertaUrgencia(NODO *ap, int urgencia, int operaciones) {
	NODO *aux, *anterior, *nuevo, *pos1, *pos2;
    int distancia;
	
	nuevo=creaNodo(urgencia,operaciones);
	if (nuevo == NULL) return ap;
	if (ap==NULL) {
		ap=nuevo;
	}
	else {
			distancia = nuevo->urgencia;
			while(aux != NULL) 
            {
				anterior = ap;
                aux=anterior->sig; //se recorre al siguiente nodo
				if (aux == NULL)
				{
					if (anterior->urgencia > nuevo->urgencia)
					{
						nuevo->sig = anterior;
						anterior->sig = NULL;
						ap = nuevo;
												
					}
					else if ( anterior->urgencia <= nuevo->urgencia )
					{
						anterior->sig = nuevo;
					}	
				}
				else if (anterior->urgencia != aux->urgencia) 
                {
                    if ( aux->urgencia - nuevo->urgencia < distancia )
                        {
                            distancia = aux->urgencia - nuevo->urgencia;
                            pos1 = anterior;
                            pos2 = aux;
                        }
                }
                
			}
			//se inserta el nuevo nodo en la lista
            if (  distancia >=0 && aux != NULL )
            {
                pos1->sig = nuevo;
                nuevo->sig = pos2;
            }
            else if (distancia < 0 && aux != NULL)
            {
                pos2->sig = nuevo;
            }
        	
		}
	
	return ap;
}

int cuentaNodos(NODO *ap){
	int c;
	
	c=0;
	while (ap!=NULL) {
		ap=ap->sig;
		c++;
	}
	return c;
}
	
int main() {
	NODO *raiz, *raiz1;

	printf("\nPrimera lista");
	raiz=NULL;
    raiz=insertaUrgencia(raiz, 3,3);
	imprimeLista(raiz);
    raiz=insertaUrgencia(raiz, 1,2);
	imprimeLista(raiz);
    raiz=insertaUrgencia(raiz, 2,1);
	imprimeLista(raiz);
    raiz=insertaUrgencia(raiz, 3,2);
    raiz=insertaUrgencia(raiz, 4,2);
    imprimeLista(raiz);
}