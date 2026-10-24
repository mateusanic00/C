#include <stdio.h>
#include <windows.h>

int main(void) {
    int delay_ms = 50;
    int duration_s = 0;
    INPUT input[2] = {0};
    int total = 0;


    printf("Press 'F6' to exit the program\n");
    printf("Enter the delay in ms: ");
    scanf("%d", &delay_ms);
    printf("You typed %d\n", delay_ms);
    
    printf("Enter the duration in seconds: ");
    scanf(" %d", &duration_s);
    printf("You typed %d \n", duration_s);

    printf("Move the mouse to the target...\n");
    printf("3\n");
    Sleep(1000);
    printf("2\n");
    Sleep(1000);
    printf("1\n");
    Sleep(1000);

    DWORD start = GetTickCount();

     
    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    
    while (!(GetAsyncKeyState(VK_F6) & 0x8000))
     {
        if (duration_s > 0 && GetTickCount() - start >= duration_s * 1000)
        {
            break;
        }

        UINT sent = SendInput(2, input, sizeof(INPUT));
        Sleep(delay_ms);
        total++;
        
     }
    printf("Total clicks: %d", total);
    return (0);
}