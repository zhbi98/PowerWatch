
#include "ina226.h"

INA226_Typedef ina226_data;

void INA226_Init(void)
{
    // IIC_Init();
    ina226_gpio_init();
    INA226_SendData(INA226_ADDR1, CFG_REG, 0x8000); // 重新启动
    INA226_SendData(INA226_ADDR1, CFG_REG, MODE_INA226);
    INA226_SendData(INA226_ADDR1, CAL_REG, CAL); // 设置分辨率
    INA226_Get_ID(INA226_ADDR1); // 获取 ina226 的 id
    INA226_Get_MID(INA226_ADDR1);
}

// 发送, 写入数据
void INA226_SendData(uint8_t addr, uint8_t reg, uint16_t data)
{
    unsigned char temp = 0;
    ina226_i2c_start();//IIC_Start();

    ina226_i2c_send_byte(addr);//IIC_Send_Byte(addr);
    ina226_i2c_wait_ack();//IIC_Wait_Ack();

    ina226_i2c_send_byte(reg);//IIC_Send_Byte(reg);
    ina226_i2c_wait_ack();//IIC_Wait_Ack();
    
    temp = (unsigned char)(data >> 8);
    ina226_i2c_send_byte(temp);//IIC_Send_Byte(temp);
    ina226_i2c_wait_ack();//IIC_Wait_Ack();

    temp = (unsigned char)(data & 0x00ff);
    ina226_i2c_send_byte(temp);//IIC_Send_Byte(temp);
    ina226_i2c_wait_ack();//IIC_Wait_Ack();
    
    ina226_i2c_stop();//IIC_Stop();
}

// 设置寄存器指针
void INA226_SetRegPointer(uint8_t addr, uint8_t reg)
{
    ina226_i2c_start();//IIC_Start();

    ina226_i2c_send_byte(addr);//IIC_Send_Byte(addr);
    ina226_i2c_wait_ack();//IIC_Wait_Ack();

    ina226_i2c_send_byte(reg);//IIC_Send_Byte(reg);
    ina226_i2c_wait_ack();//IIC_Wait_Ack();

    ina226_i2c_stop();//IIC_Stop();
}

// 读取数据
uint16_t INA226_ReadData(uint8_t addr)
{
    uint16_t temp=0;
    ina226_i2c_start();//IIC_Start();

    ina226_i2c_send_byte(addr + 1);//IIC_Send_Byte(addr+1);
    ina226_i2c_wait_ack();//IIC_Wait_Ack();
    
    temp = ina226_i2c_read_byte(1);//IIC_Read_Byte(1);
    temp <<= 8;   
    temp |= ina226_i2c_read_byte(0);//IIC_Read_Byte(0);
    
    ina226_i2c_stop();//IIC_Stop();
    return temp;
}

// 获取 id
void INA226_Get_ID(uint8_t addr)
{
    uint32_t temp = 0;
    INA226_SetRegPointer(addr, INA226_GET_ADDR);
    temp = INA226_ReadData(addr);
    ina226_data.ina226_id = temp;
}

// 获取 Manufacturer ID
void INA226_Get_MID(uint8_t addr)
{
    uint32_t temp = 0;
    INA226_SetRegPointer(addr, INA226_GET_MID);
    temp = INA226_ReadData(addr);
    ina226_data.ina226_mid = temp;
}

// 获取校准值
uint16_t INA226_GET_CAL_REG(uint8_t addr)
{
    uint32_t temp = 0;
    INA226_SetRegPointer(addr, CAL_REG);
    temp = INA226_ReadData(addr);
    return (uint16_t)temp;
}

// 总线电压寄存器02H----------->1.25mV/bit
uint16_t INA226_GetVoltage(uint8_t addr)
{
    uint32_t temp = 0;
    INA226_SetRegPointer(addr, BV_REG);
    temp = INA226_ReadData(addr);
    return (uint16_t)temp;
}

// 分流电压寄存器01H----------->2.5uV/bit
int16_t INA226_GetShuntVoltage(uint8_t addr)
{
    int16_t temp = 0;
    INA226_SetRegPointer(addr, SV_REG);
    temp = INA226_ReadData(addr);
    // if(temp&0x8000) temp = ~(temp - 1);
    return (int16_t)temp;
}

// 电流寄存器04H----------->1mA/bit
int16_t INA226_GetShunt_Current(uint8_t addr)
{
    int16_t temp=0;
    INA226_SetRegPointer(addr, CUR_REG);
    temp = INA226_ReadData(addr);
    // if(temp&0x8000) temp = ~(temp - 1);
    return temp;
}

// 功率寄存器03H----------->25mW/bit
uint16_t INA226_Get_Power(uint8_t addr)
{
    int16_t temp=0;
    INA226_SetRegPointer(addr, PWR_REG);
    temp = INA226_ReadData(addr);
    return (uint16_t)temp;
}

// 获取总线电压----------->1.25mV/bit
void GetVoltage(float * Voltage) // mV
{
    // LSB 为 1.25 mV
    *Voltage = INA226_GetVoltage(INA226_ADDR1) * VOLTAGE_LSB;
}

// 获取分流电压----------->2.5uV/bit
void Get_Shunt_voltage(float * Voltage) // uV
{
    // LSB 为 2.5 uV 
    *Voltage = (INA226_GetShuntVoltage(INA226_ADDR1) * INA226_VAL_LSB);//如需矫正电流分流参数请将这里改为2.5
}

// 获取电流----------->1mA/bit
void Get_Shunt_Current(float * Current) // mA
{
    *Current = (INA226_GetShunt_Current(INA226_ADDR1) * CURRENT_LSB);
}

// 获取功率----------->25mW/bit
void Get_Power(float * Power)//mW
{
    *Power = (INA226_Get_Power(INA226_ADDR1) * POWER_LSB);
}

// 获取功率 = 总线电压 * 电流
void get_power() // W
{
    GetVoltage(&ina226_data.voltageVal);            // mV
    Get_Shunt_voltage(&ina226_data.Shunt_voltage);  // uV
    Get_Shunt_Current(&ina226_data.Shunt_Current);  // mA
    Get_Power(&ina226_data.Power);                  // mW
    ina226_data.Power_Val = ina226_data.voltageVal * 0.001f * ina226_data.Shunt_Current * 0.001f; // mV * mA
}

//不设置报警，舍弃
/*
unsigned char INA226_AlertAddr()
{
    unsigned char temp;
    ina226_i2c_start();//IIC_Start();

    ina226_i2c_send_byte(INA226_GETALADDR);//IIC_Send_Byte(INA226_GETALADDR);
    ina226_i2c_wait_ack();//IIC_Wait_Ack();

    temp = ina226_i2c_read_byte(1);//IIC_Read_Byte(1);

    ina226_i2c_stop();//IIC_Stop();
    return temp;
}
*/
