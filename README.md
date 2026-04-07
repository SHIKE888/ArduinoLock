# ArduinoLock

基于 ESP32 的多方式智能门锁项目，支持本地与联网双模式开锁，并提供 OLED 状态显示和 Web 配网功能。

## 功能简介

- 密码开锁（矩阵键盘）
- 指纹开锁（Adafruit Fingerprint）
- RFID 卡开锁（MFRC522）
- Blinker 远程开锁
- OLED 显示交互状态
- 失败次数限制与锁定倒计时
- Web AP 配网并保存 WiFi/Blinker 参数到 EEPROM

## 目录说明

- `ArduinoLock/`：主工程源码（`.ino` 与各模块 `.cpp/.h`）
- `build/`：本地编译产物与中间文件（不应提交到仓库）

## 主要模块

- `ArduinoLock.ino`：主流程与状态机
- `finger.cpp`：指纹录入、删除、验证
- `rfid.cpp`：RFID 读卡、添加、校验
- `key.cpp`：键盘输入与密码管理
- `web.cpp`：AP 模式配网与参数保存
- `e2prom.cpp`：EEPROM 读写封装
- `door.cpp`：开门控制与蜂鸣器反馈

## 开发说明

- 平台：ESP32（Arduino Framework）
- 依赖库见 `build/libraries/` 的编译引用（如 U8g2、MFRC522、Blinker、Adafruit_Fingerprint）
- 上传前请确保 `build/` 不被纳入提交

## 上传前建议

可用以下命令确认构建目录不会被提交：

```bash
git status
git check-ignore -v build/
```
