#include <iostream> 
#include <string> 
#include <conio.h> 
#include <mysql.h> //libmysql
#include <iomanip>
#include<functional>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

void Register();
void Login();
int main();
void InsertMovie();//Director
void ViewMovie(const std::function<void()>& returnMenu, const std::string& userType);
void SearchMovie(const std::function<void()>& returnMenu, const std::string& userType);
void Report(const std::string& userType);
void AdminMenu();//Admin
void GuestMenu();//Guest
void fetchMovieDetails(int option);
void MovieDetails(const std::string& userType, int movieId, const std::string& origin);
void ReviewerMenu();
void DirectorMenu();
void CommentAbility(int movieId,int userId);//Reviewer
void clearInputBuffer();
void addMovieRating(int movieId,int userId);//Reviewer
void tableFormat(Table& table);
void EditMovie();
void DeleteMovie();
void DeleteComment();
void EditMovieForDirector(int directorId); //Director
void DeleteMovieForDirector(int directorId); //Director
void ShowRanking(const std::string& userType);
void ShowReviewerRanking(const std::string& userType);
void addToFavorites(int movieId, const std::string& userType);
void GenerateGenreFavoritesChart();
void DeleteOwnComment(int movieId, const std::vector<int>& userCommentIds, const std::vector<int>& commentIds);


int qstate;
MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;
string UserID;

class db_response
{
public:
    static void ConnectionFunction()
    {
        conn = mysql_init(0);
        if (conn)
            cout << "Database Connected" << endl;
        else
            cout << "Failed To Connect!" << endl;

        conn = mysql_real_connect(conn, "localhost", "root", "", "movie_review", 3306,
            NULL, 0);
        if (conn)
            cout << "Database Connected To MySql" << endl;
        else
            cout << "Failed To Connect!" << endl;
    }
};


