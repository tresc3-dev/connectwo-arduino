#include <connectwo.h>


tresc3::ConnecTwo controller(10,11);


int leftTurn = 4;
int rightTurn = 5;
int forward = 6;
int backward = 7;


double linear_x = 0;
double angluar_z = 0;

void setup()
{
  Serial.begin(9600);
}
uint32_t nowTick =0;
uint32_t pastTick = 0;
void loop()
{
  nowTick = millis();
  if(nowTick - pastTick > 1000)
  {
    Serial.println("arduino running");
    pastTick = nowTick;
  }
  tresc3::packet result;
  if(controller.run(&result))
  {
    controller.printStatus();
  }
}
