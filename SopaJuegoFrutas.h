/* TIPO DE DATOS ABSTRACTO: CATEGORIA FRUTAS */

/* librerias */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/* valores constantes */
#define CADENA_F 30
#define MAX_PAL_F 7
#define MAX_COLUM_F 8
#define MAX_FILA_F 8 

/* definicion tipo de dato cadena */
typedef char tc_cadCar[CADENA_F];

/* definicion registro de palabra */
typedef struct {
	int categoria;
	tc_cadCar palabra;
}tr_sopaLetras_F;

/* definicion tipo vector de registro (palabras) */
typedef tr_sopaLetras_F tArrayPalCat_F[MAX_PAL_F];

/* definicion estructura lista estatica */
typedef struct {
	tArrayPalCat_F listaPalabras;
	int indice;
} tLista_F;

/* definicion estructura pila estatica */
typedef struct {
	tArrayPalCat_F pilaPalabras;
	int tope;
} tPila_F;

/* definicion de matriz */
typedef char tMatriz[MAX_FILA_F][MAX_COLUM_F];

/* prototipado funciones - archivo binario */
void iniciarProceso_F();
void leerArchivo_F();
void procesarRegistros_F();
void finalizarProceso_F();

/* prototipado funciones definidas por el programador */
void inicializarFunciones_F();
void ingresarPalabra_F();
void comparaPalabras_F(tLista_F, tPila_F);
void condBuscarPalabra_F();
void procesaBusqueda_F();
void cantPalabrasEncontradas_F();
bool estaEnPila_F(tPila_F, tc_cadCar);

/* prototipado funciones - lista est�tica */
void inicializarLista_F();
bool listaVacia_F(tLista_F);
bool listaLlena_F(tLista_F);
void insertarElementos_F(tr_sopaLetras_F);
void visualizarElementos_F(tLista_F);

/* prototipado funciones - pila */
void crearPila_F();
bool pilaVacia_F(tPila_F);
bool pilaLlena_F(tPila_F);
void apilarPalabra_F(tr_sopaLetras_F);
void visualizarPila_F();
void desapilarPalabra_F();

/* prototipado funciones - matriz */
void inicializarMatriz_F();
void asignarLetrasSopa_F();
void asignarLetrasAzar_F();
void visualizarMatriz_F();

/* variables registro, fichero, lista est�tica, pila y matriz */
tr_sopaLetras_F vr_sopaLetras_F;
FILE * vf_sopaLetras_F;
tLista_F lista_F;
tPila_F pila_F;
tMatriz sopa_F;

/* variable de entrada( palabra ingresada por teclado ) */
tc_cadCar palabra;

/* var de entrada( define si sigue o no comparando palabras ) */
char condComparaPal;

/* contadores */
int palCorrectas, palIncorrectas;

/* inicializaciones de lista - pila - matriz y archivo binario */

void inicializarFunciones_F() {
	inicializarLista_F();
	crearPila_F();
	inicializarMatriz_F();
	iniciarProceso_F();
	
	/* inicializacion de contadores */
	palCorrectas = 0;
	palIncorrectas = 0;
}

/* declaraci�n de instrucciones funciones de archivo */

void iniciarProceso_F() {
	/* apertura del archivo en modo "lectura" */
	vf_sopaLetras_F = fopen("SopaLetrasJuego.dat", "rb");
	
	/* lectura adelantada */
	leerArchivo_F();
}

void leerArchivo_F() {
	/* lectura de cada registro dentro del archivo binario */
	fread(&vr_sopaLetras_F, sizeof(tr_sopaLetras_F), 1, vf_sopaLetras_F);
}

