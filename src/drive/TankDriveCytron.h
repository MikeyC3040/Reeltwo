#ifndef TankDriveCytron_h
#define TankDriveCytron_h

#include "drive/TankDrive.h"
#include "motor/CytronSmartDriveDuoDriver.h"

/**
  * \ingroup drive
  *
  * \class TankDrive
  *
  * \brief Base template of automatic forwarder from i2c to CommandEvent
  *
  *
  * \code
  * #include "drive/TankDrive.h"
  *
  * TankDrive tankDrive;
  * \endcode
  *
  */
class TankDriveCytron: public TankDrive, public CytronSmartDriveDuoDriver
{
public:
    /** \brief Constructor
      *
      * Only a single instance of WifiSerialBridge should be created per sketch.
      *
      * \param port the port number of this service
      */
    TankDriveCytron(byte address, HardwareSerial& serial,uint8_t initialByte, JoystickController& driveStick) :
        TankDrive(driveStick),
        CytronSmartDriveDuoDriver(address, serial, initialByte)
    {
    }

    virtual void setup() override
    {
        autobaud(true);
        CytronSmartDriveDuoDriver::stop();
    }

    virtual void stop() override
    {
        CytronSmartDriveDuoDriver::stop();
        TankDrive::stop();
    }

protected:
    virtual void motor(float left, float right, float throttle) override
    {
        left *= throttle;
        right *= throttle;
        MOTOR_DEBUG_PRINT("ST1: ");
        MOTOR_DEBUG_PRINT((int)(left * 127));
        MOTOR_DEBUG_PRINT(" ST2: ");
        MOTOR_DEBUG_PRINTLN((int)(right * 127));
        CytronSmartDriveDuoDriver::motor(left * 127, right*127);
    }
};
#endif
