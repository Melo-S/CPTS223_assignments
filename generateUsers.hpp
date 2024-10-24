#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <fstream>
#include <sstream> 

using namespace std;

// randomly generate a string (given a vocabulary and the length of the generated string)
string randomString(const string& chars, int length) {
    string result;
    for (int i = 0; i < length; ++i) {
        result += chars[rand() % chars.size()];
    }
    return result;
}

// randomly generate names (all lower cases)
string randomName() {
    const string chars = "abcdefghijklmnopqrstuvwxyz";
    string name = randomString(chars, rand() % 6 + 3); // length == [3, 8]
    return name;
}

// randomly generate emails
string randomEmail(const string& first, const string& last) {
    const vector<string> domains = { "gmail.com", "yahoo.com", "outlook.com", "example.com" };
    return first + "." + last + "@" + domains[rand() % domains.size()];
}

// randomly generate categories
string randomCategory() {
    const vector<string> categories = { "Technology", "Sports", "Music", "Food", "Travel", "Education" };
    return categories[rand() % categories.size()];
}

struct User {
    string userName;
    string lastName;
    string firstName;
    string email;
    int numPosts;
    string mostViewedCategory;
};

void printAUser(User aUser) {
    cout << aUser.userName
          << "," << aUser.lastName
          << "," << aUser.firstName
          << "," << aUser.email
          << "," << aUser.numPosts
          << "," << aUser.mostViewedCategory
          << endl;
}

void printUsers(vector<User> users) {
    for (const auto& user : users) 
        printAUser(user);
}


vector<User> readCSV(const string& fileName) {
    vector<User> users;
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Unable to open file: " << fileName << endl;
        return users; // return an empty vector if not openning
    }

    string line;

    // read each line from csv
    while (getline(file, line)) {
        stringstream ss(line);
        string userName, lastName, firstName, email, numPostsStr, mostViewedCategory;
        User user;

        // read each part
        getline(ss, userName, ',');
        getline(ss, lastName, ',');
        getline(ss, firstName, ',');
        getline(ss, email, ',');
        getline(ss, numPostsStr, ',');
        getline(ss, mostViewedCategory, ',');

        user.userName = userName;
        user.lastName = lastName;
        user.firstName = firstName;
        user.email = email;
        user.numPosts = stoi(numPostsStr); 
        user.mostViewedCategory = mostViewedCategory;

        // push back to the users vector
        users.push_back(user);
    }

    file.close();
    return users;
}

vector<User> generateUsers(int n) {
    srand(time(0)); // set a random seed
    vector<User> users = readCSV("C:/Users/Phoni/iCloudDrive/Documents/WSU 24-25/CPTS_223/MA3/existingData.csv");
    int numExist = users.size();
    for (int i = 0; i < n - numExist; ++i) {
        User user;
        user.firstName = randomName();
        user.lastName = randomName();
        user.userName = randomName() + "_" + user.firstName + user.lastName + to_string(rand() % 100);
        user.email = randomEmail(user.firstName, user.lastName);
        user.numPosts = rand() % 1000; // # of twitts: 0 - 999
        user.mostViewedCategory = randomCategory();
        user.firstName[0] = toupper(user.firstName[0]);
        user.lastName[0] = toupper(user.lastName[0]);
        users.push_back(user);
    }

    return users;
}