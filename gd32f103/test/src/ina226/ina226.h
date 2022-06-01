
#ifndef __INA226_H__
#define __INA226_H__

#include "ina226_i2c.h"

#define MODE_INA226      0x4327 // 0x4127
#define CFG_REG          0x00   // 配置寄存器
#define SV_REG           0x01   // 分流电压
#define BV_REG           0x02   // 总线电压
#define PWR_REG          0x03   // 电源功率
#define CUR_REG          0x04   // 电流
#define CAL_REG          0x05   // 校准，设定满量程范围以及电流和功率测数的 
#define ONFF_REG         0x06   // 屏蔽 使能 警报配置和转换准备就绪
#define AL_REG           0x07   // 包含与所选警报功能相比较的限定值
#define INA226_GET_ADDR  0xff   // 包含唯一的芯片标识号 0x2260
#define INA226_GET_MID   0xfe   // 包含唯一的工厂制造识别号 0x5449
#define INA226_ADDR1     0x80
#define INA226_GETALADDR 0x14

// 定义配置数据
#define VOLTAGE_LSB      1.25f  // 总线电压 LSB 1.25mV
#define INA226_VAL_LSB   2.5f   // 分流电压 LSB 2.5uV
#define CURRENT_LSB      1.0f   // 电流 LSB 1mA
#define POWER_LSB        (25 * CURRENT_LSB)
#define CAL              2560   // 0.00512 / (Current_LSB * R_SHUNT) = 512 // 电流偏大改小

/**
 * 因为 Shunt Voltage Register 的值最大为 0x7FFF, LSB=2.5uV, FSR = 81.92mV。
 * 又因为分流电阻阻值为 0.1 欧，所以最大电流为 819.2mA。(注意这个问题，
 * 避免在实际使用中出现的超量程情况，以至得出错误测量数据)
 * 所以 Maximum Expected Current 的值不能超过 819.2mA。
 */

/**
 * CAL 值计算
 * 假设 Current_LSB = 0.02mA, 则 Maximum Expected Current = 655.36mA，
 * 满足上述条件。
 * 则 CAL = 0.00512/(0.02*0.1)*1000 = 2560 = 0x0A00
 * 所以最后写入 Calibration Register中 的数据为 0x0A00
 */

typedef struct {
    float voltageVal;    // mV
    float Shunt_voltage; // uV
    float Shunt_Current; // mA
    float Power_Val;     // 功率
    float Power;         // 功率 mW
    uint32_t ina226_id;
    uint32_t ina226_mid;
} INA226_Typedef;

extern INA226_Typedef ina226_data;

extern void INA226_SetRegPointer(uint8_t addr,uint8_t reg);
extern void INA226_SendData(uint8_t addr, uint8_t reg, uint16_t data);
extern uint16_t INA226_ReadData(uint8_t addr);

extern void INA226_Get_ID(uint8_t addr);              // 获取 id
extern void INA226_Get_MID(uint8_t addr);             // 获取 Manufacturer ID
extern uint16_t INA226_GET_CAL_REG(uint8_t addr);     // 获取校准值
extern uint16_t INA226_GetVoltage( uint8_t addr);     // 获取总线电压装载值
extern int16_t INA226_GetShunt_Current(uint8_t addr); // 获取分流电流装载值
extern int16_t INA226_GetShuntVoltage(uint8_t addr);  // 分流电压装载值
extern uint16_t INA226_Get_Power(uint8_t addr);       // 获取功率装载值，不使用

extern void INA226_Init(void);
extern void GetVoltage(float * Voltage);
extern void Get_Shunt_voltage(float * Current);
extern void Get_Shunt_Current(float * Current);
extern void get_power(void); // 获取功率 = 总线电压 * 电流

extern uint8_t INA226_AlertAddr(void);
extern void Get_Power(float * Power);

#endif
