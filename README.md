## M5Core2 電子名札

従来のM5Stack Coreでも動作する

### プリプロセッサマクロ

`config.h` の `#define` を編集する

- いずれか1つ選択
  - `BOARD_M5CORE`: M5Stack Basic/Gray/Fire用
  - `BOARD_M5CORE2`: M5Core2用
- 必要に応じて追加
  - `ENABLE_SHT31`: SHT31 温湿度センサ 使用

### 設定JSON

`settings.json` を編集する

#### データ構造

- `foreground`: 文字色 (RGB配列)
- `background`: 背景色 (RGB配列)
- `menu`: 画面下部メニュー
  - `foreground`: 文字色 (RGB配列)
  - `background`: 背景色 (RGB配列)
- `led`: M5GO Base内蔵LED
  - `color`: 色 (RGB配列)
  - `pattern`: 点灯パターン (0: 点灯, 1: フェードイン/アウト, 2: 点滅)
- `image`: 画像
  - `src`: ファイル名 (BMP/JPG/PNG対応)
  - `x`: 左上X座標
  - `y`: 左上Y座標
- `text`: 文字 (配列: 複数個対応)
  - 各要素
    - `x`: 左上X座標
    - `y`: 左上Y座標
    - `size`: フォントサイズ (16, 24, 32, 40から選択)
    - `text`: 表示する文字列
    - `foreground`: 文字色 (RGB配列)
    - `background`: 背景色 (RGB配列)
- `qrcode`: QRコード
  - `x`: 左上X座標
  - `y`: 左上Y座標
  - `width`: 幅 (高さも同一になる)
  - `url`: QRコードの内容
