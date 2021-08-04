#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include "test_de_personalidad.h"
#include "utiles.h"
#include "osos_contra_reloj.h"

#define MAX_OBSTACULOS 600
#define MAX_HERRAMIENTAS 600

#define MAX_COLUMNAS_ 50
#define MAX_FILAS_ 50

const int DISTANCIA_MANHATAN = 3;

const double TIEMPO_PIEDRA = 2;
const double TIEMPO_ARBOL = 1;
const double TIEMPO_PIEDRA_POLAR = 0;
const double TIEMPO_ARBOL_PARDO = 0.5;
const double TIEPO_GPS_PANDA = 30;

const char PANDA = 'P';
#define EMOJI_PANDA "\U0001f43c"
const char PARDO = 'G';
#define EMOJI_PARDO "\U0001f43b"
const char POLAR = 'I';
#define EMOJI_POLAR "\u26C4"


const char VACIO = '_';
#define EMOJI_VACIO "\u2B1B"


const char ARRIBA = 'W';
const char ABAJO = 'S';
static const char DERECHA = 'D';
const char IZQUIERDA = 'A';

const int TIEMPO = 'T';

const int SUMAR_UNO = 1;
const int RESTAR_UNO = -1;
const int QUEDARSE_QUIETO = 0;

const char MINUS_A_MAJUS = ('A'-'a');
const char MAJUS_A_MINUS = (-'A'+'a');

const int MAX_COLUMNAS = 30;
const int MAX_FILAS = 20;

const char ARBOL = 'A';
#define EMOJI_ARBOL "\U0001f332"
const char PIEDRA = 'R';
#define EMOJI_PIEDRA "\U0001f94c"
const char KOALA = 'K';
#define EMOJI_KOALA "\U0001f428"

const int CANT_ARBOLES = 350;
const int CANT_PIEDRAS = 80;

const char LINTERNA = 'L';
#define EMOJI_LINTERNA "\U0001f526"
const char VELA = 'V';
#define EMOJI_VELA "\U0001f9e8"
const char BENGALA = 'E';
#define EMOJI_BENGALA "\U0001f387"
const char PILA = 'B';
#define EMOJI_PILA "\U0001f50b"


const int CANT_LINTERNAS_INI = 1;
const int CANT_VELAS_INI = 4;
const int CANT_BENGALAS_INI = 0;

const int CANT_VELAS_POLAR = 6;
const int CANT_BENGALAS_PANDA = 2;

const int DURACION_LINTERNA = 10;
const int DURACION_LINTERNA_PARDO = 15;
const int DURACION_PILA = 5;
const int DURACION_VELAS = 5;
const int DURACION_BENGALAS = 3;

const int CANT_PILAS_MAPA = 30; 
const int CANT_VELAS_MAPA = 30;
const int CANT_BENGALAS_MAPA = 10;

const char CHLOE = 'C';
#define EMOJI_CHLOE "\U0001f467"

const int COLUMNAS = 20;
const int FILAS = 30;

/*
 *PRE: Rango dado
 *POST: Genera un numero random dentro de un rango 
 */
