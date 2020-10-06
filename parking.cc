#include <iostream>
#include <fstream>
#include <deque>
#include <stack>
#include <string>
#include <algorithm>
#include <cstring>

#define FILE1 "./parking.in"
#define LIMIT 10

/* Weizheng Jiang
 * z1861817
 * CSCI 340 Section 2
 *
 *
 * I certify that this is my own work and where appropriate an extension
   of the starter code provided for the assignment.
*/

using namespace std;

//define the structure to keep all information
typedef struct{
	int id;
	string lp;
	int no_mv = 0;
}CAR;



//get the input data, the first is the act
//use the substr to get the lp
void get_input_vals(const string &line, char &act, string &lp)
{
	act = line[0];

	lp = line.substr( 2, line.length()-3);

}

//print out the message if the garage is not full, if it is full, print out the message shows the garage is full
void arrival(const CAR &car, deque<CAR> &D)
{
	cout << " Car " << car.id << " with license plate " << car.lp << " is arrived\n" << endl;   
	if(D.size() == LIMIT)
	{
		cout << " But garage is full\n " << endl;
	}
	else
	{
		//if the garage is not full, push the car into the deque
		D.push_back(car);
	}
}

//
void departure(const string &lp, deque<CAR> &D, stack<CAR> &S)
{
	bool move = false;

	while(!D.empty())
	{
		//check the lp for the car, if it is correct, car can moves directly
		CAR car;
	        car = D.front();
		D.pop_front();
		if(car.lp == lp)
		{
			move = true;
			car.no_mv++;
			cout << " Car " << car.id << " with license plate " << car.lp << " is departed\n " << endl;
			cout << " Car was moved " << car.no_mv << " times in the garage\n " << endl; 
			break;
		}
		else
		{
			//if the lp is not correct, push the cars that before it into the stack
			S.push(car);
		}
	}

	if(!move)
	{
		//if the lp is an invalid number, print the error message.
		cout << " No car with license plate " << lp << " in garage\n " << endl;
	}
}




int main()
{
	//declare the deque and stack
	deque<CAR> Car;
	stack<CAR> s_car;
	
	//open the input file, initialize the id
	ifstream input;
	input.open(FILE1);
	string line;
	int id = 1;

	while(input)
	{
		//read the data line by line
		getline(input,line);
		char act;
		string lp;
		
		get_input_vals(line,act,lp);

		if(act == 'A')
		{
			//if the action is arrive, call the arrival method
			CAR car;
			car.id = id;
			car.lp = lp;
			arrival(car,Car);
			id++;
		}
		else if(act == 'D')
		{
			//if the action is departure, call the departure method
			departure(lp,Car,s_car);
			while(!s_car.empty())
			{	
				//put the cars in the stack back to the deque
				CAR car = s_car.top();
				car.no_mv++;
				Car.push_front(car);
				s_car.pop();
			}

		}
		else{
			cout << " ' " << act << " ' " << " Invalid action\n " << endl;
		}


	}

	return 0;
}	
