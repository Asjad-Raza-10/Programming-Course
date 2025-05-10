#include <iostream>
using namespace std;

int main() {
    
    int total_population = 80000;
    cout << "Given total population of the town: "<<total_population<<endl;

    float men_percentage = 52.0;
    float literacy_percentage = 48.0;
    float literate_men_percentage = 35.0;

    cout << "Given percentage of men in population: " << men_percentage << endl<<endl;

    
    int men = (men_percentage / 100) * total_population;
    int women = total_population - men;

    cout << "Total number of men in population: " << men << endl << "Total number of women in population: " << women << endl<<endl;

    
    cout << "Given literacy percentage: " << literacy_percentage << endl << "Given men literacy percentage: " << literate_men_percentage << endl << endl;

    int total_literate_people = (literacy_percentage / 100) * total_population;
    int literate_men = (literate_men_percentage / 100) * total_population;
    cout << "Total literate people: " << total_literate_people << endl << "Total literate men: " << literate_men << endl;

    
    int literate_women = total_literate_people - literate_men;
    cout << "Total literate women: " << literate_women << endl<<endl;


    int illiterate_men = men - literate_men;
    cout << "Total illiterate men: " << illiterate_men << endl;

    int illiterate_women = women - literate_women;
    cout << "Total illiterate women: " << illiterate_women << endl << endl;

    return 0;
}

