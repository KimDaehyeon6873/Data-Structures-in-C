#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 13

void swap(int* i, int* j)
{
    int temp;

    temp = *i;
    *i = *j;
    *j = temp;
}

// maxValue를 찾아서 내림차순으로 정렬하기.
int main(int argc, char* argv[])
{
    int randomArray[ARRAY_SIZE] = { 7,2,29,8,40,1,21,6,90,63,10,3,14 };

    //라운드
    for(int j=0; j<ARRAY_SIZE - 1; j++)
    {
        int maxValue = -2147483648; //매 라운드마다 maxValue는 int의 가장 작은 값으로 출발
        int maxIndex = -1; //유효하지 않은 인덱스이지만 첫 턴에 무조건 maxValue가 바뀌면서서 유효인덱스로 지정
        
        //턴
        for(int i=j; i<ARRAY_SIZE; i++)
        {
            if (maxValue < randomArray[i])
            {
                maxValue = randomArray[i];       
                maxIndex = i;
            }
        }

        if(j != maxIndex) swap(&randomArray[j], &randomArray[maxIndex]);
        
    }

    for(int i=0; i<ARRAY_SIZE; i++) printf("%d ", randomArray[i]); //현재 턴 대상 배열의 가장 왼쪽으로 옮기기

    return 0;
}