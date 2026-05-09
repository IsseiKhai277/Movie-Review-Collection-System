#include <iostream> 
#include <string> 
#include <conio.h>
#include <mysql.h> //libmysql 
#include <iomanip> //for setprecision
#include <chrono>
#include <thread>
#include "User.h"
#include <limits>
#include <regex>// for birthday date
#include <set>
#include<map> //for addtofav bar
#include <functional>
#include <tabulate/table.hpp>

using namespace tabulate;

int userId = 0;

int main() {
    system("cls");
    system("title My Project");
    db_response::ConnectionFunction();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    system("cls");

    int menu;


    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    while (true) {
        SetConsoleTextAttribute(h, 1);
        std::cout << "  W       W    EEEEEEEE   LL          CCCCCC     OOOOOOO   MM       MM   EEEEEEEE" << endl;
        SetConsoleTextAttribute(h, 2);
        std::cout << "  W       W    E          LL         CC         OO     OO  MMM     MMM   E" << endl;
        SetConsoleTextAttribute(h, 3);
        std::cout << "  W       W    E          LL        CC          OO     OO  MMMM   MMMM   E" << endl;
        SetConsoleTextAttribute(h, 4);
        std::cout << "  W   W   W    EEEEE      LL        C           OO     OO  MM MM MM MM   EEEEE" << endl;
        std::cout << "  W  W W  W    E          LL        CC          OO     OO  MM  MMM  MM   E" << endl;
        SetConsoleTextAttribute(h, 5);
        std::cout << "  W W   W W    E          LL         CC         OO     OO  MM   M   MM   E" << endl;
        SetConsoleTextAttribute(h, 6);
        std::cout << "  WW     WW    EEEEEEEE   LLLLLLLL     CCCCCC    OOOOOOO   MM       MM   EEEEEEEE" << endl;
        SetConsoleTextAttribute(h, 13);
        std::cout << endl;
        SetConsoleTextAttribute(h, 7);
        std::cout << "---------------------------------------------------------------------------------------\n";
        std::cout << endl;
        SetConsoleTextAttribute(h, 16);
        std::cout << "                           MOVIE REVIEW COLLECTION SYSTEM                                ";
        SetConsoleTextAttribute(h, 7);
        std::cout << endl;
        std::cout << endl;
        std::cout << "---------------------------------------------------------------------------------------\n";
        std::cout << endl;


        std::cout << "1. Login" << endl;
        std::cout << "2. Register" << endl;
        std::cout << "3. Exit" << endl;
        std::cout << "Choose: ";
        cin >> menu;

        if (std::cin.fail()) {
            clearInputBuffer(); // Use custom function to clear buffer
            std::cout << "Invalid input. Please enter a number between 1 and 3." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            system("cls");
            continue;
        }

        switch (menu)
        {
        case 1:
            Login();
            break;
        case 2:
            Register();
            break;
        case 3:
            cout << "Program Exiting..." << endl;
            exit(0);
        default:
            cout << "Please choose between 1 - 3. Press Enter To Continue...";
            (void)_getch(); //get char - pause console 
            system("cls");
            main();
            break;
        }
    }

    return 0;
}

void clearInputBuffer() {
    std::cin.clear(); // Clear error state
    while (std::cin.get() != '\n'); // Discard all characters until newline
}

 
//REGISTRATION 


void Register() {
    system("cls");
    string name, phone, birthday, username, password, confirmPassword, usertype, invitationCode;
    const string reviewerCode = "REVIEWER2023";
    const string directorCode = "DIRECTOR2023";

    cout << "--- User Registration ---" << endl;

    while (true) {
        cout << "Enter Name: ";
        cin.ignore(1, '\n');
        getline(cin, name);

        bool isValidName = true;
        for (char c : name) {
            if (isdigit(c)) {
                isValidName = false;
                break;
            }
        }

        if (isValidName) {
            break;
        }
        else {
            cout << "Invalid name. Please enter a name without numbers.\n";
        }
    }

    while (true) {
        cout << "Enter Phone (numbers only): ";
        getline(cin, phone);

        bool isNumeric = true;
        for (char c : phone) {
            if (!isdigit(c)) {
                isNumeric = false;
                break;
            }
        }

        if (isNumeric) {
            break;
        }
        else {
            cout << "Invalid phone number. Please enter numbers only.\n";
        }
    }

    while (true) {
        cout << "Enter Birthday (YYYY-MM-DD): ";
        getline(cin, birthday);

        regex datePattern("^\\d{4}-\\d{2}-\\d{2}$");
        if (regex_match(birthday, datePattern)) {
            int year, month, day;

            // Use sscanf_s for safe parsing
            if (sscanf_s(birthday.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
                cout << "Invalid date format. Please use YYYY-MM-DD.\n";
                continue;
            }

            time_t t = time(nullptr);
            tm currentTime{};

            // Use localtime_s for thread-safe local time
            if (localtime_s(&currentTime, &t) != 0) {
                cout << "Error retrieving current time. Please try again later.\n";
                return;
            }

            int currentYear = currentTime.tm_year + 1900;

            if (year >= currentYear || year < (currentYear - 120)) {
                cout << "Invalid year. Please enter a realistic year of birth.\n";
                continue;
            }

            // Validate month and day ranges
            if (month < 1 || month > 12) {
                cout << "Invalid month. Please enter a month between 01 and 12.\n";
                continue;
            }

            if (day < 1 || day > 31) {
                cout << "Invalid day. Please enter a day between 01 and 31.\n";
                continue;
            }

            // Handle months with fewer than 31 days
            if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
                cout << "Invalid day. This month only has 30 days.\n";
                continue;
            }

            // Handle February (leap year check)
            bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            if (month == 2 && ((isLeapYear && day > 29) || (!isLeapYear && day > 28))) {
                cout << "Invalid day. February only has 28 days (29 in leap years).\n";
                continue;
            }

            int age = currentYear - year;
            if (age < 10) {
                cout << "Invalid age. You must be at least 10 years old to register.\n";
                continue;
            }

            break;
        }
        else {
            cout << "Invalid date format. Please use YYYY-MM-DD.\n";
        }
    }

    cout << "Enter Username: ";
    getline(cin, username);

    while (true) {
        cout << "Select User Type:\n";
        cout << "1. Director (requires invitation code)\n";
        cout << "2. Reviewer (requires invitation code)\n";
        cout << "3. Guest\n";
        cout << "Enter your choice (1/2/3): ";
        string choice;
        getline(cin, choice);

        if (choice == "1") {
            usertype = "Director";
            cout << "Enter Invitation Code: ";
            getline(cin, invitationCode);
            if (invitationCode == directorCode) {
                break;
            }
            else {
                cout << "Invalid invitation code for Director. Please try again.\n";
            }
        }
        else if (choice == "2") {
            usertype = "Reviewer";
            cout << "Enter Invitation Code: ";
            getline(cin, invitationCode);
            if (invitationCode == reviewerCode) {
                break;
            }
            else {
                cout << "Invalid invitation code for Reviewer. Please try again.\n";
            }
        }
        else if (choice == "3") {
            usertype = "Guest";
            break;
        }
        else {
            cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }

    while (true) {
        password.clear();
        confirmPassword.clear();

        cout << "Enter Password (Minimum 8 characters): ";
        char ch;
        while ((ch = _getch()) != 13) {
            if (ch == '\b') {
                if (!password.empty()) {
                    password.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                password += ch;
                cout << '*';
            }
        }
        cout << endl;

        if (password.length() < 8) {
            cout << "Password must be at least 8 characters long. Please try again.\n";
            continue;
        }

        cout << "Re-enter Password: ";
        while ((ch = _getch()) != 13) {
            if (ch == '\b') {
                if (!confirmPassword.empty()) {
                    confirmPassword.pop_back();
                    cout << "\b \b";
                }
            }
            else {
                confirmPassword += ch;
                cout << '*';
            }
        }
        cout << endl;

        if (password == confirmPassword) {
            break;
        }
        else {
            cout << "The passwords do not match. Please try again.\n";
        }
    }

    string checkUser_query = "SELECT * FROM user WHERE username = '" + username + "'";
    const char* cu = checkUser_query.c_str();
    qstate = mysql_query(conn, cu);

    if (!qstate) {
        res = mysql_store_result(conn);
        if (res->row_count == 1) {
            cout << "Username already exists. Press Enter to Try Again...";
            (void)_getch();
            Register();
        }
        else {
            string insertCustomer_query =
                "INSERT INTO user (name, contact_no, birthday, username, password, usertype) "
                "VALUES ('" + name + "', '" + phone + "', '" + birthday + "', '" + username +
                "', SHA2('" + password + "', 256), '" + usertype + "')";
            const char* q = insertCustomer_query.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate) {
                cout << endl << "You have been registered. Press Enter to Continue...";
                (void)_getch();
                main();
            }
            else {
                cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
            }
        }
    }
    else {
        cout << "Query Execution Problem! " << mysql_errno(conn) << endl;
    }
}





//LOGIN 
void Login() {
    system("cls");
    std::string username, password;

    std::cout << "--- Login Page ---" << std::endl;
    std::cout << "Username : ";
    std::cin >> username;

    std::cout << "Password : ";
    char ch;
    while (true) {
        ch = _getch(); // Read a single character without displaying it on the screen

        if (ch == 13) { // Enter key
            break;
        }
        else if (ch == 8) { // Backspace key
            if (!password.empty()) {
                password.pop_back(); // Remove the last character from the password
                std::cout << "\b \b"; // Move cursor back, print a space to erase '*', and move back again
            }
        }
        else if (isalnum(ch) || ispunct(ch)) { // Allow only alphanumeric and punctuation characters
            password += ch;
            std::cout << '*'; // Display asterisk for the entered character
        }
    }
    std::cout << std::endl;

    // Query to check username and password
    std::string query = "SELECT user_id, usertype FROM user WHERE username = '" + username +
        "' AND password = SHA2('" + password + "', 256)";

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Failed to execute query: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (res == nullptr) {
        std::cerr << "Failed to store result: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_num_rows(res) == 1) {
        // Login successful
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row) {
            userId = std::stoi(row[0]); // Set global userId
            std::string userType = row[1];

            std::cout << "Login successful! User ID: " << userId << std::endl;
            (void)_getch();

            // Redirect based on user type
            if (userType == "Admin") {
                AdminMenu();
            }
            else if (userType == "Director") {
                DirectorMenu();
            }
            else if (userType == "Reviewer") {
                ReviewerMenu();
            }
            else if (userType == "Guest") {
                GuestMenu();
            }
            else {
                std::cerr << "Invalid user type found in the database." << std::endl;
            }
        }
    }
    else {
        // Login failed
        std::cout << "\nInvalid username or password.\n";

        char choice;
        do {
            std::cout << "\nWhat would you like to do?\n";
            std::cout << "1. Retry Login\n";
            std::cout << "2. Go Back to Main Menu\n";
            std::cout << "Choose an option (1/2): ";
            std::cin >> choice;

            if (std::cin.fail()) { // If invalid input
                std::cin.clear(); // Clear error flags
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                std::cout << "Invalid input! Please enter 1 or 2.\n";
            }
            else {
                switch (choice) {
                case '1':
                    Login(); // Retry login
                    return;
                case '2':
                    main(); // Go back to main menu
                    return;
                default:
                    std::cout << "Invalid input! Please enter 1 or 2.\n";
                    break;
                }
            }
        } while (true);
    }

    mysql_free_result(res);
}



