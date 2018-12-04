# Stuffed Robot V3 Firmware

## TODO
- use timerinterrupt for UART.
-- 一定時間ごとにUART通信をする。
-- 送信の間隔は、タイマ割り込みを使って作るように変更
--- 送信完了割り込み→タイマー起動→タイマー割り込み→次の送信

-ADCを自動スキャン、I2Sから受け取る
	https://gist.github.com/phonec/42d685580b4c5b93c8b38d5fa68e0e58 が参考になる。


- ロボットの状態を保持し、Wifiからの問い合わせにはすぐに答える。
　・制御モードなども。

- Serial通信は常時行う。