void procesarRegistros_F() {
	/* mientras que, no sea el ultimo registro leido en el archivo, y se cumpla la condicion que la categoria pertenezca al nro 1 (frutas) 
	   el registro se almacena en una lista estatica */
	while( !feof(vf_sopaLetras_F) ) {
		if (vr_sopaLetras_F.categoria == 1) {
			insertarElementos_F(vr_sopaLetras_F);
		}
		/* realiza la lectura del siguiente registro */
		leerArchivo_F();
	}
	/* una vez que inserta el ultimo dato, se corta la ejecucion de la iteracion y se cierra el archivo */
	finalizarProceso_F();
}

void finalizarProceso_F() {
	/* cierre del archivo binario */
	fclose(vf_sopaLetras_F);
}

/* declaracion de instrucciones funciones de matriz - categoria fruta */

void inicializarMatriz_F() {
	/* se realiza el correspondiente recorrido para asignar cada posicion de la matriz (fila/columna) como valor inicial 'vacio' */
	int i, j;
	
	for (i = 0; i < MAX_FILA_F; i++) {
		for (j = 0; j < MAX_COLUM_F; j++) {
			sopa_F[i][j] = ' ';
		}
	}
	/* se muestra titulo de presentacion */
	printf("\n\t *** ENSOPA-2 - CATEGORIA FRUTAS ***\n\n");
}

void asignarLetrasAzar_F() {
	/* de acuerdo con la funcion rand(), se asigna a cada posicion de la matriz un caracter al azar entre la A y la Z mayuscula */
	int i, j;
	
	srand(time (NULL) );
	
	for (i = 0; i < MAX_FILA_F; i++) {
		for (j = 0; j < MAX_COLUM_F; j++) {
			sopa_F[i][j] = 'A' + rand() % ('Z' - 'A'+1 );
		}
	}
}

void asignarLetrasSopa_F() {
	/* para cada posicion (fila/columna) se define el caracter a ocupar, para luego, formar y determinar el sentido de la palabra (vertical u horizontal) */
	sopa_F[1][0] = 'A'; sopa_F[1][1] = 'N'; sopa_F[1][2] = 'A'; sopa_F[1][3] = 'N'; sopa_F[1][4] = 'A';
	sopa_F[0][2] = 'B'; sopa_F[1][2] = 'A'; sopa_F[2][2] = 'N'; sopa_F[3][2] = 'A'; sopa_F[4][2] = 'N'; sopa_F[5][2] = 'A';
	sopa_F[4][0] = 'M'; sopa_F[4][1] = 'A'; sopa_F[4][2] = 'N'; sopa_F[4][3] = 'Z'; sopa_F[4][4] = 'A'; sopa_F[4][5] = 'N'; sopa_F[4][6] = 'A';
	sopa_F[0][5] = 'P'; sopa_F[1][5] = 'E'; sopa_F[2][5] = 'R'; sopa_F[3][5] = 'A';
	sopa_F[1][7] = 'C'; sopa_F[2][7] = 'O'; sopa_F[3][7] = 'C'; sopa_F[4][7] = 'O';
	sopa_F[6][0] = 'K'; sopa_F[6][1] = 'I'; sopa_F[6][2] = 'W'; sopa_F[6][3] = 'I';
	sopa_F[7][3] = 'F'; sopa_F[7][4] = 'R'; sopa_F[7][5] = 'E'; sopa_F[7][6] = 'S'; sopa_F[7][7] = 'A';
}

void visualizarMatriz_F() {
	/* a partir del recorrido desde el inicio hasta el final de la matriz, se muestran los caracteres correspondientes */
	int i, j;
	
	for (i = 0; i < MAX_FILA_F; i++) {
		printf("\t");
		for (j = 0; j < MAX_COLUM_F; j++) {
			printf(" %c | ", sopa_F[i][j] );
		}
		printf("\n");
	}
}

/* declaraci�n de instrcucciones funciones de lista est�tica */

void inicializarLista_F() {
	/* el valor de la lista se inicializa en -1, porque el primer elemento a insertar lo har� en la posicion 0 */
	lista_F.indice = -1;
}