void AdminMenu() {
    int menu;

    do {
        system("cls");
        cout << "-----Admin Page------" << endl;
        cout << "1. Search Movie" << endl;
        cout << "2. Update Movie Information" << endl;
        cout << "3. Delete Movie" << endl;
        cout << "4. Delete Comment" << endl;
        cout << "5. View Movie" << endl;
        cout << "6. View Current Movie Preference" << endl;
        cout << "7. Logout" << endl;
        cout << "Choose menu: ";

        cin >> menu;

        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a number between 1 and 7. Press Enter to continue...";
            cin.get(); 
            continue;
        }

        switch (menu) {
        case 1:
            SearchMovie(AdminMenu,"Admin");
            return;
        case 2:
            EditMovie();
            return;
        case 3:
            DeleteMovie();
            return;
        case 4:
            DeleteComment();
            return;
        case 5:
            ViewMovie(AdminMenu,"Admin");
            return;
        case 6:
            Report("Admin");
            return;
        case 7:
            system("cls");
            main();
            return;
        default:
            cout << "Please choose a valid option (1 - 7). Press Enter to continue...";
            cin.get(); 
            break;
        }
    } while (true);
}


//THIS THE MENU FOR UNREGISTERED USER

void GuestMenu() {
    int menu;

    while (true) {
        system("cls");
        std::cout << "----- Guest Page -----" << std::endl;
        std::cout << "1. View Movie List" << std::endl;
        std::cout << "2. Search Movie" << std::endl;
        std::cout << "3. View Current Movie Preference" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choose menu: ";

        if (!(std::cin >> menu)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 4.\nPress Enter to continue...";
            (void)_getch();
            continue;
        }

        switch (menu) {
        case 1:
            ViewMovie(GuestMenu, "Guest"); 
            break;
        case 2:
            SearchMovie(GuestMenu,"Guest");
            break;
        case 3:
            Report("Guest");
            break;
        case 4:
            system("cls");
            main();
        default:
            std::cout << "Invalid choice! Please choose between 1 and 4.\nPress Enter to continue...";
            (void)_getch();
            break;
        }
    }
}

void ViewMovie(const std::function<void()>& returnMenu, const std::string& userType) {
    system("cls");
    std::cout << "\t\t\t\t--- List of All Movies ---" << std::endl;

  
    qstate = mysql_query(conn, "SELECT movie_id, movie_name, movie_genre, duration FROM movie");

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);

        if (res) {
            
            Table movieTable;
            movieTable.add_row({ "ID", "Movie Name", "Genre", "Duration" });

            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))) {
                movieTable.add_row({ row[0], row[1], row[2], row[3] });
            }

          
            tableFormat(movieTable);
            std::cout << movieTable << std::endl;

            mysql_free_result(res);

            
            MovieDetails(userType, -1, "View");
        }
        else {
            std::cerr << "Error: Failed to retrieve movie list. " << mysql_error(conn) << std::endl;
        }
    }
    else {
        std::cerr << "Query Execution Problem! Error Code: " << mysql_errno(conn) << std::endl;
    }

    returnMenu();
}








