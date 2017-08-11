// TeamProject.cpp : Defines the entry point for the console application.
//

/*This is the Learning Team D Theater Seating Program for week 5 of the PRG 410 course at University of Phoenix. This program will allow the user to purchase and reserve
seats in the theater. In addition, it allows the user to review seating and sales history from the introducty menu option by selecting 1 or they may press 0 and ENTER to
continue on to ticket purchase and seat selection.*/

#include "stdafx.h"
using namespace std;
#include <iostream>
#include <fstream>
#include<string>
#include <vector>
#include <sstream>

// global variables for number of rows and seats
int const rows = 10, seats = 9;


// function declarations
void show_display(int[rows][seats]);
void init_hold_array(int[rows][seats]);
void show_cart(int[rows][seats], int, int);

int main()
{
	// calls file for use by the program
	ofstream outfile;
	ifstream infile;

	// load in text file
	infile.open("theater.txt");
	string line;

	// imports the data
	vector<vector<int> > import;
	while (getline(infile, line))
	{
		import.push_back(vector<int>());
		istringstream ss(line);
		int value;
		while (ss >> value)
		{
			import.back().push_back(value);
		}
	}

	for (int rows = 0; rows < import.size(); rows++)
	{
		for (int seats = 0; seats < import[rows].size(); seats++);

	}

	infile.close();
	// end of importing data

	// variable declarations
	char purchase, confirm, view_cart;
	int seat_chart[rows][seats], ticket_hold[rows][seats], row_num, seat_num, total_seats, seat_count, counter = 0,
		ticket_cost = 11, seats_purchased = 0;
	bool end_purchase = false, invalid_choice = true, seat_availability = true;

	// welcome title screen designed to look like curtains on a theater screen
	cout << "******************************************************************************\n";
	cout << "******************************************************************************\n";
	cout << "*************************************  ***************************************\n";
	cout << "************************************    **************************************\n";
	cout << "***********************************      *************************************\n";
	cout << "********************************            **********************************\n";
	cout << "******************************                ********************************\n";
	cout << "****************************                    ******************************\n";
	cout << "*************************                          ***************************\n";
	cout << "**********************                                ************************\n";
	cout << "*******************                                       ********************\n";
	cout << "*****************                                            *****************\n";
	cout << "***************                                                ***************\n";
	cout << "************                                                      ************\n";
	cout << "**********                                                          **********\n";
	cout << "********                                                              ********\n";
	cout << "*****OO                             Fun                                OO*****\n";
	cout << "*OOOO                              Times                                 OOOO*\n";
	cout << "OOOO                              Theaters                                OOOO\n";
	cout << "****                           Seating Program                            ****\n";
	cout << "******                                                                  ******\n";
	cout << "******                                                                  ******\n";





	//the following is to copy the imported data into each needed array <- start of matt
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			seat_chart[i][j] = import[i][j];
		}
	}


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			ticket_hold[i][j] = import[i][j];
		}
	}

	// end of matt


	init_hold_array(ticket_hold);
	// show_display(seat_chart);

	
	cout << "\nWelcome to Fun Times Theater! Please select one of the following menu options.\n"; // presents a welcome message and instructions for menu selection

	// purchase loop
	while (!end_purchase){

		// initialize variables
		int seatchart = 2;
		seat_count = 0;

		// seating chart loop tests initial value of seatchart
		// keeps looping with invalid choices
		while (invalid_choice || seatchart < 0 || seatchart > 1){

			// get user input
			cout << "\nPress 0 and hit ENTER to reserve seats and purchase tickets.\n";
			cout << "\nPress 1 and hit ENTER to view the seating chart and sales history.\nEnter selection: ";
			cin >> seatchart;

			// test for non numeric input
			invalid_choice = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		// initialize number
		int number = 0;

		// provides user option to view the seating chart and sales history or move on to ticket purchase. 
		if (seatchart > 0){
			show_display(seat_chart);
			int y = 0;

			// for loop to display the number of seats total (available and taken) and seats available per row
			for (int i = 0; i<10; i++)
			{
				int seats_available = 0;
				for (int j = 0; j < 9; j++)
				{
					if (seat_chart[i][j] == 0){
						y++;
						number = y;
						seats_available++;
					}
				}

				// displays the number of seats per row
				cout << "\nThere are " << seats_available << " seats available in row " << i + 1 << ".";
			}
			cout << "\n\nThere are currently " << number << " seats available for purchase.\n";
			cout << "\nThere are currently " << (rows * seats) - number << " seats sold in this theater.\n";
			seatchart = 0;
		}

		// row number loop
		do {
			// gets user input
			cout << "\n\nThere are 10 total rows available.\n";
			cout << "\nPlease enter the row where you wish to reserve seats(1 - 10) : "; // selects seating row
			cin >> row_num;

			// tests for non numeric input
			invalid_choice = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// tests to see if row is in range of the number of rows available
			if (row_num < 1 || row_num > 10){
					cout << "\nPlease enter a valid number (1 - 10)\n";
					invalid_choice = true;
				}
				else
					invalid_choice = false;
			
		} while (invalid_choice); // end row number

		// seat selection loop
		do {
			// get user input
			cout << "\nThere are 9 seats in each row.\n";
			cout << "\nPlease enter the starting seat number that you wish to reserve(1 - 9) : "; // selects seat number
			cin >> seat_num;

			// test for non numeric values
			invalid_choice = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// test if the seat number is in the range of the number of seats
			if (seat_num < 1 || seat_num > 9){
				cout << "\nPlease enter a valid number (1 - 9)\n";
				invalid_choice = true;
			}
			else
				invalid_choice = false;
		} while (invalid_choice); // end seat number

		// number of seats to reserve loop
		do {
			// get user input
			cout << "\nPlease enter total number of seats you wish to reserve (1 - 9): "; // selects number of seats to purchase
			cin >> total_seats;

			// test for valid input (non numeric)
			invalid_choice = cin.fail();
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// tests to see if the seat values are in range for valid number of seats
			if (total_seats < 1 || total_seats > 9 || (total_seats + seat_num - 1) > 9){
				cout << "\nPlease enter a valid number (1 - 9).  Only 9 seats are available per row.\n";
				invalid_choice = true;
			}
			else
				invalid_choice = false;

			// counts the seats available in the row
			for (int index = (seat_num - 1); index < seats; index++){
				if (seat_chart[row_num - 1][index] == 0)
					seat_count++;
			}

		} while (invalid_choice); // end seat number

		// checks to see if tickets are available
		if (seat_count >= total_seats){
			cout << "\nTickets available.\n";
			invalid_choice = false;

			// confirms the user would like to add seats to the cart
			cout << "\nWould you like to add this to your cart? (Y or y to conirm): ";
			cin >> confirm;

			// loop to add seats to the cart and the seating chart arrays
			if (confirm == 'Y' || confirm == 'y'){
				cout << "\nAdded to cart!";
				for (int index = (seat_num - 1); index <= (seats); index++){
					if (seat_chart[row_num - 1][index] == 0 && counter < total_seats){
						seat_chart[row_num - 1][index] = 1;
						ticket_hold[row_num - 1][index] = 1;						
						counter++;
					}
					
				}

				// loop to display the tickets added to the cart
				cout << "\nThe following seats have been added:\n\n";
				for (int row_index = 0; row_index < 10; row_index++){
					for (int seat_index = 0; seat_index < 9; seat_index++){
						if (ticket_hold[row_index][seat_index] == 1){
							cout << "Row: " << row_index + 1 << " Seat: " << seat_index + 1 << endl;
						}
					}
				}

				// displays the total purchase price for the tickets
				seats_purchased = seats_purchased + total_seats;
				cout << "\nTotal for ticket purchases: $" << seats_purchased * ticket_cost << endl << endl;
				show_display(seat_chart);
			}
		}
		else{
			cout << "\n\nI am sorry.  The ticket selection is not available.  Please try again.\n\n";
			invalid_choice = true;
		}

		// inputs  for another purchase 
		cout << "\n\nWould you like to select other seats?\n";
		cout << "\nPress Y for Yes or hit any key and ENTER to checkout : ";
		cin >> purchase;

		// if the user selects to continue, the program will loop again.  otherwise, the program continues to the if statement
		if (purchase == 'Y' || purchase == 'y')
			end_purchase = false;
		else {
			end_purchase = true;

			// tests to see if tickets are in the cart and allows the user to checkout
			if (counter > 0){
				cout << "\nWould you like to view your cart?\n";
				cout << "\nPress Y to view cart or N and ENTER to exit the program : ";
				cin >> view_cart;

				if (view_cart == 'Y' || view_cart == 'y'){
					show_cart(ticket_hold, seats_purchased, ticket_cost);
					end_purchase = true;
				}
			}
		}


	}// end purchase loop


	// get_data(seat_chart);
	// show_display(seat_chart);

	// export array
	outfile.open("theater.txt");

	for (int count = 0; count < rows; count++)
	{
		for (int index = 0; index < seats; index++)
			outfile << seat_chart[count][index] << " ";

		outfile << endl;        //New line for each row
	}

	outfile.close();
	// end exporting  



	return 0;
}// end main 

