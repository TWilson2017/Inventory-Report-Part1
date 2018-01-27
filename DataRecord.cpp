//Count In Leap Year
//MAKE SETW SMALLER !!!!!
#include <iostream>
using namespace std;
#include "DataRecord.h"
#include <fstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

void AccessData:: Read()
{
   //Declare variables
	ifstream inF;                   
	unsigned int Item_Number1;
    string Item_Category1;
	int Item_Purchase_DateM1, Item_Purchase_DateD1, Item_Purchase_DateY1, Item_Count1, Item_Sold1;
	float Item_Cost1;
	vector <int> InputNumbers;
	TotalRevenue = 0.0; 
	
	//Open File
	inF.open("Data.txt");
	
	//Test File For Error
	if(inF.fail())
	{
		   cout << endl << "FATAL ERROR: UNABLE TO OPEN FILE \"Data.txt\". TERMINATING..."
                << endl << endl;
           exit (1);
	}
	else
	{
		while(inF >> Item_Number1 >> Item_Category1 >> Item_Purchase_DateM1 
			      >> Item_Purchase_DateD1 >> Item_Purchase_DateY1 >> Item_Cost1 
			      >> Item_Count1 >> Item_Sold1)
		{
			//---------------------------------------
			//If Error Are Encountered, Skip The Line
			//---------------------------------------
			//Check If Date Is Beyond Today's Date
			if(CheckDate(Item_Purchase_DateM1, Item_Purchase_DateD1, Item_Purchase_DateY1) == false)
				continue;
			
			//Check Month For Out Of Range
			if(Item_Purchase_DateM1 < 1 || Item_Purchase_DateM1 > 12 || Item_Purchase_DateM1 == 0)
				continue;
			
			//Check Day For Out Of Range
			if(Item_Purchase_DateD1 < 1 || Item_Purchase_DateD1 > 31 || Item_Purchase_DateD1 == 0)
				continue;
			
		    //Check if Year Is Negative
		    if(Item_Purchase_DateY1 < 0 || Item_Purchase_DateY1 == 0)
				continue;
			
			//Check Item Cost For Negative Numbers
			if(Item_Cost1 < 0.0)
				continue;
			
			//Check Item Count For Negative Numbers
			if(Item_Count1 < 0)
				continue;
			
			//Check Item Sold For Negative Numbers
			if(Item_Sold1 < 0)
				continue;
						
			//Input Numbers Into Vector To Make Sure No Duplicates Get Inserted Into The List
			InputNumbers.push_back(Item_Number1);
				
			//Check To Make Sure There Is No Duplicate Item_Number
			if(LinearSearch(InputNumbers, Item_Number1) > 1)
				continue;
			
			else
			{
				//If The Data Passes The Test, Send It To The Linked List
				Insert(Item_Number1, Item_Category1, Item_Purchase_DateM1, 
					   Item_Purchase_DateD1, Item_Purchase_DateY1, Item_Cost1,
			           Item_Count1, Item_Sold1);
				TotalRevenue += (Item_Sold1 * Item_Cost1);
			}//else
		}//while
	}//else
	            //Close The Input File
			    inF.close();
}//Read
	

void AccessData:: Insert(unsigned int Item_Number2, string Item_Category2, int Item_Purchase_DateM2, 
						  int Item_Purchase_DateD2, int Item_Purchase_DateY2, float Item_Cost2,
			              int Item_Count2, int Item_Sold2) 
{
	Node *temp = NULL;
	temp = new Node(Item_Number2, Item_Category2, Item_Purchase_DateM2, Item_Purchase_DateD2, Item_Purchase_DateY2, 
					Item_Cost2, Item_Count2, Item_Sold2, temp);
	
	/*Check To See If Head Is Null || Check To See If Head's Value Is Greater Than Current Value, 
	If So, Insert Value At Head*/
	if(Head == NULL || Head->Item_Number > Item_Number2)
	{
		temp->next = Head;
		Head = temp;
	}//if
	
	//Check To See If The Next Item In The List Is Greater Than The Current Value, 
	//If So, Insert Value Before Greater Number
	else if(Head->next != NULL && Head->next->Item_Number >= Item_Number2)
	{
		Node *tempNext = new Node;
		tempNext = Head->next;
		temp->next = tempNext;
		Head->next = temp;
	}//elseif
	
	//Check To See If The Next Item In The List Is Less Than The Current Value, 
	//If So, Insert Value After Lesser Number
	else
	{
		Node *current = new Node;
		current = Head;
		while(current ->next != NULL && current->next->Item_Number <= Item_Number2)
		{
			current = current -> next;
		}//while
		temp->next = current->next;
		current->next = temp;
	}//else 
}//Insert

