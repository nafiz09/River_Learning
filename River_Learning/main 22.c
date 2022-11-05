# include "iGraphics.h"
# include <stdio.h>
# include <string.h>
# include <time.h>

int f = 0, log1_y = 600, len=0, m3, mm3, stop_dec = 0, log2_y = 800, m1, m2, mm1, mm2, point = 0;
int i, ans_f =0, p, c, s, log3_y = 1000, c3=0, lev=50;
char n1[4], nn1[4], c1 = 0, c2 = 0, score[4];
char ch, in_ans[10], in_ans1[10], in_ans2[10], log1_math[4], log2_math[4],signs[4]={'+','-','x','/0'};
char colour[5][50] = {"Red","Green", "Orange", "Blue", "Purple"};
char shape[5][50] = {"Square", "Circle", "Triangle", "Diamond", "Pentagon"};


void log1_y_dec(void);
void log2_y_dec(void);
void score_in(void);
int intConvert(char in_ans[]);

void initialize(){
    f = 0;
    log1_y = 600, log2_y = 800, log3_y = 1000;
    point = 0;
    c1=0, c2=0, c3 = 0;
    stop_dec = 0;
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

/* void math_sum_exp2(void)
{
    /*generates a mathematical expression with a plus sign.
    PROBLEM: once compiles it gives the same expresion until it is compiled again*/
    //int mm1, mm2;
    //srand(time(NULL));
    /*mm1 = rand() % 10;
    nn1[0] = 48 + mm1;
    //nn1[1] = '+';
    mm2 = rand() % 10;
    nn1[2] = 48 + mm2;
    nn1[3] = '=';
    //mm3 = mm1 + mm2;
    nn1[4] = '\0';
    int sign2 = rand() % 3;
    nn1[1] = signs[sign2];

    if(sign2 == 0) mm3 = mm1 + mm2;
    else if (sign2 == 1) mm3 = mm1 - mm2;
    else mm3 = mm1 * mm2;

} */

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
        if (stop_dec==0){
            log1_y -= 3;
            log2_y -= 3;
            log3_y -= 3;
        }
        if (stop_dec==1){
            log1_y += 600;
            //if(log1_y <600) log1_y = 600;
            c1=0;
            point += 5;
            stop_dec=0;
        }

        if (log1_y <= 128 || log2_y <= 128 || log3_y <= 128){
            f = 4;///final screen flag
        }
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
        iShowBMP(0, 0, "home back.bmp");
        iSetColor(255, 0, 0);
        iRectangle(130, 300, 240, 67);///lower box
        iRectangle(130, 367, 240, 67);///middle box
        iRectangle(130, 434, 240, 67);///upper box
        iText(215, 460, "START", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(165, 390, "INSTRUCTIONS", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(220, 325, "QUIT", GLUT_BITMAP_TIMES_ROMAN_24);
    }

    if (f == 1)
    {
        ///main game page
        iSetColor(47, 141, 255);
        iFilledRectangle(100, 0, 300, 600);

        iSetColor(0, 0, 0);
        iText(290,60,"YOUR ANSWER:");
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

        iSetColor(0, 0, 0);
        iText(320,40,in_ans, GLUT_BITMAP_TIMES_ROMAN_24);

        if (intConvert(in_ans2) == m3)
            stop_dec = 1;

        //if (intConvert(in_ans2) == mm3)
        //    stop_dec = 2;
        // this portion checks keyboard input string converted to an integer and compares it to the actual answer of the expression
        //if they match stops loading the log image
        // PROBLEM: Doesn't set the log back, doesn't work for continuos logs.

        iSetColor(0, 0, 0);
        iFilledRectangle(0, 600, 500, 50);
        iSetColor(255, 255, 255);
        iText(200, 620, "SCORE: ");

        p = point;
        for(i=3;i>=0;i--){
            score[i] = p%10 + 48;
            p /= 10;
        }
        score[4]='\0';

        iSetColor(255, 255, 255);
        iText(260,620,score);

        // scores isn't complete
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

    }
    if (f == 2)
    {
        ///instruction page
        iShowBMP(0, 0, "ins.bmp");
        iSetColor(255, 255, 200);
        iText(10, 10, "GO BACK", GLUT_BITMAP_TIMES_ROMAN_24);

    }
    if (f == 3)
    {
        ///quit button
        exit(1);
    }
    if (f == 4)
    {
        ///end screen
        iText(180, 500, "GAME OVER", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(10, 10, "RETURN HOME", GLUT_BITMAP_9_BY_15);
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
        if (mx>130 && my>434 && mx <370 && my<501 && f == 0)
        {
            f = 1;
        }
        if (mx>130 && my>367 && mx <370 && my<433 && f == 0)
        {
            f = 2;
        }
        if (mx>130 && my>300 && mx <370 && my<366 && f == 0)
        {
            f = 3;
        }
        if (mx>10 && my>10 && mx <100 && my<50 && f == 2)
        {
            f = 0;
        }
        if (mx>10 && my>10 && mx < 100 && my < 50 && f == 4){
            initialize();
        }

        ///colour answer
        if(log2_y < 600 && log2_y >= 128)
        {
            ///red
            if(c==0 && mx > 400 && mx < 500 && my > 0 && my < 100)
            {
                log2_y += 600;
                c2 = 0;
                point += 5;
            }

            ///green
            if(c==1 && mx > 400 && mx < 500 && my > 100 && my < 200)
            {
                log2_y += 600;
                c2 = 0;
                point += 5;
            }

            ///orange
            if(c==2 && mx > 400 && mx < 500 && my > 200 && my < 300)
            {
                log2_y += 600;
                c2 = 0;
                point += 5;
            }

            ///blue
            if(c==3 && mx > 400 && mx < 500 && my > 300 && my < 400)
            {
                log2_y += 600;
                c2 = 0;
                point += 5;
            }

            ///purple
            if(c==4 && mx > 400 && mx < 500 && my > 400 && my < 500)
            {
                log2_y += 600;
                c2 = 0;
                point += 5;
            }

        }

        ///shape answer
        if(log3_y < 600 && log3_y >= 128)
        {
            ///square
            if(s==0 && mx > 0 && mx < 100 && my > 0 && my < 100)
            {
                log3_y += 600;
                c3 = 0;
                point += 5;
            }

            ///circle
            if(s==1 && mx > 0 && mx < 100 && my > 100 && my < 200)
            {
                log3_y += 600;
                c3 = 0;
                point += 5;
            }

            ///Triangle
            if(s==2 && mx > 0 && mx < 100 && my > 200 && my < 300)
            {
                log3_y += 600;
                c3 = 0;
                point += 5;
            }

            ///diamond
            if(s==3 && mx > 00 && mx < 100 && my > 300 && my < 400)
            {
                log3_y += 600;
                c3 = 0;
                point += 5;
            }

            ///pentagon
            if(s==4 && mx > 00 && mx < 100 && my > 400 && my < 500)
            {
                log3_y += 600;
                c3 = 0;
                point += 5;
            }

        }

    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
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
        }
        else
        {
            in_ans[len] = key;
            //puts(in_ans);
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
    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
    //place your codes for other keys here
}

void level(){
    lev -= 5;
}

int main()
{
    //place your own initialization codes here.
    iSetTimer(10,level);
    iSetTimer(lev, log1_y_dec);

    iInitialize(500, 650, "RIVER LEARNING");
    return 0;
}

