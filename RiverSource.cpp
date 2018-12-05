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

int RiverSource::getRiverSize()
{
  return  numberOfRivers;
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
	return nullptr;
}
void RiverSource::addRiver(River *river)
{
	int key=hashRiver(river->riverName);
	River *location=new River;
	location=&rivers[key];
	if(location->riverName=="NONAME")
		{
			rivers[key]=*river;
		}
	else
	{
		while(location->nextRiver!=nullptr)
		{
			location=location->nextRiver;
		}
		River *lastRiv=searchRiver(location->riverName);
		lastRiv->nextRiver=river;
		
	}

}
void RiverSource::addSection(River *name, Section* sectionToAdd)
{
	int key=hashRiver(name->riverName);
	Section temp=new Section;
	temp=&rivers[key].firstSection;
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
	Section temp2=new Section;
	temp2=&sections[key2];
	if(temp2==nullptr)
	{
		sections[key2]=*sectionToAdd;
	}
	else
	{
		while(temp2->secHashSec!=nullptr)
		{
			temp2=temp2->secHashSec;
		}
		temp2->secHashSec=sectionToAdd; // should we be adding *sectionToAdd instead like up above
	}
}
void RiverSource::addLevels()
{
		for(int i=0;i<numberOfSections;i++)
			{
				Section *currentSection=new Section;
				currentSection=&sections[i];
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

void RiverSource::displayEntireRiver(string riverName,int data)
{
  River *displayRiver=searchRiver(riverName);

  Section *currentSection=displayRiver->firstSection;

  while(currentSection!=nullptr)
  {
    currentSection=currentSection->nextSection;
    if(data>=1)
    {
      cout<<currentSection->secName<<endl;
    }
    if(data>=2&&data!=5)
    {
      cout<<currentSection->rapidClass<<endl;
    }
    if(data>=3)
    {
      cout<<currentSection->sectionLength<<endl;
    }
    if(data>=4&&data!=5)
    {
      cout<<currentSection->bestWaterLevel<<endl;
    }
    cout<<"    |    "<<endl;
    cout<<"    V   "<<endl;
  }

}

void RiverSource::printAll()
{
	 for(int i=0;i<15;i++)
  {

  }
  for(int i=0;i<numberOfRivers;i=i+1)
  {
  	cout<<i<<endl;
    River temp=rivers[i];
    if (temp.riverName!="NONAME")
    {
    	cout<<"here"<<endl;
	    if(temp.nextRiver==nullptr)
	    {
	      displayEntireRiver(temp.riverName,4);
	    }
	    else if(temp.nextRiver!=nullptr)
	    {
	      while(temp.nextRiver!=nullptr)
	      {
	        displayEntireRiver(temp.riverName,4);
	        temp=*temp.nextRiver;
	      }
	    }
	}
  }
}
void RiverSource::showLevels(string name)
{
	Section *searched=searchSections(name);
	for (int i=0;i<365;i++)
	{
		cout<<"here"<<endl;
		cout<<searched->secName<<endl;
		cout<<searched->levels[i].waterLevel<<endl;
		int level=searched->levels[i].waterLevel;
		cout<<level<<endl;
	}
}
void RiverSource::showSections()
{
	for (int i=0;i<numberOfSections;i++)
	{
		Section *temp=&sections[i];
		while(temp->nextSection!=nullptr)
		{
			cout<<temp->secName<<"->";
			temp=temp->nextSection;
		}
		cout<<temp->secName<<endl;
	}
}
void RiverSource::showRivers()
{
	for (int i=0;i<numberOfRivers;i++)
	{
		River *temp=&rivers[i];
		while(temp->nextRiver!=nullptr)
		{
			cout<<temp->riverName<<"->";
			temp=temp->nextRiver;
		}
		cout<<temp->riverName<<endl;
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
        Section *temp=new Section;
        temp->riverName=riverName;
        temp->secName=secName;
        getline(ss,word,',');
        c=word;
        temp->rapidClass=c;
        getline(ss,word,',');
        length=stod(word);
        temp->sectionLength=length;
        getline(ss,word,',');
        bestFlow=stoi(word);
        temp->bestWaterLevel=bestFlow;
        temp->nextSection=nullptr;
        temp->notes=nullptr;
        Source.addSection(riverExist,temp);
      }
      else
      {
        Source.mergeRivers(riverExist,sectionExist);
      }
    }
  }
  Source.showRivers();
  Source.addLevels();
  Source.showSections();
  Source.showLevels("Shoshone");
  cout<<"Welcome to RiverSource!"<<endl;
	cout<<"================================"<<endl;
	string userChoice;
	cout<<"Please select an option:"<<endl;
	cout<<"1. Quit"<<endl;
	cout<<"2. Print a river"<<endl;
	cout<<"3. Print all rivers"<<endl;
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
			break;
		}
		case 2:
		{
			  Source.printAll();

			break;
		}
	}
		cout<<"Please select an option:"<<endl;
	cout<<"1. Quit"<<endl;
	cout<<"2. Print a river"<<endl;
	cout<<"3. Print all rivers"<<endl;
	getline(cin,userChoice);
	choice=stoi(userChoice);

}
  return 0;
}
