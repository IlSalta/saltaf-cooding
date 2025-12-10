// Programma per gestione striscia a LED indirizzabile per installazione San Pietro
// By Michele Comici e Andrea Saltafosso
// Versione: 1.2
// Data di creazione: 06/12/2025
// Ultima Modifica: 09/12/2025

#include <FastLED.h>

#define DATA_PIN    3
#define LED_TYPE    WS2811
#define COLOR_ORDER BRG
#define NUM_LEDS    100
CRGB leds[NUM_LEDS];
#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  60

// Variabili varie
uint8_t puntatore_flusso = 0;                             // Puntatore per selezionare il LED del flusso di colori che cambiano
uint8_t selettore_tipo_colore_flusso = 0;                 // Puntatore per il tipo di colore nel flusso di colori che cambiano
const uint8_t tipi_di_colore_flusso = 5;                  // Numero di colori diversi da usare nei flussi
uint8_t temporizzatore_lampeggio = 0;                     // Contatore per temporizzazione dei lampeggi
CRGB colore_base = CRGB(255, 0, 20);                      // Colore base nell'effetto dei lampeggi
CRGB colore_lampeggi = CRGB(0, 255, 50);                  // Colore delle parti lampeggianti nell'effetto dei lampeggi
CRGB colore_flusso = CRGB(255, 0, 30);                    // Colore dell'effetto "flusso" 

int change_pal_seg = 1;                                   // creo una variabile intera per cambiare il colore della palette                                  

// *************************************************************************************
void setup() {
  // put your setup code here, to run once:
  //delay(3000); // 3 second delay for recovery
  
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);

}

// Dichiarazione delle routine per gli effetti
void juggle();
void nextPattern();
void flusso_colore();
void lampeggio_segmenti();

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { flusso_colore, lampeggio_segmenti, juggle };
//SimplePatternList gPatterns = { lampeggio_segmenti };
//SimplePatternList gPatterns = { flusso_colore };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

// *************************************************************************************
void loop() {                                                                            
  // put your main code here, to run repeatedly:

  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/FRAMES_PER_SECOND); 

  // Cambia l'effetto ogni X secondi
  EVERY_N_SECONDS( 10 ) { nextPattern(); } 
  // Sposta il punto del flusso ogni X millisecondi
  EVERY_N_MILLISECONDS( 5 ) { 
    puntatore_flusso--;
    if (puntatore_flusso > NUM_LEDS) {
      puntatore_flusso = NUM_LEDS;
    } 
  }
  // Incrementa il temporizzatore per il lampeggio
  EVERY_N_MILLISECONDS( 2 ) { temporizzatore_lampeggio++; }
  // Cambia il colore base e il colore lampeggio ogni X secondi

             // creo una variabile intera per cambiare il colore della palette
  EVERY_N_SECONDS( 3 ) {                                       // ogni 3 secondi 
    if (change_pal_seg > 6) {                                  // se il numero della  variabile change_pal_seg è maggiore di 5
      change_pal_seg = 1;                                      // imposta la variabile a 1                                        
    } else {
      if (change_pal_seg == 1){                                // Palette n°1
        colore_base = CRGB(0, 220, 200);
        colore_lampeggi = CRGB(140, 0, 60);
        change_pal_seg ++;

      } else if (change_pal_seg == 2) {                       // Palette n°2
        colore_base = CRGB(255, 0, 170);
        colore_lampeggi = CRGB(0, 90, 50);
        change_pal_seg ++;

      } else if (change_pal_seg == 3) {                       // Palette n° 3                     
        colore_base = CRGB(255, 125, 20);
        colore_lampeggi = CRGB(0, 80, 60);
        change_pal_seg ++;

      } else if (change_pal_seg == 4) {                       // Palette n° 4
        colore_base = CRGB(40, 70, 110);
        colore_lampeggi = CRGB(200, 150, 20);
        change_pal_seg ++;

      } else if (change_pal_seg == 5) {                       // Palette n° 5
        colore_base = CRGB(255, 100, 180);
        colore_lampeggi = CRGB(40, 70, 110);
        change_pal_seg ++;

      } else if (change_pal_seg == 6) {                       // Palette n° 6
        colore_base = CRGB(70, 255, 120);
        colore_lampeggi = CRGB(170, 60, 255);
        change_pal_seg ++;
      }
       
    }

   } // change patterns periodically

}

