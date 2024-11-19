

#include <stdlib.h> // sleep(2000); wait 2 seconds
// #include <stdbool.h>
// #include <stdio.h>
#include <unistd.h>
#include <iostream>
// #include <iomanip>
#include <fstream>
// #include <sstream>
// #include <cctype>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

#define INF 999

int V;
int src;
// graph
int cost[100][100];
// distances
int dist[100];
// visited flags
bool visited[100];
// track parent node. [index = key], "value = parent"
int parent[100];
//  create input and output files
ifstream infile1;
ifstream infile2;
ofstream outfile;

void title()
{
	vector<string> authors = {" Nathan White, "};
	cout << "\n\n----------------------------------------------------------------\n";
	cout << "Authors: ";
	for (string author : authors)
	{
		cout << author;
	}
	cout << endl;
	cout << "Date: 11/24/2024\n";
	cout << "Course: CS311 (Data structures and Algorithms)\n";
	cout << "Description : Program to find the shortest route between cities\n";
	cout << "----------------------------------------------------------------\n";
}

void pause_time(int seconds)
{
	int pause = 0;
	while (pause < seconds)
	{
		pause++;
		fprintf(stderr, ".");
		sleep(1);
		fflush(stdout);
	}
}

void init()
{
	for (int i = 0; i < V; i++)
	{
		parent[i] = i; // initialize the parent: A = 1, B = 2, etc...
		dist[i] = INF; // initial distances are INFINITY
	}
	dist[src] = 0;
}

int getNearest()
{
	int minvalue = INF; // minimum value distance node next
	int minnode = 0;
	for (int i = 0; i < V; i++)
	{
		// ith node not visited and distance less than current minimum value
		if (!visited[i] && dist[i] < minvalue)
		{
			// update minimum value to the lesser distance
			minvalue = dist[i];
			// update the corresponding minimum value to the ith node
			minnode = i;
		}
	}
	// return the corresponding minimum node
	return minnode;
}

/**
 * Extracts the city information from an input file
 * @param ID the entry number of the associated city
 * @param City_Code the key representing a city
 * @param City_Name the string for holding the city name
 * @param Population the population of the associated city
 * @param Elevation the elevation of the associated city
 */
struct City
{
	int ID;
	string City_Code;
	string City_Name;
	int Population;
	int Elevation;
};

/**
 * Extracts the route information from an input file
 * @param From_City_ID the key representing the source city
 * @param To_City_ID the key representing the destination city
 * @param Distance the distance from the source to the destination
 */
struct Route
{
	string From_City_ID;
	string To_City_ID;
	int Distance;
};

/*
 * argv[0]: "prog"
 * argv[1]: "From_City"
 * argv[2]: "To_City"
 */
int main(int argc, char **argv)
{
	title();
	// sleep(1);

	// City: ID, City_Code, City_Name, Population, Elevation
	City city;
	vector<City> cityList;
	Route route;
	vector<Route> routeList;

	// Route: From_City_ID, To_City_ID, Distance
	const char *source = argv[1];
	const char *destination = argv[2];

	if (argv[1] && argv[2])
	{
		// cout << "Source: " << source << endl;
		cout << "Source: " << source << endl;
		// sleep(3);
		// cout << "Destination: " << destination << endl;
		cout << "Destination: " << destination << endl;
	}
	cout << endl;
	// sleep(3);

	// pause_time(1);
	//  Open input file 1 - Exit the program if opening failed
	infile1.open("city.txt");
	if (infile1.fail())
	{
		cout << "Error opening input file - city.txt:\n";
		return 1;
	}
	while (infile1)
	{
		infile1 >> city.ID >> city.City_Code >> city.City_Name >> city.Population >> city.Elevation;
		cityList.emplace_back(city);
		V = V + 1;
	}
	infile1.close();
	// pause_time(1);
	//  open input file 2 - Exit the program if opening failed
	infile2.open("roads.txt");
	if (infile2.fail())
	{
		std::cout << "Error opening input file - roads.txt\n";
		return 1;
	}
	while (infile2)
	{
		int x, y, price;
		infile2 >> x >> y >> price;
		cost[x][y] = price;
		// infile2 >> route.From_City_ID >> route.To_City_ID >> route.Distance;
		// routeList.emplace_back(route);
		// cost[infile2][infile2];
	}
	infile2.close();
	// pause_time(1);
	//  Open output file - Exit the program if opening failed
	outfile.open("city_data.txt");
	if (outfile.fail())
	{
		cout << "Error opening output file city_data.txt\n";
		return 1;
	}

	// print cities
	if (argv[1] && argv[2])
	{
		for (int i = 0; i < cityList.size() - 1; i++)
		{
			if (source == cityList[i].City_Code)
			{
				cout << "source == cityList[i].ID: " << cityList[i].City_Name << endl;
				outfile << "source == cityList[i].ID: " << cityList[i].City_Name << endl;
			}
			if (destination == cityList[i].City_Code)
			{
				cout << "destination == cityList[i].ID: " << cityList[i].City_Name << endl;
				outfile << "destination == cityList[i].ID: " << cityList[i].City_Name << endl;
			}
		}
	}
	else
	{
		cout << "No source or destination input" << endl;
		cout << "please run ./a.out <City_Code> <City_Code>" << endl;
		cout << "ex: ./a.out AN VV" << endl;
		cout << endl;
		for (int i = 0; i < cityList.size() - 1; i++)
		{
			// cout << cityList[i].ID << ", " << cityList[i].City_Code << ", " << cityList[i].City_Name;
			// cout << ", " << cityList[i].Population << ", " << cityList[i].Elevation << endl;
		}
	}
	/*
		// print routes
		for (int j = 0; j = routeList.size() - 1; j++)
		{
			cout << routeList[j].From_City_ID << ", " << routeList[j].To_City_ID << ", " << routeList[j].Distance << endl;
		}
	*/

	outfile.close();
	return 0;
}

/*
 * Cost Matrix: (9 Vertices in graph)
 * ----------------------------------
 *                           I N C O M I N G  E D G E  S I D E                                                    *
 *
 *       * * 000  111  222  333  444  555  666  777  888  999  010  011  012  013  014  015  016  017  018  019
 *       * *------------------------------------------------------------------------------------------------------*
 *  O     0 |     732       212                                                                        36         *
 *  U     1 |66                                      111            29                       65        14         *
 *  T     2 |390  17                                 11        38             122            211                  *
 *  G     3 |          273       29                                 42                                            *
 *  O     4 |               122                      32                                 12                  102   *
 *  I     5 |62                  211            132                 871                                           *
 *  N     6 |20   200       41                                 122       81   11                                  *
 *  G     7 |          210            5                                                 74                        *
 *        8 |     95                       120                 2                                            11    *
 *  E     9 |          925                                          121                                     653   *
 *  D    10 |     81        90                                      219                 211                       *
 *  G    11 |          11        98        122  390                                          121       122        *
 *  E    12 |719                                     9                                       26             932   *
 *       13 |          22                            13   182                                               219   *
 *  R    14 |                         22                                                                          *
 *  O    15 |                                                  73                                 98              *
 *  W    16 |77                                      200       21   93                                      190   *
 *  S    17 |                                   29        33                       33   940                 121   *
 *       18 |     322            74   219                 111                                                     *
 *       19 |                                                                                                     *
 *  * * ----------------------------------------------------------------------------------------------------------*
 */
