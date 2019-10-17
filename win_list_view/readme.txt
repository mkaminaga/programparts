作成日 2019年10月19日
作成者 Mamoru Kaminaga

ListViewコントロールのテストです。


ResEditでリストビューコントロールが含まれるファイルを読み込もうとすると、エラーが出て読み込めない問題が生じている。
以下のコントロールをリソースファイルに手動で追加。

resource.rc
CONTROL         "", IDC_LIST1, WC_LISTVIEW, WS_TABSTOP | WS_BORDER | LVS_ALIGNLEFT | LVS_SHOWSELALWAYS | LVS_REPORT, 5, 5, 180, 240, WS_EX_LEFT

resource.h
#define IDC_LIST1                               40100
