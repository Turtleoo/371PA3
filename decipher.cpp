#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstdlib>

using namespace std;

string read_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: The file " << filename << " could not be found." << endl;
        exit(2);
    }
    string content, line;
    while (getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    return content;
}

string decipher(const string& ciphertext, const unordered_map<char, char>& mapping) {
    string plaintext = "";
    for (char c : ciphertext) {
        char lower_c = tolower(c);
        if (mapping.find(lower_c) != mapping.end()) {
            char mapped_char = mapping.at(lower_c);
            plaintext += isupper(c) ? toupper(mapped_char) : mapped_char;
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./decipher <cipher_file>" << endl;
        exit(1);
    }

    string cipher_file = argv[1];
    string cipher_text = read_file(cipher_file);

    unordered_map<char, char> manual_mapping = {
        {'x', 'e'}, {'t', 'n'}, {'j', 't'}, {'m', 'a'}, {'p', 'h'}, {'c', 'o'}, {'r', 's'},
        {'b', 'i'}, {'n', 'd'}, {'v', 'r'}, {'g', 'l'}, {'w', 'g'}, {'y', 'w'}, {'a', 'c'},
        {'l', 'm'}, {'i', 'f'}, {'u', 'u'}, {'h', 'k'}, {'f', 'b'}, {'e', 'y'}, {'q', 'p'},
        {'d', 'v'}, {'o', 'z'}, {'k', 'q'}, {'s', 'j'}, {'z', 'x'}
    };

    cout << "Original Text:" << endl;
    cout << cipher_text << endl;

    cout << "\nDeciphered Text:" << endl;
    cout << decipher(cipher_text, manual_mapping) << endl;

    return 0;
}
