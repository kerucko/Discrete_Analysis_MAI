#include <iostream>
#include <cstring>

using namespace std;

class String {
    char* string = (char*)malloc(2 * sizeof(char));
    int capacity = 2;
    int size = 0;

public:
    char& operator[](int index) {
        return string[index];
    }

    void Add(char symbol) {
        if (size == capacity - 1) {
            capacity *= 2;
            string = (char*)realloc(string, capacity);
        }
        string[size] = symbol;
        ++size;
    }

    void AddLine(char* line) {
        for (int i = 0; i < strlen(line); ++i) {
            Add(line[i]);
        }
    }

    int Size() {
        return size;
    }

    char* GetString() {
        return string;
    }

    void Print() {
        printf("%s", string);
    }
    
    friend ostream& operator<<(ostream& os, const String& line);
};

ostream& operator<<(ostream& os, const String& line) {
    os << line.string;
    return os;
}


String Input() {
    char symbol = getchar();
    String result;

    while (symbol != EOF) {
        result.Add(symbol);
        symbol = getchar();
    }

    return result;
}

int Split(String input, int& count_lines) {
    for (int i = 1; i < input.Size(); ++i) {
        if (input[i] == '\n') {
            ++count_lines;
        }
        if (input[i] == '\n' && input[i + 1] == '\n') {
            return i + 1;
        }
    }
    return -1;
}


void ParseInput(String input) {
    int count_patterns = 0;
    int empty_string_index = Split(input, count_patterns);
    if (empty_string_index == -1) {
        count_patterns = 1;
    }

    char* input_string = input.GetString();
    char** patterns = (char**)malloc(sizeof(char*) * count_patterns);
    char* current_pattern = strtok(input_string, "\n");
    patterns[0] = current_pattern;
    for (int i = 1; i < count_patterns; ++i) {
        current_pattern = strtok(NULL, "\n");
        patterns[i] = current_pattern;
    }

    char ** text = (char**)malloc(sizeof(char*) * 2);
    int capacity = 2;
    int text_size = 0;
    char* current_word = strtok(NULL, " \t\n");
    while (current_word != NULL) {
        if (text_size == capacity - 1) {
            capacity *= 2;
            text = (char**)realloc(text, sizeof(char*) * capacity);
        }
        text[text_size] = current_word;
        ++text_size;
        current_word = strtok(NULL, " \t\n");
    }
}


int main() {
    String input = Input();
    // cout << input << endl;
    ParseInput(input);
    return 0;
}