#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#define GRAN_CANTIDAD 100000
#define CONST1 1
#define CONST2 7
#define CONST3 15
#define CONST4 17
#define CONST5 2


/* ******************************************************************
*                   PRUEBAS UNITARIAS ALUMNO
* *****************************************************************/

/***************************************
 *          PRUEBAS DE LA LISTA
 * ************************************/

void pruebas_lista_vacia(lista_t* lista){
    printf("\n**PRUEBAS CON LISTA VACÍA**\n");
    lista_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL: ", ejemplo == NULL);

    print_test("Crear lista: ", lista != NULL);
    print_test("lista está vacía: ", lista_esta_vacia(lista));
    print_test("Lista_largo: ", lista_largo(lista) == 0);
    print_test("Borrar primero de lista vacía: ", lista_borrar_primero(lista) == NULL);
    print_test("Ver primer elemento de lista vacía: ", lista_ver_primero(lista) == NULL);

    int i = CONST1;
    print_test("Insertar primero lista vacía", lista_insertar_primero(lista, &i)); // [&i]
    print_test("Lista_largo: ", lista_largo(lista) == 1);
    int j = CONST2;
    print_test("Insertar primero lista vacía", lista_insertar_primero(lista, &j)); //[&j, &i]
    print_test("Lista_largo: ", lista_largo(lista) == 2);
    int k = CONST3;
    print_test("Insertar último lista vacía", lista_insertar_ultimo(lista, &k)); // [&j, &i, &k]
    print_test("Lista_largo: ", lista_largo(lista) == 3);
    print_test("Borrar primero: ", lista_borrar_primero(lista) == &j);
    print_test("Borrar primero: ", lista_borrar_primero(lista) == &i);
    print_test("Borrar primero: ", lista_borrar_primero(lista) == &k);

    lista_destruir(lista,NULL);
    print_test("Destruir lista con destruir_dato = NULL: ", true);
}

bool lista_esta_ordenada(void** vector, int n, lista_t* lista); // definida al final
void pruebas_lista_algunos_elementos(){
    printf("\n**PRUEBAS CON ALGUNOS ELEMENTOS**\n");

    lista_t* lista = lista_crear();
    print_test("Crear lista", lista != NULL);

    int i = CONST1;
    int j = CONST2;
    int k = CONST3;
    int l = CONST4;

    printf("Insertar primero %d en lista:", i);
    print_test("", lista_insertar_primero(lista, &i)); // [i]
    printf("%d primero en la lista:", i);
    print_test("", lista_ver_primero(lista) == &i);

    printf("Insertar primero %d en lista:", j);
    print_test("", lista_insertar_primero(lista, &j)); // [j, i]
    printf("%d primero en la lista:", j);
    print_test("", lista_ver_primero(lista) == &j);
    

    printf("Insertar_primero %d en lista:", k);
    print_test("", lista_insertar_primero(lista, &k)); // [k, j, i]
    printf("%d primero en la lista:", k);
    print_test("", lista_ver_primero(lista) == &k);

    printf("Insertar_primero %d en lista:", l);
    print_test("", lista_insertar_primero(lista, &l)); // [l, k, j, i]
    printf("%d primero en la lista:", l);
    print_test("", lista_ver_primero(lista) == &l);

    void* vector[4] = {&l, &k, &j, &i};

    bool lista_ordenada = lista_esta_ordenada( vector, 4, lista);
    print_test("lista ordenada: ", lista_ordenada);
    printf("*La lista se encuentra vacía*\n");

    void* n = NULL;
    print_test("insertar_primero NULL en lista: ", lista_insertar_primero(lista, n));
    print_test("NULL primero en la lista: ", lista_ver_primero(lista) == n);
    print_test("borrar_primero NULL", lista_borrar_primero(lista) == n);

    lista_destruir(lista, NULL);
    print_test("Destruir lista con destruir_dato = NULL: ", true);
}

