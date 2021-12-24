//insertion tool for database project, created by wilmxre in 2021
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <map>

using namespace std;

bool isNumber(const string& str);
int generateRandom(int number);
string generateProductSeries(int len_alpha1, int len_num, int len_alpha2);
tuple<int, int, string> generateStorage();
int generatePrice();
string generateImageFormat();

int main() {

    srand(time(nullptr));
    //READING TABLE AND FIELD NAMES FROM FILE BELOW

    //outputs
    ofstream outptr;
    outptr.open("output_product-laptop.txt");

    if (!outptr) {
        cout << "error reading file!";
        exit(1);
    }

    ofstream outptr_img;
    outptr_img.open("output_product-laptop_img.txt");

    if (!outptr_img) {
        cout << "error reading file!";
        exit(1);
    }

    ofstream outptr_cat;
    outptr_cat.open("output_product-laptop_cat.txt");

    if (!outptr_cat) {
        cout << "error reading file!";
        exit(1);
    }

    //input1
    ifstream inptr;
    inptr.open("input_prod.txt");

    if (!inptr) {
        cout << "error reading from file!";
        exit(1);
    }

    //inpu2
    ifstream inptr_img;
    inptr_img.open("input_img.txt");

    if (!inptr_img) {
        cout << "error reading from file!";
        exit(1);
    }

    //input3
    ifstream inptr_cat;
    inptr_cat.open("input_cat.txt");

    if (!inptr_cat) {
        cout << "error reading from file!";
        exit(1);
    }

    //read from file1
    string table_name;
    string line;

    getline(inptr, table_name);

    vector<string> fields;
    vector<string> fields_img;
    vector<string> fields_cat;
    string();

    while (getline(inptr, line)) {
        fields.push_back(line);
        fields.emplace_back(", ");
    }

    fields.resize(fields.size() - 1);

    //read from file2
    string table_name2;

    getline(inptr_img, table_name2);

    while (getline(inptr_img, line)) {
        fields_img.push_back(line);
        fields_img.emplace_back(", ");
    }

    fields_img.resize(fields_img.size() - 1);

    //read from file3
    string table_name3;

    getline(inptr_cat, table_name3);

    while (getline(inptr_cat, line)) {
        fields_cat.push_back(line);
        fields_cat.emplace_back(", ");
    }

    fields_cat.resize(fields_cat.size() - 1);

    //------------LAPTOP NAMES------------

    ifstream inptr_laptops;
    inptr_laptops.open("laptop_brands.txt");

    if (!inptr_laptops) {
        cout << "error reading from file!";
        exit(1);
    }

    vector<string> laptop_names;
    map<int, string> brands;
    int key_brands = 1;
    while (getline(inptr_laptops, line)) {
        laptop_names.push_back(line);
        brands.insert(make_pair(key_brands++, line));
    }

    //------------------------------------

    //---------LAPTOP PROCESSORS----------

    ifstream inptr_laptop_processors;
    inptr_laptop_processors.open("laptop_processor.txt");

    if (!inptr_laptop_processors) {
        cout << "error reading from file!";
        exit(1);
    }

    vector<string> laptop_processors;
    map <int, string> processors;
    int key_proc = 1;
    while (getline(inptr_laptop_processors, line)) {
        laptop_processors.push_back(line);
        processors.insert(make_pair(key_proc++, line));
    }

   /* for (auto i = processors.begin(); i != processors.end(); i++) {
        cout << i->first << " " << i->second;
        cout << endl;
    }*/

    //------------------------------------

    //---------LAPTOP PROCESSORS----------

    ifstream inptr_laptop_gpus;
    inptr_laptop_gpus.open("laptop_gpu.txt");

    if (!inptr_laptop_gpus) {
        cout << "error reading from file!";
        exit(1);
    }

    vector<string> laptop_gpus;
    map<int, string> gpus;
    int key_gpu = 1;
    while (getline(inptr_laptop_gpus, line)) {
        laptop_gpus.push_back(line);
        gpus.insert(make_pair(key_gpu++, line));
    }

    //------------------------------------

    string laptop_name;
    string laptop_series;

    int nr_of_it;
    cout << "enter number of iteration!\n\tn:: ";
    cin >> nr_of_it;

    vector<string> img_ids;
    vector<int> random_brands;
    vector<int> random_processors;
    vector<int> random_gpus;
    vector<int> random_rams;
    vector<int> ram_size = { 1, 2, 4, 8, 12, 16, 24, 32, 48, 64 };
    vector<pair<int, int>> ind_pair;
    string img_id;

    //--------------------GENERATE PRODUCTS--------------------

    for (int i = 1; i <= nr_of_it; i++) {

        outptr << "INSERT INTO " << table_name << " (";

        for (auto & field : fields) {
            outptr << field;
        }

        outptr << ")\nVALUES (";

        outptr << to_string(i) << ", ";

//        laptop_name += laptop_names.at(generateRandom(laptop_names.size()));

        //-----INSERT PRODUCT NAME
        int rand_brand_ind;
        rand_brand_ind = generateRandom(brands.size()) + 1;
        random_brands.push_back(rand_brand_ind);

        laptop_name += brands[rand_brand_ind];
        laptop_series += generateProductSeries(1, 3, 2);
        outptr << "'Laptop " + laptop_name + " " + laptop_series << "', ";

        //-----INSERT PROCESSOR
        int rand_proc_ind = generateRandom(processors.size());
        random_processors.push_back(rand_proc_ind);
        outptr << "'This laptop comes with an Intel " + processors.at(rand_proc_ind) << " processor, ";

        //-----INSERT STORAGE

        auto tup = generateStorage();
        outptr << "a storage of " << get<2>(tup) << ", ";
        ind_pair.emplace_back(get<0>(tup) + 1, get<1>(tup) + 1);

        //-----INSERT RAM
        int rand_ram_ind = generateRandom(ram_size.size());
        random_rams.push_back(rand_ram_ind);
        outptr << to_string(ram_size.at(rand_ram_ind)) << "GB Ram and an ";

        //-----INSERT GPU
        int rand_gpu_ind = generateRandom(laptop_gpus.size());
        random_gpus.push_back(rand_gpu_ind);
        outptr << laptop_gpus.at(rand_gpu_ind) << " graphics card', ";

        //-----INSERT PRICE
        outptr << to_string(generatePrice() - 1) + ".99" << ", ";
        outptr << to_string(generateRandom(250)) << ", ";

        //-----CREATE IMAGE FORMAT
        transform(laptop_name.begin(), laptop_name.end(), laptop_name.begin(), [](unsigned char c) {return tolower(c); });
        transform(laptop_series.begin(), laptop_series.end(), laptop_series.begin(), [](unsigned char c) {return tolower(c); });
        laptop_name.erase(remove_if(laptop_name.begin(), laptop_name.end(), ::isspace), laptop_name.end());
        img_id += laptop_name + laptop_series + generateImageFormat();
        img_ids.push_back(img_id);


        outptr << "'" << img_id << "'";
        outptr << ");" << endl << endl;

        laptop_name = "";
        laptop_series = "";
        img_id = "";
    }

    //-----TEST CODE SNIPPETS HERE:

    /*for (auto & i : ind_pair) {
        cout << i.first + 1 << " " << i.second + 1<< endl;
    }*/



    //------------------GENERATE COMPONENTS------------------

    ofstream outptr_components;
    outptr_components.open("output_components");

      for (auto i = 0; i < nr_of_it; i++) {
        outptr_components << "INSERT INTO COMPONENTS(ID, PRODUCT_ID, PROCESSOR_ID, GPU_ID, RAM_ID, STORAGE_ID)\nVALUES(";
        outptr_components << to_string(i + 1) << ", " << to_string(i + 1) << ", ";
        outptr_components << random_processors.at(i) << ", ";
        outptr_components << random_gpus.at(i) + 1 << ", ";
        outptr_components << random_rams.at(i) + 1 << ", ";

        if (ind_pair.at(i).second % 2 == 0) {
            outptr_components << ind_pair.at(i).first * 2;
        }
        else {
            outptr_components << ind_pair.at(i).first * 2 - 1;
        }

        outptr_components << ");\n\n";
    }


    outptr_components.close();

    //----------------GENERATE PRODUCT IMAGES----------------

    int counter_img = 1;

    for (int i = 0; i < img_ids.size(); i++) {

        //------------first------------
        outptr_img << "INSERT INTO " << table_name2 << " (";

        for (auto & img : fields_img) {
            outptr_img << img;
        }


        outptr_img << ")\nVALUES (";
        outptr_img << counter_img++ << ", ";

        outptr_img << to_string(i+1) << ", ";

        img_id += img_ids.at(i);
        img_id.insert(img_id.find('.'), string("-1"));
        outptr_img << "'" << img_id<< "'";

        outptr_img << ");" << endl << endl;

        img_id = "";

        //------------second-----------
        outptr_img << "INSERT INTO " << table_name2 << " (";

        for (auto & img : fields_img) {
            outptr_img << img;
        }

        outptr_img << ")\nVALUES (";
        outptr_img << counter_img++ << ", ";

        outptr_img << to_string(i + 1) << ", ";

        img_id += img_ids.at(i);
        img_id.insert(img_id.find('.'), string("-2"));
        outptr_img << "'" << img_id << "'";

        outptr_img << ");" << endl << endl;

        img_id = "";

        //------------third------------
        outptr_img << "INSERT INTO " << table_name2 << " (";

        for (auto & img : fields_img) {
            outptr_img << img;
        }

        outptr_img << ")\nVALUES (";
        outptr_img << counter_img++ << ", ";

        outptr_img << to_string(i + 1) << ", ";

        img_id += img_ids.at(i);
        img_id.insert(img_id.find('.'), string("-3"));
        outptr_img << "'" << img_id << "'";

        outptr_img << ");" << endl << endl;

        img_id = "";

    }


    //------------GENERATE PRODUCT CATEGORIES------------

    for (int i = 0; i < nr_of_it; i++) {

        outptr_cat << "INSERT INTO " << table_name3 << " (";

        for (auto & field_cat : fields_cat) {
            outptr_cat << field_cat;
        }


        outptr_cat << ")\nVALUES (";

        outptr_cat << to_string(i + 1) << ", ";
        outptr_cat << to_string(i + 1) << ", ";

        outptr_cat << random_brands.at(i);

        outptr_cat << ");" << endl << endl;

        img_id = "";

    }


    //------------GENERATE CPU------------

    /*ofstream outptr_cpu;
    outptr_cpu.open("output_processor");


    for (auto & processor : processors) {
        outptr_cpu << "INSERT INTO PROCESSOR(ID, NAME)\nVALUES(";
        outptr_cpu << processor.first << ", '" << processor.second << "');\n\n";
    }


    outptr_cpu.close();*/

    //------------GENERATE GPU------------

   /* ofstream outptr_gpu;
    outptr_gpu.open("output_gpu");


    for (auto & gpu : gpus) {
        outptr_gpu << "INSERT INTO GPU(ID, NAME)\nVALUES(";
        outptr_gpu << gpu.first << ", '" << gpu.second << "');\n\n";
    }


    outptr_gpu.close();*/

    //------------GENERATE RAM------------

    /*ofstream outptr_ram;
    outptr_ram.open("output_ram");

    vector<int> temporary_ram = {1, 2, 4, 8, 12, 16, 24, 32, 48, 64};

    int counter_ram = 1;
    for (auto i : temporary_ram) {
       outptr_ram << "INSERT INTO RAM(ID, NAME)\nVALUES(";
       outptr_ram << counter_ram++ << ", '" << i << "GB');\n\n";
    }

    outptr_ram.close();*/

    //------------GENERATE STORAGE------------

    /*ofstream outptr_storage;
    outptr_storage.open("output_storage");

    vector<float> temporary_storage = {128, 240, 256, 500, 512, 1, 1.5, 2, 2.5};
    vector<string> temporary_storage_type = { "HDD", "SSD" };

    int counter_storage = 1;
    for (float i : temporary_storage) {
        for (auto & j : temporary_storage_type) {
            outptr_storage << "INSERT INTO STORAGE(ID, NAME)\nVALUES(";
            outptr_storage << counter_storage++ << ", '" << i;
            if (i > 3) {
                outptr_storage << "GB ";
            }
            else {
                outptr_storage << "TB ";
            }
            outptr_storage << j << "');\n\n";
        }
    }

    outptr_storage.close();*/

    //------------GENERATE BRANDS------------

    /*ofstream outptr_brands;
    outptr_brands.open("output_brands");


    for (auto & brand : brands) {
        outptr_brands << "INSERT INTO BRANDS(ID, NAME)\nVALUES(";
        outptr_brands << brand.first << ", '" << brand.second << "');\n\n";
    }


    outptr_brands.close();*/

    outptr.close();
    outptr_img.close();
    outptr_cat.close();
    inptr.close();
    inptr_cat.close();
    inptr_img.close();
    inptr_laptops.close();
    inptr_laptop_processors.close();
    inptr_laptop_gpus.close();

    return 0;
}

