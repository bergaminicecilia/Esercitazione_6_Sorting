# include "SortingAlgorithm.hpp"
# include <chrono>
# include <numeric>
# include <algorithm>
# include <vector>
# include <cstdlib>
# include <ctime>
# include <random>
# include <iomanip>
# include <iostream>
# include <sstream>

using namespace std;
using namespace SortLibrary;

template <typename T>
vector<T> generateVector(int size){
    vector<T> vec;
    vec.reserve(size);
    for(int i = 0; i < size; ++i)
    {
        if(is_integral<T>::value)
        {
            vec.push_back(rand()%1000);
        }
        else
        {
            vec.push_back(static_cast<T>(rand())/static_cast<T>(RAND_MAX));
        }
    }
    return vec;
}


template <typename T>
double time_BubbleSort(vector<T>& v){

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    BubbleSort(v);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    double timeElapsed = chrono::duration_cast<chrono::microseconds> (end - start).count();

    return timeElapsed;
}

template <typename T>
double time_MergeSort(vector<T>& v){

    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    MergeSort(v);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    double timeElapsed = chrono::duration_cast<chrono::microseconds> (end - start).count();

    return timeElapsed;
}

double avarage(vector<double>& v){
    double sum = accumulate(v.begin(), v.end(), 0);
    double mean = sum/size(v);
    return mean;
}

string generateChar(const unsigned int len){
    const int max = 26;
    char alphabet[max] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                           'i', 'j', 'k','l', 'm', 'n', 'o', 'p',
                          'q', 'r', 's', 't', 'u', 'v','w', 'x', 'y', 'z'};
    string stringa = "";
    for(unsigned int i = 0; i <len; i++)
    {
        stringa +=  alphabet[rand()%max];
    }
    return stringa;
}


