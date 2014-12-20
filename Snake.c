/**	This a Program to make a classic snake game
*	2014.12.20 @author aLIEzTED
*   @SNAKE define the snake's location
*   @USER define the user's name AND score
*   Have Fun!
*/


#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include<string.h> 
#include <windows.h>
#include <dos.h>
#define ENTER 13
#define ESC   27
#define RIGHT 77
#define LEFT 75
#define UP 72
#define DOWN 80
typedef struct SNAKE{
	struct SNAKE *next;
	int x;
	int y;
}Snake;
typedef struct USER{
	char username[20];
	int userscore;
}User;

Snake *head;
User *user;
int pch,cch;
int foodx[2];
int poisonx[2];
int minex[2];
int score; 
int userCount=0;
int speed;
int sLv;
char pause;
char usrname[20];                                    //var define

void displayMessage();
void displayscore();
void displaySnake(Snake *head);
void mine(int minex[2]);
void displaymine(int foodx[2]);
void food(int foodx[2]);
void displayfood(int foodx[2]);
void poison(int poisonx[2],int score);
void displaypoison(int poisonx[2]);
void insertnew(Snake *head,int x,int y);
void Map();
void Over();
void record();
void setlog();
void restart();
void sort();
void game();
char* getTime();

/*
*getCurrentTime
*/
char* getTime(){
	time_t t;
	t=time(NULL);
	char *time;
	time=ctime(&t);
	return time;
}
void gotoxy(int x,int y)  
{  
    COORD P;  
    P.X=x;  
    P.Y=y;  
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),P);  
}  
void HideCursor()	
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
/*
*   Print the Map
*/
void Map()				
{
	unsigned i,j;
	gotoxy(10,0);
	for(j=0;j<50;j++)
		printf("*");
	for(i=1;i<25;i++)
	{
		gotoxy(10,i);
		for(j=0;j<50;j++)
		{
			if(j==0||j==49)
				printf("*");
			else
				printf(" ");
		}
	}
	gotoxy(10,i);
	for(j=0;j<50;j++)
		printf("*");
}

void init()
{
	score=0;
	HideCursor();
	printf("选择难度:\n1代表简单\n2代表中等\n3代表难\n其他键退出");
	int lv; 
	scanf("%d",&lv);
	if(lv==1){
		speed=400;
	}else if(lv==2){
		speed=300;
	}else if(lv==3){
		speed=250;
	}else{
		exit(0);
	}
	system("cls"); 
	displayMessage();
	Map();
	head=(Snake*)malloc(sizeof(Snake));
	head->x=40;
	head->y=10;
	head->next=NULL;
	displaySnake(head); 
	insertnew(head,40,10);
	insertnew(head,41,10);
	insertnew(head,42,10);
	displaySnake(head);
	poison(poisonx,score);
	food(foodx);
	displayfood(foodx);
	mine(minex);
	displaymine(minex);
	displayscore();	    
    gotoxy(65,13);  
	pch=cch=LEFT; 
}                          
void displayMessage()
{
	gotoxy(65,3);
	printf("#代表蛇头");
	gotoxy(65,4);
	printf("*代表蛇身");
	gotoxy(65,5);
	printf("&代表食物");
	gotoxy(65,6);
	printf("！代表毒草"); 
	gotoxy(65,7);
	printf("@代表地雷"); 
	gotoxy(65,8);
	printf("方向键上代表上");
	gotoxy(65,9);
	printf("方向键下代表下");
	gotoxy(65,10);
	printf("方向键左代表左");
	gotoxy(65,11);
	printf("方向键右代表右");
	gotoxy(63,15);
	printf("Have Fun!"); 
}                   
void displayscore()
{
	gotoxy(65,12);
	printf("总得分为%d",score);
	gotoxy(65,14);
	if(score==1){
		printf("FIRST BLOOD   ");
	}else if(score==3){
		printf("KILLING SPREE ");
	}else if(score==4){
		printf("DOMINATING    ");
	}else if(score==5){
		printf("MEGA-KILL     ");
	}else if(score==6){
		printf("UNSTOPPABLE   ");
	}else if(score==7){
		printf("WICKED SICK   ");
	}else if(score==8){
		printf("MONSTER KILL  ");
	}else if(score==9){
		printf("GODLIKE       ");
	}else if(score>=10){
		printf("BEYOND GODLIKE");
	}
}                   
/*
*Print the Snake
*/
void displaySnake(Snake *head)
{
	Snake* first=head;
	while(first!=NULL)
	{
		gotoxy(first->x,first->y);
		if(first==head)
			printf("#");
		else
			printf("*");
		first=first->next;	
	}
}                   
/*
*Make the Mine,Food,poison randomly AND display them.
*/
void mine(int minex[2])  
{  
    srand((unsigned)time(NULL));  
    minex[0]=rand()%48+7;  
    minex[1]=rand()%24+5;
	while(!((minex[0]>10)&&(minex[0]<60)&&(minex[1]>0)&&(minex[1]<25))){
		minex[0]=rand()%24+11;
		minex[1]=rand()%12+1;
	}  
}         //Make Mine randomly
void displaymine(int minex[2])  
{  
    gotoxy(minex[0],minex[1]);  
    printf("@");  
}      //Print Mine
void food(int foodx[2])  
{  
    srand((unsigned)time(NULL));  
    foodx[0]=rand()%48+11;  
    foodx[1]=rand()%24+1;
	while(!((foodx[0]>10)&&(foodx[0]<60)&&(foodx[1]>0)&&(foodx[1]<25))){
		foodx[0]=rand()%24+11;
		foodx[1]=rand()%12+1;
	}  
}         //Make Food randomly