bool isNumber(const string& str) {

    for (char const& c : str) {
        if (isdigit(c) == 0) {
            return false;
        }
    }

    return true;
}

int generateRandom(int number) {
    return rand() % number;
}

string generateProductSeries(int len_alpha1, int len_num, int len_alpha2) {
    string s;
    static const char alpha[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    static const char num[] =
            "0123456789";

    for (int i = 0; i < len_alpha1; ++i) {
        s += alpha[rand() % (sizeof(alpha) - 1)];
    }

    for (int i = 0; i < len_num; ++i) {
        s += num[rand() % (sizeof(num) - 1)];
    }

    for (int i = 0; i < len_alpha2; ++i) {
        s += alpha[rand() % (sizeof(alpha) - 1)];
    }

    return s;
}

tuple<int, int, string> generateStorage() {

    map<int, string> storage;

    string storage_type[2] = { "HDD", "SSD" };
    float storage_size[9] = { 128, 240, 256, 500, 512, 1, 1.5, 2, 2.5 };

    float size;
    int ind_size;
    int ind_type;
    string s;

    ind_size = rand() % 9;

    size = storage_size[ind_size];

    string temp = to_string(size);

    if (size == 1.5 || size == 2.5) {
        temp.erase(temp.find_last_not_of('0') + 1, std::string::npos );
    }
    else {
        temp.erase(temp.find_last_not_of('0'), std::string::npos );
    }

    if (size < 3) {
        s += temp;
        s += "TB";
    }
    else {
        s += temp;
        s += "GB";
    }

    s += " ";
    ind_type = rand() % 2;
    s += storage_type[ind_type];

    return make_tuple(ind_size, ind_type, s);

}

int generatePrice() {

    int price = 1;

    while (price % 25 != 0) {
        price =  rand() % 12000 + 1200;
    }

    return price;
}

string generateImageFormat() {
    string s;

    string img_formats[4] = { ".jpg", ".png", ".jpeg", ".gif"};

    s += img_formats[rand() % 4];

    return s;
}