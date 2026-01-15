//KATHELEYA NOLLA ANAK AKAU (INFORMATION SYSTEMS)
//TASK 2

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <cctype>

// Trims leading and trailing spaces from a string
std::string trim(const std::string& s) {
    const std::string ws = " \t\r\n";
    size_t a = s.find_first_not_of(ws), b = s.find_last_not_of(ws);
    return (a == std::string::npos) ? "" : s.substr(a, b - a + 1);
}

// Prints a separator line
void line(char ch = '-', int n = 46) {
    for (int i = 0; i < n; ++i) std::cout << ch;
    std::cout << "\n";
}

// Reads an integer within a specified range
int readIntInRange(int minVal, int maxVal) {
    int x;
    while (!(std::cin >> x) || x < minVal || x > maxVal) {
        std::cout << "\nInvalid input. Enter a number (" << minVal << "-" << maxVal << "): ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return x;
}

// Reads a 'y' or 'n' input
char readYesNo() {
    char c;
    while (true) {
        if (std::cin >> c && (c == 'y' || c == 'Y' || c == 'n' || c == 'N')) return c;
        std::cout << "\nPlease enter y or n: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Converts a string to lowercase
std::string lowerCopy(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Checks if a string is a valid name (letters, spaces, apostrophes, hyphens)
bool looksLikeName(const std::string& s) {
    if (s.empty()) return false;
    bool hasLetter = false;
    for (char c : s) {
        unsigned char uc = static_cast<unsigned char>(c);
        if (std::isalpha(uc)) hasLetter = true;
        if (!(std::isalpha(uc) || std::isspace(uc) || c == '\'' || c == '-')) return false;
    }
    return hasLetter;
}

// Checks for duplicate names (case-insensitive)
bool isDuplicateIgnoreCase(const std::vector<std::string>& names, const std::string& name) {
    std::string key = lowerCopy(name);
    return std::any_of(names.begin(), names.end(), 
        [&key](const std::string& existing) { return lowerCopy(existing) == key; });
}

// Checks if two names match exactly (case-insensitive)
bool isExactMatch(const std::string& name, const std::string& query) {
    return lowerCopy(name) == lowerCopy(query); 
}

int main() {
    line('=');
    std::cout << "Task 2: Sort Names (A-Z)\n";
    line('=');

    std::cout << "How many names do you want to enter? (minimum 1): ";
    int n = readIntInRange(1, 100);  

    std::vector<std::string> names;
    names.reserve(n);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    line();

    // Name input loop
    for (int i = 0; i < n; ++i) {
        std::string name;
        std::cout << "Enter name " << (i + 1) << ": ";
        std::getline(std::cin, name);
        name = trim(name);

        if (name.empty()) {
            --i;
            std::cout << "Name cannot be empty. Please try again.\n";
            continue;
        }
        if (!looksLikeName(name)) {
            --i;
            std::cout << "Invalid name. Use letters/spaces only (and ' or - if needed).\n";
            continue;
        }
        if (isDuplicateIgnoreCase(names, name)) {
            --i;
            std::cout << "Duplicate name detected. Please enter a different name.\n";
            continue;
        }

        names.push_back(name);
    }

    std::sort(names.begin(), names.end()); // Sort names alphabetically

    line();
    std::cout << "Sorted names (A-Z) | Total: " << names.size() << "\n";
    line();

    // Display sorted names
    for (std::size_t i = 0; i < names.size(); ++i) {
        std::cout << (i + 1) << ". " << names[i] << "\n";
    }

    while (true) {
        line();
        std::cout << "Search Menu\n1) Search by name\n2) Search by number\n3) Exit search\nChoose (1-3): ";
        int opt = readIntInRange(1, 3);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        if (opt == 3) break;

        if (opt == 1) {  // Search by name
            std::cout << "Enter name: ";
            std::string q;
            std::getline(std::cin, q);
            q = trim(q); 

            if (q.empty()) { 
                std::cout << "Name cannot be empty.\n"; 
                continue; 
            }
            if (!looksLikeName(q)) {
                std::cout << "Invalid name. Use letters/spaces only (and ' or - if needed).\n";
                continue;
            }

            auto it = std::find_if(names.begin(), names.end(), 
                [&q](const std::string& existing) { return isExactMatch(existing, q); });

            if (it != names.end()) {
                std::cout << "Found: " << *it << " (Position " << (std::distance(names.begin(), it) + 1) << ")\n";
            } else {
                std::cout << "Not found.\n";
            }
        } else {  // Search by position
            std::cout << "Enter list position (1-" << names.size() << "): ";
            int idx = readIntInRange(1, static_cast<int>(names.size()));
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Name " << idx << ": " << names[idx - 1] << "\n";
        }
    }

    line('=');
    std::cout << "Program ended.\n";
    line('=');
    return 0;
}

