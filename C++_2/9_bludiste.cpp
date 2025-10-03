#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>  // std::pair
#include <set>
#include <map>

/*

#################
#               #
# ###############
# #            ##
# #S# # ##### #E#
# # # #    ## # #
#   ##### ###   #

*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>  // std::pair
#include <set>
#include <map>
#include <limits>  // std::numeric_limits

std::vector<std::string> read_file(std::string filename)
{
    // otevreme soubor pro cteni
    std::ifstream file(filename);

    std::vector<std::string> result;

    // kontrola chyb pomoci file.good()
    while (file.good()) {
        // cteni obsahu pomoci funkce getline()
        std::string line;
        std::getline(file, line);
        result.push_back(line);
    }

    if (!file.good()) {
        std::cerr << "pri cteni souboru doslo k nejake chybe" << std::endl;
    }

    // vratit vysledek
    return result;
}

bool check_maze(std::vector<std::string> maze)
{
    int count_S = 0;
    int count_E = 0;

    for (std::string line : maze) {
        for (int i = 0; i < line.length(); i++) {
            // - pouze 4 povolene znaky: "# SE"
            //if (line[i] != '#' && line[i] != ' '
            //     && line[i] != 'S' && line[i] != 'E') {
            // python: if line[i] not in "# SE":
            // C++
            //if (! std::string("# SE").contains(line[i])) {
            if (std::string("# SE").find(line[i]) == std::string::npos) {
                std::cerr << "bludiste obsahuje nepovoleny znak: " << line[i] << std::endl;
                return false;
            }

            // - S a E se vyskytuji prave jednou
            if (line[i] == 'S') {
                count_S++;
            }
            if (line[i] == 'E') {
                count_E++;
            }
        }

        // - vsechny radky stejne dlouhe
        if (line.length() != maze[0].length()) {
            std::cerr << "bludiste nema vsechny radky stejne dlouhe" << std::endl;
            return false;
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

    return true;
}

std::vector<std::pair<int, int>> find_shortest_path(std::vector<std::string> maze)
{
    // nepotrebujeme graf - propojeni je v tom "maze"
    // vrcholy = policka bludiste
    // propojeni - urcime podle sousednich policek (mezera nebo #)

    // jak ukladat vrcholy - dvojice indexu (radek a sloupec) --> std::pair<int, int>
    // najit startovni vrchol
    using Vertex = std::pair<int, int>;
    Vertex start;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'S') {
                start.first = i;  // index radku
                start.second = j; // index sloupce
            }
        }
    }

    // mnozina nenavstivenych uzlu
    std::set<Vertex> Q;
    // vzdalenosti ze startu do vrcholu
    std::map<Vertex, int> dist;
    // predchudce vrcholu pro sestaveni cesty
    std::map<Vertex, Vertex> prev;

/* Inicializace:
    for each vertex v in Graph.Vertices:
        dist[v] ← INFINITY
        prev[v] ← UNDEFINED
        add v to Q
    dist[source] ← 0
*/
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            // preskocit nesmyslne pozice
            if (maze[i][j] == '#') {
                continue;
            }
            // zpracovat i,j-ty vrchol
            Vertex v(i, j);
            dist[v] = std::numeric_limits<int>::max();  // infinity
            // undefined nejde - staci nic nedelat
            Q.insert(v);
        }
    }
    dist[start] = 0;

    /*
    while Q is not empty:
        u ← vertex in Q with minimum dist[u]
        remove u from Q

        for each neighbor v of u still in Q:
            alt ← dist[u] + 1    [1 is a constant distance between neighbors - instead of Graph.Edges(u, v)]
            if alt < dist[v]:
                dist[v] ← alt
                prev[v] ← u
    */
    while (!Q.empty()) {
        // vertex in Q with minimum dist[u]
        Vertex u;
        int u_dist = std::numeric_limits<int>::max();  // infinity
        for (Vertex v : Q) {
            if (dist[v] < u_dist) {
                u = v;
                u_dist = dist[v];
            }
        }
        // remove u from Q
        Q.erase(u);

        // find neighbors of u
        std::vector<Vertex> neighbors;
        // zkontrolovat meze
        // zkontrolovat '#' na dane pozici
        if (u.first + 1 < maze.size() && maze[u.first + 1][u.second] != '#') {
            // soused nahore
            neighbors.push_back(Vertex(u.first + 1, u.second));
        }
        if (u.first > 0 && maze[u.first - 1][u.second] != '#') {
            // soused dole
            neighbors.push_back(Vertex(u.first - 1, u.second));
        }
        if (u.second + 1 < maze[u.first].size() && maze[u.first][u.second + 1] != '#') {
            // soused napravo
            neighbors.push_back(Vertex(u.first, u.second + 1));
        }
        if (u.second > 0 && maze[u.first][u.second - 1] != '#') {
            // soused nalevo
            neighbors.push_back(Vertex(u.first, u.second - 1));
        }

        // for each neighbor v of u still in Q:
        for (Vertex v : neighbors) {
            // alt ← dist[u] + 1    [1 is a constant distance between neighbors - instead of Graph.Edges(u, v)]
            // if alt < dist[v]:
            //    dist[v] ← alt
            //    prev[v] ← u
            int alt = dist[u] + 1;
            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
            }
        }
    }

    /* Rekonstrukce nejkratsi cesty:
    path ← empty sequence
    u ← target
    if prev[u] is defined or u = source:          // Proceed if the vertex is reachable
        while u is defined:                       // Construct the shortest path
            insert u at the beginning of path
            u ← prev[u]                           // Traverse from target to source
    */
    std::vector<Vertex> path;  // nema efektivni vkladani na zacatek, ale ted to nevadi :-)
    Vertex u;
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'E') {
                u.first = i;  // index radku
                u.second = j; // index sloupce
            }
        }
    }
    if (prev.count(u) == 1) {
        while (true) {
            // insert u at the beginning of path
            path.insert(path.begin(), u);
            if (prev.count(u) == 1) {
                // Traverse from target to source
                u = prev[u];
            }
            else {
                break;
            }
        }
    }

    return path;
}

int main()
{
    std::vector<std::string> maze = read_file("bludiste.txt");
    for (std::string line : maze) {
        std::cout << line << std::endl;
    }

    if (check_maze(maze)) {
        std::cout << "bludiste je v poradku" << std::endl;
        auto path = find_shortest_path(maze);

        std::cout << "nejkratsi cesta ma delku " << path.size() << ":" << std::endl;
        for (auto v : path) {
            std::cout << "(" << v.first << ", " << v.second << ")" << std::endl;

            // zvyrazneni cesty v bludisti
            if (maze[v.first][v.second] == ' ') {
                maze[v.first][v.second] = '+';
            }
        }

        // vypis vysledne bludiste
        for (std::string line : maze) {
            std::cout << line << std::endl;
        }
    }
    else {
        std::cout << "bludiste ma nejakou chybu" << std::endl;
    }
}
