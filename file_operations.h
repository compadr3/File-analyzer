//
// Created by Samsung on 27.05.2021.
//

#ifndef PJATEXT2_FILE_OPERATIONS_H
#define PJATEXT2_FILE_OPERATIONS_H

#include <fstream>
#include <algorithm>
#include <sstream>
/**
 * Returns a number of lines in a file
 * @param file_path - txt file path
 * @return integer which represents amount of counted numbers
 */
int get_num_of_lines(const std::string &file_path) {
    int counter = 0;
    std::string str;
    std::ifstream file(file_path);

    while (std::getline(file, str)) {
        counter++;
    }

    file.close();
    return counter;
}
/**
 * Returns a number of digits in a file
 * @param file_path - path of txt file
 * @return integer which represents amount of counted digits
 */
int get_num_of_digits(const std::string &file_path) {
    int counter = 0;
    std::string str;
    std::ifstream file(file_path);

    while (file >> str) {
        for (char i : str) {
            if (isdigit(i)) {
                counter++;
            }
        }
    }

    file.close();
    return counter;
}
/**
 * Returns amount of numbers(int) present in a file.
 * for each word:
 * Checks if a word have ',' in it. If it does and its only one - checks if it contains digits only.
 * If not checks if it contains digits only.
 * Otherwise doesnt count it as a number.
 * @param file_path - txt file path
 * @return integer which represents amount of counted numbers
 */
int get_num_of_numbers(const std::string &file_path) {
    int counter = 0;
    int count = 0;
    std::ifstream file;
    std::string word;
    file.open(file_path);

    while (file >> word) {
        if (std::count(word.begin(), word.end(), ',') == 0) {
            for (char i : word) {
                if (!isdigit(i)) {
                    count++;
                }
            }
        } else if (std::count(word.begin(), word.end(), ',') == 1) {
            auto iterator = find(word.begin(), word.end(), ',');
            word.erase(iterator);
            for (char i : word) {
                if (!isdigit(i)) {
                    count++;
                }
            }
        } else {
            count++;
        }
        if (count == 0) {
            counter++;
        }
        count = 0;
    }

    file.close();
    return counter;
}
/**
 * Gets number of characters present in a file.
 * Goes through each line and counts its characters.
 * @param file_path - txt file path
 * @return integer which represents amount of counted characters
 */
int get_num_of_characters(const std::string &file_path) {
    int counter = 0;
    std::string str;
    std::ifstream file(file_path);
    while (std::getline(file, str)) {
        for (int i = 0; i < str.size(); i++) {
            counter++;
        }
    }

    file.close();
    return counter;
}

/**
 * Gets vector of strings from a file.
 * Each read word is added to a vector.
 * @param file_name - txt file path
 * @return vector of strings(words)
 */
std::vector<std::string> get_words(const std::string &file_name) {
    std::ifstream file;
    std::vector<std::string> words;
    std::string word;

    file.open(file_name);

    while (file >> word) {
        words.push_back(word);
    }

    file.close();
    return words;
}

/**
 * Compares each word with the other other one.
 * If at least one of those two words have a capital letter at the beginning,
 * this capital letter is "changed" to a small letter. (so that its the same ASCII number)
 * @param a - string
 * @param b -string
 * @return true if first char of string a is smaller than char from b
 */
bool compare_words(std::string a, std::string b) {
    if(a[0] >= 'A' && a[0] <= 'Z' && (b[0] <= 'A' || b[0] >= 'Z')){
        a[0] += 32;
        return a < b;
    } else if((a[0] <= 'A' || a[0] >= 'Z') && b[0] >= 'A' && b[0] <= 'Z'){
        b[0] += 32;
        return a < b;
    } else if(a[0] >= 'A' && a[0] <= 'Z' && a[0] >= 'A' && a[0] <= 'Z'){
        a[0] += 32;
        b[0] += 32;
        return a < b;
    } else {
        return a<b;
    }
}

/**
 * Gets string with words from file sorted in alphabetical order. Either from a to z or z to a.
 *
 * @param file_path - txt file path.
 * @param a_to_z - bool depending on whether words should be sorted from a to z or from z to a.
 * @return text which includes a info about how words were sorted and sorted words.
 */
std::string get_words_sorted_alphabetical(const std::string &file_path, bool a_to_z) {
    auto words = get_words(file_path);
    std::string a;
    std::string b;
    std::string sorted_words;
    sort(words.begin(), words.end(), compare_words);

    if (a_to_z) {
        sorted_words = "Words sorted in alphabetical order: ";
        for (int i = 0; i < words.size() - 1; i++) {
            sorted_words += words[i] + ",";
        }
        sorted_words += words[words.size() - 1] + "\n";
    } else {
        sorted_words = "Words sorted in reversed alphabetical order: ";
        for (int i = words.size() - 1; i > 0; i--) {
            sorted_words += words[i] + ",";
        }
        sorted_words += words[0] + "\n";
    }
    return sorted_words;
}

