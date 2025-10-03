#include <string>
#include <fstream>
#include <iostream>
/*

#################
#               #
# ###############
# #            ##
# #S# # ##### #E#
# # # #    ## # #
#   ##### ###   #

*/

std::string read_file(std::string filename)
{
    // otevreme soubor pro cteni
    std::ifstream file(filename);

    std::string result;

    // kontrola chyb pomoci file.good()
    while (file.good()) {
        // cteni obsahu pomoci funkce getline()
        std::string line;
        std::getline(file, line);
        result += line + "\n";
    }

    if (!file.good()) {
        std::cerr << "pri cteni souboru doslo k nejake chybe" << std::endl;
    }

    // vratit vysledek
    return result;
}

bool check_maze(std::string input)
{
    int count_S = 0;
    int count_E = 0;

    for (int i = 0; i < input.length(); i++) {
        // - pouze 4 povolene znaky: "# SE"
        //if (input[i] != '#' && input[i] != ' '
        //     && input[i] != 'S' && input[i] != 'E') {
        // python: if input[i] not in "# SE":
        // C++
        //if (! std::string("# SE").contains(input[i])) {
        if (std::string("# SE\n").find(input[i]) == std::string::npos) {
            std::cerr << "bludiste obsahuje nepovoleny znak: " << input[i] << std::endl;
            return false;
        }
        
        // - S a E se vyskytuji prave jednou
        if (input[i] == 'S') {
            count_S++;
        }
        if (input[i] == 'E') {
            count_E++;
        }

    }

    // - S a E se vyskytuji prave jednou
    if (count_S != 1) {
        std::cerr << "bludiste obsahuje " << count_S << "x znak S" << std::endl;
        return false;
    }
    if (count_E != 1) {
        std::cerr << "bludiste obsahuje " << count_E << "x znak E" << std::endl;
        return false;
    }


    // - vsechny radky stejne dlouhe
    // - velikost je alespon 2x1 nebo 1x2
    // - pokud je to vetsi bludiste, tak musi byt alespon 1 mezera

    return true;
}

void find_shortest_path(std::string maze)
{
}

int main()
{
    std::string maze = read_file("M:\\PRC2\\cv08\\bludiste.txt");
    std::cout << maze << std::endl;
    if (check_maze(maze)) {
        std::cout << "bludiste je v poradku" << std::endl;
    }
    else {
        std::cout << "bludiste ma nejakou chybu" << std::endl;
    }
}