bool listaVacia_F(tLista_F pLista) {
	/* devuelve "true" si el valor de la lista es -1, es decir, si esta vacia. 
	Caso contrario, si tiene por lo menos 1 elemento, devuelve "false" */
	return pLista.indice == -1;
}

bool listaLlena_F(tLista_F pLista) {
	/* devuelve "true" si el valor de la lista es igual al limite maximo de palabras admitidas, en ese caso, 7 palabras. 
	   De lo contratio, devuelve "false" */
	return pLista.indice == MAX_PAL_F-1;	
}

void insertarElementos_F(tr_sopaLetras_F pSopa) {
	/* si la lista no esta llena, significa que tenemos espacio para seguir insertando datos. el indice avanza un valor 
	   y se realiza la insercion de lo que se recibe por parametro en la lista de palabras. 
	   de lo contrario, si la lista esta llena, se informara un aviso */
	if( !listaLlena_F(lista_F) ) {
		lista_F.indice +=1;
		lista_F.listaPalabras[lista_F.indice] = pSopa;
	} else {
		printf("\n\t\t *** No pueden agregar mas de %d palabras. La lista esta llena *** \n", MAX_PAL_F);
	}
}

void visualizarElementos_F(tLista_F pLista) {
	/* si la lista no esta vacia, significa que hay elementos para mostrar, lo hace a traves de un recorrido que muestra los elementos 
	   a medida que se desplaza por el vector, el recorrido inicia desde 0 hasta el elemento final (indice) */
	int i;
	
	if( !listaVacia_F(lista_F) ) {
		printf("\n Palabras en la lista \n\n");
		
		for(i=0; i <= pLista.indice; i++) {
			printf(" %s - ", pLista.listaPalabras[i].palabra);
		}
	} else {
		printf("\n\t\t *** No es posible listar los elementos. Lista vacia! *** \n");
	}
	printf("\n\n");
}

/* declaraci�n de instrucciones funciones de pila */

void crearPila_F() {
	/* el valor de la pila se inicializa en -1, porque el primer elemento a insertar lo hara en la posicion 0 */
	pila_F.tope = -1;
}

bool pilaVacia_F(tPila_F pPila) {
	/* devuelve "true" si el valor de la pila es -1, es decir, si esta vacia. 
	Caso contrario, si tiene por lo menos 1 elemento, devuelve "false" */
	return pPila.tope == -1;
}

bool pilaLlena_F(tPila_F pPila) {
	/* devuelve "true" si el valor de la pila es igual al limite maximo de palabras admitidas, en ese caso, 7 palabras. 
	   De lo contratio, devuelve "false" */
	return pPila.tope == MAX_PAL_F-1;
}

void apilarPalabra_F(tr_sopaLetras_F pPalYcat) {
	/* si la pila no esta llena, significa que tenemos espacio para seguir insertando datos. el tope incrementa un valor 
	   y se realiza la insercion de lo que se recibe por parametro en la pila de palabras. 
	   de lo contrario, si la pila esta llena, se informara un aviso */
	if( !pilaLlena_F(pila_F) ) {
		pila_F.tope+=1;
		pila_F.pilaPalabras[pila_F.tope] = pPalYcat;
	} else {
		printf("\n *** No es posible almacenar mas de %d elementos *** \n", MAX_PAL_F);
	}
}

void visualizarPila_F() {
	/* si la pila esta vacia, significa que no hay elementos por mostrar y se notificar� mediante un aviso, de lo contrario, 
	muestra los elementos a medida que se desplaza por el vector, el recorrido inicia desde 0 hasta el elemento final (tope) */
	int i;
	
	if( pilaVacia_F(pila_F) ) {
		printf("\n *** No se encontraron palabras! *** \n");
	} else {
		printf("\n\t *** FIN DEL JUEGO *** \n\n Palabras encontradas: \n");
		
		for(i=0; i <= pila_F.tope; i++) {
			printf(" %s - ", pila_F.pilaPalabras[i].palabra);
		}
	}
	/* al final del juego se muestran los resultados correspondientes a las palabras acertadas y los errores */
	cantPalabrasEncontradas_F();
}

