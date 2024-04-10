#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono> // Biblioteka do pomiaru czasu
#include <random>

using namespace std;
using namespace std::chrono;

// Szablon funkcji do wypisywania tablicy na ekranie
template<typename T>
void printArray(T arr[], int size) {
    if(size <= 50){
        for(int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    else {
        cout << "Rozmiar tablicy jest wiekszy od 50 elementow" << endl;
    }
}

// Szablon funkcji do weryfikacji, czy tablica jest posortowana
template<typename T>
bool isSorted(T arr[], int size) {
    for(int i = 1; i < size; ++i) {
        if(arr[i] < arr[i-1]) {
            return false;
        }
    }
    return true;
}

// Implementacja sortowania przez wstawianie (Insertion Sort)
template<typename T>
void insertionSort(T arr[], int size) {
    for(int i = 1; i < size; ++i) {
        T key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Implementacja sortowania przez scalanie (Merge Sort)
template<typename T>
void merge(T arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    T L[n1], R[n2];

    for(int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; ++j)
        R[j] = arr[middle + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template<typename T>
void mergeSortHelper(T arr[], int left, int right) {
    if(left < right) {
        int middle = left + (right - left) / 2;
        mergeSortHelper(arr, left, middle);
        mergeSortHelper(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

template<typename T>
void mergeSort(T arr[], int size) {
    mergeSortHelper(arr, 0, size - 1);
}

// Implementacja sortowania bąbelkowego (Bubble Sort)
template<typename T>
void bubbleSort(T arr[], int size) {
    for(int i = 0; i < size - 1; ++i) {
        for(int j = 0; j < size - i - 1; ++j) {
            if(arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Funkcja do generowania losowych danych
template<typename T>
void generateRandomArray(T arr[], int size, char dataType) {
    int min_int = std::numeric_limits<int>::min(); // Najmniejsza wartość typu int
    int max_int = std::numeric_limits<int>::max(); // Największa wartość typu int
    float min_float = std::numeric_limits<float>::lowest(); // Najmniejsza wartość typu float
    float max_float = std::numeric_limits<float>::max();    // Największa wartość typu float
    srand(time(nullptr)); // Inicjalizacja generatora liczb pseudolosowych
    if(dataType == 'a'){
        // Inicjalizacja generatora liczb losowych
        random_device rd;
        mt19937 gen(rd());

        // Określenie rozkładu liczbowego (int_min do int_max)
        uniform_int_distribution<int> distribution(min_int, max_int);
        for(int i = 0; i < size; ++i){
            arr[i] = distribution(gen);
        }
    }
    else if(dataType == 'b'){
        // Utwórz generator liczb losowych
        random_device rd;
        default_random_engine generator(rd());

        uniform_real_distribution<double> distribution(min_float, max_float);

        for(int i = 0; i < size; ++i){
            arr[i] = distribution(generator);
        }
    }
    //OLD VERSION
    /*
    for(int i = 0; i < size; ++i) {
        arr[i] = static_cast<T>(rand());
        //arr[i] = rand() % 1000; // Zakres 0-999 dla przykładu
    }
     */
}

// Funkcja do wczytywania danych z pliku
template<typename T>
T* loadArrayFromFile(T arr[], int& size, const string& filepath) {
    ifstream file(filepath); // Tworzenie strumienia do odczytu z pliku
    if (file.is_open()) {
        file >> size;
        arr = new T[size];
        for (int i = 0; i < size; ++i) {
            file >> arr[i];
        }
        file.close();
        return arr;
    }
    else {
        cout << "Nie udalo sie otworzyc pliku. Sprawdz czy poprawnie wpisales nazwe." << endl; // Komunikat o błędzie
    }
}

// Funkcja do menu 1 poziomu

void displayMenu1(){
    cout << "Menu 1:" << endl;
    cout << "Wybierz typ danych:" << endl;
    cout << "a) int" << endl;
    cout << "b) float" << endl;
    cout << "q) wyjscie z programu" << endl;
    cout << "Wybierz opcje: ";
}

// Funkcja do menu 1 poziomu

void displayMenu2() {
    cout << "Menu 2:" << endl;
    cout << "a) Wczytaj tablice z pliku" << endl;
    cout << "b) Wygeneruj tablice losowych wartosci" << endl;
    cout << "c) Wyswietl tablice" << endl;
    cout << "d) Uruchom algorytm sortowania" << endl;
    cout << "e) Wyswietl posortowana tablice" << endl;
    cout << "q) Wyjscie z programu" << endl;
    cout << "Wybierz opcje: ";
}


// Funkcja do pomiaru czasu sortowania
template<typename T>
double measureSortingTime(void (*sortFunc)(T[], int), T arr[], int size) {
    auto start = high_resolution_clock::now(); // Początek pomiaru czasu
    sortFunc(arr, size); // Wywołanie funkcji sortującej
    auto stop = high_resolution_clock::now(); // Koniec pomiaru czasu
    auto duration = duration_cast<milliseconds>(stop - start); // Obliczenie czasu trwania sortowania
    return duration.count(); // Zwrócenie czasu sortowania w milisekundach
}

template<typename T>
string menu2(char dataType){
    char choice;
    int size;
    string filepath;
    string program = "run";
    T* arr = nullptr;
    //int* arr = nullptr;

    while(program == "run") {
        displayMenu2(); // Wyświetlenie menu
        cin >> choice; // Wczytanie wyboru użytkownika

        switch(choice) {
            case 'a':
                cout << "Podaj nazwe sciezki pliku: ";
                cin >> filepath;
                arr = loadArrayFromFile(arr, size, filepath); // Wczytanie tablicy z pliku
                break;
            case 'b':
                cout << "Podaj rozmiar tablicy: ";
                cin >> size;
                arr = new T[size];
                generateRandomArray(arr, size, dataType);
                /*
                if(dataType == 'a'){
                    arr = new int[size];
                    generateRandomArray(arr, size); // Wygenerowanie tablicy losowych wartości
                }
                else if(dataType == 'b'){
                    float* arrFloat = nullptr;
                    arrFloat = new float[size];
                    generateRandomArray(arrFloat, size); // Wygenerowanie tablicy losowych wartości
                }
                */
                break;
            case 'c':
                if(arr == nullptr) {
                    cout << "Tablica nie zostala jeszcze utworzona." << endl;
                }
                else {
                    cout << "Tablica: " << endl;
                    printArray(arr, size); // Wyświetlenie tablicy
                }
                break;
            case 'd':
                if(arr == nullptr) {
                    cout << "Tablica nie zostala jeszcze utworzona." << endl;
                }
                else {
                    cout << "Wybierz algorytm sortowania:" << endl;
                    cout << "1. Sortowanie przez wstawianie" << endl;
                    cout << "2. Sortowanie przez scalanie" << endl;
                    cout << "3. Sortowanie babelkowe" << endl;
                    cout << "Wybierz opcje: ";
                    char sortChoice;
                    cin >> sortChoice;

                    switch(sortChoice) {
                        case '1':
                            cout << "Czas sortowania przez wstawianie: " << measureSortingTime(insertionSort, arr, size) << " ms" << endl;
                            break;
                        case '2':
                            cout << "Czas sortowania przez scalanie: " << measureSortingTime(mergeSort, arr, size) << " ms" << endl;
                            break;
                        case '3':
                            cout << "Czas sortowania babelkowego: " << measureSortingTime(bubbleSort, arr, size) << " ms" << endl;
                            break;
                        default:
                            cout << "Niepoprawny wybor algorytmu sortowania." << endl;
                            break;
                    }

                    // Weryfikacja poprawności sortowania
                    if(isSorted(arr, size)) {
                        cout << "Tablica zostala poprawnie posortowana." << endl;
                    }
                    else {
                        cout << "Blad: Tablica nie zostala poprawnie posortowana." << endl;
                    }
                }
                break;
            case 'e':
                if(arr == nullptr) {
                    cout << "Tablica nie zostala jeszcze utworzona." << endl;
                }
                else {
                    cout << "Posortowana tablica: ";
                    printArray(arr, size); // Wyświetlenie posortowanej tablicy
                }
                break;
            case 'q':
                if(arr != nullptr) {
                    delete[] arr; // Zwolnienie pamięci
                }
                cout << "Wyjscie z menu 2." << endl;
                cout << " " << endl;
                program = "exit";
                return program;
            default:
                cout << "Niepoprawny wybor." << endl;
                break;
        }
    }
}


int main() {
    char choiceOfType;

    while(true) {
        displayMenu1();
        cin >> choiceOfType;
        switch(choiceOfType){
            case 'a' :
                menu2<int>(choiceOfType);
                break;
            case 'b' :
                menu2<float>(choiceOfType);
                break;
            case 'q':
                cout << "Koniec programu." << endl;
                return 0;
            default:
                cout << "Niepoprawny wybor." << endl;
                break;
        }
    }

    return 0;
}