void displayfood(int foodx[2])  
{  
    gotoxy(foodx[0],foodx[1]);  
    printf("&");  
}      //Print Food
void poison(int poisonx[2],int score)
{
	if(score>5&&score<10){
		int i=0;
		srand((unsigned)time(NULL));
		poisonx[0]=rand()%24+11;
		poisonx[1]=rand()%12+1;
		while(!((poisonx[0]>10)&&(poisonx[0]<60)&&(poisonx[1]>0)&&(poisonx[1]<25))){
			poisonx[0]=rand()%24+11;
			poisonx[1]=rand()%12+1;
		}
		displaypoison(poisonx);
	}
	
}                      //Make Poison
void displaypoison(int poisonx[2])
{
	gotoxy(poisonx[0],poisonx[1]);
	printf("!");
}               //Print Poison


void myclear(Snake *head)  
{  
    while(head!=NULL)  
    {  
        gotoxy(head->x,head->y);  
        printf(" ");  
        head=head->next;  
        
    }  
}        
void insertnew(Snake *head,int x,int y)
{
	Snake *newlnk;
	Snake *first=head;
	newlnk=(Snake*)malloc(sizeof(Snake));
	newlnk->x=x;
	newlnk->y=y;
	while(first->next!=NULL)
	{
		first=first->next;
	}
	first->next=newlnk;
	newlnk->next=NULL;
}     //New Snake
/*
*	EventListener
*/
void eatfood(Snake *head)
{
	Snake *newlink,*current;
	if((head->x==foodx[0])&&(head->y==foodx[1]))
	{
		newlink=(Snake*)malloc(sizeof(Snake));
		while(head->next!=NULL)
		{
			current=head;
			head=head->next;
		}
		head->next=newlink;
		newlink->x=current->x;
		newlink->y=current->y;
		newlink->next=NULL;
		score++;
		if(score>5){
			sLv++;
			speed-=25;
		}else if(score>10){
			sLv++;
			speed-=50;
		}
        food(foodx);
		displayfood(foodx);
		poison(poisonx,score);
	}
	
}                             
void eatpoison(Snake *head)
{
	Snake *current=head;
	
	if((head->x==poisonx[0])&&(head->y==poisonx[1]))
	{
		
		while(current->next->next!=NULL)
		{
			
			current=current->next;
		}
	
		current->next=NULL;
		poison(poisonx,score);
		score--;
	}
	
}                        
void eatMine(Snake *head){
	Snake *current;
	int count=0; 
	int i=0;
	if((head->x==minex[0])&&(head->y==minex[1]))
	{
		while(current->next!=NULL)
		{
			count++;
			current=current->next;
		}
		current=head;
		
		while(current->next!=NULL){
			i++;
			if(i==(count+1)/2){
				break;
			}
			current=current->next;
		}
		current->next=NULL;
		score=score/2;
		current=head;
        mine(minex);
		displaymine(minex);
		
	}
}                       
/*
* Check whether head meets tail
*/
int test(Snake *head)
{
	Snake *first=head->next;
	while(first!=NULL)
	{
		if((first->x==head->x)&&(first->y==head->y))
		{
			return 0;
		}
		first=first->next;
	}
	return 1;
}        
/*
*  KeyBoardListener
*/
int button()  
{  
    int ch;  
    if(_kbhit())  
    {  
    	ch=_getch();
    	if(ch==244){
    		  ch=_getch();  
    	}
    }  
    return ch; 
}
  									

