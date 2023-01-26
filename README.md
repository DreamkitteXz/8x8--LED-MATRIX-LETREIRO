<h2 align='center'>
  Testando a plataforma Wokwi 
</h2>
<h3>
  Visão geral 
</h3>
<p>
  <p></p>
<p>Você irá brincar com a Matriz de LED Escrevendo alguma coisa e aparecendo no Letreiro.</p>
</p>
<p>
Voce ira aprender:
<ul>
    <li>Instalar uma biblioteca no Arduino IDE.</li>  
</ul>

  <h2 align='center'>Começando...</h2>
      <h3>Componentes utilizados</h3>
      <ul>
    <li>8x24 LED Dot Matrix with MAX7219 Controller<p align='center'><img src="https://raw.githubusercontent.com/gist/DreamkitteXz/f73cf72a38741b16a3b242c1f9c6d438/raw/3cb9e826bdac35c51cb7cfd657911a2fa0955045/download.svg" alt="Screen" width="389" height="72"></p></li> 
    <li>Arduino Uno.<p align='center'><img src="https://upload.wikimedia.org/wikipedia/commons/7/7c/Arduino_Uno_%28Versi%C3%B3n_Inform%C3%A1tica%29.png" alt="Screen" width="417" height="212"></p></li> 
</ul>
    <h3>Conexões</h3>
      <p>As conexões do outro lado do módulo do Led não serão feitas, pois nosso objetivo é usar apenas uma matriz de 8x8.</p>
      <table border="3" align='center'>
    <tr>
        <td><b>Pinos Led</b></td>
        <td><b>Pinos Arduino</b></td>
    </tr>
    <tr>
        <td align='center'>VCC</td>
        <td align='center'>5V</td>
    </tr>
    <tr>
        <td align='center'>GND</td>
        <td align='center'>GND</td>
    </tr>
    <tr>
        <td align='center'>DIN</td>
        <td align='center'>Pin 11</td>
    </tr>
    <tr>
        <td align='center'>CS</td>
        <td align='center'>pin 10</td>
    </tr>
    <tr>
        <td align='center'>CLK</td>
        <td align='center'>pin 13</td>
    </tr>
</table>
<h3 align='center'>Letreiro</h3>
<p> Logo abaixo tem o código de um letreiro que mostra um o texto que você quiser, mas antes de executarmos esse código temos que instalar a biblioteca <code>Max72xxPanel.h</code> para o código funcionar. Para fazer isso é muito facil, basta você clicar <a href="https://embarcados.com.br/wokwi-simulador-de-esp32/#O-que-e-o-Wokwi
">nesse link</a> para baixar a pasta compactada da biblioteca, uma vez feito isso vamos para o Arduino IDE e procurar por <code>Sketch</code> > <code>Incluir bibliioteca</code> > <code>Adicionar .ZIP</code> .
</p>
<p align='center'><img src="c.png" alt="Screen" width="641" height="357"></p>
<p> Procure pela pasta baixada e clique em <code>abrir</code></p>
<p align='center'><img src="pl.png" alt="Screen" width="800" height="650"></p>
<p> Agora iremos instalar outra biblioteca <code> Adafruit GFX Library</code>, dessa vez iremos utilizar outra forma de instalar, basta clicar em <code>Ferramentas</code> > <code>Gerenciar bibliotecas</code>.
</p>
<p align='center'><img src="K.png" alt="Screen" width="584" height="408"></p>
<p> Procure por <code> Adafruit GFX Library</code> e instale.</p>
<p align='center'><img src="sa.png" alt="Screen" width="799" height="464"></p>
<p> Pronto agora uma vez que as conexões estão feitas execute o código abaixo:</p>

<p align='center'><pre><code >
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
}</code></pre></p>
<p>Espere o seguinte resultado:</p>
<p align='center'><img src="ETEFMC.gif" alt="Screen" width="600" height="338">
<h3 align='center'>
  Testando na prática
</h3>
<p>
  <p>Agora vamos testar na prática o que fizemos no simulador, iremos precisar dos mesmos componentes, serão as mesmas conexões e utilizaremos o Arduino IDE.</p>
<p>1. Monte seu circuito na prática fazendo as mesmas conexões</p>
<p>2. Copie e cole o código para o Arduino IDE.</p>
<p>3. Selecione a porta <code>COM</code></p>
<p>4. Execute o código.</p>
<p align='center'><img src="Arduinoide.gif" alt="Screen" width="600" height="337">
<p> Espere o seguinte resultado:</p>
<p align='center'><img src="Happy.gif" alt="Screen" width="600" height="1067"></p>
<h3 align='center'>
  Explicando o código
</h3>
<h4 align='center'>Usando as funções da biblioteca LedControl</h4>
<p>A maneira mais fácil de exibir algo na matriz de pontos é usando as funções <code>setLed()</code> , <code>setRow()</code> ou <code>setColumn()</code> . Estas funções permitem controlar um único led, uma linha ou uma coluna de cada vez.</p>
<p>Aqui estão os parâmetros para cada função:</p>
<b>setLed(addr, linha, coluna, estado)</b>
<ul>
    <li><code>addr</code> é o endereço da sua matriz, por exemplo, se você tiver apenas 1 matriz, o int addr será zero.</li>  
    <li><code>linha</code> é a linha onde o led está localizado.</li>  
<li><code>col</code> é a coluna onde o led está localizado</li>  
<li><code>Estado</code> <ul><li>É verdadeiro ou 1 se quiser acender o led</li><li>É falso ou 0 se você quiser desligá-lo</li></ul></li> 
</ul>
<b>setRow(addr, linha, valor)</b>
<p></p>
<b>setCol(addr, coluna, valor)</b>

<h4 align='center'>byte arrays</h4>
<img src="Untitled.png" alt="Screen" width="964" height="150">
<p> Essas Arrays de Bytes são o que informa os pontos gráficos(Led's) que serão acionados no Display </p>
<p align='center'><img src="jhg.png" alt="Screen" width="222" height="166"></p>
<p><code>lc.shutdown(0,false);</code> Liga o Display.</p>
<p><code>lc.setIntensity(0,8);</code> Configura o brilho do Display, sendo o máximo 15 e o mínimo 0.</p>
<p><code>lc.clearDisplay(0);</code> Limpa o display após liga-lo.</p>
<p align='center'><img src="sfes.png" alt="Screen" width="232" height="267"></p>
<p><code>void drawFaces(){</code> é uma função void onde mostra a cara triste, neutra e feliz.</p>
<p><code>lc.setRow(0,0,sf[0]);</code> A função setRow(addr,row,value) recebe 3 argumentos. O primeiro é o endereço do dispositivo. O segundo é a linha que precisa ser atualizada e o terceiro é o valor a ser definido para esta linha.</p>
<p><code>delay(delaytime);</code> Tempo de delay, nesse caso 1 segundo entre as faces, foi atribuido á uma variável global mas poderia ser o valor numérico em milissegundos normal.</p>
<p align='center'><img src="Loop.png" alt="Screen" width="155" height="105"></p>
<p><code>void loop(){</code> Executa o código em loop.</p>
<p><code>drawFaces();</code> Executa o código que está na função que acabamos de criar <code>void drawFaces(){</code>.</p>