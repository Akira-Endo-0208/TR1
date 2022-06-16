#include <stdio.h>
#include <windows.h>
#include <windows.h>
#include <Sensapi.h>
#include <ShlDisp.h>
#pragma comment(lib, "Sensapi.lib")


// �A�N�Z�X���̒萔
#define OPEN_PROCESS_TOKEN      (TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY)

// �v���Z�X�n���h�������������L��/����
BOOL ProcessPrivilegeName(HANDLE hProcess, LPCTSTR lpPrivilegeName, BOOL bEnable)
{
    BOOL bSuccess = FALSE;          // �߂�l(����/���s)
    HANDLE              hToken;     // �A�N�Z�X�g�[�N���̃n���h��
    LUID                Luid;       // LUID(���[�J���E���j�[�NID)
    DWORD               dwSize;     // �����g�[�N���e��(�ύX�O�̓���)
    TOKEN_PRIVILEGES    OldPriv;    // �����g�[�N�����(�ύX�O�̓���)
    TOKEN_PRIVILEGES    NewPriv;    // �����g�[�N�����(�V��������)

    // �A�N�Z�X�g�[�N���̃n���h�����擾
    if (OpenProcessToken(hProcess, OPEN_PROCESS_TOKEN, &hToken)) {
        if (LookupPrivilegeValue(NULL, lpPrivilegeName, &Luid)) {    // ��������LUID���擾
            NewPriv.PrivilegeCount = 1;                // ������
            NewPriv.Privileges[0].Luid = Luid;             // ���ʎq
            NewPriv.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;

            // �����g�[�N����Ԃ̗L��/����
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

// ���C���֐�
int main(void)
{
    UINT uFlag = 0;
    UINT uMenu = 0;

    do {
        printf(TEXT("\n"));
        printf(TEXT("1...���O�I�t\n"));
        printf(TEXT("2...�p���[�I�t\n"));
        printf(TEXT("3...�ċN��\n"));
        printf(TEXT("4...�V���b�g�_�E��\n"));
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
    // ���O�I�t/�p���[�I�t/�ċN��/�V���b�g�_�E�������s����
    ExitWindowsEx(uFlag, 0);
    return 0;
}