/**************************************************************************
Ejemplo para usar la pantalla OLED 128x32 pixeles usando I2C 
utilizando la librería <Adafruit_SSD1306.h>
 
 Para este ejemplo se utilizó un arduino UNO para comunicarse con la 
 pantalla OLED SSD1306 0.91" 

 Pines I2C ( UNO):      SDA => A4
                        SCL => A5

             Mega 2560: SDA => 20
                        SCL => 21

             Leonardo:  SDA => 2
                        SCL => 3

 Autor: Uriel Lomelí. Julio 2025. Mazatlán, Sinaloa (MX).

 La líbería y mas información de ella en => https://www.adafruit.com

 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Ancho en pixeles de la pantalla OLED
#define SCREEN_HEIGHT 32 // Alto en pixeles de la pantalla OLED
#define OLED_RESET     -1 // Pin de reset (-1) si la pantalla no tiene pin de reset
#define SCREEN_ADDRESS 0x3C // Dirección de pantalla; 0x3C para 128x32, 0x3D para 128x64


// Creación del objeto "display" con la clase Adafruit_SSD1306, &Wire indica que se usará I2C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// Mapas de bits donde se "dibujan" objetos de 16x16 llamadas logo_1, logo_2 y logo_3; 
// PROGMEM indica que los mapas de bits se grabaran en la memoria Flash

// Dibujo 1 en mapa de bits 16x16 

static const unsigned char PROGMEM logo_1[] =
{ 0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00011000, 0b00011000,
  0b00000100, 0b00100000,
  0b00000100, 0b00100000,
  0b00011111, 0b11111000,
  0b00111111, 0b11111100,
  0b01100111, 0b11100110,
  0b11111111, 0b11111111,
  0b11111111, 0b11111111,
  0b10011111, 0b11111001,
  0b10011111, 0b11111001,
  0b00010000, 0b00001000,
  0b00001110, 0b01110000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000 };

// Dibujo 2 en mapa de bits 16x16  

  static const unsigned char PROGMEM logo_2[] =
{ 0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b11111000,
  0b00000011, 0b11000100,
  0b00001111, 0b11110010,
  0b00011111, 0b11111000,
  0b00001111, 0b00000000,
  0b00000111, 0b11100000,
  0b00000111, 0b11100000,
  0b00001111, 0b11110000,
  0b00011111, 0b11111000,
  0b00011111, 0b11111000,
  0b00010000, 0b00001000,
  0b11110000, 0b00001111,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000 };

// Dibujo 3 en mapa de bits 16x16

  static const unsigned char PROGMEM logo_3[] =
{ 0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00111001, 0b10011100,
  0b00000101, 0b10100000,
  0b00000010, 0b01000000,
  0b00000101, 0b10100000,
  0b00000010, 0b01000000,
  0b01010101, 0b10101010,
  0b10001010, 0b10100001,
  0b01000101, 0b01010010,
  0b10010101, 0b10101001,
  0b00101000, 0b01010100,
  0b00010100, 0b00101000,
  0b10101010, 0b01010101,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000 };


// Inicialización 

void setup() {
  Serial.begin(9600);  // Inicializa el puerto serie

  // SSD1306_SWITCHCAPVCC = genera el voltaje del display de 3.3V internamente 
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // "Si" la OLED no se inicializa correctamente 
    Serial.println(F("SSD1306 allocation failed"));          // imprime por el puerto serie que falló 
    for(;;);                                                 // Se queda en este ciclo de forma inderetminada 
  }
  
  // Si la OLED se inicalizó correctamente
  display.display();  // Imprime en la OLED lo que este guardado en el Buffer, en este caso el logo de Adafruit
  delay(1000); // Espera 1 segundo

//*************************** Presentacion ************************************//
// Se hace una impresión en la OLED de texto sobre el proyecto, una presentación
  display.clearDisplay();              // Borra el display; se usa para limpiar pantalla e imprimir algo nuevo
  display.setTextSize(1);              // Tamaño de texto, existen tamaños 1, 2 y 3
  display.setTextColor(SSD1306_WHITE); // Seleccion de color, en esta OLED solo hay color blanco, SSD1306_WHITE <= 1, SSD1306_BLACK <= 0
  display.setCursor(0,0);              // Se posiciona el cursor, (x,y) siendo (0,0) el pixel de la esquina superior izquierda
  display.println("Proyecto: OLED");   // Se carga el texto en el buffer de la OLED 
  display.setCursor(0,10);             // Se cambia la posicion del cursor 
  display.println("Nombre: Uriel Engine"); // Se carga el texto en el buffer de la OLED 
  display.setCursor(0,20);             
  display.println("Lugar: Mazatlan, Sin");
  display.display();                    // Se imprime en pantalla todo lo cargado en el buffer de la OLED
  delay(3000);                          // Espera de 3 segundos
