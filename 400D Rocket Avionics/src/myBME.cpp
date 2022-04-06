#include "myBME.h"

/*!
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    @brief Initializes the sensor with desired sampling rate
            , then calculate a baseline altitude in two seconds
    @return true if started successfully, false if not 
=======
=======
>>>>>>> Stashed changes
    @brief Initializes the sensor at 100Hz, then calculate a baseline altitude in two seconds
    @return 1 (true) if initialized successfully, 0 (false) otherwise
>>>>>>> Stashed changes
*/
bool myBME::start()
{
    unsigned status;
    status = begin();
    setFrequency(BME_FREQ);

    if (status) {
        int i = 1;
        double sum = 0;
        elapsedMillis timePastMs;
        elapsedMicros timePastMicros;

        while (timePastMs <= 2000)
        {
            if (timePastMicros >= 1000000/BME_LOGFREQ && i <= BASELINE_SIZE) 
            {
                sum += readPressure();
                timePastMicros -= 1000000/BME_LOGFREQ;
                ++i;
            }
        }

        baselinePressure = sum / BASELINE_SIZE;
        baselineAltitude = readAltitude(baselinePressure/100);
    }   


    // Serial.print("Base line pressure(Pa): ");
    // Serial.print(baselinePressure);
    // Serial.print(" | Baseline altitude(m): ");
    // Serial.println(baselineAltitude);

    return status;
}

/*!
    @brief BME sensor starts measuring data (temperature, altitude, humidity)
    @return flag indicating new data from sensor, 1 if data updated, 0 otherwise
*/
bool myBME::getData()
{    

    if (timeSinceDataRead >= 1000000/BME_FREQ)
    {
        temp = readTemperature();
        altitude = readAltitude(baselinePressure/100);
        humidity = readHumidity();
<<<<<<< Updated upstream
<<<<<<< Updated upstream
        
        timeSinceDataRead -= interval;
=======

        timeSinceDataRead -= 1000000/BME_FREQ;
=======

        timeSinceDataRead -= 1000000/BME_FREQ;
    }

    if (timeSinceBufferUpdate >= 1000000/BME_LOGFREQ) {
        updateBuffers();
        timeSinceBufferUpdate -= 1000000/BME_LOGFREQ;
>>>>>>> Stashed changes
    }

    if (timeSinceBufferUpdate >= 1000000/BME_LOGFREQ) {
        updateBuffers();
        timeSinceBufferUpdate -= 1000000/BME_LOGFREQ;
>>>>>>> Stashed changes
    }

    newDataDetect = 1;
    return newDataDetect;
}

/*!
    @brief sets new data flag to false, meaning no new data from BME sensor
    @return 0 (false) flag
*/
bool myBME::resetDataFlag()
{
    newDataDetect = 0;
    return newDataDetect;
}


