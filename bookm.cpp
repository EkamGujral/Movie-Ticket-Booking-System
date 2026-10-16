#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<iomanip>
#include<limits>
using namespace std;

int lastBookedMovieID = -1; 
int readInt(const char* prompt) {
    int x;
    cout << prompt;
    while (!(cin >> x)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Please enter a number: ";
    }
    return x;
}

class Movie {
    public:
    int movieId;
    char name [50];
    char showTime [20];
    char cast[100];
    char language[20];
    float rating;
    char releaseDate[20];
    char director[20];
    int seats[10][10];
    int seatsbooked;
    static const int totalseats=100;
  

Movie(){
    seatsbooked = 0;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            seats[i][j] = 0; // all seats empty
}
  
//Setting Movie Details   
 void setMovie(int id, const char* n, const char* lang, const char* rDate, const char* c, const char* d, float rt, const char* sTime) {
        movieId = id;
        strcpy(name, n);
        strcpy(language, lang);
        strcpy(releaseDate, rDate);
        strcpy(cast, c);
        strcpy(director, d);
        rating = rt;
        strcpy(showTime, sTime);
    }  
    

//Display Movie
      void displayMovie() {
        cout << "\nMovie ID: " << movieId << endl;
        cout << "Name: " << name << endl;
        cout << "Language: " << language << endl;
        cout << "Release Date: " << releaseDate << endl;
        cout << "Cast: " << cast << endl;
        cout << "Director: " << director << endl;
        cout << "Rating: " << rating << endl;
        cout << "Show Time: " << showTime << endl;
        cout << "Seats Booked: " << seatsbooked << endl;
        cout << "Seats Available: " << totalseats - seatsbooked << endl;
    }

//Display Seat Layout
    void showSeatLayout() {
    cout << "=========================================\n";
    cout << " SEAT LAYOUT for " << name << " (" << showTime << ")\n";
    cout << "=========================================\n";
    cout << "\nSeat Layout for " << name << " (" << showTime << ")\n";
    cout << "O = Available, X = Booked\n";
    cout << "\n  ";
    for (int j = 0; j < 10; j++)
        cout << " " << left << setw(3) << j + 1;   
    cout << "\n  ---------------------------------------\n";
    for (int i = 0; i < 10; i++) {
        char row = 'A' + i;   // Row letters A–J
        cout << row << " ";
        for (int j = 0; j < 10; j++) {
            if (seats[i][j] == 0)
                cout << "[O] ";    // available
            else
                cout << "[X] ";    // booked
        }
        cout << endl;
    }
}

//Booking Tickets
void bookTicket() {
    int n;
    cout << "\nBooking for " << name << " at " << showTime << endl;
    showSeatLayout();
    n = readInt("Enter number of tickets to book: ");

    if (n <= 0) {
        cout << "Invalid number of tickets!" << endl;
        return;
    }  

    if (seatsbooked + n > totalseats) {
        cout << "Not enough seats available!\n";
        system("pause");
        return;
    }

//Seat Selection
    int bookedRow[100], bookedCol[100];
    for (int t = 0; t < n; t++) {
        char row;
        int col;
        while (true) {
            cout << "\nSelect seat " << t + 1 << " (e.g. A5): ";
            cin >> row >> col;
            int r = toupper(row) - 'A';
            int c = col - 1;

            if (r < 0 || r >= 10 || c < 0 || c >= 10) {
                cout << "Invalid seat! Try again.\n";
                continue;
            }

            if (seats[r][c] == 1) {
                cout << "Seat already booked! Choose another.\n";
                continue;
            }

            seats[r][c] = 1;
            seatsbooked++;
            cout << "Seat " << row << col << " booked successfully!\n";
            showSeatLayout();
            break;

            bookedRow[t] = r;
            bookedCol[t] = c;
        }
    }

    cout << "\nAll tickets booked successfully! Total seats booked: " << seatsbooked << endl;
    lastBookedMovieID = movieId;

    // Automatically process payment after booking
    if (!payment(n)) {
        for (int i = 0; i < n; i++) {
        seats[bookedRow[i]][bookedCol[i]] = 0;
        }
        seatsbooked -= n;
        cout << "\nPayment failed. Your booking has been cancelled.\n";
        system("pause");
}

}

//Canceling Tickets
void cancelTicket() {
        int n;
        cout << "\nCancelling for " << name << " at " << showTime << endl;
        n = readInt("Enter number of tickets to cancel: ");

        if (n <= 0|| n> seatsbooked) {
            cout << "Invalid number of tickets!" << endl;
        return ;
        }
       
    for (int t = 0; t < n; t++) {
        char row;
        int col;
        cout << "Enter seat to cancel (e.g. A5): ";
        cin >> row >> col;
        int r = toupper(row) - 'A';
        int c = col - 1;

        if (r < 0 || r >= 10 || c < 0 || c >= 10) {
            cout << "Invalid seat!\n";
            t--;
            continue;
        }
        if (seats[r][c] == 0) {
            cout << "Seat already empty!\n";
            t--;
            continue;
        }

        seats[r][c] = 0;
        seatsbooked--;
        cout << "Seat " << row << col << " cancelled!\n";
    }

    cout << "\nUpdated Layout:\n";
    showSeatLayout();
}

