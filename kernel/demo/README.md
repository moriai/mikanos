# MikanOS (tag: osbook2_day08c) bitmap memory manager デモ

## ビルドと実行

```
$ make
$ ./memory_manager_demo [ -q | --quiet ]
```

## 出力例

```

[1. 初期状態：すべて空き]
  alloc_map_[0] = 0x00  frame  0- 7: ........
  alloc_map_[1] = 0x00  frame  8-15: ........
  alloc_map_[2] = 0x00  frame 16-23: ........
  alloc_map_[3] = 0x00  frame 24-31: ........
  alloc_map_[4] = 0x00  frame 32-39: ........
  alloc_map_[5] = 0x00  frame 40-47: ........
  alloc_map_[6] = 0x00  frame 48-55: ........
  alloc_map_[7] = 0x00  frame 56-63: ........

[2. 予約済み領域の登録後]
  alloc_map_[0] = 0x00  frame  0- 7: -.......
  alloc_map_[1] = 0x0f  frame  8-15: ####....
  alloc_map_[2] = 0x00  frame 16-23: ........
  alloc_map_[3] = 0x00  frame 24-31: ........
  alloc_map_[4] = 0x00  frame 32-39: ........
  alloc_map_[5] = 0x00  frame 40-47: ........
  alloc_map_[6] = 0x00  frame 48-55: ........
  alloc_map_[7] = 0x00  frame 56-63: --------

a = Allocate(3)
  frame 1 から：空き
  => frame 1-3 を確保

b = Allocate(6)
  frame 1〜3 から：先頭が使用中 → 1 つずつ進む
  frame 4 から：frame 8 が使用中 → 9 から再検索
  frame 9〜11 から：先頭が使用中 → 1 つずつ進む
  frame 12 から：空き
  => frame 12-17 を確保

c = Allocate(4)
  frame 1〜3 から：先頭が使用中 → 1 つずつ進む
  frame 4 から：空き
  => frame 4-7 を確保

d = Allocate(3)
  frame 1〜17 から：先頭が使用中 → 1 つずつ進む
  frame 18 から：空き
  => frame 18-20 を確保

e = Allocate(2)
  frame 1〜20 から：先頭が使用中 → 1 つずつ進む
  frame 21 から：空き
  => frame 21-22 を確保

[3. a〜e を確保した後]
  alloc_map_[0] = 0xfe  frame  0- 7: -#######
  alloc_map_[1] = 0xff  frame  8-15: ########
  alloc_map_[2] = 0x7f  frame 16-23: #######.
  alloc_map_[3] = 0x00  frame 24-31: ........
  alloc_map_[4] = 0x00  frame 32-39: ........
  alloc_map_[5] = 0x00  frame 40-47: ........
  alloc_map_[6] = 0x00  frame 48-55: ........
  alloc_map_[7] = 0x00  frame 56-63: --------

[4. a と d を解放した後：3 フレームの穴が 2 つ]
  alloc_map_[0] = 0xf0  frame  0- 7: -...####
  alloc_map_[1] = 0xff  frame  8-15: ########
  alloc_map_[2] = 0x63  frame 16-23: ##...##.
  alloc_map_[3] = 0x00  frame 24-31: ........
  alloc_map_[4] = 0x00  frame 32-39: ........
  alloc_map_[5] = 0x00  frame 40-47: ........
  alloc_map_[6] = 0x00  frame 48-55: ........
  alloc_map_[7] = 0x00  frame 56-63: --------

f = Allocate(4)
  frame 1 から：frame 4 が使用中 → 5 から再検索
  frame 5〜17 から：先頭が使用中 → 1 つずつ進む
  frame 18 から：frame 21 が使用中 → 22 から再検索
  frame 22 から：frame 22 が使用中
  frame 23 から：空き
  => frame 23-26 を確保

g = Allocate(3)
  frame 1 から：空き
  => frame 1-3 を確保

[5. f, g を確保した後]
  alloc_map_[0] = 0xfe  frame  0- 7: -#######
  alloc_map_[1] = 0xff  frame  8-15: ########
  alloc_map_[2] = 0xe3  frame 16-23: ##...###
  alloc_map_[3] = 0x07  frame 24-31: ###.....
  alloc_map_[4] = 0x00  frame 32-39: ........
  alloc_map_[5] = 0x00  frame 40-47: ........
  alloc_map_[6] = 0x00  frame 48-55: ........
  alloc_map_[7] = 0x00  frame 56-63: --------

h = Allocate(30)
  frame 1〜17 から：先頭が使用中 → 1 つずつ進む
  frame 18 から：frame 21 が使用中 → 22 から再検索
  frame 22〜26 から：先頭が使用中 → 1 つずつ進む
  frame 27 から：範囲の終わりに到達
  => エラー: kNoEnoughMemory

[6. h を確保できなかった後]
  alloc_map_[0] = 0xfe  frame  0- 7: -#######
  alloc_map_[1] = 0xff  frame  8-15: ########
  alloc_map_[2] = 0xe3  frame 16-23: ##...###
  alloc_map_[3] = 0x07  frame 24-31: ###.....
  alloc_map_[4] = 0x00  frame 32-39: ........
  alloc_map_[5] = 0x00  frame 40-47: ........
  alloc_map_[6] = 0x00  frame 48-55: ........
  alloc_map_[7] = 0x00  frame 56-63: --------
```