// *************************************************************************************
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void flusso_colore()
{
  // Controlla se la variabile "puntatore_flusso" vale 0
  if (puntatore_flusso == 100) {
    // Il puntatore del led su cui lavorare è a 0
    // Passa al colore successivo incrementando "selettore_tipo_colore_flusso"
    selettore_tipo_colore_flusso++;
    // Controlla di non aver superato il valore limite
    if (selettore_tipo_colore_flusso > tipi_di_colore_flusso) {
      // Superato il limite, resetta
      selettore_tipo_colore_flusso = 0;
    }
    // Imposta il colore in base al puntatore di tipo colore
    if (selettore_tipo_colore_flusso == 0) {
      // Fucsia
      colore_flusso = CRGB(255, 0, 30);
      
    } else if (selettore_tipo_colore_flusso == 1) {
      // Blu
      colore_flusso = CRGB(0, 0, 255);

    } else if (selettore_tipo_colore_flusso == 2) {
      // Giallo
      colore_flusso = CRGB(255, 255, 0);
      //colore_flusso = CRGB(255, 120, 0);
      
    }else if (selettore_tipo_colore_flusso == 3) {
      // Verde
      colore_flusso = CRGB(102, 255, 0);
      //colore_flusso = CRGB(120, 255, 0);                       //verde lime neon
      //colore_flusso = CRGB(0, 255, 160);                       //verde menta elettrico
      //colore_flusso = CRGB(0, 220, 100);                       //verde smeraldo acceso

    }else if (selettore_tipo_colore_flusso == 4) {               
      // Rosso
      colore_flusso = CRGB(255, 0, 0);                         // rosso vivo
      //colore_flusso = CRGB(255, 60, 20);                       // rosso fuoco
      //colore_flusso = CRGB(180, 0, 40);                        // rosso cremesi

    }else if (selettore_tipo_colore_flusso == 5) {               
      // lilla
      colore_flusso = CRGB(200, 100, 255);                     //lilla neon
      //colore_flusso = CRGB(180, 80, 220);                      //lilla elettrico
      //colore_flusso = CRGB(150, 120, 255);                     //lavanda accesa
    }
    // FINIRE CON ALTRI ELSE !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  }
  // Modifica il colore del LED
  leds[puntatore_flusso] = colore_flusso;
}

int somma(int valore1, int valore2) {
  int risultato = valore1 + valore2;
  return risultato;
}

void lampeggio_segmenti()
{
  // Controlla se il contatore è arrivato al valore scelto (serve per temporizzare l'effetto)
  if (temporizzatore_lampeggio > 3) {
    // Esegui l'effetto
    // Imposta tutti i LED con il colore base
    fill_solid(leds, NUM_LEDS, colore_base);
    // Genera un numero casuale per puntare dove fare il verde
    long casuale = random(0, NUM_LEDS);
    // Modifica il colore del LED (piccola striscia da 5)
    for (uint8_t pezzo_lampeggiante = casuale;pezzo_lampeggiante<(casuale + 8);pezzo_lampeggiante++) {
      // Controlla se hai superato il numero di led
      if (pezzo_lampeggiante > (NUM_LEDS - 1)) {
        break;
      } else {
        leds[pezzo_lampeggiante] = colore_lampeggi;
      }
    }

    // Resetta il contatore
    temporizzatore_lampeggio = 0;
  }

}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}


// *************************************************************************************
void fadeInOut() {
    static uint8_t brightness = 0;
    static int8_t direction = 1;

    EVERY_N_MILLISECONDS(10) {
        brightness += direction;

        if (brightness == 0 || brightness == 255) {
            direction = -direction;
        }

        FastLED.setBrightness(brightness);
        fill_solid(leds, NUM_LEDS, CRGB::Purple);
        FastLED.show();
    }
}

// *************************************************************************************
void fadeToColor(CRGB targetColor, uint8_t fadeAmount) {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = blend(leds[i], targetColor, fadeAmount);
    }
}

// *************************************************************************************
