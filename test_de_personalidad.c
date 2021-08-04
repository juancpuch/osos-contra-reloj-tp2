#include <stdio.h>
#include <stdbool.h>
#include "test_de_personalidad.h"

#define ANIME 'A'
#define MUSICA_POP 'M'
#define LIMPIEZA 'L'
#define BAMBU 'B'
#define PESCADO 'P'
#define FOCAS 'F'

static const char POLAR = 'I';
static const char PANDA = 'P';
static const char PARDO = 'G';

const int MINIMO_TORRE = 1;
const int MAXIMO_TORRE = 18;

const int MINIMO_GRITO = 1;
const int MAXIMO_GRITO = 18;

const int MULTIPICADOR_LIMPIEZA = 1;
const int MULTIPICADOR_ANIME = 2;
const int MULTIPICADOR_MUSICA_POP = 3;

const int PUNTOS_FOCAS = 3;
const int PUNTOS_BAMBU = 6;
const int PUNTOS_PESCADO = 9;

const int MAXIMO_POLAR = 24;
const int MAXIMO_PANDA = 43;
const int MAXIMO_PARDO = 63;


/* 
 *PRE: 	Valor dado del canal_tv.
 *POST: -Devuelve TRUE si canal_tv es igual a ANIME MUSICA_POP o LIMPIEZA.
 *   	-De lo contrario devuelve FALSE.
 */
bool es_canal_valido (char canal_tv){

	return (canal_tv ==  ANIME || canal_tv == MUSICA_POP || canal_tv == LIMPIEZA);
}
/*
 *PRE:	-
 *POST: Pide al usuario que elija un canal (ANIME, MUSICA POP o LIMPIEZA).
 */
void pedir_canal_tv (char* canal_tv){

	printf ("Vas a ver television un rato, pones el canal de ANIME (%c), MUSICA_POP (%c) o LIMPIEZA (%c):", ANIME, MUSICA_POP, LIMPIEZA);
	scanf(" %c", canal_tv);

	while (!es_canal_valido(*canal_tv)){

		printf("Ese caracter no representa ninguna de las opciones.\nQue canal pones? ANIME (%c), MUSICA_POP (%c) o LIMPIEZA (%c):", ANIME, MUSICA_POP, LIMPIEZA);
		scanf(" %c",canal_tv);
	}
}


/* 
 *PRE: 	Valor dado de alimento.
 *POST: -Devuelve TRUE si canal_tv es igual a BAMBU PESCADO o FOCAS.
 *   	-De lo contrario devuelve FALSE.
 */
bool es_alimento_valido (char alimento){

	return ((alimento ==  BAMBU || alimento == PESCADO || alimento == FOCAS));
}
/*
 *PRE:	-
 *POST: Pide al usuario que elija un alimento (PESCADO, BAMBU o FOCAS)
 */
void pedir_alimento_a_guardar (char *alimento){

	printf("Solo podes guardar un alimento en tu vianda, guardas el BAMBU (%c), PESCADO (%c) o FOCAS (%c):", BAMBU, PESCADO, FOCAS);
	scanf(" %c", alimento);

	while (!es_alimento_valido (*alimento)){

		printf("Ese caracter no representa ninguna de las opciones.\nQue alimento guardas? BAMBU (%c), PESCADO (%c) o FOCAS (%c):", BAMBU, PESCADO, FOCAS);
		scanf(" %c", alimento);
	}
}


/*
 *PRE: 	Valor dado del piso de la torre.
 *POST: -Devuelve TRUE si piso_de_torre es mayor al maximo o menor al minimo.
 *  	-Devuelve False si piso_de_torre esta entre el maximo o minimo.
 */
bool es_piso_valido (int piso_de_torre){

	return(piso_de_torre > MAXIMO_TORRE || piso_de_torre < MINIMO_TORRE);
}
/*
 *PRE: -
 *POST:	Pide al usuario que ejija un piso_de_torre.
 */
void pedir_piso_de_torre (int *piso_de_torre){

	printf("Te compras un torre con tus dos hermanos de 18 pisos. En que piso te gustaria vivir?:");
	scanf(" %i", piso_de_torre);

	while (es_piso_valido(*piso_de_torre)){

		printf("No hay tantos (o tan pocos?) pisos.\nEn que piso te gustaria vivir sino? (%i - %i):", MINIMO_TORRE, MAXIMO_TORRE);
		scanf(" %i", piso_de_torre);
	}
}


