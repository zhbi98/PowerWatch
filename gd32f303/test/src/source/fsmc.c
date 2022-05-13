
#include "fsmc.h"

void exmc_gpio_init()
{
    // PD14(EXMC_D0), PD15(EXMC_D1),PD0(EXMC_D2), PD1(EXMC_D3), PD8(EXMC_D13), PD9(EXMC_D14), PD10(EXMC_D15) 
    gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_0 | GPIO_PIN_1| GPIO_PIN_8 | GPIO_PIN_9 |
                                                         GPIO_PIN_10 | GPIO_PIN_14 | GPIO_PIN_15);
    // PE7(EXMC_D4), PE8(EXMC_D5), PE9(EXMC_D6), PE10(EXMC_D7), PE11(EXMC_D8), PE12(EXMC_D9), 
    // PE13(EXMC_D10), PE14(EXMC_D11), PE15(EXMC_D12)
    gpio_init(GPIOE, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | 
                                                         GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | 
                                                         GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
    // configure PE2(EXMC_A16-EXMC_A23)
    gpio_init(GPIOE, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | 
                                                         GPIO_PIN_5 | GPIO_PIN_6);
    gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13);
    // configure NOE and NWE 
    gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_4 | GPIO_PIN_5);
    // configure EXMC NE0 
    gpio_init(GPIOD, GPIO_MODE_AF_PP, GPIO_OSPEED_50MHZ, GPIO_PIN_7);
}

void exmc_init()
{
    exmc_norsram_parameter_struct fpga_init_struct;
    exmc_norsram_timing_parameter_struct fpga_timing_init_struct;

    exmc_gpio_init();

    // EXMC clock enable
    rcu_periph_clock_enable(RCU_EXMC);

    fpga_timing_init_struct.asyn_access_mode = EXMC_ACCESS_MODE_A;
    fpga_timing_init_struct.syn_data_latency = EXMC_DATALAT_2_CLK;
    fpga_timing_init_struct.syn_clk_division = EXMC_SYN_CLOCK_RATIO_DISABLE;
    fpga_timing_init_struct.bus_latency = 2;
    fpga_timing_init_struct.asyn_data_setuptime = 10;   // Data establishment time 83ns
    fpga_timing_init_struct.asyn_address_holdtime = 2;  // Address hold time 16ns
    fpga_timing_init_struct.asyn_address_setuptime = 5; // Address establishment time 41ns

    fpga_init_struct.norsram_region = EXMC_BANK0_NORSRAM_REGION0;
    fpga_init_struct.write_mode = EXMC_ASYN_WRITE;
    fpga_init_struct.extended_mode = DISABLE;
    fpga_init_struct.asyn_wait = DISABLE;
    fpga_init_struct.nwait_signal = DISABLE;
    fpga_init_struct.memory_write = ENABLE;
    fpga_init_struct.nwait_config = EXMC_NWAIT_CONFIG_BEFORE;
    fpga_init_struct.wrap_burst_mode = DISABLE;
    fpga_init_struct.nwait_polarity = EXMC_NWAIT_POLARITY_LOW;
    fpga_init_struct.burst_mode = DISABLE;
    fpga_init_struct.databus_width = EXMC_NOR_DATABUS_WIDTH_16B;
    fpga_init_struct.memory_type = EXMC_MEMORY_TYPE_SRAM;
    fpga_init_struct.address_data_mux = DISABLE;
    fpga_init_struct.read_write_timing = &fpga_timing_init_struct;
    fpga_init_struct.write_timing = &fpga_timing_init_struct;

    exmc_norsram_init(&fpga_init_struct);
    exmc_norsram_enable(EXMC_BANK0_NORSRAM_REGION0);
}

void write_data(uint8_t address, uint16_t data)
{
    *(__IO uint16_t *)(FPGA_COMM_ADDRESS + (address << 17)) = data;
}

uint8_t read_data(uint8_t address)
{
    return *(__IO uint16_t *)(FPGA_COMM_ADDRESS + (address << 17));
}
