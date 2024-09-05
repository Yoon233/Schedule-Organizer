#include <iostream>
#include <ctime>
#include <chrono> // Time management 
#include <thread> 
#include <string> 
#include <fstream> // File handling headerFile
#include <cstring>

#ifdef _WIN32
#include <windows.h>
#elif __linux__ || __APPLE__
#include <dirent.h>
#endif

using namespace std;

void clear(void) {
    int result;

    #ifdef _WIN32
        result = system("cls");  // Use "cls" on Windows
    #else
        result = system("clear");
    #endif

    if (result != 0) {
        cerr << "Error clearing the screen." << endl;
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
    cout << "Enter Occation Name: ";
    getline(cin, occationName);
    cout << "Date of Occation (Format : 12232024) : ";
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

void occationList(const std::string& folderPath) {
#ifdef _WIN32
    WIN32_FIND_DATA fileData;
    HANDLE hFind;

    std::string searchPath = folderPath + "\\*.txt";  // Windows-style path
    hFind = FindFirstFile(searchPath.c_str(), &fileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Could not open directory " << folderPath << std::endl;
        return;
    }

    std::cout << "Occasions stored in folder '" << folderPath << "':\n";

    do {
        if (!(fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            std::cout << "- " << fileData.cFileName << std::endl;
        }
    } while (FindNextFile(hFind, &fileData) != 0);

    FindClose(hFind);

#elif __linux__ || __APPLE__
    DIR* dir;
    struct dirent* entry;

    dir = opendir(folderPath.c_str());
    if (dir == nullptr) {
        std::cerr << "Error: Could not open directory " << folderPath << std::endl;
        return;
    }

    std::cout << "Occasions stored in folder '" << folderPath << "':\n";

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_type == DT_REG && std::strstr(entry->d_name, ".txt")) {
            std::cout << "- " << entry->d_name << std::endl;
        }
    }

    closedir(dir);
#endif
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
        cout << "\t[Schedule Organizer]\n";
        cout << "\t" << monthInfo << " " << time_info->tm_mday << dateSuffix << " " << time_info->tm_year << endl;
        cout << "\t1. Check Occasions \n";
        cout << "\t2. Exit Event Calendar\n\n";
        cout << "\tEnter a number." << endl;

        int option = 0;
        cin >> option;

        switch (option) {
            case 1:
                clear();
                cout << "\t[Check Occations]\n";
                occationList();
                cout << "\t1. Add Occasions \n";
                cout << "\t2. Delete Occasions\n";
                cout << "\t3. Edit Occasions\n";
                cout << "\t4. Exit\n\n";
                cout << "\tEnter a number." << endl;
                option = 0;
                cin >> option;

                if (option == 1) {
                    createOccation();
                }

                break;

            case 2:
                clear();
                return 0;

            default:
                cout << "Invalid option, try again.\n";
        }
    }
}
