#ifndef __CONNECTWO_H__
#define __CONNECTWO_H__
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <StateMachine.h>

#include <tresc3TypeDef.h>

namespace tresc3
{
    
struct linearVel
{
    double x;
    double y;
    double z;
};

struct angularvel
{
    double x;
    double y;
    double z;
};

struct euler
{
    double roll;
    double pitch;
    double yaw;
};

struct cmdVel
{
    linearVel linear;
    angularvel angular;
};

class ConnecTwo
{
    public:
        ConnecTwo();

        /*
         * @function ConnecTwo(int rxPin, int txPin)
         * @arguments
         * @rxPin: softwareSerial rxPin number
         * @txPin: softwareSerial txPin number
        */
        ConnecTwo(int rxPin, int txPin);
        ~ConnecTwo();
    private:
        euler _imu;
        cmdVel _target;
        
    private:
        SoftwareSerial *_SoftSerial;
        StateMachine _Machine;
    public:
        bool run(packet *result, uint8_t data);
        bool setCmdVel(const cmdVel target);

    public:
        int makeCmdPacket(uint8_t *data);      

        euler getImuData()
        {
            return _imu;
        }

        void printStatus();
};
}   // namespace connectwo

#endif // __CONNECTWO_H__