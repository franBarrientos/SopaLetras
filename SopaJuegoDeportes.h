/* TIPO DE DATOS ABSTRACTO: CATEGORIA DEPORTES */

/* librerias */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/* valores constantes */
#define CADENA_D 30
#define MAX_PAL_D 6
#define MAX_COLUM_D 8
#define MAX_FILA_D 8 

/* definicion tipo de dato cadena */
typedef char tc_cadCar[CADENA_D];

/* definicion registro de palabra */
typedef struct {
	int categoria;
	tc_cadCar palabra;
}tr_sopaLetras_D;

/* definicion tipo vector de registro (palabras) */
typedef tr_sopaLetras_D tArrayPalCat_D[MAX_PAL_D];

/* definicion estructura lista estatica */
typedef struct {
	tArrayPalCat_D listaPalabras;
	int indice;
} tLista_D;

/* definicion estructura pila estatica */
typedef struct {
	tArrayPalCat_D pilaPalabras;
	int tope;
} tPila_D;

/* definicion de matriz */
typedef char tMatriz[MAX_FILA_D][MAX_COLUM_D];

/* prototipado funciones - archivo binario */
void iniciarProceso_D();
void leerArchivo_D();
void procesarRegistros_D();
void finalizarProceso_D();

/* prototipado funciones definidas por el programador */
void inicializarFunciones_D();
void ingresarPalabra_D();
void comparaPalabras_D(tLista_D, tPila_D);
void condBuscarPalabra_D();
void procesaBusqueda_D();
void cantPalabrasEncontradas_D();
bool estaEnPila_D(tPila_D, tc_cadCar);

/* prototipado funciones - lista estática */
void inicializarLista_D();
bool listaVacia_D(tLista_D);
bool listaLlena_D(tLista_D);
void insertarElementos_D(tr_sopaLetras_D);
void visualizarElementos_D(tLista_D);

/* prototipado funciones - pila */
void crearPila_D();
bool pilaVacia_D(tPila_D);
bool pilaLlena_D(tPila_D);
void apilarPalabra_D(tr_sopaLetras_D);
void visualizarPila_D();
void desapilarPalabra_D();

/* prototipado funciones - matriz */
void inicializarMatriz_D();
void asignarLetrasSopa_D();
void asignarLetrasAzar_D();
void visualizarMatriz_D();

/* variables registro, fichero, lista estática, pila y matriz */
tr_sopaLetras_D vr_sopaLetras_D;
FILE * vf_sopaLetras_D;
tLista_D lista_D;
tPila_D pila_D;
tMatriz sopa_D;

/* variable de entrada( palabra ingresada por teclado ) */
tc_cadCar palabra;

/* var de entrada( define si sigue o no comparando palabras ) */
char condComparaPal;

/* contadores */
int palCorrectas, palIncorrectas;

/* inicializaciones de lista - pila - archivo y matriz */

void inicializarFunciones_D() {
	inicializarLista_D();
	crearPila_D();
	inicializarMatriz_D();
	iniciarProceso_D();
	
	/* inicializacion de contadores */
	palCorrectas = 0;
	palIncorrectas = 0;
}

/* declaración de instrucciones funciones de archivo */

void iniciarProceso_D() {
	/* apertura del archivo en modo "lectura" */
	vf_sopaLetras_D = fopen("SopaLetrasJuego.dat", "rb");
	
	/* lectura adelantada */
	leerArchivo_D();
}

void leerArchivo_D() {
	/* lectura de cada registro dentro del archivo binario */
	fread(&vr_sopaLetras_D, sizeof(tr_sopaLetras_D), 1, vf_sopaLetras_D);
}

