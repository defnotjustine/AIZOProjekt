#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono> // Biblioteka do pomiaru czasu

using namespace std;
using namespace std::chrono;

// Szablon funkcji do wypisywania tablicy na ekranie
template<typename T>
void printArray(T arr[], int size) {
    for(int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
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
void generateRandomArray(T arr[], int size) {
    srand(time(nullptr)); // Inicjalizacja generatora liczb pseudolosowych
    for(int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000; // Zakres 0-999 dla przykładu
    }
}

// Funkcja do wczytywania danych z pliku
template<typename T>
void loadArrayFromFile(T arr[], int& size, const string& filename) {
    ifstream file(filename); // Tworzenie strumienia do odczytu z pliku
    if(file.is_open()) {
        file >> size; // Wczytanie rozmiaru tablicy z pliku
        for(int i = 0; i < size; ++i) {
            file >> arr[i]; // Wczytanie kolejnych elementów tablicy
        }
        file.close(); // Zamknięcie pliku
    }
    else {
        cout << "Nie udalo sie otworzyc pliku." << endl; // Komunikat o błędzie
    }
}

// Funkcja do menu 1 poziomu

void displayMenu1(){
    cout << "Menu:" << endl;
    cout << "Wybierz typ danych:" << endl;
    cout << "a) int" << endl;
    cout << "b) float" << endl;
    cout << "Wybierz opcje: ";
}

// Funkcja do menu 1 poziomu

void displayMenu2() {
    cout << "Menu:" << endl;
    cout << "a) Wczytaj tablice z pliku" << endl;
    cout << "b) Wygeneruj tablice losowych wartosci" << endl;
    cout << "c) Wyswietl tablice" << endl;
    cout << "d) Uruchom algorytm sortowania" << endl;
    cout << "e) Wyswietl posortowana tablice" << endl;
    cout << "q) Wyjscie z programu" << endl;
    cout << "Wybierz opcje: ";
}

char menu1(){
    char choice;
    cin >> choice;
    if(choice == 'a' || choice == 'b' || choice == 'q'){
        return choice;
    }
    else {
        cout << "Blad! Prosze wybrac 'a' lub 'b'. Jesli chcesz wyjsc z programu nacisnij 'q'" << endl;
        menu1();
    }
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

int main() {
    char choiceOfType, choice;
    int size;
    string filename;
    int* arr = nullptr;

    while(true) {
        displayMenu1();
        choiceOfType = menu1(); // a - int, b - float, q - exit
        displayMenu2(); // Wyświetlenie menu
        cin >> choice; // Wczytanie wyboru użytkownika

        switch(choice) {
            case 'a':
                cout << "Podaj nazwe pliku: ";
                cin >> filename;
                loadArrayFromFile(arr, size, filename); // Wczytanie tablicy z pliku
                break;
            case 'b':
                cout << "Podaj rozmiar tablicy: ";
                cin >> size;
                if(choiceOfType == 'a'){
                    arr = new int[size];
                    generateRandomArray(arr, size); // Wygenerowanie tablicy losowych wartości
                }
                else if(choiceOfType == 'b'){
                    float* arrFloat = nullptr;
                    arrFloat = new float[size];
                    generateRandomArray(arrFloat, size); // Wygenerowanie tablicy losowych wartości
                }
                break;
            case 'c':
                if(arr == nullptr) {
                    cout << "Tablica nie zostala jeszcze utworzona." << endl;
                }
                else {
                    cout << "Tablica: ";
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
                cout << "Koniec programu." << endl;
                return 0;
            default:
                cout << "Niepoprawny wybor." << endl;
                break;
        }
    }

    return 0;
}
