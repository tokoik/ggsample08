# ggsample08 - テクスチャマッピング

## 1. 概要

本プログラムは、[ゲームグラフィックス特論](https://tokoik.github.io/gg/)の講義資料 [ggnote08.pdf](https://tokoik.github.io/gg/ggnote08.pdf) に対応する宿題のひな型プログラムです。

- 講義ポータル: [ゲームグラフィックス特論 - 床井研究室](https://tokoik.github.io/gg/)
- 講義資料: [ggnote08.pdf](https://tokoik.github.io/gg/ggnote08.pdf)

## 2. 宿題の内容

回転する球にテクスチャをマッピングしてください。

- テクスチャユニット 0 に割り当てられたテクスチャ (`color.tga`, サンプラ `color`) を、陰影を付けてマッピングする処理を `ggsample08.frag` に実装してください。
- `in` 変数 `pv`, `nv`, `tv`（位置、法線、テクスチャ座標）を使用してください。

## 3. 対応環境

- **Windows**: Visual Studio 2019 / 2022 / 2026 (CMake 経由で GLFW 3.4 を自動ダウンロード)
- **macOS**: Xcode (GLFW 3.4 を自動ダウンロード、OpenGL Framework を使用)
- **Ubuntu Linux**: GCC / Make (システム標準の libglfw3-dev, libgl1-mesa-dev を使用)

## 4. ビルド手順

### Windows (Visual Studio)

```pwsh
cmake -B build -S .
cmake --build build --config Release
```

### macOS (Xcode)

```bash
cmake -B build -G Xcode
cmake --build build --config Release
```

### Ubuntu Linux (Makefile)

```bash
sudo apt-get update
sudo apt-get install -y libglfw3-dev libgl1-mesa-dev
cmake -B build -S .
cmake --build build
```

## 5. 起動方法

ビルド完了後、生成された実行ファイルを実行します。

- **Windows**: `build/Release/ggsample08.exe`
- **macOS**: `build/Release/ggsample08.app`
- **Linux**: `build/ggsample08`

## 6. 操作方法

- **マウス左ドラッグ**: シーンの視点回転
- **マウス右ドラッグ**: 視点の平行移動
- **マウスホイール**: ズームイン / ズームアウト
- **[q] / [Q] / [ESC]**: プログラムの終了