int generar_random (int rango){

    int numero_random = rand () % (rango);

    return numero_random;
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE:
 *POST: Agrega un elemento a la mochila (tipo, coordenada y movimientos restantes) y suma 1 a la cantidad de elementos
 */
void agregar_elementos_mochila (personaje_t* personaje, char tipo_elemento, int movimientos_restantes,int cantidad){
    
    for (int i = 0; i < cantidad; i++){

        personaje->mochila[personaje->cantidad_elementos].tipo = tipo_elemento;

        personaje->mochila[personaje->cantidad_elementos].movimientos_restantes = movimientos_restantes;
        personaje->cantidad_elementos ++;
    }
}

/*
 *PRE:
 *POST: Identifica el personaje y agrega los elementos de la mochila (PARDO, PANDA Y POLAR)
 */
void generador_elementos_mochila (juego_t* juego, char personalidad_detectada){

    juego->personaje.cantidad_elementos = 0;
    
    if (personalidad_detectada == PARDO){
    agregar_elementos_mochila(&(juego->personaje), LINTERNA, DURACION_LINTERNA_PARDO, CANT_LINTERNAS_INI);
    }
    else {
        agregar_elementos_mochila(&(juego->personaje), LINTERNA, DURACION_LINTERNA, CANT_LINTERNAS_INI);
    }
    if (personalidad_detectada == POLAR){
        agregar_elementos_mochila(&(juego->personaje), VELA, DURACION_VELAS, CANT_VELAS_POLAR);
    }
    else{
        agregar_elementos_mochila(&(juego->personaje), VELA, DURACION_VELAS, CANT_VELAS_INI);
    }
    if (personalidad_detectada == PANDA){
        agregar_elementos_mochila(&(juego->personaje), BENGALA, DURACION_BENGALAS, CANT_BENGALAS_PANDA);
    }
    else {
        agregar_elementos_mochila(&(juego->personaje), BENGALA, DURACION_BENGALAS, CANT_BENGALAS_INI); 
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            
/*
 *PRE: Coordenadas de elemento a comparar
 *POST: Devuelve    ->true si las coordenadas del elemento y las del elemento a comparar coinciden
 *                  ->false caso contrario
 */        
bool coincide_con_elemento (elemento_del_mapa_t elementos[MAX_OBSTACULOS], elemento_del_mapa_t elementos_a_comparar[MAX_OBSTACULOS], int cantidad_elementos, int j){

    return (elementos[cantidad_elementos].posicion.fil == elementos_a_comparar[j].posicion.fil && elementos[cantidad_elementos].posicion.col == elementos_a_comparar[j].posicion.col);
}

/*
 *PRE: Coordenadas de personaje y del elemento
 *POST: Devuelve    ->true si las coordenadas del elemento y personaje coiniden
 *                  ->false caso contrario
 */
bool coincide_con_personaje (juego_t juego, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int cantidad_elementos){

    return (elementos[cantidad_elementos].posicion.fil == juego.personaje.posicion.fil && elementos[cantidad_elementos].posicion.col == juego.personaje.posicion.col);
}

/*
 *PRE: Coordenadas de chloe y del elemento
 *POST: Devuelve    ->true si las coordenadas del elemento y chloe coiniden
 *                  ->false caso contrario
 */
bool coincide_con_chloe (juego_t juego,  elemento_del_mapa_t elementos[MAX_OBSTACULOS],  int cantidad_elementos){

    return (elementos[cantidad_elementos].posicion.fil == juego.amiga_chloe.fil && elementos[cantidad_elementos].posicion.col == juego.amiga_chloe.col);
}

/*
 *PRE: Coordenadas de todos los elementos del mapa
 *POST: Compara las coordenadas de un elemento con todos los otros. Si es que hay alguna concidencia encontro superposicion cambia a true y deja de comparar
 */
void chequear_elementos_mapa (elemento_del_mapa_t elementos[MAX_OBSTACULOS], elemento_del_mapa_t elementos_a_comparar[MAX_OBSTACULOS], int cantidad_elementos, int cantidad_elementos_a_comparar, bool *encontro_superposicion){

    int j = 0;

    while (j < cantidad_elementos_a_comparar && !(*encontro_superposicion)){
        if (coincide_con_elemento(elementos, elementos_a_comparar, cantidad_elementos, j)){ 
            
            *encontro_superposicion = true;
        }
        j++;
    }
}

/*
 *PRE:
 *POST: Chequea si es que el elemento coincide con el personaje, chloe y algun otro elemento. Si es asi vuelve a generar unas nuevas coordenadas y vuelve a chequear
 */
void chequear_superposicion (juego_t juego, elemento_del_mapa_t elementos[MAX_OBSTACULOS], elemento_del_mapa_t elementos_a_comparar[MAX_OBSTACULOS], int cantidad_elementos, int cantidad_elementos_a_comparar){
    bool encontro_superposicion = true;

    while (coincide_con_personaje (juego, elementos, cantidad_elementos) || coincide_con_chloe(juego, elementos, cantidad_elementos) || encontro_superposicion){

        encontro_superposicion = false;

        chequear_elementos_mapa(elementos, elementos, cantidad_elementos, cantidad_elementos, &encontro_superposicion);
        chequear_elementos_mapa(elementos, elementos_a_comparar, cantidad_elementos, cantidad_elementos_a_comparar, &encontro_superposicion);

        if (encontro_superposicion || coincide_con_personaje (juego, elementos, cantidad_elementos) || coincide_con_chloe(juego, elementos, cantidad_elementos)){

            elementos[cantidad_elementos].posicion.fil = generar_random(MAX_FILAS);
            elementos[cantidad_elementos].posicion.col = generar_random(MAX_COLUMNAS);
        }
    }
}

/*
 *PRE:
 *POST: Genera todos los elementos del mapa (tipo , los hace ivisibles, coordenadas) y aumenta la cantidad de elementos a medida que se van generando
 */
void generador_elementos_mapa ( juego_t juego, elemento_del_mapa_t elementos[MAX_OBSTACULOS], elemento_del_mapa_t elementos_a_comparar[MAX_OBSTACULOS], char tipo, int cantidad, int* cantidad_elementos, int cantidad_elementos_a_comparar){ 

    for (int i = 0; i < cantidad; i++){

        elementos[*cantidad_elementos].tipo = tipo;
        elementos[*cantidad_elementos].visible = false;
        elementos[*cantidad_elementos].posicion.fil = generar_random(MAX_FILAS);
        elementos[*cantidad_elementos].posicion.col = generar_random(MAX_COLUMNAS);

        chequear_superposicion (juego, elementos, elementos_a_comparar, *cantidad_elementos, cantidad_elementos_a_comparar);
        *cantidad_elementos += 1;
        

    }
    
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE:
 *POST: Coloca un koala ( coordenadas, lo hace invisible, el tipo ) y aumenta 1 a la cantidad de obstaculos
 */
void generador_koala (juego_t* juego){

        juego->obstaculos[juego->cantidad_obstaculos].tipo = KOALA;
        juego->obstaculos[juego->cantidad_obstaculos].visible = false;
        juego->obstaculos[juego->cantidad_obstaculos].posicion.fil = generar_random(MAX_FILAS);
        juego->obstaculos[juego->cantidad_obstaculos].posicion.col = generar_random(MAX_COLUMNAS);

        chequear_superposicion (*juego, juego->obstaculos, juego->herramientas,juego->cantidad_obstaculos, juego->cantidad_herramientas);

        juego->cantidad_obstaculos +=1;

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: Tipo de personaje identificado
 *POST: Inicializa las coordenadas del personaje, lo hace invisible , inicializa el elemento en uso, inicializa el ultimo movimiento y asigna el tipo de personaje
 */
void generar_personaje (personaje_t* personaje, char tipo_personaje){

    personaje->posicion.fil = generar_random(20);
    personaje->posicion.col = 0;
    personaje->ultimo_movimiento = DERECHA;
    personaje->elemento_en_uso = -1;
    personaje->tipo = tipo_personaje;
}

/*
 *PRE: Coordenadas del personaje
 *POST: Devuelve -> true si las coordenadas de chloe coinciden con las del personaje
 *               -> caso contrario
 */
bool chloe_coincide_personaje (juego_t juego){
    return (juego.amiga_chloe.fil == juego.personaje.posicion.fil && juego.amiga_chloe.col == juego.personaje.posicion.col);
}

/*
 *PRE: 
 *POST: Inicializa las coordenadas de chloe mientras no coincida con la del personaje y la hace invisible mientras 
 */
void generar_chloe (juego_t* juego){

    juego->amiga_chloe.fil = generar_random (MAX_FILAS);
    juego->amiga_chloe.col = generar_random (MAX_COLUMNAS);
    juego->chloe_visible = false;

    while (chloe_coincide_personaje(*juego)){
        juego->amiga_chloe.fil = generar_random (MAX_FILAS);
        juego->amiga_chloe.col = generar_random (MAX_COLUMNAS);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: Tipo de personaje identificado
 *POST: Inicializa el juego
 */
void inicializar_juego (juego_t* juego, char tipo_personaje){ //fijarse el tema del tope 

    juego->cantidad_obstaculos = 0;
    juego->cantidad_herramientas = 0;

    generar_personaje(&(juego->personaje), tipo_personaje);
    generar_chloe(juego);

    generador_elementos_mapa(*juego, juego->obstaculos, juego->herramientas,ARBOL,CANT_ARBOLES, &(juego->cantidad_obstaculos), juego->cantidad_herramientas);
    generador_elementos_mapa(*juego, juego->obstaculos, juego->herramientas,PIEDRA,CANT_PIEDRAS, &(juego->cantidad_obstaculos), juego->cantidad_herramientas);

    generador_elementos_mapa(*juego, juego->herramientas, juego->obstaculos,PILA, CANT_PILAS_MAPA, &(juego->cantidad_herramientas), juego->cantidad_obstaculos);
    generador_elementos_mapa(*juego, juego->herramientas, juego->obstaculos,VELA, CANT_VELAS_MAPA, &(juego->cantidad_herramientas), juego->cantidad_obstaculos);
    generador_elementos_mapa(*juego, juego->herramientas, juego->obstaculos,BENGALA, CANT_BENGALAS_MAPA, &(juego->cantidad_herramientas), juego->cantidad_obstaculos);

    generador_koala (juego);

    generador_elementos_mochila(juego, tipo_personaje);


}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: 
 *POST: Todos los elementos del bosque se vuelven invisibles
 */
void apagar_luces (elemento_del_mapa_t elementos[MAX_OBSTACULOS], int tope_elementos_mapa){

    for (int i = 0; i < tope_elementos_mapa; i++){

        elementos[i].visible = false;
    }
}

/*
 *PRE:
 *POST: Si el personaje es panda y su tiempo perdido es mayor a 30 chloe se vuelve visible
 *      En el caso contrario chloe es invisible
 */
void chloe_invisible (juego_t* juego){
    if (juego->personaje.tiempo_perdido >= 30 && juego->personaje.tipo == PANDA){

        juego->chloe_visible = true;
    }
    else{

        juego->chloe_visible = false;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: 
 *POST: Devuelve    ->true si la posicion del personaje si es que se realiza queda dentro del rango de las columnas del bosque
 *                  ->false caso contrario
 */
bool columna_dentro_rango (int mov_col, coordenada_t posicion){
    return(posicion.col + mov_col < MAX_COLUMNAS && posicion.col + mov_col >= 0);
}

/*
 *PRE: 
 *POST: Devuelve    ->true si la posicion del personaje si es que se realiza queda dentro del rango de las filas del bosque
 *                  ->false caso contrario
 */
bool fila_dentro_rango (int mov_fil, coordenada_t posicion){
    return(posicion.fil + mov_fil < MAX_FILAS && posicion.fil + mov_fil >= 0);
}

/*
 *PRE: Movimiento detectado y coordenadas del personaje
 *POST: Si es posible el personaje se mueve
 */
void deteccion_moviemiento (int mov_fil, int mov_col, personaje_t* personaje){ 
    if (columna_dentro_rango(mov_col, personaje->posicion)){

        personaje->posicion.col += mov_col;
    }
    if (fila_dentro_rango (mov_fil, personaje->posicion)){

        personaje->posicion.fil += mov_fil;
    }    
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: Elemento gastadoo
 *POST: Muestra por pantalla un mensaje
 */
void mostrar_elemento_gastado(char herramienta){
    printf("Se gasto la herramienta en uso herramienta (%c)\n", herramienta);
}
/*
 *PRE: Elemento en uso distinto de -1
 *POST: Si la herramienta tiene mas de 1 movimiento restante se le resta un movimiento
 *      Si la herramienta en uso es LINTERNA y tiene 1 solo movimiento-> se le resta el movimiento
 *      Si no es asi se elimina de la mochila
 */
void gastar_elemento_mochila (personaje_t* personaje){ 

    if (personaje->mochila[personaje->elemento_en_uso].movimientos_restantes > 1 ){

        personaje->mochila[personaje->elemento_en_uso].movimientos_restantes -- ;

    }
    else if (personaje->mochila[personaje->elemento_en_uso].tipo == LINTERNA && personaje->mochila[personaje->elemento_en_uso].movimientos_restantes == 1){

        personaje->mochila[personaje->elemento_en_uso].movimientos_restantes --;
        personaje->elemento_en_uso = -1;
    }
    else {

        mostrar_elemento_gastado(personaje->mochila[personaje->elemento_en_uso].tipo);
        for (int i = personaje->elemento_en_uso; i < personaje->cantidad_elementos; i++){
            personaje->mochila[i].tipo = personaje->mochila[i + 1].tipo;
            personaje->mochila[i].movimientos_restantes = personaje->mochila[i+1].movimientos_restantes;
        }
        personaje->cantidad_elementos -= 1;
        personaje->elemento_en_uso = -1;
    }
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: 
 *POST: Ilumina todos los elementos que estes arriba del personaje y a chloe si es que lo esta
 */
void iluminar_arriba (juego_t* juego, personaje_t* personaje, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int*  cantidad_elementos){
    for (int i = 0; i < *cantidad_elementos; i++){
        if (elementos[i].posicion.col == personaje->posicion.col && elementos[i].posicion.fil < personaje->posicion.fil){

            elementos[i].visible = true;
        }
    }
    if (juego->amiga_chloe.col == personaje->posicion.col && juego->amiga_chloe.fil < personaje->posicion.fil){

        juego->chloe_visible = true;
    }
}
/*
 *PRE: 
 *POST: Ilumina todos los elementos que estes abajo del personaje y a chloe si es que lo esta
 */
void iluminar_abajo (juego_t* juego, personaje_t* personaje, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int*  cantidad_elementos){
    for (int i = 0; i < *cantidad_elementos; i++){
        if (elementos[i].posicion.col == personaje->posicion.col && elementos[i].posicion.fil > personaje->posicion.fil){

            elementos[i].visible = true;
        }
    }
    if (juego->amiga_chloe.col == personaje->posicion.col && juego->amiga_chloe.fil > personaje->posicion.fil){

        juego->chloe_visible = true;
    }
}
/*
 *PRE: 
 *POST: Ilumina todos los elementos que estes a la izquierda del personaje y a chloe si es que lo esta
 */
void iluminar_izquierda (juego_t* juego, personaje_t* personaje, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int*  cantidad_elementos){
    for (int i = 0; i < *cantidad_elementos; i++){
        if (elementos[i].posicion.fil == personaje->posicion.fil && elementos[i].posicion.col < personaje->posicion.col){

            elementos[i].visible = true;
        }
    }
    if (juego->amiga_chloe.fil == personaje->posicion.fil && juego->amiga_chloe.col < personaje->posicion.col){

        juego->chloe_visible = true;
    }
}
/*
 *PRE: 
 *POST: Ilumina todos los elementos que estes a la derecha del personaje y a chloe si es que lo esta
 */
void iluminar_derecha (juego_t* juego, personaje_t* personaje, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int*  cantidad_elementos){
    for (int i = 0; i < *cantidad_elementos; i++){
        if (elementos[i].posicion.fil == personaje->posicion.fil && elementos[i].posicion.col > personaje->posicion.col){

            elementos[i].visible = true;
        }
    }
    if (juego->amiga_chloe.fil == personaje->posicion.fil && juego->amiga_chloe.col > personaje->posicion.col){

        juego->chloe_visible = true;
    }
}
/*
 *PRE: Coordenadas del personaje
 *POST: Identifica si el ultimo movimiento es:
 *          -> ARRIBA 
 *          -> DERECHA
 *          -> ABAJO
 *          -> IZQUIERDA
 */
void activar_linterna ( juego_t* juego ,personaje_t* personaje, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int* cantidad_elementos){
    
    if (personaje->ultimo_movimiento == ARRIBA){
        iluminar_arriba (juego, personaje, elementos, cantidad_elementos);
    }
    else if (personaje->ultimo_movimiento == ABAJO){
        iluminar_abajo (juego, personaje, elementos, cantidad_elementos);
    }
    else if (personaje->ultimo_movimiento == IZQUIERDA){
        iluminar_izquierda (juego, personaje, elementos, cantidad_elementos);
    }
    else if (personaje->ultimo_movimiento == DERECHA){
        iluminar_derecha (juego, personaje, elementos, cantidad_elementos);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 *PRE:
 *POST:Devuelv      ->true si chloe esta en una de las posiciones alrededor del personaje
 *                  ->false si chloe no esta en una de las  posiciones alrededor del personaje
 */
bool esta_chloe_alrededor (juego_t juego, personaje_t personaje, int lado_horizontal, int lado_vertical){
    return((personaje.posicion.fil + lado_horizontal) == juego.amiga_chloe.fil) && ((personaje.posicion.col + lado_vertical) == juego.amiga_chloe.col);
}

/*
 *PRE:
 *POST:Devuevle     ->true esta chloe alrededor
 *                  ->false si no esta chloe alrededor
 */
bool revisar_chloe_alrededor(juego_t juego, personaje_t personaje){ 
    return ( esta_chloe_alrededor(juego, personaje, SUMAR_UNO, SUMAR_UNO) ||
    esta_chloe_alrededor(juego, personaje, SUMAR_UNO, RESTAR_UNO) ||
    esta_chloe_alrededor(juego, personaje, SUMAR_UNO, QUEDARSE_QUIETO) ||
    esta_chloe_alrededor(juego, personaje, RESTAR_UNO, RESTAR_UNO) ||
    esta_chloe_alrededor(juego, personaje, RESTAR_UNO, SUMAR_UNO) ||
    esta_chloe_alrededor(juego, personaje, RESTAR_UNO, QUEDARSE_QUIETO) ||
    esta_chloe_alrededor(juego, personaje, QUEDARSE_QUIETO, QUEDARSE_QUIETO) ||
    esta_chloe_alrededor(juego, personaje, QUEDARSE_QUIETO, RESTAR_UNO) ||
    esta_chloe_alrededor(juego, personaje, QUEDARSE_QUIETO, SUMAR_UNO) );
}

/*
 *PRE:
 *POST:Devuelve     ->true hay algun elemento en una de las posiciones alrededor del personaje
 *                  ->false si no hay ningun elemento en una de las posiciones alrededor del personaje
 */
bool esta_alrededor (personaje_t personaje, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int lado_horizontal, int lado_vertical, int i){
    return((personaje.posicion.fil + lado_horizontal) == elementos[i].posicion.fil) && ((personaje.posicion.col + lado_vertical) == elementos[i].posicion.col);
}

/*
 *PRE:
 *POST: Devuelve    ->true hay algun elemento alrededor
 *                  ->false si no hay ningun elemento alrededor
 */
bool revisar_alrededor(personaje_t personaje, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int i){ 
    return ( esta_alrededor(personaje, elementos, SUMAR_UNO, SUMAR_UNO, i) ||
    esta_alrededor(personaje, elementos, SUMAR_UNO, RESTAR_UNO, i) ||
    esta_alrededor(personaje, elementos, SUMAR_UNO, QUEDARSE_QUIETO, i) ||
    esta_alrededor(personaje, elementos, RESTAR_UNO, RESTAR_UNO, i) ||
    esta_alrededor(personaje, elementos, RESTAR_UNO, SUMAR_UNO, i) ||
    esta_alrededor(personaje, elementos, RESTAR_UNO, QUEDARSE_QUIETO, i) ||
    esta_alrededor(personaje, elementos, QUEDARSE_QUIETO, QUEDARSE_QUIETO, i) ||
    esta_alrededor(personaje, elementos, QUEDARSE_QUIETO, RESTAR_UNO, i) ||
    esta_alrededor(personaje, elementos, QUEDARSE_QUIETO, SUMAR_UNO, i) );
}


/*
 *PRE: Coordenadas de personaje
 *POST: Por cada elemento y chloe si alguno esta alrededor del personaje lo hace visible
 */
void activar_vela (juego_t* juego, personaje_t personaje, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int cantidad_elementos){ //obstaculos y herramientas
    for  (int i = 0; i < cantidad_elementos; i++){
        if (revisar_alrededor(personaje, elementos, i)){

            elementos[i].visible = true;

        }
    }
    if (revisar_chloe_alrededor(*juego, personaje)){

        juego->chloe_visible = true;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 *PRE: Coordenadas del centro de la bengala dada
 *POST: Ilumina los elementos y hace visible a chloe si es que estan dentro del rango de la bengala
 */
void iluminar_bengala (juego_t* juego, elemento_del_mapa_t elementos[MAX_OBSTACULOS], int cantidad_elementos, int col_centro_bengala, int fil_centro_bengala){

    for (int i = 0; i < cantidad_elementos; i++){
        if ( ( abs (elementos[i].posicion.fil - fil_centro_bengala) + abs (elementos[i].posicion.col - col_centro_bengala) ) <= DISTANCIA_MANHATAN){
            elementos[i].visible = true;
        }
    }
    if ( ( abs (juego->amiga_chloe.fil - fil_centro_bengala) + abs (juego->amiga_chloe.col - col_centro_bengala) ) <= DISTANCIA_MANHATAN){
        juego->chloe_visible = true;
    }
}

/*
 *PRE:
 *POST: Genera el centro de la bengala
 */
void activar_bengala (juego_t* juego){

    int col_centro_bengala = generar_random (MAX_COLUMNAS);
    int fil_centro_bengala = generar_random (MAX_FILAS);

    iluminar_bengala(juego, juego->herramientas, juego->cantidad_herramientas, col_centro_bengala, fil_centro_bengala);
    iluminar_bengala(juego, juego->obstaculos, juego->cantidad_obstaculos, col_centro_bengala, fil_centro_bengala);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: Tipo = BENGALA, LINTERNA o VELA
 *POST: Devuelve -> La posicion del elemento del tipo en la mochila
 *               -> Si no esta el tipo en la mochila devuelve -1
 */
int buscar_elemento_mochila (personaje_t personaje, char tipo){ 

    int i = 0;
    int locacion = -1;

    while (i < personaje.cantidad_elementos && locacion == -1){
        if (personaje.mochila[i].tipo == tipo){

            locacion = i;
        }
        i++;
    }
    return locacion;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE:
 *POST: Devuelve:   -> true si el tipo de elemento en uso es igaul a la jugada y si el tipo de elemento en uso no es una BENGALA
 *                  -> false si el tipo de elemento en uso es distinto a la jugada o si el tipo de elemento en uso es una BENGALA
 */
bool quiere_desactivar_elemento(personaje_t personaje,char jugada){ 

    return( (personaje.mochila[personaje.elemento_en_uso].tipo == jugada) && (personaje.mochila[personaje.elemento_en_uso].tipo != BENGALA));
}

/*
 *PRE:
 *POST:Devuelve:   -> true si es que la locacion es distinta a -1 y si los movimientos restantes de el elemento son distintos a 0
 *                 -> false si la locacion es -1 o iguales a 0
 */
bool tiene_elemento(personaje_t personaje, char tipo){

    int locacion = buscar_elemento_mochila (personaje,tipo);
    return (locacion != -1 && personaje.mochila[locacion].movimientos_restantes != 0);
}

/*
 *PRE: Elemento identificado
 *POST:Devuelve:   -> true Si la jugada es igual al elemento y la jugada es distinta a la BENGALA
 *                 -> false La jugada es igual al elemento o la jugada es BENGALA
 */
bool quiere_activar_elemento (char jugada, char elemento, personaje_t personaje){

    return ( jugada == elemento && personaje.mochila[personaje.elemento_en_uso].tipo != BENGALA && tiene_elemento(personaje, jugada));
}


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE:
 *POST: Identifica si el tipo de elemento en uso es una LINTERNA, VELA o BENGALA y si hay algun elemento en uso
 */
void revision_elementos_en_uso (juego_t* juego){ 

    apagar_luces(juego->obstaculos, juego->cantidad_obstaculos);
    apagar_luces(juego->herramientas, juego->cantidad_herramientas);
    chloe_invisible(juego);

    if (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == LINTERNA){

        activar_linterna (juego,&(juego->personaje), juego->herramientas, &(juego->cantidad_herramientas));
        activar_linterna (juego,&(juego->personaje), juego->obstaculos, &(juego->cantidad_obstaculos));

    }
    else if (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == VELA){

        activar_vela(juego, juego->personaje, juego->obstaculos, juego->cantidad_obstaculos);
        activar_vela(juego, juego->personaje, juego->herramientas, juego->cantidad_herramientas);

    }
    else if (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == BENGALA){

        activar_bengala (juego);

    }
    if (juego->personaje.elemento_en_uso != -1){

        gastar_elemento_mochila(&(juego->personaje));
    }

}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE:
 *POST: Muestra un aviso segun se active la LINTERNA, VELA o BENGALA o si desactivaste un elemento
 */
void avisar_activacion (char herramienta){
    if (herramienta == LINTERNA){
        printf("Activaste la LINTERNA\n");
    }
    else if (herramienta == VELA){
        printf("Activaste la VELA\n");
    }
    else if (herramienta == BENGALA){
        printf("Activaste la BENGALA\n");
    }
    else {
        printf("Desactivaste el elemento en uso (%c)\n", herramienta);
    }
}

/*
 *PRE: Heramienta en uso identificada
 *POST: Muestra un aviso segun no se pueda activar la BENGALA, no se pueda activar algun elemento pq la BANGALA esta activada
 *      o no se tenga el elemento en la mochila
 */
void avisar_inhabilitacion (char herramienta_en_uso, char jugada){
    if (jugada == herramienta_en_uso){
        printf("No se puede desactivar la BENGALA\n");
    }
    else if (herramienta_en_uso == BENGALA){
        printf("No se puede activar el elemento que selecciono (%c) pq la BENGALA esta activa\n",jugada);
    }
    else {
        printf("No tiene el elemento que selecciono (%c)\n", jugada);
    }
}


/*
 *PRE: La jugada tiene que ser L, V o E
 *POST: Identifica si:  -> Se quiere desactivar un elemento (cambia el elemento en uso)
 *                      -> Se quiere activar la LINTERNA(cambia el elemento en uso)
 *                      -> Se quiere activar una VELA(cambia el elemento en uso)
 *                      -> Se quiere activar una BENGALA (cambia el elemento en uso)
 *                      -> El elemento en uso es una BENGALA 
 *                      -> No tiene el elemento seleccionado en la mochila
 */
void utilizar_elemento (juego_t* juego, char jugada){ 

    if ( quiere_desactivar_elemento(juego->personaje, jugada) ){

        avisar_activacion(-1);

        juego->personaje.elemento_en_uso = -1;


        apagar_luces(juego->obstaculos, juego->cantidad_obstaculos);
        apagar_luces(juego->herramientas, juego->cantidad_herramientas);
        chloe_invisible(juego);
    }
    else if (quiere_activar_elemento(jugada, LINTERNA, juego->personaje)){

        generador_koala(juego);

        apagar_luces(juego->obstaculos, juego->cantidad_obstaculos);
        apagar_luces(juego->herramientas, juego->cantidad_herramientas);
        chloe_invisible(juego);

        juego->personaje.elemento_en_uso = buscar_elemento_mochila (juego->personaje, jugada);

        avisar_activacion(juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo);

        activar_linterna (juego,&(juego->personaje), juego->herramientas, &(juego->cantidad_herramientas));
        activar_linterna (juego,&(juego->personaje), juego->obstaculos, &(juego->cantidad_obstaculos));

        gastar_elemento_mochila (&(juego->personaje));
 
    }
    else if (quiere_activar_elemento(jugada, VELA, juego->personaje)){


        apagar_luces(juego->obstaculos, juego->cantidad_obstaculos);
        apagar_luces(juego->herramientas, juego->cantidad_herramientas);
        chloe_invisible(juego);

        juego->personaje.elemento_en_uso = buscar_elemento_mochila (juego->personaje, jugada);

        avisar_activacion(juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo);

        activar_vela(juego, juego->personaje, juego->obstaculos, juego->cantidad_obstaculos);
        activar_vela(juego, juego->personaje, juego->herramientas, juego->cantidad_herramientas);

        gastar_elemento_mochila (&(juego->personaje));
    }
    else if (tiene_elemento(juego->personaje, BENGALA) && jugada == BENGALA){


        apagar_luces(juego->obstaculos, juego->cantidad_obstaculos);
        apagar_luces(juego->herramientas, juego->cantidad_herramientas);
        chloe_invisible(juego);

        juego->personaje.elemento_en_uso = buscar_elemento_mochila (juego->personaje, jugada);
        avisar_activacion(juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo);

        activar_bengala (juego);

        gastar_elemento_mochila(&(juego->personaje));

    }
    else if (juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo == BENGALA){

        avisar_inhabilitacion(juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo, jugada);
        gastar_elemento_mochila(&(juego->personaje));
    }
    else {
        avisar_inhabilitacion(juego->personaje.mochila[juego->personaje.elemento_en_uso].tipo, jugada);
    }
}
 
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 *PRE: 
 *POST: Si es que el tiempo perdido es 30 segs y el tipo de personaje es PANDA chloe se vuelve visible
 */
void activar_gps (juego_t* juego){

    if (juego->personaje.tiempo_perdido > 30 && juego->personaje.tipo == PANDA){

        juego->chloe_visible = true;
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: Herramienta encontrada es PILA 
 *POST: A laLINTERNA en la mochila se le suman 5 movimientos
 *     
 */
void encontro_pila (juego_t* juego){

    int locacion = buscar_elemento_mochila(juego->personaje, LINTERNA);
    juego->personaje.mochila[locacion].movimientos_restantes += DURACION_PILA;
}

/*
 *PRE: Tipo la herramienta encontrada
 *POST: Identifica la herramienta encontrada (PILA, VELA o BENGALA);
 */
void identificar_herramienta (juego_t* juego, char tipo){
    if (tipo == PILA){
        encontro_pila(juego);
    }
    else if (tipo == VELA){
        agregar_elementos_mochila(&(juego->personaje), VELA, DURACION_VELAS, 1);
    }
    else if (tipo == BENGALA){
        agregar_elementos_mochila(&(juego->personaje), BENGALA, DURACION_BENGALAS, 1);
    }
}

/*
 *PRE: Posicion de la herramienta para eliminar
 *POST: Elimina la herramienta del mapa
 */
void eliminar_herramienta_mapa (juego_t* juego, elemento_del_mapa_t herramientas[MAX_OBSTACULOS], int i){

    herramientas[i].posicion.col = herramientas[juego->cantidad_herramientas-1].posicion.col;
    herramientas[i].posicion.fil = herramientas[juego->cantidad_herramientas-1].posicion.fil;
    herramientas[i].tipo = herramientas[juego->cantidad_herramientas-1].tipo;
    herramientas[i].visible = false;
    juego->cantidad_herramientas --;
}

/*
 *PRE:  Juego inicializado
 *POST: Encuentra el herramienta en donde se encuentra el personaje
 */
void encontrarse_herramienta (juego_t* juego){
    for (int i = 0; i < juego->cantidad_herramientas; i++){
        if (juego->personaje.posicion.fil == juego->herramientas[i].posicion.fil && juego->personaje.posicion.col == juego->herramientas[i].posicion.col){
            identificar_herramienta (juego, juego->herramientas[i].tipo);
            eliminar_herramienta_mapa (juego, juego->herramientas, i);
        }
    }
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 *PRE:
 *POST: Si -> El obstaculo es ARBOL: se suma un segundo o medio dependiendo del oso al tiempo perdido
 *            El obstaculo es PIEDRA: se suma 2 segundos o ninguno dependiendo del oso al tiempo perdido
 *            El obstaculo es KOALA: posiciona al personaje en la posicion 0,0
 */
void accionar_obstaculo (juego_t* juego, char obstaculo , double tiempo_piedra, double tiepo_arbol){
    if (obstaculo == ARBOL){
        juego->personaje.tiempo_perdido += tiepo_arbol;
        activar_gps(juego);
    }
    else if (obstaculo == PIEDRA){
        juego->personaje.tiempo_perdido += tiempo_piedra;
        activar_gps(juego);
    }
    else if (obstaculo == KOALA){
        juego->personaje.posicion.fil = 0;
        juego->personaje.posicion.col = 0;

    }
}

/*
 *PRE:
 *POST: Realiza las acciones de los obstaculos segun si el personaje es PANDA, PARDO o POLAR
 */
void identificar_oso (juego_t* juego, char obstaculo){
    if (juego->personaje.tipo == PANDA){
        accionar_obstaculo(juego, obstaculo,  TIEMPO_PIEDRA,  TIEMPO_ARBOL);
    }
    else if (juego->personaje.tipo == PARDO){
        accionar_obstaculo(juego, obstaculo,  TIEMPO_PIEDRA,  TIEMPO_ARBOL_PARDO);

    }
    else if (juego->personaje.tipo == POLAR){
        accionar_obstaculo(juego, obstaculo,  TIEMPO_PIEDRA_POLAR,  TIEMPO_ARBOL);
    }
}

/*
 *PRE:   Juego inicializado
 *POST:  Encuentra el obstaculo en donde se encuentra el personaje
 */
void encontrarse_obstaculo (juego_t* juego){

    for (int i = 0; i < juego->cantidad_obstaculos; i ++){

        if (juego->personaje.posicion.fil == juego->obstaculos[i].posicion.fil && juego->personaje.posicion.col == juego->obstaculos[i].posicion.col){

            char obstaculo = juego->obstaculos[i].tipo;
            identificar_oso (juego, obstaculo);
        }
    }
}




//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE:
 *POST: Devuelve -> true: si la jugada es (en mayuscula) la que activa la vela, linterna, bengala o pila
 *               -> false: si la jugada no es ninguana de ellas
 */
bool jugada_activar (char jugada){
    return (jugada == LINTERNA || jugada == VELA || jugada == BENGALA);
}

/*
 *PRE:
 *POST: Devuelve -> true: si la jugada es (en mayuscula) la que activa el movimiento arriba, derecha, izquierda o derecha
 *               -> false: si la jugada no es ninguna ellas
 */
bool jugada_movimiento (char jugada){
    return (jugada == ARRIBA || jugada == DERECHA || jugada == ABAJO || jugada == IZQUIERDA);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: 
 *POST: Muestra en pantalla el tiempo transcurrido desde que se empezo el juego y el tiempo perdido acumulado
 */
void mostrar_tiempo (juego_t juego){
    double tiempo_ahora = tiempo_actual ();
    printf ("tiempo = %0.1f segs\ntiempo perdido = %0.1f segs\n", tiempo_ahora, juego.personaje.tiempo_perdido);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
 *PRE: Una jugada que sea W, S, D o A
 *POST: Identifica la la jugada para el movimiento y guarda el ultimo movimiento
 *          ->W: sube una posicion
 *          ->S: sube una posicion
 *          ->D: se mueve a la derecha una posicion  
 *          ->A: se mueve a la izquierda una posicion
 */
void mover_personaje (juego_t* juego, char jugada){
    if (jugada == ARRIBA){
        deteccion_moviemiento (RESTAR_UNO,QUEDARSE_QUIETO, &(juego->personaje));
        juego->personaje.ultimo_movimiento = ARRIBA;

    }
    else if (jugada == DERECHA){
        deteccion_moviemiento (QUEDARSE_QUIETO,SUMAR_UNO, &(juego->personaje));
        juego->personaje.ultimo_movimiento = DERECHA;

    }
    else if (jugada == ABAJO){
        deteccion_moviemiento (SUMAR_UNO,QUEDARSE_QUIETO, &(juego->personaje));
        juego->personaje.ultimo_movimiento = ABAJO;

    }
    else if (jugada == IZQUIERDA){
        deteccion_moviemiento (QUEDARSE_QUIETO,RESTAR_UNO, &(juego->personaje));
        juego->personaje.ultimo_movimiento = IZQUIERDA;
    }
    revision_elementos_en_uso(juego);
    encontrarse_herramienta (juego);
    encontrarse_obstaculo (juego);
}
/*
 *PRE: Una jugada valida 
 *POST: Detecta el tipo de jugada
 *          ->W, D, S o A se fija para mover el personaje
 *          ->L, E o V: se fija para activar una herramienta
 *          ->T: Muestra el tiempo perdido y el transcurrido  
*/
void realizar_jugada(juego_t* juego, char jugada){

    if (jugada_movimiento(jugada)){
        mover_personaje(juego, jugada);
    }
    else if (jugada_activar(jugada)){ 
        utilizar_elemento (juego, jugada);
    }
    else if (jugada == (TIEMPO)){
        mostrar_tiempo (*juego);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 *PRE: Una jugada
 *POST: Devuelve->  true: si es que la jugada es valida
 *                  false: si la jugada no es valida
 */
bool es_jugada_valida (char jugada){
    return (jugada == (TIEMPO) ||
    jugada == (ARRIBA) ||
    jugada == (ABAJO) ||
    jugada == (IZQUIERDA) ||
    jugada == (DERECHA) ||
    jugada == (LINTERNA) ||
    jugada == (BENGALA) ||
    jugada == (VELA) );
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 *PRE:
 *POST: Llena el bosque con Vacio
 */
void llenar_de_oscuridad (char bosque [MAX_FILAS][MAX_COLUMNAS] ){

    for (int i = 0; i < MAX_FILAS; i++){
        for (int j = 0; j < MAX_COLUMNAS; j++){

            bosque[i][j] = VACIO;
        }
    }
}

/*
 *PRE:
 *POST: Posiciona elementos del bosque
 */
void posicionar_elementos_bosque(int cant_elementos, elemento_del_mapa_t elementos[MAX_OBSTACULOS], char bosque[MAX_FILAS][MAX_COLUMNAS]){

    for(int i = 0; i < (cant_elementos); i++){

        if (elementos[i].visible){
            bosque [elementos[i].posicion.fil] [elementos[i].posicion.col] = elementos[i].tipo;
        }
    }
}
/*
 *PRE:
 *POST: Llama a las funciones para posicionar elementos del bosque y posiciona a chloe si es que es visible y el personaje en el bosque 
 */
void posicionar_bosque (juego_t juego, char bosque[MAX_FILAS][MAX_COLUMNAS]){

    posicionar_elementos_bosque(juego.cantidad_obstaculos, juego.obstaculos, bosque);
    posicionar_elementos_bosque(juego.cantidad_herramientas, juego.herramientas, bosque);

    bosque[juego.personaje.posicion.fil][juego.personaje.posicion.col] = juego.personaje.tipo;

    if (juego.chloe_visible == true){
        bosque[juego.amiga_chloe.fil][juego.amiga_chloe.col] = CHLOE;
    }
}
/*
 *PRE:
 *POST:Identifica y muestra los elementos del bosque
 */
void colocar_emojis (char bosque[MAX_FILAS][MAX_COLUMNAS], int i, int j){
    
    if (bosque[i][j] == PANDA){
        printf(" %s ",EMOJI_PANDA);
    }
    else if (bosque[i][j] == PARDO){
        printf(" %s ",EMOJI_PARDO);
    }
    else if (bosque[i][j] == POLAR){
        printf(" %s ",EMOJI_POLAR);
    }
    else if (bosque[i][j] == ARBOL){
        printf(" %s ", EMOJI_ARBOL);
    }
    else if (bosque[i][j] == PIEDRA){
        printf(" %s ", EMOJI_PIEDRA);
    }
    else if (bosque[i][j] == KOALA){
        printf(" %s ", EMOJI_KOALA);
    }
    else if (bosque[i][j] == VELA){
        printf(" %s ", EMOJI_VELA);
    }
    else if (bosque[i][j] == BENGALA){
        printf(" %s ", EMOJI_BENGALA);
    }
    else if (bosque[i][j] == PILA){
        printf(" %s ", EMOJI_PILA);
    }
    else if (bosque[i][j] == VACIO){
        printf(" %s ", EMOJI_VACIO);
    }
    else if (bosque[i][j] == CHLOE){
        printf(" %s ", EMOJI_CHLOE);
    }

}
/*
 *PRE:
 *POST: Identifica y muestra los elementos de la mochila
 */
void colocar_emojis_mochila (juego_t juego, char mochila_emoji[MAX_HERRAMIENTAS] , int i){
    
    if (juego.personaje.mochila[i].tipo == LINTERNA){
        printf(" %s (%c - %i).", EMOJI_LINTERNA, juego.personaje.mochila[i].tipo, juego.personaje.mochila[i].movimientos_restantes);
    }
    else if (juego.personaje.mochila[i].tipo == VELA){
        printf(" %s (%c - %i).", EMOJI_VELA, juego.personaje.mochila[i].tipo, juego.personaje.mochila[i].movimientos_restantes);
    }
    else if (juego.personaje.mochila[i].tipo == BENGALA){
        printf(" %s (%c - %i).", EMOJI_BENGALA, juego.personaje.mochila[i].tipo, juego.personaje.mochila[i].movimientos_restantes);
    }

}

/*
 *PRE:
 *POST: Musestra en pantalla el bosque
 */
void mostrar_bosque (char bosque[MAX_FILAS][MAX_COLUMNAS]){
    printf("\n\n");

    for (int i = 0; i < MAX_FILAS; i++){
        for (int j = 0; j < MAX_COLUMNAS; j++){
            colocar_emojis(bosque, i, j);
                
        }
        printf("\n");
    }
}

/*
 *PRE: 
 *POST: Muestra en pantalla la mochila con sus elementos y los movimientos restantes
 */
void mostrar_mochila (juego_t juego){
    printf("\n");
    char mochila_emoji[MAX_HERRAMIENTAS];


    for (int i = 0; i < juego.personaje.cantidad_elementos; i++){

        colocar_emojis_mochila (juego ,mochila_emoji, i);
        
    }
}

/*
 *PRE: El juego completo con las posiciones de los elementos del bosque las posiciones de chloe y el personaje y la mochila con sus herramientas con sus movimientos restantes
 *POST: Muestra el juego en pantalla
 */
void mostrar_juego (juego_t juego){
    char bosque [MAX_FILAS][MAX_COLUMNAS];

    llenar_de_oscuridad(bosque);
    posicionar_bosque(juego,bosque);
    mostrar_bosque(bosque);
    mostrar_mochila(juego);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
 *PRE: La posicion de el personaje en la matriz y la posicion de chloe en la matriz
 *POST: Si la posicion del personaje es igual a la de chloe devuelve 0 sino devuelve -1
 */
int estado_juego(juego_t juego){
    if (juego.personaje.posicion.fil != juego.amiga_chloe.fil || juego.personaje.posicion.col != juego.amiga_chloe.col){
        return 0;
    }
    else{
        return -1;
    }
}


