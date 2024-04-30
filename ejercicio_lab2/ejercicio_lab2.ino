#include <LiquidCrystal.h>

// Define los pines para los botones y la pantalla LCD
const int ABCD_BUTTON = 2;
const int NUM_BUTTON = 3;
const int CONFIRM_BUTTON = 4;
const int ENTER_BUTTON = 7;
const int BACK_BUTTON = 5;
const int REGIS_BUTTON = 6; //  botón para mostrar el registro de usuarios
const int RS = 13;
const int EN = 12;
const int D4 = 11;
const int D5 = 10;
const int D6 = 9;
const int D7 = 8;

// Inicializa la pantalla LCD
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

String userInput = ""; // Variable para almacenar la entrada del usuario

// Usuarios y sus contraseñas
const String user1 = "Jean";
const String pass1 = "21ab1a";
const String user2 = "Damian";
const String pass2 = "5q12as";
const String user3 = "Jhojan";
const String pass3 = "abc123";

String loggedInUsers = ""; // Usuarios que han ingresado correctamente la contraseña

void setup() {
  // Inicializa la pantalla LCD
  lcd.begin(16, 2);
  // Configura los pines de los botones como entrada
  pinMode(ABCD_BUTTON, INPUT_PULLUP);
  pinMode(NUM_BUTTON, INPUT_PULLUP);
  pinMode(CONFIRM_BUTTON, INPUT_PULLUP);
  pinMode(ENTER_BUTTON, INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);
  pinMode(REGIS_BUTTON, INPUT_PULLUP); // Nuevo botón para mostrar el registro de usuarios
  
  updateDisplay();
}

void loop() {
  // Espera hasta que se presione un botón
  while (digitalRead(ABCD_BUTTON) == HIGH &&
         digitalRead(NUM_BUTTON) == HIGH &&
         digitalRead(CONFIRM_BUTTON) == HIGH &&
         digitalRead(ENTER_BUTTON) == HIGH &&
         digitalRead(BACK_BUTTON) == HIGH &&
         digitalRead(REGIS_BUTTON) == HIGH) {
    delay(50);
  }

  if (digitalRead(ABCD_BUTTON) == LOW) {
    // Maneja el botón alfabético
    char nextChar = userInput.length() == 0 ? 'a' : ((userInput[userInput.length() - 1] - 'a' + 1) % 26) + 'a';
    userInput = userInput.substring(0, userInput.length() - 1) + nextChar;
  } else if (digitalRead(NUM_BUTTON) == LOW) {
    // Maneja el botón numérico
    char nextNum = userInput.length() == 0 ? '0' : ((userInput[userInput.length() - 1] - '0' + 1) % 10) + '0';
    userInput = userInput.substring(0, userInput.length() - 1) + nextNum;
  } else if (digitalRead(ENTER_BUTTON) == LOW) {
    // Maneja el botón de confirmar contraseña
    if (userInput == pass1) {
      loggedInUsers += user1 + " ";
      lcd.clear();
      lcd.print("Bienvenido ");
      lcd.setCursor(0, 1);
      lcd.print(user1);
    } else if (userInput == pass2) {
      loggedInUsers += user2 + " ";
      lcd.clear();
      lcd.print("Bienvenido ");
      lcd.setCursor(0, 1);
      lcd.print(user2);
    } else if (userInput == pass3) {
      loggedInUsers += user3 + " ";
      lcd.clear();
      lcd.print("Bienvenido ");
      lcd.setCursor(0, 1);
      lcd.print(user3);
    } else {
      lcd.clear();
      lcd.print("CLAVE");
      lcd.setCursor(0, 1);
      lcd.print("incorrecta");
    }
    delay(2000); // Espera 2 segundos antes de limpiar la pantalla
    userInput = ""; // Limpia la entrada del usuario
    updateDisplay(); // Actualiza la pantalla
  } else if (digitalRead(CONFIRM_BUTTON) == LOW) {
    // Maneja el botón de confirmación
    userInput += 'a'; // Añade un símbolo para confirmar la selección
    updateDisplay();
    delay(200);
  } else if (digitalRead(BACK_BUTTON) == LOW) {
    // Maneja el botón de retroceso
    if (userInput.length() > 0) {
      userInput.remove(userInput.length() - 1);
    }
 } else if (digitalRead(REGIS_BUTTON) == LOW) {
    // Maneja el botón de mostrar registro de usuarios
    lcd.clear();
    lcd.setCursor(0, 0); // Establece el cursor en la primera línea
    lcd.print("ingresos:");

    // Desplaza la lista de usuarios en la segunda línea
    for (int i = 0; i < 16 + loggedInUsers.length(); i++) {
      lcd.clear();
      lcd.setCursor(0, 0); // Establece el cursor en la primera línea
      lcd.print("ingresos:");

      lcd.setCursor(0, 1); // Establece el cursor en la segunda línea
      lcd.print(loggedInUsers.substring(i, i + 16)); // Imprime la parte correspondiente de la cadena

      delay(700); // Espera 0.4 segundos para el desplazamiento
    }

    delay(2000); // Espera 2 segundos antes de limpiar la pantalla
    updateDisplay(); // Actualiza la pantalla
}

  updateDisplay(); // Actualiza la pantalla después de cada acción
  delay(200);
}



// Función para actualizar la pantalla LCD
void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CLAVE:");
  lcd.setCursor(0, 1);
  lcd.print(userInput);
}

