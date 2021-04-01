/**
 * Task 2
 * Written by Sukhrob Ilyosbekov
 * Source code available in https://github.com/suxrobGM/CppCourseworkAssignments
 * 
 **/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
using namespace std;

const string credentials_file = "credentials.txt";
const string movies_db_file = "movies_db.txt";

class Utils
{
public:
    static bool file_exists(const string& name) 
    {
        ifstream f(name.c_str());
        return f.good();
    }

    static vector<string> split(string str, string token)
    {
        vector<string> result;
        while(str.size())
        {
            int index = str.find(token);
            if(index != string::npos)
            {
                result.push_back(str.substr(0, index));
                str = str.substr(index + token.size());
                if(str.size() == 0)
                    result.push_back(str);
            }
            else
            {
                result.push_back(str);
                str = "";
            }
        }
        return result;
    }

    static string int_to_string(int value)
    {
        ostringstream temp;
        temp << value;
        return temp.str();
    }

    static void clear_input()
    {
        cin.clear();
        cin.ignore(256,'\n');
    }

    static void display_error(string errorMsg = "Invalid value, please try again")
    {
        cout << "\n-------------------------------------------------------" << endl;
        cout << "ERROR: " << errorMsg << endl;
        cout << "-------------------------------------------------------\n" << endl;
    }

    static void log(string logMsg)
    {
        cout << "\n-------------------------------------------------------" << endl;
        cout << "DEBUG: " << logMsg << endl;
        cout << "-------------------------------------------------------\n" << endl;
    }

    // Exit from program
    static void quit_program() 
    {
        cout << "\n-------------------------------------------------------" << endl;
        cout << "Quitted program!" << endl;
        cout << "-------------------------------------------------------\n" << endl;
        exit(0); // Exit from console
    }
};

class User
{
public:
    // Public properties
    string username;
    string password;

    // Default constructor
    User()
    {
        username = "";
        password = "";
    }

    void save_to_file(string filename)
    {
        ofstream out_file(filename.c_str());

        // store data to file
        out_file << this->username << " " << this->password << " " << endl;
        out_file.close();
    }

    static User read_from_file(string filename)
    {
        User user;
        ifstream in_file(filename.c_str());

        // read data from file
        in_file >> user.username >> user.password;
        in_file.close();
        return user;
    }
};

class Movie
{
private:
    string _empty_data;

public:
    // Public properties
    int id;
    int duration;
    string title;
    string starcast;
    string director;
    string category;

    // Default constructor
    Movie()
    {
        _empty_data = "-";
        id = -1;
        duration = 0;
        title = _empty_data;
        starcast = _empty_data;
        director = _empty_data;
        category = _empty_data;
    }

    string to_string()
    {
        stringstream ss;
        string title_name = title == _empty_data ? " " : title;
        string starcast_name = starcast == _empty_data ? " " : starcast;
        string director_name = director == _empty_data ? " " : director;
        ss << "Movie ID: " << id << endl;
        ss << "Title: " << title_name << endl;
        ss << "Main Cast: " << starcast_name << endl;
        ss << "Director: " << director_name << endl;
        ss << "Duration: " << duration << " mins" << endl;
        return ss.str();
    }

    static Movie input_movie(string category_name)
    {
        Movie movie;
        movie.category = category_name;

        Utils::clear_input();
        cout << "\nInput movie title: " << endl;
        getline(cin, movie.title);

        cout << "\nInput movie director: " << endl;
        getline(cin, movie.director);

        cout << "\nInput movie main casts: " << endl;
        getline(cin, movie.starcast);

    INPUT_DURATION:
        cout << "\nInput movie duration: " << endl;
        cin >> movie.duration;

        if (cin.fail() || movie.duration <= 0)
        {
            Utils::clear_input();
            Utils::display_error();
            goto INPUT_DURATION;
        }

        return movie;
    }