void procesarRegistros_D() {
		/* mientras que, no sea el ultimo registro leido en el archivo, y se cumpla la condicion que la categoria pertenezca al nro 1 (frutas) 
	   el registro se almacena en una lista estatica *//* se realiza la insercion de datos, partiendo del registro hasta una lista estatica */
	while( !feof(vf_sopaLetras_D) ) {
		if (vr_sopaLetras_D.categoria == 2 ) {
			insertarElementos_D(vr_sopaLetras_D);
		}
		/* realiza la lectura del siguiente registro */
		leerArchivo_D();
	}
	/* una vez que inserta el ultimo dato, se corta la iteracion y se cierra el archivo */
	finalizarProceso_D();
}

void finalizarProceso_D() {
	/* cierre del archivo binario */
	fclose(vf_sopaLetras_D);
}

/* declaracion de instrucciones funciones de matriz categoria deportes */

void inicializarMatriz_D() {
	/* se realiza el correspondiente recorrido para asignar cada posicion de la matriz (fila/columna) como valor inicial 'vacio' */
	int i, j;
	
	for (i = 0; i < MAX_FILA_D; i++) {
		for (j = 0; j < MAX_COLUM_D; j++) {
			sopa_D[i][j] = ' ';
		}
	}
	/* se muestra titulo de presentacion */
	printf("\n\t *** ENSOPA-2 - CATEGORIA DEPORTES ***\n\n");
}

void asignarLetrasAzar_D() {
	/* de acuerdo con la funcion rand(), se asigna a cada posicion de la matriz un caracter al azar entre la A y la Z mayuscula */
	int i, j;
	
	srand(time (NULL) );
	
	for (i = 0; i < MAX_FILA_D; i++) {
		for (j = 0; j < MAX_COLUM_D; j++) {
			sopa_D[i][j] = 'A' + rand() % ('Z' - 'A'+1 );
		}
	}
}

void asignarLetrasSopa_D() {
	/* para cada posicion (fila/columna) se define el caracter a ocupar, para luego, formar y determinar el sentido de la palabra (vertical u horizontal) */
	sopa_D[0][1] = 'F'; sopa_D[1][1] = 'U'; sopa_D[2][1] = 'T'; sopa_D[3][1] = 'B'; sopa_D[4][1] = 'O'; sopa_D[5][1] = 'L';
	sopa_D[3][1] = 'B'; sopa_D[3][2] = 'A'; sopa_D[3][3] = 'S'; sopa_D[3][4] = 'K'; sopa_D[3][5] = 'E'; sopa_D[3][6] = 'T';
	sopa_D[7][0] = 'V'; sopa_D[7][1] = 'O'; sopa_D[7][2] = 'L'; sopa_D[7][3] = 'E'; sopa_D[7][4] = 'Y';
	sopa_D[3][3] = 'S'; sopa_D[4][3] = 'K'; sopa_D[5][3] = 'A'; sopa_D[6][3] = 'T'; sopa_D[7][3] = 'E';
	sopa_D[3][6] = 'T'; sopa_D[4][6] = 'E'; sopa_D[5][6] = 'N'; sopa_D[6][6] = 'I'; sopa_D[7][6] = 'S';
	sopa_D[1][3] = 'R'; sopa_D[1][4] = 'U'; sopa_D[1][5] = 'G'; sopa_D[1][6] = 'B'; sopa_D[1][7] = 'Y';
}

void visualizarMatriz_D() {
	/* a partir del recorrido desde el inicio hasta el final de la matriz, se muestran los caracteres correspondientes */
	int i, j;
	
	for (i = 0; i < MAX_FILA_D; i++) {
		printf("\t");
		for (j = 0; j < MAX_COLUM_D; j++) {
			printf(" %c | ", sopa_D[i][j] );
		}
		printf("\n");
	}
}

/* declaración de instrcucciones funciones de lista estática */

void inicializarLista_D() {
	/* el valor de la lista se inicializa en -1, porque el primer elemento a insertar lo hará en la posicion 0 */
	lista_D.indice = -1;
}

