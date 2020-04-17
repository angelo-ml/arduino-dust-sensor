/* This program reads and stores the data from
   Sharp dust OPC sensor
   Author: Malandrakis Angelos // Date: 06/03/2019 //
   
   // Sensor Features //
   1. Sensor captures readings very 100ms
   2. Converts output voltage on mass density [ug/m3]
   3. It logs the data on the SD card only if mass density is greater than 0
   4. Renames old dataset files as "dataset_old.csv"
   5. Return smooth data on the serial monitor every 5s and keeps record of the captured data
*/

const int chipSelect = 10;

char filename[] = "dataset.csv";


// set time between readings ( in seconds )
const int timeRate = 1;
// set time between readings ( in seconds )

#include <SdFat.h>

SdFat sd;
SdFile logFile;

// initialization for the dust sensor
int measurePin = A5;
int ledPower = 9;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float voMeasured = 0.00;
float calcVoltage = 0.00;
float dustDensity = 0.00;
float uptime = 0.00;
float previousLogTime = 5.00;
float dustDensitySum = 0.00;
float dustDensityMean = 0.00;
int logCounter = 0;


void setup() {
  
  pinMode(ledPower, OUTPUT); // Led of the dust sensor
  delay(2000);
  
  if (!sd.begin(chipSelect)) {
    Serial.println("xxx SD card error.");
  } else {
    Serial.println("=== SD card OK.");
  }

  // Rename old dataset.csv file
  if (sd.exists(filename)) {

    int fileNum = 1;
    String tempString = String(fileNum);
    String main_name = "dataset_old";
    String extension = ".csv";
    String finalName = main_name + tempString + extension;
    char fname[60];
    finalName.toCharArray(fname,60);

    while (sd.exists(fname)) {
      fileNum = fileNum + 1;
      tempString = String(fileNum);
      finalName = main_name + tempString + extension;
      finalName.toCharArray(fname,60);
    }
    
    Serial.println("=== Rename old dataset file to " + finalName);
    sd.rename(filename, fname);
  }
}

void loop() {

  digitalWrite(ledPower, LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower, HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured * (5.0 / 1024);
  dustDensity = (0.986 * calcVoltage - 0.582) * 1000;

  
  //Get Data
  uptime = millis() / 1000.000;  // get uptime
  delay(100); // capture readings very 100ms (0.10secs)

  if (dustDensity > 0) {
    
    // open file
    if (!logFile.open(filename, O_RDWR | O_CREAT | O_AT_END)) {
      sd.errorHalt("xxx dataset.CSV file failed.");
    }
    else {
      // write data
      
      logFile.print(uptime);
      logFile.print(",");
      logFile.println(dustDensity);
    
      logFile.close(); // close file
    }
  
    // Serial Monitor Print every 5s
    if (uptime - previousLogTime > 5) {
      dustDensityMean = dustDensitySum / logCounter;
      Serial.println(" --- ");
      Serial.print("Time: "); Serial.print(uptime); Serial.print("s | ");
      Serial.print("Dust Density: "); Serial.print(dustDensityMean); Serial.println("ug/m3 ");
      Serial.print("# of Samples: "); Serial.print(logCounter); Serial.println(" ");
     
      previousLogTime = uptime;
      dustDensitySum = 0.00;
      logCounter = 0;
      
    }
    else {
      dustDensitySum = dustDensitySum + dustDensity;
      logCounter = logCounter + 1;
    }
  }

}
