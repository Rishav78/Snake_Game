#include <iostream>
#include <conio.h>
#include<ctime>
#include<map>
#include<algorithm>
#include<vector>
#include <windows.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

using namespace std;
enum direction{STOP=0,LEFT,RIGHT,DOWN,UP,OVER};
class Moving
{
    char **border;
    int Food;
    char c;
    vector<int> coX,coY;
    int foodx,foody,f;
    int m,n,intp,finalp;
    direction dir,prv;
public:
    int score;
    Moving()
    {
        score=0;
        f=0;
        c=0;
        Food=0;
        dir = STOP;
        prv = DOWN;
        cout << endl << "ENTER BORDER WIDTH AND HEIGHT :" << endl;
        cin >> m >> n;
        foodx=m/2;
        foody=n/2;
        intp = 1;finalp = 1;
        border = new char*[m];
        for(int i=0;i<m;i++)
        {
            border[i] = new char[n];
        }
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==0 || j==0 || i==(m-1) || j==(n-1))
                {
                    border[i][j]='#';
                }
                else
                {
                    border[i][j]=' ';
                }
            }
        }
        border[foodx][foody]='A';
        cout << "USE: " << endl << "W FOR UP" << endl << "S FOR DOWN" << endl << "A FOR LEFT" << endl << "D FOR RIGHT" << "P FOR PAUSE" << endl << "R FOR RESUME" <<endl;
    }
    void Draw_food()
    {
        border[foodx][foody]= 65 + (++Food)%26;
    }
    void Generate_food()
    {
        if((intp==foodx && finalp==foody) || (border[foodx][foody]<65 || border[foodx][foody]>90))
        {
            time_t now = time(0);
            tm *ltm = localtime(&now);
            foodx=((ltm->tm_sec)*rand())%(m-1);
            foody=((ltm->tm_sec)*rand())%(n-1);
            if(foodx==0)
            {
                foodx=1;
            }
            if(foody==0)
            {
                foody=1;
            }
            for(int i=0;i<coX.size();i++)
            {
                if(foodx==coX[i] && foody==coY[i])
                {
                    Generate_food();
                    return;
                }
            }
            Draw_food();
            coX.insert(coX.begin(),intp);
            coY.insert(coY.begin(),finalp);
            score = score + 10;
        }
    }
    void Create_object()
    {
        border[1][1] = 'R';
    }
    void Start()
    {
        if(kbhit())
        {
            switch(getch())
            {
                case 'a':
                case KEY_LEFT:
                {
                    if(dir!=RIGHT)
                    {
                        dir = LEFT;
                    }
                    break;
                }
                case 'd':
                case KEY_RIGHT:
                {
                    if(dir!=LEFT)
                    {
                        dir = RIGHT;
                    }
                    break;
                }
                case 'w':
                case KEY_UP:
                {
                    if(dir!=DOWN)
                    {
                        dir = UP;
                    }
                    break;
                }
                case 's':
                case KEY_DOWN:
                {
                    if(dir!=UP)
                    {
                        dir = DOWN;
                    }
                    break;
                }
                case 'p':
                {
                    prv = dir;
                    dir = STOP;
                    break;
                }
                case 'x':
                {
                    dir = OVER;
                    break;
                }
            }
        }
        border[intp][finalp]=' ';
        if(coX.size()!=0)
        {
            int w,q;
            w = coX[0];
            q = coY[0];
            coX[0]=intp;
            coY[0]=finalp;
            border[intp][finalp]='o';
            for(int i=1;i<coX.size();i++)
            {
                int p = coX[i];
                int r = coY[i];
                coX[i]=w;
                coY[i]=q;
                border[w][q]='o';
                w=p;
                q=r;
            }
            border[w][q]=' ';
        }
            if(dir==LEFT && c!='r')
            {
                if(--finalp<1)
                {
                    finalp=n-2;
                }
                border[intp][finalp]='<';
            }
            else if(dir==RIGHT && c!='r')
            {
                if(++finalp>(n-2))
                {
                    finalp=1;
                }
                border[intp][finalp]='>';
            }
            else if(dir==UP && c!='r')
            {
                if(--intp<1)
                {
                    intp = m-2;
                }
                border[intp][finalp]='^';
            }
            else if(dir==DOWN && c!='r')
            {
                if(++intp>(m-2))
                {
                    intp = 1;
                }
                border[intp][finalp]='v';
            }
            else if(dir == STOP)
            {
                c = 'a';
                cout << "RIGHT NOW SCORE IS: " << score << endl;
                cout << "GAME PAUSE" << endl << "PRESS R KEY TO RESUME";
                while(c!='r')
                {
                    c = getch();
                }
                dir = prv;
                c='a';
            }
            else if(dir==OVER)
            {
                cout << "FINAL SCORE: " << score << endl;
                throw 1;
            }
            if(c!='a')
            {
                for(int i=0;i<coX.size();i++)
                {
                    if(coX[i]==intp && coY[i]==finalp)
                    {
                        cout << "FINAL SCORE: " << score << endl;
                        throw 1;
                    }
                }
            }
            else
            {
                c = 'q';
            }
        system("cls");
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout << border[i][j];
            }
            cout << endl;
        }
    }
    ~Moving()
    {
        delete border;
    }
};

int main()
{
    int usr,pswd;
    cout << "ENTER USERNAME: ";
    cin >> usr;
    cout << "\nENTER PASSWORD: ";
    cin >> pswd;
    if(usr==1710991661 && pswd==1710991661)
    {
        enum Difficulti_level{EASY=80,MEDIUM=40,HARD=10};
        int n,l=0;
        Difficulti_level ob;
        cout << "CHOOSE THE DIFICULTY LEVEL:" << endl;
        cout << "1. EASY" <<endl;
        cout << "2. MEDIUM" <<endl;
        cout << "3. HARD" <<endl;
        cin >> n;
        if(n==1)
        {
            ob = EASY;
            n = EASY;
        }
        else if(n==2)
        {
            ob = MEDIUM;
            n = MEDIUM;
        }
        else if(n==3)
        {
            ob = HARD;
            n = HARD;
        }
        Moving obj;
        obj.Create_object();
        while(true)
        {
            if(obj.score==(l+50))
            {
                l=obj.score;
                if(ob==MEDIUM && n>3)
                {
                    n = n - 2;
                }
                else if(ob==EASY && n>6)
                {
                    n = n - 5;
                }
            }
            obj.Generate_food();
            try
            {
                obj.Start();
            }
            catch(int x)
            {
                cout << "GAME OVER";
                break;
            }
            Sleep(n);
        }
    }
    else
    {
        cout << "WRONG USERNAME AND PASSWORD";
    }
    return 0;
}
