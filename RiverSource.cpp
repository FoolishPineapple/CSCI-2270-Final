/*
Brant Smith and Matt Janc
River Source 
December 10,2018
***CSCI 2270 Final Project***
Professor Shayon Gupta
*/

#include "RiverSource.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>// used for absolute value
using namespace std;

/*
	Purpose: Constructor
	Made by: Matt
	Description: Initialize the global variables number of rivers and number of sections.
	Allocate memory for the hash table of rivers and the hash table of sections.
*/
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
/*
	Purpose: Getter function for the private variable number of rivers.
	Made by: Matt
	Description: Basic getter function.
*/
int RiverSource::getRiverSize()
{
  return  numberOfRivers;
}
/*
	Purpose: Return the index of a river name.
	Made by: Brant
	Description: Adds up the ASCI values of the characters in the river name. 
	Then takes the modulo of that number and the number of rivers.
*/
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
/*
	Purpose: Return the index of a section name.
	Made by: Brant
	Description: Adds up the ASCI values of the characters in the section name.
	Returns the modulo of that sum and the defined number of sections
*/
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
/*
	Purpose: Merge the end of one river with a particular section on another.
	Made by: Brant
	Description: Given the end of one river and the section where the two rivers meet,
	set the next river pointer on the end of the river equal to the section on the other.
*/
void RiverSource::mergeRivers(River* feeder, Section *mainStream)
{
	Section *temp=feeder->firstSection;
	while (temp->nextSection!=nullptr)
	{
		temp=temp->nextSection;
	}
	temp->nextSection=mainStream;
}
/*
	Purpose: Locate the memory address of a river
	Made by: Brant
	Description: Go to the location of the river based on its hash key. Then traverse the linked list of rivers.
*/
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
/*
	Purpose: Locate the memory address of a section
	Made by: Brant
	Description: Go to the location of the section based on the hash value of the name.Then traverse the linked list of sections
*/
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
/*
	Purpose: Add a new river to the hash table
	Made by: Brant
	Description: Allocate memory and place the new river in the hash table of rivers.
*/
void RiverSource::addRiver(River *river)
{
	int key=hashRiver(river->riverName);
	River *location=new River;
	location=&rivers[key];
	//If there is no river in that hash location.
	if(location->riverName=="NONAME")
		{
			rivers[key]=*river;
		}
	//If there is already an item in that location, resolve the collision using chaining
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
/*
	Purpose: Add sections to the section hash and as a linked list to a river
	Made by: Brant
	Description: Hash the river that the given section is on. Add the section to the
	chain of sections in the river. Then allocate memory for the section so that it 
	can also reside int the section hash.
*/
void RiverSource::addSection(River *name, Section* sectionToAdd)//working
{
	int key=hashRiver(name->riverName);
	River *tempRiv=&rivers[key];
	//Traverse until the river is found.
	while(tempRiv->riverName!=name->riverName)
	{
		tempRiv=tempRiv->nextRiver;
	}

	Section *temp;
	temp=tempRiv->firstSection;
	//If there is no section on the river
	if (temp==nullptr)
	{
		tempRiv->firstSection=sectionToAdd;
	}
	//Traverse to the end of the chain of sections on a river and add the new section
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
	//If the location in the section hash table is empty
	if(temp2->secName=="NONAME")
	{
		sections[key2]=*sectionToAdd;
	}
	//If there is already an element in the section hash table, resolve collisions using chaining.
	else
	{
		while(temp2->secHashSec!=nullptr)
		{
			temp2=temp2->secHashSec;
		}
		temp2->secHashSec=sectionToAdd;
	}
}
/*
	Purpose: Get the day of the year as a number between 0 and 365
	Made by: Brant
	Description: Take the month and determine how many days of the year come before it.
	Add the current day to that number. NOTE: Febuary has 30 days.
*/
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
/*
	Purpose: Get a number that makes comparing sections levels easy.
	Made by: Matt
	Description: Take in the level and the current section. Get the absolute value of
	the current level- the best level for that section. Divide by the best number.
	The closer this number is to 0, the better the water on that day. 
*/
double RiverSource::getRelativeLevel(Section *currentSection, int level)
{
  double bestLevel=currentSection->bestWaterLevel;
  double dlevel=level;
  double relativeLevel=abs(level-bestLevel)/bestLevel;
  return relativeLevel;
}
/*
	Purpose: Add the water levels for every day from a file
	Made by: Brant
	Description: Go through the sections hash to get every section name. Add .txt.
	Read the water levels and store them in the levels array for each section.
*/
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
				//default.txt populates the array with the proper dates.
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
				int curLevel;
				double curRel;
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
					// In the event that the water level data doesnt start on January 1st. 
					// Find the proper starting day.
					if(dayOfYear==0&&curMonth!=1)
					{
					firstDay=dayOfYear=getDayOfYear(curDay,curMonth)-1;
					}
					getline(s1, word);
					curLevel=stoi(word);
					addLevel2->waterLevel=curLevel;
          			curRel=getRelativeLevel(currentSection,curLevel);
          			addLevel2->relativeLevel=curRel;
					currentSection->levels[dayOfYear]=addLevel2;
					dayOfYear++;
				}
				currentSection=currentSection->secHashSec;
			}
		}
	}
}
/*
	Purpose: Print out all the sections on a river
	Made by: Matt
	Description: Traverses the linked list of sections on a given river and display
	the desired information taken in by the user.
*/
void RiverSource::displayEntireRiver(string riverName,int data)//working
{
  River *displayRiver=searchRiver(riverName);
  if(displayRiver==nullptr)
  {
  	cout<<"This river does not exsist. Please check your spelling and try again."<<endl;
  	cout<<'\n';
  }
  else
  {
  cout<<displayRiver->riverName<<endl;
  cout<<"======================="<<endl;
  Section *currentSection=displayRiver->firstSection;

	  while(currentSection!=nullptr)
	  {
	    if(currentSection->riverName==riverName)
	    {
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
	    }
	    else
	    {
	      cout<<"End Of River"<<endl;
	      cout<<"The "<<riverName<<" feeds into the "<<currentSection->riverName<<" at the "<<currentSection->secName<<" section."<<endl;
	      break;
	    }
	    currentSection=currentSection->nextSection;
	  }
    }
}
/*
	Purpose: Print out all of the rivers
	Made by: Matt
	Description: Goes through the entire hash table and prints out every river and its sections.
*/
void RiverSource::printAll()
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
/*
	Purpose: Show all of the water levels for a year on a section
	Made by: Brant
	Description: Go through the levels array, printing data for each point
*/
void RiverSource::showLevels(string name)
{
	Section *searched=searchSections(name);
	cout<<"====================="<<endl;
	cout<<'\n';
	for (int i=0;i<=365;i++)
	{
		cout<<searched->levels[i]->month<<",";
		cout<<searched->levels[i]->day<<",";
		cout<<searched->levels[i]->waterLevel<<endl;
	}
}
/*
	Purpose: Show all of the seciton names
	Made by: Brant
	Description: Traverse the sections hash table, visiting every element and printing the name.
*/
void RiverSource::showSections()
{
	cout<<'\n';
	cout<<"All loaded sections"<<endl;
	cout<<"+++++++++++++++++++++++++"<<endl;
	for (int i=0;i<numberOfSections;i++)
	{
		Section *temp=&sections[i];
		if(temp->secName!="NONAME")
		{
			while(temp->secHashSec!=nullptr)
			{
				cout<<temp->secName<<endl;//<<"->";
				temp=temp->secHashSec;

			}
			cout<<temp->secName<<endl;
		}
	}
}
/*
	Purpose: Show all of the rivers
	Made by: Brant
	Description: Traverses the river hash table, printing every name
*/
void RiverSource::showRivers()//working
{
	cout<<'\n';
	cout<<"All loaded rivers"<<endl;
	cout<<"+++++++++++++++++++++++++"<<endl;
	for (int i=0;i<numberOfRivers;i++)
	{
		River *temp=&rivers[i];
		if(temp->riverName!="NONAME")
		{
			while(temp->nextRiver!=nullptr)
			{
				cout<<temp->riverName<<endl;//"->";
				temp=temp->nextRiver;
			}
		cout<<temp->riverName<<endl;
		}
	}
}
/*
	Purpose: Find the best day to run a section
	Made by: Matt
	Description: Compare the relative levels of every day on a section. 
	Return the best ones.
*/
WaterLevel RiverSource::getBestDay(Section *currentSection)
{
  WaterLevel *min= new WaterLevel;
  min=currentSection->levels[0];
  for(int i=1; i<=365;i++)
  {
    if(currentSection->levels[i]->relativeLevel<min->relativeLevel)
    {
      min=currentSection->levels[i];
    }
    else if(currentSection->levels[i]->relativeLevel==min->relativeLevel)
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
/*
	Purpose: Convert the class string to a compareable number
	Made by: Brant
	Description: Assigns a numerical value to each different class option.
*/
int RiverSource::convertClass(string rapClass)
{
	int converted;
	if(rapClass=="I")
	{
		converted=1;
	}
	else if(rapClass=="II"||rapClass=="II+")
	{
		converted=2;
	}
	else if(rapClass=="III"||rapClass=="III+")
	{
		converted=3;
	}
	else if(rapClass=="IV"||rapClass=="IV+")
	{
		converted=4;
	}
	else if(rapClass=="V")
	{
		converted=5;
	}
	return converted;
}
/*
	Purpose: Find a section for the user to run
	Made by: Brant
	Description: Given mileage and class, find the best section/s for the user.
	Traverses the section hash table and check the class and distance of each section.

*/
void RiverSource::findMySection(double mileage, string rapClass)
{
	Section *temp;
	//Uses a range of distance to allow more wiggle room. +/- 20%
	double low=mileage-(mileage*.2);
	double high=mileage+(mileage*.2);
	bool foundSec=false;
	for(int i=0; i<numberOfSections;i++)
	{
		temp=&sections[i];
		while(temp!=nullptr)
		{
			//Allows for a rapid class that matches what the user want or is slightly easier.
			if(convertClass(temp->rapidClass)==convertClass(rapClass)||convertClass(temp->rapidClass)==convertClass(rapClass)-1)
			{
				if(temp->sectionLength>=low&&temp->sectionLength<=high)
				{
					cout<<"River: "<<temp->riverName<<endl;
					cout<<"Section: "<<temp->secName<<endl;
					cout<<"Class: "<<temp->rapidClass<<endl;
					cout<<"Length: "<<temp->sectionLength<<" miles"<<endl;
					cout<<'\n';
					foundSec=true;
				}
			}
			temp=temp->secHashSec;
		}
	}
	if(!foundSec)
	{
		cout<<"No section found within given parameters"<<endl;
	}
}
/*
	Purpose: Find the best section on every day
	Made by: Brant
	Description: Compares every relative level on every day and saves the lowest value/s
*/
BestSection* RiverSource::bestForDay()
{
	BestSection *sectionTable=new BestSection[366];
	//temp is the current section
	Section *temp;
	for(int j=0;j<numberOfSections;j++)
	{
		temp=&sections[j];
		temp->nextBest=nullptr;
		if(temp->secName!="NONAME")
		{
			while(temp!=nullptr)
			{
				for(int i=0;i<=365;i++)
					{
					if(sectionTable[i].relLevel>temp->levels[i]->relativeLevel)
					{
						if(sectionTable[i].bestSec==nullptr)
						{
							sectionTable[i].bestSec=temp;
							sectionTable[i].relLevel=temp->levels[i]->relativeLevel;
						}
						sectionTable[i].bestSec=temp;
						sectionTable[i].bestSec->nextBest=nullptr;
						sectionTable[i].relLevel=temp->levels[i]->relativeLevel;
					}
					 else if(sectionTable[i].relLevel==temp->levels[i]->relativeLevel)
					{
						
						Section *temp2=sectionTable[i].bestSec;
						if(sectionTable[i].bestSec->nextBest==nullptr)
						{
							sectionTable[i].bestSec->nextBest=temp;
						}
						else
						{
						while(temp2!=nullptr)
						{
							temp2=temp2->nextBest;
							
						}
						temp2=temp;
						}

					}
			}
				temp=temp->secHashSec;			

		}
	}
	}
	return sectionTable;
}
/*
	Purpose: Link together sections to plan a trip
	Made by: Matt
	Description: Starts at the given section and adds the milages up.
	As long as the input mileage (plus some wiggle room) is less than the input
	mileage, the next section will be printed.
*/
void tripPlanner(Section *currentSection,double mileage)
{
  double milesTraveled=0.0;
  double maxMileage=mileage * 1.5;
  if(milesTraveled>=maxMileage)//test case if user enters 0;
  {
    cout<<"The "<<currentSection->secName<< " is "<<milesTraveled<< "miles long,  and is great for your trip."<<endl;
  }
  else
  {
    Section *temp=currentSection;
    cout<<"Trip Plan for the "<<currentSection->riverName<<endl;
    cout<<"==================="<<endl;
    cout<<"Starting Section:"<<endl;
    while(milesTraveled<mileage)
    {
      if(milesTraveled+temp->sectionLength>maxMileage)
      {
        cout<<"==================="<<endl;
        cout<<"Your trip will be "<<milesTraveled<<" miles in total."<<endl;
        milesTraveled=milesTraveled+temp->sectionLength;
      }
      else
      {
        milesTraveled=milesTraveled+temp->sectionLength;
        cout<<temp->secName<<endl;
        cout<<"Class: "<<temp->rapidClass<<endl;
        cout<<"Best Water Level:"<<temp->bestWaterLevel<<endl;
        cout<<"    |    "<<endl;
        cout<<"    |    "<<endl;
        cout<<"    V    "<<endl;
        if(temp->nextSection==nullptr)
        {
          cout<<"==================="<<endl;
          cout<<"Your trip will be "<<milesTraveled<<" miles in total."<<endl;
          milesTraveled=milesTraveled+maxMileage;
        }
        else
        {
          temp=temp->nextSection;
        }
      }
    }
  }
}
/*
	Purpose: Show the best section on every day
	Made by: Brant
	Description: Traveses the best sections array and prints the name/ names
*/
void RiverSource::showBestSection(BestSection *best)
{
	for (int i=0;i<=365;i++)
	{
		Section *temp=best[i].bestSec;
		cout<<best[i].bestSec->levels[i]->month<<"/"<<best[i].bestSec->levels[i]->day;
		cout<<": "<<best[i].bestSec->secName;
		temp=temp->nextBest;
		while(temp!=nullptr)
		{
			cout<<", "<<temp->secName;
			temp=temp->nextBest;
		}
		cout<<'\n';

	}
}
/*
	Purpose: Main function and GUI
	Made by: Matt and Brant
	Description: Runs the program and loads all data
	NOTES: River and section names that are searched must be exactly as they are saved
*/
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
        Source.addSection(riverExist,temp);
      }
      else
      {
        Source.mergeRivers(riverExist,sectionExist);
      }
    }
  }
  Source.addLevels();
  cout<<'\n'<<endl;
  BestSection *bestSections=Source.bestForDay();

  cout<<string(50,'\n');
  cout<<"Welcome to RiverSource!"<<endl;
	cout<<"================================"<<endl;
	string userChoice;
	cout<<"Please select an option:"<<endl;
	cout<<"1. Quit"<<endl;
	cout<<"2. Print a river"<<endl;
	cout<<"3. Print all rivers"<<endl;
	cout<<"4. Show all sections"<<endl;
	cout<<"5. Show best day for a section"<<endl;
	cout<<"6. Show the projected level of a section of a specific day"<<endl;
	cout<<"7. Find me a section"<<endl;
    cout<<"8. Plan a trip"<<endl;
    cout<<"9. Show the best section/sections on a given day"<<endl;
    cout<<"10. Show the best section for every day"<<endl;
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
			cout<<"\n";
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
   	 	case 4:
  		{
  			Source.showSections();
  			break;
  		}
  		case 5:
  		{
  			string menuChoice;
  			Section *sectionChoice;
  			WaterLevel bestDay;
  			cout<<"Please enter the name of a section to see the best day: ";
  			getline(cin, menuChoice);
  			sectionChoice=Source.searchSections(menuChoice);
  			bestDay=Source.getBestDay(sectionChoice);
        if(bestDay.best!=nullptr)
        {
          cout<<"\n";
          cout<<"Best flow is "<<sectionChoice->bestWaterLevel<<" cfs."<<endl;
          cout<<"Here are all the days with a water level projected to be "<< bestDay.waterLevel<<" cfs"<<":"<<endl;
          while(bestDay.best!=nullptr)
          {
      			cout<<bestDay.month<<"/"<<bestDay.day<<endl;
            bestDay=*bestDay.best;
          }
          cout<<bestDay.month<<"/"<<bestDay.day<<endl;
          break;
        }
        else
        {
          cout<<"\n";
    			cout<<"Best flow is "<<sectionChoice->bestWaterLevel<<" cfs."<<endl;
    			cout<<"The best projected day is: "<<bestDay.month<<"/"<<bestDay.day<<endl;
    			cout<<"The water level is projected to be "<<bestDay.waterLevel<<" cfs"<<endl;
    			cout<<"\n";
        }
  			break;
  		}
  		case 6:
  		{
  			cout<<'\n';
  			string sectionChoice;
  			string dateChoice;
  			int day;
  			int month;
  			cout<<"Please enter a section that you would like to view: ";
  			getline(cin,sectionChoice);
  			cout<<"Please enter a month numerically: ";
  			getline(cin, dateChoice);
  			month=stoi(dateChoice);
  			cout<<"Please enter a day numerically: ";
  			getline(cin, dateChoice);
  			day=stoi(dateChoice);
  			int dateIndex=Source.getDayOfYear(day, month);
  			Section *requestedSection=Source.searchSections(sectionChoice);
  			cout<<"\n";
  			cout<<"On "<<month<<"/"<<day<<" "<<sectionChoice<<" is projected to be at "<<requestedSection->levels[dateIndex]->waterLevel<<" cfs"<<endl;
  			break;
  		}
  		case 7:
  		{
  			string userChoice;
  			int length;
  			cout<<'\n';
  			cout<<"Please enter the length of the section (in miles) you would like to run: ";
  			getline(cin,userChoice);
  			length=stoi(userChoice);
  			cout<<"Please enter the class of the rapid you would like to run: ";
  			getline(cin,userChoice);
  			cout<<'\n';
  			Source.findMySection(length, userChoice);
  			break;
  		}
      case 8:
      {
        string sectionChoice;
  			string mileageChoice;
        double miles;
        cout<<"Let's plan a trip!"<<endl;
        cout<<"What section would you like to start at: ";
  		getline(cin,sectionChoice);
        cout<<"How long would you like your trip to be (in miles): ";
        getline(cin,mileageChoice);
        miles=stod(mileageChoice);
        Section *currentSection=Source.searchSections(sectionChoice);
        River *startRiver=Source.searchRiver(currentSection->riverName);
        Section *sec=startRiver->firstSection;
        if(sec->secName==currentSection->secName)
        {
          currentSection=sec;
        }
        else
        {
          while(sec->secName!=currentSection->secName)
          {
            sec=sec->nextSection;
          }
          currentSection=sec;
        }
        tripPlanner(currentSection,miles);
        break;
      }
      case 9:
      {
      	string word;
      	cout<<"Please enter a month numerically: ";
      	getline(cin,word);
      	int month=stoi(word);
      	cout<<"Please enter a day: ";
      	cout<<'\n';
      	getline(cin,word);
      	int day=stoi(word);
      	int date=Source.getDayOfYear(day,month);
      	 if(bestSections[date].bestSec->nextBest==nullptr)
      	 {
      		cout<<"The best section to run on "<<month<<"/"<<day<<" is: "<<bestSections[date].bestSec->secName<<endl;
      		cout<<"The class is: "<<bestSections[date].bestSec->rapidClass<<endl;
      		cout<<"The distance is: "<<bestSections[date].bestSec->sectionLength<<" miles"<<endl;
      		cout<<"The water level is: "<<bestSections[date].bestSec->levels[date]->waterLevel<<" cfs"<<endl;
      		cout<<'\n';
      	}
      	else
      	{
      		Section *temp=bestSections[date].bestSec;
      		cout<<"You have a few options on "<<month<<"/"<<day<<endl;
      		cout<<'\n';
      		while(temp!=nullptr)
      		{
      			cout<<temp->secName<<endl;
      			cout<<"The class is: "<<temp->rapidClass<<endl;
      			cout<<"The distance is: "<<temp->sectionLength<<" miles"<<endl;
      			cout<<"The water level is: "<<temp->levels[date]->waterLevel<<" cfs"<<endl;
      			cout<<'\n';
      			temp=temp->nextBest;
      		}

      	}
      	break;
      }
      case 10:
      {
      	Source.showBestSection(bestSections);
      	break;
      }
	}
	if(!done)
	{
	cout<<"\n";
	cout<<"================================"<<endl;
	cout<<"Please select an option:"<<endl;
	cout<<"1. Quit"<<endl;
	cout<<"2. Print a river"<<endl;
	cout<<"3. Print all rivers"<<endl;
	cout<<"4. Show all sections"<<endl;
	cout<<"5. Show best day for a section"<<endl;
	cout<<"6. Show the projected level of a section of a specific day"<<endl;
	cout<<"7. Find me a section"<<endl;
    cout<<"8. Plan a trip"<<endl;
    cout<<"9. Show the best section/sections on a given day"<<endl;
    cout<<"10. Show the best section for every day"<<endl;
	getline(cin,userChoice);
	choice=stoi(userChoice);
	}

}
  return 0;
}
