//---------Benjamin Parry------Section 7---------//


   #include "grid.h"
   #include <iostream>
   #include <cstdlib>   

   using namespace std;


   // build 1 x 1 grid with mover in only square, facing east
   Grid::Grid()
   {
      path=0;
      row=1;
      col=1;
      grid[0][0]='>';  
   }			

   //build grid with r rows, c cols, a baorder of blocks, the pointer in a random direction and position, and one randomly placed exit on the boarder			
   Grid::Grid(int r, int c)		
   {
      path=0;				//sets path to zero, used for TogglePath() 

      if(r<3)				//simple bound checking
         row=3;
      else if(r>40)
         row=40;
      else
         row=r;

      if(c<3)
         col=3;
      else if(c>40)
         col=40;
      else
         col=c;      

  
      for(int i=0; i<row; i++)
      {
         for(int j=0; j<col; j++)
         {  
            if(i==0 || i==row-1 || j==0 || j==col-1)			//sets '#' for row 0, row-1, col 0, col-1, then '.' for every other position
            {   
               grid[i][j]='#';
            }
            else
	       grid[i][j]= '.';
         }
      }
      srand(time(0));							//seeds rand with the current time

      int rnum=rand() % 3+1;						//random number is chosen between 0 and 3: 0=row 0, 1=col-1, 2=row-1, 3=col 0. This chooses a random edge for the escape
      int rcol,rrow;
      if(rnum==0)							//same method is chosen for a random position on the boarder, except % to one less than the bound and a do-while loop excludes 0 to prevent the escpae being on a corner 
      {
         do
         {
            rcol=rand() % (col-1);
         }while(rcol==0);
         grid[0][rcol]='.';
      }
      else if(rnum==1)
      {
         do
         {
            rrow=rand() % (row-1);
         }while(rrow==0);
         grid[rrow][col-1]='.';
      }
      else if(rnum==2)
      {
         do
         {
            rcol=rand() % (col-1);
         }while(rcol==0);
         grid[row-1][rcol]='.';
      }
      else if(rnum==3)
      {
         do
         {
            rrow=rand() % (row-1);
         }while(rrow==0);

         grid[rrow][0]='.';
      }

      do								//same as escape position, a random position is chosen for the mover inside the boarders
      {
         mov_row= rand() % (row-1);
      }while(mov_row==0);

      do
      {
         mov_col= rand() % (col-1);
      }while(mov_col==0);

      dir=rand() % 3;
      if(dir==NORTH)
         grid[mov_row][mov_col]='^';                    		//sets mover to point towards corresponding direction
      else if(dir==EAST)
         grid[mov_row][mov_col]='>';
      else if(dir==SOUTH)
         grid[mov_row][mov_col]='v';
      else if(dir==WEST)
         grid[mov_row][mov_col]='<';
     

   }				

   Grid::Grid(int r, int c, int mr, int mc, int d)
   {	
      path=0;		// bound checking
      if(r>2 && r<41)
         row=r;
      else if(r<3)
         row=3;
      else if(r>40)
         row=40;
      if(c>2 && c<41)
         col=c;
      else if(c<3)
         col=3;
      else if(c>40)
         col=40;

      for(int i=0; i<row; i++)  					//sets whole grid to '.'
      {
         for(int j=0; j<col; j++)
            grid[i][j]='.';
      }
       
      if(mr>=0 && mr<row)
         mov_row=mr;
      else if(mr<0)         						//error checking for mover position
         mov_row=0;
      else if(mr>=row)
         mov_row=row-1;

      if(mc>=0 && mc<col)
         mov_col=mc;
      else if(mc<0)
         mov_col=0;
      else if(mc>=col)
         mov_col=col-1;

      if(d>=0 && d<4)
         dir=d;
      else
         dir=0;
      if(dir==NORTH)
         grid[mov_row][mov_col]='^';                    		//error checking for mover direction then sets position and direction
      else if(dir==EAST)                   
         grid[mov_row][mov_col]='>';
      else if(dir==SOUTH)
         grid[mov_row][mov_col]='v'; 
      else if(dir==WEST)
         grid[mov_row][mov_col]='<';

   }
   
   bool Grid::Move(int s)						//move forward s spaces if possible
   {
   bool condition=true;							//condition to see if there are no blocks and move stays in the grid
   if(s>0)
      space=s;
   if (dir==NORTH)
   {  
      if(mov_row-space<0)                                      		//similar process for each direction, just some check current col or row and some move forward and some back
         condition=false; 						//if statement checks to see if the move puts the mover out of bounds and if so, condition is set to false
      for(int i=mov_row; i>=mov_row-space; i--)				//for loop checks to see if any spaces in the respective forward direction are '#'
      { 								//probably could make this more efficient by not running for loop if initial is false instead of running both 
          if(grid[i][mov_col]=='#')
             condition=false;
      }
   }  
   else if (dir==EAST)
   {
      if(mov_col+space>=col)
         condition=false;
      for(int i=mov_col; i<=mov_col+space; i++)
      {
          if(grid[mov_row][i]=='#')
             condition=false;
      }
   }
   else if (dir==SOUTH)
   {
      if(mov_row+space>=row)
         condition=false;
      for(int i=mov_row; i<=mov_row+space; i++)
      {
          if(grid[i][mov_col]=='#')
             condition=false;
      }
   }
   else if (dir==WEST)
   {
      if(mov_col-space<0)
         condition=false;
      for(int i=mov_col; i>=mov_col-space; i--)
      {
          if(grid[mov_row][i]=='#')
             condition=false;
      }
   }
    if(condition)							//if condition is true the actions are performed:
   {  									//if the current position of the mover has a block, then when it moves that position is set to a 0, if not it just becomes a ' '
      if(grid[mov_row][mov_col]=='@')
         grid[mov_row][mov_col]='0';
      else
         grid[mov_row][mov_col]=' ';
      if(dir==NORTH)
      { 
         if(mov_row-space>=0)						//the following section of code is to account for the TogglePath() function
         {								//if path is even it sets all the spots on the grid that the mover passes through to a ' '
            if(path % 2==0)
            {
               for(int i=mov_row-1; i>mov_row-space; i--)
               {
                  grid[i][mov_col]=' ';
               }
            }
         }
         if(mov_row-space>=0)
         {
           
            mov_row=mov_row-space;					//if new mover position has a 0 then it becomes a @
            if(grid[mov_row][mov_col]=='0')				//else it becomes the corresponding mover direction
               grid[mov_row][mov_col]='@';
            else
               grid[mov_row][mov_col]='^';
         }      
      }
      else if(dir==EAST)
      {
         if(mov_col+space<col)
         {
            if(path % 2==0)        
            { 
               for(int i=mov_col+1; i<mov_col+space; i++)
               {  
                  grid[mov_row][i]=' ';
               }
            }
         } 
         if(mov_col+space<col)
         {
            mov_col=mov_col+space;
            if(grid[mov_row][mov_col]=='0')
               grid[mov_row][mov_col]='@';
            else
               grid[mov_row][mov_col]='>';
         }
      }
      else if(dir==SOUTH)
      {
         if(mov_row+space<row)
         {
            if(path % 2==0)        
            { 
               for(int i=mov_row+1; i<mov_row+space; i++)
               {  
                  grid[i][mov_col]=' ';
               }
            }
         }
         if(mov_row+space<row)
         {
            mov_row=mov_row+space;
            if(grid[mov_row][mov_col]=='0')
               grid[mov_row][mov_col]='@';
            else
               grid[mov_row][mov_col]='v';
         }
      }
      else if(dir==WEST)
      {
         if(mov_col-space>=0)
         {
            if(path % 2==0)
            {
               for(int i=mov_col-1; i>mov_col-space; i--)
               {
                  grid[mov_row][i]=' ';
               }
            }
         }
         if(mov_col-space>=0)
         {
            mov_col=mov_col-space;
            if(grid[mov_row][mov_col]=='0')
               grid[mov_row][mov_col]='@';
            else
               grid[mov_row][mov_col]='<';
         }

      }

   }
   return condition;
   }

   void Grid::TogglePath()		// toggle whether or not moved path is shown
   {
      path++;       			//if path is even then TogglePath() is on and if odd it is off
   }

   void Grid::TurnLeft()		// turn the mover to the left
   {
      if(dir==NORTH)
      {
         if(grid[mov_row][mov_col]!='@')  				//for each direction it checks to see if the mover's position is not @, if so it is turned left 90 degrees
            grid[mov_row][mov_col]='<';					//if the position is @ then the grid spot stays @ and only the direction is changed
         dir=WEST;
      }
      else if(dir==EAST)
      {
         if(grid[mov_row][mov_col]!='@')
            grid[mov_row][mov_col]='^';
         dir=NORTH;
      }
      else if(dir==SOUTH)
      {
         if(grid[mov_row][mov_col]!='@')
            grid[mov_row][mov_col]='>';
         dir=EAST;
      }
      else if(dir==WEST)
      {
         if(grid[mov_row][mov_col]!='@')
            grid[mov_row][mov_col]='v';
         dir=SOUTH;
      }
   }

   void Grid::PutDown()		// put down an item at the mover's position
   {
      grid[mov_row][mov_col]='@';					//puts down a 0 at the mover's position so it becomes a @
   }  

   bool Grid::PutDown(int r, int c)  // put down an item at (r,c), if possible
   {
      bool condition;
      if(r>=0 && r<=40 && c>=0 && c<=40)
      {
         if(r==mov_row && c==mov_col)					//condition checking
         {								//if r and c are the mover's postiton then it becomes @
            grid[r][c]='@';	
            condition=true;
         }
         else if(grid[r][c]!='0' || grid[r][c]!='#')			//if there is not already a 0 or the desired position is not a # then grid[r][c] becomes a 0
         {
            grid[r][c]='0';
            condition=true;
         }
         else
            condition=false;
      }
      else
         condition=false;

      return condition;
   }

   bool Grid::PickUp()		// pick up item at current position
   {
      if(grid[mov_row][mov_col]=='@')
      {									//if the mover's current position has an item then it should be a @
         if(dir==NORTH)							//if it is then the direction is checked and the position is filled with the corresponding mover
            grid[mov_row][mov_col]='^';
         else if(dir==EAST)
            grid[mov_row][mov_col]='>';
         else if(dir==SOUTH)
            grid[mov_row][mov_col]='v';
         else if(dir==WEST)
            grid[mov_row][mov_col]='<';
     
         return true;
      }
      else
         return false;      
   }

   bool Grid::PlaceBlock(int r, int c)	// put a block at (r,c), if possible
   {
      if(r>=0 && r<row && c>=0 && c<col)
      {
         if(grid[r][c]=='.')						//bound checking, then checks if grid[r][c] has only a '.' and if so sets position to # and if not returns false
            grid[r][c]='#';
         return true;
      }
      else
         return false;

   }

   void Grid::Grow(int gr, int gc)	// grow the grid by gr rows, gc columns
   {
      if(gr>0 && gc>0)
      {
         if(row+gr>40)
            row=40;
         else if(row+gr<=40)
            row=row+gr;
     
         if(gc+col>40)							//sets row and col to the new values
            col=40;							//fills the new rows and columns with '.' and leaves the original grid in place
         else if(col+gc<=40)
            col=col+gc;

         for(int i=row-gr; i<row; i++)
         {
            for(int j=0; j<col; j++)
               grid[i][j]='.';
         }
         for(int i=0; i<row; i++)
         {
            for(int j=col-gc; j<col; j++)
               grid[i][j]='.';
         } 
      }
   }

   void Grid::Display() const	// display the grid on screen
   {
      cout<<"The Grid:"<<'\n';
      if(path%2!=0)							//inital if statement accounts for TOgglePath(). If path is odd then all empty white spaces are filled with a '.'
      {
         for(int i=0; i<row; i++)
         {
            for(int j=0; j<col; j++)
            {
               if(grid[i][j]==' ' && grid[i][j+1]!=' ')			//if current position being checked has a white space but the one infront of it on the same row does not, then one '.' is printed and one is added to j
               {
                  cout<<". ";
                  j++;
               }						
               else
               {
                  while(grid[i][j]==' ' && grid[i][j+1]==' ')		//if there is a white space following another white space then a while loop continues to print a '.' until all white spaces have been filled
                  {
                     cout<<". ";
                     j++;
                  }
               }   
               if(grid[i][j]==' ')					//catches the last white space that the above else statement does not
               {
                  cout<<". ";
                  j++;
               }
             cout<<grid[i][j]<<' ';					//prints finished grid with one space between
            }
            cout<<'\n';
         }
      }
      else								//simply prints the grid how it is with white spaces
      {
         for(int i=0; i<row; i++)
         {
            for(int j=0; j<col; j++)
            {
               cout<<grid[i][j]<<' ';
            }   
            cout<<'\n';
         }
        }
   }

   // Accessors
   bool Grid::FrontIsClear() const
   {
      if(dir==NORTH)
      {
         if(mov_row-1>=0 && grid[mov_row-1][mov_col]!='#')		//if the position infront of the mover's direction is not a block and not out of bounds then it returns true
            return true;
         else
            return false;
      }
      else if(dir==EAST)
      {
         if(mov_col+1<col && grid[mov_row][mov_col+1]!='#')
            return true;
         else        
            return false;
      }
      else if(dir==SOUTH)
      {
         if(mov_row+1<row && grid[mov_row+1][mov_col]!='#')
            return true;
         else        
            return false;
      }
      else if(dir==WEST)
      {
         if(mov_col-1>=0 && grid[mov_row][mov_col-1]!='#')
            return true;
         else        
            return false;
      }
      else
         return false;
   }
   				        
   bool Grid::RightIsClear() const	
   {
      if(dir==NORTH)							//checks to see if the mover's right is not a block and not out of bounds, if not it returns true, else returns false
      {
         if(mov_col+1<col && grid[mov_row][mov_col+1]!='#')
            return true;
         else
            return false;
      }
      else if(dir==EAST)
      {
         if(mov_row+1<row && grid[mov_row+1][mov_col]!='#')
            return true;
         else
            return false;
      }
      else if(dir==SOUTH)
      {
         if(mov_col-1>=0 && grid[mov_row][mov_col-1]!='#')
            return true;
         else
            return false;
      }
      else if(dir==WEST)
      {
         if(mov_row-1>=0 && grid[mov_row-1][mov_col]!='#')
            return true;
         else
            return false;
      }
      else
         return false;

   }
   				
   int Grid::GetRow() const		// return row of the mover
   {
      return mov_row;
   }

   int Grid::GetCol() const		// return column of the mover
   {
      return mov_col;
   }

   int Grid::GetNumRows() const	// return number of rows in the grid
   {
      return row;
   }
   
   int Grid::GetNumCols() const	// return number of columns in the grid
   {
      return col;
   }

