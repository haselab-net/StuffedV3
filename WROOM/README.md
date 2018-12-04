# Stuffed Robot V3 Firmware

## TODO
- use timerinterrupt for UART.
-- 一定時間ごとにUART通信をする。
-- 送信の間隔は、タイマ割り込みを使って作るように変更
--- 送信完了割り込み→タイマー起動→タイマー割り込み→次の送信


- ロボットの状態を保持
　・制御モードなども。