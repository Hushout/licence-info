#include <iostream>
#include <vector>
#include "array_functions.h"

int nb_vertices = 10;
const int inf = 10000;                    //La valeur infinie.
char cities[41][20] = {"Amiens", "Angouleme", "Avignon", "Bayonne", "Bilbao", "Bordeaux", "Bourges", "Brest", "Brive", "Bruxelles", "Caen", "Cahors", "Clermont-Ferrand", "Dijon", "Geneve", "Grenoble", "Lille", "Limoges", "Luxembourg", "Lyon", "Marseille", "Millau", "Montpellier", "Mulhouse", "Nancy", "Nantes", "Nice", "Orleans", "Paris", "Perpignan", "Poitiers", "Reims", "Rennes", "Rodez", "Rouen", "Saint-Etienne", "Strasbourg", "Toulouse", "Tours", "Troyes", "Valence"};

int position[41][2] = {{282,84},{180,334},{412,443},{140,455},{80,480},{165,389},{304,253},{14,150},{249,365},{380,15},{182,117},{258,412},{322,322},{408,231},{470,287},{464,359},{324,32},{242,332},{470,60},{405,306},{433,480},{339,440},{365,461},{497,208},{453,148},{116,233},{515,460},{277,194},{296,146},{329,505},{208,271},{369,119},{120,175},{330,410},{228,101},{383,339},{508,152},{227,466},{220,230},{363,179},{408,377}};

int kilometers[41][41];
using namespace std;

void floyd_warshall(int ** , int ** , int **);
void init_paths(int ** , int **);
void find_itinerary(int ** , int , int , vector<int> *);
void calculate_transitive_closure(int ** , int **);
void initialize_cities();
void generate_arcs(int ** , int);
int find_index_by_city_name(string);
void print_diameter(int ** , int , bool);