 bool payment(int ticketsInThisBooking) {
    if (ticketsInThisBooking == 0) {
        cout << "\nNo tickets booked yet for this movie!\n";
        return false;
    }      
    int pricePerTicket = 200;
    int totalAmount = ticketsInThisBooking * pricePerTicket;
    int choice;

    cout << "\n========== PAYMENT SECTION ==========\n";
    cout << "Movie Name     : " << name << endl;
    cout << "Show Time      : " << showTime << endl;
    cout << "Seats Booked   : " << ticketsInThisBooking << endl;
    cout << "Price per Seat :RS " << pricePerTicket << endl;
    cout << "--------------------------------------\n";
    cout << "Total Amount   : RS " << totalAmount << endl;
    cout << "--------------------------------------\n";

    cout << "\nChoose Payment Method:\n";
    cout << "1. Net Banking\n";
    cout << "2. Credit / Debit Card\n";
    cout << "3. UPI Payment\n";
    choice = readInt("Enter your choice: ");

    switch (choice) {
        case 1:
            cout << "\nProcessing payment via Net Banking...\n";
            break;
        case 2:
            cout << "\nProcessing payment via Credit/Debit Card...\n";
            break;
        case 3:
            cout << "\nProcessing payment via UPI...\n";
            break;
         default:
            cout << "\nInvalid payment option! Try again.\n";
            return false;
    }

    cout << "\nPayment Successful! \n";
    cout << "--------------------------------------\n";
    cout << "Total Paid: RS " << totalAmount << endl;
    cout << "Thank you for booking! Enjoy your movie \n";
    cout << "======================================\n";
    system("pause");
    return true;
}


};

void setDetails();
void showallMovies();
void cancelTicket();


Movie screens[4][4];