void SearchMovie(const std::function<void()>& returnMenu, const std::string& userType) {
    system("cls");
    std::string movie;

    while (true) {
        std::cout << "Search movie by title: ";
        std::getline(std::cin, movie);

        std::cout << "--- List of Searched Movies ---" << std::endl;

        // Construct SQL query to search movies
        std::string search_query = "SELECT movie_id, movie_name, movie_genre, duration FROM movie WHERE movie_name LIKE '%" + movie + "%'";
        qstate = mysql_query(conn, search_query.c_str());

        if (!qstate) {
            MYSQL_RES* res = mysql_store_result(conn);

            if (res) {
                if (mysql_num_rows(res) == 0) {
                    std::cout << "No results found for your query.\n";
                    mysql_free_result(res);
                    std::cout << "Press Enter to return to the menu...";
                    std::cin.get();
                    returnMenu();
                    return;
                }

                // Create and format the table
                tabulate::Table movieTable;
                movieTable.add_row({ "ID", "Movie Name", "Genre", "Duration" });

                // Populate rows with search results
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res))) {
                    movieTable.add_row({ row[0], row[1], row[2], row[3] });
                }

                // Apply table formatting
                tableFormat(movieTable);

                // Print the formatted table
                std::cout << movieTable << std::endl;

                mysql_free_result(res);

                // Call MovieDetails function
                MovieDetails(userType, -1, "Search");

                // Clear the input buffer to avoid leftover '\n' causing issues
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            else {
                std::cerr << "Error: Failed to retrieve search results. " << mysql_error(conn) << std::endl;
            }
        }
        else {
            std::cerr << "Query Execution Problem! Error Code: " << mysql_errno(conn) << std::endl;
        }

        // Ask the user if they want to search again
        char choose;
        while (true) {
            std::cout << "\nDo you want to search for another movie? (y/n): ";
            std::cin >> choose;

            if (choose == 'y' || choose == 'Y') {
                // Clear the input buffer before repeating the search
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break; // Restart the search
            }
            else if (choose == 'n' || choose == 'N') {
                returnMenu();
                return;
            }
            else {
                std::cout << "Invalid input! Please enter 'y' or 'n'.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}




void fetchMovieDetails(int option) {
    std::string query =
        "SELECT movie.movie_name, movie.movie_genre, movie.duration, "
        "movie.avg_rating, movie.rating_count, user.name AS director_name "
        "FROM movie "
        "INNER JOIN user ON movie.user_id = user.user_id "
        "WHERE movie.movie_id = " + std::to_string(option);

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    if (res == nullptr) {
        std::cerr << "Failed to store result: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(res))) {
       
        std::cout << "\nMovie Details:\n";
        std::cout << "Title: " << (row[0] ? row[0] : "N/A") << "\n";
        std::cout << "Genre: " << (row[1] ? row[1] : "N/A") << "\n";
        std::cout << "Duration: " << (row[2] ? row[2] : "N/A") << "\n";

        
        std::string avgRating = row[3] ? row[3] : "N/A";
        std::string ratingCount = row[4] ? row[4] : "0";

        
        if (avgRating != "N/A" && ratingCount != "0") {
            std::cout << "Average Rating: " << avgRating << " stars\n";
            std::cout << "Number of Ratings: " << ratingCount << "\n";
        }
        else {
            std::cout << "No ratings yet.\n";
        }

       
        std::string directorName = row[5] ? row[5] : "Unknown";
        std::cout << "Director: " << directorName << "\n";

        
        std::string favoriteCheckQuery =
            "SELECT COUNT(*) FROM favorites WHERE user_id = " + std::to_string(userId) +
            " AND movie_id = " + std::to_string(option);

        if (mysql_query(conn, favoriteCheckQuery.c_str())) {
            std::cerr << "Failed to check favorites: " << mysql_error(conn) << std::endl;
        }
        else {
            MYSQL_RES* favRes = mysql_store_result(conn);
            if (favRes) {
                MYSQL_ROW favRow = mysql_fetch_row(favRes);
                bool isFavorite = favRow && std::stoi(favRow[0]) > 0;

                if (isFavorite) {
                    std::cout << "\033[31mFavourite\033[0m\n";
                }
                mysql_free_result(favRes);
            }
            else {
                std::cerr << "Failed to store favorites result: " << mysql_error(conn) << std::endl;
            }
        }
    }
    else {
        std::cout << "No movie found with ID " << option << "\n";
    }

    mysql_free_result(res);
}

void MovieDetails(const std::string& userType, int movieId, const std::string& origin) {
    while (true) {
        if (movieId == -1) {
            std::cout << "\nInsert the movie ID if you want to see the details (or 0 to go back): ";
            std::cin >> movieId;

            if (std::cin.fail() || movieId < 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "\033[31mInvalid input! Please enter a valid Movie ID.\033[0m\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                system("cls");

                // Re-display the correct menu based on the origin
                if (origin == "Search") {
                    if (userType == "Reviewer") {
                        SearchMovie(ReviewerMenu, "Reviewer");
                    }
                    else if (userType == "Guest") {
                        SearchMovie(GuestMenu, "Guest");
                    }
                    else if (userType == "Director") {
                        SearchMovie(DirectorMenu, "Director");
                    }
                    else if (userType == "Admin") {
                        SearchMovie(AdminMenu, "Admin");
                    }
                }
                else if (origin == "View") {
                    if (userType == "Reviewer") {
                        ViewMovie(ReviewerMenu, userType);
                    }
                    else if (userType == "Guest") {
                        ViewMovie(GuestMenu, userType);
                    }
                    else if (userType == "Director") {
                        ViewMovie(DirectorMenu, userType);
                    }
                    else if (userType == "Admin") {
                        ViewMovie(AdminMenu, userType);
                    }
                }
                return; // Ensure it stops looping and returns to the respective function
            }

            if (movieId == 0) {
                // Redirect back based on the origin
                if (origin == "Search") {
                    if (userType == "Reviewer") {
                        SearchMovie(ReviewerMenu, "Reviewer");
                    }
                    else if (userType == "Guest") {
                        SearchMovie(GuestMenu, "Guest");
                    }
                    else if (userType == "Director") {
                        SearchMovie(DirectorMenu, "Director");
                    }
                    else if (userType == "Admin") {
                        SearchMovie(AdminMenu, "Admin");
                    }
                }
                else if (origin == "View") {
                    if (userType == "Reviewer") {
                        ReviewerMenu();
                    }
                    else if (userType == "Guest") {
                        GuestMenu();
                    }
                    else if (userType == "Director") {
                        DirectorMenu();
                    }
                    else if (userType == "Admin") {
                        AdminMenu();
                    }
                }
                return;
            }

            system("cls");
        }

        // Check if the movie exists in the database
        std::string checkMovieQuery = "SELECT COUNT(*) FROM movie WHERE movie_id = " + std::to_string(movieId);
        if (mysql_query(conn, checkMovieQuery.c_str())) {
            std::cerr << "Failed to validate movie ID: " << mysql_error(conn) << std::endl;
            return;
        }

        MYSQL_RES* checkRes = mysql_store_result(conn);
        if (checkRes == nullptr) {
            std::cerr << "Failed to store result for movie validation: " << mysql_error(conn) << std::endl;
            return;
        }

        MYSQL_ROW checkRow = mysql_fetch_row(checkRes);
        int movieExists = checkRow && std::stoi(checkRow[0]) > 0;
        mysql_free_result(checkRes);

        if (!movieExists) {
            std::cout << "No movie found with ID: " << movieId << std::endl;
            std::cout << "Press Enter to try again...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            movieId = -1;
            system("cls");

            // Re-display the relevant list based on origin
            if (origin == "Search") {
                if (userType == "Reviewer") {
                    SearchMovie(ReviewerMenu, "Reviewer");
                }
                else if (userType == "Guest") {
                    SearchMovie(GuestMenu, "Guest");
                }
                else if (userType == "Director") {
                    SearchMovie(DirectorMenu, "Director");
                }
                else if (userType == "Admin") {
                    SearchMovie(AdminMenu, "Admin");
                }
            }
            else if (origin == "View") {
                if (userType == "Reviewer") {
                    ViewMovie(ReviewerMenu, userType);
                }
                else if (userType == "Guest") {
                    ViewMovie(GuestMenu, userType);
                }
                else if (userType == "Director") {
                    ViewMovie(DirectorMenu, userType);
                }
                else if (userType == "Admin") {
                    ViewMovie(AdminMenu, userType);
                }
            }
            return;
        }

        // Fetch and display movie details
        fetchMovieDetails(movieId);

        // Query to fetch comments, thumbs count, and usernames
        std::string query = R"(
            SELECT 
                comment.comment_id, 
                comment.user_id, 
                user.username, 
                comment.rev_comment, 
                comment.thumbs_count, 
                (SELECT COUNT(*) FROM thumbs WHERE thumbs.comment_id = comment.comment_id AND thumbs.user_id = )" + std::to_string(userId) + R"() AS user_liked
            FROM comment
            INNER JOIN user ON comment.user_id = user.user_id
            WHERE comment.movie_id = )" + std::to_string(movieId);

        if (mysql_query(conn, query.c_str())) {
            std::cerr << "Failed to fetch comments: " << mysql_error(conn) << std::endl;
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            std::cerr << "Failed to store result: " << mysql_error(conn) << std::endl;
            return;
        }

        MYSQL_ROW row;
        std::cout << "\nComments:\n" << std::string(40, '-') << '\n';

        std::vector<int> commentIds;
        std::vector<int> userCommentIds;
        int commentCount = 0;

        while ((row = mysql_fetch_row(res))) {
            int commentId = row[0] ? std::stoi(row[0]) : 0;
            int commentUserId = row[1] ? std::stoi(row[1]) : 0;
            std::string username = row[2] ? row[2] : "Unknown";
            std::string comment = row[3] ? row[3] : "No comment";
            int thumbsCount = row[4] ? std::stoi(row[4]) : 0;
            bool userLiked = row[5] ? std::stoi(row[5]) > 0 : false;

            commentIds.push_back(commentId);

            if (commentUserId == userId) {
                userCommentIds.push_back(commentId);
                std::cout << ++commentCount << ". Username: \033[34m" << username << "\033[0m\n";
            }
            else {
                std::cout << ++commentCount << ". Username: " << username << '\n';
            }

            std::cout << "   Comment: " << comment << '\n';
            std::cout << "   Likes: " << (userLiked ? "\033[33m" : "") << thumbsCount << (userLiked ? "\033[0m" : "") << '\n';
            std::cout << std::string(40, '-') << '\n';
        }

        if (commentCount == 0) {
            std::cout << "No comments for this movie yet.\n";
        }
        mysql_free_result(res);

        char choice;
        std::cout << "\nWhat would you like to do?\n";
        if (userType == "Reviewer") {
            std::cout << "1. Add a Comment\n";
            std::cout << "2. Add a Rating\n";
                std::cout << "3. Delete your own Comment\n";
            std::cout << "4. Go Back\n";
        }
        else if (userType == "Guest") {
            std::cout << "1. Add/Remove from Favorites\n";
                std::cout << "2. Like/Unlike a Comment\n";
            std::cout << "3. Go Back\n";
        }
        else {
            std::cout << "1. Go Back\n";
        }
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (userType == "Reviewer") {
            switch (choice) {
            case '1':
                CommentAbility(movieId, userId);
                break;
            case '2':
                addMovieRating(movieId, userId);
                break;
            case '3':
                if (!userCommentIds.empty()) {
                    DeleteOwnComment(movieId, userCommentIds, commentIds);
                }
                else {
                    std::cout << "You have no comments to delete for this movie.\n";
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                }
                break;
            case '4':
                if (origin == "Search") {
                    SearchMovie(ReviewerMenu, "Reviewer");
                }
                else if (origin == "View") {
                    ViewMovie(ReviewerMenu, "Reviewer");
                }
                return;
            default:
                std::cout << "Invalid choice. Press enter to try again.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        }
        else if (userType == "Guest") {
            switch (choice) {
            case '1':
                addToFavorites(movieId, "Guest");
                break;
            case '2':
                if (commentCount > 0) {
                    int selectedComment;
                    std::cout << "\nEnter the comment number to like/unlike: ";
                    std::cin >> selectedComment;

                    if (std::cin.fail() || selectedComment <= 0 || selectedComment > commentIds.size()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input! Press enter to try again.\n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                        continue;
                    }

                    int commentId = commentIds[selectedComment - 1];

                    // Check if the user already liked the comment
                    std::string checkLikeQuery = "SELECT COUNT(*) FROM thumbs WHERE user_id = " + std::to_string(userId) +
                        " AND comment_id = " + std::to_string(commentId);

                    if (mysql_query(conn, checkLikeQuery.c_str())) {
                        std::cerr << "Failed to check like status: " << mysql_error(conn) << std::endl;
                        continue;
                    }

                    MYSQL_RES* checkRes = mysql_store_result(conn);
                    if (checkRes == nullptr) {
                        std::cerr << "Failed to store like check result: " << mysql_error(conn) << std::endl;
                        continue;
                    }

                    MYSQL_ROW checkRow = mysql_fetch_row(checkRes);
                    bool alreadyLiked = checkRow && std::stoi(checkRow[0]) > 0;
                    mysql_free_result(checkRes);

                    // Like or unlike the comment
                    std::string updateQuery;
                    if (alreadyLiked) {
                        updateQuery = "DELETE FROM thumbs WHERE user_id = " + std::to_string(userId) +
                            " AND comment_id = " + std::to_string(commentId);
                        std::string decrementQuery = "UPDATE comment SET thumbs_count = thumbs_count - 1 WHERE comment_id = " + std::to_string(commentId);
                        mysql_query(conn, decrementQuery.c_str());
                    }
                    else {
                        updateQuery = "INSERT INTO thumbs (user_id, comment_id) VALUES (" + std::to_string(userId) +
                            ", " + std::to_string(commentId) + ")";
                        std::string incrementQuery = "UPDATE comment SET thumbs_count = thumbs_count + 1 WHERE comment_id = " + std::to_string(commentId);
                        mysql_query(conn, incrementQuery.c_str());
                    }

                    if (mysql_query(conn, updateQuery.c_str())) {
                        std::cerr << "Failed to update like status: " << mysql_error(conn) << std::endl;
                    }
                    else {
                        std::cout << (alreadyLiked ? "\nYou unliked the comment.\n" : "\nYou liked the comment.\n");
                        std::cout << "Press Enter to continue...";
                        std::cin.ignore();
                        std::cin.get();
                    }
                }
                else {
                    std::cout << "There are no comments to like/unlike.\n";
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore();
                    std::cin.get();
                }
                break;
            case '3':
                if (origin == "Search") {
                    SearchMovie(GuestMenu, "Guest");
                }
                else if (origin == "View") {
                    ViewMovie(GuestMenu, "Guest");
                }
                return;
            default:
                std::cout << "Invalid choice. Press enter to try again.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        }
        else {
            if (choice == '1') {
                if (origin == "Search") {
                    if (userType == "Admin") {
                        SearchMovie(AdminMenu, "Admin");
                    }
                    else if (userType == "Director") {
                        SearchMovie(DirectorMenu, "Director");
                    }
                }
                else if (origin == "View") {
                    if (userType == "Admin") {
                        ViewMovie(AdminMenu, "Admin");
                    }
                    else if (userType == "Director") {
                        ViewMovie(DirectorMenu, "Director");
                    }
                }
                return;
            }
            else {
                std::cout << "Invalid choice. Press enter to try again.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        }
        system("cls");
    }
}


void ReviewerMenu()
{
    int menu;
    do {
        system("cls");
        cout << "-----Reviewer Page------" << endl;

        cout << "1. View Movie List" << endl;
        cout << "2. Search Movie" << endl;
        cout << "3. View current movie preference" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose menu: ";

        cin >> menu;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 4. Press Enter to continue...";
            cin.get();
            continue;
        }

        switch (menu)
        {
        case 1:
            ViewMovie(ReviewerMenu,"Reviewer");
            break;
        case 2:
            SearchMovie(ReviewerMenu,"Reviewer");
            break;
        case 3:
            Report("Reviewer");
            break;
        case 4:
            system("cls");
            main();
            break;
        default:
            cout << "Please choose a valid option (1 - 4). Press Enter to continue...";
            cin.get();
            break;
        }
    } while (true);
}

void DirectorMenu() {
    int menu;
    int directorId = userId;

    do {
        system("cls");
        cout << "-----Director Page------" << endl;
        cout << "1. View Movie List" << endl;
        cout << "2. Search Movie" << endl;
        cout << "3. Add Own Movie Information" << endl;
        cout << "4. Update Own Movie Information" << endl;
        cout << "5. Delete Own Movie Information" << endl;
        cout << "6. View Current Movie Preference" << endl;
        cout << "7. Logout" << endl;
        cout << "Choose menu: ";

        cin >> menu;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 7. Press Enter to continue...";
            cin.get();
            continue;
        }

        switch (menu) {
        case 1:
            ViewMovie(DirectorMenu,"Director");
            return;
        case 2:
            SearchMovie(DirectorMenu,"Director");
            return;
        case 3:
            InsertMovie();
            return;
        case 4:
            EditMovieForDirector(userId);
            return;
        case 5:
            DeleteMovieForDirector(directorId);
        case 6:
            Report("Director");
            return;
        case 7:
            system("cls");
            main();
            return;
        default:
            cout << "Please choose a valid option (1 - 7). Press Enter to continue...";
            cin.get();
            break;
        }
    } while (true);
}

void CommentAbility(int movieId, int userId) { 
    string commentText;

    // Prompt the user to enter a comment
    cout << "\nAdd Your Comment for the Movie:\n";
    cout << "Comment: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, commentText);

    // Escape single quotes in the commentText
    size_t pos = 0;
    while ((pos = commentText.find("'", pos)) != string::npos) {
        commentText.insert(pos, "\\");
        pos += 2; // Move past the escaped quote
    }

    // Prepare the SQL query to insert the comment
    string query = "INSERT INTO comment (movie_id, rev_comment, user_id) VALUES (" +
        to_string(movieId) + ", '" + commentText + "', " + to_string(userId) + ")";

    // Execute the query
    if (mysql_query(conn, query.c_str())) {
        cerr << "Failed to add comment: " << mysql_error(conn) << endl;
    }
    else {
        cout << "\nYour comment has been added successfully!" << endl;
    }

    // Pause and wait for user input
    cout << "Press Enter to continue...\n";
    (void)_getch();
}


//THIS IS TO ADD MOVIE RATING (FOR REVIEWER ONLY)
void addMovieRating(int movieId, int userId) {
    double userRating;

    // Get user input for the rating
    do {
        std::cout << "Enter your rating for the movie (0.1 to 5.0 stars): ";
        std::cin >> userRating;

        if (std::cin.fail() || userRating < 0.1 || userRating > 5.0) {
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a rating between 0.1 and 5.0.\n";
        }
        else {
            break;
        }
    } while (true);

    // Check if the user has already rated this movie
    std::string checkQuery = "SELECT rating_id FROM rating WHERE user_id = " + std::to_string(userId) +
        " AND movie_id = " + std::to_string(movieId);

    if (mysql_query(conn, checkQuery.c_str())) {
        std::cerr << "Failed to check existing rating: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);
    bool ratingExists = (row != nullptr);
    mysql_free_result(res);

    std::string query;
    if (ratingExists) {
        // Update the existing rating
        query = "UPDATE rating SET rating_given = " + std::to_string(userRating) +
            " WHERE user_id = " + std::to_string(userId) +
            " AND movie_id = " + std::to_string(movieId);
    }
    else {
        // Insert a new rating
        query = "INSERT INTO rating (user_id, movie_id, rating_given) VALUES (" +
            std::to_string(userId) + ", " + std::to_string(movieId) + ", " + std::to_string(userRating) + ")";
    }

    if (mysql_query(conn, query.c_str())) {
        std::cerr << "Failed to add or update rating: " << mysql_error(conn) << std::endl;
        return;
    }

    // Update the avg_rating and rating_count in the movie table
    std::string recalculateQuery = "SELECT AVG(rating_given), COUNT(rating_given) FROM rating WHERE movie_id = " + std::to_string(movieId);
    if (mysql_query(conn, recalculateQuery.c_str())) {
        std::cerr << "Failed to recalculate average rating: " << mysql_error(conn) << std::endl;
        return;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    if (row && row[0] && row[1]) {
        double avgRating = std::stod(row[0]);
        int ratingCount = std::stoi(row[1]);

        // Update the movie table with the new avg_rating and rating_count
        std::string updateMovieQuery = "UPDATE movie SET avg_rating = " + std::to_string(avgRating) +
            ", rating_count = " + std::to_string(ratingCount) +
            " WHERE movie_id = " + std::to_string(movieId);

        if (mysql_query(conn, updateMovieQuery.c_str())) {
            std::cerr << "Failed to update movie rating and count: " << mysql_error(conn) << std::endl;
        }
        else {
            std::cout << "Your rating has been saved successfully!\n";
            std::cout << "The new average rating for the movie is: " << std::fixed << std::setprecision(1)
                << avgRating << " stars from " << ratingCount << " ratings.\n";
        }
    }
    else {
        std::cerr << "Failed to retrieve updated rating details.\n";
    }

    mysql_free_result(res);
}



void tableFormat(Table& table) {
    // Format the header row (smaller size with single-line borders)
    table[0].format()
        .font_color(Color::grey)
        .background_color(Color::green)
        .font_style({ FontStyle::bold })
        .padding(0)  // Remove padding
        .font_align(FontAlign::center)
        .border_top("-")  // Use single-line border
        .border_bottom("-")
        .border_left("|")
        .border_right("|");

    // Format each row
    size_t index = 0;
    for (auto& row : table) {
        if (index > 0) { // Skip header row
            row.format()
                .font_style({ FontStyle::bold })
                .font_align(FontAlign::center)
                .border_top(" ")
                .border_bottom(" ")
                .border_left(" ")
                .border_right(" ")
                .corner(" ");
        }
        index++;
    }
}



void EditMovie() {
    system("cls");

    std::string data;
    int choose;
    char option;
    std::string MovieID;

    std::cout << "----- Edit Movie -----\n" << std::endl;

    // Query to fetch movie data
    qstate = mysql_query(conn, "SELECT movie_id, movie_name, movie_genre, duration FROM movie");

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);

        if (res) {
            tabulate::Table movieTable;
            movieTable.add_row({ "ID", "Movie Name", "Genre", "Duration" });

            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))) {
                movieTable.add_row({ row[0], row[1], row[2], row[3] });
            }

            tableFormat(movieTable);
            std::cout << movieTable << std::endl;

            mysql_free_result(res);
        }
        else {
            std::cerr << "Error: Failed to retrieve result set! " << mysql_error(conn) << std::endl;
            return;
        }

        
        do {
            std::cout << "Choose Movie ID (or press 0 to go back): ";
            std::cin >> MovieID;

            if (MovieID == "0") {
                AdminMenu();
                return;
            }

            std::string fetchQuery = "SELECT movie_name, movie_genre, duration FROM movie WHERE movie_id = '" + MovieID + "'";
            if (mysql_query(conn, fetchQuery.c_str())) {
                std::cerr << "Error fetching movie details: " << mysql_error(conn) << std::endl;
                continue;
            }

            MYSQL_RES* fetchRes = mysql_store_result(conn);
            if (!fetchRes || mysql_num_rows(fetchRes) == 0) {
                std::cerr << "No movie found with the given ID.\n";
                std::cerr << "Press Enter to continue ";
                if (fetchRes) mysql_free_result(fetchRes);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                system("cls");
                EditMovie();
                return;
            }

            MYSQL_ROW currentDetails = mysql_fetch_row(fetchRes);
            std::string previousName = currentDetails[0];
            std::string previousGenre = currentDetails[1];
            std::string previousDuration = currentDetails[2];
            mysql_free_result(fetchRes);

            system("cls");
            std::cout << " Previous Name : " << previousName << " ";
            std::cout << "(Press Enter to keep the current name)\n";
            std::cout << "New Movie Name : ";
            std::getline(std::cin.ignore(), data);
            if (!data.empty()) {
                std::string update_query = "UPDATE movie SET movie_name = '" + data + "' WHERE movie_id = '" + MovieID + "'";
                qstate = mysql_query(conn, update_query.c_str());
                if (qstate) std::cerr << "Error updating name: " << mysql_error(conn) << std::endl;
            }

            std::vector<std::string> genres = {
                "Action", "Thriller", "Drama", "Comedy", "Horror",
                "Sci-Fi", "Romance", "Adventure", "Fantasy", "Crime",
                "Mystery", "Animation", "Family", "Musical", "Documentary",
                "Biography", "History", "War", "Western", "Sport"
            };

            std::cout << "\nChoose new movie genre(s) (Previous: " << previousGenre << ") by entering the corresponding numbers (e.g., 1-2-3).";
            std::cout << "\n(Press Enter to keep the current genre)\n";
            for (size_t i = 0; i < genres.size(); ++i) {
                std::cout << i + 1 << ". " << genres[i] << "\n";
            }

            std::cout << "Your choice: ";
            std::string genreChoice;
            std::getline(std::cin, genreChoice);

            if (!genreChoice.empty()) {
                std::istringstream iss(genreChoice);
                std::string genre;
                std::set<std::string> selectedGenres;
                while (std::getline(iss, genre, '-')) {
                    int genreIndex = std::stoi(genre) - 1;
                    if (genreIndex >= 0 && genreIndex < genres.size()) {
                        selectedGenres.insert(genres[genreIndex]);
                    }
                    else {
                        std::cerr << "Invalid genre selection: " << genre << ". Skipping genre update.\n";
                        selectedGenres.clear();
                        break;
                    }
                }

                if (!selectedGenres.empty()) {
                    data = "";
                    for (const auto& g : selectedGenres) {
                        if (!data.empty()) {
                            data += ", ";
                        }
                        data += g;
                    }

                    std::string update_query = "UPDATE movie SET movie_genre = '" + data + "' WHERE movie_id = '" + MovieID + "'";
                    qstate = mysql_query(conn, update_query.c_str());
                    if (qstate) std::cerr << "Error updating genre: " << mysql_error(conn) << std::endl;
                }
            }

            std::cout << "Enter New Duration (Previous: " << previousDuration << "):\n";
            std::cout << "(Press Enter to keep the current duration)\n";

            std::string input;
            int hours = -1, minutes = -1;

            std::cout << "Hours: ";
            std::getline(std::cin, input);
            if (!input.empty()) {
                try {
                    hours = std::stoi(input);
                }
                catch (...) {
                    std::cerr << "Invalid input for hours. Skipping update.\n";
                    hours = -1;
                }
            }

            std::cout << "Minutes: ";
            std::getline(std::cin, input);
            if (!input.empty()) {
                try {
                    minutes = std::stoi(input);
                }
                catch (...) {
                    std::cerr << "Invalid input for minutes. Skipping update.\n";
                    minutes = -1;
                }
            }

            if (hours >= 0 && minutes >= 0) {
                data = std::to_string(hours) + " hours " + std::to_string(minutes) + " minutes";
                std::string update_query = "UPDATE movie SET duration = '" + data + "' WHERE movie_id = '" + MovieID + "'";
                qstate = mysql_query(conn, update_query.c_str());
                if (qstate) std::cerr << "Error updating duration: " << mysql_error(conn) << std::endl;
            }
            else {
                std::cout << "Duration unchanged.\n";
            }

            std::cout << "Movie updated successfully!\n";

            do {
                std::cout << "Do you want to edit another movie? (y/n): ";
                std::cin >> option;

                if (option == 'y' || option == 'Y') {
                    EditMovie();
                    return;
                }
                else if (option == 'n' || option == 'N') {
                    AdminMenu();
                    return;
                }
                else {
                    std::cout << "Invalid input! Please enter 'y' for yes or 'n' for no.\n";
                }
            } while (true);
        } while (true);
    }
    else {
        std::cerr << "Query Execution Problem! Error Code: " << mysql_errno(conn) << std::endl;
    }
}







//  For Director Only
void InsertMovie() {
    system("cls");

    std::string movieName, movieGenre, duration;
    char option;

   
    const char* genres[] = {
        "Action", "Thriller", "Drama", "Comedy", "Horror",
        "Sci-Fi", "Romance", "Adventure", "Fantasy", "Crime",
        "Mystery", "Animation", "Family", "Musical", "Documentary",
        "Biography", "History", "War", "Western", "Sport"
    };

    const size_t genreCount = sizeof(genres) / sizeof(genres[0]);

    std::cout << "----- Insert New Movie -----" << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    std::cout << "Movie Name: ";
    std::getline(std::cin, movieName);

    
    std::cout << "\nChoose movie genre(s) by entering the corresponding numbers (e.g., 1-2-3):\n";
    for (size_t i = 0; i < genreCount; ++i) {
        std::cout << i + 1 << ". " << genres[i] << "\n";
    }

    std::cout << "Your choice: ";
    std::string genreChoice;
    std::getline(std::cin, genreChoice);

   
    std::istringstream iss(genreChoice);
    std::string genre;
    std::set<std::string> selectedGenres; 
    while (std::getline(iss, genre, '-')) {
        try {
            int genreIndex = std::stoi(genre) - 1;
            if (genreIndex >= 0 && genreIndex < static_cast<int>(genreCount)) {
                selectedGenres.insert(genres[genreIndex]);
            }
            else {
                throw std::out_of_range("Invalid index");
            }
        }
        catch (...) {
            std::cerr << "Invalid genre selection: " << genre << ". Please try again.\n";
            return InsertMovie(); 
        }
    }

    
    movieGenre = "";
    for (const auto& g : selectedGenres) {
        if (!movieGenre.empty()) {
            movieGenre += ", ";
        }
        movieGenre += g;
    }

    int hours, minutes;
    std::cout << "Duration:" << std::endl;
    std::cout << "  Hours: ";
    while (!(std::cin >> hours) || hours < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Enter a valid number of hours: ";
    }

    std::cout << "  Minutes: ";
    while (!(std::cin >> minutes) || minutes < 0 || minutes >= 60) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input! Enter a valid number of minutes (0-59): ";
    }

    
    duration = std::to_string(hours) + " hours " + std::to_string(minutes) + " minutes";

   
    std::string insertQuery = "INSERT INTO movie (movie_name, movie_genre, duration, user_id) "
        "VALUES ('" + movieName + "', '" + movieGenre + "', '" + duration + "', " + std::to_string(userId) + ")";

  
    if (mysql_query(conn, insertQuery.c_str())) {
        std::cerr << "Failed to add movie. Error: " << mysql_error(conn) << std::endl;
        return;
    }

    std::cout << "New movie added successfully by director with user_id: " << userId << "!\n";
    system("cls");

   
    qstate = mysql_query(conn, "SELECT movie_id, movie_name, movie_genre, duration FROM movie");
    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);

        if (res) {
            
            tabulate::Table movieTable;

            
            movieTable.add_row({ "ID", "Movie Name", "Genre", "Duration" });

         
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res))) {
                movieTable.add_row({ row[0], row[1], row[2], row[3] });
            }

           
            tableFormat(movieTable);

           
            std::cout << "\nUpdated Movies List:\n";
            std::cout << movieTable << std::endl;

            mysql_free_result(res);
        }
        else {
            std::cerr << "Error: Failed to retrieve result set! " << mysql_error(conn) << std::endl;
        }
    }
    else {
        std::cerr << "Error fetching updated movie list: " << mysql_error(conn) << std::endl;
    }

    do {
        std::cout << "Do you want to add another movie? (y/n): ";
        std::cin >> option;

        if (option == 'y' || option == 'Y') {
            InsertMovie();
            return;
        }
        else if (option == 'n' || option == 'N') {
            DirectorMenu();
            return;
        }
        else {
            std::cout << "Invalid input! Please enter 'y' for yes or 'n' for no.\n";
        }
    } while (true);
}



