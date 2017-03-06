#include<stdio.h>
int main(void){
    int input , cnt = 0, b;
    scanf("%d" , &input);
    while(input){
        b = input ^ (input & -input);
        if((input & -input) == ((b & -b) >> 1))
            input += (input & -input) , cnt++;
        else input ^= (input & -input) , cnt++;
    }
    printf("%d\n" , cnt);
    return 0;
}
