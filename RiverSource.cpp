#include "RiverSource.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
  RiverSource Source();
  ifstream riverFile("riverRead.txt");
  string line;
  string riverName;
  string secName;
  string c;
  double length;
  int bestFlow;
  River* riverExist;
  Section* sectionExist;
  if(riverFile.is_open())
  {
    while(getline(riverFile,line))
    {
      stringstream ss;
      ss<<line;
      string word;
      getline(ss,word,','');
      riverName=word;
      riverExist=searchRiver(riverName);
      if(riverExist==nullptr)
      {
        riverExist= new River(riverName);
      }
      getline(ss,word,',');
      secName=word;
      sectionExist=searchSections(secName);
      if(sectionExist==nullptr)
      {
        Section temp;
        temp.secName=secName;
        getline(ss,word,',');
        c=word;
        temp.rapidClass=c;
        getline(ss,word,',');
        length=stod(word);
        temp.sectionLength=length;
        getline(ss,word,',');
        bestFlow=stoi(word);
        temp.bestWaterLevel=bestFlow;
        temp->nextSection=nullptr;
        temp->notes=nullptr;
        addSection(riverExist,temp);
      }
      else
      {
        mergeRivers(riverExist,sectionExist);
      }
    }
  }
  //*****
  //GUI and user interface
  //*****
  return 0;
}