void DeleteMovie() {
    system("cls");

    std::string MovieID;
    char option;

    std::cout << "----- Delete Movie -----" << std::endl;

    std::string query = "SELECT movie_id, movie_name, movie_genre, duration FROM movie";
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);

        
        if (!res || mysql_num_rows(res) == 0) {
            std::cout << "No movies available in the database.\n" << std::endl;
            mysql_free_result(res);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            AdminMenu();
            return;
        }

        
        tabulate::Table movieTable;

   
        movieTable.add_row({ "ID", "Movie Name", "Genre", "Duration" });

        
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            movieTable.add_row({ row[0], row[1], row[2], row[3] });
        }

     
        tableFormat(movieTable);

        
        std::cout << "\nMovies List:\n";
        std::cout << movieTable << std::endl;

        mysql_free_result(res);

        
        while (true) {
            std::cout << "Enter the Movie ID to delete (or press 0 to go back): ";
            std::cin >> MovieID;

           
            if (MovieID == "0") {
                AdminMenu();
                return;
            }

            std::string validateQuery = "SELECT movie_id FROM movie WHERE movie_id = '" + MovieID + "'";
            if (mysql_query(conn, validateQuery.c_str())) {
                std::cerr << "Error validating Movie ID: " << mysql_error(conn) << std::endl;
                continue;
            }

            MYSQL_RES* validateRes = mysql_store_result(conn);
            if (!validateRes || mysql_num_rows(validateRes) == 0) {
                std::cout << "Invalid Movie ID. Please try again.\n";
                std::cout << "Press Enter to continue ";
                if (validateRes) mysql_free_result(validateRes);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                DeleteMovie();
                return;
            }

            
            mysql_free_result(validateRes);
            break;
        }

       
        std::cout << "Are you sure you want to delete Movie ID " << MovieID << "? (y/n): ";
        std::cin >> option;

        if (option == 'y' || option == 'Y') {
          
            std::string deleteQuery = "DELETE FROM movie WHERE movie_id = '" + MovieID + "'";
            qstate = mysql_query(conn, deleteQuery.c_str());

            if (!qstate) {
                std::cout << "Movie deleted successfully! Press Enter to continue " << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                system("cls");
            }
            else {
                std::cerr << "Failed to delete movie. Error: " << mysql_error(conn) << std::endl;
            }
        }
        else {
            std::cout << "Deletion canceled." << std::endl;
        }

       
        qstate = mysql_query(conn, query.c_str());
        if (!qstate) {
            MYSQL_RES* updatedRes = mysql_store_result(conn);

            if (updatedRes) {
                
                tabulate::Table updatedMovieTable;

               
                updatedMovieTable.add_row({ "ID", "Movie Name", "Genre", "Duration" });

               
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(updatedRes))) {
                    updatedMovieTable.add_row({ row[0], row[1], row[2], row[3] });
                }

                
                tableFormat(updatedMovieTable);

               
                std::cout << "\nUpdated Movies List:\n";
                std::cout << updatedMovieTable << std::endl;

                mysql_free_result(updatedRes);
            }
            else {
                std::cerr << "Error: Failed to retrieve updated movie list! " << mysql_error(conn) << std::endl;
            }
        }
        else {
            std::cerr << "Error fetching updated movie list: " << mysql_error(conn) << std::endl;
        }
    }
    else {
        std::cerr << "Query Execution Problem! Error Code: " << mysql_errno(conn) << std::endl;
    }

    
    do {
        std::cout << "Do you want to delete another movie? (y/n): ";
        std::cin >> option;

        if (option == 'y' || option == 'Y') {
            DeleteMovie();
            return;
        }
        else if (option == 'n' || option == 'N') {
            AdminMenu();
            return;
        }
        else {
            std::cout << "Invalid input! Please enter 'y' for yes or 'n' for no.\n";
        }
    } while (true);
}


