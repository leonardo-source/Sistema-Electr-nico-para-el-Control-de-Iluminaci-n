#include <Arduino.h>
#include <LiquidCrystal.h>

/*El código controla la iluminación de dos bombillos led por medio de dos fotorresistencias, cauando la intensidad lumínica 
  natural cae por debajo de cierto porcentaje se iluminaran los bombillos y por pantalla lcd se mostrará que bombillo está
  encendido y que porcentaje de iluminación natural esta recibiendo cada fotorresistencia*/

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; // los pines del lcd relacionado con los pines a conectar con arduino
LiquidCrystal lcd(12,11,5,4,3,2); //función para usar los pines de arduino con los pines del lcd 

/*inicializamos las variables*/
int sala_1= 0; // variable que almacenará el valor analógo por la fotoresistencia 1
int sala_2= 0; // variable que almacenará el valor analógo por la fotoresistencia 1
int led_sala_1= 9; //el pin 9 de arduino le asignamos un nombre led_sala_1
int led_sala_2= 10; //el pin 10 de arduino le asignamos un nombre led_sala_2

void setup(){
Serial.begin(9600); //Inicio comunicación con el monitor serial
lcd.begin(16, 2); //Inicio comunicación con la pantalla LCD

pinMode(A0, INPUT); // entrada análoga del fotosensor del salón 1
pinMode(A1, INPUT);// entrada análoga del fotosensor del salón 2
pinMode(led_sala_1, OUTPUT); // establece la salida en el pin 9 del arduino 
pinMode(led_sala_2, OUTPUT); // establece la salida en el pin 10 del arduino



/*la pantalla lcd es una matriz de 16 filas por 2 columnas, para ingresar un caracter se debe indicar las coordenadas 
  donde inicia el texto a ingresar
*/
lcd.setCursor(0, 0); //fijar un texto en la columna 0 y fila 0
lcd.print("SALA 1: ");


lcd.setCursor(0, 1); //fijar un texto en la columna o y fila 1
lcd.print("SALA 2: ");

}

void loop(){

  sala_1= analogRead(A0); //la variable tomará la lectura que arduino reciba en A0 que sería la intensidad de luz natural en el salón
  sala_2= analogRead(A1); //la variable tomará la lectura que arduino reciba en A1 que sería la intensidad de luz natural en el salón

  
 
  /* se usa la función map para reorganizar los datos de resolución de arduino 1023 bits en 100 bits de manera que se pueda 
     interpretar a manera de porcentaje donde 1023 es el 100% de AUSENCIA de luz    
  */
  
  //int porcentaje1= map(sala_1, 0, 1023, 0, 100);
  int porcentaje1= ((map(sala_1, 0, 1023, 0, 100)- 100) * -1);
  int porcentaje2= ((map(sala_2, 0, 1023, 0, 100)- 100) * -1);
  //int porcentaje2= map(sala_2, 0, 1023, 0, 100);

  
  // información enviada al monitor serial
  Serial.print("fotosensor 1: ");
  Serial.print(sala_1);
  Serial.print("  Porcentaje luz laboratorio 1: ");
  Serial.print(porcentaje1);
  Serial.print("%");
  Serial.println(" ");
  
  Serial.print("forosensor 2: ");
  Serial.print(sala_2);
  Serial.print("  Porcentaje luz laboratorio 2: ");
  Serial.print(porcentaje2);
  Serial.print("%");
  Serial.println(" ");
  Serial.println(" ");


  // se fija en la pantalla lcd el porcentaje de luz que incide sobre las fotoresistencias
  lcd.setCursor(8, 0);
  lcd.print(porcentaje1);
  lcd.print("%");
  lcd.print(" ");

  lcd.setCursor(8, 1);
  lcd.print(porcentaje2);
  lcd.print("%");
  lcd.print(" ");

  if (porcentaje1 > 59) // primer condicional el salón 1 se ilumina si la luz natural está por debajo del 60%
  {
    digitalWrite(9, LOW); //señal de bajo apaga el led

    // fijar texto en la pantalla lcd
    lcd.setCursor(13, 0);
    lcd.print("OFF");
    lcd.print(" ");
  }else{
    
    digitalWrite(9, HIGH);// se envía un alto en el caso contrario

    // fija información en la pantalla lcd
    lcd.setCursor(13, 0);
    lcd.print("ON");
    lcd.print(" ");
  }


  if (porcentaje2 > 39) // segundo condicional para el salón 2 se ilumina si la luz natural está por debajo del 40%
  {
    digitalWrite(10, LOW); // señal de bajo cuando es verdadero

    // fija información en la pantalla lcd
    lcd.setCursor(13, 1);
    lcd.print("OFF");
    lcd.print(" ");

  }else{
    digitalWrite(10, HIGH);// se envía un alto en el caso contrario

    // fija información en la pantalla lcd
    lcd.setCursor(13, 1);
    lcd.print("ON");
    lcd.print(" ");
  }
  
  delay(1000);

}
