#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
using namespace std;

/*
CLI_Rendering_Engine
By Androsh7

MIT License

Copyright (c) 2024 Androsh7

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
    
    // gets the actual character length excluding ANSI terminal codes
    unsigned int real_length(string in_string) {
        int color_length = 0;
        bool color_detected = false;
        for (int i = 0; i < in_string.size(); i++) {
            if (in_string.at(i) == '\033') {
                color_detected = true;
            }
            if (color_detected) {
                color_length++;
                if (in_string.at(i) == 'm') {
                    color_detected = false;
                }
            }
        }

        return in_string.size() - color_length;
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

    int fill_area(point start_fill,unsigned int x_len, unsigned int y_len = 1, char fill_char = ' ') {
        set_cursor(start_fill);
        for (int y = 0; y < y_len; y++) {
            for (int x = 0; x < x_len; x++) {
                cout << fill_char;   
            }
            set_cursor(point{start_fill.x, start_fill.y + y});
        }
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

    // print a right-aligned string at the current cursor position, allows an optional specifier for max length and max lines
    // returns a point structure {max_len, lines}
    point print_right(string out_str, unsigned int max_print_len = 0, unsigned int max_print_lines = 0) {
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
                move_cursor_left(min(this->real_length(curr_string), max_print_len));
                int printed_chars = print_str(curr_string, max_print_len);
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
            move_cursor_left(min(this->real_length(curr_string), max_print_len));
            int printed_chars = print_str(curr_string, max_print_len);
            max_len = max(max_len, u_int(printed_chars));
        }
        return point{max_len, lines};
    }
};
cursor_write terminal;

// Get Keyboard State
class keyboard_state {
public:
    short key_state_prev[256];
    const int winlen = 51;
    const char winkeylist[51] = { '\b', '\t', '\n', ' ', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ';', '=', ',', '-', '.', '/', '`' , '[', '\\', ']', '\''};
    const char altkeylist[51] = { '\b', '\t', '\n', ' ', ')', '!', '@', '#', '$', '%', '^', '&', '*', '(', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ':', '+', '<', '_', '>', '?', '~' , '{', '|' , '}', '\"'};
    const int wincodelist[51] = { 8,    9,    13,   32,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  186, 187, 188, 189, 190, 191, 192,  219, 220,  221, 222 };
    // given a character it fines the corresponding window key code
    int find_key(char key) {
        for (int i = 0; i < winlen; i++){
            if (winkeylist[i] == key){
                return wincodelist[i];
            }
        }
        for (int i = 0; i < winlen; i++){
            if (altkeylist[i] == key){
                return wincodelist[i];
            } 
        }
        return -1;
    }

    // returns an output depending on the state of the key
    //  0 = key up, 1 = key pressed, 2 = key down
    int get_key_press(int code){
        // key press
        if (GetKeyState(code) < 0){
            if (key_state_prev[code] >= 0){
                key_state_prev[code] = -127;
                return 1; // key was just pressed
            } else {
                return 2; // key is currently pressed
            }
        }
        key_state_prev[code] = 0;
        return 0; // key is not pressed
    }

    // press enter to continue
    int wait_for_enter() {
        while (true) {
            if (get_key_press(13) == 1) {
                return 0;
            }
        }
    }

    // constructor
    keyboard_state() {
        for (int i = 0; i < 256; i++){
            key_state_prev[i] = 0;
        }
    }
};
keyboard_state keyboard;

class option_list {
private:
    vector<string> options;
    vector<string> highlight;
    point print_loc;
    int selected = 0;
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

    // get length of options vector
    int get_length() {
        return options.size();
    }

    // prints all the options from the print location
    int print_options() {
        terminal.set_cursor(print_loc);
        for (int i = 0; i < options.size(); i++) {
            string curr_highlight = "";
            if (i == selected) {
                if (highlight.at(i) == "") {
                    curr_highlight = White_Highlight;
                }
                else {
                    curr_highlight = Purple_Highlight;
                }
            }
            else {
                curr_highlight = highlight.at(i);
            }
            terminal.print_left(curr_highlight + options.at(i) + RST_color);
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

    // invert the highlighting for a tile
    int invert_highlight(int index, string color = Red_Highlight) {
        if (highlight.at(index) == "") {
            highlight.at(index) = Red_Highlight;
        }
        else {
            highlight.at(index) = "";
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

    // holds the user in a while loop where they must select a specified option
    // exit codes: -1 user quit early, 0 - 9999 selection code
    int run_options() {
        bool option_change = false;
        bool first_key_pressed = false; // this requires the user to press a key besides ENTER before making a selection
        print_options();
        while (true) {
            // Up option (W key pressed)
            if (keyboard.get_key_press(87) == 1) {
                selected = max(selected - 1, 0);
                option_change = true;
                first_key_pressed = true;
            }
            // Down option (S key pressed)
            else if (keyboard.get_key_press(83) == 1) {
                selected = min(selected + 1, int(options.size() - 1));
                option_change = true;
                first_key_pressed = true;
            }
            // Right option (D key pressed)
            else if (keyboard.get_key_press(68) == 1) {
                return selected;
            }
            // Left option (A key pressed)
            else if (keyboard.get_key_press(65) == 1) {
                return -1;
            }
            // Select option (ENTER key pressed)
            else if (keyboard.get_key_press(13) == 1 && first_key_pressed) {
                invert_highlight(selected);
                print_options();
            }
            // Quit option (Q key pressed)
            else if (keyboard.get_key_press(81) == 1) {
                return -2;
            }

            if (option_change) {
                print_options();
                option_change = false;
            }
        }
    }

    option_list(point start_point) {
        print_loc = start_point;
    }
};

int main() {
    terminal.set_cursor(point{20,0});
    terminal.clear_screen();
    option_list example_list(point{0,0});
    example_list.add_option("Option 1\n");
    example_list.add_option("Option 2\n");
    example_list.add_option("Option 3\n");
    option_list sub_list_1(point{10,0});
    sub_list_1.add_option("Sub-Option 1.1\n");
    sub_list_1.add_option("Sub-Option 1.2\n");
    sub_list_1.add_option("Sub-Option 1.3\n");
    option_list sub_list_2(point{10,0});
    sub_list_2.add_option("Sub-Option 2.1\n");
    sub_list_2.add_option("Sub-Option 2.2\n");
    sub_list_2.add_option("Sub-Option 2.3\n");
    option_list sub_list_3(point{10,0});
    sub_list_3.add_option("Sub-Option 3.1\n");
    sub_list_3.add_option("Sub-Option 3.2\n");
    sub_list_3.add_option("Sub-Option 3.3\n");
    while (true) {
        int list_1 = example_list.run_options();
        terminal.set_cursor(point{0,10});
        terminal.print_left("Hello");
        int sub_1 = 0, sub_2 = 0, sub_3 = 0;
        while (list_1 == 0) {
            int sub_1 = sub_list_1.run_options();
            if (sub_1 == -2) {
                return 0;
            }
            else if (sub_1 == -1) {
                break;
            }
        }
        while (list_1 == 1) {
            int sub_2 = sub_list_2.run_options();
            if (sub_2 == -2) {
                return 0;
            }
            else if (sub_2 == -1) {
                break;
            }
        }
        while (list_1 == 2) {
            int sub_3 = sub_list_3.run_options();
            if (sub_3 == -2) {
                return 0;
            }
            else if (sub_3 == -1) {
                break;
            }
        }
        if (list_1 == -2) {
            return 0;
        }
    }    
}
