#ifndef METER_H
#define METER_H

#include "Arduino.h"

#define ADDR_VOLTAGE_LN                     0x0000
#define ADDR_VOLTAGE_LN_LENGTH              3       // length * size of word = 3 * 2 = 6 byte

#define ADDR_CURRENT_LN                     0x0003
#define ADDR_CURRENT_LN_LENGTH              3       // 6 byte

#define ADDR_TOTAL_CURRENT                  0x0006
#define ADDR_TOTAL_CURRENT_LENGTH           1

#define ADDR_ACTIVE_POWER                   0x0007
#define ADDR_ACTIVE_POWER_LENGTH            3

#define ADDR_REACTIVE_POWER                 0x000A
#define ADDR_REACTIVE_POWER_LENGTH          3

#define ADDR_APPARENT_POWER                 0x000D
#define ADDR_APPARENT_POWER_LENGTH          3

#define ADDR_POWER_FACTOR                   0x0010
#define ADDR_POWER_FACTOR_LENGTH            3

#define ADDR_VOLTAGE_L                      0x0016
#define ADDR_VOLTAGE_L_LENGTH               3

#define ADDR_TOTAL_ACTIVE_POWER             0x001C
#define ADDR_TOTAL_ACTIVE_POWER_LENGTH      1

#define ADDR_TOTAL_REACTIVE_POWER           0x001D
#define ADDR_TOTAL_REACTIVE_POWER_LENGTH    1

#define ADDR_TOTAL_APPARENT_POWER           0x001E
#define ADDR_TOTAL_APPARENT_POWER_LENGTH    1

#define ADDR_

typedef struct 
{
    float L1;
    float L2;
    float L3;
}VolN;

typedef struct 
{
    float L1_L2;
    float L2_L3;
    float L3_L1;
}VolL;

typedef struct 
{
    float L1;
    float L2;
    float L3;
}CurrentLN;

typedef struct 
{
    float L1;
    float L2;
    float L3;
}ActivePower;

typedef struct 
{
    float L1;
    float L2;
    float L3;
}PowerFactor;

typedef struct 
{
    float L1;
    float L2;
    float L3;
}ReactivePower;

typedef struct 
{
    float L1;
    float L2;
    float L3;
}ApparentPower;

typedef struct
{
    // address of meter
    uint8_t addr;   
    // voltage N
    VolN volN;
    // voltage L
    VolL volL;
    CurrentLN currentL;
    ActivePower activePower;
    PowerFactor powerFactor;
    ReactivePower reactivePower;
    ApparentPower apparentPower;
    float totalCurrent;
    float totalActivePower;
    float totalReactivePower;
    float totalApparentPower;
    float totalPowerFactor;
} MeterSensor;

#endif