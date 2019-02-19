#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <string.h>
/*Project Midterm (MineSweeper)*/
//functions
void printGameBoard(int a[14][30]);
void bombGenerator(int a[14][30]);
void bombFinder(int Ar[14][30],int x,int y);
int isHit(int Bomb[14][30],int i,int j);
int haveFinished(int a[14][30]);
int isValid(int i,int j);
void cls();
/*-----------------------------Notes:
1-8:= Used for saving the number of Bombs nearby 
10:= Untouched Cell => #
15:= Flagged Cell   => P
16:= Flagged Bomb    P
20:= Safe Cell(No Bombs In It's Precinct) => " "
200:= Bomb => * (if revealed)
100:= Hidden Bomb 
---------------------------------------------------*/
//Main =>>**********************************************************************************
int main(void) {
	//sets the screen's Border 
	system("mode 97, 38");
	int i,j,x,y;
	char cmd[3];
	//Game's Main Array
	int Garr[14][30];
	for(i=0;i<14;i++){
		for(j=0;j<30;j++){
		Garr[i][j]=10;
	}
	}
	printGameBoard(Garr);
	bombGenerator(Garr);
	while(1){
//		printf("Cheat:\n ");
//		for(i=0;i<14;i++){
//			for(j=0;j<30;j++)
//			printf("%3d ",Garr[i][j]);
//			printf("\n ");
//		}
		fgets(cmd, sizeof(cmd)*3, stdin);
		if(strcmp(cmd,"cho\n")==0){
			scanf("%d%d",&x,&y);
			//User Can Only Choose the cells which they are Untouched and the selected coordinate should be valid as well
			if((Garr[x][y]==10||Garr[x][y]==100)&&(isValid(x,y)==1)){
				if(isHit(Garr,x,y)==1){
					for(i=0;i<14;i++){
						for(j=0;j<30;j++){
							if(Garr[i][j]==100){
								Garr[i][j]=200;
							}
						}
					}
					cls();
					printGameBoard(Garr);
					//if user loses the gameboards forecolor turns into red
					system("color 04");
					printf("You Have Lost!\n   Created By S.Shayan Daneshvar\n");
					break;
				}
				//if the selected cell is safe it calles the bombFinder Function
				else if(isHit(Garr,x,y)==0){
					bombFinder(Garr,x,y);
				}
			}	
		}
		if(strcmp(cmd,"fla\n")==0){
			scanf("%d%d",&x,&y);
			//user can only flag cells which are untouched
			if(Garr[x][y]==10&&isValid(x,y)==1){
				Garr[x][y]=15;
			}
			else if(Garr[x][y]==100){
				Garr[x][y]=16;
			}
		}
		//User can only unflag flagged cells
		if(strcmp(cmd,"ufl\n")==0){
			scanf("%d%d",&x,&y);
			if(Garr[x][y]==15&&isValid(x,y)==1){
				Garr[x][y]=10;
			}
			else if(Garr[x][y]==16){
				Garr[x][y]=100;
			}
		}
		if(strcmp(cmd,"ext\n")==0){
			return 0;
		}
		if(haveFinished(Garr)==1){
			system("color 03");
			printf("Congratulations!\n You Have Won!\n   Created By S.Shayan Daneshvar\n");
			break;
		}
		cls();
		printGameBoard(Garr);
	}
	printf("\a");
	//when game's over the program will wait for 7 seconds and then terminates the program 
	Sleep(7000);
	return 0;
}
//End Of Main *************************************************************************
//this function prints the gameboard
void printGameBoard(int a[14][30]){
	int i,j;
	printf("\n    |");
	for(i=0;i<30;i++){
		printf("%2d|",i);
	}
	printf("\n");
	printf("  ---------------------------------------------------------------------------------------------");
	printf("\n");
	printf(" ");
		for(i=0;i<14;i++){
			printf(" %2d| ",i);
			for(j=0;j<30;j++){
			if(a[i][j]==10||a[i][j]==100)
				printf("#|");
			if(a[i][j]==15||a[i][j]==16)
				printf("P|");
			else if(a[i][j]==200)
				printf("*|");	
			else if(a[i][j]==20)
				printf(" |");
			else if(a[i][j]==1){
				printf("1|");
			}
			else if(a[i][j]==2){
				printf("2|");
			}
			else if(a[i][j]==3){
				printf("3|");
			}
			else if(a[i][j]==4){
				printf("4|");
			}
			else if(a[i][j]==5){
				printf("5|");
			}
			else if(a[i][j]==6){
				printf("6|");
			}
			else if(a[i][j]==7){
				printf("7|");
			}
			else if(a[i][j]==8){
				printf("8|");
			}
			printf(" ");
		}
	printf("\n");
	printf("  ---------------------------------------------------------------------------------------------");
	printf("\n ");
	}
}
//Using Rand Function for Generating Bombs
void bombGenerator(int a[14][30]){
	int i,j,n=0;
	srand(time(NULL));
	while(n<=40){
			i=rand()%14;
			j=rand()%30;
			if(a[i][j]==100){
				n--;
			}
			a[i][j]=100;
			n++;
	}
}
// Recursive Function that find's whether there is a bomb around or not (if there is,it prints number of bombs)
void bombFinder(int Ar[14][30],int i,int j){
	int count=0;
	//North Cell
	if(isValid(i-1,j)==1){
		if(Ar[i-1][j]==100||Ar[i-1][j]==16){
			count++;
		}
	}
	//North West Cell
	if(isValid(i-1,j-1)==1){
		if(Ar[i-1][j-1]==100||Ar[i-1][j-1]==16){
			count++;
		}
	}
	//North-East Cell
	if(isValid(i-1,j+1)==1){
		if(Ar[i-1][j+1]==100||Ar[i-1][j+1]==16){
			count++;
		}
	}
	//West Cell
	if(isValid(i,j-1)==1){
		if(Ar[i][j-1]==100||Ar[i][j-1]==16){
			count++;
		}
	}
	//East Cell
	if(isValid(i,j+1)==1){
		if(Ar[i][j+1]==100||Ar[i][j+1]==16){
			count++;
		}
	}
	//South West Cell
	if(isValid(i+1,j-1)==1){
		if(Ar[i+1][j-1]==100||Ar[i+1][j-1]==16){
			count++;
		}
	}
	//South Cell
	if(isValid(i+1,j)==1){
		if(Ar[i+1][j]==100||Ar[i+1][j]==16){
			count++;
		}
	}
	//South East Cell
	if(isValid(i+1,j+1)==1){
		if(Ar[i+1][j+1]==100||Ar[i+1][j+1]==16){
			count++;
		}
	}
	if(count>0){
		Ar[i][j]=count;
		return;
	}
	else if(count==0){
		Ar[i][j]=20;	
	//North		
	if(isValid(i-1,j)==1){
		if(Ar[i-1][j]>9&& Ar[i-1][j]!=20)
			bombFinder(Ar,i-1,j);
	}
	//North West Cell
	if(isValid(i-1,j-1)==1){
		if(Ar[i-1][j-1]>9&& Ar[i-1][j-1]!=20)
			bombFinder(Ar,i-1,j-1);
	}
	//North-East Cell
	if(isValid(i-1,j+1)==1){
		if(Ar[i-1][j+1]>9&& Ar[i-1][j+1]!=20)
			bombFinder(Ar,i-1,j+1);
	}
	//West Cell
	if(isValid(i,j-1)==1){
		if(Ar[i][j-1]>9&& Ar[i][j-1]!=20)
			bombFinder(Ar,i,j-1);
	}
	//East Cell
	if(isValid(i,j+1)==1){
		if(Ar[i][j+1]>9&& Ar[i][j+1]!=20)
			bombFinder(Ar,i,j+1);
	}
	//South West Cell
	if(isValid(i+1,j-1)==1){
		if(Ar[i+1][j-1]>9&& Ar[i+1][j-1]!=20)
			bombFinder(Ar,i+1,j-1);
	}
	//South Cell
	if(isValid(i+1,j)==1){
		if(Ar[i+1][j]>9&& Ar[i+1][j]!=20)
			bombFinder(Ar,i+1,j);
	}
	//South East Cell
	if(isValid(i+1,j+1)==1){
		if(Ar[i+1][j+1]>9&& Ar[i+1][j+1]!=20)
			bombFinder(Ar,i+1,j+1);
	}
	}
}
//if hit, returns 1,0 if not
int isHit(int Bomb[14][30],int i,int j){
	if(Bomb[i][j]==100){
		return 1;
	}
	return 0;
}
//Game Ends When There is No More Safe Cells Left on the Game Board
int haveFinished(int a[14][30]){
	int i,j;
	for(i=0;i<14;i++)
		for(j=0;j<30;j++){
			if(a[i][j]==10){
				return 0;
			}
		}
	return 1;
}
void cls(){
	system("cls");
}
int isValid(int i,int j){
	if(i>=0&&i<14&&j>=0&&j<30){
		return 1;
	}
	return 0;
}
