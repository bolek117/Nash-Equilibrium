#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

#define debug 0
using namespace std;

vector< vector <int> > getData(unsigned int rows, unsigned int columns)
{
	vector< vector <int> > result;

	for (unsigned int i=0; i<rows; i++)
	{
		vector < int > tmp;
		result.push_back(tmp);

		cout << "\n\nRow [" << i << "]\n";
		for (unsigned int j=0; j<columns; j++)
		{			
			int toPush;

			do
			{
				cin.clear();

				cout << "\tColumn [" << i << "][" << j << "] = ";
				cin >> toPush;
				cin.sync();

				if (cin.fail())
					cout << "Entered value must be a number\n";
			} while(cin.fail());

			result[i].push_back(toPush);
		}
	}

	return result;
}

int main()
{
	unsigned int rows=0, columns=0;
	vector < vector < int > > first;
	vector < vector < int > > second;
	
	unsigned int mode = 0;
	
	do
	{
		cout << "Type in [0] to enter your own data or [1] to get default data and press enter: ";
		cin >> mode;
		cin.sync();
		cout << "\n";
	} while (mode != 0 && mode != 1);
	
	if (mode == 0)
	{
		do
		{
			cin.clear();

			cout << "Enter number of rows: ";
			cin >> rows;
			cin.sync();

			if (cin.fail())
				cout << "Number of rows must be positive number\n\n";
		} while(cin.fail());

		do
		{
			cin.clear();

			cout << "Enter number of columns: ";
			cin >> columns;
			cin.sync();

			if (cin.fail())
				cout << "Number of columns must be positive number\n\n";
		} while(cin.fail());

		cout << "\n---------------------\n";
		cout << "Matrice for D1:";
		first = getData(rows, columns);

		cout << "---------------------\n";
		cout << "Matrice for D2:";
		second = getData(rows, columns);
	}
	else
	{
		rows = 3;
		columns = 3;

		vector < int > tmp;
		first.push_back(tmp);
		first[0].push_back(2);
		first[0].push_back(-1);
		first[0].push_back(0);
	
		first.push_back(tmp);
		first[1].push_back(-1);
		first[1].push_back(4);
		first[1].push_back(-3);
	
		first.push_back(tmp);
		first[2].push_back(-1);
		first[2].push_back(0);
		first[2].push_back(-2);

	
		second.push_back(tmp);
		second[0].push_back(8);
		second[0].push_back(-3);
		second[0].push_back(2);

		second.push_back(tmp);
		second[1].push_back(-7);
		second[1].push_back(-7);
		second[1].push_back(-1);
	
		second.push_back(tmp);
		second[2].push_back(-1);
		second[2].push_back(-5);
		second[2].push_back(-2);

		cout << "Rows: " << rows << "\n";
		cout << "Columns: " << columns << "\n";

		cout << "\n------------------\n"
			<< "Looses table for D1:\n";
		for (unsigned int i=0;i<rows;i++)
		{
			for (unsigned int j=0;j<columns;j++)
				cout << "\t" << setw(3) << first[i][j];

			cout << "\n";
		}

		cout << "\n------------------\n"
			<< "Looses table for D2:\n";

		for (unsigned int i=0;i<rows;i++)
		{
			for (unsigned int j=0;j<columns;j++)
				cout << "\t" << setw(3) << second[i][j];

			cout << "\n";
		}
	}

	vector < vector < bool > > nash;

	for(int i=0;i<rows;i++)
	{
		vector < bool > tmp;
		nash.push_back(tmp);
		for(int j=0;j<columns;j++)
		{
			bool result = true;
			for (int k=0;k<2;k++)
			{
				switch(k)
				{
				case 0:
					{
						if (i-1 >= 0)
						{
							if (first[i][j] > first[i-1][j])
								result = false;
						}

						if (j-1 >= 0)
						{
							if (second[i][j] > second[i][j-1])
								result = false;
						}
					}
					break;

				case 1:
					{
						if (i < rows-1)
						{
							if (first[i][j] > first[i+1][j])
								result = false;
						}

						if (j < columns-1)
						{
							if (second[i][j] > second[i][j+1])
								result = false;
						}
					}
					break;
				}
			}
			nash[i].push_back(result);
		}
	}

	cout << "\n------------------\n";

	stringstream resume;
	for(unsigned int i=0;i<rows;i++)
	{
		for(unsigned int j=0;j<columns;j++)
		{
			cout << "\t" << (int)nash[i][j];
			if (nash[i][j] == true)
				resume << "Nash equilibrium at (" << i+1 << "," << j+1 << ") with values (" << first[i][j] << "," << second[i][j] << ")\n";
		}
		cout << "\n";
	}

	cout << "\n" << resume.str() << "\n";

	return 0;
}
