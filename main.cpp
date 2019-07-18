#include <mbed.h>
#include <BNO080.h>
 
int main()
{
    Serial pc(USBTX, USBRX);
 
    // Create IMU, passing in output stream, pins, I2C address, and I2C frequency
    // These pin assignments are specific to my dev setup -- you'll need to change them
    BNO080 imu(&pc, D0, D1, D3, D4, 0x4a, 100000); 
 
    pc.baud(9600);
    pc.printf("============================================================\n");
 
    // Tell the IMU to report rotation every 100ms and acceleration every 200ms
    imu.enableReport(BNO080::ROTATION, 100);
    imu.enableReport(BNO080::TOTAL_ACCELERATION, 200);
 
    while (true)
    {
        wait(.001f);
        
        // poll the IMU for new data -- this returns true if any packets were received
        if(imu.updateData())
        {
            // now check for the specific type of data that was received (can be multiple at once)
            if (imu.hasNewData(BNO080::ROTATION))
            {
                // convert quaternion to Euler degrees and print
                pc.printf("IMU Rotation Euler: ");
                TVector3 eulerRadians = imu.rotationVector.euler();
                TVector3 eulerDegrees = eulerRadians * (180.0 / M_PI);
                eulerDegrees.print(pc, true);
                pc.printf("\n");
            }
            if (imu.hasNewData(BNO080::TOTAL_ACCELERATION))
            {
                // print the acceleration vector using its builtin print() method
                pc.printf("IMU Total Acceleration: ");
                imu.totalAcceleration.print(pc, true);
                pc.printf("\n");
            }
        }
    }
 
}
 
 
