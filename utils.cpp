
#include "utils.h"

using namespace std;

Employee emp1("Alice", 50000.0);
Employee emp2("Bob", 60000.0);
Employee emp3("Charlie", 55000.0);
Employee emp4("David", 58000.0);

bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

int nextPrime( int n )
{
    if( n % 2 == 0 )
        ++n;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

string generateARandomName(int length) {
    static const std::string allowedChars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    random_device rd;
    mt19937 generator(rd()); 
    uniform_int_distribution<int> distribution(0, allowedChars.size() - 1);

    string name;
    for (int i = 0; i < length; ++i) {
        name += allowedChars[distribution(generator)];
    }
    return name;
}

vector<string> generateRandomNames(int numNames) {
    int stringLength = 10;
    vector<string> strings;
    for (int i = 0; i < numNames; i++)
        strings.push_back( generateARandomName(stringLength) );
    return strings;
}


int generateARandomInteger(int MAXNUM) {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<std::mt19937::result_type> dist6(1, MAXNUM); 

    return dist6(rng);
}

vector<int> generateRandomIntegers(int numNumbers) {
    int MAXNUM = 100000000;
    vector<int> numbers;
    for (int i=0; i < numNumbers; i++)
        numbers.push_back( generateARandomInteger(MAXNUM) );
    return numbers;
}
