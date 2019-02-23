# ESP32-Duktape
The ESP32 is a WiFi and Bluetooth enabled MCU from Espressif.  It is a dual core
processor with 512K of RAM and commonly 4M of flash.  Each processor runs at
240MHz.  It has built in WiFi and Bluetooth as well as a rich assortment of
sensor inputs and outputs.

Duktape is an open source implementation of a JavaScript environment including
a runtime, compiler, debugger and a wealth of well written documentation.

This project provides an environment for running JavaScript on the ESP32 using the
Duktape engine.  In addition to providing all the necessary components to run
a simple JavaScript program, a framework is also provided that provides premade
modules for many of the common ESP32 functions including networking, web servers,
web sockets, GPIO and much more.

An integrated browser based JavaScript editor and file system are also present
meaning that once installed, one needs no specialized tools in order to build and
run JavaScript.

All components in this project are open source.  Collaborators welcomed.



# Stuffed Robot V3 Firmware

## DONE
- Continuously update RobotState via UART communication by using CI_ALL command.
-ADCを自動スキャン、I2Sから受け取る
	https://gist.github.com/phonec/42d685580b4c5b93c8b38d5fa68e0e58 が参考になる。

- ロボットの状態を保持し、Wifiからの問い合わせにはすぐに答える。
　・制御モードなども。

## TODO

- UDP通信の更新方法(送信＝PC→Robot)?
再送方式の場合
-- 返信の番号までが、送信できたと考えて、番号がそれ以上のコマンドをすべて再送する。
-- 送信が遅れてバッファが空になったら、停止

再送しない場合
-- ターゲットの時刻とCOWを見て補間する。
-- COWが飛んだときは、あいだのターゲットを補間して作る。
-- COWがまだ読み出しされていなければ、更新する。
