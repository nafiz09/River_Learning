# include "iGraphics.h"
# include <stdio.h>
# include <string.h>
# include <time.h>
# include <ctype.h>
# include <windows.h>
# include <mmsystem.h>

int f = 0, log1_y = 600, len=0, m3, mm3, log2_y = 800, m1, m2, mm1, mm2, point = 0,x=3, c_point = 0, waiting = 0;
int i, ans_f =0, p, c, s, l, log3_y = 1000, c3=0, c4 = 0, lev=50, type = 0, life = 3, log4_y = 1200,pq=0, level=0;
int file_f=0, sq_x = 400, sq_y = 400, flag =0;
char n1[4], nn1[4], c1 = 0, c2 = 0, score[4],lives[3], in_name[20], str_level[4];
char ch, in_ans[100], in_ans2[100], log1_math[4], log2_math[4],signs[4]={'+','-','x','/0'};
char colour[5][50] = {"Red","Green", "Orange", "Blue", "Purple"};
char shape[5][50] = {"Square", "Circle", "Triangle", "Diamond", "Pentagon"};
FILE *fp, *fp_hs;
int nth, j, nn, sound=1;
char word[50][30], ans_letter, word2[30], input;
struct highscore{
    char name[20];
    char score_str[20];
    int score;
};

struct highscore hs[5];

void log1_y_dec(void);
void log2_y_dec(void);
void score_in(void);
int intConvert(char in_ans[]);

void music_on(int y)
{
    if (y==0)PlaySound(NULL, 0,0);
    if(sound==1){
        if (y==1)PlaySound(TEXT("ping.wav"), NULL, SND_ASYNC);
        //if (y==2)PlaySound(TEXT("wrong.wav"), NULL, SND_ASYNC);
        if (y==3)PlaySound(TEXT("loss.wav"), NULL, SND_ASYNC);
        if (y==4)PlaySound(TEXT("game-over.wav"), NULL, SND_ASYNC);
        if (y==5)PlaySound(TEXT("congrats.wav"), NULL, SND_ASYNC);
        if (y==6)PlaySound(TEXT("movinout.wav"), NULL, SND_LOOP|SND_ASYNC);
        if (y==7)PlaySound(TEXT("riverflow.wav"), NULL, SND_LOOP|SND_ASYNC);
    }
}

void initialize(){
    music_on(0);
    music_on(6);
    f = 0;
    log1_y = 600, log2_y = 800, log3_y = 1000, log4_y = 1200;
    point = 0;
    c1=0, c2=0, c3 = 0, c4 =0;
    x=3;
    life = 3;
    file_f = 0;
}


void high_score_check(int score)
{
    int i=0, j;

    fp_hs = fopen("highscores.txt", "r");

    /*if(fp_hs==NULL){
        printf("Error");
        return;
    }*/

    for(i=0; i<=5; i++){
        fscanf(fp_hs, "%s %d", hs[i].name, &hs[i].score);
    }

    fclose(fp_hs);

    for(i=0; i<5; i++){
        if(score>=hs[i].score){
            file_f = 1;
            break;
        }
    }

    if(score == hs[4].score) file_f = 0;

    return;
}

void high_score_add(int score)
{
    int i=0, j, t;
    char t_name[20];

    fp_hs = fopen("highscores.txt" , "w");
    strcpy(hs[4].name, in_name);
    hs[4].score = score;
    for(i=0; i<5; i++){
        for(j=i+1; j<5; j++){
            if(hs[i].score < hs[j].score){
                t = hs[j].score;
                hs[j].score = hs[i].score;
                hs[i].score = t;
                strcpy(t_name, hs[j].name);
                strcpy(hs[j].name, hs[i].name);
                strcpy(hs[i].name, t_name);
            }
        }
    }


    for(i=0; i<5; i++)
        fprintf(fp_hs, "%s %d\n", hs[i].name, hs[i].score);

    fclose(fp_hs);
}


int intConvert(char in_ans[])
{
    /*this function converts a string of numbers to interger number. it's parameter is the string that takes input from the keyboard
    it will be cosidered the ans to the math expression.*/
    int i, ans, k=0;
    ans = in_ans[strlen(in_ans) - 1] - 48;
    if(in_ans[0]=='-')k=1;
    for (i = strlen(in_ans) - 2; i >= k; i--){
        ans = ans + (in_ans[i] - 48)*10;
    }
    if(k==0)return ans;
    else return ans*-1;
}

