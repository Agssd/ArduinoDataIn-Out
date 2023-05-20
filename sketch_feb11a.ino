
#define LED_1 3
#define LED_2 5
#define LED_3 6
#define POT_1 A0
#define POT_2 A1
#define POT_3 A3

unsigned char serialValues[3]; 
long item = 0; // Номер элемента
long power = 0; // Яркость светодиода
int comNum = 0; // Номер команды
/************************************************/
void recieveData() // Функция для получения данных
{
  if (Serial.available() > 0) // Если в буфере есть данные
  {
    int serialIndex = 0; // Стартовый индекс
    while (Serial.available() > 0) // Пока во входном буфере есть данные
    {
      serialValues[serialIndex] = Serial.read(); 
      serialIndex++; // Увеличение индекса на 1
    }
    comNum = (int)(serialValues[0]); // Считываем номер команды
    item = (long)(serialValues[1]); // Получаем номер элемента
    if(comNum == 1) // Если номер команды равен 1
     power = (long)(serialValues[2]);
    delay(100);
   switch (item) {
    case 1:
      if(comNum == 0) // Если номер команды равен 0
        sendData(item, analogRead(POT_1)); // Отправляем данные
      if(comNum == 1) // Если номер команды равен 1
        analogWrite(LED_1,power); // Включаем светодиод
      break;
    case 2:
      if(comNum == 0) // Если номер команды равен 0
        sendData(item, analogRead(POT_2)); // Отправляем данные
      if(comNum == 1) // Если номер команды равен 1
        analogWrite(LED_2,power); // Включаем светодиод
        break;
    case 3:
      if(comNum == 0) // Если номер команды равен 0
        sendData(item, analogRead(POT_3)); // Отправляем данные
      if(comNum == 1) // Если номер команды равен 1
        analogWrite(LED_3,power); // Включаем светодиод
      break;
    default:
      break;
    }
  }
}

void sendData(int num, unsigned long int message) // Функция для отправки данных
{
  unsigned char byteArray[3]; // Создание массива для отправки данных
  byteArray[0] = (int)((num & 0XFF)); // Записываем в массив номер элемента
  /* Записываем значение кода потенциометра. Поскольку оно изменяется в
  пределах 0–1023, требуется 2 байта. Для передачи используем битовый сдвиг*/
  byteArray[1] = (int)((message & 0XFF));
  byteArray[2] = (int)((message >> 8) & 0XFF);
  Serial.write(byteArray,3); // Отправляем данные компьютеру
}
/************************************************/
void setup() {
  Serial.begin(9600);
  pinMode(LED_1, OUTPUT); // установить режим работы порта на «Выход»
  pinMode(LED_2, OUTPUT); // установить режим работы порта на «Выход»
  pinMode(LED_3, OUTPUT); // установить режим работы порта на «Выход»
//  pinMode(LED_4, OUTPUT); // установить режим работы порта на «Выход»
//  pinMode(LED_5, OUTPUT); // установить режим работы порта на «Выход»
  while (!Serial) {
   ; // Ждем пока не установится соединение с последовательным портом
  }
}
/************************************************/
// Цикл работы программы
void loop() {
  recieveData(); // Принимаем данные
  delay(5); // Пауза в 5 мс
}
