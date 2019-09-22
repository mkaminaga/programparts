簡易キャプチャソフト 　ScreenCaptureTool.exe
2019年9月22日　Mamoru Kaminaga
====
【言い訳】
これは私がWindowsプログラミングの勉強用に作成したものです。
そのため、単純で不親切です。

【概要】
・デスクトップ全画面をキャプチャし、PNGファイルに保存
・保存の過程でクリップボードを介さない
・タスクトレイ常駐型
・PauseやScrLkキーを押すとキャプチャを実行
・出力先フォルダはデフォルトでは実行可能ファイルがあるフォルダ、変更が可能
・ファイル名は日時から自動的で決定

【動作確認済み環境】
Windows 8.1
プロセッサ: Intel(R) Core(TM) i5-5200U CPU @2.20GHz
メモリ: 8.00 GB
OS: Windows 8.1 (64bit)

【インストール・アンインストール】
＜インストール＞
1. libpngをインストールする(インストール済みであればスキップ可)
2. programparts/screen_capture_toolをローカルにコピー
3. makefileを修正する（主に以下の変数のパスの修正）
	CC
	LINK
	CPPFLAGS
	LFLAGS
4. 開発者コマンドプロントなどからnmakeする

＜アンインストール＞
フォルダごと削除してください。

【注意点】
・グローバルフックの使用について
シャッターキーが押されたことを知るために、グローバルフックを使用しています。
グローバルフックはキーロガーに使うことのできてしまう技術です。
このソフトに悪意はありませんが、念のため言及しておきます。

【既知の不具合】
・DPIの関係でスケーリングがおかしくなることがあります
その場合、ScreenCaptureTool.exeを右クリック、プロパティを選択、互換性のタブを開き、「高DPI設定では画面のスケーリングを無効にする」にチェックを入れてみてください。

・シャッターキーを受け付けなくなる
原因は不明です。
ScreenCaptureTool.exeを再起動してください。