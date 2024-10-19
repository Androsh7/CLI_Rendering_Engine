#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

// I.E: cout << Black << "My Text" << RST_color;
#define RST_color string("\033[0m") // Terminal Color Code
#define Black string("\033[30m") // Terminal Color Code
#define Blue string("\033[34m") // Terminal Color Code
#define Green string("\033[32m") // Terminal Color Code
#define Cyan string("\033[36m") // Terminal Color Code
#define Red string("\033[31m") // Terminal Color Code
#define Purple string("\033[35m") // Terminal Color Code
#define Brown string("\033[33m") // Terminal Color Code
#define Light_Gray string("\033[37m") // Terminal Color Code
#define Dark_Gray string("\033[1;30m") // Terminal Color Code
#define Light_Blue string("\033[1;34m") // Terminal Color Code
#define Light_Green string("\033[1;32m") // Terminal Color Code
#define Light_Cyan string("\033[1;36m") // Terminal Color Code
#define Light_Red string("\033[1;31m") // Terminal Color Code
#define Light_Purple string("\033[1;35m") // Terminal Color Code
#define Yellow string("\033[1;33m") // Terminal Color Code
#define White string("\033[1;37m") // Terminal Color Code

#define Black_Highlight string("\033[40m")
#define Red_Highlight string("\033[41m")
#define Green_Highlight string("\033[42m")
#define Yellow_Highlight string("\033[43m")
#define Blue_Highlight string("\033[44m")
#define Purple_Highlight string("\033[45m")
#define Cyan_Highlight string("\033[46m")
#define White_Highlight string("\033[47m")

// returns a string of a repeated character
string generate_repeat_char(char repeat_char, int print_len) {
    string out_string = "";
    for (int i = 0; i < print_len; i++) {
        out_string += repeat_char;
    }
    return out_string;
}

// converts a number to a status bar, so 55 would look like: "[===========         ]"
string generate_status_bar(int in_num, int max_num = 100, int increment_num = 5, char percent_char = '=', char start_char = '[', char end_char = ']', char pad_char = ' '){
    string outstring = "";
    int percent_num = in_num / increment_num; // number of percent chars to print
    int remainder = (max_num / increment_num) - percent_num; // number of pad chars to print
    
    // creates outstring
    outstring += start_char;
    outstring += generate_repeat_char(percent_char, percent_num);
    outstring += generate_repeat_char(pad_char, remainder);
    outstring += end_char;

    return outstring;
}

// draws a line
string generate_line(int length, char start_char = '<', char middle_char = '=', char end_char = '>') {
    string out_string = "";
    out_string += start_char;
    for (int i = 0; i < length - 2; i++){
        out_string += middle_char;
    }
    out_string += end_char;
    return out_string;
}

struct point{
    unsigned int x,y;
};

// includes tools to write using the cursor
class cursor_write {
private:
    point cursor_pos = point{0,0};
public:
    point get_pos() {
        return cursor_pos;
    }
    
    // runs cout but keeps track of the cursor position and allows max_length restrictions
    // returns the number of real characters printed
    // NOTE: the command stops if it encounters a newline
    int print_str(string print_str, int max_len = 0) {
        point start_pos = cursor_pos;
        int color_override = 0;
        bool color_detected = false;
        int printed_len = 0;
        for (int i = 0; i < print_str.size(); i++) {
                if (print_str.at(i) == '\033') {
                    color_detected = true;
                }
                if (color_detected) {
                    color_override++;
                    cout << print_str.at(i);
                    if (print_str.at(i) == 'm') {
                        color_detected = false;
                    }
                    continue;
                }

            // cancels operation if max_len (excluding color codes) is exceeded or if newline is encountered
            if ((max_len && i + 1 > max_len + color_override) || print_str.at(i) == '\n') {
                return printed_len;
            }
            cout << print_str.at(i);
            printed_len++;
            cursor_pos.x += 1;
        }
        return printed_len;
    }

    // clears the terminal
    // This will not reset the cursor position
    int clear_screen() {
        printf("\033[2J");
        return 0;
    }

