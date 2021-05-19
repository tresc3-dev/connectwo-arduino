#include <connectwo.h>


tresc3::ConnecTwo controller(10, 11);

uint32_t nowTick = 0;
uint32_t pastTick = 0;

/* linear x y z angular x y z */
tresc3::cmdVel target{{1, 0, 0}, {0, 0, 0}};

tresc3::cmdVel target1{{1, 0, 0}, {0, 0, 0}};
tresc3::cmdVel target2{{ -1, 0, 0}, {0, 0, 0}};
tresc3::cmdVel target3{{1, 0, 0}, {0, 0, 0}};
tresc3::cmdVel target4{{2, 0, 0}, {0, 0, 0}};
tresc3::cmdVel target5{{0, 0, 0}, {0, 0, 3}};
tresc3::cmdVel target6{{0, 0, 0}, {0, 0, -3}};

int cnt = 0;

void setup()
{
  Serial.begin(57600);

  Serial.println("Tresc3 connectwo arduino example");
  Serial.println("https://www.github.com/tresc3-dev/connectwo-arduino");
  Serial.println("YeongJunKim");
}


void loop()
{
  nowTick = millis();
  if (nowTick - pastTick > 2000)
  {
    if (cnt == 0)
      controller.setCmdVel(target);
    else if (cnt == 1)
      controller.setCmdVel(target1);
    else if (cnt == 2)
      controller.setCmdVel(target2);
    else if (cnt == 3)
      controller.setCmdVel(target3);
    else if (cnt == 4)
      controller.setCmdVel(target4);
    else if (cnt == 5)
      controller.setCmdVel(target5);
    else if (cnt == 6)
      controller.setCmdVel(target6);
    cnt++;
    if(cnt == 7)
      cnt = 0;
  Serial.println("");
    pastTick = nowTick;
  }
  tresc3::packet result;
  if (Serial.available() > 0)
  {
    uint8_t data = Serial.read();
    if (controller.run(&result, data))
      controller.printStatus();
  }
}
