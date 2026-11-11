/**
 * @file main.cpp
 *
 * BitmapMemoryManager を PC 上で動かし、確保・解放でビットマップが
 * どう変わるかを観察するサンプル．
 */

#include <cstdio>
#include <string>

#include "memory_manager.hpp"
#include "observe.hpp"

// 確保を要求して結果を表示する
// #@@range_begin(request)
FrameID Request(BitmapMemoryManager& mm, const char* name, size_t num_frames) {
  printf("\n%s = Allocate(%zu)\n", name, num_frames);
  auto [frame, err] = mm.Allocate(num_frames);
  if (err) {
    printf("  => エラー: %s\n", err.Name());
  } else {
    printf("  => frame %zu-%zu を確保\n", frame.ID(), frame.ID() + num_frames - 1);
  }
  return frame;
}
// #@@range_end(request)

bool quiet{false};

void wait_for_key() {
  if (quiet) return;

  printf("\nPress Enter to continue...");
  fflush(stdout);
  while (getchar() != '\n') ;
}

// #@@range_begin(main)
int main(int argc, char* argv[]) {
  if (argc > 1 &&
      (std::string(argv[1]) == "--quiet" || std::string(argv[1]) == "-q")) {
    quiet = true;
  }

  BitmapMemoryManager mm;
  mm.Dump("1. 初期状態：すべて空き");
  wait_for_key();

  // 場面 1：予約済み領域の登録（main.cpp がメモリマップを見て行う処理）
  mm.MarkAllocated(FrameID{8}, 4);            // frame 8-11 は使用できない領域
  mm.SetMemoryRange(FrameID{1}, FrameID{56}); // frame 0 と 56 以降は管理しない
  mm.Dump("2. 予約済み領域の登録後");
  wait_for_key();

  // 場面 2：確保と解放の基本
  trace = true;
  FrameID a = Request(mm, "a", 3);
  Request(mm, "b", 6);                        // frame 8-11 を避けて再検索
  Request(mm, "c", 4);                        // b より前の隙間に入る
  FrameID d = Request(mm, "d", 3);
  Request(mm, "e", 2);
  wait_for_key();
  mm.Dump("3. a〜e を確保した後");
  wait_for_key();

  mm.Free(a, 3);
  mm.Free(d, 3);
  mm.Dump("4. a と d を解放した後：3 フレームの穴が 2 つ");
  wait_for_key();

  // 場面 3：断片化と再検索
  Request(mm, "f", 4);                        // 3 フレームの穴には入らない
  Request(mm, "g", 3);                        // 先頭の穴にちょうど入る
  wait_for_key();
  mm.Dump("5. f, g を確保した後");
  wait_for_key();

  // 場面 4：メモリ不足エラー
  Request(mm, "h", 30);                       // 空きは計 32 個あるが連続 30 個はない
  wait_for_key();
  mm.Dump("6. h を確保できなかった後");
}
// #@@range_end(main)