/*
 *PRE: 	Valor dado de la intensidad_grito.
 *POST: -Devuelve True si intensidad_grito es mayor al maximo o menor al minimo.
 *		-Devuelve False si intensidad_grito esta entre el maximo y el minimo.
 */
bool es_grito_valido (int intensidad_grito){
	
	return (intensidad_grito > MAXIMO_GRITO|| intensidad_grito < MINIMO_GRITO);
}
/*
 *PRE: -
 *POST: Pide al usuario que elija una intensidad_grito.
 */
void pedir_intensidad_de_grito (int *intensidad_grito){

	printf("Oh, una rata! Que tan fuerte gitas del %i al %i? Siendo 1 no gritar y 18 desgarrarse la garganta:", MINIMO_GRITO, MAXIMO_GRITO);
	scanf("%i", intensidad_grito);

	while (es_grito_valido(*intensidad_grito)){

		printf("Esa intensidad es invalida.\nQue tan fuerte gritas (%i - %i):", MINIMO_GRITO, MAXIMO_GRITO);
		scanf("%i", intensidad_grito);
	}
}


/*
 *PRE: 	El canal de tv ya verificado
 *POST: Crea una variable que contiene el valor del multiplicador correspondiente al canal de tv.
 */
int dar_valor_canal_tv (char canal_tv){
	int valor_canal_tv = 0;
	switch (canal_tv){

		case ANIME:
			valor_canal_tv = MULTIPICADOR_ANIME;
			break;
		case MUSICA_POP:
			valor_canal_tv = MULTIPICADOR_MUSICA_POP;
			break;
		case LIMPIEZA:
			valor_canal_tv = MULTIPICADOR_LIMPIEZA;
			break;
	}
	return valor_canal_tv;
}


/*
 *PRE: 	El alimento ya verificado
 *POST: Crea una variable que contiene el valor del los puntos del alimento correspondiente.
 */
int dar_valor_alimentos (char alimento){
	int valor_alimento = 0;
	switch (alimento){

		case BAMBU:
			valor_alimento = PUNTOS_BAMBU;
			break;
		case PESCADO:
			valor_alimento = PUNTOS_PESCADO;
			break;
		case FOCAS:
			valor_alimento = PUNTOS_FOCAS;
			break;
	}
	return valor_alimento;
}


/*
 *PRE:	-Las variables canal_tv, alimento, intensidad_grito y piso_de_torre ya dadas , verificadas
 *POST: -El puntaje total de la formula para el test (5 - 63)
 */
void calcular_puntaje_total(int *puntaje_total, char canal_tv, char alimento, int intensidad_grito, int piso_de_torre){

	*puntaje_total = (dar_valor_alimentos(alimento) * dar_valor_canal_tv(canal_tv) + intensidad_grito + piso_de_torre);
}


/*
 *PRE: 
 *POST: -Imprime el resultado del test
 */
void dar_resultados (int puntaje_total, char personalidad_detectada){
	if (personalidad_detectada == POLAR){

			printf("\n\nPuntaje = (%i).Tu personalidad coincide con la de - Polar (%c) -\n",puntaje_total, POLAR);
		}
		else if (personalidad_detectada == PANDA){

			printf("\n\nPuntaje = (%i).Tu personalidad coincide con la de - Panda (%c) -\n",puntaje_total, PANDA);
		}
		else {

			printf("\n\nPuntaje = (%i).Tu personalidad coincide con la de - Pardo (%c) -\n",puntaje_total, PARDO);
		}
}

char detectar_personalidad (int puntaje_total){
	if (puntaje_total <= MAXIMO_POLAR){

		return POLAR;
	}
	else if (puntaje_total <= MAXIMO_PANDA){

		return PANDA;
	}
	else {

		return PARDO;
	}
}

void test_de_personalidad(char* personalidad_detectada){

	char canal_tv;
	char alimento;
	int piso_de_torre;
	int intensidad_grito;
	int puntaje_total = 0;

	pedir_canal_tv(&canal_tv);
	pedir_alimento_a_guardar(&alimento);
	pedir_piso_de_torre(&piso_de_torre);
	pedir_intensidad_de_grito(&intensidad_grito);

	calcular_puntaje_total (&puntaje_total, canal_tv, alimento, intensidad_grito, piso_de_torre);

	*personalidad_detectada = detectar_personalidad (puntaje_total);
	dar_resultados (puntaje_total, *personalidad_detectada);

}
