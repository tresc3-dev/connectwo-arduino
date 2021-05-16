#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__



namespace tresc3
{
    enum machineSequence
    {
        start, confirm, cmd1, cmd2, length1, length2, data, check,
    };

    struct packet{
        unsigned int cmd;
        unsigned int length;
        char data[255];
        char checkSum;
    };

    class StateMachine
    {
        public:
            StateMachine();
            ~StateMachine();

        private:
            int state;
            packet result;
            int dataCount;
        public:
            bool run(char data);
            void resetPacket();
            packet getPacket();
    };
}  // namespace tresc3
#endif // __STATEMACHINE_H__