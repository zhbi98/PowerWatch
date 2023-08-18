
### USB CDC

```c
if (USBD_CONFIGURED == usb_device_dev.status) {
    if (1 == packet_receive && 1 == packet_sent) {
        packet_sent = 0;
        /* receive datas from the host when the last packet datas have sent to the host */
        cdc_acm_data_receive(&usb_device_dev);
    } else {
        if (0 != receive_length) {
            /* send receive datas */
            cdc_acm_data_send(&usb_device_dev, receive_length);
            receive_length = 0;
        }
    }
}

memcpy(usb_data_buffer, "Hello, world!\n", 14);
cdc_acm_data_send(&usb_device_dev, 14);
sleep_ms(100);
memcpy(usb_data_buffer, "Hello, gd32f103!\n", 17);
cdc_acm_data_send(&usb_device_dev, 17);
sleep_ms(100);
memcpy(usb_data_buffer, "Hello, USB virtual usart!\n", 26);
cdc_acm_data_send(&usb_device_dev, 26);
sleep_ms(100);
usb_fs_send_string("GD32F103 USB FS\n");
```

### INA226

```c
printf("Bus Voltage  : 0x%04x", INA226_GetVoltage(INA226_ADDR1));
sleep_ms(2000);
printf("Shunt Voltage: 0x%04x", INA226_GetShuntVoltage(INA226_ADDR1));
sleep_ms(2000);
printf("Current      : 0x%04x", INA226_GetShunt_Current(INA226_ADDR1));
sleep_ms(2000);
printf("Power        : 0x%04x", INA226_Get_Power(INA226_ADDR1));
sleep_ms(2000);
printf("........................");
sleep_ms(100);

printf("Bus Voltage  : %.3f(mV)", INA226_GetVoltage(INA226_ADDR1) * 1.25);
sleep_ms(2000);
printf("Shunt Voltage: %.3f(uV)", INA226_GetShuntVoltage(INA226_ADDR1) * 2.5);
sleep_ms(2000);
printf("Current      : %.3f(mA)", INA226_GetShunt_Current(INA226_ADDR1) * /*0.02*/0.1);
sleep_ms(2000);
printf("Power        : %.3f(mW)", INA226_Get_Power(INA226_ADDR1) * /*0.02*/0.1 * 25.0);
sleep_ms(2000);
/*Calcu Current(mA) = Shunt Voltage(mV) / Sampling resistor(Oumu)*/
printf("Calcu Current: %.3f(mA)", INA226_GetShuntVoltage(INA226_ADDR1) * 2.5 * 0.001 / /*0.1*/0.02);
sleep_ms(2000);
printf("========================");
sleep_ms(100);
```

```
Power = Bus Voltage x Current
--------------------------------
1(V) x 1(A) = 1W
1(mW) = 0.001(W)

0.001(V) x 1(A) = 0.001(W) = 1(mW)
OR
1(V) x 0.001(A) = 0.001(W) = 1(mW)

1(mV) x 1(A) = 1(mW)
OR
1(V) x 1(mA) = 1(mW)
```
