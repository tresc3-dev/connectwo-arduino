#include <ConnecTwo.h>

namespace tresc3
{
    ConnecTwo::ConnecTwo()
    {

    }

    ConnecTwo::ConnecTwo(int rxPin, int txPin)
    {
        SoftSerial = new SoftwareSerial(rxPin, txPin);
        SoftSerial->begin(57600);
    }
    
    ConnecTwo::~ConnecTwo()
    {

    }

    bool ConnecTwo::run(packet *result)
    {
        if(SoftSerial->available() > 0)
        {
            char data = SoftSerial->read();
            if(Machine.run(data))
            {
                *result = Machine.getPacket();
            }
        }
    }

    void ConnecTwo::printStatus()
    {
        Serial.println("connecTwo status");
    }
}  // namespace tresc3