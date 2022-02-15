/* Hello! This is Kaitlyn's Machine Project for CCPROG1.
   It works as a simple cash register.*/
   
#include <stdio.h>
#include <windows.h> // Change color of text, size of screen, clear screen
#include <conio.h>  // Used for getch()

// Command to clear screen.
void clrscr(){
    system("@cls||clear");
}

// Change size of console window.
void size(){
    SMALL_RECT windowSize = {0 , 0 , 70 , 30}; //change the values
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
}

// The following functions were copied from this URL: https://stackoverflow.com/questions/52877110/using-the-gotoxy-function-to-center-x-coordinate
// Using this so I can easily center align text.
void set_cursor_position(int x, int y){
   COORD coord = { x, y };
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD get_console_dimensions(void){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    COORD dimensions = { csbi.srWindow.Right - csbi.srWindow.Left,
                         csbi.srWindow.Bottom - csbi.srWindow.Top };
    return dimensions;
}

COORD get_console_cursor_pos(void){
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition;
}

void gotoxy(short x, short y){
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// This function is used to specifically to center align text.
void puts_centered(char const *str){
    size_t length = strlen(str);
    short x = (short)(get_console_dimensions().X - length) / 2;
    gotoxy(x, get_console_cursor_pos().Y);
    puts(str);
}

// This function is used when I ask the user to press any key. It gets input and then clears screen.
void pressKey(){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	printf("\n\n\n");
	puts_centered("Press any key to continue!");
	SetConsoleTextAttribute(hConsole, 15);
	getch();
	clrscr();
}

// This function displays the text when a user is prompted to exit the program. They have the option to either return to main menu or exit the program entirely.
void endPrompt(){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	clrscr();
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	SetConsoleTextAttribute(hConsole, 14);
    puts_centered("Do you want to leave the program or continue shopping?");
    printf("\n\n");
    puts_centered("Press 'B' to end program, ");
    puts_centered("or press 'M' to return to main menu.\n");
    SetConsoleTextAttribute(hConsole, 15);
}

// This function computes for the total quantities of each item and total spend. Only items that were purchased succesfully through check out will display here.
void generateReport(int qPotato, int qApple, int qOrange, int qBanana, int qPopcorn, int qBottled, int qCola){
    int num = 1, input;
    float total = 0;
    HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
    printf("\n\n         [Daily Report]\n\n");
    SetConsoleTextAttribute(hConsole, 15);
    if(qPotato >= 1){
        printf("Potato         50.00 x %d = %d.00\n", qPotato, qPotato*50);
        total = total + (qPotato*50);
    }
    if(qApple >= 1){
        printf("Apple          35.00 x %d = %d.00\n", qApple, qApple*35);
        total = total + (qApple*35);
    }
    if(qOrange >= 1){
        printf("Orange         40.00 x %d = %d.00\n", qOrange, qOrange*40);
        total = total + (qOrange*40);
    }
    if(qBanana >= 1){
        printf("Banana         25.00 x %d = %d.00\n", qBanana, qBanana*25);
        total = total + (qBanana*25);
    }
    if(qPopcorn >= 1){
        printf("Popcorn       120.00 x %d = %d.00\n", qPopcorn, qPopcorn*120);
        total = total + (qPopcorn*120);
    }
    if(qBottled >= 1){
        printf("Bottled Water  20.00 x %d = %d.00\n", qBottled, qBottled*20);
        total = total + (qBottled*20);
    }
    if(qCola >= 1){
        printf("Cola           45.00 x %d = %d.00\n", qCola, qCola*45);
        total = total + (qCola*45);
    }
    printf("---------------------------------\n");
    printf("TOTAL              P %.2f ", total);
    printf("\n\n[1] Return to the main menu\n");
    scanf("%d", &input);
    
    while (num != 0){
        if(input == 1){
            clrscr();
            num = 0;
        }
        else{
            scanf("%d", &input);
        }
    }
}

// This function displays all items and the quantities added from Purchase Items. If the user is to repurchase an item, the quantity is overwritten. Only the most recent quantity from Purchase Items is displayed. Total for the current cart is also shown. The text menu for New Transaction is also found here.
void currentCart(int cartPotato, int cartApple, int cartOrange, int cartBanana, int cartPopcorn, int cartBottled, int cartCola){
    float currentTotal = (cartPotato*50)+(cartApple*35)+(cartOrange*40)+(cartBanana*25)+(cartPopcorn*120)+(cartBottled*20)+(cartCola*45);
 
    clrscr();
    printf("\n\n   [Current Cart]\n\n");
    printf("Potato         50.00 x %d\n", cartPotato);
    printf("Apple          35.00 x %d\n", cartApple);
    printf("Orange         40.00 x %d\n", cartOrange);
    printf("Banana         25.00 x %d\n", cartBanana);
    printf("Popcorn       120.00 x %d\n", cartPopcorn);
    printf("Bottled Water  20.00 x %d\n", cartBottled);
    printf("Cola           45.00 x %d\n", cartCola);
    printf("_________________________\n");
    printf("TOTAL            P %.2f", currentTotal);

    printf("\n\n\n\n[1] Purchase Items\n");
    printf("[2] Check Out\n");
    printf("[3] Cancel Transaction\n");
    printf("[4] Clear Current Cart\n\n");
    printf("Enter input: ");
}

// This function is shown when user inputs 1 from the Menu. It first displays a table with all items and their prices. The user is then asked whether they would like to Purchase Item (1), Check Out (2), or Cancel Transaction (3).
void newTransaction(int *qPotato, int *qApple, int *qOrange, int *qBanana, int *qPopcorn, int *qBottled, int *qCola, int *total){
    int  input, item, num = 1, num2 = 1, num3 = 1;
    int cartPotato = 0, cartApple = 0, cartOrange = 0, cartBanana = 0, cartPopcorn = 0, cartBottled = 0, cartCola = 0;
    float amount = 0, currentTotal = 0, change = 0;
    char ch;
    HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("\n\n\n\n\n\n\n\n");
    puts_centered("  -Here's the item list!-");
    printf("\n");
    SetConsoleTextAttribute(hConsole, 14);
    puts_centered("   [Item] ----------[Price]");
    SetConsoleTextAttribute(hConsole, 15);
    printf("\n");
    puts_centered("Potato ----------  P50");
    puts_centered(" Apple ----------  P35");
    puts_centered("Orange ----------  P40");
    puts_centered("Banana ----------  P25");
    puts_centered("Potato ----------  P50");
    puts_centered("Bottled Water ----------  P20       ");
    puts_centered("  Cola ----------  P45");
	pressKey();
	
    while(num != 0){
        currentCart(cartPotato, cartApple, cartOrange, cartBanana, cartPopcorn, cartBottled, cartCola);
        scanf("%d", &input);
        
        if (input > 4 || input < 1){
        	SetConsoleTextAttribute(hConsole, 12);
        	printf("\nEnter a valid number: \n");
        	SetConsoleTextAttribute(hConsole, 15);
        	scanf("%d", &input);
        }
        clrscr();
// Purchase Items: List items and their corresponding number linked to it. User inputs number and quantity of item. Once succesful, inputs are added to the Current Cart.
        if(input == 1){
            clrscr();
            printf("\n\n[1] Potato\n");
            printf("[2] Apple\n");
            printf("[3] Orange\n");
            printf("[4] Banana\n");
            printf("[5] Popcorn\n");
            printf("[6] Bottled Water\n");
            printf("[7] Cola\n");
            printf("[8] Cancel\n");
            printf("\nPurchase which item? ");
            scanf("%d", &item);
          
            switch(item){
                case 1:
                    printf("Buying Potato!\n\n");
                    printf("Enter quantity? ");
                    scanf("%d", &cartPotato);
                    printf("%d Potatoes purchased!", cartPotato);
                    pressKey();
                    break;
                case 2:
                    printf("Buying Apple!\n\n");
                    printf("Enter quantity? ");
                    scanf("%d", &cartApple);
                    printf("%d Apples purchased!", cartApple);
                    pressKey();
                    break;
                case 3:
                    printf("Buying Orange!\n\n");
                    printf("Enter quantity? ");
                    scanf("%d", &cartOrange);
                    printf("%d Oranges purchased!", cartOrange);
                    pressKey();
                    break;
                case 4:
                    printf("Buying Banana!\n\n");
                    printf("Enter quantity? ");
                    scanf("%d", &cartBanana);
                    printf("%d Bananas purchased!", cartBanana);
                	pressKey();
                    break;
                case 5:
                    printf("Buying Popcorn!\n\n");
                    printf("Enter quantity? ");
                    scanf("%d", &cartPopcorn);
                    printf("%d Popcorns purchased!", cartPopcorn);
                    pressKey();
                    break;
                case 6:
                    printf("Buying Bottled Water!\n\n");
                    printf("Enter quantity? ");
                    scanf("%d", &cartBottled);
                    printf("%d Bottled waters purchased!", cartBottled);
                    pressKey();
                    break;
                case 7:
                    printf("Buying Cola!\n\n");
                    printf("Enter quantity? ");
                    scanf("%d", &cartCola);
                    printf("%d Colas purchased!", cartCola);
                    pressKey();
                    break;
                case 8:
                    printf("\nCancel order.\n");
                    pressKey();
                    break;
                default:
                    printf("\nEnter a valid number: \n");
            }
   		 }
   		 
// Check Out: Once the user is satisfied with the items and quantities they want to purchase, check out screen is where they may pay for the items. All successful payments are then updated on the Daily Report screen.
        if(input == 2){ 
        currentTotal = (cartPotato*50)+(cartApple*35)+(cartOrange*40)+(cartBanana*25)+(cartPopcorn*120)+(cartBottled*20)+(cartCola*45);
            clrscr();
            if(currentTotal <= 0){
        		clrscr();
        		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
            	puts_centered("You have nothing in your cart :(");
				puts_centered("Add something to your cart before checking out!");
            	pressKey();
        	}
            if (currentTotal > 0){
                printf("\n\n           [Check Out]\n\n");
                if(cartPotato >= 1){
                    printf("Potato        50.00 x %d = %d.00\n", cartPotato, cartPotato*50);
                }
                if(cartApple >= 1){
                    printf("Apple         35.00 x %d = %d.00\n", cartApple, cartApple*35);
                }
                if(cartOrange >= 1){
                    printf("Orange        40.00 x %d = %d.00\n", cartOrange, cartOrange*40);
                }
                if(cartBanana >= 1){
                    printf("Banana        25.00 x %d = %d.00\n", cartBanana, cartBanana*25);
                }
                if(cartPopcorn >= 1){
                    printf("Popcorn      120.00 x %d = %d.00\n", cartPopcorn, cartPopcorn*120);
                }
                if(cartBottled >= 1){
                    printf("Bottled Water 20.00 x %d = %d.00\n", cartBottled, cartBottled*20);
                }
                if(cartCola >= 1){
                    printf("Cola          45.00 x %d = %d.00\n", cartCola, cartCola*45);
                }
                printf("\n----------------------------------");
                printf("\nTOTAL                 P %.2f", currentTotal);
                printf("\n\nEnter amount: ");
                scanf("%f", &amount);
                
      			while(amount < currentTotal){
                    printf("Please enter a valid amount: ");
                    scanf("%f", &amount);
                }
                clrscr();
                SetConsoleTextAttribute(hConsole, 14);
                printf("\n\n     [Official Receipt]\n\n");
                SetConsoleTextAttribute(hConsole, 15);
                
                if(cartPotato >= 1){
                    printf("Potato        50.00 x %d = %d.00\n", cartPotato, cartPotato*50);
                }
                if(cartApple >= 1){
                    printf("Apple         35.00 x %d = %d.00\n", cartApple, cartApple*35);
                }
                if(cartOrange >= 1){
                    printf("Orange        40.00 x %d = %d.00\n", cartOrange, cartOrange*40);
                }
                if(cartBanana >= 1){
                    printf("Banana        25.00 x %d = %d.00\n", cartBanana, cartBanana*25);
                }
                if(cartPopcorn >= 1){
                    printf("Popcorn      120.00 x %d = %d.00\n", cartPopcorn, cartPopcorn*120);
                }
                if(cartBottled >= 1){
                    printf("Bottled Water 20.00 x %d = %d.00\n", cartBottled, cartBottled*20);
                }
                if(cartCola >= 1){
                    printf("Cola          45.00 x %d = %d.00\n", cartCola, cartCola*45);
                }
                
                printf("---------------------------------\n\n");
                printf("TOTAL                P  %.2f\n\n", currentTotal);
                printf("CASH TENDERED        P  %.2f\n\n", amount);
                change = amount - currentTotal;
                printf("CHANGE               P  %.2f\n\n", change);
                printf("Salamat Shopee! Come again! :)");
                pressKey();
                *qPotato = *qPotato + cartPotato;
                *qApple = *qApple + cartApple;
                *qOrange = *qOrange + cartOrange;
                *qBanana = *qBanana + cartBanana;
                *qPopcorn = *qPopcorn + cartPopcorn;
                *qBottled = *qBottled +cartBottled;
                *total = *total + currentTotal;
                clrscr();
                num = 0;
            
   			}
		}

// Cancel Transaction: Prompt user to disregard progress in cart bringing them back to the Menu.
        if(input == 3){
        	clrscr();
        	printf("\n\n\n\n\n\n\n\n");
        	SetConsoleTextAttribute(hConsole, 14);
            puts_centered("Are you sure you want to cancel transaction?\n");
            puts_centered("Enter 'Y' for yes, else 'N' to retain items.\n");
            SetConsoleTextAttribute(hConsole, 15);
            printf("\n\nEnter input: ");
            scanf("%c", &ch);
            
            while(num3 != 0){
                scanf("%c", &ch);
                if(ch == 'Y'){
                    num3 = 0;
                    num = 0;
                }
                else if(ch == 'N'){
                    num3 = 0;
                    num = 1;
                }
                if(ch != 'Y' || ch != 'N'){
                }
            }
            num3 = 1;
   		}
        
// Clear Current Cart: This is where the user can opt to disregard all progress in their Current Cart without having to head back to Menu.
// Originally a mistake I made for cancel transaction. Decided to keep it as an additional optipn since it does work.
        if (input == 4){
        	printf("\n\n\n\n\n\n\n\n\n\n\n");
        	SetConsoleTextAttribute(hConsole, 14);
            puts_centered("Are you sure you want to clear your current cart?\n");
            puts_centered("Enter 'Y' for yes, else 'N' to retain items.\n");
            SetConsoleTextAttribute(hConsole, 15);
            printf("Enter input: ");
            scanf("%c", &ch);
            
            while (num2 != 0){
                scanf("%c", &ch);
                if (ch == 'Y'){
                        cartPotato = 0;
                        cartApple = 0;
                        cartOrange = 0;
                        cartBanana = 0;
                        cartPopcorn = 0;
                        cartBottled = 0;
                        currentTotal = 0;
                        clrscr();
                        num2 = 0;
           		}
           		else if(ch == 'N'){
           			num2 = 0;
				   }
                else if(ch != 'Y' || ch != 'N'){
                    printf("Enter a valid input: ");
                }
            }
            num2 = 1;
        }
	}	
}

// This function displays text for the Menu.
void printMenu(){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  	printf("\n\n\n\n\n\n\n\n\n");
  	SetConsoleTextAttribute(hConsole, 14);
  	puts_centered("Welcome to Shopee!");
  	SetConsoleTextAttribute(hConsole, 15);
  	puts_centered("How may I help you?");
  	SetConsoleTextAttribute(hConsole, 10);
  	printf("\n\n");
  	SetConsoleTextAttribute(hConsole, 13);
  	puts_centered("[1] New Transaction");
  	printf("\n");
  	SetConsoleTextAttribute(hConsole, 11);
  	puts_centered("[2] Generate Report");
  	printf("\n");
  	SetConsoleTextAttribute(hConsole, 10);
  	puts_centered("[3] Leave shop     ");
  	printf("\n\n\n");
   	SetConsoleTextAttribute(hConsole, 15);
	printf("Enter input to begin: ");
}

// Main function that directs to the different parts of the menu and that has all the variables that are then used as pointers in Generate Report.
int main() {
    int input = 0, num1 = 1, num = 1, total = 0;
    int qPotato = 0, qApple = 0, qOrange = 0, qBanana = 0, qPopcorn = 0, qBottled = 0, qCola = 0;
    char ch;
    
 	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    size();
    
    while(num1 != 0){
    	clrscr();
        printMenu();
        scanf("%d", &input);
        if(input == 1){
            clrscr();
            newTransaction(&qPotato, &qApple, &qOrange, &qBanana, &qPopcorn, &qBottled, &qCola, &total);
        }
        else if(input == 2){
            clrscr();
            generateReport(qPotato, qApple, qOrange, qBanana, qPopcorn, qBottled, qCola);
        }
        else if(input > 3 || input < 1){
        	SetConsoleTextAttribute(hConsole, 12);
            puts_centered("Enter a valid input: ");
            SetConsoleTextAttribute(hConsole, 15);
        }
        else if(input == 3){
            endPrompt();
            while(num != 0){
            	scanf("%c", &ch);
	            if (ch == 'M'){
	            	num = 0;
	       		}
	        	else if(ch == 'B'){
	            	num = 0;
		        	num1 = 0;
		    	}
        	}
        }
        num = 1;
    }
    return 0;
}

