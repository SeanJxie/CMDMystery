#include "console_gui.hpp"

class CmdMysteryGame : public ConsoleGUI {
public:

    CmdMysteryGame();
    ~CmdMysteryGame();

    void input_check(std::string prompt, std::string target);
    std::string tolower_str(std::string str);
    void write_file_from_hex(const int hex_array[], int size, std::string out_name);

    void start();
};