int main(int argc , char * argv[]){
    srand((u_int)time(NULL));
    int origin = 0 , destination = 0;
    int ** closure;
    int ** lengths;
    int ** distances;
    int ** paths;
    int ** adjacency;
    vector<int> itinerary (0);
    string city_name;
    bool cities_mode = false;
    
    if(argc > 1) {
        //passing "cities" in the command line arguments uses a prepared graph of cities
        if((string)argv[1] == "cities") {
            nb_vertices = 41;
            cities_mode = true;
            
        //otherwise you can pass the number of vertices as arguments. If there are no arguments, the default value is 10
        } else {
            char * p;
            nb_vertices = (int)strtol(argv[1] , &p , 10);
        }
    }
    
    //initialize all the arrays depending on the number of vertices or whether we're using the cities graph
    lengths = new int * [nb_vertices];
    adjacency = new int * [nb_vertices];
    closure = new int * [nb_vertices];
    distances = new int * [nb_vertices];
    paths = new int * [nb_vertices];
    for(int i = 0 ; i < nb_vertices ; i++) {
        lengths[i] = new int [nb_vertices];
        adjacency[i] = new int [nb_vertices];
        closure[i] = new int [nb_vertices];
        distances[i] = new int [nb_vertices];
        paths[i] = new int [nb_vertices];
    }
    
    if(cities_mode) {
        initialize_cities();
        for(int i = 0 ; i < nb_vertices ; i++)
            for(int j = 0 ; j < nb_vertices ; j++)
                lengths[i][j] = kilometers[i][j];
    } else
        generate_arcs(lengths , nb_vertices);
    
    for(int i = 0 ; i < nb_vertices ; i++)
        for(int j = 0 ; j < nb_vertices ; j++)
            if(lengths[i][j] != inf && lengths[i][j] != -1 && i != j)
                adjacency[i][j] = 1;
            else
                adjacency[i][j] = 0;
    
    //This is the start of the actual program
    cout << endl << "Applying Floyd-Warshall algorithm" << endl;
    init_paths(lengths, paths);
    floyd_warshall(lengths , distances , paths);
    
    //only print all the info if the graph has a maximum of 40 vertices, otherwise it gets unreadable
    if(nb_vertices <= 40) {
        cout << "ARC LENGTHS" << endl;
        if(cities_mode)
            print_cities(lengths , cities , nb_vertices , inf);
        else
            print_matrix(lengths , nb_vertices , inf);
        
        cout << endl << "DISTANCES" << endl;
        if(cities_mode)
            print_cities(distances , cities , nb_vertices , inf);
        else
            print_matrix(distances , nb_vertices , inf);
        
        cout << endl << "ADJACENCY" << endl;
        if(cities_mode)
            print_cities(adjacency , cities , nb_vertices , inf);
        else
            print_matrix(adjacency , nb_vertices , inf);
        
        cout << endl << "CLOSURE" << endl;
        calculate_transitive_closure(adjacency, closure);
        if(cities_mode)
            print_cities(closure , cities , nb_vertices , inf);
        else
            print_matrix(closure , nb_vertices , inf);
        
        cout << endl << "PATHS" << endl;
        if(cities_mode)
            print_cities_paths(paths , cities , nb_vertices , inf);
        else
            print_matrix(paths , nb_vertices , inf);
    }
    print_diameter(distances , nb_vertices , cities_mode);
    
    //lets you see the shortest path between any two vertices.
    //this part will keep prompting you until you force close the program
    while(true) {
        cout << "Where are you? ";
        if(cities_mode) {
            cout << "(name of a city) ";
            cin >> city_name;
            origin = find_index_by_city_name(city_name);
        } else {
            cout << "(integer between 0 and "<< nb_vertices - 1 <<") ";
            cin >> origin;
        }
        
        cout << "Where are you going? ";
        if(cities_mode) {
            cout << "(name of a city) ";
            cin >> city_name;
            destination = find_index_by_city_name(city_name);
        } else {
            cout << "(integer between 0 and "<< nb_vertices - 1 <<") ";
            cin >> destination;
        }
        find_itinerary(paths , origin , destination , &itinerary);
        
        if(!(itinerary.empty())) {
            for(int i = 0 ; i < itinerary.size() - 1 ; i++) {
                if(cities_mode)
                    cout << (string)cities[itinerary[i]] << " -> ";
                else
                    cout << itinerary[i] << " -> ";
            }
            if(cities_mode)
                cout << (string)cities[itinerary[itinerary.size() - 1]];
            else
                cout << itinerary[itinerary.size() - 1];
        } else
            cout << "There is no direct path from " << origin << " to " << destination;
        itinerary.clear();
        cout << endl;
    }
    return 0;
}

/**
 * The Floyd-Warshall algortihm that fills the distances and paths array
 */
void floyd_warshall(int ** lengths, int ** distances , int ** paths) {
    for(int i = 0 ; i < nb_vertices ; i++) {
        for(int j = 0 ; j < nb_vertices ; j++) {
            distances[i][j] = lengths[i][j];
        }
    }
    
    for(int k = 0 ; k < nb_vertices ; k++) {
        for(int i = 0 ; i < nb_vertices ; i++) {
            for(int j = 0 ; j < nb_vertices ; j++) {
                if(distances[i][j] > (distances[i][k] + distances[k][j])) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                    paths[i][j] = paths[i][k];
                }
            }
        }
    }
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        if(distances[i][i] < 0) {
            cout << "There is a cycle with negative weight at " << i << endl;
        }
    }
}

/**
 * An algorithm based on Floyd-Warshall that fills the transitive closure array
 */
void calculate_transitive_closure(int ** adjacency , int ** closure) {
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        for(int j = 0 ; j < nb_vertices ; j++) {
            closure[i][j] = adjacency[i][j];
        }
    }
    
    for(int k = 0 ; k < nb_vertices ; k++) {
        for(int i = 0 ; i < nb_vertices ; i++) {
            for(int j = 0 ; j < nb_vertices ; j++) {
                closure[i][j] = closure[i][j] || (closure[i][k] && closure[k][j]);
            }
        }
    }
}

/**
 * Finds the path between two vertices from the values in the paths array
 */
void find_itinerary(int ** paths , int origin , int destination , vector<int> * itinerary) {
    if(paths[origin][destination] == -1)
        return;
    itinerary->push_back(origin);
    origin = paths[origin][destination];
    if(origin == destination) {
        itinerary->push_back(destination);
        return;
    } else
        find_itinerary(paths , origin , destination , itinerary);
}

