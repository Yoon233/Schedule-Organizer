#include <iostream>
#include <ctime>
#include <chrono> // Time management
#include <thread> // 
#include <string> 
#include <fstream> // File handling

using namespace std;

void clear(void) {
  int result;
  
  #ifdef _WIN32
    result = system("clear");
    if (result != 0) {
        // Handle the error, e.g., print an error message
        std::cerr << "Error clearing the screen." << std::endl;
    }
  
  #elif __APPLE__
  result = system("clear");
  if (result != 0) {
      // Handle the error, e.g., print an error message
      std::cerr << "Error clearing the screen." << std::endl;
  }
  
  #elif __linux__
  result = system("clear");
  if (result != 0) {
      // Handle the error, e.g., print an error message
      std::cerr << "Error clearing the screen." << std::endl;
  }
  #endif
}

std::tm* CheckTime() {

  auto now = std::chrono::system_clock::now(); 
  std::time_t time_t = std::chrono::system_clock::to_time_t(now);
  std::tm* time_info = std::localtime(&time_t);

  std::cout << "Year: " << (1900 + time_info->tm_year) << std::endl; 
  std::cout << "Month: " << (1 + time_info->tm_mon) << std::endl;
  std::cout << "Day: " << time_info->tm_mday << std::endl;
  std::cout << "Hour: " << time_info->tm_hour << std::endl;
  std::cout << "Minute: " << time_info->tm_min << std::endl;
  std::cout << "Second: " << time_info->tm_sec << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(5)); // Wait for 5 seconds

  return(time_info);
}

class occation {
public :
  int createOccation() {
    cin >> occationName;
    cout << "Date of Occation (Format : 12232024) : ";
    cin >> occationDate;
    string fileName = occationName + ".txt";
    std::ofstream outFile(fileName);
    if(outFile.is_open()) {
      outFile << occationName << endl;
      outFile.close();
      return 0;
    }
    return 1;
  }
  int selectOccation();
  int deleteOccation();
private : 
  std::string occationName;
  char occationDate[9];
  
}

int main() {
  while(true) {
    clear();
    std::cout << "\t[Event Calendar]\n";
    std::cout << "\t1. Today's' Information\n";
    std::cout << "\t2. Check Occasions \n";
    std::cout << "\t3. Exit Event Calendar\n\n";
    std::cout << "\tEnter a number." << std::endl;

    int option = 0;
    std::cin >> option;
    getchar();
  
    switch(option){
      std::tm* time_info;
      case 1:
        clear();
        std::cout << "\t[Today's' Information]" << std::endl;
        time_info= CheckTime();
        break;
      
      case 2:
        clear();
        std::cout << "\t[Check Occations]" << std::endl;
        
        break;
      
      case 3:
        return(0);
        break;
  
      default:
        printf("Invalid option, try again.\n");
    }
  }
}