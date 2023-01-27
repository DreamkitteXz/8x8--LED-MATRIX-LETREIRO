#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Max72xxPanel.h"
int pinCS = 10; // Conecte CS a este pino, DIN(11) a MOSI e CLK(13) a SCK
int numberOfHorizontalDisplays = 1;
int numberOfVerticalDisplays = 3;


Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);


String txtDisplay = "ETEFMC";
int width = 5 + 1; // A largura da fonte é de 5 pixels


void setup()
{


matrix.setIntensity(15); // Use um valor entre 0 e 15 para brilho
matrix.setPosition(0, 0, 0); // A primeira exibição está em <0, 0>
matrix.setPosition(1, 0, 1); // A segunda tela está em <1, 0>
matrix.setPosition(2, 0, 2); // A terceira tela está em <2, 0>
matrix.setRotation(1);    // A mesma espera para a última exibição
matrix.fillScreen(LOW);
matrix.write();
delay(400);
matrix.print("ETE");
matrix.write();
delay(2000);
}


void loop()
{
for ( int i = 0 ; i < width * txtDisplay.length() + matrix.width() - 1 - 1; i++ )
{
matrix.fillScreen(LOW);


int letter = i / width;
int x = (matrix.width() - 1) - i % width;
int y = (matrix.height() - 8) / 2; // centraliza o texto verticalmente

while ( x + width - 1 >= 0 && letter >= 0 ) 
{
  if ( letter < txtDisplay.length() ) 
  {
    matrix.drawChar(x, y, txtDisplay[letter], HIGH, LOW, 1);
  }
  letter--;
  x -= width;
}

matrix.write(); // Envia bitmap para exibição
delay(100);

}
}