void DeleteComment() {
    system("cls");
    char choose;

    do {
        system("cls");
        cout << "Search movie by title to delete a comment (or press 0 to go back): ";
        string movie;
        getline(cin.ignore(), movie); // Read the movie title or 0

        // Check if the user wants to go back
        if (movie == "0") {
            AdminMenu();
            return;
        }

        // Search for movies matching the input
        string search_query = "SELECT movie_id, movie_name FROM movie WHERE movie_name LIKE '%" + movie + "%'";
        const char* q = search_query.c_str();
        qstate = mysql_query(conn, q);

        if (!qstate) {
            MYSQL_RES* res = mysql_store_result(conn);

            if (res) {
                vector<int> movieIds; // Store the list of movie IDs
                MYSQL_ROW row;

                // Create the table for movie results
                Table movieTable;
                movieTable.add_row({ "Movie ID", "Movie Name" });

                while ((row = mysql_fetch_row(res))) {
                    movieIds.push_back(atoi(row[0]));
                    movieTable.add_row({ row[0], row[1] });
                }

                mysql_free_result(res);

                if (movieIds.empty()) {
                    cout << "No movies found matching your search.\n";
                    cout << "\nDo you want to search again? (y/n): ";
                    do {
                        cin >> choose;
                        if (choose == 'y' || choose == 'Y') {
                            break; // Continue the search loop
                        }
                        else if (choose == 'n' || choose == 'N') {
                            AdminMenu();
                            return;
                        }
                        else {
                            cout << "Invalid input! Please enter 'y' or 'n': ";
                        }
                    } while (true);

                    continue; // Restart the search loop
                }

                // Apply the custom table format
                tableFormat(movieTable);
                cout << "\n--- List of Movies ---\n";
                cout << movieTable << endl;

                // Prompt user for Movie ID
                int movieId;
                do {
                    cout << "\nEnter the movie ID to see details (or press 0 to go back): ";
                    cin >> movieId;

                    if (cin.fail()) { // Handle invalid input
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a valid Movie ID.\n";
                    }
                    else if (movieId == 0) {
                        cout << "Restarting Delete Comment Menu \n";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                        system("cls");
                       DeleteComment();
                        return;
                    }
                    else if (find(movieIds.begin(), movieIds.end(), movieId) == movieIds.end()) {
                        cout << "Invalid Movie ID. Please try again.\n";
                    }
                    else {
                        break; // Valid Movie ID entered
                    }
                } while (true);

                system("cls");
                // Show movie details
                fetchMovieDetails(movieId);

                // Query for comments related to the selected movie
                string comment_query = "SELECT comment.comment_id, user.username, comment.rev_comment "
                    "FROM comment "
                    "INNER JOIN user ON comment.user_id = user.user_id "
                    "WHERE comment.movie_id = " + to_string(movieId);
                if (mysql_query(conn, comment_query.c_str())) {
                    cerr << "Failed to fetch comments: " << mysql_error(conn) << endl;
                    AdminMenu();
                    return;
                }

                MYSQL_RES* commentRes = mysql_store_result(conn);
                if (commentRes == nullptr) {
                    cerr << "Failed to store comments result: " << mysql_error(conn) << endl;
                    AdminMenu();
                    return;
                }

                MYSQL_ROW commentRow;
                vector<int> commentIds;

                // Create the table for comments
                Table commentTable;
                commentTable.add_row({ "Comment ID", "Username", "Comment" });

                while ((commentRow = mysql_fetch_row(commentRes))) {
                    int commentId = atoi(commentRow[0]);
                    string username = commentRow[1] ? commentRow[1] : "Unknown";
                    string comment = commentRow[2] ? commentRow[2] : "No comment";

                    commentIds.push_back(commentId);
                    commentTable.add_row({ commentRow[0], username, comment });
                }

                if (commentIds.empty()) {
                    cout << "No comments available for this movie.\n";
                    mysql_free_result(commentRes);
                    continue; // Restart the search loop
                }

                // Apply the custom table format
                tableFormat(commentTable);
                cout << "\n--- Comments for Selected Movie ---\n";
                cout << commentTable << endl;

                // Loop for re-entering the comment ID until valid or "go back" option
                int commentIdToDelete;
                do {
                    cout << "\nEnter the Comment ID to delete (or 0 to go back): ";
                    cin >> commentIdToDelete;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        cout << "Invalid input. Please enter a valid Comment ID.\n";
                    }
                    else if (commentIdToDelete == 0) {
                        cout << " \n";
                        mysql_free_result(commentRes);
                        break; // Go back to movie selection
                    }
                    else if (find(commentIds.begin(), commentIds.end(), commentIdToDelete) == commentIds.end()) {
                        cout << "Invalid Comment ID selected. Please try again.\n";
                    }
                    else {
                        // Deletion query
                        string delete_query = "DELETE FROM comment WHERE comment_id = " + to_string(commentIdToDelete);
                        if (mysql_query(conn, delete_query.c_str())) {
                            cerr << "Failed to delete comment: " << mysql_error(conn) << endl;
                        }
                        else {
                            cout << "Comment deleted successfully.\n";
                        }
                        mysql_free_result(commentRes);
                        break; // Exit to main loop after deletion
                    }
                } while (true);
            }
            else {
                cerr << "Error: Failed to retrieve movies. " << mysql_error(conn) << endl;
            }
        }
        else {
            cerr << "Query Execution Problem! Error Code: " << mysql_errno(conn) << endl;
        }


        cout << "\nDo you want to delete another comment or go back to Admin Menu? (y/n): ";
        do {
            cin >> choose;
            if (choose == 'y' || choose == 'Y') {
                break;
            }
            else if (choose == 'n' || choose == 'N') {
                AdminMenu();
                return;
            }
            else {
                cout << "Invalid input! Please enter 'y' or 'n': ";
            }
        } while (true);

    } while (true);
}

