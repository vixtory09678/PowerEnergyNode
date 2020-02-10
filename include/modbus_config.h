#ifndef MODBUS_CONFIG_H
#define MODBUS_CONFIG_H
#include "MeterSensor.h"
#include "esp32ModbusRTU.h"
#include "config.h"

#define METER_ADDR 0x01
#define REGISTER_LENGTH 11

esp32ModbusRTU modbus(&Serial1);
MeterSensor meter;
DebugMode mbDebug("MODBUS");

void sendCode();
int decodeReceiveData(uint8_t* dataCode, size_t len);
void onDataReceive(uint8_t serverAddress, esp32Modbus::FunctionCode fc, uint16_t address, uint8_t* data, size_t length);
void onErrorReceive(esp32Modbus::Error error);
void (*callback)(MeterSensor meter) = NULL;

// setup everything about modbus
void modbusSetup(void (*mCallback)(MeterSensor meter), bool debug = true) {
    Serial1.begin(19200, SERIAL_8N1, 33, 32);
    modbus.onData(onDataReceive);
    modbus.onError(onErrorReceive);
    modbus.begin();
    mbDebug.SET_DEBUG(debug);
    callback = mCallback;
}

// request data from meter
void sendCode() {
    modbus.readHoldingRegisters(METER_ADDR, ADDR_VOLTAGE_LN, ADDR_VOLTAGE_LN_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_CURRENT_LN, ADDR_CURRENT_LN_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_TOTAL_CURRENT, ADDR_TOTAL_CURRENT_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_ACTIVE_POWER, ADDR_ACTIVE_POWER_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_REACTIVE_POWER, ADDR_REACTIVE_POWER_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_APPARENT_POWER, ADDR_APPARENT_POWER_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_POWER_FACTOR, ADDR_POWER_FACTOR_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_VOLTAGE_L, ADDR_VOLTAGE_L_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_TOTAL_ACTIVE_POWER, ADDR_TOTAL_ACTIVE_POWER_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_TOTAL_REACTIVE_POWER, ADDR_TOTAL_REACTIVE_POWER_LENGTH);
    modbus.readHoldingRegisters(METER_ADDR, ADDR_TOTAL_APPARENT_POWER, ADDR_TOTAL_APPARENT_POWER_LENGTH);
}

int decodeReceiveData(uint8_t* dataCode, size_t len) {
    int data = 0;

    for (int i = 0, j = (len - 1); i < len; i++ , j--)
        data |= (int)(dataCode[i] << 8 * (j));

    return data;
}

