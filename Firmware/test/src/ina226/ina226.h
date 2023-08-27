/**
 * @file ina226.h
 *
 */

#ifndef __INA226_H__
#define __INA226_H__

/*********************
 *      INCLUDES
 *********************/

#include "ina226_i2c.h"

/*********************
 *      DEFINES
 *********************/

#define MODE_INA226      0x4327 /**< 0x4127*/
#define CFG_REG          0x00   /**< 配置寄存器*/
#define SV_REG           0x01   /**< 分流电压*/
#define BV_REG           0x02   /**< 总线电压*/
#define PWR_REG          0x03   /**< 电源功率*/
#define CUR_REG          0x04   /**< 电流*/
#define CAL_REG          0x05   /**< 校准，设定满量程范围以及电流和功率测数的 */
#define ONFF_REG         0x06   /**< 屏蔽 使能 警报配置和转换准备就绪*/
#define AL_REG           0x07   /**< 包含与所选警报功能相比较的限定值*/
#define INA226_GET_ADDR  0xff   /**< 包含唯一的芯片标识号 0x2260*/
#define INA226_GET_MID   0xfe   /**< 包含唯一的工厂制造识别号 0x5449*/
#define INA226_ADDR1     0x80
#define INA226_GETALADDR 0x14

/*定义配置数据*/
#define VOLTAGE_LSB      1.25f  /**< 总线电压 LSB 1.25mV*/
#define INA226_VAL_LSB   2.5f   /**< 分流电压 LSB 2.5uV*/
#define CURRENT_LSB      0.1f   /**< 电流 LSB 0.1mA*/
#define POWER_LSB        (25.0f * CURRENT_LSB)
#define CAL              2560   /**< 0.00512 / (Current_LSB * R_SHUNT)*/

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

/**
 * 更换采样电阻为 0.02 欧
 * Current Max = 81.92mV / 0.02 = 4096mA
 * Current_LSB = 0.1mA, 0.1mA * 32768(0x7FFF) = 3276.8mA < 4096mA
 * CAL = 0.00512/(0.1*0.02)*1000 = 2560 = 0x0A00
 */

/**********************
 *      TYPEDEFS
 **********************/

typedef struct {
    float Bus_voltage;   /**< 总线电压 mV*/
    float Shunt_voltage; /**< 分流电压 uV*/
    float Shunt_Current; /**< 分流电流 mA*/
    float Power;         /**< 功率 mW*/
    float Ref_Power;     /**< 用户计算功率，用户通过总线电压和电流计算得到*/
    uint32_t ID;         /**< 设备 ID*/
    uint32_t MID;        /**< Manufacturer ID*/
} INA226_Data_Typedef;

extern INA226_Data_Typedef INA226_Data;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

void INA226_Init(void);
void Get_Bus_Voltage(float * Voltage);
void Get_Shunt_voltage(float * Voltage);
void Get_Shunt_Current(float * Current);
void Get_Power(float * Power);
void INA226_Update(void);
uint8_t INA226_AlertAddr(void);

#endif /*__INA226_H__*/