    static void edit_movie(Movie& movie)
    {
        cout << "Note: Leave empty to skip editing" << endl;
        string title = "";
        string director = "";
        string starcast = "";
        int duration = 0;

        Utils::clear_input();
        cout << "\nInput movie title: " << endl;
        getline(cin, title);

        cout << "\nInput movie director: " << endl;
        getline(cin, director);

        cout << "\nInput movie main casts: " << endl;
        getline(cin, starcast);

    INPUT_DURATION:
        cout << "\nInput movie duration: " << endl;
        cin >> duration;

        if (cin.fail())
        {
            Utils::clear_input();
            Utils::display_error();
            goto INPUT_DURATION;
        }

        if (title != "" && title != " " && title != "\n")
            movie.title = title;
        
        if (director != "" && director != " " && director != "\n")
            movie.director = director;
        
        if (starcast != "" && starcast != " " && starcast != "\n")
            movie.starcast = starcast;
        
        if (duration > 0)
            movie.duration = duration;

        Utils::clear_input();
    }
};

class MoviesRepository
{
private:
    string _db_file;
    string _delimiter;
    string _empty_data;

public:

    MoviesRepository(string db_file)
    {
        _db_file = db_file;
        _delimiter = "/";
        _empty_data = "-";
    }

    // Get number of movies in the category
    int get_movies_count(string category_name)
    {
        int movies_count = 0;
        vector<Movie> movies = get_movies();
        for (size_t i = 0; i < movies.size(); i++)
        {
            if (movies[i].category == category_name && movies[i].title != _empty_data)
            {
                movies_count++;
            }
        }

        return movies_count;
    }

    // Check exists movie by comapring id and categroy name
    bool exists_movie(int id, string category_name)
    {
        vector<Movie> movies = get_movies();

        for (size_t i = 0; i < movies.size(); i++)
        {
            if (movies[i].id == id && 
                movies[i].category == category_name)
            {
                return true; 
            }    
        }

        return false;
    }

    // Get movie by id
    Movie get_movie(int id)
    {
        vector<Movie> movies = get_movies();
        Movie defualt_movie;

        for (size_t i = 0; i < movies.size(); i++)
        {
            if (movies[i].id == id)
            {
                return movies[i]; 
            }    
        }

        return defualt_movie;
    }

    // Get collection of movies from file
    vector<Movie> get_movies()
    {
        vector<Movie> movies;
        ifstream in_file(_db_file.c_str());

        while (!in_file.eof())
        {
            Movie movie;
            string buffer;
            getline(in_file, buffer);
            vector<string> str_buffer = Utils::split(buffer, _delimiter);

            if (str_buffer.size() >= 5)
            {
                movie.id = atoi(str_buffer[0].c_str());
                movie.title = str_buffer[1];
                movie.starcast = str_buffer[2];
                movie.director = str_buffer[3];
                movie.category = str_buffer[4];
                movie.duration = atoi(str_buffer[5].c_str());
                movies.push_back(movie);
            }
        }
        
        in_file.close();
        return movies;
    }

    bool add_movie_to_available_slot(const Movie& movie)
    {
        vector<Movie> movies = get_movies();
        ofstream out_file(_db_file.c_str(), ios::trunc);
        bool writtenInAvailableSlot = false;

        for (size_t i = 0; i < movies.size(); i++)
        {
            if (!writtenInAvailableSlot && 
                movies[i].category == movie.category && 
                movies[i].title == _empty_data)
            {
                movies[i].title = movie.title;
                movies[i].starcast = movie.starcast;
                movies[i].director = movie.director;
                movies[i].category = movie.category;
                movies[i].duration = movie.duration;
                writtenInAvailableSlot = true;
            }

            out_file << movies[i].id << _delimiter << movies[i].title << _delimiter << movies[i].starcast << _delimiter 
                    << movies[i].director << _delimiter << movies[i].category << _delimiter << movies[i].duration << _delimiter << endl;
        }

        out_file.close();

        return writtenInAvailableSlot;
    }

