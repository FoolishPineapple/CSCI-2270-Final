#ifndef RIVERSOURCE_HPP
#define REVERSOURCE_HPP
#include <string>
#include <iostream>
using namespace std;
struct River
{
	string riverName;
	*section sections;
};
struct Section
{
	int bestWaterLevel;
	string secName;
	string rapidClass;
	*section nextSection;
	*rapid firstRapid;
	*note notes;
};
struct Rapid
{
	string rapidName;
	double mileage;
	string rapidClass;
	*rapid nextRapid;
	Sting beta;
};
struct waterLevel
{
	string date;
	int waterLevel;	
};
struct Note
{
	string aNote;
	*note nextNote;
};
public:
	//constructor
	RiverSource();

	//deconstructor
	~riverSource();

	//find the best day to run a certain section given the name of the section
	void bestDayOnSection(string name);

	//display the beta for a run
	//outputs the mileage for each rapid in a section 
	//outputs the beta for each rapid
	void diplayBeta(section *wantedSection);

	//given a start and stop section, output all raipids and their beta
	//with the correct mileages
	void linkSections(section *start,section *stop);

	//displays a water water level for a given day
	void diplayWaterLevel(section *wantedSection, string date);

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
	void addSection();

	//displays an entire river from head to end
	//takes in the name of the river
	void diplayEntireRiver(string riverName);

private:
int numberOfRivers=20;
River rivers[numberOfRivers];
int currentLength;

#endif





