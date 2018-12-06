#ifndef RIVERSOURCE_HPP
#define RIVERSOURCE_HPP
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
struct Note
{
	string aNote;
	Note* nextNote;
};
struct WaterLevel
{
	int day;
	int month;
	int waterLevel;
	double relativeLevel;
	WaterLevel *best;
	WaterLevel()
	{
		this->day=0;
		this->month=0;
		this->waterLevel=0;
		this->relativeLevel=200.0;
		this->best=nullptr;
	}
};
struct Section
{
	int bestWaterLevel;
	string riverName;
	string secName;
	string rapidClass;
	double sectionLength;
	WaterLevel *levels[366];
	Section *nextSection;
	Section *secHashSec;
	WaterLevel bestDay;
	Note* notes;
	Section(string name,string river)
	{
		this->secName=name;
		this->riverName=river;
		this->nextSection=nullptr;
		this->secHashSec=nullptr;

	}
	Section()
	{
		this->secName="NONAME";
		this->nextSection=nullptr;
		this->secHashSec=nullptr;
		this->bestWaterLevel=0;

	}
};
struct River
{
	string riverName;
	Section* firstSection;
	River *nextRiver;
	River(string name)
	{
		this->riverName=name;
		this->firstSection=nullptr;
		this->nextRiver=nullptr;
	}
	River()
	{
		this->riverName="NONAME";
		this->firstSection=nullptr;
		this->nextRiver=nullptr;
	}
};




class RiverSource
{
	public:
		//constructor
		RiverSource(int riverSize,int sectionSize);

		//deconstructor
		~RiverSource();


		void createSection();


		//find the best day to run a certain section given the name of the section
		void bestDayOnSection(string name);

		//given a start and stop section, output all raipids and their beta
		//with the correct mileages
		void linkSections(Section *start,Section *stop);

		//displays a water water level for a given day
		void diplayWaterLevel(Section *wantedSection, string date);

		//find the best section to run on a given day
		//takes in the class, date and wanted mileage
		void findBestSection(string wantedClass, string date, int mileage);

		//adds the river names from a csv
		//prompts user for the file name and reads in the river names
		void addRiverNames();

		//add beta for a section from a file
		void addBeta();

		//add section names from a file
		//promts user for a river and for file name
		void addSection(River *riverName, Section* sectionToAdd);

		//displays an entire river from head to end
		//takes in the name of the river
		void displayEntireRiver(string riverName,int data);

		//find the location of a section
		Section* findSection(string river, string secitonName);

		int hashRiver(string name);

		int hashSection(string name);

		void buildSectionHash();

		River* searchRiver(string name);

		Section* searchSections(string name);

		void mergeRivers(River* feeder, Section *mainStream);

		void addRiver(River *river);

		void addLevels();

		int getRiverSize();

		void printAll();

		void showLevels(string name);

		void showRivers();

		void showSections();

		double getRelativeLevel(Section *currentSection, int level);

		WaterLevel getBestDay(Section *currentSection);

		int getDayOfYear(int day, int month);

		Section* getBestSecction(int date);

		void findMySection(double mileage, string rapClass);

		int convertClass(string rapClass);

		void tripPlanner(string startingSection,double mileage);

	private:
		int numberOfRivers;
		int numberOfSections;
		River *rivers;
		Section *sections;
		int currentLength;


};
#endif
