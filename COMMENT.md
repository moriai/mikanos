# Commentary on MikanOS day06c

## ポーリングでマウス入力

### [PCI バスから xHC を探す](kernel/main.cpp#L139-L154)
+ [見つかったデバイス数だけ繰り返す](kernel/main.cpp#L140-L149)
    + [クラスコードが 0x0c0330 なら xhc_dev にデバイスを代入](kernel/main.cpp#L141-L143)
    + [ベンダーID が 0x8086（インテル）ならループを出る](kernel/main.cpp#L144-L146)
+ [見つかった xHC をログに出力する](kernel/main.cpp#L150-L154)

### [xHC の制御レジスタのアドレスを読み取る](kernel/main.cpp#L157-L161)
+ xhc_mmio_base: xHC の制御レジスタのアドレス

### [xHC を初期化し、起動する](kernel/main.cpp#L164-L176)
+ [class usb::xhci::Controller のインスタンスを生成する](kernel/main.cpp#L164)
+ [ベンダーID がインテルだったら、強制的に xHCI モードにする](kernel/main.cpp#L166-L169)
+ [xHC を初期化する](kernel/main.cpp#L169-L173)
+ [xHC を起動する](kernel/main.cpp#L174-L176)

### [USB ポートを調べ、接続済みポートの設定を行う](kernel/main.cpp#L179-L193)
+ [USB マウスからのデータ受信用の関数を設定する](kernel/main.cpp#L179)
+ [接続されているポート数だけ繰り返す](kernel/main.cpp#L181-L193)
    + [i番目のポートに何か接続されていたら、ポートの設定を行う](kernel/main.cpp#L182-L192)

### [xHC に溜まっているイベントを処理する](kernel/main.cpp#L196-L202)

### [マウスからのイベントを処理する](kernel/main.cpp#L50-L56)
+ MouseCursor クラスのインスタンスの MoveRelative() メソッドを呼び出す

### [MouseCursor クラス](kernel/mouse.hpp#L10-L23)
+ [MouseCursor クラスの本体](kernel/mouse.cpp#L60-L73)