/**
 * Initializes the paths array with the default values
 */
void init_paths(int ** lengths , int ** paths) {
    for(int i = 0 ; i < nb_vertices ; i++) {
        for(int j = 0 ; j < nb_vertices ; j++) {
            if(lengths[i][j] != inf && i != j) paths[i][j] = j;
            else paths[i][j] = -1;
        }
    }
}

/**
 * Prints the diameter of the graph (longest distance between two vertices)
 */
void print_diameter(int ** distances , int nb_vertices , bool cities_mode) {
    int diameter = 0,
        x = 0 ,
        y = 0;
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        for(int j = 0 ; j < nb_vertices ; j++) {
            if(distances[i][j] != inf) {
                if(diameter != max(diameter , distances[i][j])) {
                    diameter = distances[i][j];
                    x = i;
                    y = j;
                }
            }
        }
    }
    if(cities_mode) cout << "The diameter of this graph is the path going from " << cities[x] << " to " << cities[y];
    else cout << "The diameter of this graph is the path going from " << x << " to " << y;
    cout << " with a length of " << diameter << endl;
}

/**
 * Returns the index of the city based on its name
 */
int find_index_by_city_name(string name) {
    for(int i = 0 ; i < 41 ; i++)
        if((string)cities[i] == name)
            return i;
    return 0;
}

/**
 * Generates random arcs so that each vertice in the graph has two outgoing arcs
 */
void generate_arcs(int ** lengths, int nb_vertices) {
    int nb_arcs[nb_vertices];
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        for(int j = 0 ; j < nb_vertices ; j++) {
            lengths[i][j] = inf;
        }
    }
    
    for(int i = 0 ; i < nb_vertices ; i++) {
        nb_arcs[i] = 0;
        int t1,
            t2;
        
        do {
            t1 = rand() % nb_vertices;
            t2 = rand() % nb_vertices;
        } while (t1 == t2 || t1 == i || t2 == i);
        
        lengths[i][t1] = 1;
        lengths[i][t2] = 1;
    }
}

/**
 * Initializes the graph with the prepared values corresponding to cities
 */
