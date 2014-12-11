/**	This a Program to make a classic snake game
*	@NODE define the snake's location
*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include <windows.h>
#include <dos.h>
void gotoxy(int x,int y)  
{  
    COORD P;  
    P.X=x;  
    P.Y=y;  
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),P);  
}  
void HideCursor()	//隐藏光标
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
typedef struct NODE{
	struct NODE *next;
	int x;
	int y;
}Node;
Node *head;
char pch,cch;
int foodx[2];
int poisonx[2];
int minex[2];
int score=0; 
int speed=400;
char pause;                                 //var define

void init()
{
	HideCursor();
	displayMessage();
	Map();
	head=(Node*)malloc(sizeof(Node));
	head->x=40;
	head->y=10;
	head->next=NULL;
	displaySnake(head); 
	insertnew(head,40,10);
	insertnew(head,41,10);
	insertnew(head,42,10);
	displaySnake(head); 
	poison(poisonx);
	displaypoison(poisonx);
	food(foodx);
	displayfood(foodx);
	mine(minex);
	displaymine(minex);
	displayscore();
	while(!_kbhit());  
    getch();  
    gotoxy(65,13);  
    //printf("空格键暂停游戏");
	pch=cch='a'; 
}                          //初始化 
void displayMessage()
{
	gotoxy(65,3);
	printf("#代表蛇头");
	gotoxy(65,4);
	printf("@代表蛇身");
	gotoxy(65,5);
	printf("&代表食物");
	gotoxy(65,6);
	printf("！代表毒草"); 
	gotoxy(65,8);
	printf("w代表上");
	gotoxy(65,9);
	printf("s代表下");
	gotoxy(65,10);
	printf("a代表左");
	gotoxy(65,11);
	printf("d代表右");
	gotoxy(63,15);
	printf("按任意键开始游戏"); 
}                   //信息初始化 
void displayscore()
{
	gotoxy(65,12);
	printf("总得分为%d",score);
}                    //Score List
void displaySnake(Node *head)
{
	Node* first=head;
	while(first!=NULL)
	{
		gotoxy(first->x,first->y);
		if(first==head)
			printf("#");
		else
			printf("*");
		first=first->next;	
	}
}                    //Print Snake
void mine(int minex[2])  
{  
    srand((unsigned)time(NULL));  
    minex[0]=rand()%48+7;  
    minex[1]=rand()%24+5;  
}         //Make Food randomly
void displaymine(int minex[2])  
{  
    gotoxy(minex[0],minex[1]);  
    printf("@");  
}      //Print Food
void food(int foodx[2])  
{  
    srand((unsigned)time(NULL));  
    foodx[0]=rand()%48+11;  
    foodx[1]=rand()%24+1;  
}         //Make Food randomly

void displayfood(int foodx[2])  
{  
    gotoxy(foodx[0],foodx[1]);  
    printf("&");  
}      //Print Food
void poison(int poisonx[2])
{
	srand((unsigned)time(NULL));
	poisonx[0]=rand()%24+11;
	poisonx[1]=rand()%12+1;
}                      //Make Poison
void displaypoison(int poisonx[2])
{
	gotoxy(poisonx[0],poisonx[1]);
	printf("!");
}               //Print Poison
void insertnew(Node *head,int x,int y)
{
	Node *newlnk;
	Node *first=head;
	newlnk=(Node*)malloc(sizeof(Node));
	newlnk->x=x;
	newlnk->y=y;
	while(first->next!=NULL)
	{
		first=first->next;
	}
	first->next=newlnk;
	newlnk->next=NULL;
}     //Create one list
void eatfood(Node *head)
{
	Node *newlink,*current;
	if((head->x==foodx[0])&&(head->y==foodx[1]))
	{
		newlink=(Node*)malloc(sizeof(Node));
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
		if((speed>=50)&&(score<=30)&&(score%6==5))  
            speed-=50;  
        else if((score<=50)&&(speed>=50))  
            speed-=10;  
        else if((speed<=50)&&(speed>=10))  
            speed-=10;  
        food(foodx);
		displayfood(foodx);
		
	}
	
}                            //isEatFood 
void eatpoison(Node *head)
{
	Node *current=head;
	
	if((head->x==poisonx[0])&&(head->y==poisonx[1]))
	{
		
		while(current->next->next!=NULL)
		{
			
			current=current->next;
		}
	
		current->next=NULL;
		poison(poisonx);
		displaypoison(poisonx);
		score--;
	}
	
}                        //isEatFood
void eatMine(Node *head){
	Node *current;
	int tailX,tailY; 
	if((head->x==minex[0])&&(head->y==minex[1]))
	{
		while(current->next!=NULL)
		{
			current=current->next;
		}
		tailX=current->x;
		tailY=current->y;
		current=head;
		
		while(current->next!=NULL){
			if(pch=='a'||pch=='d'){
				if(current->x==(head->x+tailX)/2||current->next->next==NULL)
						
						break;
			}
			if(pch=='w'||pch=='s'){
				if(current->y==(head->y+tailY)/2||current->next->next==NULL)
						
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
void Map()				//Print Map
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
int test(Node *head)
{
	Node *first=head->next;
	while(first!=NULL)
	{
		if((first->x==head->x)&&(first->y==head->y))
		{
			return 0;
		}
		first=first->next;
	}
	return 1;
}        //Test 
char button()  
{  
    char ch=0;  
    if(_kbhit())  
    {  
        while(_kbhit())  
            ch=getch();  
    }  
    return isalpha(ch)?tolower(ch):ch;  
}  										//cin 
void myclear(Node *head)  
{  
    while(head!=NULL)  
    {  
        gotoxy(head->x,head->y);  
        printf(" ");  
        head=head->next;  
        
    }  
}        //del
void move(Node*head)
{
	int x1,x2,y1,y2,flag=0;
	x1=head->x;
	y1=head->y;
	switch(cch)
	{
		case 'w':
		 		if(pch=='a'||pch=='d')
				 {
				 	head->y--;
				 	flag=1;
				 	pch=cch;
				}
				break;	
		case 'a':
				if(pch=='w'||pch=='s')
				{
					head->x--;
					flag=1;
					pch=cch;
				}
				break;
		case 's':
				if(pch=='a'||pch=='d')
				{
					head->y++;
					flag=1;
					pch=cch;
				}
				break;
		case 'd':
				if(pch=='w'||pch=='s')
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
		if(pch=='a')
			head->x--;
		else if(pch=='w')
			head->y--;
		else if(pch=='s')
			head->y++;
		else if(pch=='d')
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
void game()
{
	while((head->x>10)&&(head->x<60)&&(head->y>0)&&(head->y<25))  
    {  
      	if(score<0)
		break;  
        displaySnake(head);  
        Sleep(speed);
        myclear(head); 
		cch=button(); 
		pause=(cch==' ')?!pause:pause;
        if(!pause)  
        {  
            gotoxy(62,13);  
            printf("空格键暂停游戏");  
            move(head);
		
        }  
        else  
        {  
            gotoxy(62,13);  
            printf("空格键继续游戏");  
        }  
      	
      	displayscore();
      	if(!test(head)||head->next==NULL)
      		break;
      	
    }
	if(head->next==NULL){
		gotoxy(20,12);
		printf("你见过只有蛇头的蛇吗！？U deserve it!");
	}else
		Over();
}						
void Over(){
	gotoxy(30,12); 
	printf("GAME OVER!!!");  
}
void record(){
	
}
int main()
{
	init();
	game();
	record();
	return 0;
}