bool vaciar_lista(lista_t* lista);
lista_t* chequear_capacidad(lista_t* lista);
bool grandes_cantidades_insertar_primero(lista_t* lista, void** vector);
bool grandes_cantidades_insertar_ultimo(lista_t* lista, void** vector);
void pruebas_lista_gran_cantidad_elementos(){
    printf("\n**PRUEBAS CON GRANDES CANTIDADES DE ELEMENTOS**\n");

    lista_t* lista = lista_crear();
    print_test("Crear lista", lista != NULL);
    
    void* vector[GRAN_CANTIDAD];
    // Guardo en cada posición de memoria un puntero que apunta a su respectiva posición de memoria
    for (int i = 0; i < GRAN_CANTIDAD; i++){

        vector[i] = &vector[i]; 
    }

    // insertar_ultimo y luego borrar_primero para chequear orden
    // que debe ser igual al orden del vector
    bool insertado = grandes_cantidades_insertar_ultimo(lista,vector);
    printf("insertado de %d elementos:",GRAN_CANTIDAD);
    print_test("",insertado);
    bool lista_ordenada2 = lista_esta_ordenada(vector, GRAN_CANTIDAD, lista);
    print_test("lista ordenada: ", lista_ordenada2);
    printf("*La lista se encuentra vacía*\n");

    //insertar_primero y luego borrar_primero para chequear orden
    // que debe ser inverso al orden del vector
    insertado = grandes_cantidades_insertar_primero(lista,vector);
    printf("insertado de %d elementos:",GRAN_CANTIDAD);
    print_test("",insertado);
    
    for (int i = 0; i < GRAN_CANTIDAD && insertado; i++){ //invierto el vector

        vector[i] = &vector[GRAN_CANTIDAD-i-1]; 
    }

    bool lista_ordenada3 = lista_esta_ordenada(vector, GRAN_CANTIDAD, lista);
    print_test("lista ordenada: ", lista_ordenada3);
    printf("*La lista se encuentra vacía*\n");
    

    // Comprueba que una lista con elementos insertados y luego con dichos elementos borrados hasta vaciarse se comporte como lista vacía
    printf("\nSE COMPRUEBA QUE LISTA CON ELEMENTOS INSERTADOS QUE SON LUEGO \nELIMINADOS HASTA VACIARSE SE COMPORTA COMO LISTA VACÍA:");
    pruebas_lista_vacia(lista);
}
void pila_destruir_wrapper (void* pila);
void pruebas_lista_diferentes_estructuras(){
    printf("\n**PRUEBAS ENLISTANDO ESTRUCTURAS PARTICULARES**\n");

    lista_t* lista = lista_crear();
    print_test("Crear lista", lista != NULL);
    
    pila_t* pila1 = pila_crear();
    pila_t* pila2 = pila_crear();
    pila_t* pila3 = pila_crear();
    pila_t* pila4 = pila_crear();

    print_test("insertar_primero pila1 en lista: ", lista_insertar_primero(lista, pila1));
    print_test("insertar_primero pila2 en lista: ", lista_insertar_primero(lista, pila2));
    print_test("insertar_primero pila3 en lista: ", lista_insertar_primero(lista, pila3));
    print_test("insertar_primero pila4 en lista: ", lista_insertar_primero(lista, pila4));

    lista_destruir(lista, pila_destruir_wrapper);
    print_test("lista_destruir con destruir_dato != NULL: ", true);
}

/***************************************
 *          PRUEBAS ITERADOR EXTERNO
 * ************************************/

