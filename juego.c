#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include "test_de_personalidad.h"
#include "utiles.h"
#include "osos_contra_reloj.h"

int main(){

    srand (( unsigned)time(NULL));
    
    juego_t juego;
    char jugada;
    char personalidad_detectada;
    estado_juego(juego);

    system("clear");

    char tecla;
    test_de_personalidad (&personalidad_detectada);

    printf("\n\nPara comenzar el juego presionar cualquier tecla y [Enter]:  ");
    scanf(" %c", &tecla);

    system("clear");

    inicializar_juego(&juego, personalidad_detectada);

    iniciar_cronometro();
    printf("\n");
    mostrar_juego(juego);
    

    while (estado_juego(juego) == 0){

        printf("\nRealizar jugada: ");
        scanf(" %c", &jugada);

        system("clear");

        if (es_jugada_valida(jugada)){

            realizar_jugada(&juego, jugada);

        }
        else{
            printf ("La jugada %c es invalida.\n", jugada);
        }
        mostrar_juego(juego);
        
    }
    double tiempo = detener_cronometro() + juego.personaje.tiempo_perdido;
    printf ("\nTu tiempo fue de \n%0.2f segs", tiempo);

    if (tiempo < 120){
        printf(" \n\n\
          ::::::::           :::        ::::    :::           :::        ::::::::   :::::::::::       :::::::::: \n \
        :+:    :+:        :+: :+:      :+:+:   :+:         :+: :+:     :+:    :+:      :+:           :+:        \n \
       +:+              +:+   +:+     :+:+:+  +:+        +:+   +:+    +:+             +:+           +:+         \n \
      :#:             +#++:++#++:    +#+ +:+ +#+       +#++:++#++:   +#++:++#++      +#+           +#++:++#     \n \
     +#+   +#+#      +#+     +#+    +#+  +#+#+#       +#+     +#+          +#+      +#+           +#+           \n \
    #+#    #+#      #+#     #+#    #+#   #+#+#       #+#     #+#   #+#    #+#      #+#           #+#            \n \
    ########       ###     ###    ###    ####       ###     ###    ########       ###           ##########      \n ");
    }
    else{
        printf(" \n\n\
     PPPP  EEEE RRRR  DDD  III  SSS  TTTTTT EEEE \n \
    P   P E    R   R D  D  I  S       TT   E    \n \
    PPPP  EEE  RRRR  D  D  I   SSS    TT   EEE  \n \
    P     E    R R   D  D  I      S   TT   E    \n \
    P     EEEE R  RR DDD  III SSSS    TT   EEEE \n ");
    }
    

    return 0;
}
