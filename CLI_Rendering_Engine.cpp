#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <windows.h>
using namespace std;

// Terminal Color Codes
// I.E: cout << Black << "My Text" << RST_color;
#define RST_color "\033[0m"
#define Black "\033[30m" // more like a grey on powershell
#define Blue "\033[34m"
#define Green "\033[32m"
#define Cyan "\033[36m"
#define Red "\033[31m"
#define Purple "\033[35m"
#define Brown "\033[33m"
#define Light_Gray "\033[37m"
#define Dark_Gray "\033[1;30m"
#define Light_Blue "\033[1;34m"
#define Light_Green "\033[1;32m"
#define Light_Cyan "\033[1;36m"
#define Light_Red "\033[1;31m"
#define Light_Purple "\033[1;35m"
#define Yellow "\033[1;33m"
#define White "\033[1;37m"

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
    
    // runs cout but keeps track of the cursor position
    int print_str(string print_str) {
        point start_pos = cursor_pos;
        for (int i = 0; i < print_str.size(); i++) {
            if (print_str.at(i) == '\n') {
                cursor_pos.y++;
                cursor_pos.x = 0;
                continue;
            }
            cout << print_str.at(i);
            cursor_pos.x += 1;
        }
        return 0;
    }

    // uses a terminal command to clear the screen
    int clear_screen() {
        printf("\033[2J");
        return 0;
    }

    // set the cursor position with the provided x,y cords
    int set_cursor(point set_cord) {
        printf("\033[%d;%dH", set_cord.y + 1, set_cord.x + 1);
        cursor_pos = set_cord;
        return 0;
    }

    int move_cursor_left(unsigned int x_change = 1) {
        printf("\033[%dD", x_change);
        cursor_pos.x -= x_change;
        return 0;
    }

    int move_cursor_right(unsigned int x_change = 1) {
        printf("\033[%dC", x_change);
        cursor_pos.x += x_change;
        return 0;
    }

    int move_cursor_up(unsigned int y_change = 1) {
        printf("\033[%dA", y_change);
        cursor_pos.y -= y_change;
        return 0;
    }

    int move_cursor_down(unsigned int y_change = 1) {
        printf("\033[%dB", y_change);
        cursor_pos.y += y_change;
        return 0;
    }

    // print a left-aligned string at the current cursor position
    // returns a point structure {max_len, lines}
    point print_left(string out_str) {
        string curr_string = "";
        unsigned int max_len = 0;
        unsigned int lines = 1;
        for (int i = 0; i < out_str.size(); i++) {
            if (out_str.at(i) == '\n') {
                print_str(curr_string);
                move_cursor_left(curr_string.size());
                move_cursor_down();
                max_len = max(max_len, u_int(curr_string.size()));
                lines++;
                curr_string = "";
                continue;
            }
            curr_string += out_str.at(i);
        }
        if (curr_string.size()) {
            print_str(curr_string);
            move_cursor_left(curr_string.size());
            move_cursor_down();
            max_len = max(max_len, u_int(curr_string.size()));
        }
        return point{max_len, lines};
    }
};
cursor_write terminal;

int main() {

    return 0;
}
