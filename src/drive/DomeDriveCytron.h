#ifndef DomeDriveCytron_h
#define DomeDriveCytron_h

#include "drive/DomeDrive.h"
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
class DomeDriveCytron : public DomeDrive, protected CytronSmartDriveDuoDriver
{
public:
    /** \brief Constructor
      *
      * Only a single instance of WifiSerialBridge should be created per sketch.
      *
      * \param port the port number of this service
      */
    DomeDriveCytron(byte address, Stream& serial, uint8_t initialByte, JoystickController& domeStick) :
        DomeDrive(domeStick),
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
        DomeDrive::stop();
    }

protected:
    virtual void motor(float m) override
    {
        static bool sLastZero;
        if (!sLastZero || m != 0)
        {
            VERBOSE_DOME_DEBUG_PRINT("ST: ");
            VERBOSE_DOME_DEBUG_PRINTLN((int)(m * 127));
            sLastZero = (abs(m) == 0);
        }
        CytronSmartDriveDuoDriver::motor(m * 127);
    }

    uint16_t fBaudRate;
};
#endif