void pruebas_iterador_externo_unico(){
    printf("\n**PRUEBAS CON INTERADORES EXTERNOS**\n");
    lista_t* lista = lista_crear();
    print_test("Crear lista", lista != NULL);

    lista_iter_t* iterador = lista_iter_crear(lista);
    print_test("Crear iterador", iterador != NULL);

    print_test("Avanzar con una lista vacía", !lista_iter_avanzar(iterador));
    print_test("Ver actual de lista vacía", lista_iter_ver_actual(iterador) == NULL);
    //si la lista está vacía, se define que el iterador está al final y al principio al mismo tiempo
    // por lo tanto lista_iter_al_final devuelve true
    print_test("El iterador llegó al final de la lista", lista_iter_al_final(iterador));
    int valor = CONST1;
    print_test("Insertar un elemento en la lista por medio de iteradores externos", lista_iter_insertar(iterador,&valor));
    print_test("Lista_largo = 1: ", lista_largo(lista) == 1);
    print_test("lista->primero = valor: ", lista_ver_primero(lista) == &valor);
    print_test("lista->ultimo = valor: ", lista_ver_ultimo(lista) == &valor);
    print_test("Eliminar el elemento de la lista por medio de iteradores externos", lista_iter_borrar(iterador) == &valor);
    print_test("Lista_largo = 0: ", lista_largo(lista) == 0);
    print_test("lista->primero = NULL: ", lista_ver_primero(lista) == NULL);
    print_test("lista->ultimo = NULL: ", lista_ver_ultimo(lista) == NULL);
    
    int i = CONST1;
    int j = CONST2;
    int k = CONST3;
    int l = CONST4;

    print_test("Insertar un elemento en la lista por medio de iteradores externos", lista_iter_insertar(iterador,&i)); // [i]
    printf("Actual = %d\n",i);
    print_test("Ver actual", lista_iter_ver_actual(iterador) == &i);
    print_test("Lista_largo = 1: ", lista_largo(lista) == 1);
    print_test("lista->primero = valor1: ", lista_ver_primero(lista) == &i);
    print_test("lista->ultimo = valor1", lista_ver_ultimo(lista) == &i);

    print_test("Insertar un elemento en la lista por medio de iteradores externos", lista_iter_insertar(iterador,&j)); // [j, i]
    printf("Actual = %d\n",j);
    print_test("Ver actual", lista_iter_ver_actual(iterador) == &j);
    print_test("Lista_largo = 2: ", lista_largo(lista) == 2);
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &j);
    print_test("lista->ultimo = valor1", lista_ver_ultimo(lista) == &i);

    print_test("Avanzar un lugar", lista_iter_avanzar(iterador));
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &j);
    print_test("lista->ultimo = valor1", lista_ver_ultimo(lista) == &i);

    printf("Actual = %d\n",i);
    print_test("Ver actual", lista_iter_ver_actual(iterador) == &i);

    print_test("Avanzar un lugar", lista_iter_avanzar(iterador));
    print_test("El iterador llegó al final de la lista", lista_iter_al_final(iterador));
    print_test("Ver actual", lista_iter_ver_actual(iterador) == NULL);
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &j);
    print_test("lista->ultimo = valor1", lista_ver_ultimo(lista) == &i);

    print_test("Insertar un elemento en la lista por medio de iteradores externos", lista_iter_insertar(iterador,&k)); // [j, i, k]
    printf("Actual = %d\n",k);
    print_test("Ver actual", lista_iter_ver_actual(iterador) == &k);
    print_test("Lista_largo = 3: ", lista_largo(lista) == 3);
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &j);
    print_test("lista->ultimo = valor3", lista_ver_ultimo(lista) == &k);

    print_test("Borrar elemento",lista_iter_borrar(iterador) == &k); // [j,i]
    print_test("Lista_largo = 2: ", lista_largo(lista) == 2);
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &j);
    print_test("lista->ultimo = valor3", lista_ver_ultimo(lista) == &i);
    printf("Actual = %d\n",l);
    print_test("Ver actual", lista_iter_ver_actual(iterador) == NULL);
    print_test("Insertar un elemento en la lista por medio de iteradores externos", lista_iter_insertar(iterador,&l)); // [j, i, l]
    printf("Actual = %d\n",l);
    print_test("Lista_largo = 3: ", lista_largo(lista) == 3);
    print_test("Ver actual", lista_iter_ver_actual(iterador) == &l);
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &j);
    print_test("lista->ultimo = valor4", lista_ver_ultimo(lista) == &l);

    print_test("Avanzar un lugar", lista_iter_avanzar(iterador));
    print_test("El iterador llegó al final de la lista", lista_iter_al_final(iterador));
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &j);
    print_test("lista->ultimo = valor4", lista_ver_ultimo(lista) == &l);

    lista_iter_destruir(iterador);
    print_test("Destruir iterador",true);
    lista_destruir(lista, NULL);
    print_test("Destruir lista",true);
}

