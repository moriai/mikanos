/**
 * @file observe.cpp
 *
 * BitmapMemoryManager の動作を観察するための機能（サンプルで追加したファイル）．
 */

#include "observe.hpp"

#include <cstdio>

#include "memory_manager.hpp"

bool trace = false;

// #@@range_begin(trace)
// 先頭フレームが使用中で 1 つずつ進む区間は、まとめて 1 行で表示する
void Trace(size_t start, const char* what, size_t used) {
  static size_t run_begin = 0, run_end = 0;  // まとめ中の区間 [run_begin, run_end]
  static bool in_run = false;
  if (!trace) return;

  bool step_by_one = used != 0 && used == start;  // 先頭が使用中 → 次は start + 1
  if (step_by_one && in_run && start == run_end + 1) {
    run_end = start;
    return;
  }
  if (in_run) {
    if (run_begin == run_end) {
      printf("  frame %zu から：frame %zu が使用中\n", run_begin, run_begin);
    } else {
      printf("  frame %zu〜%zu から：先頭が使用中 → 1 つずつ進む\n", run_begin, run_end);
    }
    in_run = false;
  }
  if (step_by_one) {
    run_begin = run_end = start;
    in_run = true;
  } else if (used) {
    printf("  frame %zu から：frame %zu が使用中 → %zu から再検索\n", start, used, used + 1);
  } else {
    printf("  frame %zu から：%s\n", start, what);
  }
}
// #@@range_end(trace)

// alloc_map_ の 1 要素を 1 行に表示する．# = 使用中, . = 空き, - = 管理範囲外
// #@@range_begin(dump)
void BitmapMemoryManager::Dump(const char* title) const {
  printf("\n[%s]\n", title);
  for (size_t n = 0; n < alloc_map_.size(); ++n) {
    printf("  alloc_map_[%zu] = 0x%02x  frame %2zu-%2zu: ",
           n, alloc_map_[n], n * kBitsPerMapLine, (n + 1) * kBitsPerMapLine - 1);
    for (size_t m = 0; m < kBitsPerMapLine; ++m) {
      FrameID f{n * kBitsPerMapLine + m};
      bool in_range = range_begin_.ID() <= f.ID() && f.ID() < range_end_.ID();
      putchar(!in_range ? '-' : GetBit(f) ? '#' : '.');
    }
    putchar('\n');
  }
}
// #@@range_end(dump)