int main(int argc, char ** argv)
{
    unsigned int num_mis = 1000;
    unsigned int dim_vec;
    istringstream converter(argv[1]);
    converter >> dim_vec;

    cout << scientific << setprecision(4);

    // 1a. vettore con elementi interi in ordine crescente
    cout << endl;
    vector<double> time_BS_crescente(num_mis);
    vector<double> time_MS_crescente(num_mis);
    time_BS_crescente.reserve(num_mis);
    time_MS_crescente.reserve(num_mis);

    for(unsigned int i = 0; i < num_mis; i++)
    {
        vector<int> v1(dim_vec);
        vector<int> v2(dim_vec);
        iota(v1.begin(), v1.end(), i);
        v2 = v1;

        time_BS_crescente[i] = time_BubbleSort(v1);
        time_MS_crescente[i] = time_MergeSort(v2);
    }
    cout << "1a." << endl;
    cout << "Measures with vectors of int elements sorted in ascending order with dimension " << dim_vec << "." << endl;
    cout << "Avarage time with BubbleSort algorithm: " << avarage(time_BS_crescente) << endl;
    cout << "Avarage time with MergeSort algorithm: " << avarage(time_MS_crescente) << endl;

    // 1b. vettore con elementi interi metà ordinati e metà no
    cout << endl;
    vector<double> time_BS_mix(num_mis);
    vector<double> time_MS_mix(num_mis);
    time_BS_mix.reserve(num_mis);
    time_MS_mix.reserve(num_mis);

    for(unsigned int i = 0; i < num_mis; i++)
    {
        vector<int> v1(dim_vec);
        vector<int> v2(dim_vec);
        iota(v1.begin(), v1.end(), i);

        for(unsigned int j = dim_vec/2; j<dim_vec; j++){
            v1[j] = rand() % 101;
        }

        v2 = v1;

        time_BS_mix[i] = time_BubbleSort(v1);
        time_MS_mix[i] = time_MergeSort(v2);
    }
    cout << "1b." << endl;
    cout << "Measures with vectors of int elements half sorted in ascending order and half generated randomly with dimension " << dim_vec << "." << endl;
    cout << "Avarage time with BubbleSort algorithm: " << avarage(time_BS_mix) << endl;
    cout << "Avarage time with MergeSort algorithm: " << avarage(time_MS_mix) << endl;


    // 1c. vettore con elementi interi in ordine decrescente
    cout << endl;
    vector<double> time_BS_decrescente(num_mis);
    vector<double> time_MS_decrescente(num_mis);
    time_BS_decrescente.reserve(num_mis);
    time_MS_decrescente.reserve(num_mis);

    for(unsigned int i = 0; i < num_mis; i++)
    {
        vector<int> v1(dim_vec);
        vector<int> v2(dim_vec);
        unsigned int j = dim_vec + i;
        generate(v1.begin(), v1.end(), [&j] () {return j--; });

        v2 = v1;

        time_BS_decrescente[i] = time_BubbleSort(v1);
        time_MS_decrescente[i] = time_MergeSort(v2);
    }
    cout << "1c." << endl;
    cout << "Measures with vectors of int elements sorted in descending order with dimension " << dim_vec << "." << endl;
    cout << "Avarage time with BubbleSort algorithm: " << avarage(time_BS_decrescente) << endl;
    cout << "Avarage time with MergeSort algorithm: " << avarage(time_MS_decrescente) << endl;


    // 1d. vettore con elementi randomici interi
    cout << endl;
    vector<double> time_BS_int_random(num_mis);
    vector<double> time_MS_int_random(num_mis);
    time_BS_int_random.reserve(num_mis);
    time_MS_int_random.reserve(num_mis);

    for(unsigned int i = 0; i < num_mis; i ++)
    {
        vector<int> v1 = generateVector<int>(dim_vec);
        vector<int> v2 = v1;
        time_BS_int_random[i] = time_BubbleSort(v1);
        time_MS_int_random[i] = time_MergeSort(v2);
    }
    cout << "1d." << endl;
    cout << "Measures with vectors of int random elements with dimension " << dim_vec << "." << endl;
    cout << "Avarage time with BubbleSort algorithm: " << avarage(time_BS_int_random) << endl;
    cout << "Avarage time with MergeSort algorithm: " << avarage(time_MS_int_random) << endl;

    // 1e. vettore con elementi quintuplicati
    cout << endl;
    vector<double> time_BS_int_random_new(num_mis);
    vector<double> time_MS_int_random_new(num_mis);
    time_BS_int_random_new.reserve(num_mis);
    time_MS_int_random_new.reserve(num_mis);

    unsigned int dim_vec_new = 5*dim_vec;
    for(unsigned int i = 0; i < num_mis; i ++)
    {
        vector<int> v1 = generateVector<int>(dim_vec_new);
        vector<int> v2 = v1;
        time_BS_int_random_new[i] = time_BubbleSort(v1);
        time_MS_int_random_new[i] = time_MergeSort(v2);
    }
    cout << "1e." << endl;
    cout << "Measures with vectors of int random elements with dimension " << dim_vec_new << "." << endl;
    cout << "Avarage time with BubbleSort algorithm: " << avarage(time_BS_int_random_new) << endl;
    cout << "Avarage time with MergeSort algorithm: " << avarage(time_MS_int_random_new) << endl;

    // 1f. vettore con elementi decuplicati
    cout << endl;
    vector<double> time_BS_int_random_new2(num_mis);
    vector<double> time_MS_int_random_new2(num_mis);
    time_BS_int_random_new2.reserve(num_mis);
    time_MS_int_random_new2.reserve(num_mis);

    unsigned int dim_vec_new2 = 10*dim_vec;
    for(unsigned int i = 0; i < num_mis; i ++)
    {
        vector<int> v1 = generateVector<int>(dim_vec_new2);
        vector<int> v2 = v1;
        time_BS_int_random_new2[i] = time_BubbleSort(v1);
        time_MS_int_random_new2[i] = time_MergeSort(v2);
    }
    cout << "1f." << endl;
    cout << "Measures with vectors of int random elements with dimension " << dim_vec_new2 << "." << endl;
    cout << "Avarage time with BubbleSort algorithm: " << avarage(time_BS_int_random_new2) << endl;
    cout << "Avarage time with MergeSort algorithm: " << avarage(time_MS_int_random_new2) << endl;



    // 2. vettore con elementi randomici floating point
    cout << endl;
    vector<double> time_BS_float_random(num_mis);
    vector<double> time_MS_float_random(num_mis);
    time_BS_float_random.reserve(num_mis);
    time_MS_float_random.reserve(num_mis);

    for(unsigned int i = 0; i < num_mis; i ++)
    {
        vector<float> v1 = generateVector<float>(dim_vec);
        vector<float> v2 = v1;
        time_BS_float_random[i] = time_BubbleSort(v1);
        time_MS_float_random[i] = time_MergeSort(v2);
    }
    cout << "2." << endl;
    cout << "Measures with vectors of float random elements with dimension " << dim_vec << "." << endl;
    cout << "Avarage time with BubbleSort algorithm: " << avarage(time_BS_float_random) << endl;
    cout << "Avarage time with MergeSort algorithm: " << avarage(time_MS_float_random) << endl;


    // 3. vettore con elementi randomici caratteri
    cout << endl;
    vector<double> time_BS_char_random(num_mis);
    vector<double> time_MS_char_random(num_mis);
    time_BS_char_random.reserve(num_mis);
    time_MS_char_random.reserve(num_mis);

    const unsigned int dim_string = 20;
    for(unsigned int i = 0; i < num_mis; i ++)
    {
        vector<string> v1(dim_vec);
        vector<string> v2(dim_vec);

        for(unsigned int j = 0; j<dim_vec; j++)
        {
            v1[j] = generateChar(dim_string);
        }

        time_BS_char_random[i] = time_BubbleSort(v1);
        time_MS_char_random[i] = time_MergeSort(v2);
    }
    cout << "3." << endl;
    cout << "Measures with vectors of char random elements with dimension " << dim_vec << "." << endl;
    cout << "Avarage time with BubbleSort algorithm: " << avarage(time_BS_char_random) << endl;
    cout << "Avarage time with MergeSort algorithm: " << avarage(time_MS_char_random) << endl;


    return 0;
}

