#ifndef CONSOLE_GUI_HPP
#define CONSOLE_GUI_HPP

#define NOMINMAX

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <Windows.h>

#define DISABLE_INPUT_FLAG (ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS)

class ConsoleGUI {
public:
    HANDLE                     m_consoleHandleInput;
    HANDLE                     m_consoleHandleOutput;
    CONSOLE_SCREEN_BUFFER_INFO m_screenBufferInfo;
    HWND                       m_windowHandle;
    CONSOLE_CURSOR_INFO        m_cursorInfo;
    COORD                      m_visibleScreenBufferSize;
    int                        m_screenWt, m_screenHt;

    ConsoleGUI();

    void toggle_fullscreen();
    void hide_scrollbar();
    void update_sbi();
    void hide_cursor();
    void set_console_cursor_pos(short x, short y);
    void disable_input();
    void enable_input();
    void set_font(SHORT wt, SHORT ht);
    void set_window_size(int wt, int ht); // In char cells
    void get_desktop_resolution(int &wt, int &ht); // Pass by ref
    void set_console_col(int col_attr);
    void type_print(std::string str, int delay, bool nl);
    void sleep_ms(int ms);
};


#endif