void onDataReceive(uint8_t serverAddress, esp32Modbus::FunctionCode fc, uint16_t address, uint8_t* data, size_t length) {
    
    // callback when receive full data
    static int countCheckFinishReceive = 0;
    if (countCheckFinishReceive == REGISTER_LENGTH && callback != NULL) {callback(meter); countCheckFinishReceive = 0;}
    else countCheckFinishReceive += 1;

    switch (address) {
        case ADDR_VOLTAGE_LN:
            mbDebug.DEBUG("ADDR_VOLTAGE_LN");
            meter.volN.L1 = (float)decodeReceiveData(&data[0], 2) * 0.1;
            meter.volN.L2 = (float)decodeReceiveData(&data[2], 2) * 0.1;
            meter.volN.L3 = (float)decodeReceiveData(&data[4], 2) * 0.1;
            // Serial.printf("%f %f %f\n\n",meter.volN.L1, meter.volN.L2, meter.volN.L3);
        break;
        case ADDR_CURRENT_LN:
            mbDebug.DEBUG("ADDR_CURRENT_LN");
            meter.currentL.L1 = (float)decodeReceiveData(&data[0], 2) * 20 * 0.001;
            meter.currentL.L2 = (float)decodeReceiveData(&data[2], 2) * 20 * 0.001;
            meter.currentL.L3 = (float)decodeReceiveData(&data[4], 2) * 20 * 0.001;
            // Serial.printf("%f %f %f\n\n", meter.currentL.L1, meter.currentL.L2, meter.currentL.L3);
        break;
        case ADDR_TOTAL_CURRENT:
            mbDebug.DEBUG("ADDR_TOTAL_CURRENT");
            meter.totalCurrent = (float)decodeReceiveData(&data[0], 2) * 20 * 0.001;
            // Serial.printf("%f\n\n", meter.totalCurrent);
        break;
        case ADDR_ACTIVE_POWER:
            mbDebug.DEBUG("ADDR_ACTIVE_POWER");
            meter.activePower.L1 = (float)decodeReceiveData(&data[0], 2) * 20;
            meter.activePower.L2 = (float)decodeReceiveData(&data[2], 2) * 20;
            meter.activePower.L3 = (float)decodeReceiveData(&data[4], 2) * 20;
            // Serial.printf("%f %f %f\n\n",meter.activePower.L1, meter.activePower.L2, meter.activePower.L3);
        break;
        case ADDR_REACTIVE_POWER:
            mbDebug.DEBUG("ADDR_REACTIVE_POWER");
            meter.reactivePower.L1 = (float)decodeReceiveData(&data[0], 2) * 20 ;
            meter.reactivePower.L2 = (float)decodeReceiveData(&data[2], 2) * 20 ;
            meter.reactivePower.L3 = (float)decodeReceiveData(&data[4], 2) * 20 ;
            // Serial.printf("%f %f %f\n\n",meter.reactivePower.L1, meter.reactivePower.L2, meter.reactivePower.L3);
        break;
        case ADDR_APPARENT_POWER:
            mbDebug.DEBUG("ADDR_APPARENT_POWER");
            meter.apparentPower.L1 = (float)decodeReceiveData(&data[0], 2) * 20 ;
            meter.apparentPower.L2 = (float)decodeReceiveData(&data[2], 2) * 20 ;
            meter.apparentPower.L3 = (float)decodeReceiveData(&data[4], 2) * 20 ;
            // Serial.printf("%f %f %f\n\n",meter.apparentPower.L1, meter.apparentPower.L2, meter.apparentPower.L3);
        break;
        case ADDR_POWER_FACTOR:
            mbDebug.DEBUG("ADDR_POWER_FACTOR");
            meter.powerFactor.L1 = (float)decodeReceiveData(&data[0], 2) * 0.001;
            meter.powerFactor.L2 = (float)decodeReceiveData(&data[2], 2) * 0.001;
            meter.powerFactor.L3 = (float)decodeReceiveData(&data[4], 2) * 0.001;
            // Serial.printf("%f %f %f\n\n",meter.powerFactor.L1, meter.powerFactor.L2, meter.powerFactor.L3);
        break;
        case ADDR_VOLTAGE_L:
            mbDebug.DEBUG("ADDR_VOLTAGE_L");
            meter.volL.L1_L2 = (float)decodeReceiveData(&data[0], 2) * 0.1;
            meter.volL.L2_L3 = (float)decodeReceiveData(&data[2], 2) * 0.1;
            meter.volL.L3_L1 = (float)decodeReceiveData(&data[4], 2) * 0.1;
            // Serial.printf("%f %f %f\n\n",meter.volL.L1_L2, meter.volL.L2_L3, meter.volL.L3_L1);
        break;
        case ADDR_TOTAL_ACTIVE_POWER:
            mbDebug.DEBUG("ADDR_TOTAL_ACTIVE_POWER");
            meter.totalActivePower = (float)decodeReceiveData(&data[0], 2) * 20;
            // Serial.printf("%f\n\n",meter.totalPowerFactor);
        break;
        case ADDR_TOTAL_REACTIVE_POWER:
            mbDebug.DEBUG("ADDR_TOTAL_REACTIVE_POWER");
            meter.totalReactivePower = (float)decodeReceiveData(&data[0], 2) * 20;
            // Serial.printf("%f\n\n",meter.totalReactivePower);
        break;
        case ADDR_TOTAL_APPARENT_POWER:
            mbDebug.DEBUG("ADDR_TOTAL_APPARENT_POWER");
            meter.totalApparentPower = (float)decodeReceiveData(&data[0], 2) * 20;
            // Serial.printf("%f\n\n",meter.totalApparentPower);
        break;
    };
  
}

void onErrorReceive(esp32Modbus::Error error){
    String msg = String("error: ") + String(static_cast<uint8_t>(error), HEX);
    mbDebug.DEBUG(msg.c_str());
}

#endif