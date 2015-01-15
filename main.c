#include <stdio.h>
#include <stdlib.h>
void printBoard(char **board, int n);
int NextStep(char **board, char **board1, int n, int i, int j, int c, int *a, char player)
{
 int row, col, k, l;
 while(c < ((n*n)))
 {
  row=c/n;
  col=c%n;
  if(board1[row][col]=='.')
  {
   board1[row][col]=player;
   if(a[4] < (a[5] - findLongest(board1, n, row, col)))
   {
	a[0]=i;
	a[1]=j;
	a[2]=row;
	a[3]=col;
	a[4]= a[5] - findLongest(board1, n, row, col);
   }
board1[row][col] = board[row][col];
  }
  NextStep(board, board1, n, i, j,  c+1, a, player);
  break;
 }
}
int winner(char **board, int n)
{
   int i, j, winner1;
   char winner;
   for(i=0; i<n; i++)
   {
   	for(j=0; j<n; j++)
   	{
       	if(findLongest(board, n, i, j)>=6 && board[i][j]!='.')
       	{
           	winner=board[i][j];
       	}
   	}
   }
   if(winner=='B')
   	winner1=0;
   else if(winner=='W')
   	winner1=1;
   else
   	winner1=2;

    return winner1;
}
int longestHorizontal(char **board, int n, int row, int col)
{
   int i, counter;
   counter=0;
   for(i=col; i<n; i++)
   {
   	if(board[row][i]==board[row][col])
       	counter++;
   	else
       	i=n+1;
   }
   for(i=col; i>=0; i--)
   {
   	if(board[row][i]==board[row][col])
       	counter++;
   	else
       	i=-1;
   }
   counter--;
   return counter;
}
int longestVertical(char **board, int n, int row, int col)
{
   int i, counter;
   counter=0;
   for(i=row; i<n; i++)
   {
   	if(board[i][col]==board[row][col])
       	counter++;
   	else
       	i=n+1;
   }
   for(i=row; i>=0; i--)
   {
   	if(board[i][col]==board[row][col])
       	counter++;
   	else
       	i=-1;
   }
   counter--;
   return counter;
}
int longestDiagonal1(char **board, int n, int row, int col)
{
   int i, j, counter;
   counter=0;
   for(i=col, j=row; i<n, j<n; i++, j++)
   {
   	if(board[j][i]==board[row][col])
       	counter++;
   	else
   	{
       	i=n+1;
       	j=n+1;
   	}
   }
   for(i=col, j=row; i>=0, j>=0; i--, j--)
   {
   	if(board[j][i]==board[row][col])
       	counter++;
   	else
   	{
       	i=-1;
       	j=-1;
   	}
   }
   counter--;
   return counter;
}
int longestDiagonal2(char **board, int n, int row, int col)
{
   int i, j, counter;
   counter=0;
   for(i=col, j=row; i<n, j>=0; i++, j--)
   {
   	if(board[j][i]==board[row][col])
       	counter++;
   	else
   	{
       	i=n+1;
       	j=-1;
   	}
   }
   for(i=col, j=row; i>=0, j<n; i--, j++)
   {
   	if(board[j][i]==board[row][col])
       	counter++;
   	else
   	{
       	i=-1;
       	j=n+1;
   	}
   }
   counter--;
   return counter;
}
int findLongest(char **board, int n, int row, int col)
{
   int c_h, c_v, c_d, longest, c_d1, c_d2;
   c_h=longestHorizontal(board, n, row, col);
   c_v=longestVertical(board, n, row, col);
   c_d1=longestDiagonal1(board, n, row, col);
   c_d2=longestDiagonal2(board, n, row, col);
   if(c_d1>c_d2)
   	c_d=c_d1;
   else
   	c_d=c_d2;
   longest=c_h;
   if(c_v>longest)
 	longest=c_v;
   if(c_d>longest)
 	longest=c_d;
   return longest;
}
void printBoard(char **board, int n)
{
   int i, j;
   for(i=0; i<n; i++)
   {
   	for(j=0; j<n; j++)
   	{
       	printf("%c", board[i][j]);
   	}
   	printf("\n");
   }
}
int main(void)
{
   int n, i, j, c, row, col, loop, k, l, turns;
   turns=0;
   int a[6];
   char computer, player;
   loop=1;
   printf("Enter board dimensions (n): ");
   scanf("%d", &n);
   char **board=(char**)malloc(n*sizeof(char*));
   for(i=0; i<n; i++)
   	board[i]=(char*)malloc(n*sizeof(char));
   for(i=0; i<n; i++)
   	for(j=0; j<n; j++)
       	board[i][j]='.';
   printBoard(board, n);
   printf("Computer playing B or W?: ");
   scanf(" %c", &computer);
   if(computer=='B')
   {
   	c=0;
   	player='W';
   }
   else
   {
   	c=1;
   	player='B';
   }
   while(loop==1 && turns < n*n-4)
   {
   	if(winner(board, n)==0)
   	{
    	printf("Black player wins.\n");
    	loop=2;
    continue;
   	}
   	else if(winner(board, n)==1)
   	{
    	printf("White player wins.\n");
    	loop=2;
    continue;
   	}

   	if((c%2)==1)
   	{
       	printf("Lay down a stone (ROW COL): ");
       	scanf("%d %d", &row, &col);
       	if(board[row][col]=='.')
       	{
           	board[row][col]=player;
           	c++;
           	printBoard(board, n);
           	turns++;
       	}
       	else
       	{
           	printf("That square is occupied.\n");
       	}
   	}
   	else
   	{
        	int longest_current, best_move_current_row, best_move_current_col, longest_next, best_move_next_row, best_move_next_col, loop1;
        	char **board1=(char**)malloc(n*sizeof(char*));
        	for(i=0; i<n; i++)
         	board1[i]=(char*)malloc(n*sizeof(char));
        	for(i=0; i<n; i++)
         	for(j=0; j<n; j++)
          	board1[i][j]=board[i][j];
        	a[4]=-100;
    	for(i=0; i<n; i++)
        	{
         	for(j=0; j<n; j++)
         	{
          	if(board[i][j]=='.')
          	{
           	for(k=0; k<n; k++)
            	for(l=0; l<n; l++)
             	board1[k][l]=board[k][l];
           	board1[i][j]=computer;
           	a[5]=findLongest(board1, n, i, j);
           	NextStep(board, board1, n, i, j,  0, a, player);
          	}
         	}
        	}
        	int comp_row, comp_col;
        	comp_row=a[0];
        	comp_col=a[1];
        	board[comp_row][comp_col]=computer;
        	printf("Computer lays a stone at ROW %d COL %d.\n", a[0], a[1]);
        	printBoard(board, n);
        	c++;
        	turns++;
   	}
   }
}
