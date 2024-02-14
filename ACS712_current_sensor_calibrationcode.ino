

#include <Calculus.h>
#include <Filters.h>

/*Code adapted from 
https://www.instructables.com/id/Simplified-Arduino-AC-Current-Measurement-Using-AC/ 
by Álvaro Henrique
email: pacottte@gmail.com*/
 
 

 
 
void setup() {
  Serial.begin( 9600 );    // start the serial port
}
 
void loop() {
 measure_current(4000);
}
 
 
float measure_current(unsigned long printPeriod) {// in milliseconds
 
  float testFrequency = 60;                     // test signal frequency (Hz)
  float windowLength = 20.0 / testFrequency;   // how long to average the signal, for statistist
  int sensorValue = 0;
  float intercept = -0.1129; // to be adjusted based on calibration testing
  float slope = 0.0405; // to be adjusted based on calibration testing
  float current_amps; // estimated actual current in amps
 
  int voltage =220; //change this to 110 if you have 110Vac
  // Track time in milliseconds since last reading
  unsigned long previousMillis = 0;
  //RunningStatistics inputStats;                 // create statistics to look at the raw test signal
 // inputStats.setWindowSecs( windowLength );
  previousMillis = millis();   // update time
 
  while ((unsigned long)(millis() - previousMillis) < printPeriod) {
    sensorValue = analogRead(A0);  // read the analog in value:
    inputStats.input(sensorValue);  // log to Stats function
  }
  // display current values to the screen
  Serial.print( "\n" );
  // output sigma or variation values associated with the inputValue itsel
  Serial.print( "\tSigma: " );
  //Serial.print( inputStats.sigma() );
  // convert signal sigma value to current in amps
  current_amps = intercept + slope * inputStats.sigma();
  Serial.print( "\tCurrent: " ); Serial.print( current_amps ,4);Serial.print( " A rms");
  Serial.print( "\tPower Comsuption: " ); Serial.print( current_amps * voltage );Serial.print( " W");
}