void pruebas_iterador_externo_varios(){
    printf("\n**VARIOS ITERADORES SOBRE MISMA LISTA**\n");
    lista_t* lista = lista_crear();
    print_test("Crear lista", lista != NULL);

    lista_iter_t* iterador1 = lista_iter_crear(lista);
    print_test("Crear iterador", iterador1 != NULL);

    int i = CONST1;
    int j = CONST2;
    int k = CONST3;
    int l = CONST4;

    print_test("Ver actual ITERADOR 1", lista_iter_ver_actual(iterador1) == NULL);

    print_test("Insertar un elemento en la lista por medio de iteradores externos", lista_iter_insertar(iterador1,&l));  // [l]
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &l);
    print_test("lista->ultimo = valor4", lista_ver_ultimo(lista) == &l);
    print_test("Ver actual ITERADOR 1", lista_iter_ver_actual(iterador1) == &l);

    print_test("Insertar un elemento en la lista por medio de iteradores externos", lista_iter_insertar(iterador1,&k)); // [k, l]
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &k);
    print_test("lista->ultimo = valor4", lista_ver_ultimo(lista) == &l);
    print_test("Ver actual ITERADOR 1", lista_iter_ver_actual(iterador1) == &k);

    print_test("Insertar un elemento en la lista por medio de iteradores externos", lista_iter_insertar(iterador1,&j)); // [j, k, l]
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &j);
    print_test("lista->ultimo = valor4", lista_ver_ultimo(lista) == &l); 
    print_test("Ver actual ITERADOR 1", lista_iter_ver_actual(iterador1) == &j);

    print_test("Insertar un elemento en la lista por medio de iteradores externos", lista_iter_insertar(iterador1,&i)); // [i, j, k, l]
    print_test("lista->primero = valor2: ", lista_ver_primero(lista) == &i);
    print_test("lista->ultimo = valor4", lista_ver_ultimo(lista) == &l);
    print_test("Ver actual ITERADOR 1", lista_iter_ver_actual(iterador1) == &i);

    lista_iter_t* iterador2 = lista_iter_crear(lista);
    print_test("\nCrear iterador 2", iterador2 != NULL);

    print_test("Ver actual ITERADOR 2", lista_iter_ver_actual(iterador2) == &i);

    print_test("Avanzar ITERADOR1", lista_iter_avanzar(iterador1));
    print_test("Avanzar ITERADOR1", lista_iter_avanzar(iterador1));
    print_test("Ver actual ITERADOR 2", lista_iter_ver_actual(iterador2) == &i);
    print_test("Ver actual ITERADOR 1", lista_iter_ver_actual(iterador1) == &k);

    print_test("Avanzar ITERADOR2", lista_iter_avanzar(iterador2));
    print_test("Ver actual ITERADOR 2", lista_iter_ver_actual(iterador2) == &j);

    print_test("Si avanzo el ITERADOR 1, llego al último elemento de la lista", lista_iter_avanzar(iterador1) && lista_iter_ver_actual(iterador1) == lista_ver_ultimo(lista));
    print_test("Avanzar ITERADOR1", lista_iter_avanzar(iterador1));
    print_test("El ITERADOR 1 llegó al final de la lista", lista_iter_al_final(iterador1));
    print_test("Avanzar con el ITERADOR 1 devuelve false", !lista_iter_avanzar(iterador1));
    print_test("Ver actual ITERADOR 2", lista_iter_ver_actual(iterador2) == &j);
    


    lista_iter_destruir(iterador1);
    lista_iter_destruir(iterador2);
    print_test("Destruir iteradores",true);
    lista_destruir(lista, NULL);
    print_test("Destruir lista",true);
}

/***************************************
 *          PRUEBAS ITERADOR INTERNO
 * ************************************/

