int stop_c = 0;//Variable que permite saber si se presionó el botón para controlar la fuga y detener la alarma. Inicia en 0 para ingresar en la primera ejecución
int check;//Variable que lee el estado del botón
int Valor;//Lectura del valor de tensión del sensor
const int ref = 800;//Valor de referencia que se asocia al sensor sin fugas
void setup() {
  pinMode(3, INPUT);//Asignación del pin 3 como entrada
  pinMode(4, OUTPUT);//Asignación del pin 4 como salida
  pinMode(7, INPUT);//Asignación del pin 7 como entrada
}
void loop() {
  Valor = analogRead(3);//Lectura del valor de la tensión actual en el sensor
  while (Valor > ref){//Mientras se detecte un cambio en el valor de la referencia
    tone(4,350);//Alerta sonora en la salida
    check = digitalRead(7);//Lectura del estado del botón
    if (check == HIGH){//Si se presiona el botón
      stop_c = 1;//Cambio que permite conocer que el botón de revisión ya fue presionado
      noTone(4);//Apaga la alerta sonora en la salida
      break;//Rompe el ciclo
    }
    Valor = analogRead(3);//vuelve a leer el valor para confirmar si debe entrar al ciclo o no
  }
  check = digitalRead(7);//Lectura del estado del botón en caso de que se estabilice
  if (check == HIGH){//Si se presiona el botón cuando está estable
    noTone(4);//Detiene el tono en caso de que la alarma esté funcionando (no tiene efecto si se presiona sin que se haya destabilizado)
    stop_c == 1;//Indica que se presionó el botón
  }
  while (stop_c == 1){//Mientras el botón esté presionado
    Valor = analogRead(3);//Lectura del valor de la tensión actual en el sensor
    if (Valor <= ref){//Si el valor se encuentra en el estado estable
      tone(4,350,200);//Tono con una duración definida para indicar que se realizó correctamente la corrección
      stop_c = 0;//Reseteo del valor del botón presionado
      break;//Rompe ciclo
    }
  }
}

