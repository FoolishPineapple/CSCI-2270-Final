#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void readIN()
{
  bool quit=false;
  string riverName;
  string secName;
  string c;
  string length;
  string bestFlow;
  ofstream outFile;
  string choice;
  outFile.open("riverRead.txt",std::ofstream::out | std::ofstream::app);
  if(outFile.is_open())
  {
    while(quit==false)
    {
      cout<<"Enter River Name: "<<endl;
      getline(cin,riverName);
      cout<<"Enter Section Name: "<<endl;
      getline(cin,secName);
      cout<<"Enter the section's Class: "<<endl;
      getline(cin,c);
      cout<<"Enter the section length: "<<endl;;
      getline(cin,length);
      cout<<"Enter the section's best flow: "<<endl;
      getline(cin,bestFlow);
      outFile<<riverName<<","<<secName<<","<<c<<","<<length<<","<<bestFlow<<endl;
      cout<<"successfully loaded"<<endl;
      cout<<"enter more 1-yes 0-no :"<<endl;
      getline(cin,choice);
      if(choice!="1")
      {
        quit=true;
      }
    }
  }
  else
  {
    cout<<"failed to open file"<<endl;
  }
  outFile.close();
}


int main()
{
  readIN();
  return 0;
}