bool multiplicar_por_factor(void*dato, void* extra); //definido al final
bool sumar_datos(void*dato, void* suma_acumulada); // definido al final
bool dato_hacer_cero(void* dato, void* corte); // definido al final
void pruebas_iterador_interno(){
    printf("\n**PRUEBAS CON INTERADORES INTERNOS**\n");
    lista_t* lista = lista_crear();
    print_test("Crear lista", lista != NULL);

    int i = CONST1;
    int j = CONST2;
    int k = CONST3;
    int l = CONST4;

    // Duplicados de los valores originales,
    // que se mantendrán constantes para poder comparar luego:
    int const_i = CONST1;
    int const_j = CONST2;
    int const_k = CONST3;
    int const_l = CONST4;

    lista_insertar_primero(lista,&i);
    lista_insertar_primero(lista,&j);
    lista_insertar_primero(lista,&k);
    lista_insertar_primero(lista,&l); // [l, k, j, i]

    
    int factor = 5;
    printf("\nLista_iterar(lista,multiplicar_por_factor,factor):\n");
    lista_iterar(lista,multiplicar_por_factor,&factor);
    lista_iter_t* iterador = lista_iter_crear(lista);
    print_test("multiplicar 1er elemento de lista por factor: ", * (int*) lista_iter_ver_actual(iterador) == const_l * factor);
    lista_iter_avanzar(iterador);
    print_test("multiplicar 2do elemento de lista por factor: ", * (int*) lista_iter_ver_actual(iterador) == const_k * factor);
    lista_iter_avanzar(iterador);
    print_test("multiplicar 3er elemento de lista por factor: ", * (int*) lista_iter_ver_actual(iterador) == const_j * factor);
    lista_iter_avanzar(iterador);
    print_test("multiplicar 4to elemento de lista por factor: ", * (int*) lista_iter_ver_actual(iterador) == const_i * factor);

    lista_iter_destruir(iterador);

    int suma = 0;
    printf("\nLista_iterar(lista,sumar_datos,factor):\n");
    lista_iterar(lista,sumar_datos,&suma);
    printf("La suma de %d, %d, %d y %d es %d", i, j, k, l, suma);
    print_test("",suma == i+j+k+l);

    int n = CONST5;
    printf("\nLista_iterar(lista,dato_hacer_cero,nuevo):\n");
    lista_iterar(lista,dato_hacer_cero,&n);

    lista_iter_t* iterador2 = lista_iter_crear(lista);

    int contador;
    printf("Prueba: los primeros %d elementos son CERO:\n", CONST5);
    for (contador = 1; contador <= CONST5; contador++){
        printf("El elemento %d es CERO:", contador);
        print_test("", *(int*) lista_iter_ver_actual(iterador2) == 0);
        lista_iter_avanzar(iterador2);
    }

    printf("El resto de los %lu elementos no son CERO:\n", lista_largo(lista) - (size_t) contador +1);
    while (!lista_iter_al_final(iterador2)){
        printf("Elemento %d != NULL:",contador);
        print_test("", *(int*)lista_iter_ver_actual(iterador2) != 0);
        lista_iter_avanzar(iterador2);
        contador++;        
    }
    
    lista_iter_destruir(iterador2);
    lista_destruir(lista, NULL);
}

bool grandes_cantidades_insertar_primero(lista_t* lista, void** vector){
    bool insertado = true;
    
    // Encolo las direcciones de las posiciones de memoria del vector en la lista
    for (int i = 0; i < GRAN_CANTIDAD && insertado; i++){
        
        insertado = lista_insertar_primero(lista, &vector[i]);
    }
    return insertado;
}

bool grandes_cantidades_insertar_ultimo(lista_t* lista, void** vector){
    bool insertado = true;
    
    // Encolo las direcciones de las posiciones de memoria del vector en la lista
    for (int i = 0; i < GRAN_CANTIDAD && insertado; i++){
        
        insertado = lista_insertar_ultimo(lista, &vector[i]);
    }
    return insertado;
}

bool vaciar_lista(lista_t* lista){ //vacía la lista chequeando que el primero sea igual al elemento que se desenlista posteriormente  
    void* primero;
    void* borrado;
    bool son_diferentes = false;

    while (!(lista_esta_vacia(lista)) && !(son_diferentes)){
        
        primero = lista_ver_primero(lista);
        borrado = lista_borrar_primero(lista);
        son_diferentes = (primero != borrado);
    }
    return !(son_diferentes);
}

bool lista_esta_ordenada(void** vector, int n, lista_t* lista){ // verifica que la lista mantenga el orden de inserción
    int i = 0;
    bool ordenada = true;

    while (i < n && ordenada){
        void* elemento_correspondiente = vector[i];
        void* borrado = lista_borrar_primero(lista);
        ordenada = (elemento_correspondiente == borrado);
        i++;
    }
    return ordenada;
}

void pila_destruir_wrapper (void* pila){
    pila_destruir((pila_t*) pila);
}


// multiplica cada dato de la lista por el factor
bool multiplicar_por_factor(void*dato, void* factor){
    * (int*) dato *= *(int*) factor;
    return true;
}

bool sumar_datos(void*dato, void* suma_acumulada){

    *(int*) suma_acumulada += * (int*) dato;
    return true;
}

bool dato_hacer_cero(void* dato, void* corte){

    if (*(int*) corte == 0){
        return false;
    }
    *(int*) dato = 0;
    * (int*) corte -= 1;
    return true;    
}

void pruebas_lista_alumno(){
    lista_t* lista = lista_crear();

    pruebas_lista_vacia(lista);
    pruebas_lista_algunos_elementos();
    pruebas_lista_gran_cantidad_elementos();
    pruebas_lista_diferentes_estructuras();
    pruebas_iterador_externo_unico();
    pruebas_iterador_externo_varios();
    pruebas_iterador_interno();
    return;
}
