#ifndef RIVERSOURCE_HPP
#define RIVERSOURCE_HPP
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
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
	Section *nextBest;
	Section(string name,string river)
	{
		this->secName=name;
		this->riverName=river;
		this->nextSection=nullptr;
		this->secHashSec=nullptr;
		this->nextBest=nullptr;

	}
	Section()
	{
		this->secName="NONAME";
		this->nextSection=nullptr;
		this->secHashSec=nullptr;
		this->bestWaterLevel=0;
		this->nextBest=nullptr;
	}
};
struct BestSection
{
	Section *bestSec;
	double relLevel;
	BestSection()
	{
		this->bestSec=nullptr;
		this->relLevel=200;
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

		void addSection(River *riverName, Section* sectionToAdd);

		void displayEntireRiver(string riverName,int data);

		int hashRiver(string name);

		int hashSection(string name);

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

		void findMySection(double mileage, string rapClass);

		int convertClass(string rapClass);

		void tripPlanner(string startingSection,double mileage);

		BestSection* bestForDay();

		void showBestSection(BestSection *best);

	private:
		int numberOfRivers;
		int numberOfSections;
		River *rivers;
		Section *sections;
		int currentLength;

};
#endif
