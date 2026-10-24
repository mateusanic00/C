#include <stdio.h>
#include <windows.h>

//made by Mateus

int delay_ms = 50;
    int duration_s = 0;
    INPUT input[2] = {0};
    int total = 0;


    void start (void) {
        DWORD start = GetTickCount();
        
        while (!(GetAsyncKeyState(VK_F6) & 0x8000))
     {
        
        if (duration_s > 0 && GetTickCount() - start >= duration_s * 1000) {
        break;
            }
            click();
        Sleep(delay_ms);
     }
        
    }

    void click (void) {
    DWORD up = MOUSEEVENTF_LEFTUP;
    DWORD down = MOUSEEVENTF_LEFTDOWN;

    input[0].type = INPUT_MOUSE;
    input[0].mi.dwFlags = down;
    input[1].type = INPUT_MOUSE;
    input[1].mi.dwFlags = up;

    UINT sent = SendInput(2, input, sizeof(INPUT));

    if (sent == 2)
        {
            total++;
        }
}


int main(void) {
    


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

    
    
    
    printf("Total clicks: %d", total);
    return (0);
}