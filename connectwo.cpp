#include <ConnecTwo.h>

namespace tresc3
{
    ConnecTwo::ConnecTwo()
    {

    }

    ConnecTwo::ConnecTwo(int rxPin, int txPin)
    {
        _SoftSerial = new SoftwareSerial(rxPin, txPin);
        _SoftSerial->begin(115200);
    }
    
    ConnecTwo::~ConnecTwo()
    {

    }

    bool ConnecTwo::run(packet *result, uint8_t data)
    {
        if(_Machine.run(data))
        {
            *result = _Machine.getPacket();

            if(result->cmd == CMD_STATE_LINEAR)
            {

            }
            else if(result->cmd == CMD_STATE_ANGULAR)
            {

            }
            else if(result->cmd == CMD_STATE_IMU)
            {
                int dataImuRoll = 0;
                int dataImuPitch = 0;
                int dataImuYaw = 0;
                dataImuRoll = result->data[0];
                dataImuRoll |= (result->data[1] << 8);
                dataImuRoll |= (result->data[2] << 16);
                dataImuRoll |= (result->data[3] << 24);
                
                dataImuPitch = result->data[4];
                dataImuPitch |= (result->data[5] << 8);
                dataImuPitch |= (result->data[6] << 16);
                dataImuPitch |= (result->data[7] << 24);
                
                dataImuYaw = result->data[8];
                dataImuYaw |= (result->data[9] << 8);
                dataImuYaw |= (result->data[10] << 16);
                dataImuYaw |= (result->data[11] << 24);

                _imu.roll = (double)dataImuRoll / 1000.0;
                _imu.pitch = (double)dataImuPitch / 1000.0;
                _imu.yaw = (double)dataImuYaw / 1000.0;
            }

            return true;
        }
        return false;
    }
    
    bool ConnecTwo::setCmdVel(const cmdVel target)
    {
        uint8_t sendData[255] = {0,};
        _target = target;
        int size = makeCmdPacket(sendData);

        Serial.write(sendData, size);
    }
    
    int ConnecTwo::makeCmdPacket(uint8_t *data)
    {
        int targetLinearX = (int)(_target.linear.x * 1000);
        int targetAngluarZ = (int)(_target.angular.z * 1000);

        uint16_t length = 24;
        uint8_t checkSum = 0x00;
        data[0] = 0xFF;
        data[1] = 0xFF;
        data[2] = CMD_TARGET_ODOM;
        data[3] = (uint16_t)CMD_TARGET_ODOM >> 8;
        data[4] = length;
        data[5] = length >> 8;
        data[6] = targetLinearX;
        data[7] = targetLinearX >> 8;
        data[8] = targetLinearX >> 16;
        data[9] = targetLinearX >> 25;
        data[26] = targetAngluarZ;
        data[27] = targetAngluarZ >> 8;
        data[28] = targetAngluarZ >> 16;
        data[29] = targetAngluarZ >> 24;

        for(int i = 6; i < 30; i++)
            checkSum += data[i];
        data[30] = checkSum;

        return 31;
    }

    void ConnecTwo::printStatus()
    {
        Serial.println("connecTwo update state");
        Serial.print("roll: ");
        Serial.print(_imu.roll);
        Serial.print(", pitch: ");
        Serial.print(_imu.pitch);
        Serial.print(", yaw: ");
        Serial.println(_imu.yaw);
    }
}  // namespace tresc3