#include <luna/shared/file_parser.h>

#include <fstream>
#include <sstream>

std::string parse_file(const std::string& file_path)
{
    std::ifstream file(file_path);

    std::stringstream file_text;

    while(file)
    {
        std::string current_line;
        std::getline(file, current_line);

        file_text << current_line << "\n";
    }
    return file_text.str();
} 