void EditMovieForDirector(int directorId) {
    system("cls");

    std::string data;
    int choose;
    char option;
    std::string MovieID;

    std::cout << "----- Edit Your Movies -----\n" << std::endl;

    // Query to fetch movies created by the director
    std::string query = "SELECT movie_id, movie_name, movie_genre, duration FROM movie WHERE user_id = " + std::to_string(directorId);
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);

        // Check if the result set is empty
        if (!res || mysql_num_rows(res) == 0) {
            std::cout << "Your Movie Is not in our database yet :( \n" << std::endl;
            mysql_free_result(res);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            DirectorMenu();
            return;
        }

        // Create and populate the table
        tabulate::Table movieTable;
        movieTable.add_row({ "ID", "Movie Name", "Genre", "Duration" });

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            movieTable.add_row({ row[0], row[1], row[2], row[3] });
        }

        tableFormat(movieTable);
        std::cout << movieTable << std::endl;

        mysql_free_result(res);

        // Allow the user to choose a movie or go back
        do {
            std::cout << "Choose Movie ID (or enter 0 to go back): ";
            std::cin >> MovieID;

            // Check if the user entered '0' to go back
            if (MovieID == "0") {
                DirectorMenu();
                return;
            }

            // Check if the entered Movie ID exists for the director
            std::string fetchQuery = "SELECT movie_name, movie_genre, duration FROM movie WHERE movie_id = '" + MovieID + "' AND user_id = " + std::to_string(directorId);
            if (mysql_query(conn, fetchQuery.c_str())) {
                std::cerr << "Error fetching movie details: " << mysql_error(conn) << std::endl;
                std::cout << "Press Enter to proceed...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                system("cls");
                EditMovieForDirector(directorId);
                return;
            }

            MYSQL_RES* fetchRes = mysql_store_result(conn);
            if (!fetchRes || mysql_num_rows(fetchRes) == 0) {
                std::cerr << "No movie found with the given ID under your ownership.\n";
                if (fetchRes) mysql_free_result(fetchRes);
                std::cout << "Press Enter to try again...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                system("cls");
                EditMovieForDirector(directorId);
                return;
            }

            // Movie ID is valid, proceed with editing
            MYSQL_ROW currentDetails = mysql_fetch_row(fetchRes);
            std::string previousName = currentDetails[0];
            std::string previousGenre = currentDetails[1];
            std::string previousDuration = currentDetails[2];
            mysql_free_result(fetchRes);
            system("cls");

            // Edit Movie Name
            std::cout << " Previous Name : " << previousName << " ";
            std::cout << "(Press Enter to keep the current name)\n";
            std::cout << "New Movie Name : ";
            std::getline(std::cin.ignore(), data);
            if (!data.empty()) {
                std::string update_query = "UPDATE movie SET movie_name = '" + data + "' WHERE movie_id = '" + MovieID + "' AND user_id = " + std::to_string(directorId);
                qstate = mysql_query(conn, update_query.c_str());
                if (qstate) std::cerr << "Error updating name: " << mysql_error(conn) << std::endl;
            }

            // Edit Movie Genre
            std::vector<std::string> genres = {
                "Action", "Thriller", "Drama", "Comedy", "Horror",
                "Sci-Fi", "Romance", "Adventure", "Fantasy", "Crime",
                "Mystery", "Animation", "Family", "Musical", "Documentary",
                "Biography", "History", "War", "Western", "Sport"
            };

            std::cout << "\nChoose new movie genre(s) (Previous: " << previousGenre << ") by entering the corresponding numbers (e.g., 1-2-3). Press Enter to keep the same genre:\n";
            for (size_t i = 0; i < genres.size(); ++i) {
                std::cout << i + 1 << ". " << genres[i] << "\n";
            }

            std::cout << "Your choice: ";
            std::string genreChoice;
            std::getline(std::cin, genreChoice);

            if (!genreChoice.empty()) {
                std::istringstream iss(genreChoice);
                std::string genre;
                std::set<std::string> selectedGenres;
                while (std::getline(iss, genre, '-')) {
                    int genreIndex = std::stoi(genre) - 1;
                    if (genreIndex >= 0 && genreIndex < genres.size()) {
                        selectedGenres.insert(genres[genreIndex]);
                    }
                    else {
                        std::cerr << "Invalid genre selection: " << genre << ". Skipping genre update.\n";
                        selectedGenres.clear();
                        break;
                    }
                }

                if (!selectedGenres.empty()) {
                    data = "";
                    for (const auto& g : selectedGenres) {
                        if (!data.empty()) {
                            data += ", ";
                        }
                        data += g;
                    }

                    std::string update_query = "UPDATE movie SET movie_genre = '" + data + "' WHERE movie_id = '" + MovieID + "' AND user_id = " + std::to_string(directorId);
                    qstate = mysql_query(conn, update_query.c_str());
                    if (qstate) std::cerr << "Error updating genre: " << mysql_error(conn) << std::endl;
                }
            }

            // Edit Movie Duration
            std::cout << "Enter New Duration (Previous: " << previousDuration << "):\n";
            std::cout << "(Press Enter to keep the current duration)\n";

            std::string input;
            int hours = -1, minutes = -1;

            std::cout << "Hours: ";
            std::getline(std::cin, input);
            if (!input.empty()) {
                try {
                    hours = std::stoi(input);
                }
                catch (...) {
                    std::cerr << "Invalid input for hours. Skipping update.\n";
                    hours = -1;
                }
            }

            std::cout << "Minutes: ";
            std::getline(std::cin, input);
            if (!input.empty()) {
                try {
                    minutes = std::stoi(input);
                }
                catch (...) {
                    std::cerr << "Invalid input for minutes. Skipping update.\n";
                    minutes = -1;
                }
            }

            if (hours >= 0 && minutes >= 0) {
                data = std::to_string(hours) + " hours " + std::to_string(minutes) + " minutes";
                std::string update_query = "UPDATE movie SET duration = '" + data + "' WHERE movie_id = '" + MovieID + "'";
                qstate = mysql_query(conn, update_query.c_str());
                if (qstate) std::cerr << "Error updating duration: " << mysql_error(conn) << std::endl;
            }
            else {
                std::cout << "Duration unchanged.\n";
            }

            std::cout << "Movie updated successfully!\n";

            break; // Exit the loop once a valid movie is edited
        } while (true);

        do {
            std::cout << "Do you want to edit another movie? (y/n): ";
            std::cin >> option;

            if (option == 'y' || option == 'Y') {
                EditMovieForDirector(directorId);
                return;
            }
            else if (option == 'n' || option == 'N') {
                DirectorMenu();
                return;
            }
            else {
                std::cout << "Invalid input! Please enter 'y' for yes or 'n' for no.\n";
            }
        } while (true);
    }
    else {
        std::cerr << "Query Execution Problem! Error Code: " << mysql_errno(conn) << std::endl;
    }
}