/* declaracion de instrucciones funciones definidas por el programador */

void cantPalabrasEncontradas_F() {
	/* se muestran los resultados correspondientes */
	printf("\n\n Encontraste %d palabras correctas", palCorrectas);
	printf("\n Realizaste %d palabras incorrectas\n", palIncorrectas);
}

void condBuscarPalabra_F() {
	/* pregunta al usuario si ha encontrado una palabra */
	printf("\n Ha encontrado una palabra? (s/n): ");
	fflush(stdin);
	scanf("%c", &condComparaPal);
	
	/* invocacion a la funcion que realizara el proceso de busqueda y comparacion de la palabra */
	procesaBusqueda_F();
}

void procesaBusqueda_F() {
	/* mientras que el usuario haya encontrado palabras, es decir, ingresa la letra 's', registrar� esa palabra por teclado, 
	   se realiza la comparacion de la palabra ingresada por teclado con la palabra almacenada en la lista y la pila, una vez terminado este proceso,
	   se vuelve a preguntar al usuario si encontro alguna otra palabra, la condicion terminara su ejecucion cuando el usuario ingrese la letra 'n' */
	while(condComparaPal == 's' || condComparaPal == 'S') {
		ingresarPalabra_F();
		comparaPalabras_F(lista_F, pila_F);
		condBuscarPalabra_F();
	}
}

void ingresarPalabra_F() {
	/* ingresa por teclado la palabra que descubre el usuario */
	printf("\n Escriba la palabra: ");
	fflush(stdin);
	scanf("%s", &palabra);
}

bool estaEnPila_F(tPila_F pPila, tc_cadCar palabra) {
	/* si el valor del tope es el valor del inicio (-1) significa que la palabra no esta dentro de la pila, por lo tanto, devuelve 'false' 
	   si el valor es distinto del tope, se recorre la pila desde el inicio hasta el final (tope) comparando si la palabra que se ingreso por teclado 
	   coincide con alguna palabra ya almacenada en la pila, si esto es asi, devuelve 'true', de otra manera, devuelve 'false' */
	int i;
	
	if(pPila.tope == -1) {
		return false;
	} else {
		for(i=0; i <= pPila.tope; i++) {
			if(strcmp(pPila.pilaPalabras[i].palabra, palabra) == 0) {
				return true;
			}
		}
		return false;
	}
}

void comparaPalabras_F(tLista_F pLista, tPila_F pPila) {
	/* recorre la lista de palabras almacenadas desde el inicio hasta el final (indice) y compara la palabra que se ingreso 
	   por teclado con alguna de las palabras que se encuentra en la lista, si la misma coincide y
	   ademas se cumple que dicha palabra no se encuentra almacenada en la pila, la misma va a apilarse y cambia el valor de la variable bandera.
	   luego, si la bandera es valor 'true' significa que apilo la palabra y la misma se encuentra en la cuadricula, incrementa el contador de la palabra correcta
	   si, por el contrario, la bandera es valor 'false', significa que la palabra ya fue almacenada, o, que no se encuentra en la cuadricula e,  incrementa el contador de la palabra incorrecta */
	int i;
	bool flag = false;
	
	for(i=0; i <= pLista.indice && flag != true; i++) {
		if(strcmp(pLista.listaPalabras[i].palabra, palabra) == 0) {
			
			if( !estaEnPila_F(pPila, palabra) ) {
				apilarPalabra_F(pLista.listaPalabras[i]);
				flag = true;
			}
		}
	}
	
	if(flag == true) {
		printf(" La palabra se encuentra en la sopa! \n");
		palCorrectas += 1;
	} else {
		printf(" Ups! Esa palabra ya la encontraste, o no esta dentro de la sopa\n Intentalo de nuevo! \n");
		palIncorrectas += 1;
	}
}
