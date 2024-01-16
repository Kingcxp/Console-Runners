/*
                ######  ####### #     #  #####  #     #    #    ######  
                #     # #     #  #   #  #     # #     #   # #   #     # 
                #     # #     #   # #   #       #     #  #   #  #     # 
                ######  #     #    #    #       ####### #     # ######  
                #     # #     #   # #   #       #     # ####### #   #   
                #     # #     #  #   #  #     # #     # #     # #    #  
                ######  ####### #     #  #####  #     # #     # #     #
    
    Boxchar is a simple header only library for creating text based user interfaces 
    in C and C++. It is designed to be lightweight and easy to use.

    MIT License

    Copyright (c) 2023 Dane Madsen

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
#ifndef BOXCHAR_H
#define BOXCHAR_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <stdint.h>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#ifdef _WIN32
static HANDLE hConsole;
#else
static struct termios old_tio;
#endif

enum bc_color {
    BC_BLACK = 0,
    BC_RED = 1,
    BC_GREEN = 2,
    BC_YELLOW = 3,
    BC_BLUE = 4,
    BC_MAGENTA = 5,
    BC_CYAN = 6,
    BC_WHITE = 7
};

typedef void (*bc_callback)(void);

typedef struct {
    int x;
    int y;
} bc_point;

typedef struct {
    uint8_t foreground;
    uint8_t background;
} bc_colorpair;

typedef struct {
    bc_point position;
    wchar_t label[30];
    bc_colorpair colors;
    bc_callback callback;
} bc_button;

static void bc_init() {
    // Set the locale to the user's default
    setlocale(LC_ALL, "");
    
    // Initialize the terminal for boxchar
    #ifdef _WIN32
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbiInfo; 

        GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
        SetConsoleMode(hConsole, ENABLE_VIRTUAL_TERMINAL_PROCESSING);

        // Hide cursor
        CONSOLE_CURSOR_INFO cursor_info = {1, 0};
        SetConsoleCursorInfo(hConsole, &cursor_info);
    #else
        struct termios new_tio;

        // get the terminal settings for stdin
        tcgetattr(STDIN_FILENO, &old_tio);

        // we want to keep the old setting to restore them at the end
        new_tio = old_tio;

        // disable canonical mode (buffered i/o) and local echo
        new_tio.c_lflag &=(~ICANON & ~ECHO);

        // set the new settings immediately
        tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
        
        // Hide cursor and clear screen
        printf("\033[?25l\033[H\033[J");
    #endif
}

static void bc_end() {
    // Cleanup the terminal after boxchar
    #ifdef _WIN32
        // Restore original console mode
        SetConsoleMode(hConsole, 0);
    #else
        // restore the former settings
        tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
        
        // Show cursor
        printf("\033[?25h\033[H\033[J");
    #endif
}

bc_point bc_getcursor() {
    bc_point pos = {0, 0};
    
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            pos.x = csbi.dwCursorPosition.X;
            pos.y = csbi.dwCursorPosition.Y;
        }
    #else
        int ret;
        char buf[32];
        unsigned i = 0;

        // Write the escape sequence to get the cursor position
        write(STDOUT_FILENO, "\x1b[6n", 4);

        // Read the response: ESC [ rows ; cols R
        while (i < sizeof(buf) - 1) {
            ret = read(STDIN_FILENO, buf + i, 1);
            if (ret == -1 || (i > 0 && buf[i] == 'R')) break;
            i += ret;
        }
        buf[i] = '\0';

        // Parse the response
        if (sscanf(buf, "\x1b[%d;%dR", &pos.y, &pos.x) != 2) {
            // Parsing failed, return (0, 0)
            pos.x = 0;
            pos.y = 0;
        }
    #endif
    
    return pos;
}

void bc_setcursor(bc_point point) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = {point.x, point.y};
        SetConsoleCursorPosition(hConsole, coord);
    #else
        printf("\033[%d;%dH", point.y, point.x);
    #endif
}

void bc_termsize(int* width, int* height) {
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        *width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        *height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    #else
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        *width = w.ws_col;
        *height = w.ws_row;
    #endif
}

void bc_clear() {
    #ifdef _WIN32
        COORD coord = {0, 0};
        DWORD written;
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        // Get the number of cells in the current buffer 
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            DWORD cellCount = csbi.dwSize.X *csbi.dwSize.Y;

            // Fill the entire buffer with spaces 
            FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, coord, &written);

            // Fill the entire buffer with the current colors and attributes
            FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, coord, &written);

            // Move the cursor position to the top left
            SetConsoleCursorPosition(hConsole, coord);
        }
    #else
        printf("\033[H\033[J");
    #endif
}

int bc_getchar() {
    #ifdef _WIN32
        return getch();
    #else
        struct termios oldt, newt;
        int ch;
        int flags;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
        flags = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

        ch = getchar();
        
        fcntl(STDIN_FILENO, F_SETFL, flags);
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        
        return ch;
    #endif
}

void bc_putchar(bc_point point, wchar_t ch) {
    #ifdef _WIN32
        COORD coord = {point.x, point.y};
        SetConsoleCursorPosition(hConsole, coord);
        wprintf(L"%lc", ch);
    #else
        printf("\033[%d;%dH%lc", point.y, point.x, ch);
    #endif
}

int bc_kbhit() {
    #ifdef _WIN32
        return kbhit();
    #else
        struct termios term;
        tcgetattr(0, &term);

        struct termios term2 = term;
        term2.c_lflag &= ~ICANON;
        tcsetattr(0, TCSANOW, &term2);

        int byteswaiting;
        ioctl(0, FIONREAD, &byteswaiting);

        tcsetattr(0, TCSANOW, &term);

        return byteswaiting > 0;
    #endif
}

void bc_printf(bc_point point, const wchar_t* str) {
    #ifdef _WIN32
        COORD coord = {point.y, point.x};
        SetConsoleCursorPosition(hConsole, coord);
        wprintf(L"%ls", str);
    #else
        printf("\033[%d;%dH%ls", point.y, point.x, str);
    #endif
}

void bc_startcolor(bc_colorpair colorpair) {
    #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, colorpair.foreground + (colorpair.foreground * 16));
    #else
        printf("\033[38;5;%d;48;5;%dm", colorpair.foreground, colorpair.background);
    #endif
}

void bc_endcolor() {
    #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, 7);
    #else
        printf("\033[0m");
    #endif
}

void bc_drawbox(bc_point start, bc_point end, wchar_t border) {
    for(int i = 0; i < end.x; i++) {
        bc_putchar((bc_point) {start.x + i, start.y}, border);
        bc_putchar((bc_point) {start.x + i, start.y + end.y - 1}, border);
    }

    for(int i = 0; i < end.y; i++) {
        bc_putchar((bc_point) {start.x, start.y + i}, border);
        bc_putchar((bc_point) {start.x + end.x - 1, start.y + i}, border);
    }
}

void bc_drawline(bc_point start, bc_point end, wchar_t character) {
    int dx = end.x - start.x;
    int dy = end.y - start.y;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xinc = dx / (float)steps;
    float yinc = dy / (float)steps;
    float x = start.x;
    float y = start.y;

    for (int i = 0; i <= steps; i++) {
        bc_putchar((bc_point) {x, y}, character);
        x += xinc;
        y += yinc;
    }
}

void bc_createbutton(bc_button button) {
    bc_startcolor(button.colors);

    // Create the button label
    wchar_t button_label[30];
    swprintf(button_label, 30, L"%ls", button.label);

    // Calculate position for the button label
    bc_point label_position = {
        .x = button.position.x,
        .y = button.position.y
    };

    // Print the button label
    bc_printf(label_position, button_label);

    bc_endcolor();
}

int bc_ispressed(bc_button button, wchar_t key) {
    int ch = bc_getchar();

    if (ch == key) {
        bc_point cursor_position = bc_getcursor();
        int button_width = wcslen(button.label) + 2;
        return cursor_position.x >= button.position.x &&
               cursor_position.x <= button.position.x + button_width &&
               cursor_position.y == button.position.y;
    }

    return 0;
}

#endif // BOXCHAR_H