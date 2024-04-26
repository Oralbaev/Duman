#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Структура 
struct Tovar {
    int id;
    string aty;
    double bahasy;
    int sanysy;
};

// Блокноттан құрылымға деректерді жүктеу функциясы
void yukleTovarlar(Tovar tovarlar[], int& san) {
    ifstream file("tovarlar.txt");
    san = 0;
    while (file >> tovarlar[san].id >> tovarlar[san].aty >> tovarlar[san].bahasy >> tovarlar[san].sanysy) {
        san++;
    }
    file.close();
}

// Деректерді құрылымнан блокнотқа сақтауға арналған функция
void Loading(Tovar tovarlar[], int san) {
    ofstream file("tovarlar.txt");
    for (int i = 0; i < san; i++) {
        file << tovarlar[i].id << " " << tovarlar[i].aty << " " << tovarlar[i].bahasy << " " << tovarlar[i].sanysy << endl;
    }
    file.close();
}

// Өнімді сатып алу функциясы
void satynAlu(Tovar tovarlar[], int san, int tovarId) {
    for (int i = 0; i < san; i++) {
        if (tovarlar[i].id == tovarId) {
            cout << "Сатып алыныз келе ме " << tovarlar[i].aty << " ушин " << tovarlar[i].bahasy << " тенге? (Y/N): ";
            char tanu;
            cin >> tanu;
            if (tanu == 'Y' || tanu == 'y') {
                if (tovarlar[i].sanysy > 0) {
                    tovarlar[i].sanysy--;
                    cout << "Сатып алу саттi аяkталды!" << endl;
                }
                else {
                    cout << "Кешiрiniз, тауар жок" << endl;
                }
            }
            return;
        }
    }
    cout << "Көрсетiлген идентификаторы бар тауар табылган жок." << endl;
}

// Өнім туралы ақпаратты шығару функциясы
void tovarTuralyAktaratu(Tovar tovarlar[], int san, int tovarId) {
    for (int i = 0; i < san; i++) {
        if (tovarlar[i].id == tovarId) {
            cout << "Тауар туралы акпарат (id " << tovarlar[i].id << "):" << endl;
            cout << "Аты: " << tovarlar[i].aty << endl;
            cout << "Бағасы: " << tovarlar[i].bahasy << " теңге" << endl;
            cout << "Саны: " << tovarlar[i].sanysy << endl;
            return;
        }
    }
    cout << "Кoрсетiлген идентификаторы бар тауар табылган жок." << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    const int M_MAX_Tovarlar = 100;
    Tovar tovarlar[M_MAX_Tovarlar];
    int tovarSan = 0;

    // Деректерді блокноттан жүктеу
    yukleTovarlar(tovarlar, tovarSan);

    char tanu;
    do {
        cout << "ToiDuman дүкенiне kош келдiniз. Aрекетті таnдаnыз (Y - сатып алу, I - аkпарат, N - аяkтау): ";
        cin >> tanu;
        if (tanu == 'Y' || tanu == 'y') {
            int tovarId;
            cout << "Сатып алу үшiн тауардыn ID енгiзiңiз: ";
            cin >> tovarId;
            satynAlu(tovarlar, tovarSan, tovarId);
        }
        else if (tanu == 'I' || tanu == 'i') {
            int tovarId;
            cout << "Аkпарат алу үшiн тауардыn идентификаторын енгiзiнiз: ";
            cin >> tovarId;
            tovarTuralyAktaratu(tovarlar, tovarSan, tovarId);
        }
    } while (tanu != 'N' && tanu != 'n');
    cout << "Бiздiн дүкенiмiзбен арекет жасаганызга рахмет, саттылык!";

    // Деректерді блокнотқа сақтау
    Loading(tovarlar, tovarSan);

    return 0;
}
