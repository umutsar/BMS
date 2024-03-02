/*
  Project Name: [BMS]
  Description: [BMS (Battery Management System) Codes]
  Author: [Umut Sar]
  Email: [contact@umutsar.com]
  License: [MIT]
  GitHub: [github.com/umutsar]
  
  This code file is licensed under MIT.
*/

byte dataUart[64];
uint16_t cells[20];
uint16_t sumVoltage, soc, powerWatt, cellsVoltage[20], temps[4], maxTemp, current;
int count = 0;

int issue = 0;


void setup()
{
    Serial.begin(9600);
    Serial1.begin(9600);
}

void loop()
{

    for (int i = 0; i < 53; i++) {
        dataUart[i] = 0;
    }

    count = 0;

    while (Serial1.available() == 53) {
        for (int i = 0; i < 53; i++)
        {
            dataUart[i] = Serial1.read();
        }

        
        /* 
         * Control full data
        for(int i = 0; i < 53; i++) {
          Serial.print(dataUart[i]);
          Serial.print(" ");
        } 
    
        Serial.println(""); */


        sumVoltage = (dataUart[0] * 256 + dataUart[1]);
        soc = (dataUart[2] * 256 + dataUart[3]) / 10;
        powerWatt = (dataUart[4] * 256 + dataUart[5]) / 1000;

        maxTemp = dataUart[50] - 40;
        current = (dataUart[51] * 256 + dataUart[52]) / 63;

        for (int i = 0; i < 20; i++)
        {
            cells[i] = (dataUart[count + 6] * 256 + dataUart[count + 7]);
            count += 2;
        }

        for (int i = 0; i < 4; i++)
        {
            temps[i] = dataUart[i + 46] - 40;
        }
        if (temps[1] > 100) {
            issue++;
        }
        Serial.println("\n\n\n");

        Serial.println("******************* START ********************");
        Serial.print("Sum Voltage: ");
        Serial.println(sumVoltage);

        Serial.print("SOC: ");
        Serial.println(soc);

        Serial.print("Power Watt: ");
        Serial.println(powerWatt);

        Serial.print("Max Temp: ");
        Serial.println(maxTemp);

        Serial.print("Current: ");
        Serial.println(current);

        Serial.println("********** TEMPERATURE ***********");

        Serial.print("Temp 1: ");
        Serial.println(temps[0]);

        Serial.print("Temp 2: ");
        Serial.println(temps[1]);

        Serial.print("Temp 3: ");
        Serial.println(temps[2]);

        Serial.print("Temp 4: ");
        Serial.println(temps[3]);

        Serial.println("************* CELLS **************");

        for (int i = 0; i < 20; i++)
        {
            Serial.print(cells[i]);
            Serial.print(" ");
        }
        Serial.println(" ");
        Serial.println(issue);
    }
}
