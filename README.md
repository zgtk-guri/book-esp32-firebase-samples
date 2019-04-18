# 「ESP32でFirebase」サンプルダウンロードページ

本リポジトリは，Guri-Techの同人誌「ESP32でFirebase」のサンプルソースを公開するためのものです。

「ESP32でFirebase」は，BOOTHにて500円で販売しております。
次のURLからご購入ください。

https://guri-tech.booth.pm/items/1318547

![ESP32でFirebase表紙絵](thumbnail.png)


## リポジトリの構成

- wifi-sample ディレクトリ
  - M5StackでWi-Fiに接続するだけのサンプルです。
- without-auth ディレクトリ
  - 本書 第3章「ESP32 からRealtime Database（ユーザー認証なし）」に対応するサンプルです。
  - M5StackのBボタン（中央）でFirebaseから読み出しをします。
  - Cボタン（右）で書き込みをします。
- with-auth ディレクトリ
  - 本書 第4章「ESP32 からRealtime Database（ユーザー認証あり）」に対応するサンプルです。
  - 本サンプルは，ArduinoJson バージョン6.10.0が必要です。
  - M5StackのAボタン（左）でFirebase Authenticationでアカウントを作成（Sign up）します。
  - Bボタン（中央）でFirebase Authenticationでサインイン（Sign in）します。
  - Cボタン（右）で現在サインインしているアカウントでFirebaseから読み出しをします。
