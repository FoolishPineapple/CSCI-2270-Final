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
      cout<<"Enter River Name: ";
      getline(cin,riverName);
      cout<<"Enter Section Name: ";
      getline(cin,secName);
      cout<<"Enter the section's Class: ";
      getline(cin,c);
      cout<<"Enter the section length: ";
      getline(cin,length);
      cout<<"Enter the section's best flow: ";
      getline(cin,bestFlow);
      outFile<<riverName<<","<<secName<<","<<c<<","<<length<<","<<bestFlow<<endl;
      cout<<"successfully loaded"<<endl;
      cout<<"enter more 1-yes 0-no :";
      cin>>choice;
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
