#ifndef __CONNECTWO_H__
#define __CONNECTWO_H__
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <StateMachine.h>

#include <tresc3TypeDef.h>

namespace tresc3
{
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
        SoftwareSerial *SoftSerial;
        StateMachine Machine;
    public:
        bool run(packet *result);
        void printStatus();
};
}   // namespace connectwo

#endif // __CONNECTWO_H__