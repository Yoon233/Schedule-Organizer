#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <chrono> // Time management 
#include <thread> 
#include <string> 
#include <fstream> // File handling headerFile
#include <cstring>
#include <sstream>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#elif __linux__ || __APPLE__
#include <dirent.h>
#endif

using namespace std;

void sleepSecond(const int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

string extractDateFromFile(const string& filePath) {
    ifstream inFile(filePath);
    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << filePath << endl;
        return "";
    }

    string name, date;
    getline(inFile, name);
    getline(inFile, date);
    inFile.close();
    return date;
}

void clear(void) {
    int result;

    #ifdef _WIN32
        result = system("cls");  // Use "cls" on Windows
    #else
        result = system("clear");
    #endif

    if (result != 0) {
        cout << "Error clearing the screen." << endl;
    }
}

tm* CheckTime() {
    auto now = chrono::system_clock::now(); 
    time_t time_t = chrono::system_clock::to_time_t(now);
    tm* time_info = localtime(&time_t);

    time_info->tm_year += 1900;
    time_info->tm_mon += 1;

    return time_info;
}

void getDateSuffix (string* dateSuffix, tm* time_info) {
    int dateTenth = time_info->tm_mday / 10;
    int dateOneth = time_info->tm_mday % 10;
    if (dateTenth == 1 || dateOneth != 1 || dateOneth != 2 || dateOneth != 3) *dateSuffix = "th";
    else if (dateOneth == 1) *dateSuffix = "st";
    else if (dateOneth == 2) *dateSuffix = "nd";
    else if (dateOneth == 3) *dateSuffix = "rd";
    else *dateSuffix = "Error: no suffix";
}

int createOccation() {
    string occationName;
    string occationDate;
    string occationDetail;
    string occationTime;

    cin.ignore(); // Preventing the reading leftover letters in input buffer
    cout << "Enter Occation Name : ";
    getline(cin, occationName);
    cout << "Date of Occation (Format : YYYYMMDD) : ";
    getline(cin, occationDate);
    string fileName = "Occation/" + occationName + ".txt";

    ofstream outFile(fileName);
    if (outFile.is_open()) {
        outFile << occationName << endl;
        outFile << occationDate << endl;
        outFile << occationDetail << endl;
        outFile << occationTime << endl;
        outFile.close();
        return 0;
    }
    cerr << "Error creating the occasion file." << endl;
    return 1;
}

vector<pair<string, string>> occationReading(vector<pair<string, string>>& fileDatePairs) {
      // Pair of filename and date

#ifdef _WIN32
    WIN32_FIND_DATA fileData;
    HANDLE hFind;

    std::string searchPath = "Occation\\*" + fileDatePairs[] + ".txt";
    hFind = FindFirstFile(searchPath.c_str(), &fileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Could not open directory " << std::endl;
        return fileDatePairs;
    }

    do {
        if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::string fileName = fileData.cFileName;
            std::string filePath = "Occation\\" + fileName;
            std::string fileDate = extractDateFromFile(filePath);
            if (!fileDate.empty()) {
                fileDatePairs.emplace_back(fileName, fileDate);
            }
        }
    } while (FindNextFile(hFind, &fileData) != 0);

    FindClose(hFind);

#elif __linux__ || __APPLE__
    DIR* dir;
    struct dirent* entry;

    dir = opendir("Occation");
    if (dir == nullptr) {
        std::cerr << "Error: Could not open directory " << "Occation" << std::endl;
        return fileDatePairs;
    }

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG && std::strstr(entry->d_name, ".txt")) {
            std::string fileName = entry->d_name;
            std::string filePath = "Occation/" + fileName;
            std::string fileDate = extractDateFromFile(filePath);
            if (!fileDate.empty()) {
                fileDatePairs.emplace_back(fileName, fileDate);
            }
        }
    }

    closedir(dir);
#endif

    // Sort the vector by date
    std::sort(fileDatePairs.begin(), fileDatePairs.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    return fileDatePairs;
}

void occationListingOutput(vector<pair<string, string>>& fileDatePairs) {
    int count = 1;
    for (const auto& pair : fileDatePairs) {
        cout << count++ << ". " << pair.first << " (Date: " << pair.second << ")\n";
    }

}

