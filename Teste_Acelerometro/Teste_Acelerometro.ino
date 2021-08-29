// Biblioteca para comunicação I2C
#include <Wire.h>
// Definindo os endereços I2C
#define MPU1 0x68
#define MPU2 0x69
// Variáveis para os valores dos sensores
float AcX1, AcX2, AcY1, AcY2, AcZ1, AcZ2, GirX1, GirX2, GirY1, GirY2, GirZ1, GirZ2;
float Temp1, Temp2;

void setup()
{
  // Começa a serial
  Serial.begin(9600);
  // Começa I2C
  Wire.begin(); 
  
  // Iniciando o primeiro MPU
  Wire.beginTransmission(MPU1); // Comunica com o primeiro MPU
  Wire.write(0x6B);
  Wire.write(0); // "Acorda" o primeiro MPU
  Wire.endTransmission(true); // Termina a transmissão

  // Iniciando o segundo MPU
  Wire.beginTransmission(MPU2); // Comunica com o segundo MPU
  Wire.write(0x6B);
  Wire.write(0); // "Acorda" o segundo MPU
  Wire.endTransmission(true); // Termina a transmissão
 
 
}
void loop()
{
  // Primeiro MPU
  Wire.beginTransmission(MPU1); // Começa a transmissao
  Wire.write(0x3B); // Registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU1,14,true); // Faz um "pedido" para ler 14 dados
  // Salva os dados nas variáveis certas
  AcX1 = Wire.read()<<8|Wire.read();
  AcY1 = Wire.read()<<8|Wire.read();
  AcZ1 = Wire.read()<<8|Wire.read();
  Temp1 = Wire.read()<<8|Wire.read();
  GirX1 = Wire.read()<<8|Wire.read();
  GirY1 = Wire.read()<<8|Wire.read();
  GirZ1 = Wire.read()<<8|Wire.read();
  Wire.endTransmission(true);

  // Segundo MPU
  Wire.beginTransmission(MPU2); // Começa a transmissao
  Wire.write(0x3B); // Registrador dos dados medidos (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU2,14,true); // Faz um "pedido" para ler 14 dados
  // Salva os dados nas variáveis certas
  AcX2 = Wire.read()<<8|Wire.read();
  AcY2 = Wire.read()<<8|Wire.read();
  AcZ2 = Wire.read()<<8|Wire.read();
  Temp2 = Wire.read()<<8|Wire.read();
  GirX2 = Wire.read()<<8|Wire.read();
  GirY2 = Wire.read()<<8|Wire.read();
  GirZ2 = Wire.read()<<8|Wire.read();

  // MPU1
  Serial.println("SENSOR 1");
  Serial.print("AcX1 = "); Serial.print(AcX1/16384);// Equação para giro em graus por segundo
  Serial.print(" | AcY1 = "); Serial.print(AcY1/16384);
  Serial.print(" | AcZ1 = "); Serial.print((AcZ1-5000)/16384);
  Serial.print(" | Temp1 = "); Serial.print(Temp1/340.00+36.53);// Equação da temperatura em Cº de acordo com o datasheet
  Serial.print(" | GirX1 = "); Serial.print(GirX1/250);// Equação para giro em graus por segundo
  Serial.print(" | GirY1 = "); Serial.print(GirY1/250);
  Serial.print(" | GirZ1 = "); Serial.println(GirZ1/250);
  // MPU2
  Serial.println("SENSOR 2");
  Serial.print("AcX2 = "); Serial.print(AcX2/16384);// Equação para giro em graus por segundo
  Serial.print(" | AcY2 = "); Serial.print(AcY2/16384);
  Serial.print(" | AcZ2 = "); Serial.print(AcZ2/16384);
  Serial.print(" | Temp2 = "); Serial.print(Temp2/340.00+36.53); // Equação da temperatura em Cº de acordo com o datasheet
  Serial.print(" | GirX2 = "); Serial.print(GirX2/250);// Equação para giro em graus por segundo
  Serial.print(" | GirY2 = "); Serial.print(GirY2/250);
  Serial.print(" | GirZ2 = "); Serial.println(GirZ2/250);

  delay(500);
}