//*****************************************************************************//

}

//   Loop que se repetirá de forma indefinida 

void loop() {

//*************************** Dim *********************************************//
// .dim() se usa para bajar el brillo de la OLED, por default usa 1 que es el modo brillante, con 0 se baja un poco la intencidad

  display.dim(0);                    // Se usa 0 para poner el brillo de la OLED al maximo (valor por defecto)
  display.clearDisplay();            
  display.setCursor(0,0);
  display.println("display.dim(0)"); // Carga en el buffer el texto que indica la instrucción para observarla en tiempo de ejecución
  display.setCursor(55,16);
  display.println("Dim 0");          // Carga en el buffer un texto de prueba solo para observar el cambio de dim 1 a dim 0
  display.display();                 // Imprime en la OLED lo que esté en su buffer
  delay(3000);                       // Espera de 3 segundos

  display.dim(1);                   // Se usa 1 para bajar le brillo de la OLED 
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.dim(1)");
  display.setCursor(55,16);
  display.println("Dim 1");
  display.display();
  delay(3000);

  display.dim(0);                   // Volvemos al brillo por defecto 

//*****************************************************************************//

//*************************** Tamaños de texto ********************************//
// setTextSize() nos sirve para elegir el tamaño del texto, pudiendo ser 1 el mas pequeño, 2 grande y 3 mas grande
// Si no usamos la instrucción automaticamente tomará el valor de 1

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.setTextSize(1)"); // Se varga al bufer el texto que representa la instruccion
  display.setCursor(50,18);
  display.println("chico");                  // No es necesario usar setTextSize(1) ya que por defecto tiene ese tamaño
  display.display();
  delay(3000);

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.setTextSize(2)"); // Se carga el texto al buffer con tamaño "1"
  display.setTextSize(2);                    // Se cambia  el tamaño del texto a "2"
  display.setCursor(18,12);
  display.println("mediano");                // Se carga el texto al buffer con tamaño "2"
  display.display();                         // Imprime en la OLED un texto de tamaño 1 y el otro con tamaño 2 
  delay(3000);

  display.clearDisplay();
  display.setTextSize(1);                    // Se vuelve al tamaño "1"
  display.setCursor(0,0);
  display.println("display.setTextSize(3)");
  display.setTextSize(3);                    // Se cambia a tamaño "3" 
  display.setCursor(8,9);
  display.println("grande");
  display.display();                         // Imprime en la OLED un texto de tamaño 2 y el otro con tamaño 3 
  delay(3000);
  
//*****************************************************************************//


//*************************** Invert Display **********************************//
// invertDisplay() como su nombre lo indica, invierte la OLED, los pixeles que normalmente estarían apagados (en 0) cambian a
// encendido (1) y viceverza, es decir en vez de tener texto y pixeles activos brillando en blanco y el fondo apagado ahora
// tendremos el texto y pixeles activos apagados o en "negro" y el fondo activado o "blanco"

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("display.invertDisplay(0)");
  display.setCursor(50,16);
  display.println("Normal");                   
  display.display();                         // Se imprime normalmente un texto para tenerlo como referencia 
  delay(3000);

  display.invertDisplay(1);                  // Se inverten los valores de la OLED para cambiar 0 por 1 y viceversa 
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("display.invertDisplay(1)");
  display.setCursor(45,16);
  display.println("Invertido");
  display.display();                         // Se imprime en pantalla para observar el cambio
  delay(3000);

  display.invertDisplay(0);                  // Regresamos al modo normal "0"

//*****************************************************************************//

//*************************** Draw Pixel **************************************//
// drawPixel() nos sirve para imprimir un solo pixel en un punto de la OLED indicado por "x" y "y"
// drawPixel(x, y, color)   

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.drawPixel(64,18,SSD1306_WHITE)");  
  display.drawPixel(64, 18, SSD1306_WHITE);  // Se carga el encendido de un punto en la pantalla (pixel) en el buffer
  display.display();                         // Se imprime el pixel
  delay(4000);

//*****************************************************************************//

//*************************** Dibujar formas **********************************//
// Para dibujar formas tenemos una serie de herramientas que nos ayudan a imprimir desde líneas hasta figuras básicas

// drawFastHLine(x, y, ancho en pixeles); dibuja una línea horizontal en la posición de x, y con un ancho determinado de pixeles

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.drawFastHLine(61,24,6,SSD1306_WHITE)");
  display.drawFastHLine(60, 24, 8, SSD1306_WHITE);     // dibuja una línea horizontal en la posicion x=60, y=32 con un ancho de 8 pixeles
  display.display();
  delay(3000);


// drawFastVLine(x, y, alto en pixeles); dibuja una línea vertical en la posición de x, y con un alto determinado de pixeles
  
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.drawFastVLine(61,24,6,SSD1306_WHITE)");
  display.drawFastVLine(64, 24, 8, SSD1306_WHITE);     // dibuja una línea vertical en la posición x=64, y=24 con una altura de 8 pixeles
  display.display();
  delay(3000);

// drawLine(x0, y0, x1, y1, color); dibuja una línea que inicia en (x0, y0) y termina en (x1, y1)

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.drawLine(60,24,60,32,SSD1306_WHITE)");
  display.drawLine(60, 24, 68, 32, SSD1306_WHITE);  // dibuja una línea que inicia en (60,24) y termina en (68,32)
  display.display();
  delay(3000);

// drawRect(x, y, ancho, alto, color); dibuja un rectángulo que inicia en la posicón (x, y) de un alto y ancho especifico

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.drawRect(60,20,10,8,SSD1306_WHITE)");
  display.drawRect( 60, 20, 10, 8, SSD1306_WHITE);  // dibuja rectangulo que inicia en la posición (60, 20) de ancho 10 y altura 8
  display.display();
  delay(3000);  

// fillRect(x, y, ancho, alto, color); dibuja un rectángulo sólido que inicia en la posicón (x, y) de un alto y ancho especifico

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.fillRect(60,20,10,8,SSD1306_WHITE)");
  display.fillRect(60, 20, 10, 8, SSD1306_WHITE);   // dibuja rectangulo sólido que inicia en la posición (60, 20) de ancho 10 y altura 8
  display.display();
  delay(3000);

// drawCircle(x, y, r, color); dibuja un circulo con centro en la posicón (x, y) con un radio en pixeles "r" 

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.drawCircle(64,16,5,SSD1306_WHITE)");
  display.drawCircle(64, 24, 5, SSD1306_WHITE);   // dibuja un circulo con centro en la posición (64, 24) con un radio de 5 pixeles
  display.display();
  delay(3000);

// fillCircle(x, y, r, color); dibuja un circulo sólido con centro en la posicón (x, y) con un radio en pixeles "r" 

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.fillCircle(64,16,5,SSD1306_WHITE)");
  display.fillCircle(64, 24, 5, SSD1306_WHITE);   // dibuja un circulo sólido con centro en la posición (64, 24) con un radio de 5 pixeles
  display.display();
  delay(3000);

// drawTriangle(x0, y0, x1, y1, x2, y2, color); dibuja un triangulo entre los puntos (x0, y0), (x1, y1) y (x2, y2)

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.drawTriangle(64,30,80,30,72,20,SSD1306_WHITE)");
  display.drawTriangle(64, 30, 80, 30, 72, 20, SSD1306_WHITE); // dibuja un triangulo entre los puntos (64, 30), (80, 30) y (72, 20)
  display.display();
  delay(3000);

// fillTriangle(x0, y0, x1, y1, x2, y2, color); dibuja un triangulo sólido entre los puntos (x0, y0), (x1, y1) y (x2, y2)

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.fillTriangle(64,30,80,30,72,20,SSD1306_WHITE)");
  display.fillTriangle(64, 30, 80, 30, 72, 20, SSD1306_WHITE);   // dibuja un triangulo sólido entre los puntos (64, 30), (80, 30) y (72, 20)
  display.display();
  delay(3000);

// drawRoundRect(x, y, ancho, alto, r, color); Dibuja un rectangulo con las esquinas redondeadas con un radio "r"

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.drawRoundRect(80,20,20,10,3, SSD1306_WHITE)");
  display.drawRoundRect(80, 20, 20, 10, 3, SSD1306_WHITE);   // Dibuja un rectángulo que inicia en (80, 20), ancho 20, alto 10 y bordes redondeadons con r = 3
  display.display();
  delay(3000);

// fillRoundRect(x, y, ancho, alto, r, color); Dibuja un rectangulo sólido con las esquinas redondeadas con un radio "r"

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("display.fillRoundRect(80,20,20,10,3, SSD1306_WHITE)");
  display.fillRoundRect(80, 20, 20, 10, 3, SSD1306_WHITE);   // Dibuja un rectángulo sólido que inicia en (80, 20), ancho 20, alto 10 y bordes redondeadons con r = 3
  display.display();
  delay(3000);

//*****************************************************************************//


//******************************** Dibujar bitmap *****************************//
// Para poder dibujar cosas más complejas podemos usar los mapas de bits o bitmaps donde podemos crear alguna matríz con valores
// binarios para crear alguna forma o dibujo; para este ejemplo se crearon 3 (logo_1, logo_2 y logo_3) que se pueden ver
// al inicio del código. Son 3 bitmaps de 16x16 que emulan la forma de algunos personajes de juegos de los 70's/80's.
// para imprimir un mapa de bits primero se posiciona el cursos en la posición deseada u posteriormente se usa drawBitmap.

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Imprimir mapas de bits");
  display.setCursor(0,9);
  display.println("display.drawBitmap()");
  display.display();
  delay(2000);

// drawBitmap(x, y, nombre_del_bitmap, ancho, alto, color); dibuja en la posición (x, y) el bitmap indicado el nombre, la anchura
// y altura

  display.clearDisplay();
  display.setCursor(0,0);
  display.drawBitmap(20, 12, logo_1, 16, 16, WHITE);   // dibuja la imagen logo_1
  display.drawBitmap(56, 12, logo_2, 16, 16, WHITE);   // dibuja la imagen logo_2
  display.drawBitmap(92, 12, logo_3, 16, 16, WHITE);   // dibuja la imagen logo_3 
  display.display();                                   // imprime en la OLED los bitmaps del buffer
  delay(2000);
 
//*****************************************************************************// 

//******************************** Scroll *************************************//
// En este apartado se utilizan los Scroll o desplazamientos a la derehca, izquierda, diagonal derecha y diagonal izquierda para 
// hacer una pequeña animación de los bitmaps, la librería maneja un concepto llamado "paginas" que indica grupos de pixeles 
// verticales de 8 bits, es decir que cada pagina esta compuesta por un grupo de pixeles de 8 bits de altura y del ancho de la pantalla. 
// para mover toda la pantalla compleda en este caso particular que es de 128x32 tenemos que indicar que moveremos 4 paginas,
// es decir 0x00, 0x01, 0x02 hasta 0x03, al ser grupos de 8 pixeles esto sería 4x8 = 32 (la altura de la pantalla completa).

// startscrollright(de esta página, a esta página); realiza un desplazamiento de las paginas seleccionadas hacia la derecha
  display.startscrollright(0x00, 0x03);  // de la página 0 a la 15 (todas)
  delay(4000);
  display.stopscroll();

// startscrollleft(de esta página, a esta página); realiza un desplazamiento de las paginas seleccionadas hacia la izquierda
  display.startscrollleft(0x00, 0x03);  // de la página 0 a la 15 (todas)
  delay(4000);
  display.stopscroll();

// startscrolldiagright(de esta página, a esta página); realiza un desplazamiento en dirección de diagonal derehca
  display.startscrolldiagright(0x00, 0x03);
  delay(4000);
  display.stopscroll();

// startscrolldiagleft(de esta página, a esta página); realiza un desplazamiento en direccion de diagonal izquierda
  display.startscrolldiagleft(0x00, 0x03);
  delay(4000);
  display.stopscroll();

//***************************************************************************//

}
