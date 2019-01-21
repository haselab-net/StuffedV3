# Stuffed Robot V3 Firmware

## DONE
- Continuously update RobotState via UART communication by using CI_ALL command.
-ADCを自動スキャン、I2Sから受け取る
	https://gist.github.com/phonec/42d685580b4c5b93c8b38d5fa68e0e58 が参考になる。

## TODO
- ロボットの状態を保持し、Wifiからの問い合わせにはすぐに答える。
　・制御モードなども。

- UDP通信の更新方法(送信＝PC→Robot)

再送方式の場合
-- 返信の番号までが、送信できたと考えて、番号がそれ以上のコマンドをすべて再送する。
-- 送信が遅れてバッファが空になったら、停止

再送しない場合
-- ターゲットの時刻とCOWを見て補間する。
-- COWが飛んだときは、あいだのターゲットを補間して作る。
-- COWがまだ読み出しされていなければ、更新する。