int main() {
    tm* time_info;
    time_info = CheckTime();

    string monthInfo;
    switch (time_info->tm_mon) {
        case 1: monthInfo = "Jan"; break;
        case 2: monthInfo = "Feb"; break;
        case 3: monthInfo = "Mar"; break;
        case 4: monthInfo = "Apr"; break;
        case 5: monthInfo = "May"; break;
        case 6: monthInfo = "Jun"; break;
        case 7: monthInfo = "Jul"; break;
        case 8: monthInfo = "Aug"; break;
        case 9: monthInfo = "Sep"; break;
        case 10: monthInfo = "Oct"; break;
        case 11: monthInfo = "Nov"; break;
        case 12: monthInfo = "Dec"; break;
        default: monthInfo = "Invalid month"; break;
    }

    string dateSuffix;
    getDateSuffix(&dateSuffix, time_info);

    while (true) {
        clear();
        cout << endl;
        vector<pair<string, string>> fileDatePairs;
        fileDatePairs.clear();
        occationReading(fileDatePairs);
        
        cout << "\t[Schedule Organizer]\n";
        cout << "\t" << monthInfo << " " << time_info->tm_mday << dateSuffix << " " << time_info->tm_year << endl;
        cout << "\t1. Check Occasions \n";
        cout << "\t2. Exit Event Calendar\n\n";
        cout << "Enter a number : ";

        int option = 0;
        int deleteFileOption = 0;
        string NewOccationDate;
        string NewOccationName;
        cin >> option;

        switch (option) {
            case 1:
                clear();
                cout << "\t[Check Occations]\n";
                occationListingOutput(fileDatePairs);
                cout << "\t1. Add Occasions \n";
                cout << "\t2. Delete Occasions\n";
                cout << "\t3. Edit Occasions\n";
                cout << "\t4. Exit\n\n";
                cout << "Enter a number : ";
                option = 0;
                cin >> option;

                switch (option)
                {
                    case 1:
                    clear();
                    if(createOccation() != 0 ) cout << "Failed to make an Occation File.\n";
                    break;
                    
                    case 2:
                    clear();
                    occationListingOutput(fileDatePairs);
                    cout << "What occations do you want to delete? Please Select the number : ";
                    cin >> deleteFileOption;
                    deleteFileOption -= 1;
                    while(true){
                        clear();
                        char optionYN;
                        cout << "Do you really want to delete '" << fileDatePairs[deleteFileOption].first << "'?\n";
                        cout << "Delete for Y or Back to lobby for N : ";
                        cin >> optionYN;
                        cout << endl;
                        if (optionYN == 'Y')
                        {
                            ::remove(("Occation/" + fileDatePairs[deleteFileOption].first).c_str());
                            cout << fileDatePairs[deleteFileOption].first << " is now Deleted.";
                            sleepSecond(5);
                            break;
                        }
                        else if(optionYN == 'N')
                        {
                            cout << fileDatePairs[deleteFileOption].first << ", Deleting Canceled.";
                            sleepSecond(5);
                            break;
                        }
                        else {
                            cout << "Wrong Input. Please Eneter Y or N.";
                            sleepSecond(5);
                        }
                    }
                    break;

                    case 3:
                        clear();
                        occationListingOutput(fileDatePairs);
                        cout << "What occations do you want to edit? Please Select the number : ";
                        cin >> deleteFileOption;
                        deleteFileOption -= 1;
                        cout << "What information do you want to edit from " << fileDatePairs[deleteFileOption].first << "?" << endl;
                        cout << "1. Name of Occation" << endl;
                        cout << "2. Date of Occation" << endl;
                        cout << "Please Select the Number : ";

                        int option;
                        cin >> option;
                        switch (option) {
                        case 1:
                            cout << "Change the name of " << fileDatePairs[deleteFileOption].first << " into : ";
                            cin >> NewOccationName;
                            break;

                        case 2:
                            cout << "Change the Date of "<< fileDatePairs[deleteFileOption].first <<", " << fileDatePairs[deleteFileOption].second << " into : ";
                            break;
                        }
                        while(true){
                            clear();
                            char optionYN;
                            cout << "Do you really want to save your changes of '" << fileDatePairs[deleteFileOption].first << "'?\n";
                            cout << "Save for Y or Back to lobby for N : ";
                            cin >> optionYN;
                            cout << endl;
                            if (optionYN == 'Y')
                            {

                                ofstream outFile("Occation/" + fileDatePairs[deleteFileOption].first);
                                if (outFile.is_open()) {
                                    outFile << NewOccationName << endl;
                                    outFile << NewOccationDate << endl;
                                    outFile.close();
                                }
                                cout << fileDatePairs[deleteFileOption].first << " is Saved.";
                                sleepSecond(5);
                                break;
                            }
                            else if(optionYN == 'N')
                            {
                                cout << fileDatePairs[deleteFileOption].first << ", Editing Canceled.";
                                sleepSecond(5);
                                break;
                            }
                            else {
                                cout << "Wrong Input. Please Eneter Y or N.";
                                sleepSecond(5);
                            }
                        }
                    break;

                    case 4:
                        clear();
                    break;

                }
            break;
            
            case 2:
                clear();
                return 0;

            default:
                cout << "Invalid option, try again.\n";
                break;
        }
    }
}
