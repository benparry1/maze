
#include "grid.h"
#include <iostream>
using namespace std;

int main()
{
  
  Grid g1(4,4), g2(5,5), g3(4,6);  
  g1.Display();
  cout<<'\n';
  g2.Display();
  cout<<'\n';
  g3.Display();
  cout<<'\n';

  Grid g4(4,4,2,2,3);
  g4.Display();
  cout<<'\n';
  cout<<g4.Move(1)<<'\n';
  g4.Display();
  cout<<'\n';
  cout<<g4.Move(2)<<'\n';
  g4.Display();
  cout<<'\n';  
  
  g4.PutDown();
  g4.Display();
  cout<<'\n';

  g2.PutDown(2,2);
  g2.Display();
  cout<<'\n';

  if(g1.FrontIsClear()==1)
     cout<<"space is clear"<<'\n';
  else
     cout<<"space is blocked"<<'\n';
  g1.Display();
  cout<<'\n';

  if(g2.FrontIsClear()==1)
     cout<<"space is clear"<<'\n';
  else
     cout<<"space is blocked"<<'\n';
  g2.Display();
  cout<<'\n';

  if(g3.FrontIsClear()==1)
     cout<<"space is clear"<<'\n';
  else
     cout<<"space is blocked"<<'\n';
  g3.Display();
  cout<<'\n';

  if(g4.FrontIsClear()==1)
     cout<<"space is clear"<<'\n';
  else
     cout<<"space is blocked"<<'\n';
  g4.Display();
  cout<<'\n';

  if(g1.RightIsClear()==1)
     cout<<"right space is clear"<<'\n';
  else
     cout<<"right space is blocked"<<'\n';
  g1.Display();
  cout<<'\n';

  if(g2.RightIsClear()==1)
     cout<<"right space is clear"<<'\n';
  else
     cout<<"right space is blocked"<<'\n';
  g2.Display();
  cout<<'\n';

  if(g3.RightIsClear()==1)
     cout<<"right space is clear"<<'\n';
  else
     cout<<"right space is blocked"<<'\n';
  g3.Display();
  cout<<'\n';

  if(g4.RightIsClear()==1)
     cout<<"right space is clear"<<'\n';
  else
     cout<<"right space is blocked"<<'\n';
  g4.Display();
  cout<<'\n';




}

