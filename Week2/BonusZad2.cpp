#include<iostream>
#include<cstring>
#include<fstream>

enum class ErrorInCatalog {
    catalog_not_open,
    read_from_empty_catalog,
    movie_not_in_catalog,
    no_error_occurred
};

struct SafeAnswer {
    int number=0;
    ErrorInCatalog error;
};

struct Movie {
    char name[128];
    unsigned int price;
};
bool isEmpty(const char* catalogName)
{
    std::ifstream in(catalogName);
    if (!in.is_open())
    {
        return true;
    }

    in.get();
    return in.eof();
}
SafeAnswer getNumberOfMovies(const char* catalogName) {
    SafeAnswer answer;
    std::ifstream in(catalogName);
    if (!in.is_open())
    {
        return { 0,ErrorInCatalog::catalog_not_open };
    }
    
    if (isEmpty(catalogName)) 
    {
        return { 0,ErrorInCatalog::read_from_empty_catalog };
    }
    
    char buffer[1024];
   
   
    while (!in.eof())
    {
        in.getline(buffer, 1024);
        answer.number++;
        
    }
    answer.error = ErrorInCatalog::no_error_occurred;
    return answer;
}

SafeAnswer averagePrice(const char* catalogName) {
    SafeAnswer answer = getNumberOfMovies(catalogName);
    if (answer.error != ErrorInCatalog::no_error_occurred)
    {
        return answer;
    }
    std::ifstream in(catalogName);
    if (!in.is_open())
    {
        return { 0,ErrorInCatalog::catalog_not_open };
    }

    if (isEmpty(catalogName))
    {
        return { 0,ErrorInCatalog::read_from_empty_catalog };
    }
    double averagePrice = 0.0;
    unsigned int currentPrice;
    char title[1024];

    for (int i = 0; i < answer.number; i++)
    {
        in >> title;
        in >> currentPrice;
        averagePrice += currentPrice;
    }
    
    answer.number = (int) averagePrice / answer.number;
    return answer;

}

SafeAnswer getMoviePrice(const char* catalogName, const char* movieName) {
    SafeAnswer answer = getNumberOfMovies(catalogName);
    if (answer.error != ErrorInCatalog::no_error_occurred)
    {
        return answer;
    }
    std::ifstream in(catalogName);
    if (!in.is_open())
    {
        return { 0,ErrorInCatalog::catalog_not_open };
    }

    if (isEmpty(catalogName))
    {
        return { 0,ErrorInCatalog::read_from_empty_catalog };
    }
    char title[1024];
    unsigned int currentPrice;
    for (int i = 0; i < answer.number; i++)
    {
        in >> title;
        in >> currentPrice;
        if (strcmp(movieName,title)==0) {
            answer.number = currentPrice;
            return answer;
        }
       
    }
    answer.error = ErrorInCatalog::movie_not_in_catalog;
    return answer;
    
}

Movie readMovie(std::ifstream& file) {
    //добавете аргумент - файлов поток за четене
    Movie movie;
    char title[128];
    file >> title;
    file >> movie.price;
    strcpy(movie.name, title);

    return movie;
}

Movie* saveMoviesInArray(std::ifstream& file, int numberOfMovies) {
    Movie* movies = new Movie[numberOfMovies];
    for (int i = 0; i < numberOfMovies; i++)
    {
        movies[i] = readMovie(file);
    }
    return movies;
}

void freeMoviesFromArray(Movie* movies) {
    // добавете нужните аргументи
    delete[] movies;
}


void sortMoviesInArray(Movie* movies, int numberOfMovies) { // добавете нужните аргументи
    for (int i = 0; i < numberOfMovies - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < numberOfMovies; j++)
        {
            if (movies[j].price < movies[minIndex].price)
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
        {
            std::swap(movies[i], movies[minIndex]);
        }
    }
}

ErrorInCatalog saveMoviesSorted(const char* catalogName, const char* catalogSortedName) {
    // Ако файл, отворен с файлов поток за писане, не съществува, то той се създава
    SafeAnswer safeanswer;
    std::ofstream out(catalogSortedName);
    std::ifstream in(catalogName);
    if (!out.is_open() || !in.is_open())
    {
        return ErrorInCatalog::catalog_not_open;
    }
    if (isEmpty(catalogName))
    {
        return ErrorInCatalog::read_from_empty_catalog;
    }
    // Първо намерете колко филма има във файла с име catalogName
    safeanswer =getNumberOfMovies(catalogName);
    if (safeanswer.error != ErrorInCatalog::no_error_occurred)
    {
        return safeanswer.error;
    }
    Movie* movies = saveMoviesInArray(in, safeanswer.number);
    sortMoviesInArray(movies, safeanswer.number);
    for (int i = 0; i < safeanswer.number; i++)
    {
        out << movies[i].name << " " << movies[i].price<<std::endl;
    }
    freeMoviesFromArray(movies);
    // след това продължете с имплементацията на функцията

    // Погледнете примера за писане във файл
    return ErrorInCatalog::no_error_occurred;
}

int main() {
    SafeAnswer safeNumberOfMovies = getNumberOfMovies("movieCatalog.txt");
    if (safeNumberOfMovies.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The number of movies is: " << safeNumberOfMovies.number << std::endl;
    }
    SafeAnswer safeAveragePrice = averagePrice("movieCatalog.txt");
    if (safeAveragePrice.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The average price is: " << safeAveragePrice.number << std::endl;
    }

    SafeAnswer safePrice = getMoviePrice("movieCatalog.txt", "Black-bullet");
    if (safePrice.error == ErrorInCatalog::no_error_occurred) {
        std::cout << "The price for the Black bullet movies is: " << safePrice.number << std::endl;
    }

    ErrorInCatalog errorSorting = saveMoviesSorted("movieCatalog.txt", "movieCatalogSorted.txt");
    if (errorSorting == ErrorInCatalog::no_error_occurred) {
        std::cout << "Look the content of the movieCatalogSorted.txt file" << std::endl;
    }
}
