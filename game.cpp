#include "game.hpp"
#include "hex_assets/image1.h"
#include "hex_assets/audio1.h"


CmdMysteryGame::CmdMysteryGame() {
    /*
    Before we display any dialogue, we need to turn the cmd window into a restricted blank fullscreen canvas.
    */

    // Quick and dirty console clear.
    system("cls"); 
    
    // Set fullscreen
    toggle_fullscreen();

    // Hide scrollbar, console cursor, and disable input interaction
    hide_scrollbar();
    hide_cursor(); 
    disable_input();


}

CmdMysteryGame::~CmdMysteryGame() {
    // Leave the mess we've just created.
    PostMessage(m_windowHandle, WM_CLOSE, 0, 0);
}

void CmdMysteryGame::write_file_from_hex(const int hex_array[], int size, std::string out_name) {
    std::ofstream ofs(out_name, std::ios_base::out | std::ios_base::binary);
    for (int j = 0; j < size; j++) {
        ofs << (char)hex_array[j]; 
    }
    ofs.close();
}

void CmdMysteryGame::input_check(std::string prompt, std::string target) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;
    input = tolower_str(input);
    while (input != target) {
        std::cout << prompt;
        std::cin >> input;
        input = tolower_str(input);
    }
}

std::string CmdMysteryGame::tolower_str(std::string str) {
    std::string ret = "";
    for (int i = 0; i < str.length(); i++) {
            ret += tolower(str[i]);
    }
    return ret;
}

void CmdMysteryGame::start() {
    /*
s
    The "storyline" goes here.
`
    */

    /*
    Let's do some math:

    Consider a string of length n, a line fitting a maximum of w characters, and a scale factor f. 
    Let w / f be the font width of every character in the string of length n. The total width of the string is thus n( w / f ).
    We want to fit all n characters withing the length w, so the following must hold:

        => n( w / f ) <= w
        => n / f <= 1      
        => n <= f.

    Therefore, the number of characters n in the string, must be less than or equal to the scale factor used for determining the font width size.

    The same holds for character height.

    Notice, then, that all set_font() calls take the form:

        set_font((SHORT)(m_screenWt / w), ((SHORT)m_screenHt / h));

    By the rules derived above, the length of any string printed under the specified font size must not be greater than w.
    Furthermore, the number of lines printed should under the specified font size must not be greater than h.

    Therefore, we can fill the screen with text in a perfect way if we know the length of the longest string, and the amount of lines to be printed by adjusting font size accordingly.
    */

   
    // Create first objective: A creepy haiku ---
    std::string path(getenv("USERPROFILE"));

    path += "/Desktop/not_her.txt";
    std::ofstream firstfile(path);
    firstfile << "look in the mirror\nit is not your reflection\nthat stares back at you";
    firstfile.close();

    // Intro ---
    // Notice the longest string has length 29 and there are 4 lines to be printed.
    set_font((SHORT)(m_screenWt / 21), (SHORT)(m_screenHt / 4));
    SetConsoleTextAttribute(m_consoleHandleOutput, 12); // Red text

    sleep_ms(5000);
    type_print("Don't try and scream.", 400, true);
    sleep_ms(2000);
    type_print("Everyone is gone.", 300, true);
    sleep_ms(2000);
    type_print("Something is wrong.", 300, true);
    sleep_ms(2000);
    type_print("Keep me alive.", 300, true);
    sleep_ms(2000);

    // First user interaction ---
    toggle_fullscreen();
    set_font((SHORT)(m_screenWt / 100), (SHORT)(m_screenHt / 50));
    enable_input();
    input_check(">", "haiku");
    
    // After first user interaction ---
    system("cls"); 
    system("color C0"); // Black fg with light-red bg. Kind of a weird hardcode but it'll do for now.
    toggle_fullscreen();
    hide_scrollbar();
    hide_cursor(); 
    disable_input();
    SetConsoleTextAttribute(m_consoleHandleOutput, 192); // Red text
    set_font((SHORT)(m_screenWt / 22), (SHORT)(m_screenHt / 2));

    
     // Second objective: image.
    write_file_from_hex(bmp_hex, 120054, "TestBMP.bmp");
    write_file_from_hex(mp3_hex, 69954,  "TestMP3.mp3");

    sleep_ms(5000);
    type_print("What is in the mirror?", 100, true);
    sleep_ms(3000);
    type_print("Who did you see?", 100, true);
    sleep_ms(10000);    
}