bool listaVacia_D(tLista_D pLista) {
	/* devuelve "true" si el valor de la lista es -1, es decir, si esta vacia. 
	Caso contrario, si tiene por lo menos 1 elemento, devuelve "false" */
	return pLista.indice == -1;
}

bool listaLlena_D(tLista_D pLista) {
	/* devuelve "true" si el valor de la lista es igual al limite maximo de palabras admitidas, en ese caso, 7 palabras. 
	   De lo contratio, devuelve "false" */
	return pLista.indice == MAX_PAL_D - 1;	
}

void insertarElementos_D(tr_sopaLetras_D pSopa) {
	/* si la lista no esta llena, significa que tenemos espacio para seguir insertando datos. el indice avanza un valor 
	   y se realiza la insercion de lo que se recibe por parametro en la lista de palabras. 
	   de lo contrario, si la lista esta llena, se informara un aviso */
	if( !listaLlena_D(lista_D) ) {
		lista_D.indice+=1;
		lista_D.listaPalabras[lista_D.indice] = pSopa;
	} else {
		printf("\n\t\t *** No pueden agregar mas de %d palabras. La lista esta llena *** \n", MAX_PAL_D);
	}
}

void visualizarElementos_D(tLista_D pLista) {
	/* si la lista no esta vacia, significa que hay elementos para mostrar, lo hace a traves de un recorrido que muestra los elementos 
	   a medida que se desplaza por el vector, el recorrido inicia desde 0 hasta el elemento final (indice) */
	int i;
	
	if( !listaVacia_D(lista_D) ) {
		printf("\n Palabras en la lista \n\n");
		
		for(i=0; i <= pLista.indice; i++) {
			printf(" %s - ", pLista.listaPalabras[i].palabra);
		}
	} else {
		printf("\n\t\t *** No es posible listar los elementos. Lista vacia! *** \n");
	}
	printf("\n\n");
}

/* declaración de instrucciones funciones de pila */

void crearPila_D() {
	/* el valor de la pila se inicializa en -1, porque el primer elemento a insertar lo hará en la posicion 0 */
	pila_D.tope = -1;
}

bool pilaVacia_D(tPila_D pPila) {
	/* devuelve "true" si el valor de la pila es -1, es decir, si esta vacia. 
	Caso contrario, si tiene por lo menos 1 elemento, devuelve "false" */
	return pPila.tope == -1;
}

bool pilaLlena_D(tPila_D pPila) {
	/* devuelve "true" si el valor de la pila es igual al limite maximo de palabras admitidas, en ese caso, 7 palabras. 
	   De lo contratio, devuelve "false" */
	return pPila.tope == MAX_PAL_D-1;
}

void apilarPalabra_D(tr_sopaLetras_D pPalYcat) {
	/* si la pila no esta llena, significa que tenemos espacio para seguir insertando datos. el tope incrementa un valor 
	   y se realiza la insercion de lo que se recibe por parametro en la pila de palabras. 
	   de lo contrario, si la pila esta llena, se informara un aviso */
	if( !pilaLlena_D(pila_D) ) {
		pila_D.tope+=1;
		pila_D.pilaPalabras[pila_D.tope] = pPalYcat;
	} else {
		printf("\n *** No es posible almacenar mas de %d elementos *** \n", MAX_PAL_D);
	}
}

void visualizarPila_D() {
	/* si la pila esta vacia, significa que no hay elementos por mostrar y se notificará mediante un aviso, de lo contrario, 
	muestra los elementos a medida que se desplaza por el vector, el recorrido inicia desde 0 hasta el elemento final (tope) */
	int i;
	
	if(pilaVacia_D(pila_D)) {
		printf("\n *** No se encontraron palabras! *** \n");
	} else {
		printf("\n\t *** FIN DEL JUEGO *** \n\n Palabras encontradas: \n");
		
		for(i=0; i <= pila_D.tope; i++) {
			printf(" %s - ", pila_D.pilaPalabras[i].palabra);
		}
	}
	/* al final del juego se muestran los resultados correspondientes a las palabras acertadas y los errores */
	cantPalabrasEncontradas_D();
}