int colour_exp()
{
    c = rand()%5;
    return c;
}

int shape_exp()
{
    s = rand()%5;
    return s;
}

void word_exp()
{
    int nth=rand()%45;
    int len = strlen(word[nth]);
    word[nth][len] = '\0';
    nn=rand()%(len-1);
    ans_letter=word[nth][nn];
    strcpy(word2,word[nth]);
    word2[nn]='_';
    word2[len-1] = '\0';
}

void loss(int n)
{
    life--;
    music_on(0);
    music_on(3);
    //waiting = 0;
    //music_on(7);
    if(life == 0 )
    {
        f = 4;
        music_on(4);
        c_point = 0;
    }
    if(n==1)log1_y += 800, c1 = 0;
    else if (n==2) log2_y += 800, c2=0;
    else if (n==3) log3_y += 800, c3=0;
    else log4_y += 800, c4=0;

}

void math_sum_exp(void)
{
    /*generates a mathematical expression with a plus sign.
    PROBLEM: once compiles it gives the same expresion until it is compiled again*/
    //int m1, m2;
    srand(time(NULL));
    m1 = rand() % 10;
    n1[0] = 48 + m1;
    //n1[1] = '+';
    m2 = rand() % 10;
    n1[2] = 48 + m2;
    n1[3] = '=';
    //m3 = m1 + m2;
    n1[4] = '\0';

    int sign1 = rand() % 3;
    n1[1] = signs[sign1];

    if(sign1 == 0) m3 = m1 + m2;
    else if (sign1 == 1) m3 = m1 - m2;
    else m3 = m1 * m2;

    strcpy(log1_math,n1);
}

void log1_y_dec(void)
{
    /*decreases the logs y co-ordinate to lower it. if the log crashes with the boat y coordinate is set back to initial*/
    if (f == 1)
    {
            log1_y -= x;
            log2_y -= x;
            log3_y -= x;
            log4_y -= x;
    }
}

