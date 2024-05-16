

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Adafruit_GFX.h"// Hardware-specific library
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;

#define SERIALRX 53
#define SERIALTX 51

#include <SoftwareSerial.h>

SoftwareSerial mySerial(SERIALRX, SERIALTX); // RX, TX


// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define GRAY    0b0100001000001000

int W;  // largeur écran
int H;  // hauteur écran

int ymax=450;
#define Nmax 440
int xmax=Nmax;
int ymin=0;
int xmin=0;

int mx=30;
int my=40;
int w;
int h;

int  d[Nmax];

int xscale(float x)
{
  return (int)(w*x/xmax+mx);
}

int yscale(float y)
{
   return (int)(H-h*y/ymax-my);
}


int distance;
int x;
int xa;
int ya;
int kp;
int ki;
int kd;
int state;



void setup(void) {
    Serial.begin(115200);
    mySerial.begin(57600);
    
    
    uint16_t ID = tft.readID(); //
    //Serial.print("ID = 0x");
    //Serial.println(ID, HEX);
    if (ID == 0xD3D3) ID = 0x9481; // write-only shield

  tft.begin(ID);
  H = tft.width();
  W = tft.height();
  w=W-mx-10;   // largeur du graphe
  h=H-my-10;   // hauteur du graphe
  Serial.println(W);
  Serial.println(H);
  tft.fillScreen(BLACK);
  tft.setRotation(3);
  tft.setTextSize(3);
  tft.setCursor(30, 30);
  tft.setTextColor(WHITE);
  tft.println("Ball & Beam");
  tft.setCursor(30, 100);
  tft.setTextColor(RED);
  tft.println("(c) IETR 2023");
  delay(1000);
   tft.setTextSize(1);
   tft.fillScreen(BLACK);
   tft.drawFastHLine(mx,h+10,w,WHITE);
   tft.drawFastVLine(mx,yscale(ymax),h,WHITE);
   for (int i=10; i<=Nmax; i+=10) tft.drawFastVLine(xscale(i),10,h,GRAY);
   for (int i=50; i<=ymax; i+=50) tft.drawFastHLine(mx,yscale(i),w,GRAY);
    tft.drawFastHLine(mx,yscale(250),w,GREEN);



      
       //tft.fillRect(0, 48 + 63, wid, 100, BLUE);

       distance=0;
       x=0;
       xa=-1;
       kp=ki=kd=state=0;
       for (int i=0; i<Nmax; i++) d[i]=0;
       tft.setTextSize(3);
}

void grosPixel(int x,int y, int color)
{
  tft.drawPixel(x,y,color);
  tft.drawPixel(x-1,y,color);
  tft.drawPixel(x-1,y-1,color);
  tft.drawPixel(x+1,y,color);
  tft.drawPixel(x+1,y+1,color);
}
char s[40];
void printCoef()
{
  tft.fillRect(mx,h+11,w,40,BLACK);
  int d1kp=kp/100;
  int d2kp=(kp-d1kp*100);
  int d1kd=kd/100;
  int d2kd=(kd-d1kd*100);
  int d1ki=ki/100;
  int d2ki=(ki-d1ki*100);
  sprintf(s,"P %d.%d I %d.%d D %d.%d",d1kp,d2kp,d1ki,d2ki,d1kd,d2kd);
  tft.setCursor(mx,h+25);
  tft.print(s);
}

void loop(void) {
  if (mySerial.available())
  {
    char c=mySerial.read();
    if ((c>='0')&&(c<='9'))
    { 
      switch (state)
      {
        case 0: distance=distance*10+(c-'0'); break;
        case 1: kp=kp*10+(c-'0'); break;
        case 2: ki=ki*10+(c-'0'); break;
        case 3: kd=kd*10+(c-'0'); break;
      }
    }
    if (c==',') state++;
    if (c==10) {
      Serial.println(distance);
      Serial.println(kp);
      Serial.println(ki);
      Serial.println(kd);
      x++; 
      if (x>=xmax)
      {
        x=0;
       for (int i=0; i<Nmax; i++) grosPixel(xscale(i),d[i],BLACK);
       // tft.fillScreen(BLACK);
        tft.drawFastHLine(mx,h+10,w,WHITE);
        tft.drawFastVLine(mx,10,h,WHITE);
        for (int i=10; i<Nmax; i+=10) tft.drawFastVLine(xscale(i),10,h,GRAY);
        for (int i=50; i<ymax; i+=50) tft.drawFastHLine(mx,yscale(i),w,GRAY);
        tft.drawFastHLine(mx,yscale(250),w,GREEN);
      }
      int xx=xscale(x);
     
      if (distance>ymax) distance=ymax;
      if (distance<ymin) distance=ymin;
      int yy=yscale(distance);
      grosPixel(xx,yy,RED);
      d[x]=yy;
      //
      if (kp!=0)printCoef();
      distance=kp=ki=kd=state=0;
    }
    
  }
    
    
}
