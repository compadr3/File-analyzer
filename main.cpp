#include <iostream>
#include <vector>
#include <algorithm>
#include "file_operations.h"

/**
 * shows flags that can be used and what is their purpose.
 */
void show_help() {
    std::cout << "\nPJAText2 EXAMINES TEXT FILES\n\nCommands:\n"
                 "-f |--file: enables you to write file directory in the next argument. ex.-f file.txt\n"
                 "Following arguments have to be written after (-f file.txt):\n\n"
                 "-n |--newlines: shows number of lines\n"
                 "-d |--digits: shows how many digits are in the file\n"
                 "-dd|--numbers: shows how many numbers are in the file\n"
                 "-c |--chars: shows number of characters\n"
                 "-w |--words: shows number of words\n"
                 "-s |--sorted: shows every word in an alphabetical order\n"
                 "-rs|--reverse-sorted: shows every word in an opposite alphabetical order (z-a)\n"
                 "-m |--most-common: shows most common word and number of times it was used\n"
                 "-l |--by-length: modifies [-s] or [-rs] command so that program shows every word sorted by word length\n"
                 "-a |--anagrams: after that write any words. Program will show anagrams for those words\n"
                 "-p |--palindromes: after that write any words. Program will show all palindromes from file which match those written by you\n"
                 "-o |--output: after that write .txt file directory (existed or not). Output is saved in txt file\n"
                 "-i |--input: after that write .txt file directory. Program executes commands given in this file\n"
                 "(no flag)/--help : shows this info";
}

/**
 * Executes commands given by user.
 * Goes through all arguments and depending on argument calls for function from "file_operations.h".
 * Then adds output string from that(header func) function to string. This string is then transmitted to a file.
 * -repeats
 * @param arguments - vector of strings(arguments) to be executed.
 * @param save
 */
void execute_commands(std::vector<std::string> arguments, bool save) {
    using namespace std;
    string first_file = arguments[1];
    string file_input = "";
    ofstream file;
    auto iter = find(arguments.begin(), arguments.end(), "-o");
    auto iter2 = find(arguments.begin(), arguments.end(), "--output");
    auto f_index = 0;
    if (iter != arguments.end()) {
        f_index = iter - arguments.begin() + 1;
    } else if (iter2 != arguments.end()) {
        f_index = iter2 - arguments.begin() + 1;
    }

    for (int i = 0; i < arguments.size(); i++) {
        file.open(arguments[f_index]);
        if (arguments[i] == "-n" || arguments[i] == "--newlines") {
            file_input += "Number of lines: " + std::to_string(get_num_of_lines(first_file)) + "\n";
        } else if (arguments[i] == "-d" || arguments[i] == "--digits") {
            file_input += "Number of digits: " + std::to_string(get_num_of_digits(first_file)) + "\n";
        } else if (arguments[i] == "-dd" || arguments[i] == "--numbers") {

            file_input += "Amount of numbers: " + to_string(get_num_of_numbers(first_file)) + "\n";//zrobione

        } else if (arguments[i] == "-c" || arguments[i] == "--chars") {

            file_input += "Amount of characters: " + to_string(get_num_of_characters(first_file)) + "\n";//zrobione

        } else if (arguments[i] == "-w" || arguments[i] == "--words") {

            file_input += "Number of words: " + to_string(get_words(first_file).size()) + "\n"; // zrobione

        } else if ((arguments[i] == "-s" || arguments[i] == "--sorted") &&
                   (arguments[i - 1] != "-l" || arguments[i] == "--by-length")) {

            file_input += get_words_sorted_alphabetical(first_file, true) + "\n";         //zrobione

        } else if ((arguments[i] == "-rs" || arguments[i] == "--reverse-sorted") &&
                   (arguments[i - 1] != "-l" || arguments[i] == "--by-length")) {

            file_input += get_words_sorted_alphabetical(first_file, false) + "\n";         //zrobione

        } else if (arguments[i] == "-l" || arguments[i] == "--by-length") {
            int index = 0;
            auto it = find(arguments.begin()+i, arguments.end(),"-s"),
            it2 = find(arguments.begin()+i, arguments.end(),"-sorted"),
            it3 = find(arguments.begin()+i, arguments.end(),"-rs"),
            it4 = find(arguments.begin()+i, arguments.end(),"--reverse-sorted");
            if(it != arguments.end() || it2 != arguments.end()){
                index = it - arguments.begin();
            } else if(it3 != arguments.end() || it4 != arguments.end()){
                index = it3 - arguments.begin();
            }
            file_input += get_words_sorted_by_length(first_file,arguments[index], arguments[i-1]); //zrobione

        } else if (arguments[i] == "-a" || arguments[i] == "--anagrams") {

            vector<string> possible_anagrams;
            for (int j = i + 1; j < arguments.size(); j++) {                   //zrobione
                possible_anagrams.push_back(arguments[j]);
            }
            file_input += get_anagrams(first_file, possible_anagrams) + "\n";

        } else if (arguments[i] == "-p" || arguments[i] == "--palindromes") {    //zrobione

            vector<string> possible_palindromes;
            for (int j = i + 1; j < arguments.size(); j++) {
                possible_palindromes.push_back(arguments[j]);
            }
            file_input += "Palindromes: ";
            for (const string &s :get_palindromes(first_file, possible_palindromes)) {
                file_input += s + ",";
            }
            file_input += "\n";

        } else if(arguments[i] == "-m" || arguments[i] == "--most-common") {
            file_input += "Most common word is: " + get_most_common_word(first_file) + "\n";
        }
        file << file_input;
        file.close();
    }

}

