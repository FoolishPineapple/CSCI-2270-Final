#include "RiverSource.hpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int RiverSource::hashRiver(string name)
{
	int key=0;
	for (int i=0;i<name.size();i++)
	{
		key+=int(name[i]);
	}
	key=key%numberOfRivers;
	return key;
}
int RiverSource::hashSection(string name)
{
	int key=0;
	for (int i=0;i<name.size();i++)
	{
		key+=int(name[i]);
	}
	key=key%numberOfSections;
	return key;
}
void RiverSource::buildSectionHash()
{
	int key;
	Section newSection;
	for (int i=0;i<15;i++)
	{
		Section* current=rivers[i].firstSection;
		while (current!=nullptr)
		{
			key=hashSection(current->secName);
			sections[key].push_back(current);
			current=current->nextSection;
		}
	}
}
River* RiverSource::searchRiver(string name)
{
	int key= hashRiver(name);
	River *current=&rivers[key];
	while(current!=nullptr)
	{
		if (current->riverName==name)
		{
			return current;
		}
		current=current->nextRiver;
	}
	return nullptr;
}
Section* RiverSource::searchSections(string name)
{
	Section* location;
	int key=hashSection(name);
	Section *current=&sections[key];
	while(current!=nullptr)
	{
		if (current->secName==name)
			{
				return current;
			}
		current=current->nextSection;
	}
	cout<<"section not found"<<endl;
	return nullptr;
}
int main()
{
  RiverSource Source;
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
      getline(ss,word,',');
      riverName=word;
      riverExist=Source.searchRiver(riverName);
      if(riverExist==nullptr)
      {
        riverExist= new River(riverName);
      }
      getline(ss,word,',');
      secName=word;
      sectionExist=Source.searchSections(secName);
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
        temp.nextSection=nullptr;
        temp.notes=nullptr;
        Source.addSection(riverExist,temp);
      }
      else
      {
        Source.mergeRivers(riverExist,sectionExist);
      }
    }
  }
  //*****
  //GUI and user interface
  //*****
  return 0;
}
