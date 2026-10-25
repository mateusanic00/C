#include <stdio.h>
#include <string.h>

int main (void) {
    char string[] = "Mateus";
    char list[6];
    

    for (int index = 0; index < strlen(string); index++) 
    {
        char character = printf("%c\n", string[index]);
        list[index] = character;
    }

    return (0);
}