// loop to initialize the current purchase array to 0
void init_hold_array(int hold[rows][seats]){
	for (int index_row = 0; index_row < rows; index_row++){
		for (int index_seat = 0; index_seat < seats; index_seat++){
			hold[index_row][index_seat] = 0;
		}
	}

} // end init array function

// displays the output using a nested for loop to display rows and seats
void show_display(int seat_chart[rows][seats]){
	
	// header for display
	cout << "\n# - available seat\n* - sold seat\n";
	cout << "\nRows\t\tSeats\n\t";
	
	// sets the seat numbers along the top
	for (int seat_count = 1; seat_count <= seats; seat_count++){
		cout << " " << seat_count;
	}

	// sets the * and # depending on the value of the specific seat
	for (int row_index = 0; row_index < rows; row_index++){
		cout << endl << row_index + 1 << "\t";
		for (int seat_index = 0; seat_index < seats; seat_index++){
			if (seat_chart[row_index][seat_index] == 0)
				cout << " #";
			else
				cout << " *";
		}
	}
	cout << endl;
} // end display function

// cart function
void show_cart(int ticket_hold[rows][seats], int seats_purchased, int cost){ // this contains the ticket purchase cart and payment 

	//variable declaration
	char payMethod;
	int  cvcNum = 0, zipCode = 0;
	double cardNum = 0;
	const double cardMatchLow = 999999999999999, cardMatchHigh = 10000000000000000;
	const int cvcMatchLow = 99, cvcMatchHigh = 1000, zipLow = 9999, zipHigh = 100000;
	bool invalid_pay = true;

	// prompt for user input
	cout << "\nYour total for the tickets is $" << cost * seats_purchased;
	cout << "\nWe take Debt or Credit Cards. Press (Y or y) to checkout now :";
	cin >> payMethod;

	// while loop to test valid input information
	while (invalid_pay) {
		if (payMethod == 'Y' || payMethod == 'y') {

			// catches inputs less or greater to 16 digits and non negative integers
			while (cardNum < cardMatchLow || cardNum > cardMatchHigh || invalid_pay) {
				cout << "Enter your card number: (16 digit number): ";
				cin >> cardNum;

				// checks for state of invalid entry
				invalid_pay = cin.fail();
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			// catches inputs less or greater to 3 digits and non negative integers
			while (cvcNum < 99 || cvcNum > 1000 || invalid_pay) {

				cout << "Enter CVC code (three digit number): ";
				cin >> cvcNum;

				// checks for state of invalid entry
				invalid_pay = cin.fail();
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

			}

			// catches inputs less or greater to 5 digits and non negative integers
			while (zipCode < zipLow || zipCode > zipHigh || invalid_pay){
				cout << "Enter billing zip code (5 digit number): ";
				cin >> zipCode;

				// checks for state of invalid entry
				invalid_pay = cin.fail();
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

			// successful pay information message
			cout << "Thank you for your purchase!  Enjoy the movie!";
			invalid_pay = false;
		}
		else
			invalid_pay = true;
	}

	// end message and system pause
	cout << "\nPlease visit us again soon!";
	system("pause");
} // end pay function