//Movie Details
void setDetails(){
    screens[0][0].setMovie(101, "Avengers: Endgame", "English", "26-04-2019", "Robert Downey Jr., Chris Evans, Mark Ruffalo, Chris Hemsworth", "Anthony & Joe Russo", 8.4, "10:00 AM");
    screens[0][1].setMovie(102, "Dunki", "Hindi", "21-12-2023", "Shah Rukh Khan, Taapsee Pannu, Anil Grover, Vicky Kaushal", "Rajkumar Hirani", 8.2, "01:00 PM");
    screens[0][2].setMovie(103, "Chal Mera Putt 3", "Punjabi", "14-07-2023", "Amrinder Gill, Simi Chahal, Nasir Chinyoti, Akram Udas", "Janmejot Singh", 7.5, "04:00 PM");
    screens[0][3].setMovie(104, "Interstellar", "English", "07-11-2014", "Matthew McConaughey, Anne Hathaway, Jessica Chastian, Matt Damon", "Christopher Nolan", 8.6, "07:00 PM");

    screens[1][0].setMovie(201, "Titanic", "English", "19-12-1997", "Leonardo DiCaprio, Kate Winslet, Billy Zane", "James Cameron", 7.8, "10:00 AM");
    screens[1][1].setMovie(202, "Pathaan", "Hindi", "25-01-2023", "Shah Rukh Khan, Deepika Padukone, Salman Khan", "Siddharth Anand", 8.5, "01:00 PM");
    screens[1][2].setMovie(203, "Honsla Rakh", "Punjabi", "15-09-2021", "Diljit Dosanjh, Sonam Bajwa, Shinda Grewal, Shehnaz Gill", "Dheeraj Rattan", 7.9, "04:00 PM");
    screens[1][3].setMovie(204, "Guardians of Galaxy", "English", "01-08-2014", "Chris Pratt, Zoe Saldana, James Gunn", "James Gunn", 8.0, "07:00 PM");

    screens[2][0].setMovie(301, "Spider-Man: No Way Home", "English", "17-12-2021", "Tom Holland, Zendaya, Andrew Garfield", "Jon Watts", 8.5, "10:00 AM");
    screens[2][1].setMovie(302, "Bholaa", "Hindi", "30-03-2023", "Ajay Devgn, Tabu, Abhishek Bachan", "Sanjeev Kumar", 7.6, "01:00 PM");
    screens[2][2].setMovie(303, "Ardab Mutiyaran", "Punjabi", "24-02-2022", "Sonam Bajwa, Ninja, Ajay Sarkaria", "Manav Shah", 7.4, "04:00 PM");
    screens[2][3].setMovie(304, "Thor: Ragnarok", "English", "03-11-2017", "Chris Hemsworth, Cate Blanchett, Jeff Goldblum", "Taika Waititi", 7.9, "07:00 PM");

    screens[3][0].setMovie(401, "The Matrix Resurrections", "English", "22-12-2021", "Keanu Reeves, Jessica Henwick, Hugo Weaving", "Lana Wachowski", 7.3, "10:00 AM");
    screens[3][1].setMovie(402, "Jawan", "Hindi", "07-09-2023", "Shah Rukh Khan, Nayanthara, Atlee Kumar", "Atlee", 8.7, "01:00 PM");
    screens[3][2].setMovie(403, "Punjabi Aa Gaye Oye", "Punjabi", "22-08-2025", "Twinkle Arora, Singga, Kanwaljit Singh", "Aditya Sood", 8, "04:00 PM");
    screens[3][3].setMovie(404, "The Batman", "English", "04-03-2022", "Robert Pattinson, Zoe Kravitz, Paul Dano", "Matt Reeves", 7.8, "07:00 PM");

}
//Save all movies and seats to file
void saveMovies() {
    ofstream out("screens.dat", ios::binary);
    if (!out) {
        cout << "Could not save data!\n";
        return;
    }
    out.write((char*)screens, sizeof(screens));
}

//Load all movies and seats from file
void loadMovies() {
    setDetails();   // default data first

    ifstream in("screens.dat", ios::binary);
    if (!in) return;   // no saved file yet, keep defaults

    static Movie temp[4][4];
    in.read((char*)temp, sizeof(temp));
    if (in.gcount() == (streamsize)sizeof(temp)) {
        memcpy(screens, temp, sizeof(screens));   // only use it if fully read
    }
}

// Display all movies with available seats
void showallMovies() {
    cout<<"\n ======== MOVIE LIST========\n";
    for(int s=0;s<4;s++){
        cout << "\nScreen " << s+1 << ":\n";
        for(int m=0;m<4;m++){
            screens[s][m].displayMovie();
            cout<<"-------------------------------\n";
      }
    }
    system("pause");
}


//File Handling   
fstream f1;

//Add Record
void addRecord(){
    f1.open("movie.dat", ios::out | ios::app | ios::binary); 
    if(!f1){
        cout << "Error opening file!\n";
        return;
    }

    Movie m1;
    int id;
    char name[50], language[20], releaseDate[20], cast[100], director[20], showTime[20];
    float rating;
    
    cout << "Enter Movie ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(name, 50);
    cout << "Enter Language: ";
    cin.getline(language, 20);
    cout << "Enter Release Date: ";
    cin.getline(releaseDate, 20);
    cout << "Enter Cast: ";
    cin.getline(cast, 100);
    cout << "Enter Director: ";
    cin.getline(director, 20);
    cout << "Enter Rating: ";
    cin >> rating;
    cin.ignore();
    cout << "Enter Show Time: ";
    cin.getline(showTime, 20);
    
    m1.setMovie(id, name, language, releaseDate, cast, director, rating, showTime);
    f1.write((char*)&m1, sizeof(Movie)); // write object to file
    f1.close();

    cout << "\nMOVIE ADDED!\n";
    system("pause");
}

