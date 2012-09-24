#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int dx[]={1,-1,0,0};
const int dy[]={0,0,1,-1};
const int N=20;
const int M=20;
const int people=40;
const int numberOfLevelZero=40;
const int foodNumber=-1;

class fish{
private:
    static int map[N][M];
    static int HP[people];
    static int Att[people];
    int Level;
    int Speed;
    int rest;
    int maxHP;
    bool haveID;
    int ID;
    int px,py;
    bool haveMove;
    bool haveAttack;
    void fresh(){
        for(int i=1;i<=N;++i)
            for(int j=1;j<=M;++j){
                if(map[i][j]==foodNumber)
                    map[i][j]=0;
            }
        srand(unsigned(time(0)));
        for(int i=1;i<=numberOfLevelZero;++i){
            int x=rand()%N+1;
            int y=rand()%M+1;
            if(map[x][y])continue;
            map[x][y]=foodNumber;
        }
    }
public:
    bool overBoard(int your_x,int your_y){
        if(your_x<1||your_x>N)return 0;
            if(your_y<1||your_y>M)return 0;
        return 1;
    }
    void kill(int killer,int bekill){
        printf("%d killed %d\n",killer,bekill);
    }
    void Set_id(int some_id){
        if(haveID)return;
        ID=some_id;
        haveID=true;
    }
    bool moveTo(int your_x, int your_y){
        if(overBoard(your_x,your_y))return 0;
        if(map[your_x][your_y]!=0)return 0;
        
        if(haveMove)return 0;
        if(haveAttack)return 0;
        haveMove=1;
        map[px][py]=0;
        map[your_x][your_y]=ID;
        px=your_x;
        py=your_y;
    }
    bool attack(int your_x,int your_y){
        if(overBoard(your_x,your_y))return 0;
        if(abs(your_x-px)+abs(your_y-py)!=1)return 0;
        
        if(haveAttack)return 0;
        haveAttack=1;
        if(map[your_x][your_y]==foodNumber){
            if(Att[ID]<1)return 0;
            kill(ID,foodNumber);
            return 1;
        }
        else{
            int kid=map[your_x][your_y];
            HP[kid]-=Att[ID];
            if(HP[kid]<1)
                kill(ID,kid);
            return 1;
        }
    }
    int askPoint(){
        return rest;
    }
    int askX(){
        return px;
    }
    int askY(){
        return py;
    }
    int askHP(){
        return HP[ID];
    }
    int askAtt(){
        return Att[ID];
    }
    int askSp(){
        return Speed;
    }
    int askWhat(int your_x,int your_y){
        return map[your_x][your_y];
    }
    int askHP(int your_id){
        return HP[your_id];
    }
    int askMaxHP(){
        return maxHP;
    }
    bool increaseHP(){
        if(rest<1)return 0;
        HP[ID]+=1;
        maxHP+=1;
        rest-=1;
        return 1;
    }
    bool increaseAtt(){
        if(rest<1)return 0;
        Att[ID]+=1;
        rest-=1;
        return 1;
    }
    bool increaseSp(){
        if(rest<1)return 0;
        Speed+=1;
        rest-=1;
        return 1;
    }
    virtual void play(){}
};

int fish::map[N][M];
int fish::HP[people];
int fish::Att[people];