void DeleteMovieForDirector(int directorId) {
    system("cls");

    std::string MovieID;
    char option;

    std::cout << "----- Delete Your Movies -----\n" << std::endl;

    std::string query = "SELECT movie_id, movie_name, movie_genre, duration FROM movie WHERE user_id = " + std::to_string(directorId);
    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);

     
        if (!res || mysql_num_rows(res) == 0) {
            std::cout << "Your Movie Is not in our database yet :( \n" << std::endl;
            mysql_free_result(res);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            DirectorMenu(); 
            return;
        }

    
        tabulate::Table movieTable;

       
        movieTable.add_row({ "ID", "Movie Name", "Genre", "Duration" });

      
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            movieTable.add_row({ row[0], row[1], row[2], row[3] });
        }

        
        tableFormat(movieTable);

        
        std::cout << "\nYour Movies:\n";
        std::cout << movieTable << std::endl;

        mysql_free_result(res);

      
        while (true) {
            std::cout << "Enter the Movie ID to delete (or press 0 to go back): ";
            std::cin >> MovieID;

           
            if (MovieID == "0") {
                std::cout << "Returning to the Director menu \n";
                DirectorMenu();
                return;
            }

            
            std::string validateQuery = "SELECT movie_id FROM movie WHERE movie_id = '" + MovieID + "' AND user_id = " + std::to_string(directorId);
            if (mysql_query(conn, validateQuery.c_str())) {
                std::cerr << "Error validating Movie ID: " << mysql_error(conn) << std::endl;
                continue;
            }

            MYSQL_RES* validateRes = mysql_store_result(conn);
            if (!validateRes || mysql_num_rows(validateRes) == 0) {
                std::cout << "Invalid Movie ID or the movie does not belong to you. Press enter to try again.\n";
                if (validateRes) mysql_free_result(validateRes);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                system("cls");
                DeleteMovieForDirector(directorId);

            }

            
            mysql_free_result(validateRes);
            break;
        }

        std::cout << "Are you sure you want to delete Movie ID " << MovieID << "? (y/n): ";
        std::cin >> option;

        if (option == 'y' || option == 'Y') {
            
            std::string deleteQuery = "DELETE FROM movie WHERE movie_id = '" + MovieID + "' AND user_id = " + std::to_string(directorId);
            const char* q = deleteQuery.c_str();
            qstate = mysql_query(conn, q);

            if (!qstate) {
                std::cout << "Movie deleted successfully!" << std::endl;
            }
            else {
                std::cerr << "Failed to delete movie. Error: " << mysql_error(conn) << std::endl;
            }
        }
        else {
            std::cout << "Deletion canceled." << std::endl;
        }

      
        qstate = mysql_query(conn, query.c_str());
        if (!qstate) {
            MYSQL_RES* res = mysql_store_result(conn);

            if (res) {
                
                tabulate::Table updatedMovieTable;

                
                updatedMovieTable.add_row({ "ID", "Movie Name", "Genre", "Duration" });

                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res))) {
                    updatedMovieTable.add_row({ row[0], row[1], row[2], row[3] });
                }

                
                tableFormat(updatedMovieTable);

               
                std::cout << "\nUpdated Movies List:\n";
                std::cout << updatedMovieTable << std::endl;

                mysql_free_result(res);
            }
            else {
                std::cerr << "Error: Failed to retrieve result set! " << mysql_error(conn) << std::endl;
            }
        }
        else {
            std::cerr << "Error fetching updated movie list: " << mysql_error(conn) << std::endl;
        }
    }
    else {
        std::cerr << "Query Execution Problem! Error Code: " << mysql_errno(conn) << std::endl;
    }

    
    do {
        std::cout << "Do you want to delete another movie? (y/n): ";
        std::cin >> option;

        if (option == 'y' || option == 'Y') {
            DeleteMovieForDirector(directorId);
            return;
        }
        else if (option == 'n' || option == 'N') {
            DirectorMenu();
            return;
        }
        else {
            std::cout << "Invalid input! Please enter 'y' for yes or 'n' for no.\n";
        }
    } while (true);
}



void ShowRanking(const std::string& userType) {
    system("cls");

    std::cout << "----- Movie Rankings -----\n" << std::endl;

    std::string meanRatingQuery = "SELECT AVG(avg_rating) FROM movie WHERE avg_rating IS NOT NULL";
    if (mysql_query(conn, meanRatingQuery.c_str())) {
        std::cerr << "Failed to calculate mean rating (C): " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* meanRes = mysql_store_result(conn);
    if (!meanRes) {
        std::cerr << "Failed to retrieve mean rating: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_ROW meanRow = mysql_fetch_row(meanRes);
    double C = meanRow && meanRow[0] ? std::stod(meanRow[0]) : 3.0;
    mysql_free_result(meanRes);

    std::string totalMoviesQuery = "SELECT COUNT(*) FROM movie";
    if (mysql_query(conn, totalMoviesQuery.c_str())) {
        std::cerr << "Failed to calculate the total number of movies: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* totalMoviesRes = mysql_store_result(conn);
    if (!totalMoviesRes) {
        std::cerr << "Failed to retrieve total number of movies: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_ROW totalMoviesRow = mysql_fetch_row(totalMoviesRes);
    int totalMovies = totalMoviesRow && totalMoviesRow[0] ? std::stoi(totalMoviesRow[0]) : 1;
    mysql_free_result(totalMoviesRes);

    double m = totalMovies * 0.1;
    m = m < 10 ? 10 : m;

    std::string query = R"(
        SELECT 
            movie.movie_id, 
            movie.movie_name, 
            movie.movie_genre, 
            movie.duration, 
            movie.avg_rating, 
            movie.rating_count, 
            user.name AS director_name 
        FROM 
            movie 
        INNER JOIN 
            user 
        ON 
            movie.user_id = user.user_id
        WHERE 
            movie.avg_rating IS NOT NULL 
            AND movie.rating_count IS NOT NULL
    )";

    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);

        if (!res || mysql_num_rows(res) == 0) {
            std::cout << "No movies available in the database for ranking.\n" << std::endl;
            mysql_free_result(res);
            std::cout << "Press any key to return to the report...";
            std::cin.get();
            Report(userType);
            return;
        }

        std::vector<std::tuple<std::string, std::string, std::string, std::string, double, int, double>> rankings;
        MYSQL_ROW row;

        while ((row = mysql_fetch_row(res))) {
            std::string movieName = row[1];
            std::string movieGenre = row[2];
            std::string duration = row[3];
            double avgRating = std::stod(row[4]);
            int ratingCount = std::stoi(row[5]);
            std::string directorName = row[6];

            double score = ((ratingCount / (ratingCount + m)) * avgRating) +
                ((m / (ratingCount + m)) * C);

            score *= 2; // Scale the score to a 10-point scale

            rankings.emplace_back(movieName, movieGenre, duration, directorName, avgRating, ratingCount, score);
        }

        mysql_free_result(res);

        std::sort(rankings.begin(), rankings.end(), [](const auto& a, const auto& b) {
            return std::get<6>(a) > std::get<6>(b);
            });

        tabulate::Table rankingTable;

        rankingTable.add_row({ "Rank", "Movie Name", "Genre", "Duration", "Director", "Avg Rating", "Rating Count", "Score" });

        int rank = 1;
        for (const auto& movie : rankings) {
            std::ostringstream avgRatingStream, scoreStream;

            avgRatingStream << std::fixed << std::setprecision(1) << std::get<4>(movie);
            scoreStream << std::fixed << std::setprecision(1) << std::get<6>(movie);

            rankingTable.add_row({
                std::to_string(rank++),
                std::get<0>(movie),
                std::get<1>(movie),
                std::get<2>(movie),
                std::get<3>(movie),
                avgRatingStream.str(),
                std::to_string(std::get<5>(movie)),
                scoreStream.str()
                });
        }

        tableFormat(rankingTable);

        std::cout << rankingTable << std::endl;

    }
    else {
        std::cerr << "Query Execution Problem! Error Code: " << mysql_errno(conn) << std::endl;
    }

    std::cout << "Press enter to return ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    Report(userType);
}










void Report(const std::string& userType) {
    int menu;

    do {
        system("cls");
        std::cout << "----- Movie Preference ------" << std::endl;
        std::cout << "1. Movie Ranking" << std::endl;
        std::cout << "2. Reviewer Ranking" << std::endl;
        std::cout << "3. User Choice Favourite" << std::endl;
        std::cout << "4. Go Back" << std::endl;
        std::cout << "Choose menu: ";

        std::cin >> menu;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number between 1 and 4. Press Enter to continue...";
            std::cin.get();
            continue;
        }

        switch (menu) {
        case 1:
            if (userType == "Reviewer") {
                ShowRanking("Reviewer");
            }
            else if (userType == "Director") {
                ShowRanking("Director");
            }
            else if (userType == "Admin") {
                ShowRanking("Admin");
            }
            else if (userType == "Guest") {
                ShowRanking("Guest");
            }
            else {
                std::cerr << "Invalid user type! Returning to Movie Preference Menu" << std::endl;
                return;
            }
            break;
        case 2:
            if (userType == "Reviewer") {
                ShowReviewerRanking("Reviewer");
            }
            else if (userType == "Director") {
                ShowReviewerRanking("Director");
            }
            else if (userType == "Admin") {
                ShowReviewerRanking("Admin");
            }
            else if (userType == "Guest") {
                ShowReviewerRanking("Guest");
            }
            else {
                std::cerr << "Invalid user type! Returning to Movie Preference Menu" << std::endl;
                return;
            }
            break;
        case 3:
            GenerateGenreFavoritesChart();
            break;
        case 4:
            if (userType == "Reviewer") {
                ReviewerMenu();
            }
            else if (userType == "Director") {
                DirectorMenu();
            }
            else if (userType == "Admin") {
                AdminMenu();
            }
            else if (userType == "Guest") {
                GuestMenu();
            }
            return;
        default:
            std::cout << "Please choose a valid option (1 - 4). Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
    } while (true);
}




void ShowReviewerRanking(const std::string& userType) {
    system("cls");

    std::cout << "----- User Ranking by Total Likes -----\n" << std::endl;

    // SQL query to aggregate thumbs_count per user
    std::string query = R"(
        SELECT 
            user.user_id, 
            user.username, 
            SUM(comment.thumbs_count) AS total_likes
        FROM 
            comment
        INNER JOIN 
            user ON comment.user_id = user.user_id
        GROUP BY 
            user.user_id, user.username
        HAVING 
            total_likes > 0
        ORDER BY 
            total_likes DESC
    )";

    qstate = mysql_query(conn, query.c_str());

    if (!qstate) {
        MYSQL_RES* res = mysql_store_result(conn);

        // Check if the result set is empty
        if (!res || mysql_num_rows(res) == 0) {
            std::cout << "No users have received likes on their comments.\n" << std::endl;
            mysql_free_result(res);
            std::cout << "Press any key to return ";
            std::cin.get();
            Report(userType);
            return;
        }

        // Create and populate the table
        tabulate::Table rankingTable;

        // Add headers
        rankingTable.add_row({ "Rank", "Username", "Total Likes" });

        // Fetch data and populate the rows
        MYSQL_ROW row;
        int rank = 1;
        while ((row = mysql_fetch_row(res))) {
            std::string username = row[1] ? row[1] : "Unknown";
            std::string totalLikes = row[2] ? row[2] : "0";

            rankingTable.add_row({
                std::to_string(rank++), // Rank
                username,               // Username
                totalLikes              // Total Likes
                });
        }

        mysql_free_result(res);

        // Apply formatting to the table
        tableFormat(rankingTable);

        // Print the formatted table
        std::cout << rankingTable << std::endl;

    }
    else {
        std::cerr << "Query Execution Problem! Error Code: " << mysql_errno(conn) << std::endl;
    }

    std::cout << "Press enter to return ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    Report(userType);
}