//Display Record
void displayRecords(){
    f1.open("movie.dat", ios::in | ios::binary); 
    if(!f1){
        cout << "\nFile not found!\n";
        return;
    }

    Movie m1;
    while(f1.read((char*)&m1, sizeof(Movie))){
        m1.displayMovie();
        cout << "------------------\n";
    }
    f1.close();
}

//Update Record
void updateRecord(){
      int id,found=0;
       cout<<"\nEnter Movie ID to update: ";
       cin>>id;

    f1.open("movie.dat", ios::in | ios::out | ios::binary);
    if(!f1){
        cout << "\nFile not found!\n";
        system("pause");
        return;
    }
   
    Movie m1;
    while(f1.read((char*)&m1,sizeof(m1))){
        if (m1.movieId == id){
            found=1;
            cout<<"\nOld Record:";
            m1.displayMovie();
            cout<<"\nEnter New Details:\n";
            char name[50], language[20], releaseDate[20], cast[100], director[20], showTime[20];
            float rating;
            
            cout << "Enter Name: ";
            cin.ignore();
            cin.getline(name, 50);
            cout << "Enter Language: ";
            cin.getline(language, 20);
            cout << "Enter Release Date: ";
            cin.getline(releaseDate, 20);
            cout << "Enter Cast: ";
            cin.getline(cast, 100);
            cout << "Enter Director: ";
            cin.getline(director, 20);
            cout << "Enter Rating: ";
            cin >> rating;
            cout << "Enter Show Time: ";
            cin.ignore();
            cin.getline(showTime, 20);
 
            m1.setMovie(id, name, language, releaseDate, cast, director, rating, showTime);
            streampos pos = f1.tellg();
            f1.seekp(pos - (streampos)sizeof(m1));
            f1.write((char*)&m1, sizeof(m1));
            cout<<"\n---- Record updated!----\n";
            break;
        }
      }   
  f1.close();
  if(!found)
  cout<<"\n--Movie not Found!--\n";
     
  system("pause");
}

void cancelTicket() {
    cout << "\n========= SCREEN & MOVIE LIST =========\n";
    for (int s = 0; s < 4; s++) {
        cout << "\nScreen " << s + 1 << ":\n";
        for (int m = 0; m < 4; m++) {
            cout << m + 1 << ". " 
                 << screens[s][m].name       
                 << " (" << screens[s][m].showTime << ")\n";  
        }
    }

    int screenNum, movieNum;
    cout << "\nEnter Screen number (1-4): ";
    cin >> screenNum;
    cout << "Enter Movie number (1-4): ";
    cin >> movieNum;

    if (screenNum < 1 || screenNum > 4 || movieNum < 1 || movieNum > 4) {
        cout << "\nInvalid selection!\n";
        system("pause");
        return;
    }

// Call cancelTicket() of the selected movie object
    screens[screenNum - 1][movieNum - 1].cancelTicket();

    system("pause");
}

//Main Function
 int main() {
    loadMovies();
    
    int ch;
    do {
        system("cls");
        cout << "============================================\n";
        cout << "***** MOVIE TICKET BOOKING SYSTEM *****\n";
        cout << "============================================\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. Show Availability\n";
        cout << "4. Exit\n";
        ch = readInt("Enter your choice: ");

        switch(ch) {
            case 1: {
                // Display screens and movies
                cout << "\n========= SCREEN & MOVIE LIST =========\n";
                for (int s = 0; s < 4; s++) {
                    cout << "\nScreen " << s + 1 << ":\n";
                    for (int m = 0; m < 4; m++) {
                        cout << m + 1 << ". " << screens[s][m].name;
                        cout << " (" << screens[s][m].showTime << ")\n";
                    }
                }

                int screenNum, movieNum;
                screenNum = readInt("\nEnter Screen number (1-4): ");
                movieNum = readInt("Enter Movie number (1-4): ");

                if (screenNum < 1 || screenNum > 4 || movieNum < 1 || movieNum > 4) {
                    cout << "\nInvalid selection!\n";
                    system("pause");
                    break;
                }

                screens[screenNum - 1][movieNum - 1].bookTicket();
                saveMovies();
                break;
            }

            case 2: 
                cancelTicket();
                saveMovies();
                break;

            case 3:
                showallMovies();
                break;

            case 4: 
                saveMovies();
                cout << "\n.... Exiting....\n";
                break;

            default: 
                cout << "\n---- Invalid choice!----\n"; 
                system("pause");
        }
    } while(ch != 4);

    return 0;
}
