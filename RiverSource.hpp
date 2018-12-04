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
struct waterLevel
{
	int day;
	int month;
	int waterLevel;
	waterLevel()
	{
		this->day=0;
		this->month=o;
		this->waterLevel=0;
	}
};
struct Section
{
	int bestWaterLevel;
	string secName;
	string rapidClass;
	double sectionLength;
	waterLevel levels[365];
	Section* nextSection;
	Section* secHashSec;
	Note* notes;
	Section(string name)
	{
		this->secName=name;
		this->nextSection=nullptr;
		this->secHashSec=nullptr;
	}
	Section()
	{

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
		void diplayEntireRiver(string riverName);

		//find the location of a section
		Section* findSection(string river, string secitonName);

		int hashRiver(string name);

		int hashSection(string name);

		void buildSectionHash();

		River* searchRiver(string name);

		Section* searchSections(string name);

		void mergeRivers(River* feeder, Section *mainStream);

		void addRiver(River *river);



	private:
		int numberOfRivers;
		int numberOfSections;
		River *rivers;
		Section *sections;
		int currentLength;


};
#endif
