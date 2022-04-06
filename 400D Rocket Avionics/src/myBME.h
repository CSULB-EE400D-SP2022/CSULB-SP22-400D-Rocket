#pragma once

#include <Adafruit_BME280.h>
#include <Arduino.h>

const int ABOVE_BASELINE = 200;                         // meters above baseline for the rocket to be considered launched
static const int FREQUENCY = 30;                        // proposed frequency at which we are logging data
static const int SAMPLE_SIZE = 3 * FREQUENCY;           // duration for averaging * frequency in Hz
static const int RECENT_SIZE = 1 * FREQUENCY;           // duration for averaging * frequency in Hz
static const int BASELINE_SIZE = 2 *FREQUENCY;          // duration for averaging * frequency in Hz

class myBME : public Adafruit_BME280

{
    public:
        using Adafruit_BME280::Adafruit_BME280; // credit to Brandon Summers

        bool start(int rate);
        bool getData();
        bool resetDataFlag();

        float getAltitude(int index);
        float getTemp(int index);
        float getHumidity(int index);
        uint32_t getTime(int index);
        
        void updateBuffers();
        int getAvg();
        int getAvgRecent();
        float getRecentData();

        void setFrequency(int rate);
        bool detectLaunch();
        

    private:
        // automatically keeps track of time elapsed in microseconds
        elapsedMicros timeSinceDataRead;       
        elapsedMicros trueTime;

        float temp, altitude, humidity;
        int recentAverage;
        int frequency; 
        
        float altitude_buffer[SAMPLE_SIZE] = {0.0};         // buffer for altitude (m)
        float temp_buffer[SAMPLE_SIZE] = {0.0};             // buffer for temp (deg C)
        float humidity_buffer[SAMPLE_SIZE] = {0.0};         // buffer for humidity  (%)
        uint32_t timeMicros_buffer[SAMPLE_SIZE] = {0};      // buffer for time (us)

        float baselinePressure;                     // baseline for ground lv pressure
        float baselineAltitude;                     // baseline for ground lv altitude

        bool launchDetect{0};                    // flag for launch detect, init at 0
        bool newDataDetect{0};                   // flag for new data detect, init at 0

};