/*!
    @brief Returns data measured from BME
    @return temperature (deg C)
*/
<<<<<<< Updated upstream
<<<<<<< Updated upstream
float myBME::getTemp()
{
    return temp;
=======
float myBME::getTemp(int i)
{
    return temp_buffer[i];
>>>>>>> Stashed changes
=======
float myBME::getTemp(int i)
{
    return temp_buffer[i];
>>>>>>> Stashed changes
}

/*!
    @brief Returns data measured from BME
    @return altitude (m)
*/
<<<<<<< Updated upstream
<<<<<<< Updated upstream
float myBME::getAltitude()
{
    return altitude;
=======
float myBME::getAltitude(int i)
{
    return altitude_buffer[i];
>>>>>>> Stashed changes
=======
float myBME::getAltitude(int i)
{
    return altitude_buffer[i];
>>>>>>> Stashed changes
}


/*!
    @brief Returns data measured from BME
    @return humidity (%)
*/
<<<<<<< Updated upstream
<<<<<<< Updated upstream
float myBME::getHumidity()
{
    return humidity;
=======
=======
>>>>>>> Stashed changes
float myBME::getHumidity(int i)
{
    return humidity_buffer[i];
}

/*!
    @brief Returns time at which BME measured data 
    @return time (us)
*/
uint32_t myBME::getTime(int i)
{
    return timeMicros_buffer[i];
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}

/*!
    @brief Fills the buffer array (buffer of 3 seconds, 30Hz)
*/
void myBME::updateBuffers()
{

    // shifts data right to make space for new data at index 0
    for (int i = SAMPLE_SIZE - 1; i > 0; --i)
    {
        altitude_buffer[i] = altitude_buffer[i-1]; 
    }
    // populate buffer with new altitude 
    altitude_buffer[0] = altitude;
    
    for (int i = SAMPLE_SIZE - 1; i > 0; --i)
    {
        temp_buffer[i] = temp_buffer[i-1]; 
    }
    temp_buffer[0] = temp;

    for (int i = SAMPLE_SIZE - 1; i > 0; --i)
    {
        humidity_buffer[i] = humidity_buffer[i-1]; 
    }
    humidity_buffer[0] = humidity; 
}

/*!
    @brief Calculates the 3 second average of data buffer
    @return 3 second average, rounded to integer
*/
int myBME::getAvg()
{
    double sum = 0.0;

    for (int i = 0; i <= SAMPLE_SIZE - 1; ++i)
    {
        sum += altitude_buffer[i];
    }

    recentAverage = round (sum / SAMPLE_SIZE);
    return recentAverage;
}

/*!
    @brief Calculates the 1 second average of data buffer
    @return 1 second average, rounded to integer
*/
int myBME::getAvgRecent()
{
    double sum = 0.0;

    for (int i = 0; i <= RECENT_SIZE - 1; ++i)
    {
        sum += altitude_buffer[i];
    }

    return round(sum / RECENT_SIZE);
}

float myBME::getRecentData() {
    return altitude_buffer[0];
}

/*!
 *   @brief Sets the BME's output data rate in Hz
 *   @param rate desired rate in Hz (10,20,30,40,50,100)
*/
void myBME::setFrequency(int rate)
{
    if (rate == 10) {
        setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X16, // temperature
                    Adafruit_BME280::SAMPLING_X16, // pressure
                    Adafruit_BME280::SAMPLING_X16, // humidity
                    Adafruit_BME280::FILTER_OFF,
                    Adafruit_BME280::STANDBY_MS_0_5 );
    }

    else if (rate == 20) {
        setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X16, // pressure
                    Adafruit_BME280::SAMPLING_X8, // humidity
                    Adafruit_BME280::FILTER_OFF,
                    Adafruit_BME280::STANDBY_MS_0_5 ); 
    }

    else if (rate == 30) {
        setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X8, // pressure
                    Adafruit_BME280::SAMPLING_X8, // humidity
                    Adafruit_BME280::FILTER_OFF,
                    Adafruit_BME280::STANDBY_MS_0_5 );
    }

    else if (rate == 40) {
        setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X8, // pressure
                    Adafruit_BME280::SAMPLING_X4, // humidity
                    Adafruit_BME280::FILTER_OFF,
                    Adafruit_BME280::STANDBY_MS_0_5 );
    }

    else if (rate == 50) {
        setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X4, // pressure
                    Adafruit_BME280::SAMPLING_X4, // humidity
                    Adafruit_BME280::FILTER_OFF,
                    Adafruit_BME280::STANDBY_MS_0_5 );
    }

    else if (rate == 100) {
        setSampling(Adafruit_BME280::MODE_NORMAL,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF,
                    Adafruit_BME280::STANDBY_MS_0_5 );
    }

    else {
        Serial.println("Invalid sensor rate. Options include:");
        Serial.println("10, 20, 30, 40, 50, 100 Hz");
    }
}

/*!
    @brief Detects if current altitude is 200m above the baseline altitude
    @return 1 (true) if current altitude is 200m above baseline, 0 (false) otherwise
*/
bool myBME::detectLaunch()
{   
    Serial.print("baseline altitude: ");
    Serial.println(baselineAltitude);
    Serial.print("launch detect altitude: ");
    Serial.println(baselineAltitude + .5);

    if (recentAverage >= baselineAltitude + .5)
    {
        launchDetect = true;
    }

    return launchDetect;
}