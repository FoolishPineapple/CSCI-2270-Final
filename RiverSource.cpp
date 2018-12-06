#include "RiverSource.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

RiverSource::RiverSource(int riverSize,int sectionSize)//working
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

int RiverSource::getRiverSize()//working
{
  return  numberOfRivers;
}

int RiverSource::hashRiver(string name)//working
{
	int key=0;
	for (int i=0;i<name.size();i++)
	{
		key+=int(name[i]);
	}
	key=key%numberOfRivers;

	return key;
}
int RiverSource::hashSection(string name)//working
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
River* RiverSource::searchRiver(string name)//working
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
  if(current->secName!="NONAME")
  {
    while(current!=nullptr)
  	{
  		if (current->secName==name)
  			{
  				return current;
  			}
  		current=current->secHashSec;
  	}
  }
	return nullptr;
}
void RiverSource::addRiver(River *river)//working
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
void RiverSource::addSection(River *name, Section* sectionToAdd)//working
{
	int key=hashRiver(name->riverName);
	River *tempRiv=&rivers[key];
	while(tempRiv->riverName!=name->riverName)
	{
		tempRiv=tempRiv->nextRiver;
	}

	Section *temp=new Section;
	temp=tempRiv->firstSection;
	if (temp==nullptr)
	{
		tempRiv->firstSection=sectionToAdd;
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
	Section *temp2=new Section;
	temp2=&sections[key2];
	if(temp2->secName=="NONAME")
	{
		sections[key2]=*sectionToAdd;
	}
	else
	{
		while(temp2->secHashSec!=nullptr)
		{
			temp2=temp2->secHashSec;
		}
		temp2->secHashSec=sectionToAdd;
	}
}
int RiverSource::getDayOfYear(int day, int month)
{
	int dayOfYear= -1;
	if(month==1)
	{
		dayOfYear+=day;
	}
	else if(month==2)
	{
		dayOfYear+=day+31;
	}
	else if(month==3)
	{
		dayOfYear+=day+60;
	}
	else if(month==4)
	{
		dayOfYear+=day+90;
	}
	else if(month==5)
	{
		dayOfYear+=day+121;
	}
	else if(month==6)
	{
		dayOfYear+=day+151;
	}
	else if(month==7)
	{
		dayOfYear+=day+182;
	}
	else if(month==8)
	{
		dayOfYear+=day+213;
	}
	else if(month==9)
	{
		dayOfYear+=day+243;
	}
	else if(month==10)
	{
		dayOfYear+=day+274;
	}
	else if(month==11)
	{
		dayOfYear+=day+304;
	}
	else if(month==12)
	{
		dayOfYear+=day+333;
	}
	return dayOfYear;
}
void RiverSource::addLevels()
{
	
	for(int i=0;i<numberOfSections;i++)
	{
		Section *currentSection;
		currentSection=&sections[i];
		if(currentSection->secName!="NONAME")
		{
			while(currentSection!=nullptr)
			{
				string waterLevelFile=currentSection->secName + ".txt";
				ifstream defaultFile("default.txt");
				string line2;
				int counter=0;
				WaterLevel *addLevel=new WaterLevel;
				while(getline(defaultFile,line2)&&counter<=365)
				{
					int day1;
					int month1;
					stringstream ss;
					ss<<line2;
					string word;
					getline(ss,word,',');
					month1=stoi(word);
					getline(ss,word);
					day1=stoi(word);
					addLevel->month=month1;
					addLevel->day=day1;
					addLevel->waterLevel=0;
					currentSection->levels[counter]=addLevel;
					counter++;
				}
				ifstream levelFile(waterLevelFile);
				string line;
				int curDay;
				int curMonth;
				int dayOfYear=0;
				int firstDay=0;
				while(getline(levelFile, line) && dayOfYear<=365)
				{
					WaterLevel *addLevel2=new WaterLevel;
					stringstream s1;
					s1<<line;
					string word;
					getline(s1, word, ',');
					addLevel2->month=stoi(word);
					curMonth=stoi(word);
					getline(s1, word, ',');
					addLevel2->day=stoi(word);
					curDay=stoi(word);
					if(dayOfYear==0&&curMonth!=1)
					{
					firstDay=dayOfYear=getDayOfYear(curDay,curMonth);
					}
					getline(s1, word);
					addLevel2->waterLevel=stoi(word);
					currentSection->levels[dayOfYear]=addLevel2;
					dayOfYear++;

				}
				currentSection=currentSection->secHashSec;

			}
		}
	}
}

void RiverSource::displayEntireRiver(string riverName,int data)//working
{
  River *displayRiver=searchRiver(riverName);
  cout<<displayRiver->riverName<<endl;
  cout<<"======================="<<endl;
  Section *currentSection=displayRiver->firstSection;

  while(currentSection!=nullptr)
  {
    //currentSection=currentSection->nextSection;
    if(data>=1)
    {
      cout<<currentSection->secName<<endl;
    }
    if(data>=2&&data!=5)
    {
      cout<<"Class: "<<currentSection->rapidClass<<endl;
    }
    if(data>=3)
    {
      cout<<"Length: "<<currentSection->sectionLength<<" miles"<<endl;
    }
    if(data>=4&&data!=5)
    {
      cout<<"Best water level: "<<currentSection->bestWaterLevel<<" cfs"<<endl;
    }
    if(currentSection->nextSection!=nullptr)
    {
    cout<<"    |    "<<endl;
    cout<<"    V   "<<endl;
	  }
	  else
	  {
		    cout<<'\n'<<endl;
	  }
    currentSection=currentSection->nextSection;
  }
}

void RiverSource::printAll()//only printing one river
{
  for(int i=0;i<numberOfRivers;i++)
  {
    River *temp=&rivers[i];
    if (temp->riverName!="NONAME")
    {
	      while(temp->nextRiver!=nullptr)
	      {
	        displayEntireRiver(temp->riverName,4);
	        temp=temp->nextRiver;
	      }
	      displayEntireRiver(temp->riverName,4);
	}
  }
}
void RiverSource::showLevels(string name)
{
	Section *searched=searchSections(name);
	cout<<"====================="<<endl;
	for (int i=0;i<=365;i++)
	{
		cout<<searched->levels[i]->month<<",";
		cout<<searched->levels[i]->day<<",";
		cout<<searched->levels[i]->waterLevel<<endl;
	}
}
void RiverSource::showSections()
{
	for (int i=0;i<numberOfSections;i++)
	{
		Section *temp=&sections[i];
		if(temp->secName!="NONAME")
		{
			while(temp->secHashSec!=nullptr)
			{
				cout<<temp->secName<<"->";
				temp=temp->secHashSec;

			}
			cout<<temp->secName<<endl;
		}
	}
}
void RiverSource::showRivers()//working
{
	for (int i=0;i<numberOfRivers;i++)
	{
		River *temp=&rivers[i];
		if(temp->riverName!="NONAME")
		{
			while(temp->nextRiver!=nullptr)
			{
				cout<<temp->riverName<<"->";
				temp=temp->nextRiver;
			}
		cout<<temp->riverName<<endl;
		}
	}
}

double RiverSource::getRelativeLevel(Section *currentSection, int level)
{
  int bestLevel=currentSection->bestWaterLevel;
  double relativeLevel=level/bestLevel;
  return relativeLevel;
}

WaterLevel RiverSource::getBestDay(Section *currentSection)
{
  WaterLevel *min=currentSection->levels[0];
  for(int i=1; i<=365;i=i+1)
  {
    if(currentSection->levels[i]->relativeLevel<min->relativeLevel)
    {
      min=currentSection->levels[i];
    }
    if(currentSection->levels[i]->relativeLevel==min->relativeLevel)
    {
      if(min->best==nullptr)
      {
        min->best=currentSection->levels[i];
      }
      else
      {
        WaterLevel *temp=min;
        while(temp->best!=nullptr)
        {
          temp=temp->best;
        }
        temp->best=currentSection->levels[i];
      }
    }
  }
  return *min;
}

int main()
{
  RiverSource Source(15,20);
  ifstream riverFile("riverRead.txt");
  string line;
  string riverName;
  string sectionName;
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
      sectionName=word;
      sectionExist=Source.searchSections(sectionName);
      if(sectionExist==nullptr)
      {
        Section *temp=new Section(sectionName,riverName);
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
  //workin^^^
  
  Source.addLevels();
  cout<<"Welcome to RiverSource!"<<endl;
	cout<<"================================"<<endl;
	string userChoice;
	cout<<"Please select an option:"<<endl;
	cout<<"1. Quit"<<endl;
	cout<<"2. Print a rivers"<<endl;
	cout<<"3. Print all rivers"<<endl;
	cout<<"4. Show all sections"<<endl;
	cout<<"5. Show all water levels and dates for a section"<<endl;
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
			string menuChoice;
			string settingChoice;
			cout<<"Please enter the name of the river: ";
			getline(cin, menuChoice);
			cout<<"Options:"<<endl;
			cout<<"1. Display only section names."<<endl;
			cout<<"2. Display section names and class."<<endl;
			cout<<"3. Display section names, class, and length."<<endl;
			cout<<"4. Display section names, class, length, and best water level."<<endl;
			cout<<"Choice: ";
			getline(cin, settingChoice);
			int settingNumber=stoi(settingChoice);
			Source.displayEntireRiver(menuChoice, settingNumber);

			break;
		}
		case 3:
		{
		  Source.showRivers();
		  break;
		}
	}
	case 4:
	{
		Source.showSections();
		break;
	}
	if(!done)
	{
		cout<<"Please select an option:"<<endl;
	
	cout<<"1. Quit"<<endl;
	cout<<"2. Print a river"<<endl;
	cout<<"3. Print all rivers"<<endl;
	getline(cin,userChoice);
	choice=stoi(userChoice);
	}

}
  return 0;
}
