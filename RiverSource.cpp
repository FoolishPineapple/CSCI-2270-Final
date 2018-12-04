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
	char userChoice;
	cout<<"Please select an option:"<<endl;
	cout<<"1. Quit"<<endl;	
	cout<<"2. Load water level data"<<endl;
	bool done=false;
while (!done)
{
	switch(userChoice)
	{
		case ('1'):
		{
			cout<<"GoodBye"<<endl;
			done=true;
		}
		case '2':
		{
			string userInput;
			cout<<"Please load in water data for rivers"<<endl;
			bool inDone=false;
			//waterLevel temp[365];
			cout<<"Enter a river name: ";
			getline(cin, userInput);
			//int key=Source.hashRiver(userInput);
			River *tempRiv=Source.searchRiver(userInput);
			Section *currentSec=tempRiv->firstSection;
			//cout<<*rivers[key].firstSection->name<<endl;
			cout<<"Enter file name: ";
			getline(cin,userInput);
			ifstream fileRead(userInput);
			string line;

			int counter=0;
			while(getline(fileRead, line))
			{
				stringstream ss;
				ss<<line;
				string word;
				int count=0;
				while(getline(ss,word, ','))
				{
					if(count==0)
					{
						currentSec->levels[counter].month=stoi(word);
						count++;
					}
					else if (count==1)
					{
						currentSec->levels[counter].day=stoi(word);
						count++;
					}
					else
					{
						currentSec->levels[counter].waterLevel=stoi(word);
						count++;
					}	
				}
				counter++;
			}
			
				
				

			
		}
	}
}
  return 0;
}
