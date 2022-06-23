
# Elecal 迷你 USB 电源功率计

## 简介

> **Elecal** 是一个迷你的 USB 电源功率计，在硬件设计上可以同时测量电源电压电流以及功率，
同时通过软件方案实现 mAh，Ah，Wh 的实时监测。
通过 mAh，Ah，Wh 这些计量单位可以很方便的计量和计算被监测电源所输出的电能。 比如其中的 mAh 所能
说明的是一颗 3000mAh 的电池可以提供在 300mA 恒流输出状态下持续 10 小时的电能输出能力。

## 项目文件说明

**gd32f103 目录**

功率计固件源码以及编译工程所在目录，该文件夹下的 `mdk5\` 目录即为 **ARM keil5** 的工程文件，`test\` 目录包含所有功能实现需要用到的驱动库以及源码。主要包含以下文件：
- 移植好的 GD32f103 的 USB 驱动，USB 驱动使用的是虚拟串口，可以用于和上位机进行数据通讯。
- 320 * 170 分辨率的 IPS 屏幕驱动，屏幕驱动芯片是 ST7789V3。
- 移植好的 LVGL8.2.0 的 UI 绘图库，这个 UI 库可以实现美观的图形界面，使用 LVGL 后就不需要我们自己控制屏幕逐像素的绘制图形来实现 UI 了。

**image 目录**

实物效果图片展示，观看制作效果可以查看该目录下的实物照片。

**model 目录**

功率外壳模型，外壳模型包含三个零件，底盒，屏幕托架，上盖板。上盖板的想法是要制作成灰色透明的，对于这个上盖板最好使用亚克力板进行制作，普通 3D 打印无法实现透明。

**stm32_pcbv1.0 目录**

功率电路 PCB 源文件工程，该文件夹下包含电路原理图，以及 PCB 制造文件（即 Gerber 文件）将 Gerber 文件压缩后到嘉立创网站下单即可将 PCB 打样出来。
PCB 设计时原本的设想是使用 **STM32F103RCT6** 这颗芯片作为微控制器使用的，但是奈何 **STM32F103RCT6** 价格较高，所以最终芯片使用的是 **GD32F103RCT6**，但是这对电路并不影响，因为 **GD32F103RCT6** 可以 Pin 对 Pin 的兼容 **STM32F103RCT6**。
硬件已经打样验证通过，需要制作的话可以放心打样使用。

## 硬件介绍

> 1.控制器: GD32F103RCT6 芯片主频 96MHz RAM:64KB ROM:256KB)  
2.屏幕: ST7789V3 IPS 8 位并行接口 320x170 分辨率  
3.Flash: GD25Q64  
4.电压电流采样芯片: INA226  
5.外壳: 3D打印光固化  

## 3D 模型设计

> 目前正在设计外壳 V2.0 版本，设计完成后将会提供在此处。目前 **image 目录** 
下的版本是外壳 V1.0，设计完成后将开放到此处。

> **V1.0 版本效果**
> <div align=center><img align="center" src="https://github.com/zhbi98/Elecal/blob/main/image/Elecal_v1.0.png" alt="GitHub" title="GitHub,Social Coding" width="900" height="562"/></div>

> **V2.0 版本效果**
> <div align=center><img align="center" src="https://github.com/zhbi98/Elecal/blob/main/image/Elecal.png" alt="GitHub" title="GitHub,Social Coding" width="900" height="497"/></div>

## 实物效果

> <div align=center><img align="center" src="https://github.com/zhbi98/Elecal/blob/main/image/001.jpg" alt="GitHub" title="GitHub,Social Coding" width="500" height="667"/></div>
<div align=center><img align="center" src="https://github.com/zhbi98/Elecal/blob/main/image/005.jpg" alt="GitHub" title="GitHub,Social Coding" width="500" height="667"/></div>
