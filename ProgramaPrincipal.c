/* SOPA DE LETRAS "ENSOPA-2" - PROGRAMA PRINCIPAL */

/* librerias */
#include <stdio.h>
#include <locale.h>
#include "SopaJuegoFrutas.h"
#include "SopaJuegoDeportes.h"
#include "SopaJuegoAnimales.h"

/*Estructura*/
typedef struct nodo{
	float dato;
	struct nodo *left;
	struct nodo *right;
}pArbol;

pArbol * raiz;

/*Prototipos*/
/*tNodo* crearNodo(int );*/
void cargarArbol();
void push(pArbol** ,float);
void preOrden(pArbol*);

/* prototipado */
void menu ();
void juegoAnimales();
void juegoFrutas();
void juegoDeportes();

/* variables gloabales */
int opcion, juego;
clock_t t;
/* función principal */
int main() {
	/* el programa se configura al idioma español */
	setlocale (LC_ALL, "spanish");
	menu ();
	return 0;
}

void menu () {
	cargarArbol();
	printf ("\n\t *** BIENVENIDO! ***\n\n 1- Jugar a Ensopa2\n 0- Salir\n Su respuesta es: ");
    scanf ("%d", &opcion);

    if (opcion == 1) {
    	printf ("\n Que tipo del juego Ensopa2 desea jugar?\n 1- Frutas\n 2- Deportes\n 3- Animales\n 0- Volver\n\n Su respuesta es:  ");
    	scanf ("%d", &juego);
    	
    	switch (juego) {
        case 1:
        	t = clock();
            juegoFrutas();
            t = clock()-t;
            printf("\n Tiempo de juego : %f ",(float)t/CLOCKS_PER_SEC);
            push(&raiz,(float)t/CLOCKS_PER_SEC);
			printf("\n\n\t Recorrido PreOrden \n");	
			preOrden(raiz);
            menu ();
            break;
        case 2:
        	t = clock();
        	juegoDeportes();
        	t = clock()-t;
        		printf("\n Tiempo de juego : %f ",(float)t/CLOCKS_PER_SEC);
    	push(&raiz,(float)t/CLOCKS_PER_SEC);
    	printf("\n\n\t Recorrido PreOrden \n");	
    	preOrden(raiz);

            menu ();
            break;
        case 3:
        	t = clock();
        	juegoAnimales();
        	t = clock()-t;
	        printf("\n Tiempo de juego : %f ",(float)t/CLOCKS_PER_SEC);
    	push(&raiz,(float)t/CLOCKS_PER_SEC);
    	printf("\n\n\t Recorrido PreOrden \n");	
    	preOrden(raiz);

            menu ();
            break;
        case 0:
            printf ("\n\t*** Gracias por jugar. Vuelva prontos! *** \n");
            menu ();
            break;
    	}

	
    	
/*Mostrar arbol con score*/
    } else {
    	printf ("\n\t*** Gracias por jugar. Vuelva prontos! *** \n");
		printf ("\n\tSe cerró el programa");
    }
}

/* Operatividad (juegoFrutas() - juegoDeportes() - juegoAnimales() ): 
		1. inicializar las estructuras con las que se van a trabajar (pila - lista - archivo binario - matriz)
		2. obtener cada registro del archivo para luego guardarlo en una lista estatica (vector)
		3. asignar los caracteres (aleatorio y fijo) a la matriz
		4. mostrar la matriz resultante de cada categoria de juego
		5.  si el usuario ha encontrado una palabra, ingresa la misma teclado, se compara lo que se ingreso con la lista, 
			si esta dentro de ella, se apila la palabra, de lo contrario, se emite un mje
		6. una vez que no haya encontrado palabras, se hace el listado de palabras encontradas dentro de la pila
		7. se muestra la cantidad de palabras encontradas
*/

void juegoFrutas() {
	inicializarFunciones_F();
	procesarRegistros_F();
	asignarLetrasAzar_F();
	asignarLetrasSopa_F();
	visualizarMatriz_F();
	condBuscarPalabra_F();
	visualizarPila_F();
}

void juegoDeportes() {
	inicializarFunciones_D();
	procesarRegistros_D();
	asignarLetrasAzar_D();
	asignarLetrasSopa_D();
	visualizarMatriz_D();
	condBuscarPalabra_D();
	visualizarPila_D();
}

void juegoAnimales() {
	inicializarFunciones();
	procesarRegistros();
	asignarLetrasAzar();
	asignarLetrasSopa();
	visualizarMatriz();
	condBuscarPalabra();
	visualizarPila();
}
void cargarArbol(){
	raiz = NULL;
	push(&raiz, 8.66);
	push(&raiz, 4.5);
	push(&raiz, 1.65);
	push(&raiz, 33.77);
	push(&raiz, 17.45);
	
	
}

void push(pArbol ** raiz,float a){
	if(*raiz==NULL){
		*raiz = malloc(sizeof(pArbol));
        (*raiz)->dato = a;
        (*raiz)->left = NULL;
        (*raiz)->right = NULL;	
	}else{
		if(a<(*raiz)->dato){
			push(&(*raiz)->left,a);
		}else{
			push(&(*raiz)->right,a);
		}
	}
	
}

void preOrden(pArbol * raiz){
	if(raiz != NULL){
		printf("%.2f \n",raiz->dato);
		preOrden(raiz->left);
		preOrden(raiz->right);

	}
}
