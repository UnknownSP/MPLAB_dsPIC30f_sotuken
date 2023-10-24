# MPLAB_dsPIC30f_sotuken
卒業研究で製作したdsPICを用いたモータドライバ基板のプログラムになります。
メインのコードは非公開ですがMDは公開します。

製作費を抑えるため、もともと存在するロボ研の基板にシールドするという形で実装しております。

![ロボット外観](https://github.com/UnknownSP/MPLAB_dsPIC30f_sotuken/assets/39638661/7cfba4ba-6a5b-4246-a323-5edb53f42a01)

## 回路

![製作した基板](https://github.com/UnknownSP/MPLAB_dsPIC30f_sotuken/assets/39638661/2109da44-fd58-468f-ac93-956a2c836f12)
![既存基板との接続](https://github.com/UnknownSP/MPLAB_dsPIC30f_sotuken/assets/39638661/e09514a1-e32d-4d9f-b9a8-436e86eab8dd)

## ハードウェア

ハードウェアも一から製作しました。

![エンコーダ取り付け](https://github.com/UnknownSP/MPLAB_dsPIC30f_sotuken/assets/39638661/bfc6636d-9c29-4975-8b9a-9e18448932a7)
![オムニホイールとの接続](https://github.com/UnknownSP/MPLAB_dsPIC30f_sotuken/assets/39638661/dc672f14-e9b5-45f3-9b9d-1955b82e899e)

## 仕様

QEI機能を用いて取得したエンコーダの値を基に、PID制御を用いて指定の速度になるように制御しています。
速度や回転方向の指定はI2C通信を用いて行います。
