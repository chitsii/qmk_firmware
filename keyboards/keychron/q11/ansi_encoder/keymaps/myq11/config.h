#pragma once

// Debounce設定 (チャタリング対策)
#define DEBOUNCE 20

// Tap-Hold設定の最適化
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY  // キーごとにTapping Termをカスタマイズ
#define PERMISSIVE_HOLD       // より積極的にホールドと判定

// 起動時にRGB Matrix(バックライト)をオフにする
// EEPROMに保存された状態が優先される場合があるため、必要に応じて keymap.c 側でも disable を実行してください。
// #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_NONE

// バックライトのドライバ自体を消す
#undef RGB_MATRIX_ENABLE

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000
#define USB_MAX_POWER_CONSUMPTION 100