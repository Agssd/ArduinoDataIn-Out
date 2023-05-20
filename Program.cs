using System;
using System.IO.Ports;
using System.Threading;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArduinoP
{
    class Program
    {

        static void Main(string[] args)
        {
            SerialPort serialPort = new SerialPort("COM3", 9600, Parity.None);
            serialPort.Open(); // Открываем последовательный порт
            serialPort.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

            Console.Write("Введите номер команды: ");
            string comNumStr = Console.ReadLine();
            Console.Write("Введите номер светодиода/резистора: ");
            string numStr = Console.ReadLine();
            int comNum = Convert.ToInt32(comNumStr);
            int num = Convert.ToInt32(numStr);
            int ledVal;

            byte[] data = new byte[3]; // Создание массива байт для отправки
            data[0] = Convert.ToByte(comNum); // Записываем в массив номер команды
            data[1] = Convert.ToByte(num);

            if (comNum == 1)
            {
                Console.Write("Введите яркость светодиода: ");
                string ledValStr = Console.ReadLine();
                ledVal = Convert.ToInt32(ledValStr);
                data[2] = Convert.ToByte(ledVal);
                serialPort.Write(data, 0, 3);
            }
            if (comNum == 0)
                serialPort.Write(data, 0, 2);
            Console.ReadKey();
            serialPort.Close();
        }
        private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            int count = sp.BytesToRead;
            if (count > 2) // Если количество байт на входе больше 0
            {
                byte[] data = new byte[count]; // Создаем массив байт
                sp.Read(data, 0, data.Length); // Считываем данные в созданный массив
                Console.Write("Номер элемента: ");
                Console.WriteLine(data[0]); // Выводим номер элемента
                Console.Write("Измеренное значение: ");
                Console.WriteLine((data[1] & 0XFF) | ((data[2] & 0XFF) << 8));
                sp.DiscardInBuffer();
            }
        }

    }
}
