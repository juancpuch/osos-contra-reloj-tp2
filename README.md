# osos-contra-reloj-tp2
juego de tp2

Osos contra reloj es un juego de tipo arcade
El juego consiste en encontrar a chloe en un bosque en la oscuridad de la noche. El jugador que, basado en una pequeña ecuesta, podra ser cualquiera de los 3 osos escandalosos (Polar, Pardo o Panda), tendra que buscar a nuestra amiga en el menor tiempo posible utilizando las herramientas de su mochila y evadiendo los obstaculos de el bosque.

Objetivo: Econtrar a chloe y llegar a su ubicacion en menos de 120seg.
Mapa: El mapa es un bosque oscuro con obstaculos y herramientas exparcidas en el. El juego inicia con 350 arboles, 50 piedras y 1 koala y con el personaje en
una posicion random del cosatado derecho del mapa.
Obstaculos: Los obstaculos estaran en todo el bosque, y, aunque no tengas vision, estos podran afecar a tu exaustiva busqueda
            Arbol-> suman 1 segundo al tiempo transcurrido (a Pardo no le afectan los arboles)
            Piedra-> suman 2 segundos al tiempo transcurrido (a Polar solo le suma 1 seg)
            Koala Nom Nom-> si es que se encuentran con un koala el jugador se dirigira a la ezquina superior izquierda.
Herramientas: Las herramientas estaran en todo el bosque y podras agarrarlas durante el juego para utilizarlas luego. Ademas tendras algunas de estas en tu mochila.
            Linterna-> Esta tendra 10 movimientos iniciales (exepto Pardo que empezara con 15 movs iniciales). Cuando se activa la linterna (L) esta iluminara desde 
            la posicion del personaje en linea recta hacia la direccion del ultimo movimiento del personaje. Cada vez que se active la linterna aparecera un koala 
            en una posicion random del mapa.
            Pila-> Cuando se encuentra una pila en el bosque se le sumara 5 movimientos a la linterna
            Vela-> Inicialmente el personaje tendra 4 velas a su disposicion (exepto Polar que empezara con 6). Cuando se activa una vela esta podra estar activa 
            por 5 movimientos iluminando alrededor del personaje.
            Bengala-> Inicialmente no se empezara con bengalas (exepto Panda que empezara con 2). Esta, con 3 movimientos, iluminara con una distacia de 3
            manhattans una posicion random del mapa. Durante la activacion de la bengala no se podra activar ni desactivar ningun elemento (la bengala inclusive) 
            hasta que se consuman los 3 movimientos.
Controles: Movimiento-> W-A-S-D
           Herramientas (activar y desactivar)-> L(linterna), E(bengala) y V (vela)
           Tiempo-> podes chequear el tiempo transcurrido con T
           (los comandos son solo con letra mayuscula y cada vez que se efectue un movimiento pulsar ENTER)