/* declaracion de instrucciones funciones definidas por el programador */

void cantPalabrasEncontradas_D() {
	/* se muestran los resultados correspondientes */
	printf("\n\n Encontraste %d palabras correctas", palCorrectas);
	printf("\n Realizaste %d palabras incorrectas\n", palIncorrectas);
}

void condBuscarPalabra_D() {
	/* pregunta al usuario si ha encontrado una palabra */
	printf("\n Ha encontrado una palabra? (s/n): ");
	fflush(stdin);
	scanf("%c", &condComparaPal);
	
	/* invocacion a la funcion que realizara el proceso de busqueda y comparacion de la palabra */
	procesaBusqueda_D();
}

void procesaBusqueda_D() {
	/* mientras que el usuario haya encontrado palabras, es decir, ingresa la letra 's', registrará esa palabra por teclado, 
	   se realiza la comparacion de la palabra ingresada por teclado con la palabra almacenada en la lista y la pila, una vez terminado este proceso,
	   se vuelve a preguntar al usuario si encontro alguna otra palabra, la condicion terminara su ejecucion cuando el usuario ingrese la letra 'n' */
	while(condComparaPal == 's' || condComparaPal == 'S') {
		ingresarPalabra_D();
		comparaPalabras_D(lista_D, pila_D);
		condBuscarPalabra_D();
	}
}

void ingresarPalabra_D() {
	/* ingresa por teclado la palabra que descubre el usuario */
	printf("\n Escriba la palabra: ");
	fflush(stdin);
	scanf("%s", &palabra);
}

bool estaEnPila_D(tPila_D pPila, tc_cadCar palabra){
	/* si el valor del tope es el valor del inicio (-1) significa que la palabra no esta dentro de la pila, por lo tanto, devuelve 'false' 
	   si el valor es distinto del tope, se recorre la pila desde el inicio hasta el final (tope) comparando si la palabra que se ingreso por teclado 
	   coincide con alguna palabra ya almacenada en la pila, si esto es asi, devuelve 'true', de otra manera, devuelve 'false' */
	int i;
	
	if(pPila.tope == -1){
		return false;
	} else {
		for(i=0; i <= pPila.tope; i++){
			if(strcmp(pPila.pilaPalabras[i].palabra, palabra) == 0){
				return true;
			}
		}
		return false;
	}
}

void comparaPalabras_D(tLista_D pLista, tPila_D pPila) {
	/* recorre la lista de palabras almacenadas desde el inicio hasta el final (indice) y compara la palabra que se ingreso 
	   por teclado con alguna de las palabras que se encuentra en la lista, si la misma coincide y
	   ademas se cumple que dicha palabra no se encuentra almacenada en la pila, la misma va a apilarse y cambia el valor de la variable bandera.
	   luego, si la bandera es valor 'true' significa que apilo la palabra y la misma se encuentra en la cuadricula, incrementa el contador de la palabra correcta
	   si, por el contrario, la bandera es valor 'false', significa que la palabra ya fue almacenada, o, que no se encuentra en la cuadricula e,  incrementa el contador de la palabra incorrecta */
	int i;
	bool flag_D = false;
	
	for(i=0; i <= pLista.indice && flag_D != true; i++) {
		if(strcmp(pLista.listaPalabras[i].palabra, palabra) == 0) {
			
			if(!estaEnPila_D(pPila, palabra)){
				apilarPalabra_D(pLista.listaPalabras[i]);
				flag_D = true;
			}
		}
	}
	
	if(flag_D == true) {
		printf(" La palabra se encuentra en la sopa! \n");
		palCorrectas += 1;
	} else {
		printf(" Ups! Esa palabra ya la encontraste, o no esta dentro de la sopa\n Intentalo de nuevo! \n");
		palIncorrectas += 1;
	}
}
