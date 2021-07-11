#include "console_gui.hpp"

ConsoleGUI::ConsoleGUI() {
    m_consoleHandleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    m_consoleHandleInput  = GetStdHandle(STD_INPUT_HANDLE);
    m_windowHandle        = GetConsoleWindow();
    GetConsoleScreenBufferInfo(m_consoleHandleOutput, (PCONSOLE_SCREEN_BUFFER_INFO)&m_screenBufferInfo);
    get_desktop_resolution(m_screenWt, m_screenHt);
}

void ConsoleGUI::update_sbi() {
    // The screen buffer changes after the constructor is called.
    GetConsoleScreenBufferInfo(m_consoleHandleOutput, &m_screenBufferInfo);
}

void ConsoleGUI::disable_input() {
    // We need to use the input handle to toggle ss
    // Thanks to https://stackoverflow.com/a/56017313/11768102 for the flag.
    SetConsoleMode(m_consoleHandleInput, DISABLE_INPUT_FLAG);
}

void ConsoleGUI::enable_input() {
    // Quite literally, (NOT DISABLE_INPUT_FLAG) enables input.
    SetConsoleMode(m_consoleHandleInput, ~DISABLE_INPUT_FLAG);
}

void ConsoleGUI::set_font(SHORT wt, SHORT ht) {
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = wt;                   
    cfi.dwFontSize.Y = ht;                  
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_HEAVY;
    std::wcscpy(cfi.FaceName, L"Ms Gothic");
    SetCurrentConsoleFontEx(m_consoleHandleOutput, FALSE, &cfi);
}

void ConsoleGUI::set_window_size(int wt, int ht) {
    COORD coord; 
    coord.X = wt; 
    coord.Y = ht; 

    SMALL_RECT newSizeRect; 
    newSizeRect.Top = 0; 
    newSizeRect.Left = 0; 
    newSizeRect.Bottom = wt - 1; 
    newSizeRect.Right = ht - 1; 

    SetConsoleScreenBufferSize(m_consoleHandleOutput, coord);            
    SetConsoleWindowInfo(m_consoleHandleOutput, true, &newSizeRect);      
}

void ConsoleGUI::get_desktop_resolution(int &wt, int &ht) {
    // Thanks to https://stackoverflow.com/a/8690641/11768102

   RECT desktop;
   // Get a handle to the desktop window
   const HWND hDesktop = GetDesktopWindow();
   // Get the size of screen to the variable desktop
   GetWindowRect(hDesktop, &desktop);
   // The top left corner will have coordinates (0,0)
   // and the bottom right corner will have coordinates
   // (horizontal, vertical)
   wt = desktop.right;
   ht = desktop.bottom;
}

void ConsoleGUI::hide_cursor() {
    GetConsoleCursorInfo(m_consoleHandleOutput, &m_cursorInfo);
    m_cursorInfo.bVisible = false;
    SetConsoleCursorInfo(m_consoleHandleOutput, &m_cursorInfo);
}

void ConsoleGUI::set_console_cursor_pos(short x, short y) {
    SetConsoleCursorPosition(m_consoleHandleOutput, {x, y});
}

void ConsoleGUI::toggle_fullscreen() {
    // https://docs.microsoft.com/en-ca/windows/win32/inputdev/wm-syskeydown?redirectedfrom=MSDN
    SendMessage(m_windowHandle, WM_SYSKEYDOWN, VK_RETURN, 0x01 << 29);
    // Basically, just pressing alt + enter.
} 

void ConsoleGUI::set_console_col(int col_attr) {
    SetConsoleTextAttribute(m_consoleHandleOutput, col_attr);
}

void ConsoleGUI::hide_scrollbar() {
    update_sbi();
     // Dimensions of console window in character cells.
    // m_screenBufferInfo.srWindow allows us to obtain the width and height info of the visible console in character cells.
    // That visible portion is what we want to set the screen buffer to, so that no scroll bars are needed to view the entire buffer.
    m_visibleScreenBufferSize.X = m_screenBufferInfo.srWindow.Right - m_screenBufferInfo.srWindow.Left + 1; // Columns
    m_visibleScreenBufferSize.Y = m_screenBufferInfo.srWindow.Bottom - m_screenBufferInfo.srWindow.Top + 1; // Rows
     // Get rid of scrollbar by setting the screen buffer size the same as the console window size.
    SetConsoleScreenBufferSize(m_consoleHandleOutput, m_visibleScreenBufferSize);
}

void ConsoleGUI::type_print(std::string str, int delay, bool nl) {
    for (int i = 0; i < (int)str.length(); i++) {
        std::cout << str[i];
        sleep_ms(delay);
    }
    if (nl) { std::cout << std::endl; }
}


void ConsoleGUI::sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}