/**
 * Executes commands given by user.
 * Almost the same function as above, but instead of saving output to a file it shows it in the command line
 * Goes through all arguments and depending on argument calls for function from "file_operations.h".
 * Then outputs result in the command line.
 * -repeats
 * @param arguments - vector of strings(arguments) to be executed.
 */
void execute_commands(std::vector<std::string> arguments) {
    using namespace std;
    string first_file = arguments[1];

    for (int i = 0; i < arguments.size(); i++) {
        if (arguments[i] == "-n" || arguments[i] == "--newlines") {
            cout << "Number of lines: " << get_num_of_lines(first_file) << "\n";//zrobione
        } else if (arguments[i] == "-d" || arguments[i] == "--digits") {
            cout << "Number of digits: " << get_num_of_digits(first_file) << "\n";//zrobione
        } else if (arguments[i] == "-dd" || arguments[i] == "--numbers") {
            cout << "Amount of numbers: " << get_num_of_numbers(first_file) << "\n";//zrobione
        } else if (arguments[i] == "-c" || arguments[i] == "--chars") {
            cout << "Amount of characters: " << get_num_of_characters(first_file) << "\n";//zrobione
        } else if (arguments[i] == "-w" || arguments[i] == "--words") {
            cout << "Number of words: " << get_words(first_file).size() << "\n"; // zrobione
        } else if ((arguments[i] == "-s" || arguments[i] == "--sorted") &&
                   (arguments[i - 1] != "-l" || arguments[i] == "--by-length")) {
            cout << get_words_sorted_alphabetical(first_file, true); //zrobione (jak jest przecinek to tez go bierze)
        } else if ((arguments[i] == "-rs" || arguments[i] == "--reverse-sorted") &&
                   (arguments[i - 1] != "-l" || arguments[i] == "--by-length")) {
            cout << get_words_sorted_alphabetical(first_file, false);         //zrobione
        } else if (arguments[i] == "-l" || arguments[i] == "--by-length") {
            int index = 0;
            auto it = find(arguments.begin()+i, arguments.end(),"-s"),
                    it2 = find(arguments.begin()+i, arguments.end(),"-sorted"),
                    it3 = find(arguments.begin()+i, arguments.end(),"-rs"),
                    it4 = find(arguments.begin()+i, arguments.end(),"--reverse-sorted");
            if(it != arguments.end() || it2 != arguments.end()){
                index = it - arguments.begin();
            } else if(it3 != arguments.end() || it4 != arguments.end()){
                index = it3 - arguments.begin();
            }
            cout << get_words_sorted_by_length(first_file, arguments[index], arguments[i-1]);//zrobione
        } else if (arguments[i] == "-a" || arguments[i] == "--anagrams") {
            vector<string> possible_anagrams;
            for (int j = i + 1; j < arguments.size(); j++) {                   //zrobione
                possible_anagrams.push_back(arguments[j]);
            }
            cout << get_anagrams(first_file, possible_anagrams);
        } else if (arguments[i] == "-p" || arguments[i] == "--palindromes") {    //zrobione
            vector<string> possible_palindromes;
            for (int j = i + 1; j < arguments.size(); j++) {
                possible_palindromes.push_back(arguments[j]);
            }
            possible_palindromes = get_palindromes(first_file, possible_palindromes);
            cout << "Palindromes: ";
            for_each(possible_palindromes.begin(), possible_palindromes.end(), [](const string& pal) {
                cout << pal << ",";
            });
            cout << "\n";
        } else if(arguments[i] == "-m" || arguments[i] == "--most-common"){
            cout <<"Most common word is: " + get_most_common_word(first_file) + "\n";
        } else if (arguments[i] == "--help") {
            show_help();
        }
    }
}

/**
 * Checks whether given string is in txt file format.
 * @param str - string to be checked.
 * @return true if str is in .txt format, if its not returns false;
 */
bool is_it_txt_format(std::string str) {
    bool tf = false;
    std::string check;
    for (int i = str.size() - 4; i < str.size(); i++) {
        check += str[i];
    }
    if (check == ".txt") {
        tf = true;
    }
    return tf;
}

/**
 * Goes through each argument and each flag from end to beginning. Then compares both strings.
 * If they are the same it means that we found a flag and its the last one. After that the loop is stopped.
 * @param args - vector of strings(arguments) given in command line.
 * @param flags - vector of strings(flags) which are flags recognised by program.
 * @return string which is last flag given in command line.
 */
