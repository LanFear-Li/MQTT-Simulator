# MQTT-Simulator

## 介绍

本项目是一个MQTT协议客户端模拟程序，包含temp_sensor和monitor客户端。

- temp_sensor作为publisher，随机生成温度数据通过eventbus topic发送至broker。
- monitor作为subscriber，订阅eventbus topic， 从broker获取该topic的数据。

## Build

本项目运行于linux平台， 可使用cmake构建方式。

首先通过Git clone本仓库

```bash
git clone https://github.com/LanFear-Li/MQTT-Simulator
git clone git@github.com:LanFear-Li/MQTT-Simulator.git
```

自动构建：使用CLion打开本项目直接build

手动构建：

```bash
mkdir build
cd build
cmake ../
make 
```

手动make之后在MQTT-Simulator/build目录下生成了可执行文件pub， sub。通过./pub ./sub即可运行两个客户端。

## 注意事项

请提前安装好broker作为MQTT协议服务器。本人使用的是Eclipse Mosquitto(https://mosquitto.org/)

