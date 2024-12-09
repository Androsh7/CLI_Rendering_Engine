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