void AccessData:: Print()
{
	//Print Out The Contents For The Inventory Report
	cout << fixed << setw(70) << "Inventory Report" << endl;
	cout << fixed << setw(100) << "Date: ";
	GetDate(); 
	cout << endl << endl << endl << endl;
	cout << fixed << setw(0) << "Item" << setw(24) << "Item Purchase" << setw(14) << "Item"
		 << setw (18) << "Item" << setw(18) << "Item" << setw(15) << "Item" << endl;
	cout << fixed << setw(0) << "Number" << setw(17) << "Date" << setw(19) << "Cost"
		 << setw (18) << "Sold" << setw(17) << "Age" << setw(18) << "Revenue" << endl;
	
	//Print Out The Contents In The Linked List As A Inventory Report
	Node *temp = new Node;
	temp = Head;
	while(temp != NULL)
	{
		cout << setfill('0') << setw(4) << temp->Item_Number;
	    cout << setfill(' ') << setw(16) << Date(temp->Item_Purchase_DateM) << temp->Item_Purchase_DateD 
			 << setw(0) << ",\t" << temp->Item_Purchase_DateY;
		cout << setw(10) << "$ " << setprecision(2) << temp->Item_Cost;
		cout << setw(16) << temp->Item_Sold; 
		cout << setw(17) << ConvertAge(temp->Item_Purchase_DateM, temp->Item_Purchase_DateD, temp->Item_Purchase_DateY);
		cout << setw(14) << "$ " << setprecision(2) << (temp->Item_Cost * temp->Item_Sold) << endl;
		temp = temp->next;
	}//while
	
	//Print Out Total Revenue
	cout<< endl << setw(65) << "Total Revenue" << '\t' << setw(19) << "$ " << setprecision(2) << TotalRevenue;
}//Print
int AccessData:: ConvertAge(int Month1, int Day1, int Year1)
{
	int Date1[] = {Month1, Day1, Year1};
	
	//Get current time and date
	time_t t = time(0);
	tm* ltm = localtime(&t);
	int Year2 = 1900 + ltm->tm_year;
	int Month2 = 1 + ltm->tm_mon;
	int Day2 = ltm->tm_mday;
	int Date2[] = {Month2, Day2, Year2};
	
	//Subtract Date From Given Date
    tm a = {0,0,0,Day1,Month1,Year1};
	tm b = {0,0,0,Day2,Month2,Year2};
	time_t x = mktime(&a);
	time_t y = mktime(&b);
	
	if(x != (time_t)(-1) && y != (time_t)(-1))
	{
       double difference = difftime(y,x)/(60*60*24);
		    int rounding = (int)round(difference);
			int year = rounding/365;
			int days = rounding%365;
			int months = days/30;
		
			if(year >= 1 && months >= 6 && days >= 183)
				return (year+1);
		    else if(year >= 1 && months <= 5 && days <= 182)
				return (year);
		    else
				return 0;
	}//if
}//ConvertAge
	
//Function to convert the Month number into its abbreviation 
string AccessData:: Date(int Month)
{
   const string DateAbbr[12] = {"Jan. ", "Feb. ", "Mar. ", "Apr. ", 
		                  "May ", "Jun. ", "Jul. ", "Aug. ", 
						  "Sep. ", "Oct. ", "Nov. ", "Dec. "};
   switch(Month)
   {
	   case 1: return DateAbbr[0];
		       break;
	   case 2: return DateAbbr[1];
		       break;
	   case 3: return DateAbbr[2];
		       break;
	   case 4: return DateAbbr[3];
			   break;
	   case 5: return DateAbbr[4];
		       break;
	   case 6: return DateAbbr[5];
			   break;
	   case 7: return DateAbbr[6];
			   break;
	   case 8: return DateAbbr[7];
			   break;
	   case 9: return DateAbbr[8];
		       break;
	   case 10: return DateAbbr[9];
			   break;
	   case 11: return DateAbbr[10];
				break;
	   case 12: return DateAbbr[11];
				break;
	   default: return ("Wrong Month Inserted....");
		        break;
   }//Switch
}//Date

//Search Vector For Duplicate Item Numbers
int AccessData:: LinearSearch(vector<int> ItemHolder, int ItemNumber)
{
	int ItemCounter = 0;
	for(int i = 0; i < ItemHolder.size(); i++)
	{
		if(ItemHolder.at(i) == ItemNumber)
			ItemCounter++;
	}//for
	
	return ItemCounter;
}//LinearSearch

void AccessData:: GetDate()
{
	time_t t = time(0);
	tm* ltm = localtime(&t);
	cout << Date(ltm->tm_mon + 1) 
		 <<  ltm->tm_mday  << ", "
		 << (ltm->tm_year + 1900);
}//GetDate

bool AccessData:: CheckDate(int Month, int Day, int Year)
{
	time_t t = time(0);
	tm* ltm = localtime(&t);
	//Return False If Today's Year Is Less Than or Equal To File's Year
	if((ltm->tm_year + 1900) < Year)
		return false;
	//Return False If Today's Month Is Less Than or Equal To File's Month, Today's Day Is Less Than File's Day, and 
	//Today's Year Is Less Than or Equal To File's Year (e.g - Today: 1/23/2018 ----> File's Date: 1/24/2018)
	else if((ltm->tm_mon + 1) <= Month && (ltm->tm_mday) < Day && (ltm->tm_year + 1900) <= Year)
		return false;
	//Return False If Today's Month Is Less Than File's Month, Today's Day Is Less Than File's Day, and 
	//Today's Year Is Less Than or Equal To File's Year (e.g - Today: 1/23/2018 ----> File's Date: 2/27/2018)
	else if((ltm->tm_mon + 1) < Month && (ltm->tm_mday) < Day && (ltm->tm_year + 1900) <= Year)
		return false;
	//Return False If Today's Month Is Less Than File's Month, Today's Day Is Less Than or Equal To File's Day, and 
	//Today's Year Is Less Than or Equal To File's Year (e.g - Today: 1/23/2018 ----> File's Date: 2/23/2018)
	else if((ltm->tm_mon + 1) < Month && (ltm->tm_mday) <= Day && (ltm->tm_year + 1900) <= Year)
		return false;
	else 
		return true;
}//CheckDate