void initialize_cities() {
    for(int i = 0 ; i < 41 ; i++){
        for(int j = 0 ; j < 41 ; j++){
            kilometers[i][j] = inf;
        }
        kilometers[i][i]=0;
    }
    
    kilometers[0][34]=120; kilometers[0][28]=130;
    kilometers[0][31]=180; kilometers[0][16]=140;
    
    kilometers[1][30]=130;  kilometers[1][17]=110;
    kilometers[1][8]=170;  kilometers[1][5]=120;
    
    kilometers[2][40]=140;  kilometers[2][22]=90;
    kilometers[2][20]=90;
    
    kilometers[3][5]=180;  kilometers[3][37]=300;
    kilometers[3][4]=70;
    
    kilometers[4][3]=70;
    
    kilometers[5][1]=120; kilometers[5][8]=200; kilometers[5][11]=230;
    kilometers[5][37]=241; kilometers[5][3]=180;
    
    kilometers[6][27]=121; kilometers[6][39]=240; kilometers[6][13]=250;
    kilometers[6][12]=190; kilometers[6][38]=230;
    
    kilometers[7][32]=240;
    
    kilometers[8][11]=101; kilometers[8][17]=100; kilometers[8][1]=170;
    kilometers[8][5]=200; kilometers[8][33]=140;
    
    kilometers[9][16]=110; kilometers[9][31]=230; kilometers[9][18]=210;
    
    kilometers[10][34]=130; kilometers[10][38]=260; kilometers[10][32]=180;
    
    kilometers[11][21]=180; kilometers[11][8]=101; kilometers[11][5]=230;
    kilometers[11][37]=110; kilometers[11][33]=105;
    
    kilometers[12][6]=190; kilometers[12][19]=210; kilometers[12][35]=150;
    kilometers[12][17]=230; kilometers[12][33]=270;
    
    kilometers[13][19]=200; kilometers[13][23]=221; kilometers[13][24]=220;
    kilometers[13][39]=180; kilometers[13][6]=250; kilometers[13][14]=200;
    
    kilometers[14][15]=145; kilometers[14][19]=150; kilometers[14][13]=200;
    
    kilometers[15][26]=340; kilometers[15][20]=270; kilometers[15][40]=90;
    kilometers[15][19]=150; kilometers[15][14]=145;
    
    kilometers[16][0]=140; kilometers[16][31]=196; kilometers[16][9]=110;
    
    kilometers[17][30]=120; kilometers[17][1]=110; kilometers[17][8]=100;
    kilometers[17][12]=230;
    
    kilometers[18][31]=218; kilometers[18][36]=220; kilometers[18][9]=210;
    kilometers[18][24]=200;
    
    kilometers[19][40]=150; kilometers[19][35]=80; kilometers[19][12]=210;
    kilometers[19][13]=200; kilometers[19][14]=150; kilometers[19][15]=150;
    
    kilometers[20][22]=170; kilometers[20][2]=90; kilometers[20][26]=200;
    kilometers[20][15]=270;
    
    kilometers[21][37]=190; kilometers[21][11]=180; kilometers[21][22]=110;
    kilometers[21][33]=60;
    
    kilometers[22][29]=150; kilometers[22][37]=240; kilometers[22][21]=110;
    kilometers[22][2]=90; kilometers[22][20]=170; kilometers[22][40]=200;
    
    kilometers[23][13]=221; kilometers[23][24]=170; kilometers[23][36]=120;
    
    kilometers[24][36]=160; kilometers[24][23]=170; kilometers[24][13]=220;
    kilometers[24][31]=240; kilometers[24][18]=200;
    
    kilometers[25][32]=110; kilometers[25][38]=210; kilometers[25][30]=220;
    
    kilometers[26][20]=200; kilometers[26][15]=340;
    
    kilometers[27][6]=121; kilometers[27][39]=200; kilometers[27][28]=132;
    kilometers[27][38]=120;
    
    kilometers[28][0]=130; kilometers[28][34]=131; kilometers[28][27]=132;
    kilometers[28][39]=181; kilometers[28][31]=140;
    
    kilometers[29][37]=210; kilometers[29][22]=150;
    
    kilometers[30][25]=220; kilometers[30][38]=100; kilometers[30][17]=120;
    kilometers[30][1]=130;
    
    kilometers[31][24]=240; kilometers[31][28]=140; kilometers[31][39]=130;
    kilometers[31][0]=180; kilometers[31][16]=196; kilometers[31][9]=230;
    kilometers[31][18]=218;
    
    kilometers[32][10]=180; kilometers[32][38]=250; kilometers[32][7]=240;
    kilometers[32][25]=110;
    
    kilometers[33][35]=200; kilometers[33][40]=225; kilometers[33][21]=60;
    kilometers[33][8]=140; kilometers[33][11]=105; kilometers[33][12]=270;
    
    kilometers[34][0]=120; kilometers[34][28]=131; kilometers[34][10]=130;
    
    kilometers[35][12]=150; kilometers[35][19]=80; kilometers[35][40]=120;
    kilometers[35][33]=200;
    
    kilometers[36][23]=120; kilometers[36][24]=160; kilometers[36][18]=220;
    
    kilometers[37][3]=300; kilometers[37][5]=241; kilometers[37][11]=110;
    kilometers[37][21]=190; kilometers[37][22]=240; kilometers[37][29]=210;
    
    kilometers[38][10]=260; kilometers[38][32]=250; kilometers[38][25]=210;
    kilometers[38][30]=100; kilometers[38][27]=120; kilometers[38][6]=230;
    
    kilometers[39][31]=130; kilometers[39][28]=181; kilometers[39][27]=200;
    kilometers[39][6]=240; kilometers[39][13]=180;
    
    kilometers[40][2]=140; kilometers[40][15]=90; kilometers[40][35]=120;
    kilometers[40][19]=150; kilometers[40][33]=225; kilometers[40][22]=200;
    
}