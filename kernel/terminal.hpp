/**
 * @file terminal.hpp
 *
 * ターミナルウィンドウを提供する。
 */

#pragma once

#include <deque>
#include <map>
#include "window.hpp"
#include "task.hpp"
#include "layer.hpp"

class Terminal {
 public:
  static const int kRows = 15, kColumns = 60;                        // 行と列の大きさ
  static const int kLineMax = 128;                                   // ラインバッファの行数

  Terminal();                                                        // コンストラクタ
  unsigned int LayerID() const { return layer_id_; }                 // layer ID を返す
  Rectangle<int> BlinkCursor();                                      // カーソルを点滅
  Rectangle<int> InputKey(uint8_t modifier, uint8_t keycode, char ascii); // キー入力を受け付ける

 private:
  std::shared_ptr<ToplevelWindow> window_;
  unsigned int layer_id_;

  Vector2D<int> cursor_{0, 0};
  bool cursor_visible_{false};
  void DrawCursor(bool visible);                                     // カーソルを表示
  Vector2D<int> CalcCursorPos() const;

  int linebuf_index_{0};
  std::array<char, kLineMax> linebuf_{};
  void Scroll1();                                                    // １行スクロール

  void ExecuteLine();                                                // 入力行を解釈して実行
  void Print(const char* s);                                         // 文字列をターミナルで表示
};

void TaskTerminal(uint64_t task_id, int64_t data);
