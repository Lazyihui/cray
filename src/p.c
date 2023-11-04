#include "stdio.h"
void main(){
    int arr[4]={1,2,3,4};
    int index = 2;
    int a = arr[index];
    arr[index]=arr[0];
    arr[0]=a;
    index--;

    for(int i =0; i<=index;i++){
        printf("%d\r\n",arr[i]);
    }
    


}