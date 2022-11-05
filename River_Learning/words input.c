#include<stdio.h>
#include<string.h>

int main()
{
    FILE *fp;
    int n,i,j,nn;
    char word[100][30], ans_letter, word2[30], input;

    fp = fopen("words.txt", "r");

    for(i=0;i<10;i++){
        fgets(word[i], 30, fp);
    }
    //scanf("%d",&j);
    int k =1;
    srand(time(NULL));
    while(k){
        n=rand()%10;
        //puts(word[n]);
        int len = strlen(word[n]);
        nn=rand()%(len-1);
        ans_letter=word[n][nn];
        strcpy(word2,word[n]);
        word2[nn]='_';
        puts(word2);

        scanf("%c",&input);
        fflush(stdin);
        if(input != ans_letter)k=0;
        else k = 1;
    }
}
