#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 26
#define SCL_PIN 25
#endif

MPU9250 mySensor;

uint8_t sensorId;
float aX, aY, aZ, aSqrt, gX, gY, gZ;
float acc_xcal, acc_ycal, acc_zcal, gyro_xcal, gyro_ycal, gyro_zcal;
float acc_x_out = 0, acc_y_out = 0, acc_z_out = 0, gyro_x_out = 0, gyro_y_out = 0, gyro_z_out = 0;

void read_data()
{
  mySensor.accelUpdate();
  aX = mySensor.accelX();
  aY = mySensor.accelY();
  aZ = mySensor.accelZ();
  aSqrt = mySensor.accelSqrt();

  mySensor.gyroUpdate();
  gX = mySensor.gyroX();
  gY = mySensor.gyroY();
  gZ = mySensor.gyroZ();
}

void setup() {
  while(!Serial);
  Serial.begin(115200);
  
#ifdef _ESP32_HAL_I2C_H_ // For ESP32
  Wire.begin(SDA_PIN, SCL_PIN); // SDA, SCL
#else
  Wire.begin();
#endif
  
  mySensor.setWire(&Wire);
  mySensor.beginAccel();
  mySensor.beginGyro();

  // You can set your own offset for mag values
  // mySensor.magXOffset = -50;
  // mySensor.magYOffset = -55;
  // mySensor.magZOffset = -10;
 
  sensorId = mySensor.readId();
  Serial.println("Calibration Started");
  for (int cal_int = 0; cal_int < 500; cal_int++)
  {
    read_data();
    gyro_xcal += gX;
    gyro_ycal += gY;
    gyro_zcal += gZ;
    acc_xcal += aX;
    acc_ycal += aY;
    acc_zcal += aZ;
    delay(10);
  }

  gyro_xcal /= 500;
  gyro_ycal /= 500;
  gyro_zcal /= 500;
  acc_xcal /= 500;
  acc_ycal /= 500;
  acc_zcal /= 500;

  Serial.println("Thank you for calibrating IMU");
}

void loop() {
  read_data();
  aX -= acc_xcal;
  aY -= acc_ycal;
  aZ -= acc_zcal;
  gX -= gyro_xcal;
  gY -= gyro_ycal;
  gZ -= gyro_zcal;

  acc_x_out = 0.3 * aX + 0.7 * acc_x_out;
  acc_y_out = 0.3 * aY + 0.7 * acc_y_out;
  acc_z_out = 0.3 * aZ + 0.7 * acc_z_out;
  gyro_x_out = 0.3 * gX + 0.7 * gyro_x_out;
  gyro_y_out = 0.3 * gY + 0.7 * gyro_y_out;
  gyro_z_out = 0.3 * gZ + 0.7 * gyro_z_out;

  Serial.println(String(millis()) + "," + String(acc_x_out) + "," + String(acc_y_out) + "," + String(acc_z_out) + "," + String(gyro_x_out) + "," + String(gyro_y_out) + "," + String(gyro_z_out));
  
  delay(20);
}
