# 🎬 Movie Ticket Booking System (C++)

A console-based movie ticket booking system written in C++. Users can browse movies across multiple screens, pick specific seats from a visual seat map, pay (simulated), cancel tickets, and have all bookings saved between sessions.

---

## ✨ Features

- **4 screens × 4 shows** – 16 pre-loaded movies (English, Hindi and Punjabi titles)
- **Interactive seat map** – 10×10 grid (rows A–J, columns 1–10) showing `[O]` available and `[X]` booked seats
- **Multi-ticket booking** – choose the number of tickets and select each seat individually (e.g. `A5`)
- **Payment simulation** – Net Banking, Credit/Debit Card or UPI at ₹200 per ticket
- **Automatic rollback** – booking is cancelled if payment fails
- **Ticket cancellation** – free any previously booked seats
- **Availability dashboard** – movie details, seats booked and seats available for every show
- **Persistent storage** – seat data is saved to `screens.dat` and reloaded on the next run
- **Input validation** – protects against non-numeric menu input and out-of-range seats

---

## 🗂️ Project Structure

```
.
├── main.cpp        # Complete source code
├── screens.dat     # Auto-generated binary save file (created on first booking)
└── README.md
```

### Key components

| Component | Description |
|-----------|-------------|
| `class Movie` | Holds movie details, the 10×10 seat matrix, booking, cancellation and payment logic |
| `Movie screens[4][4]` | Global array of all screens and their shows |
| `setDetails()` | Loads the default movie list |
| `saveMovies()` / `loadMovies()` | Binary file persistence for seat state |
| `showallMovies()` | Displays all movies with seat availability |
| `readInt()` | Safe integer input helper |

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler with C++11 support or later (g++, MinGW, MSVC)
- **Windows** is recommended – the program uses `system("cls")` and `system("pause")`

### Compile and run

```bash
g++ main.cpp -o movie_booking
./movie_booking        # on Windows: movie_booking.exe
```

> **Linux / macOS users:** replace `system("cls")` with `system("clear")` and replace `system("pause")` with a `cin.get()` based pause, otherwise those commands will fail.

---

## 🖥️ Usage

```
============================================
***** MOVIE TICKET BOOKING SYSTEM *****
============================================
1. Book Ticket
2. Cancel Ticket
3. Show Availability
4. Exit
```

1. **Book Ticket** – choose a screen and a movie, enter the number of tickets, pick seats such as `A5`, then choose a payment method.
2. **Cancel Ticket** – choose the screen and movie, enter how many tickets to cancel and the seat for each one.
3. **Show Availability** – lists every movie with its seats booked and available.
4. **Exit** – saves all data and closes the program.

### Seat map example

```
    1   2   3   4   5   6   7   8   9   10
  ---------------------------------------
A [O] [O] [X] [O] [O] [O] [O] [O] [O] [O]
B [O] [O] [O] [O] [O] [O] [O] [O] [O] [O]
...
```

---

## 🎞️ Included Movies

| Screen | 10:00 AM | 01:00 PM | 04:00 PM | 07:00 PM |
|--------|----------|----------|----------|----------|
| 1 | Avengers: Endgame | Dunki | Chal Mera Putt 3 | Interstellar |
| 2 | Titanic | Pathaan | Honsla Rakh | Guardians of the Galaxy |
| 3 | Spider-Man: No Way Home | Bholaa | Ardab Mutiyaran | Thor: Ragnarok |
| 4 | The Matrix Resurrections | Jawan | Punjabi Aa Gaye Oye | The Batman |

---

## ⚠️ Known Limitations

- Payment is simulated – no real transaction is performed
- Ticket price is fixed at ₹200 for all seats and shows
- No user accounts, booking IDs or booking history
- Save file is a raw binary dump, so it is not portable across compilers/platforms or after changing the `Movie` class
- Admin functions (`addRecord`, `updateRecord`, `displayRecords`) exist in the code but are not yet connected to the menu

---

## 🔮 Future Improvements

- [ ] Replace `char[]` buffers with `std::string`
- [ ] Add booking IDs and a booking history
- [ ] Add an admin menu for adding/updating movies
- [ ] Dynamic pricing (premium rows, weekend rates)
- [ ] Cross-platform console handling
- [ ] Human-readable save format (JSON/CSV)
- [ ] Split code into header/source files

---

## 🧠 Concepts Demonstrated

- Object-oriented programming (classes, encapsulation, member functions)
- 2D arrays and arrays of objects
- Binary file handling with `fstream`
- Input validation and error handling
- Menu-driven console applications

---