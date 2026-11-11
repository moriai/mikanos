/**
 * @file observe.hpp
 *
 * BitmapMemoryManager の動作を観察するための機能（サンプルで追加したファイル）．
 */

#pragma once

#include <cstddef>

/** @brief true にすると Allocate の検索の様子を表示する */
extern bool trace;

/** @brief Allocate の検索の様子を 1 行表示する．
 *
 * @param start 調べ始めたフレーム
 * @param what  結果の説明
 * @param used  使用中だったフレーム（使用中で中断したときのみ）
 */
void Trace(size_t start, const char* what, size_t used = 0);
