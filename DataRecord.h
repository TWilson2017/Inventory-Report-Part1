#ifndef DATARECORD_H
#define DATARECORD_H
#include <vector>

class AccessData
{
	public:
	    //Open File & Read In Data
	    void Read();
		
	    //Insert The Data Into The Linked List In Order
		void Insert(unsigned int, string, int, int, int, float, int, int);
		
		//Print The Data In The Linked List
		void Print();
		
		//Convert Today's Date & The Item Purchase Date Into Age Years
		int ConvertAge(int, int, int);
		
		//Convert Date Into Its Abbreviation
		string Date(int);
		
		//Search Vector For Duplicate Item Numbers
		int LinearSearch(vector<int>, int);
		
		//Get Today's Date
		void GetDate();
		
		//Check Dates In File For Being Out Of Bounds
		bool CheckDate(int Month, int Day, int Year);
		
		//Destructor for Linked List
		~AccessData()
		{
			Node *ptr;
            for (ptr = Head; Head; ptr = Head)
            {
                Head = Head->next;
                delete ptr;
            }//for
		}//Destructor
    private:
		struct Node
		{
			unsigned int Item_Number; //Item Number
			string Item_Category;    //Item Category
			int Item_Purchase_DateM;  //Purchase Date (MMDDYY) - Month
			int Item_Purchase_DateD;  //Purchase Date (MMDDYY) - Day
			int Item_Purchase_DateY;  //Purchase Date (MMDDYY) - Year
			float Item_Cost;          //Item Cost
			int Item_Count;           //Item Count
			int Item_Sold;            //Item Sold
			Node *next;               //Node Pointer
			Node(){}                  //First Constructor
			Node(unsigned int Item_Number1, string Item_Category1, int Item_Purchase_DateM1,
			     int Item_Purchase_DateD1, int Item_Purchase_DateY1, float Item_Cost1, 
			     int Item_Count1, int Item_Sold1, Node *next1 = NULL)
			{
				Item_Number = Item_Number1;
				Item_Category = Item_Category1;
				Item_Purchase_DateM = Item_Purchase_DateM1;
				Item_Purchase_DateD = Item_Purchase_DateD1;
				Item_Purchase_DateY = Item_Purchase_DateY1;
				Item_Cost = Item_Cost1;
				Item_Count = Item_Count1;
				Item_Sold = Item_Sold1;
				next = next1;
			}//Second Constructor
		};//struct Node
		Node *Head = NULL;            //Node Head Pointer
		float TotalRevenue;
};
#endif