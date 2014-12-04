/*

 Rainbowduino v3.0 Library examples : Mood Lamp 

*/

#include <Rainbowduino.h>


// HSV to RGB array generated using the following perl script

/*

#HSV2RGB.pl
use Graphics::Color::HSV;
use POSIX qw(ceil floor);

$red="";
$green="";
$blue="";

for($hu = 0; $hu <256 ; $hu=$hu+4)
{
my $color = Graphics::Color::HSV->new({ hue => $hu, saturation  => 1, value  => 1,});
$red.=ceil($color->to_rgb()->red * 255) . ',';
$green.=ceil($color->to_rgb()->green * 255) . ',';
$blue.=ceil($color->to_rgb()->blue * 255) . ',';
}

print "unsigned char RED[64] = {$red};";
print "\n";
print "unsigned char GREEN[64] = {$green};";
print "\n";
print "unsigned char BLUE[64] = {$blue};";
print "\n";

*/

unsigned char RED[64] = {255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,171,154,137,119,102,85,
68,51,34,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,35,52};

unsigned char GREEN[64] = {0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,170,154,136,120,102,86,68,52,34,18,0,0,0,0};

unsigned char BLUE[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,34,52,68,86,102,120,136,154,170,188,
204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};

String inputString = "";
boolean stringComplete = false;

void setup()
{
  Rb.init(); //initialize Rainbowduino driver
  Serial.begin(9600);
  inputString.reserve(200);
}

unsigned int z,x,y,r,g,b;
void loop()
{

  if (stringComplete) {
    Serial.println(inputString);
    // expects 255255255 type string
    r = inputString.substring(0,3).toInt();
    g = inputString.substring(3,6).toInt();
    b = inputString.substring(6,9).toInt();
    Serial.println(inputString.substring(6,9));

    inputString = "";
    stringComplete = false;
  }
    for(x=0;x<8;x++) {
      for(y=0;y<8;y++) {
       //Paint random colors
       //Rb.setPixelZXY(z,x,y,RED[i],GREEN[i],BLUE[i]); //uses R, G and B color bytes
       Rb.setPixelXY(x,y,r,g,b); //uses R, G and B color bytes
      }
    }
    delay(10);
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } 
  }
}