void addToFavorites(int movieId, const std::string& userType) {
  
    std::string checkQuery = "SELECT COUNT(*) FROM favorites WHERE user_id = " + std::to_string(userId) +
        " AND movie_id = " + std::to_string(movieId);

    if (mysql_query(conn, checkQuery.c_str())) {
        std::cerr << "Failed to check favorites: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_RES* checkRes = mysql_store_result(conn);
    if (checkRes == nullptr) {
        std::cerr << "Failed to store check result: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_ROW checkRow = mysql_fetch_row(checkRes);
    bool isFavorite = checkRow && std::stoi(checkRow[0]) > 0; 
    mysql_free_result(checkRes);

    if (isFavorite) {
        
        std::string deleteQuery = "DELETE FROM favorites WHERE user_id = " + std::to_string(userId) +
            " AND movie_id = " + std::to_string(movieId);
        if (mysql_query(conn, deleteQuery.c_str())) {
            std::cerr << "Failed to remove from favorites: " << mysql_error(conn) << std::endl;
        }
        else {
            std::cout << "\nMovie removed from favorites.\n";
        }
    }
    else {
      
        std::string insertQuery = "INSERT INTO favorites (user_id, movie_id) VALUES (" + std::to_string(userId) +
            ", " + std::to_string(movieId) + ")";
        if (mysql_query(conn, insertQuery.c_str())) {
            std::cerr << "Failed to add to favorites: " << mysql_error(conn) << std::endl;
        }
        else {
            std::cout << "\nMovie added to favorites.\n";
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

#define BAR_COLOR "\033[47;30m" 
#define RESET_COLOR "\033[0m"   

void GenerateGenreFavoritesChart() {
    system("cls");

    // SQL Query to count genres based on user favorites
    string query = R"(
        SELECT genre, COUNT(*) AS count
        FROM (
            SELECT 
                favorites.user_id,
                favorites.movie_id,
                SUBSTRING_INDEX(SUBSTRING_INDEX(movie.movie_genre, ', ', numbers.n), ', ', -1) AS genre
            FROM 
                favorites
            INNER JOIN 
                movie ON favorites.movie_id = movie.movie_id
            CROSS JOIN (
                SELECT 1 AS n UNION ALL SELECT 2 UNION ALL SELECT 3 UNION ALL SELECT 4 UNION ALL SELECT 5
            ) numbers
            WHERE 
                numbers.n <= LENGTH(movie.movie_genre) - LENGTH(REPLACE(movie.movie_genre, ', ', '')) + 1
            GROUP BY favorites.user_id, favorites.movie_id, genre
        ) AS user_genres
        GROUP BY genre
        ORDER BY count DESC
    )";

    // Execute the query
    if (mysql_query(conn, query.c_str())) {
        cerr << "Failed to fetch favorite genres: " << mysql_error(conn) << endl;
        system("pause");
        return;
    }

    // Store the result
    MYSQL_RES* res = mysql_store_result(conn);
    if (res == nullptr) {
        cerr << "Failed to store result: " << mysql_error(conn) << endl;
        system("pause");
        return;
    }

    if (mysql_num_rows(res) == 0) {
        cout << "No favorite genres found in the database.\n";
        mysql_free_result(res);
        system("pause");
        return;
    }

    // Fetch data into vectors
    MYSQL_ROW row;
    vector<pair<string, int>> genreData;
    while ((row = mysql_fetch_row(res))) {
        string genre = row[0] ? row[0] : "Unknown";
        int count = row[1] ? stoi(row[1]) : 0;
        genreData.emplace_back(genre, count);
    }
    mysql_free_result(res);

    // Calculate maximum bar length
    int maxCount = 0;
    for (const auto& genre : genreData) {
        maxCount = max(maxCount, genre.second);
    }

    // Handle edge case: No genres
    if (maxCount == 0) {
        cout << "No valid data to display in the chart.\n";
        system("pause");
        return;
    }

    // Determine the x-axis interval based on maxCount
    double interval = pow(10, floor(log10(maxCount)) - 1); // Determine base scale
    if (maxCount / interval > 10) interval *= 2;           // Adjust interval if too many steps
    if (maxCount / interval > 10) interval *= 5;           // Further adjustment if needed

    // Ensure no decimals for low data values (1, 2, 3...)
    if (maxCount <= 10) {
        interval = 1; // Force integer intervals
    }

    // Print chart header
    cout << "___ Favourite Genres Chart ___\n\n";

    // Print the x-axis scale with precise spacing
    int scaleWidth = 40; // Maximum bar length
    cout << left << setw(15) << "" << "   "; // Padding for genre labels

    for (int i = 0; i <= scaleWidth; ++i) {
        int scaleValue = round(i * maxCount / scaleWidth); // Calculate the scale value for the position
        int barPos = round(scaleValue * scaleWidth / maxCount); // Calculate bar position

        if (i == barPos) {
            cout << scaleValue; // Print the scale value
        }
        else {
            cout << " "; // Fill empty space
        }
    }
    cout << endl;

    // Print the separator line under the x-axis
    cout << left << setw(15) << "" << "   ";
    for (int i = 0; i <= scaleWidth; ++i) {
        bool isSeparator = false;
        for (int j = 0; j <= maxCount; ++j) {
            if (round(j * scaleWidth / maxCount) == i) {
                isSeparator = true;
                break;
            }
        }
        cout << (isSeparator ? "|" : " "); // Print separator at calculated positions
    }
    cout << endl;

    // Print bars with genre and count
    for (const auto& genre : genreData) {
        cout << left << setw(15) << genre.first << " | ";
        int barLength = genre.second * scaleWidth / maxCount; // Scale bar to fit terminal width
        for (int i = 0; i < barLength; ++i) {
            cout << BAR_COLOR << " " << RESET_COLOR; // Print colored bar segment
        }
        cout << " " << genre.second << endl; // Display count at the end

        // Add a gap between rows
        cout << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void DeleteOwnComment(int movieId, const std::vector<int>& userCommentIds, const std::vector<int>& commentIds) {
    while (true) {
        int commentIndex;

        std::cout << "Enter the number of the comment you want to delete (or 0 to cancel): ";

        // Input validation: make sure the user enters an integer
        while (!(std::cin >> commentIndex)) {
            std::cin.clear();  // Clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
            std::cout << "Invalid input. Please enter a valid number: ";
        }

        if (commentIndex == 0) {
            std::cout << "Deletion canceled.\n";
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            return;
        }

        if (commentIndex < 1 || commentIndex > commentIds.size()) {
            std::cout << "Invalid number. Please try again.\n";
            continue;
        }

        int selectedCommentId = commentIds[commentIndex - 1];

        if (std::find(userCommentIds.begin(), userCommentIds.end(), selectedCommentId) == userCommentIds.end()) {
            std::cout << "You cannot delete someone else's comment. Please try again.\n";
            continue;
        }

        char choice;
        std::cout << "Are you sure you want to delete this comment? (y/n): ";
        std::cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            std::cout << "Deletion canceled.\n";
            std::cout << "Press Enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            return;
        }

        std::string deleteQuery = "DELETE FROM comment WHERE comment_id = " + std::to_string(selectedCommentId);
        qstate = mysql_query(conn, deleteQuery.c_str());

        if (!qstate) {
            std::cout << "Your comment has been successfully deleted.\n";
        }
        else {
            std::cerr << "Failed to delete your comment: " << mysql_error(conn) << std::endl;
        }

        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }
}



















