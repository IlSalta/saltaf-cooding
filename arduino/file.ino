

// definizione delle variabil

    // luci semafori
        int rosso_1 = 3;              //luci semaforo 1
        int giallo_1 = 4;
        int verde_1 = 5;

        int rosso_2 = 6;              //luci semaforo 2
        int giallo_2 = 7;
        int verde_2 = 8;

    //tempi Semafori
        /*int temp_rosso = 5000;*/        // tempi attesa semaforo
        int temp_giallo = 2000;
        int temp_verde = 3000;


void setup () {

}

void loop () {

    //test delle luci
    // creo una variabile valida solo all'inizio che dice che la verifica non è stata sfatta
   static int verifica = 0;
   // eseguo la verifica                                                // se e stato verificato il circuito 1 volta bypassa la verifica senno fa la verifica
   if(!verifica) {
        for(int test_loop = 0; test_loop=3; test_loop++) {              //test luci rosse
            //accendo rosso 1 e rosso 2 
            digitalWrite(rosso_1; HIGH);
            digitalWrite(rosso_2; HIGH);
            //aspetto 0,5 sec
            delay (500);
            // spengo rosso 1 e rosso 2 
            digitalWrite(rosso_1, LOW);
            digitalWrite(rosso_2; LOW);
            // attendo 0,5 sec
            delay(500);
        }
         for(int test_loop = 0; test_loop=3; test_loop++) {             // test luci gialle 
            // accebdo giallo 1 e giallo 2 
            digitalWrite(giallo_1; HIGH);
            digitalWrite(giallo_2; HIGH);
            // attendo o,5 secondi
            delay (500);
            // spengo giallo 1 e giallo 2 
            digitalWrite(giallo_1, LOW);
            digitalWrite(giallo_2; LOW);
            // attendo 0,5 secondi
            delay(500);
        }
        for(int test_loop = 0; test_loop=3; test_loop++) {              //test luci verde
            // accendo verde 1 e verde 2 
            digitalWrite(verde_1; HIGh);
            digitalWrite(verde_2; HIGH);
            // attendo 0,5 secondi
            delay (500);
            // spengo verde 1 e verde 2 
            digitalWrite(verde_1, LOW);
            digitalWrite(verde_2; LOW);
            // attendo 0,5 secondi
            delay(500);
        }

        verifica =1                                                     // modifica il valore della variabile di modifica a 1 segnando che la verifica è stata fatta
   }

    //ciclo del semaforo
    for (int ciclo_semaforo =1; ciclo_semaforo<25; ciclo_semaforo++) {
        // accendo luce rossa1 e luce verde2 del semaforo
        digitalWrite(rosso_1; HIGH);                
        digitalWrite(verde_2; HIGH);
        //aspetto tempo verde2 per mettere giallo2
        delay(temp_verde)
        //spengo verde2 e accendo giallo2
        digitalWrite(verde_2; LOW);
        digitalWrite(giallo_2; HIGH)
        // attendo il tempo per arrivare a rosso
        delay(temp_giallo);
        //spengo rosso 1 e metto verde 1 
        digitalWrite(rosso_1; LOW);
        digitalWrite(verde_1; HIGH);
        //spengo giallo2 e metto rosso 2 
        digitalWrite(giallo_2; LOW);
        digitalWrite(rosso_2; HIGH);
        //attendo la durata del verde
        delay(temp_verde);
        //spengo il verde e accendo il giallo 
        digitalWrite(verde_1; LOW);
        digitalWrite(giallo_1; HIGH);
        // attendo il tempo del giallo
        delay(temp_giallo)
        //spengo il giallo e faccio reincominciare il ciclo
        digitalWrite(temp_giallo; low);
    }
}