#include <stdio.h>
#include<stdlib.h>
#include<time.h>
int card[54];                   //54장의 섞인 카드 저장
int deckIndex = 0;              //덱의 카드 뽑기를 위한 순서
int mydeck[54], botdeck[54];    //플레이어 덱과 봇 덱
int field;                      //현재 필드 위의 카드
int choose;                     //카드 내기 또는 뽑기 선택
int num;                        //낼 카드 순서
int mydecknum = 7;              //내 카드 갯수
int botdecknum = 7;
int myturnend = 1;				//내 턴이 끝날떄까지 확인; 
//이름 출력하는 함수 
int cardnameprint(int num)
{
    if (num >= 1 && num <= 13)
        printf("다이아몬드 %d\n", num);
    else if (num >= 14 && num <= 26)
        printf("하트 %d\n", num - 13);
    else if (num >= 27 && num <= 39)
        printf("스페이드 %d\n", num - 26);
    else if (num >= 40 && num <= 52)
        printf("클로버 %d\n", num - 39);
    else if (num == 53)
        printf("흑백 조커\n");
    else if (num == 54)
        printf("컬러 조커\n");
}
//변수를 섞기
void shuffle(int a[], int b)
{
    for (int i = b-1;i > 0;i--)
    {
        int c = rand() % (i+1);
        int temp = a[i];
        a[i] = a[c];
        a[c] = temp;
    }
}
//같은 도형인지 확인. 같은 도형이라면 1, 다른 도형이라면 0. 
int sameshape(int a, int b)
{
	return ((a - 1) / 13 == (b - 1) / 13); 
}
//같은 숫자인지 확인. 같은 숫자라면 1, 다른 숫자라면 0. 
int samenumber(int a, int b)
{
    int na = (a - 1) % 13 + 1;
    int nb = (b - 1) % 13 + 1;
    return (na == nb);
}
int main()
{
    srand(time(NULL));
//card[0]부터 card[53]까지 1부터 54까지 숫자 저장.
    for (int i=0; i<54; i++)
    {
        card[i] = i+1;
    }
//card 섞기.
    shuffle(card, 54);
//mydeck에 card의 0부터 6까지의 숫자를 넣기.
    for (int i=0; i<7; i++)
    {
        mydeck[i] = card[deckIndex++]; 
    }
//mydeck의 7부터 53까지 -1 넣기.
    for (int i=7; i<54; i++)
    {
        mydeck[i] = -1;
    }
//mydeck과 똑같게 봇에게도 카드 나눠주기.
    for (int i=0; i<7; i++)
    {
        botdeck[i] = card[deckIndex++];
    }
    for (int i=7; i<54; i++)
    {
        botdeck[i] = -1;
    }
//필드에 card에서 한장 뽑아서 놓기.
    field = card[deckIndex++];
//상대나 봇 덱의 갯수가 0개가 될떄가지 반복. 
while(mydeckend==0 || botdeckend==0)
{
//내 턴이 끝날때까지 반복되는 함수.
    while (myturnend == 1)
    {
        printf("\n------------ 당신 차례-------------\n당신의 카드 : \n");
        for (int i=0; i<54; i++)
        {
        	if (mydeck[i] != -1)
            cardnameprint(mydeck[i]);
        }
        printf("-----------------------------------\n현재 필드 : ");
        cardnameprint(field);
//카드 내기 또는 뽑기 고르기.
        printf("1. 카드 내기  |  2. 카드 뽑기 : ");
        scanf("%d", &choose);
//카드 내기를 골랐을 떄.
        if (choose == 1)
        {
//몇번째 카드를 낼지 받고, 만약 없는 수라면 다시 고를 수 있게, 있다면 그 카드를 내고 mydeck의 그 자리를 -1로 만들기.
            printf("몇번째 카드를 내겠습니까? : ");
            scanf("%d", &num);
            num--;
            if (num < 0 || num >= 54 || mydeck[num] == -1)
            {
                printf("없는 카드입니다.\n");
                continue;
            }
//현재 필드 위에있는 카드와 도형이나 숫자가 같은지 확인하기.
            if (sameshape(mydeck[num], field) || samenumber(mydeck[num], field))
            {
                field = mydeck[num];
                mydeck[num] = -1;
                printf("당신이 낸 카드 : ");
                cardnameprint(field);
                myturnend=0;
            }
//낼 수 없다면 다시 고를 수 있게 돌아가기.
            else
            {
                printf("낼 수 없는 카드입니다.\n");
                continue;
            }
        }
//뽑기 카드를 골랐을 떄.
        else if (choose == 2)
        {
//mydeck에서 -1이 나올때까지 반복하다가, 만약 만나면 그 곳에 카드 넣어주고 끝내기.
            for (int i=0; i<54; i++)
            {
                if (mydeck[i] == -1)
                {
                	printf("당신이 카드를 뽑았습니다.\n");
                    mydeck[i] = card[deckIndex++];
                    mydecknum++; 
                    myturnend=0;
					break;
                }
            }
        }
//만약 내 카드가 0개가 된다면 승리하기. 
        if (mydecknum==0)
        {
        	printf("\n\n------당신이 승리했습니다!-----\n");
            break;
		}
	}
//봇 턴 시작. 
	printf("\n------------봇 차례------------\n");
    int botPlayed = 0;
//낼 수 있는 카드 찾아보기. 
    for (int i = 0; i < 54; i++)
    {
       	if (botdeck[i] != -1)
    	{
        	if (sameshape(botdeck[i], field) || samenumber(botdeck[i], field))
        	{
        	    printf("봇이 낸 카드 : ");
        	    cardnameprint(botdeck[i]);
        	    field = botdeck[i];
        	    botdeck[i] = -1;
        	    botdecknum--;
        	    botPlayed = 1;
        	    break;
        	}
    	}
    }
//없다면 뽑기. 
    if (!botPlayed)
    {
        printf("봇이 카드를 뽑습니다.\n");
        for (int i = 0; i < 54; i++)
        {
            if (botdeck[i] == -1)
            {
            	botdeck[i] = card[deckIndex++];
                botdecknum++;
                break;
            }
        }
    }
//다시 내턴 가져오기.
		myturnend = 1;
}
        // 승리 체크
        if (botdecknum == 0)
        {
            printf("\n\n------봇이 승리했습니다!-----\n");
            break;
        }
    }
	return 0;
}