void move(Snake*head)
{
	int x1,x2,y1,y2,flag=0;
	x1=head->x;
	y1=head->y;

	switch(cch)
	{
		case UP:
		 		if(pch==LEFT||pch==RIGHT)
				 {
				 	head->y--;
				 	flag=1;
				 	pch=cch;
				}
				break;	
		case LEFT:
				if(pch==UP||pch==DOWN)
				{
					head->x--;
					flag=1;
					pch=cch;
				}
				break;
		case DOWN:
				if(pch==LEFT||pch==RIGHT)
				{
					head->y++;
					flag=1;
					pch=cch;
				}
				break;
		case RIGHT:
				if(pch==UP||pch==DOWN)
				{
					head->x++;
					flag=1;
					pch=cch;
				}
				break;
		default:
				break;
	}                      //Turn 
	if(flag!=1)
	{
		if(pch==LEFT)
			head->x--;
		else if(pch==UP)
			head->y--;
		else if(pch==DOWN)
			head->y++;
		else if(pch==RIGHT)
			head->x++;		
	}                 
	eatfood(head);
	eatpoison(head);
	eatMine(head); 
	head=head->next;
	while(head!=NULL)
	{
		x2=head->x;
		y2=head->y;
		head->x=x1;
		head->y=y1;
		x1=x2;
		y1=y2;
		head=head->next;
	}					//KeepMoving 
}

void restart(){
	gotoxy(22,12);
	printf("Do You Want to Play Again?  Y/N");
	char c;
	c=getch();
	if(c=='y'){
		gotoxy(0,0);
		system("cls");
		init();
		game();
	}else if(c=='n'){
		exit(0);
	}
}		

void game()
{
	int flag=0;
	while((head->x>10)&&(head->x<59)&&(head->y>0)&&(head->y<25))  
    {  
      	if(score<0)
			break;
		if(score>15){
			break;
		}  
        displaySnake(head);  
        Sleep(speed);
        myclear(head); 
		cch=button();
		if(cch==ESC){
			exit(0);
		} 
		pause=(cch==ENTER)?!pause:pause;
        if(!pause)  
        {  
            gotoxy(62,13);  
            printf("回车键暂停游戏");  
            move(head);
		}  
        else  
        {   
			if(flag==0){
				flag=1;
				setlog();
			}
			gotoxy(62,13);  
            printf("回车键继续游戏");  
        }  
      	
      	displayscore();
      	if(!test(head)||head->next==NULL)
      		break;
      	
    }
    	if(score>15){
    		gotoxy(30,12);
    		printf("YOU WIN");
    		record();
    	}
    	Over();
		record();
		
		if(cch==ESC){
			exit(0);
		} 
}				

void Over(){
	gotoxy(30,12); 
	printf("GAME OVER!!!");  
}
void record(){
	static int flag=0; 
	char cScore[20];
	itoa(score,cScore,10);
	FILE *fp;
	
	if(!flag){
		user=(User*)malloc(sizeof(User));	
		flag=1;
	}
	if(flag==1){
		user=(User*)realloc(user,sizeof(User));
	}
	
	if(score<0){
		score=0;
	}
	
	gotoxy(30,13);
	printf("输入姓名");
	scanf("%s",usrname);
	fp=fopen("record.txt","a");
	fputs(usrname,fp);
	fputs(" Score",fp);
	fputs(cScore,fp);
	fprintf(fp,"\n",fp);
	fclose(fp);
	system("cls");
	strcpy(user[userCount].username,usrname);
	user[userCount].userscore=score;
	userCount++;
	sort(user,userCount);
	restart();
}
void sort(User *user,int userCount){
	gotoxy(25,13);
	printf("----------英雄榜----------");
	gotoxy(25,14);
	printf("Player");
	gotoxy(46,14);
	printf("Score");
	int i,j,k,t;
	char str[30];
	for(i=0;i<userCount+1;i++)
	{
		k=i;
		for(j=i+1;j<userCount;j++)
			if(user[j].userscore<user[k].userscore)
				k=j;
				t=user[k].userscore;
				strcpy(str,user[k].username);
				user[k].userscore=user[i].userscore;
				strcpy(user[k].username,user[i].username);
				user[i].userscore=t;
				strcpy(user[i].username,str);
				
	}
	for(i=0;i<userCount;i++){
		gotoxy(25,15+i);
		printf("%s",user[i].username);
		gotoxy(46,15+i);
		printf("%d",user[i].userscore);	
	}
}
void setlog(){
	char cScore[20];
	char cLv[20];
	itoa(sLv,cLv,10);
	itoa(score,cScore,10);
	FILE *log;
	log=fopen("log.txt","a");
	fprintf(log,"%s\n",getTime());
	fputs("Current Score",log);
	fputs(cScore,log);
	fputs("Current Level",log);
	fputs(cLv,log);
	fclose(log);
}
int main()
{
		init();
		game();
		return 0;
}

