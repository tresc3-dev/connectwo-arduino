#include <StateMachine.h>
#include <string.h>

namespace tresc3
{
    StateMachine::StateMachine()
    {
        state = machineSequence::start;
    }
    StateMachine::~StateMachine()
    {

    }

    bool StateMachine::run(char data)
    {
        switch(state)
        {
            case machineSequence::start:
                resetPacket();
                bool isEndPacket = false;
                dataCount = 0;
                if(data == 0xFF)
                    state = machineSequence::confirm;
                else
                    state = machineSequence::start;
                break;
            case machineSequence::confirm:
                if(data == 0xFF)
                    state = machineSequence::cmd1;
                else
                    state = machineSequence::start;
                break;
            case machineSequence::cmd1:
                result.cmd = (unsigned int)data;
                break;
            case machineSequence::cmd2:
                result.cmd = result.cmd | (unsigned int)data << 8;
                break;
            case machineSequence::length1:
                result.length = (unsigned int)data;
                break;
            case machineSequence::length2:
                result.length = result.length | (unsigned int)data << 8;
                break;
            case machineSequence::data:
                result.data[dataCount++] = data;
                result.checkSum += data;
                if(dataCount == result.length)
                    state = machineSequence::check;
                break;
            case machineSequence::check:
                if(checkSum == data)
                    return true;
                state = machineSequence::start;
                break;
        }
        return false;
    }

    void StateMachine::resetPacket()
    {
        result.cmd = 0x0000;
        result.length = 0x0000;
        memset(result.data, 0, sizeof(result.data));
    }

    packet StateMachine::getPacket()
    {
        return result;
    }
}  // namespace tresc3 