    // Add new movie to file (append to end of file)
    void add_movie(const Movie& movie)
    {
        ofstream out_file(_db_file.c_str(), ios_base::app);

        out_file << movie.id << _delimiter << movie.title << _delimiter << movie.starcast << _delimiter 
                << movie.director << _delimiter << movie.category << _delimiter << movie.duration << _delimiter << endl;
        out_file.close();
    }

    // Update existing movie
    void update_movie(const Movie& movie)
    {
        vector<Movie> movies = get_movies();
        ofstream out_file(_db_file.c_str(), ios::trunc);

        for (size_t i = 0; i < movies.size(); i++)
        {
            if (movies[i].id == movie.id)
            {
                movies[i].title = movie.title;
                movies[i].starcast = movie.starcast;
                movies[i].director = movie.director;
                movies[i].category = movie.category;
                movies[i].duration = movie.duration;
            }

            out_file << movies[i].id << _delimiter << movies[i].title << _delimiter << movies[i].starcast << _delimiter 
                    << movies[i].director << _delimiter << movies[i].category << _delimiter << movies[i].duration << _delimiter << endl; 
        }

        out_file.close();
    }

    // Remove movie from file by using ID
    void remove_movie(int movie_id)
    {
        if (movie_id == -1)
            return;

        Movie existing_movie = get_movie(movie_id);
        remove_movie(existing_movie);
    }

    // Remove movie from file
    void remove_movie(Movie& movie)
    {
        // Just set '-' to all properties (soft delete)
        movie.title = _empty_data;
        movie.director = _empty_data;
        movie.starcast = _empty_data;
        movie.duration = 0;
        update_movie(movie);
    }
};


// Main code
class Program
{
public:
    void run()
    {
        welcome_message();
        login();
        add_empty_movies();
        MoviesRepository repository(movies_db_file);

        char continue_action = 'Y';
        while (continue_action == 'Y' || continue_action == 'y')
        {
        INPUT_CATEGORY:
            int selected_category = 1;
            string selected_category_name;
            cout << "\nPlease choose a category: " << endl;
            cout << "1. Action" << endl;
            cout << "2. Adventure" << endl;
            cout << "3. Comedy" << endl;
            cin >> selected_category;

            if (cin.fail() || selected_category <= 0 || selected_category >= 4)
            {
                Utils::clear_input();
                Utils::display_error();
                goto INPUT_CATEGORY;
            }
            
        DISPLAY_MOVIES:
            if (selected_category == 1)
            {
                selected_category_name = "Action";
            }
            else if (selected_category == 2)
            {
                selected_category_name = "Adventure";
            }
            else if (selected_category == 3)
            {
                selected_category_name = "Comedy";
            }
            else 
            {
                Utils::clear_input();
                Utils::display_error("Please choice between 1, 2, or 3");
                goto INPUT_CATEGORY;
            }

            vector<Movie> movies = repository.get_movies();
            int movies_count = repository.get_movies_count(selected_category_name);
            display_movies_in_category(selected_category_name, movies_count, movies);

        INPUT_ACTION:
            int selected_action;
            cout << "-----------------------------------------------------" << endl;
            cout << "Pick an action: " << endl;
            cout << "1. Add" << endl;
            cout << "2. Update" << endl;
            cout << "3. Delete" << endl;
            cout << "4. Go to categories menu" << endl;
            cout << "Anything else to leave" << endl;
            cin >> selected_action;

            if (selected_action == 1)
            {
                if (movies_count >= 3)
                {
                    Utils::display_error("Limit already exceeds");
                    goto INPUT_ACTION;
                }

                cout << "\nAdd movie to category \'" << selected_category_name << "\'" << endl;
                Movie movie = Movie::input_movie(selected_category_name);
                repository.add_movie_to_available_slot(movie);
                goto DISPLAY_MOVIES;
            }
            else if (selected_action == 2)
            {
            INPUT_MOVIE_ID:
                int selected_movie_id;
                cout << "\nSelect movie ID to update details: ";
                cin >> selected_movie_id;
                bool exists_movie = repository.exists_movie(selected_movie_id, selected_category_name);

                if (!exists_movie)
                {
                    Utils::clear_input();
                    Utils::display_error("Could not found movie with specified ID, please try again");
                    goto INPUT_MOVIE_ID;
                }
                
                Movie selected_movie = repository.get_movie(selected_movie_id);
                selected_movie.id = selected_movie_id;

                cout << "Selected movie is \'" << selected_movie.title << "\'" << endl;
                cout << "Enter details to update" << endl;

                Movie::edit_movie(selected_movie);
                repository.update_movie(selected_movie);
                goto DISPLAY_MOVIES;
            }
            else if (selected_action == 3)
            {
                int selected_movie_id;
                cout << "\nSelect movie ID to delete: ";
                cin >> selected_movie_id;

                bool exists_movie = repository.exists_movie(selected_movie_id, selected_category_name);
                if (exists_movie)
                {
                    repository.remove_movie(selected_movie_id);
                }
                
                goto DISPLAY_MOVIES;
            }
            else if (selected_action == 4)
            {
                goto INPUT_CATEGORY;
            }
            else
            {
                Utils::quit_program();
            }
            
            cout << "Do you wish to repeat again (Y/N): ";
            cin >> continue_action;
        }
    }

private:
    void welcome_message()
    {
        cout << "******************************************************************************" << endl;
        cout << "*			KERKALA TUPOY Magazin Videos & Records Ltd                        *" << endl;
        cout << "*			108 kerkala, xuynya, Tallin,                                      *" << endl;
        cout << "*			Krasnodar, 101100 Tallin, Estonia.                                *" << endl;
        cout << "*			Contact: +231-4296-0377                                           *" << endl;
        cout << "*			Website: https://suxrobgm.net                                     *" << endl;
        cout << "******************************************************************************" << endl;
    }

