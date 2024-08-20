#include <iostream>
#include <ctime>
#include <chrono> // Time management 
#include <thread> 
#include <string> 
#include <fstream> // File handling headerFile

using namespace std;

void clear(void) {
  int result;
  
  #ifdef _WIN32
    result = system("clear");
    if (result != 0) {
        // Handle the error, e.g., print an error message
        cerr << "Error clearing the screen." << endl;
    }
  
  #elif __APPLE__
  result = system("clear");
  if (result != 0) {
      // Handle the error, e.g., print an error message
      cerr << "Error clearing the screen." << endl;
  }
  
  #elif __linux__
  result = system("clear");
  if (result != 0) {
      // Handle the error, e.g., print an error message
      cerr << "Error clearing the screen." << endl;
  }
  #endif
}

tm* CheckTime() {

  auto now = chrono::system_clock::now(); 
  time_t time_t = chrono::system_clock::to_time_t(now);
  tm* time_info = localtime(&time_t);

  time_info->tm_year += 1900;
  time_info->tm_mon += 1;

  return(time_info);
};

void getDateSuffix (string* dateSuffix, tm* time_info) {
  int dateTenth = time_info->tm_mday / 10;
  int dateOneth = time_info->tm_mday % 10;
  if( dateTenth == 1 || dateOneth != 1 || dateOneth != 2 || dateOneth != 3) *dateSuffix = "th";
  else if ( dateOneth == 1 ) *dateSuffix = "st" ;
  else if ( dateOneth == 2 ) *dateSuffix = "th" ;
  else if ( dateOneth == 3 ) *dateSuffix = "rd" ;
  else *dateSuffix = "Error : no suffix";
};

class occation {
public :
  int createOccation() {
    cin.ignore(); // preventing the reading leftover letters in input buffer
    getline(cin, occationName);
    cout << "Date of Occation (Format : 12232024) : ";
    getline(cin, occationDate);
    string fileName = "Occation/" + occationName + ".txt";
    ofstream outFile(fileName);
    if(outFile.is_open()) {
      outFile << occationName << endl;
      outFile << occationDate << endl;
      outFile << occationDetail << endl;
      outFile << occationTime << endl;
      outFile.close();
      return 0;
    }
    return 1;
  }
private : 
  string occationName;
  string occationDate;
  string occationDetail;
  string occationTime;
};

int occationList() {
  return 0;
}

int main() {
  
  tm* time_info;
  time_info= CheckTime();

  string monthInfo;
  switch (time_info->tm_mon) {
      case 1:
          monthInfo = "Jan";
          break;
      case 2:
          monthInfo = "Feb";
          break;
      case 3:
          monthInfo = "Mar";
          break;
      case 4:
          monthInfo = "Apr";
          break;
      case 5:
          monthInfo = "May";
          break;
      case 6:
          monthInfo = "Jun";
          break;
      case 7:
          monthInfo = "Jul";
          break;
      case 8:
          monthInfo = "Aug";
          break;
      case 9:
          monthInfo = "Sep";
          break;
      case 10:
          monthInfo = "Oct";
          break;
      case 11:
          monthInfo = "Nov";
          break;
      case 12:
          monthInfo = "Dec";
          break;
      default:
          monthInfo = "Invalid month";
          break;
  }

  string dateSuffix;
  getDateSuffix( &dateSuffix, time_info);

  while(true) {
    clear();
    cout << "\t[Schedule Organizer]\n";
    cout << "\t" << monthInfo << " " << time_info->tm_mday << dateSuffix << " " << time_info->tm_year << endl;
    cout << "\t1. Check Occasions \n";
    cout << "\t2. Exit Event Calendar\n\n";
    cout << "\tEnter a number." << endl;

    int option = 0;
    cin >> option;
  
    switch(option){
      case 1:
        clear();
        cout << "\t[Check Occations]" << endl;
        occationList();
        cout << "\t1. Add Occasions \n";
        cout << "\t2. Delete Occations\n";
        cout << "\t3. Edit Occations\n";
        cout << "\t4. Exit\n\n";
        cout << "\tEnter a number." << endl;
        option = 0;
        cin >> option;
        
        switch(option){
            case 1:
            
        }
        
        break;
      
      case 2:
        clear();
        return(0);
      
      default:
        printf("Invalid option, try again.\n");
    }
  }
}