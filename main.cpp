#include <stdio.h>
#include <windows.h>
#include <Sensapi.h>
#include <ShlDisp.h>
#pragma comment(lib, "Sensapi.lib")

int main()
{
    BOOL isConnected = 0;
    BOOL oldIsConnected = 0;
    DWORD kindofNetwork;
    while(1)
    { 


    oldIsConnected = isConnected;
    isConnected = IsNetworkAlive(&kindofNetwork);


    if (isConnected == TRUE) {
        if (kindofNetwork == NETWORK_ALIVE_LAN) {
            printf("�l�b�g���[�N�ɐڑ���\n");
        }
        else{
            printf("���z�l�b�g���[�N�T�[�o�[�ɐڑ���\n");
        }
    }
    else {
        printf("�l�b�g���[�N�ڑ��͂���Ă��܂���B\n");
    }

    
    }
   /* ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Undertale\\UNDERTALE.exe", NULL, NULL, SW_SHOWNA);
    ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Steam\\steamapps\\common\\DELTARUNEdemo\\DELTARUNE.exe", NULL, NULL, SW_SHOWNA);*/
    return 0;
}