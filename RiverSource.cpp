#include "RiverSource.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

RiverSource::RiverSource(int riverSize,int sectionSize)
{
  numberOfRivers=riverSize;
  numberOfSections=sectionSize;
  Section *sectionArray= new Section[numberOfSections];
  River *riverArray=new River[numberOfRivers];
  rivers=riverArray;
  sections=sectionArray;
}

RiverSource::~RiverSource()
{

}

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
// void RiverSource::buildSectionHash()
// {
// 	int key;
// 	Section newSection;
// 	for (int i=0;i<15;i++)
// 	{
//
// 			Section *current=rivers[i].firstSection;
// 			while (current!=nullptr)
// 			{
// 				key=hashSection(current->secName);
// 				/////////////
// 				current=current->nextSection;
// 			}
//
// 	}
// }
void RiverSource::mergeRivers(River* feeder, Section *mainStream)
{
	Section *temp=feeder->firstSection;
	while (temp->nextSection!=nullptr)
	{
		temp=temp->nextSection;
	}
	temp->nextSection=mainStream;
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
	int key=hashSection(name);
	Section *current=&sections[key];
	//cout<<current->secName<<endl;
  if(current!=NULL)
  {
    while(current->secName!=name && current->nextSection!=NULL)
  	{
  		if (current->secName==name)
  			{
  				return current;
  			}
  		current=current->nextSection;
  	}
  }
	//cout<<"section not found"<<endl;
	return nullptr;
}
void RiverSource::addRiver(River *river)
{
	int key=hashRiver(river->riverName);
	River *location=&rivers[key];
	if(location==nullptr)
		{
			location=river;
		}
	else
	{
		while(location->nextRiver!=nullptr)
		{
			location=location->nextRiver;
		}
		location->nextRiver=river;
	}

}
void RiverSource::addSection(River *name, Section* sectionToAdd)
{
	int key=hashRiver(name->riverName);
	Section *temp=rivers[key].firstSection;
	//cout<<temp<<endl;
	if (temp==nullptr)
	{
		temp=sectionToAdd;
	}
	else
	{
	while (temp->nextSection!=nullptr)
		{
			temp=temp->nextSection;
		}
	    temp->nextSection=sectionToAdd;
	}

	int key2=hashSection(sectionToAdd->secName);
	Section *temp2=&sections[key2];
	if(temp2==nullptr)
	{
		sections[key2]=*sectionToAdd;
	}
	else
	{
		//ERROR HERE
		while(temp2->secHashSec!=nullptr)
		{
			temp2=temp2->secHashSec;
		}
		temp2->secHashSec=sectionToAdd;
	}
}
void RiverSource::addLevels()
{
		for(int i=0;i<numberOfSections;i++)
			{
				Section *currentSection=&sections[i];
				while(currentSection!=nullptr)
				{
					string waterLevelFile=currentSection->secName + ".txt";
					ifstream levelFile(waterLevelFile);
					string line;
					int daysOfYear=0;
					while(getline(levelFile, line))
					{
						stringstream s1;
						s1<<line;
						string word;
						getline(s1, word, ',');
						currentSection->levels[daysOfYear].month=stoi(word);
						getline(s1, word, ',');
						currentSection->levels[daysOfYear].day=stoi(word);
						getline(s1, word, ',');
						currentSection->levels[daysOfYear].waterLevel=stoi(word);
						daysOfYear++;
					}
					currentSection=currentSection->secHashSec;
				}
			}	

}
int main()
{
  RiverSource Source(15,20);
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
        Source.addRiver(riverExist);
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
        Source.addSection(riverExist,&temp);
      }
      else
      {
        Source.mergeRivers(riverExist,sectionExist);
      }
    }
  }
 
  	cout<<"Welcome to RiverSource!"<<endl;
	cout<<"================================"<<endl;
	string userChoice;
	cout<<"Please select an option:"<<endl;
	cout<<"1. Quit"<<endl;	
	cout<<"2. Load water level data"<<endl;
	getline(cin, userChoice);
	int choice=stoi(userChoice);
	bool done=false;
while (!done)
{
	switch(choice)
	{
		case 1:
		{
			cout<<"GoodBye"<<endl;
			done=true;
		}
		case 2:
		{
			Source.addLevels();
		
			break;
		}
	}
}
  return 0;
}