std::string get_last_vec_flag(std::vector<std::string> args, std::vector<std::string> flags) {
    bool not_found = true;
    std::string last_flag;
    for (int i = args.size() - 1; i >= 0 && not_found; i--) {
        for (int j = flags.size() - 1; j >= 0 && not_found; j--) {
            if (args[i] == flags[j]) {
                last_flag = args[i];
                not_found = false;
            }
        }
    }
    return last_flag;
}

/**
 * For each argument checks if: given arguments is written in correct order, flags are the same as flags recognised by program.
 * If there is no arguments function show_info() is called which displays information about each flag and their functionality.
 * If there is an error: Incorrect arguments are displayed to user, program ends.
 * if there is no error: Program continues.
 * @param args- vector of strings(arguments) given in command line.
 * @param possible_flags - vector of strings(flags) which are flags recognised by program.
 * @param last_flag - string which is the last flag in arguments.
 */
void check_arguments(std::vector<std::string> args, std::vector<std::string> possible_flags, std::string last_flag) {
    using namespace std;

    vector<string> arg_suspects;

    if (args.empty()) {
        show_help();
        exit(0);
    }

    if (args[args.size() - 1] == "-f" || args[args.size() - 1] == "-o" ||
        args[args.size() - 1] == "-l" ||
        args[args.size() - 1] == "-i" || (args[0] == "-i" && args.size() != 2)) {
        arg_suspects.push_back(args[args.size() - 1]);

    }
    for (int i = 0; i < args.size(); i++) {
        if ((args[i] == "-l" || args[i] == "--by-length") && i != args.size() - 1 && args[i + 1] != "-rs" &&
            args[i + 1] != "-s" && args[i+1] != "-l" && args[i+1] != "--by-length") {
            cout << "KOLEJKA LINOWA";
            arg_suspects.push_back(args[i]);
        }
        if (args[i] == "-a" || args[i] == "-p") {
            if (count(args.begin(), args.end(), "-a") > 1 || count(args.begin(), args.end(), "--anagrams") > 1 ||
                count(args.begin(), args.end(), "-p") > 1 || count(args.begin(), args.end(), "--palindromes") > 1) {

                arg_suspects.push_back(args[i]);
            }
            if (i == 0 || i == 1) {
                arg_suspects.push_back(args[i]);
            } else if (args[i] != last_flag && last_flag != "-o" && last_flag != "--output") {
                arg_suspects.push_back(args[i]);
            }
        } else if (is_it_txt_format(args[i]) &&
                   (args[i - 1] != "-f" ^ args[i - 1] != "-o" ^ args[i - 1] != "-i")) {

            arg_suspects.push_back(args[i]);
        } else if (args[i] == "-i" && args.size() > 2) {
            arg_suspects.push_back(args[i]);
        } else if (find(possible_flags.begin(), possible_flags.end(), args[i]) ==
                   possible_flags.end()) {
            if (args[i][0] == '-') {
                arg_suspects.push_back(args[i]);
            }
        }
    }
    if (arg_suspects.size() != 0) {
        cout << "\nError\nArguments are written incorectly.\nArguments that are incorrect:\n";
        for (string sus : arg_suspects) {
            cout << sus << ",";
        }
        cout << "\n";
        exit(0);
    }
}

/**
 * Stores arguments and recognised flags. Calls a function which checks if given arguments are correct.
 * If all arguments are correct, calls a funtion which executes commands and
 * either saves output in a file or displays output in command line.
 * @param args_count - counts number of arguments
 * @param args - array of characters which are arguments
 * @return
 */
int main(int args_count, const char *args[]) {

    using namespace std;
    const auto arguments = vector<string>(args + 1, args + args_count);

    vector<string> possible_flags = {"-f", "-n", "-d", "-dd", "-c", "-w", "-s", "-rs", "-l", "-a", "-p", "-o", "-i", "-m",
                                     "--help", "--file", "--newlines", "--digits", "--numbers", "--chars", "--words",
                                     "--sorted", "--reverse-sorted", "--by-length", "--anagrams", "--output",
                                     "--palindromes", "--input", "--most-common"};

    string last_flag = get_last_vec_flag(arguments, possible_flags);

    check_arguments(arguments, possible_flags, last_flag);

    if (arguments[0] == "-i" || arguments[0] == "--input") {
        vector<string> commands_txt;
        ifstream file;
        string command;
        file.open(arguments[1]);
        while (file >> command) {
            commands_txt.push_back(command);
        }
        file.close();
        check_arguments(commands_txt, possible_flags, get_last_vec_flag(commands_txt, possible_flags));
        if (find(arguments.begin(), arguments.end(), "-o") != arguments.end() ||
            find(arguments.begin(), arguments.end(), "--output") != arguments.end()) {
            execute_commands(commands_txt, true);
        } else {
            execute_commands(commands_txt);
        }
    } else if (find(arguments.begin(), arguments.end(), "-o") != arguments.end() ||
               find(arguments.begin(), arguments.end(), "--output") != arguments.end()) {

        execute_commands(arguments, true);
    } else {
        execute_commands(arguments);
    }

}