/**
 * Compares sizes of two strings.
 * @param a - string
 * @param b - string
 * @return true if first string is smaller than the second one
 */
bool compare_word_length(const std::string& a, const std::string& b) {
    return a.size() < b.size();
}
/**
 * Sorts words by their length:
 * from the smallest to the biggest one - if arg_after_l is -s,
 * from the biggest to the smallesst one - if arg_after_l is -rs.
 * @param file_path - txt file path.
 * @return text which includes a info about how words were sorted and sorted words
 */
std::string get_words_sorted_by_length(const std::string &file_path, std::string arg_after_l, std:: string arg_before_l) {
    auto words = get_words(file_path);
    std::string a;
    std::string b;
    std::string out_str;
    sort(words.begin(), words.end(), compare_word_length);

    if(arg_before_l == "-l"){
        return out_str;
    }

    out_str =  "Words sorted by length: ";
    if(arg_after_l == "-s" || arg_after_l == "--sorted") {
        for (int i = 0; i < words.size() - 1; i++) {
            out_str += words[i] + ",";
        }
        out_str += words[words.size() - 1] + "\n";
    } else if(arg_after_l == "-rs" || arg_after_l == "--reverse-sorted"){
        for (int i = words.size() - 1; i > 0; i--) {
            out_str += words[i] + ",";
        }
        out_str += words[0] + "," + "\n";
    }

    return out_str;
}
/**
 * Gets anagrams of arguments that are present in txt file.
 * If argument is the same size as word in file both strings are sorted. Then each char of each string is compared.
 * If every character is the same, it goes to a vector of strings.
 * @param file_path - txt file path
 * @param possible_anagrams - vector of string
 * @return text which includes anagrams of a word (given in arguments) which can be found in text file
 */
std::string get_anagrams(const std::string &file_path, const std::vector<std::string>& possible_anagrams) {
    std::vector<std::string> anagrams;
    std::ifstream file;
    std::string word, copy, out_str;
    file.open(file_path);
    while (file >> word) {
        copy = word;
        for (std::string anagram: possible_anagrams) {
            if (anagram.size() == word.size()) {
                sort(word.begin(), word.end());
                sort(anagram.begin(), anagram.end());
                if (word == anagram && !(find(anagrams.begin(), anagrams.end(), copy) != anagrams.end())) {
                    anagrams.push_back(copy);
                }
            }
        }
        copy = "";
    }
    out_str = "Anagrams: ";
    for (auto & anagram : anagrams) {
        out_str += anagram + ",";
    }
    out_str += "\n";
    file.close();
    return out_str;
}
/**
 * Goes through a string from both sides and compares characters.
 * If at least one of them is not equal then returns false.
 * If every char is equal to the char on the other side of a string(str) then returns true.
 * @param str - string to be checked
 * @return true if str is a palindrome, false if its not
 */
bool is_palindrome(std::string str) {
    int j = str.size() - 1;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] != str[j]) {
            return false;
        }
        j--;
    }
    return true;
}
/**Checks whether words given by user are palindromes (calls "is_palindrome"). Those which are palindromes are added
 * to vector.
 * Checks each confirmed palindrome from vector if it is present in txt file.
 * @param file_name - txt file path.
 * @param possible_palindromes - vector of strings to be checked.
 * @return vector of strings which are palindromes and present in file.
 */
std::vector<std::string> get_palindromes(const std::string& file_name, const std::vector<std::string>& possible_palindromes) {
    std::ifstream file;
    std::string word;
    std::vector<std::string> palindromes, palindromes_out;
    file.open(file_name);
    for (const std::string& str: possible_palindromes) {
        if (is_palindrome(str)) {
            palindromes.push_back(str);
        }
    }
    while (file >> word) {

        if (!palindromes.empty() && find(palindromes.begin(), palindromes.end(), word) != palindromes.end()) {
            palindromes_out.push_back(word);
        }
    }
    file.close();
    return palindromes_out;
}
/**
 * Checks each word and counts its occurrences in a file.
 * If word that is being checked is present more times than previous most common word,
 * then this word becomes new most common word.
 * @param file_path - txt file path.
 * @return a most common string used in given txt file.
 */
std::string get_most_common_word(const std::string &file_path){
    auto words = get_words(file_path);
    std::string most_common_word;
    for (std::string word : words) {
        if(std::count(words.begin(),words.end(),word) > std::count(words.begin(),words.end(),most_common_word)){
            most_common_word = word;
        }
    }
    int how_many = std::count(words.begin(),words.end(),most_common_word);
    return most_common_word + " | written " + std::to_string(how_many) + " times.";
}
#endif //PJATEXT2_FILE_OPERATIONS_H