void done(int nnn)
{
    point += 5;
    music_on(0);
    music_on(1);
    //waiting = 0;
    //music_on(7);
    switch (nnn)
    {
    case 1:
        log1_y += 800;
        c1 = 0;
        break;
    case 2:
        log2_y += 800;
        c2 = 0;
        break;
    case 3:
        log3_y += 800;
        c3 = 0;
        break;
    default:
        log4_y += 800;
        c4 = 0;
        break;
    }
}
/*
function iDraw() is called again and again by the system.
*/
void iDraw()
{
    iClear();
    if (f == 0)
    {
        ///home screen

        //music_on();
        iShowBMP(0, 0, "home back.bmp");
        iSetColor(10, 255, 100);
        iFilledRectangle(130, 300, 240, 50);///lower box
        iFilledRectangle(130, 350, 240, 50);///middle box
        iFilledRectangle(130, 400, 240, 50);///upper box
        iFilledRectangle(130, 450, 240, 50);///high score

        iSetColor(250,100,10);
        iFilledRectangle(135, 305, 230, 40);///lower box
        iFilledRectangle(135, 355, 230, 40);///middle box
        iFilledRectangle(135, 405, 230, 40);
        iFilledRectangle(135, 455, 230, 40);


        iSetColor(0, 0, 0);
        iRectangle(130, 300, 240, 50);///lower box
        iRectangle(130, 350, 240, 50);///middle box
        iRectangle(130, 400, 240, 50);///upper box
        iRectangle(130, 450, 240, 50);///high score

        iSetColor(10,10,255);
        iFilledRectangle(373,33,137,40);


        iSetColor(255, 255, 255);
        iText(215, 470, "START", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(165, 420, "INSTRUCTIONS", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(175, 365, "HIGH SCORES", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(220, 315, "QUIT", GLUT_BITMAP_TIMES_ROMAN_24);

        iText(380, 45," CREDITS ", GLUT_BITMAP_TIMES_ROMAN_24);

        if(sound==1)iShowBMP(32,5,"sound_icon.bmp");
        else iShowBMP(32,5,"mute_icon.bmp");
    }

    if (f == 1)
    {
        ///main game page


        ///Back ground image
        iSetColor(47, 141, 255);
        iFilledRectangle(100, 0, 300, 600);

        iSetColor(0, 0, 0);
        iText(290,60,"YOUR ANSWER:");

        level = point/50;
        x = 3 + level;
        //iText(320,40,in_ans, GLUT_BITMAP_TIMES_ROMAN_24);

        //if(stop_dec==0){
        //if (intConvert(in_ans2) != m3){
        iShowBMP(100, log1_y, "log1.bmp");
        if (c1 == 0){
            math_sum_exp();
            //puts(n1);
            c1++;
        }

        iSetColor(255, 255, 255);
        iText(240, log1_y + 25, log1_math, GLUT_BITMAP_9_BY_15);


        //}

        iShowBMP(100,log2_y, "log2.bmp");
        if (c2 == 0){
            c = colour_exp();
            c2++;
        }

        iText(240, log2_y + 25, colour[c], GLUT_BITMAP_9_BY_15);

        iShowBMP(100, log3_y, "log1.bmp");
        if (c3 == 0){
            s = shape_exp();
            //puts(n1);
            c3++;
        }

        iText(240, log3_y + 25, shape[s], GLUT_BITMAP_9_BY_15);

        iShowBMP(100,log4_y, "log2.bmp");
        if (c4 == 0){
            word_exp();
            c4++;
        }

        iText(240, log4_y + 25, word2, GLUT_BITMAP_9_BY_15);

        iSetColor(0, 0, 0);
        iText(320,40,in_ans, GLUT_BITMAP_TIMES_ROMAN_24);

        //if (intConvert(in_ans2) == mm3)
        //    stop_dec = 2;
        // this portion checks keyboard input string converted to an integer and compares it to the actual answer of the expression
        //if they match stops loading the log image
        // PROBLEM: Doesn't set the log back, doesn't work for continuos logs.
        iSetColor(0, 0, 0);
        iFilledRectangle(0, 600, 500, 50);

        ///level
        iSetColor(255, 255, 255);
        iText(20, 620, "LEVEL: ");

        l = level+1;
        for(i=1;i>=0;i--){
            str_level[i] = l%10 + 48;
            l /= 10;
        }
        str_level[2]='\0';

        iText(80,620,str_level);

        ///life
        if(life > 2)
            iShowBMP(380, 610, "heart.bmp");
        if(life > 1)
            iShowBMP(420, 610, "heart.bmp");
        if(life > 0)
            iShowBMP(460, 610, "heart.bmp");
        //iSetColor(255, 255, 255);
        //iText(420, 620, "Life: ");

        lives[0] = '0';
        lives[1] = life%10 + 48;
        lives[2] = '\0';

        //iText(480,620,lives);

        ///SCORE
        iSetColor(255, 255, 255);
        iText(200, 620, "SCORE: ");

        p = point;
        for(i=2;i>=0;i--){
            score[i] = p%10 + 48;
            p /= 10;
        }
        score[3]='\0';

        iSetColor(255, 255, 255);
        iText(260,620,score);

        iText(30, 550, "SHAPES");
        iText(430, 550, "COLORS");

        iSetColor(255, 255, 255);
        iShowBMP(218, 0, "boat.bmp");

        iLine(0, 600, 500, 600);///draws horizontal line

        ///for shapes buttons
        iSetColor(255, 0, 0);///square
        iFilledRectangle(0, 0, 100, 100);

        iSetColor(0, 255, 0);///circle
        iFilledRectangle(0, 100, 100, 100);

        iSetColor(255, 173, 47);///triangle
        iFilledRectangle(0, 200, 100, 100);

        iSetColor(0, 0, 255);///diamond
        iFilledRectangle(0, 300, 100, 100);

        iSetColor(160, 32, 240);///pentagon
        iFilledRectangle(0, 400, 100, 100);

        iSetColor(255, 255, 255);
        iFilledRectangle(30, 30, 40, 40);
        iFilledCircle(50, 150, 20);
        iFilledCircle(50, 250, 20, 3);
        iFilledEllipse(50, 350, 20, 30, 4);
        iFilledCircle(50, 450, 20, 5);

        ///for color buttons
        iSetColor(255, 0, 0);///red
        iFilledRectangle(400, 0, 100, 100);

        iSetColor(0, 255, 0);///green
        iFilledRectangle(400, 100, 100, 100);

        iSetColor(255, 173, 47);///orange
        iFilledRectangle(400, 200, 100, 100);

        iSetColor(0, 0, 255);///blue
        iFilledRectangle(400, 300, 100, 100);

        iSetColor(160, 32, 240);///purple
        iFilledRectangle(400, 400, 100, 100);

        iSetColor(0, 0 ,0);
        iRectangle(sq_x, sq_y, 100, 100);

        if (log1_y <= 124)loss(1);
        if (log2_y <= 124)loss(2);
        if (log3_y <= 124)loss(3);
        if (log4_y <= 124)loss(4);
       // PlaySound(TEXT("movinout.wav"),NULL,SND_SYNC);
        //while(waiting>2000)music_on(7);

    }
    if (f == 2)
    {
        ///instruction page
        iShowBMP(0, 0, "ins.bmp");
        iSetColor(255, 255, 255);

        iRectangle(180,95,150,40);
        iText(200, 110, "GO BACK ", GLUT_BITMAP_TIMES_ROMAN_24);

    }
    if (f == 3)
    {
        ///quit button
        exit(1);
    }
    if (f == 4)
    {
        ///end screen

        iShowBMP(0,0,"game_over.bmp");

        iSetColor(256,0,0);
        iText(290, 372, score, GLUT_BITMAP_TIMES_ROMAN_24);

        iSetColor(0,256,200);
        iRectangle(130,15,260,45);

        high_score_check(point);

    }

    if(f == 5)///congratulation
    {
        iShowBMP(0,0,"congrats.bmp");
        //iText(180, 550, "CONGRATULATIONS", GLUT_BITMAP_TIMES_ROMAN_24);
        //iText(180, 450, "YOU HAVE MADE A HIGHSCORE", GLUT_BITMAP_9_BY_15);
        //iText(150, 300, "ENTER YOUR NAME: ", GLUT_BITMAP_9_BY_15);
        iSetColor(256,10,0);
        iText(200, 100, in_ans, GLUT_BITMAP_TIMES_ROMAN_24);
    }

    if(f==6) ///High Score
    {
        fp_hs = fopen("highscores.txt", "r");
        for(i=0;i<5;i++)
        {
            fscanf(fp_hs, "%s %s", hs[i].name, hs[i].score_str);
        }

        fclose(fp_hs);

        for(i=0;i<5;i++)
        {
            iSetColor(0,256,0);
            //iRectangle(0,0,500,650);

            //iSetColor(0,0,0);
            iText(150,500,"HIGH SCORES: ", GLUT_BITMAP_TIMES_ROMAN_24);
            iLine(145,480,320,480);

            for(i=0;i<5;i++)
            {
                char ii[2] = {i+49,'\0'};
                iText(100,430-50*i,ii, GLUT_BITMAP_TIMES_ROMAN_24);
                iText(130,430-50*i,hs[i].name, GLUT_BITMAP_TIMES_ROMAN_24);
                iText(290,430-50*i,hs[i].score_str, GLUT_BITMAP_TIMES_ROMAN_24);
            }
        }

        iRectangle(180,95,150,40);
        iText(200, 110, "GO BACK ", GLUT_BITMAP_TIMES_ROMAN_24);
    }

    ///credits
    if(f==7)
    {
        iShowBMP(0, 0, "credits.bmp");
        iRectangle(180,95,150,40);
        iText(200, 110, "GO BACK ", GLUT_BITMAP_TIMES_ROMAN_24);

    }
}

/*
function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //place your codes here
}
/*
function iMouse() is called when the user presses/releases the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        if (mx>130 && my>450 && mx <370 && my<500 && f == 0)
        {
            f = 1;
            music_on(0);
            music_on(7);
        }
        if (mx>130 && my>400 && mx <370 && my<450 && f == 0)
        {
            f = 2;
        }
        if (mx>130 && my>350 && mx <370 && my<400 && f == 0)
        {
            f = 6;
        }
        if (mx>130 && my>300 && mx <370 && my<350 && f == 0)
        {
            f = 3;
        }
        if (mx>373 && mx<500 && my>33 && my<73 && f == 0)
        {
            f = 7;
        }

        ///volume
        if(mx>32 && mx<64 && my>5 && my<37 && f==0)
        {
            if(sound==1){
                sound=0;
                music_on(0);
            }
            else {
                sound=1;
                music_on(6);
            }
        }

        ///Home page again
        if (mx>180 && my>95 && mx <330 && my<135 && f == 2)
        {
            f = 0;
        }
        if (mx>180 && my>95 && mx<330 && my<135 && f == 6)
        {
            f = 0;
        }
        if (mx>180 && my>95 && mx<330 && my<135 && f == 7)
        {
            f = 0;
        }

        ///making high score
        if(mx>0 && my>0 && mx <500 && my <650 && f == 4)
        {
            if (file_f == 1) {
                music_on(5);
                f=5;
            }
            else initialize();
        }

        ///colour answer
        if(log2_y < 600 && log2_y >= 128)
        {
            ///red
            if(c==0 && mx > 400 && mx < 500 && my > 0 && my < 100)
            done(2);

            ///green
            if(c==1 && mx > 400 && mx < 500 && my > 100 && my < 200)
            done(2);

            ///orange
            if(c==2 && mx > 400 && mx < 500 && my > 200 && my < 300)
            done(2);

            ///blue
            if(c==3 && mx > 400 && mx < 500 && my > 300 && my < 400)
            done(2);


            ///purple
            if(c==4 && mx > 400 && mx < 500 && my > 400 && my < 500)
            done(2);


        }

        ///shape answer
        if(log3_y < 600 && log3_y >= 128)
        {
            ///square
            if(s==0 && mx > 0 && mx < 100 && my > 0 && my < 100)
            done(3);

            ///circle
            if(s==1 && mx > 0 && mx < 100 && my > 100 && my < 200)
            done(3);

            ///Triangle
            if(s==2 && mx > 0 && mx < 100 && my > 200 && my < 300)
            done(3);

            ///diamond
            if(s==3 && mx > 00 && mx < 100 && my > 300 && my < 400)
            done(3);

            ///pentagon
            if(s==4 && mx > 00 && mx < 100 && my > 400 && my < 500)
            done(3);

        }

    }


    ///The Box under the mouse

    if(mx> 0 && mx< 100) sq_x = 0;

    if(mx>400 && mx<500) sq_x = 400;

    if(my>0 && my<100) sq_y = 0;

    if(my>100 && my<200) sq_y = 100;

    if(my>200 && my<300) sq_y = 200;

    if(my>300 && my<400) sq_y = 300;

    if(my>400 && my<500) sq_y = 400;
}
/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    /// takes input from keyboard to a string
    int i;
    if (f == 1){
        if(key == '\r')
        {
            //it'll set the string to zero

            in_ans[len] = '\0';
            strcpy(in_ans2,in_ans);


            for(i=0;i<len;i++)
                in_ans[i] = 0;

            len = 0;

            if(log4_y < 600 && log4_y >= 128)
            {
                if((in_ans2[0]) == ans_letter || (in_ans2[0] - 32) == ans_letter)
                    done(4);
                //else music_on(2);
            }
            if(log1_y < 600 && log1_y >= 128)
            {
                if(intConvert(in_ans2) == m3)
                    done(1);
                //else music_on(2);
            }
        }
        else
        {
            in_ans[len] = key;
            len++;
        }
    }

    if (f == 5){

        if(key == '\r')
        {
            //it'll set the string to zero

            in_ans[len] = '\0';

            strcpy(in_name,in_ans);
            high_score_add(point);
            initialize();

            for(i=0;i<len;i++)
                in_ans[i] = 0;

            len = 0;

        }
        else
        {
            in_ans[len] = key;
            len++;
        }
        /*if(pause == 0 && key == ' '){
            pause = 1;
        }
        if(pause == 1 && key == ' '){
            pause = 0;
        }*/
    }

    //place your codes for other keys here
}
/*
function iSpecialKeyboard() is called whenver user hits special keys likefunction
keys, home, end, pg up, pg down, arraows etc. you have to use
appropriate constants to detect them. A list is:
GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11,
GLUT_KEY_F12, GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN,
GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END,
GLUT_KEY_INSERT */
void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_LEFT && sq_x != 0)
    {
        sq_x = 0;
    }

    if (key == GLUT_KEY_RIGHT && sq_x != 400)
    {
        sq_x = 400;
    }

    if (key == GLUT_KEY_UP && sq_y != 400)
    {
        sq_y += 100;
    }

    if (key == GLUT_KEY_DOWN && sq_y != 0)
    {
        sq_y -= 100;
    }
    //place your codes for other keys here
}

int main()
{
    //place your own initialization codes here.
    //iSetTimer(10000,increase);

    fp = fopen("words.txt", "r");

    for(i=0;i<45;i++){
        fgets(word[i], 30, fp);
    }
    iSetTimer(50, log1_y_dec);
    music_on(6);
    iInitialize(500, 650, "RIVER LEARNING");
    return 0;
}
