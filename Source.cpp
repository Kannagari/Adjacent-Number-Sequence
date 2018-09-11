/*This program generates a 2D array of unique, random integers between 0 - 24, and finds the
longest sequence of adjacent integers. Adjacent in this case is defined as any number that is
+/- 1 of the current number, and is either above, below, left, or right of the current number.
Diagonals do not count as adjacent in this case.*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

//Helper function to print all the values in a 1D vector
void oneDVectorPrint(vector<int> v)
{
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";

}

//Helper function to print all the values in a 2D vector
void twoDVectorPrint(vector<vector<int>> v)
{
	cout << "The 2D vector used for path finding will be the following: \n";
	//Iterate through every cell in the Matrix, printing the value at that index
	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i].size(); j++)
			cout << v[i][j] << " ";

		cout << "\n";

	}
		
}

//Function to help fill the 2D vector with unique, random numbers
vector<int> vectorFillHelper()
{
	//Random seed so the result of random_shuffle will vary from run to run
	srand(time(0));
	//Create vector of integers of size 25
	vector<int> randHelp(25); 

	//Fill the vector with numbers 0 - 24
	for (int i = 0; i < randHelp.size(); i++)
		randHelp[i] = i;

	//Shuffle the vector in a random order, thus creating a list of random, unique numbers from 0 - 24
	random_shuffle(randHelp.begin(), randHelp.end());

	//Print and return the randomly shuffled list
	cout << "The randomly shuffled list used to fill the matrix is as follows: \n";
	oneDVectorPrint(randHelp);
	cout << "\n\n";
	return randHelp;

}

void vectorFill(vector<vector<int>> &pathSelector, int length, int width)
{
	//Catch the randomly shuffled list received from vectorFillHelper
	vector<int> temp = vectorFillHelper();
	int indTrack = 0;

	//For every cell in the matrix
	for(int i = 0; i < width; i++)
		for (int j = 0; j < length && indTrack<temp.size(); j++)
			//Set the current cell of our matrix equal to the next value in our randomly shuffled list
			pathSelector[i][j] = temp[indTrack++];
		



	//Print to show effectiveness of random, unique matrix creation
	twoDVectorPrint(pathSelector);
	cout << "\n\n";
}

//Function to check if 2 given coordinates are next to eachother in the matrix
bool isNeighbor(pair<int, int> p1, pair<int, int> p2)
{
	//Take the absolute values of the differences in the X and Y coordinates, and sum them
	//If the sum == 1, then we know their locations are adjacent, as defined above
	return(abs(p1.first - p2.first) + abs(p1.second - p2.second)) == 1;


}

//Function to generate a coordinate map based off the matrix
vector<pair<int,int>> coordMapMaker(vector<vector<int>> &matrix)
{
	//Set values to the length and width of the matrix
	int width = matrix.size();
	int length = matrix[0].size();
	//Create a vector of pairs to be the coordinate map
	vector<pair<int, int>> coordMap(width * length);

	//For every cell in the matrix
	for (int i = 0; i < width; i++)
		for (int j = 0; j < length; j++)
			//Store that cells location in the corresponding index of the coordinate map
			//ex.) If index [0,0] of the matrix holds value 7
			//The 7th index of the coordMap vector will hold the pair (0,0)
			coordMap[matrix[i][j]] = make_pair(i, j);


	return coordMap;


}

//Function to calculate the longest path in the matrix containing consecutive, adjacent integers
int longestPath(vector<vector<int>> matrix, int length, int width)
{
	//Create a vector of pairs to catch the one being received from coordMapMaker
	vector<pair<int, int>> coordMap(width * length);
	coordMap = coordMapMaker(matrix);
	//Initialize the current and max sequences to 1
	int currSeq = 1;
	int maxSeq = 1;

	//Create a vector to hold the current and max sequences of values
	vector<int> currSeqList;
	vector<int> maxSeqList;

	//For every set of coordinates in the coordMap
	for (int i = 1; i < coordMap.size(); i++)
	{
		//If the current sequence list is empty, add the element one behind the current iteration
		//Done to account for a case where the first value in coordMap is part of the max sequence
		if(currSeqList.empty())
			currSeqList.push_back(i - 1);

		//If the current coordinate set and the previous are indeed neighbors
		if (isNeighbor(coordMap[i], coordMap[i - 1]))
		{
			//Increase the counter for the current sequence
			currSeq++;
			//Add the current value to the sequence list
			currSeqList.push_back(i);
		}
			
		//Otherwise, the current sequence streak was broken
		else
		{
			//Thus, reset the currSequence to 1 and empty the currSeqList
			currSeq = 1;
			currSeqList.clear();

		}
			
		//If the current sequence is >= the previous max sequence
		//*Note: This will cause a sequence of the same size found later to replace one found earlier
		if (currSeq >= maxSeq)
		{
			//Update the value of the max sequence found
			maxSeq = currSeq;
			//Copy the contents of currSeqList to maxSeqList
			maxSeqList = currSeqList;

		}

	}
	
	//Print the values that made up the max sequence
	cout << "The max sequence was as follows: ";
	oneDVectorPrint(maxSeqList);


	return maxSeq;
}


int main()
{
	//Set a length and width of the 2D vector to be created
	int length = 5;
	int width = 5;

	//Create a variable to catch the max sequence value returned
	int maxSeq;

	//Create the 2D vector to be used in the various functions
	vector<vector<int>> pathSelector(width);
	for (int i = 0; i < width; i++)
		pathSelector[i] = vector<int>(length);

	//Fill the vector with random, unique values between 0 and 24
	vectorFill(pathSelector, length, width);

	//Catch the max sequence value returned from longestPath
	maxSeq = longestPath(pathSelector, width, length);

	//Format and print
	cout << "\n";
	cout << "The longest path in the given matrix was: " << maxSeq << "\n";

	system("pause");
	return 0;
}