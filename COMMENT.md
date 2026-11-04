# Commentary on MikanOS day06b

### [PCIデバイスを列挙する](kernel/main.cpp#L120-L131)
1. [すべてのPCIバスをスキャンする](kernel/main.cpp#L120)
1. [エラーコードを表示する](kernel/main.cpp#L121)
1. [見つかったデバイス数の分だけ繰り返す](kernel/main.cpp#L123-L131)
    + [i番目のデバイスを取り出す](kernel/main.cpp#L124)
    + [ベンダーIDを読み込む](kernel/main.cpp#L125)
    + [クラスコードを読み込む](kernel/main.cpp#L126)
    + [読み込んだ結果を出力する](kernel/main.cpp#L127-130)
