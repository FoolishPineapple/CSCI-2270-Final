#include <string>
#include <iostream>
#include<sstream>
#include<fstream>
using namespace std;
struct waterLevel
{
	int month;
	int day;
	int cfs;
};
int main()
{
	string userFile;
	waterLevel thisLevel[365];
	cout<<"enter file name: ";
	getline(cin,userFile);
	ifstream fileRead(userFile);
	int location=0;
	
		int m;
		int d;
		int c;
		string line;
		int lines=1;
		
		while (getline(fileRead, line))
		{
			stringstream ss;
			ss<<line;
			string word;
			int col=0;
			bool filled=false;
			
				
				while (getline(ss,word,'\t'))
				{

					if(filled==false)
					{
						if(col==4)
						{
							m=stoi(word);
						}
						else if(col==5)
						{
							d=stoi(word);
						}
						else if(col==20)
						{
							c=stoi(word);
							filled=true;
						}
						if (filled==true)
						{
							
							thisLevel[location].month=m;
							thisLevel[location].day=d;
							thisLevel[location].cfs=c;
							location++;
						}
						col++;
					}
				}
				
			
			lines++;
		}
	
		ofstream out(userFile);
	for(int i=0;i<location;i++)
	{
		out<<thisLevel[i].month<<", "<<thisLevel[i].day<<", "<<thisLevel[i].cfs<<'\n';
	}
}
