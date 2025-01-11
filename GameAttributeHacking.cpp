#include <iostream> 
#include <fstream> 
#include "hacking_functions.h"
using namespace std;

int main()
{
    //initialize variables
    int newValue=0;
    int choice1=-1, choice2=0, choice3=0, choice4=0;
    char ch;
    long address;



 //open the file and read addresses
 ifstream infile;
 infile.open("gameinfo.txt");
 if (infile.fail())
    exit(1);
 int PID;
 infile>>PID;
 int max=0;
 infile>>hex>>max;

 //attach game to program
 attachToProcess(PID);

 //make the 2D dynamic array to store data values
 bool **array;
 array=new bool *[3];
 for (int i=0; i<3; i++)
 {
    array[i]=new bool [max];
 }

 //declare and assign address of the 3 attributes
 long money;
 infile>>hex>>money;
 long health;
 infile>>hex>>health;
 long energy;
 infile>>hex>>energy; 

 for(int i=0; i<3; i++) //read boolean values form game and stores to the array
  {
    long address=0;
    if (i==0)
        address=money;
    else if (i==1)
        address=health;
    else if (i==2)
        address=energy;
    for (int j=0; j<max; j++)
        {
            array[i][j]=readValue(PID, address+j);//iterate to read and store each bool
        }
  }


    //read and assign UI address to variable
    long UIaddress=0;
    infile>>hex>>UIaddress;
    //close file
    infile.close();

    cout<<"Hello user!"<<endl;
do{
    if (choice1==2)
        exit(2);

    if (choice1==-1)
    {
        //menu for hacking options
        cout<<"Please enter your desire hacking mode:"<<endl;
        cout<<"[0] UI Hacking"<<endl;
        cout<<"[1] Data Hacking"<<endl;
        cout<<"[2] Exit"<<endl;
        cin>>choice1;
    }
    if (choice1==0)
    {
        //display the UI character
        cout<<"Here is the current character: "<<readUIChar(PID, UIaddress)<<endl;
        cout<<"Enter a new character to display"<<endl;
        cin>>ch;
        writeUIChar(PID, UIaddress, ch);//change UI character based on user input
        cout<<"Display character has been changed successfully! Enter the second option to EXIT and implement changes in the game.";
        choice1=-1;
    }
    if (choice1==1) 
    {
            do 
            {
                //display menu for changing statistics of attributes
                cout<<"Choose the attribute you want to change"<<endl;
                cout<<"[0] Money"<<endl;
                cout<<"[1] Health"<<endl;
                cout<<"[2] Energy"<<endl;
                cin>>choice2;

                //count the number of 1s for the attribute chosen thorugh this loop
                int ctr=0;
                for (int j=0; j<max; j++)
                {
                    if (array[choice2][j]==1)
                        ctr++;
                }
                cout<<"The current data for your attribute is: "<<ctr<<endl;
                cout<<"Enter the new value for the attribute between 0 and "<<max<<endl;
                cin>>newValue;
                //check if input is within bounds
                while (newValue>max)
                {
                    cout<<"please enter a number within the given range of 0 and "<<max<<endl;
                    cin>>newValue;
                }

                //change the boolean values in array based on input
                for (int i=0; i<newValue; i++)
                {
                    array[choice2][i]=1;
                    //assign 1 to elements with indexes from 0 to newValue-1
                }
                for (int j=newValue; j<max; j++)
                {
                    //assign 0 to the rest of the elemets
                    array[choice2][j]=0;
                }
                //assign address to use later on for modifying values in the game
                if (choice2==0)
                        address=money;
                if (choice2==1)
                        address=health;
                if (choice2==2)
                        address=energy;

                //modify values in the game based on changes made in array
                
                for (int j=0; j<max; j++)
                        {
                            modifyValue(PID, address+j, array[choice2][j]);
                            //iterate across the row and modify values
                        }
                cout<<"Do you want to modify another attribute?"<<endl;
                cout<<"[0] No, hack the game"<<endl;
                cout<<"[1] yes, I want to change some other attribute before hacking"<<endl;
                cin>>choice3;

                //exit to implement changes in the game
                if (choice3==0)
                    exit(3);    

            } while(choice3==1);    
    } 
 } while (choice1!=2);




//deallocate 2D array
for (int i=0; i<3; i++)
{
    delete [] array [i];
}
delete []array;

//detach game from program
detachProcess(PID);

return 0;
}