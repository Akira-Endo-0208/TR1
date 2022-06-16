#include <stdio.h>
#include <windows.h>
#include <windows.h>
#include <Sensapi.h>
#include <ShlDisp.h>
#pragma comment(lib, "Sensapi.lib")


// アクセス権の定数
#define OPEN_PROCESS_TOKEN      (TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY)

// プロセスハンドルから特権名を有効/無効
BOOL ProcessPrivilegeName(HANDLE hProcess, LPCTSTR lpPrivilegeName, BOOL bEnable)
{
    BOOL bSuccess = FALSE;          // 戻り値(成功/失敗)
    HANDLE              hToken;     // アクセストークンのハンドル
    LUID                Luid;       // LUID(ローカル・ユニークID)
    DWORD               dwSize;     // 特権トークン容量(変更前の特権)
    TOKEN_PRIVILEGES    OldPriv;    // 特権トークン情報(変更前の特権)
    TOKEN_PRIVILEGES    NewPriv;    // 特権トークン情報(新しい特権)

    // アクセストークンのハンドルを取得
    if (OpenProcessToken(hProcess, OPEN_PROCESS_TOKEN, &hToken)) {
        if (LookupPrivilegeValue(NULL, lpPrivilegeName, &Luid)) {    // 特権名のLUIDを取得
            NewPriv.PrivilegeCount = 1;                // 特権数
            NewPriv.Privileges[0].Luid = Luid;             // 識別子
            NewPriv.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;

            // 特権トークン状態の有効/無効
            if (AdjustTokenPrivileges(hToken, FALSE, &NewPriv, sizeof(TOKEN_PRIVILEGES), &OldPriv, &dwSize)) {
                if (GetLastError() == ERROR_SUCCESS) {
                    bSuccess = TRUE;
                }
            }
        }
        CloseHandle(hToken);
    }
    return bSuccess;
}

// メイン関数
int main(void)
{
    UINT uFlag = 0;
    UINT uMenu = 0;

    do {
        printf(TEXT("\n"));
        printf(TEXT("1...ログオフ\n"));
        printf(TEXT("2...パワーオフ\n"));
        printf(TEXT("3...再起動\n"));
        printf(TEXT("4...シャットダウン\n"));
        scanf_s(TEXT("%d"), &uMenu);

        switch (uMenu) {
        case 1:     uFlag = EWX_LOGOFF;     break;
        case 2:     uFlag = EWX_POWEROFF;   break;
        case 3:     uFlag = EWX_REBOOT;     break;
        case 4:     uFlag = EWX_SHUTDOWN;   break;
        case 5:
        default:    uMenu = 0;              break;
        }
    } while (uMenu == 0);

    ProcessPrivilegeName(GetCurrentProcess(), SE_SHUTDOWN_NAME, TRUE);
    // ログオフ/パワーオフ/再起動/シャットダウンを実行する
    ExitWindowsEx(uFlag, 0);
    return 0;
}