    void login()
    {
        // if file does not exist then create file
        if (!Utils::file_exists(credentials_file))
        {
            signup();
        }

        User admin = User::read_from_file(credentials_file);

        // Sign up if file contains empty data
        if (admin.username == "" || admin.username == " " ||
            admin.password == "" || admin.password == " ")
        {
            signup();
        }

    INPUT_DATA:
        User user;
        cout << "\nPlease log in as admin:" << endl;
        cout << "Username: " << endl;
        cin >> user.username;
        cout << "Password: " << endl;
        cin >> user.password;

        if (user.username != admin.username ||
            user.password != admin.password)
        {
            Utils::clear_input();
            Utils::display_error("Incorrect login, please check username or password");
            goto INPUT_DATA;
        }
        
        cout << "Welcome, " << user.username << " (admin)" << endl;
    }

    void signup()
    {
        User user;
        cout << "Please set admin username: " << endl;
        cin >> user.username;
        cout << "Please set admin password: " << endl;
        cin >> user.password;

        user.save_to_file(credentials_file);
        login();
    }

    void display_movies_in_category(string category_name, int movies_count, vector<Movie> movies)
    {
        cout << "\nNumber of movies in this category: " << movies_count << endl;
        cout << "Maximum Limit: 3" << endl << endl;

        for (size_t i = 0; i < movies.size(); i++)
        {
            if (movies[i].category == category_name)
            {
                cout << "-----------------------------------------------------" << endl;
                cout << movies[i].to_string() << endl;
            }
        }
    }

    // Add empty 9 records to the file 
    void add_empty_movies()
    {
        MoviesRepository repository(movies_db_file);

        if (!Utils::file_exists(movies_db_file))
        {
            for (size_t i = 1; i <= 9; i++)
            {
                Movie movie;
                movie.id = i;

                // From 1 to 3 set category to Action
                if (i >= 1 && i <= 3)
                {
                    movie.category = "Action";
                }
                else if (i >= 4 && i <= 6)
                {
                    movie.category = "Adventure";
                }
                else 
                {
                    movie.category = "Comedy";
                }
                
                repository.add_movie(movie);
            }
        }
    }
};

int main()
{
    Program program;
    program.run();

    system("pause");
    return 0;
}