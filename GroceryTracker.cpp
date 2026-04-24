#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

// Class to handle grocery item tracking functionality
class GroceryTracker {
private:
    map<string, int> itemFrequency;  // Stores item names and their frequencies
    
    // Helper function to convert string to lowercase for case-insensitive comparison
    string toLowerCase(const string& str) {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }
    
    // Helper function to trim whitespace from string
    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\n\r");
        size_t last = str.find_last_not_of(" \t\n\r");
        if (first == string::npos || last == string::npos) {
            return "";
        }
        return str.substr(first, last - first + 1);
    }
    
public:
    // Constructor - reads input file and populates frequency map
    GroceryTracker(const string& filename) {
        loadData(filename);
    }
    
    // Load and process the input file
    void loadData(const string& filename) {
    cout << "Attempting to open: " << filename << endl;
    
    ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        cerr << "Current working directory: ";
        system("cd");  // Windows command to show current directory
        return;
    }
        
        string item;
        // Read each line (each item purchased)
        while (getline(inputFile, item)) {
            item = trim(item);
            if (!item.empty()) {
                // Use case-insensitive storage - store in lowercase for consistency
                string lowerItem = toLowerCase(item);
                itemFrequency[lowerItem]++;
            }
        }
        
        inputFile.close();
        
        // Create backup data file
        createBackupFile("frequency.dat");
    }
    
    // Option 1: Display frequency of a specific item
    int getItemFrequency(const string& itemName) {
        string searchItem = toLowerCase(trim(itemName));
        if (itemFrequency.find(searchItem) != itemFrequency.end()) {
            return itemFrequency[searchItem];
        }
        return 0;  // Return 0 if item not found
    }
    
    // Option 2: Display all items with their frequencies
    void displayAllFrequencies() {
        cout << "\n=== COMPLETE FREQUENCY LIST ===\n";
        cout << "Item\t\t\tFrequency\n";
        cout << "--------------------------------\n";
        
        for (const auto& pair : itemFrequency) {
            // Format output with consistent spacing
            printf("%-20s %d\n", pair.first.c_str(), pair.second);
        }
        cout << endl;
    }
    
    // Option 3: Display histogram (visual representation)
    void displayHistogram() {
        cout << "\n=== FREQUENCY HISTOGRAM ===\n";
        cout << "Each * represents one purchase\n";
        cout << "--------------------------------\n";
        
        for (const auto& pair : itemFrequency) {
            cout << pair.first << " ";
            // Print asterisks equal to frequency
            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }
            cout << " (" << pair.second << ")" << endl;
        }
        cout << endl;
    }
    
    // Create backup file with all frequency data
    void createBackupFile(const string& backupFilename) {
        ofstream backupFile(backupFilename);
        
        if (!backupFile.is_open()) {
            cerr << "Error: Could not create backup file " << backupFilename << endl;
            return;
        }
        
        // Write each item and its frequency to the backup file
        for (const auto& pair : itemFrequency) {
            backupFile << pair.first << " " << pair.second << endl;
        }
        
        backupFile.close();
        cout << "Backup file '" << backupFilename << "' created successfully.\n";
    }
};

// Function to display the main menu
void displayMenu() {
    cout << "\n====================================\n";
    cout << "    CORNER GROCER ITEM TRACKER\n";
    cout << "====================================\n";
    cout << "1. Search for a specific item\n";
    cout << "2. Display all item frequencies\n";
    cout << "3. Display frequency histogram\n";
    cout << "4. Exit program\n";
    cout << "====================================\n";
    cout << "Enter your choice (1-4): ";
}

// Input validation for menu choice
int getValidMenuChoice() {
    int choice;
    while (true) {
        cin >> choice;
        
        // Check for input failure (non-integer input)
        if (cin.fail()) {
            cin.clear();  // Clear error flags
            cin.ignore(10000, '\n');  // Discard invalid input
            cout << "Invalid input! Please enter a number (1-4): ";
            continue;
        }
        
        // Check if choice is within valid range
        if (choice >= 1 && choice <= 4) {
            break;
        } else {
            cout << "Please enter a valid choice (1-4): ";
        }
    }
    return choice;
}

int main() {
    const string INPUT_FILENAME = "CS210_Project_Three_Input_File.txt";
    
    cout << "Welcome to the Corner Grocer Item Tracking System!\n";
    cout << "Loading grocery data...\n";
    
    // Create GroceryTracker object (automatically loads data and creates backup)
    GroceryTracker tracker(INPUT_FILENAME);
    
    int choice;
    string searchItem;
    
    // Main program loop
    do {
        displayMenu();
        choice = getValidMenuChoice();
        
        switch (choice) {
            case 1:  // Search for specific item
                cout << "\nEnter the item name to search for: ";
                cin.ignore();  // Clear the newline from previous input
                getline(cin, searchItem);
                
                if (searchItem.empty()) {
                    cout << "No item entered. Please try again.\n";
                } else {
                    int frequency = tracker.getItemFrequency(searchItem);
                    cout << "\nItem: " << searchItem << endl;
                    cout << "Frequency: " << frequency << endl;
                    if (frequency == 0) {
                        cout << "(Item not found in today's purchases)\n";
                    }
                }
                break;
                
            case 2:  // Display all frequencies
                tracker.displayAllFrequencies();
                break;
                
            case 3:  // Display histogram
                tracker.displayHistogram();
                break;
                
            case 4:  // Exit program
                cout << "\nThank you for using the Corner Grocer Item Tracker!\n";
                cout << "Goodbye!\n";
                break;
        }
    } while (choice != 4);
    
    return 0;
}