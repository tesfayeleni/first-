#include <iostream> //includes the standard input-output stream library
#include <string> // includes the string library
#include <fstream> // includes the file stream library
using namespace std;
//define symbolic constants
#define g 9.8
#define PI 3.14

int main()
{
	// declare variables
	char ch;
	int h1 = 0, h2 = 0, h = 0, D = 0, L = 0, Q = 0, d = 0, u = 0;
	double	R = 0, f = 0, v = 0, Eloss = 0, Pdrop = 0;
	string choice = "0";
	string filename;
	
	do 
	{
		//choice 1 prompts user to enter parameters
		if (choice == "1")
		{
			cout << "You have chosen to enter the parameters to calculate the pressure drop." << endl;
			//prompt user to enter height 1
			cout << "Enter the height at point 1." << endl;
			cin >> h1;
			//validate input for height 1
			while (h1 < 0)
			{
				cout << "Please enter a valid input for height at point 1" << endl;
				cin >> h1;
			}
			//prompt user to enter height 2
			cout << "Enter the height at point 2." << endl;
			cin >> h2;
			//validate input for height 2
			while (h2 < 0)
			{
				cout << "Please enter a valid input for height at point 2" << endl;
				cin >> h2;
			}
			//prompt user to enter pipe diameter
			cout << "Enter the pipe diameter." << endl;
			cin >> D;
			while (D <= 0)
			{
				cout << "Please enter a valid input for pipe diameter." << endl;
				cin >> D;
			}
			//prompt user to enter pipe length
			cout << "Enter the pipe length." << endl;
			cin >> L;
			//validate input for pipe length
			while (L <= 0)
			{
				cout << "Please enter a valid input for pipe length." << endl;
				cin >> L;
			}
			//prompt user to enter flowrate
			cout << "Enter the flowrate." << endl;
			cin >> Q;
			while (Q <= 0)
			{
				cout << "Please enter a valid input for flowrate." << endl;
				cin >> Q;
			}
			//prompt user to enter viscosity
			cout << "Enter the viscosity." << endl;
			cin >> u;
			//validate input for viscosity
			while (u <= 0)
			{
				cout << "Please enter a valid input for viscosity." << endl;
				cin >> u;
			}
			//prompt user to enter fluid density
			cout << "Enter the fluid density." << endl;
			cin >> d;
            //validate input for fluid density
			while (d <= 0)
			{
				cout << "Please enter a valid input for fluid density." << endl;
				cin >> d;
			}
			cout << "You have entered all the parameters necessary for the computation of pressure drop. Enter the SECOND option." << endl;
			choice = "0";
		}
		//choice 2 allows user to calculate parameters and save results on a text file
	    else if (choice=="2")
	    {
			//if user chooses option 2 before option 1, print message to let them choose option 1 and input parameters first
		    if (d == 0)
		    {
			    cout << "You have not entered the parameters for computation. please choose the first option and enter values for each." << endl;
			    choice = "0";
		    }
			//otherwise calculate intermediate parameters
			else
			{
				v = (4 * Q) / (PI * D * D);
				R = (d * v * D) / u;
				//in the case that reynold's number is more than 2000, print an error message that says fluid is turbulent.
					if (R > 2000)
					{
						cout << "Since Reynold’s number is greater than 2000, fluid is in turbulent flow. This program only computes pressure drop for laminar flow in a horizontal pipe!" << endl;
						exit(1);
					}
					//otherwise, proceed with the rest of the calculations
					else
					{
						f = 8 / R;
						Eloss = (4 * f * v * v * L) / D;
						h = h2 - h1;
						//if the height differnece is negative, make it positive
						if (h < 0)
							h = -h;
						Pdrop = d*(g * h + Eloss); //caluclate pressure drop
						//inform user that intermediate values and the pressure drop have been calculated
						cout << "Intermediate values and Pressure drop have been computed. To save results, enter the file name." << endl;
					    //open a file to save the results
						cin >> filename; 
						ofstream outfile;
						outfile.open(filename);
						//check if file opens successfully
						if (!outfile.is_open())
						{
							cout << "File couldn't open successfully.";
							exit(2);
						}
						//write pipe parameters into the file
						outfile << "Pipe Parameters Info" << endl;
						outfile << "  Pressure point 1 height (h1) : " << h1 << endl;
						outfile << "  Pressure point 2 height (h2) : " << h2 << endl;
						outfile << "  Pipe diameter (D) : " << D << endl;
						outfile << "  Pipe length (L) : " << L << endl;
						outfile << "  Volume flow rate (Q) : " << Q << endl;
						//wirte the fluid parameters into the file
						outfile << "Fluid Parameter Info : " << endl;
						outfile << "  Fluid Velocity (v) : " << v << endl;
						outfile << "  Fluid Density (d) : " << d << endl;
						//write the intermediate parameters into the file
						outfile << "(Intermediate Parameters)" << endl;
						outfile << "  Reynold's Number (R) : " << R << endl;
						outfile << "  Friction factor (f) : " << f << endl;
						outfile << "  Energy Loss (Eloss)" << Eloss << endl;
						outfile << "  Presure Drop (Pdrop) : " << Pdrop << endl;
						//close the file
						outfile.close();

						//inform uset that all data values have been saved successfully
						cout << "All the data values have been entered successfully!" << endl;
						//give user the option to see saved results from the file
						cout << "To display the results of the calculation of pressure drop, choose the THIRD option." << endl;
						choice = "0";

					}
			}

		}
		//choice 3 lets user see the results from the file
		else if (choice == "3")
		{
			//open the file to see results
			ifstream infile;
			infile.open(filename);
			//check if file opened successfully
			if (!infile.is_open())
			{
				cout << "File could not open successfully.";
				exit(3);
			}
			//loop until the end of file is reached
			while (!infile.eof())
			{
				//get a character from the file
				infile.get(ch);
				//print character on the console
				cout << ch;
			}
			//close file
			infile.close();
			exit(4);
		}
		//this is the menu of options that is seen to users repeatedly
		else if (choice == "0")
		{
			cout << "You can choose from the 4 options below:" << endl;
			cout << "1) Enter the parameters needed to calculate the pressure drop" << endl;
			cout << "2) Calculate pressure drop" << endl;
			cout << "3) Print program results" << endl;
			cout << "4) exit program" << endl;
			cout << "You may exit the program anytime" << endl;
			cin >> choice;
			//if user inputs a choice other than 0, 1, 2, 3 and 4, it gives the option menu again.
			if (choice!="0" && choice!="1"&& choice!= "2"&& choice!="3"&&choice!="4")
				choice = "0";
		}
		//if user chooses 4, print message of exiting program and terminate the program/
		if (choice == "4")
		{
			cout << "You have exited this program!";
			exit(5);
		}

	}
	//loop the whole code as long as the user chooses to end the program
	while (choice !="4");

 return 0;
}