    // set the cursor position with the provided x,y cords
    // NOTE: cursor positions start at 0,0
    int set_cursor(point set_cord) {
        printf("\033[%d;%dH", set_cord.y + 1, set_cord.x + 1);
        cursor_pos = set_cord;
        return 0;
    }

    int move_cursor_left(unsigned int x_change = 1) {
        printf("\033[%dD", x_change);
        if (x_change > cursor_pos.x) {
            cursor_pos.x = 0;
        } else {
            cursor_pos.x -= x_change;
        }
        return 0;
    }

    int move_cursor_right(unsigned int x_change = 1) {
        printf("\033[%dC", x_change);
        cursor_pos.x += x_change;
        return 0;
    }

    int move_cursor_up(unsigned int y_change = 1) {
        printf("\033[%dA", y_change);
        if (y_change > cursor_pos.y) {
            cursor_pos.y = 0;
        } else {
            cursor_pos.y -= y_change;
        }
        return 0;
    }

    int move_cursor_down(unsigned int y_change = 1) {
        printf("\033[%dB", y_change);
        cursor_pos.y += y_change;
        return 0;
    }

    // print a left-aligned string at the current cursor position, allows an optional specifier for max length and max lines
    // returns a point structure {max_len, lines}
    point print_left(string out_str, unsigned int max_print_len = 0, unsigned int max_print_lines = 0) {
        string curr_string = "";
        unsigned int max_len = 0;
        unsigned int lines = 1;
        
        // ignore max_print_len if it equals zero
        if (!max_print_len) max_print_len = 9999;

        for (int i = 0; i < out_str.size(); i++) {
            // quits early if max_print_lines is reached
            if (max_print_lines && lines > max_print_lines) {
                return point{max_len, lines};
            }
            if (out_str.at(i) == '\n') {
                int printed_chars = print_str(curr_string, max_print_len);
                move_cursor_left(printed_chars);
                move_cursor_down();
                max_len = max(max_len, u_int(printed_chars));
                lines++;
                curr_string = "";
                continue;
            }
            curr_string += out_str.at(i);
        }

        // prints the remaining value in curr_string
        if (curr_string.size()) {
            int printed_chars = print_str(curr_string, max_print_len);
            //move_cursor_left(printed_chars);
            //move_cursor_down();
            max_len = max(max_len, u_int(printed_chars));
        }
        return point{max_len, lines};
    }
};
cursor_write terminal;

class option_list {
private:
    vector<string> options;
    vector<string> highlight;
    point print_loc;
public:
    // adds an option to the bottom of the list
    int add_option(string option) {
        options.push_back(option);
        highlight.push_back("");
        return 0;
    }

    // removes a number of options starting from the bottom of the list
    int remove_option(int num = 1) {
        for (int i = 0; i < min(int(options.size()), num); i++) {
            options.pop_back();
            highlight.pop_back();
        }
        return 0;
    }

    // prints all the options from the print location
    int print_options() {
        terminal.set_cursor(print_loc);
        for (int i = 0; i < options.size(); i++) {
            terminal.print_left(highlight.at(i) + options.at(i) + RST_color);
        }
        return 0;
    }

    // changes the highlight for a specified index position
    // to reset the color set highlight_text to be "" or RST_color
    int change_highlight(int option_index, string highlight_text = White_Highlight) {
        highlight.at(option_index) = highlight_text;
        return 0;
    }

    // resets the highlighting for all options
    int reset_highlight() {
        for (int i = 0; i < highlight.size(); i++) {
            highlight.at(i) = "";
        }
        return 0;
    }

    // grabs the index position associated with the first highlighted option
    // returns -1 if no line is highlighted
    int get_first_highlighted() {
        for (int i = 0; i < highlight.size(); i++) {
            if (highlight.at(i) != "" && highlight.at(i) != RST_color) {
                return i;
            }
        }
        return -1;
    }

    option_list(point start_point) {
        print_loc = start_point;
    }
};

int main() {
    terminal.set_cursor(point{4,0});
    terminal.clear_screen();
    option_list mylist(point{0,0});
    mylist.add_option("The first Option\n");
    mylist.add_option("Testing\n");
    mylist.change_highlight(1, Green_Highlight);
    mylist.add_option("Last option\n");
    mylist.print_options();


    return 0;
}
