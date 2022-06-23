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

    isConnected = IsNetworkAlive(&kindofNetwork);

    printf("アプリを起動します\n");

    //                                           ↓立ち上げたいアプリの場所のパスを↓の例の通り入れてください
    ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Undertale\\UNDERTALE.exe", NULL, NULL, SW_SHOWNA);
    ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Steam\\steamapps\\common\\DELTARUNEdemo\\DELTARUNE.exe", NULL, NULL, SW_SHOWNA);

     if (isConnected == TRUE) {

    ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Steam\\steamapps\\common\\Undertale\\UNDERTALE.exe", NULL, NULL, SW_SHOWNA);
    ShellExecute(NULL, "open", "C:\\Program Files (x86)\\Steam\\steamapps\\common\\DELTARUNEdemo\\DELTARUNE.exe", NULL, NULL, SW_SHOWNA);
    /*if (isConnected == TRUE) {

        if (kindofNetwork == NETWORK_ALIVE_LAN) {
            printf("ネットワークに接続中\n");
        }
        else {
            printf("仮想ネットワークサーバーに接続中\n");
        }
    }
    else {
        printf("ネットワーク接続はされていません。\n");

    }

    }*/

    while (1)
    {


        


    }
  

}