//---------Benjamin Parry------Section 7---------//

#include <iostream>
using namespace std;

#include "grid.h"


int main()
{
  // set up the initial grid
  int row,col;

  cout<<"enter num of rows: ";
  cin>>row;

  if(row<3)
     row=3;
  else if(row>40)
     row=40;

  cout<<"enter the num of cols: ";
  cin>>col;

  if(col<3)
     col=3;
  else if(col>40)
     col=40;

  Grid g(row,col);

  //initial grid
  g.Display();

  do								//a do-while loop is set to break when the mover reaches any of the boarder rows/col
  { 								//firstly, the Move() function is used to move the mover until it hits a boarder
     while(g.FrontIsClear())					//secondly, anytime the mover's front is blocked, it turns left until the front is clear
     {								//thirdly, it moves one position along the boarder and after each move, it checks to see if the escape is to the right
        g.Move(1);						//if not it continues to move by 1's until it hits another a boarder or finds the exit
     }								//if the exit does lie to the mover's right, it turns left 3 times to be facing the exit then moves 1 and breaks the exterior do-while loop
     while(!g.FrontIsClear())
     {
        g.TurnLeft();
        
     }
     while(g.FrontIsClear())
     {
        g.Move(1);
        if(g.RightIsClear())
        {
           for(int i=0; i<3; i++)
              g.TurnLeft();
           g.Move(1);
        }
     }
     }while(g.GetRow()!=0 && g.GetRow()!=row-1 && g.GetCol()!=0 && g.GetCol()!=col-1);
   
   cout<<"We have escaped!"<<'\n';
   g.Display();
   
} 


