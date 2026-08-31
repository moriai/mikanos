# Commentary on MikanOS day03a

## MikanOS ブートローダの実行の流れ

[ブートローダのエントリポイントをUefiMainと名付ける](MikanLoaderPkg/Main.c#L114-L111)
1. [物理メモリマップ情報を取得する](MikanLoaderPkg/Main.c#L119-L118)
1. [ブートファイルシステムのルートディレクトリを開く](MikanLoaderPkg/Main.c#L122-L121)
1. [物理メモリマップ情報をファイルに保存する](MikanLoaderPkg/Main.c#L130-L124)
1. [カーネルファイルを読み込む](MikanLoaderPkg/Main.c#L153-L131)
    + [カーネルファイルを開く](MikanLoaderPkg/Main.c#L136-L133)
    + [カーネルファイルのサイズを取得する](MikanLoaderPkg/Main.c#L145-L137)
    + [カーネルのベースアドレスを設定する](MikanLoaderPkg/Main.c#L147-L146)
    + [カーネルファイル全体を読み込めるサイズのメモリを確保する](MikanLoaderPkg/Main.c#L150-L147)
    + [カーネルファイル全体を読み込む](MikanLoaderPkg/Main.c#L151-L150)
1. [EFIブートサービスを終了する](MikanLoaderPkg/Main.c#L170-L154)
1. [エントリポイントアドレスを計算する](MikanLoaderPkg/Main.c#L173-L172)
1. [エントリポイントを呼び出す](MikanLoaderPkg/Main.c#L177-L174)

## メモリマップの取得

+ [メモリマップ構造体](MikanLoaderPkg/Main.c#L19-L11)
+ [メモリマップを取得する](MikanLoaderPkg/Main.c#L33-L20)
