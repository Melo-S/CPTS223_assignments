#include <map>
#include "generateUsers.hpp"
using namespace std;


map<string, User> buildMapByUserName(vector<User> users) {
    map<string, User> usersMap;

    for (const auto& user : users) {
        usersMap[user.userName] = user;
    }

    return usersMap;
}


map<string, User> buildMapByEmail(vector<User> users) {
    map<string, User> usersMap;

    for (const auto& user : users) {
        usersMap[user.email] = user;
    }

    return usersMap;
}


void printMap(const map<string, User>& aMap) {
    for (const auto& pair : aMap) {
        cout << "Key: " << pair.first << endl;
        printAUser(pair.second);
        cout << endl;
    }
}


bool isMapSorted(const map<string, User>& aMap) {
    if (aMap.empty()) return true;

    auto it = aMap.begin();
    string prevKey = it->first;
    ++it;

    for (; it != aMap.end(); ++it) {
        if (it->first < prevKey) {
            return false;
        }
        prevKey = it->first;
    }

    return true;
}


bool testSearchByKey(const map<string, User>& aMap, const string& keyToSearch) {
    return aMap.find(keyToSearch) != aMap.end();
}


bool testDeleteByKey(map<string, User>& aMap, const string& keyToDelete) {
    return aMap.erase(keyToDelete) > 0;
}


void printActiveUsers(const map<string, User>& aMap) {
    int activeThreshold = 800;
    for (const auto& pair : aMap) {
        if (pair.second.numPosts > activeThreshold) {
            cout << pair.second.userName << endl;
        }
    }
}


void printMostPopularCategory(const map<string, User>& aMap) {
    map<string, int> categoryCounts;
    for (const auto& pair : aMap) {
        categoryCounts[pair.second.mostViewedCategory]++;
    }

    string mostPopularCategory;
    int maxCount = 0;
    for (const auto& categoryPair : categoryCounts) {
        if (categoryPair.second > maxCount) {
            maxCount = categoryPair.second;
            mostPopularCategory = categoryPair.first;
        }
    }

    cout << "Most popular category: " << mostPopularCategory << endl;
}


int main()
{
    int numUsers = 10;
    vector<User> users = generateUsers(numUsers);


    cout << "Build map with username as key" << endl;
    map<string, User> mapByUserName = buildMapByUserName(users);
    if ( mapByUserName.size() == numUsers )
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;


    cout << "Print \"mapByUserName\" map:" << endl;
    printMap(mapByUserName);
    cout << endl;


    string keyToSearch = "smith55";
    cout << "Search by key: mapByUserName[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByUserName, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    string keyToDelete = "smith55";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByUserName, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    cout << "Test if map's key is sorted" << endl;
    if ( isMapSorted(mapByUserName) )
        cout << "  Order test passed!" << endl << endl;
    else
        cout << "  Order test failed!" << endl << endl;


    cout << "Print usernames with more than 800 tweets:" << endl;
    printActiveUsers(mapByUserName);
    cout << endl;

    cout << "Print the most popular category" << endl;
    printMostPopularCategory(mapByUserName);
    cout << endl;


    cout << " ============================================================================== " << endl << endl;


    cout << "Build map with username as key" << endl;
    map<string, User> mapByEmail = buildMapByEmail(users);
    if ( mapByEmail.size() == numUsers )
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;
    

    keyToSearch = "kat@gmail.com";
    cout << "Search by key: mapByEmail[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByEmail, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    keyToDelete = "kat@gmail.com";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByEmail, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    return 0;
}