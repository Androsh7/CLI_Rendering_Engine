# CLI Rendering Engines
This is a collection of rendering engines in various languages

# Important Console Codes

## C++ Format
```
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

#define Black_Highlight string("\033[40m") // Terminal Color Code
#define Red_Highlight string("\033[41m") // Terminal Color Code
#define Green_Highlight string("\033[42m") // Terminal Color Code
#define Yellow_Highlight string("\033[43m") // Terminal Color Code
#define Blue_Highlight string("\033[44m") // Terminal Color Code
#define Purple_Highlight string("\033[45m") // Terminal Color Code
#define Cyan_Highlight string("\033[46m") // Terminal Color Code
#define White_Highlight string("\033[47m") // Terminal Color Code
```

## Python Format
```
# dictionary for cli color codes
cli_color = {
    "reset": "\033[0m",

    # standard colors
    "black": "\033[30m",
    "blue": "\033[34m",
    "green": "\033[32m",
    "cyan": "\033[36m",
    "red": "\033[31m",
    "purple": "\033[35m",
    "brown": "\033[33m",
    "yellow": "\033[1;33m",
    "white": "\033[1;37m",

    # light/dark colors
    "light_gray": "\033[33[37m",
    "dark_gray": "\033[33[1;30m",
    "light_blue": "\033[33[1;34m",
    "light_green": "\033[33[1;32m",
    "light_cyan": "\033[33[1;36m",
    "light_red": "\033[33[1;31m",
    "light_purple": "\033[33[1;35m",

    # highlights
    "black_highlight": "\033[40m",
    "red_highlight": "\033[41m",
    "green_highlight": "\033[42m",
    "yellow_highlight": "\033[43m",
    "blue_highlight": "\033[44m",
    "purple_highlight": "\033[45m",
    "cyan_highlight": "\033[46m",
    "white_highlight": "\033[47m",
}
```
