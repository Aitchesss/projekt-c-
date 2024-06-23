#include <iostream>
#include <cmath>
#include <windows.h>
#include <cstring>

using namespace std;

const string NazwaProgramu = "Wypozyczalnia Pojazdow";

void wyswietlZnaki(char znak, int dlugosc) {
	for (int i = 0; i < dlugosc; i++){
        cout << znak;
    }
}

void dekorujNapis(string napis, char znak, int szer) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
    int szerokoscUdekorowanegoNapisu = szer;
    float dlugoscDekoracji = (szerokoscUdekorowanegoNapisu - (napis.length() + 2)) / 2.0;

    wyswietlZnaki(znak, dlugoscDekoracji);
    cout << ' ' << napis << ' ';
    wyswietlZnaki(znak, ceil(dlugoscDekoracji));
    cout << endl;
}

void menuGlowne() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    cout << "1. Wypozycz pojazd" << endl;
    cout << "2. Zwroc pojazd" << endl;
    cout << "3. Jedz" << endl;
    cout << "4. Zatankuj" << endl;
    cout << "5. Wyjscie" << endl;
}

void wyborPojazdu(string napis) {
    system("cls");
    dekorujNapis(napis, '-', 40);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
    cout << "1. Samochod" << endl;
    cout << "2. Motocykl" << endl;
    cout << "3. Wroc" << endl;
}

class Pojazd {
protected:
    string marka;	
    string model;
    int id;
    bool dostepny;
    float iloscPaliwa;
    float pojemnoscBaku;
public:
    Pojazd(string marka, string model, int id, bool dostepny, float iloscPaliwa, float pojemnoscBaku)
        : marka(marka), model(model), id(id), dostepny(dostepny), 
		iloscPaliwa(iloscPaliwa), pojemnoscBaku(pojemnoscBaku) {}
    
	virtual void wyswietlInformacje() const = 0;  // Pure virtual function
	
    bool czyDostepny() const {
        return dostepny;
    }
    void wypozycz() {
        dostepny = false;
    }
    void zwroc() {
        dostepny = true;
    }
    int getId() const {
        return id;
    }
    string getModel() const {
        return model;
    }

};

class Samochod : public Pojazd {
private:
    int moc;
    int iloscMiejsc;
    string typNadwozia;

public:
    Samochod(string marka, string model, int id, bool dostepny, float iloscPaliwa, float pojemnoscBaku,
	int moc, int iloscMiejsc, string typNadwozia)
        : Pojazd(marka, model, id, dostepny, iloscPaliwa, pojemnoscBaku), moc(moc), iloscMiejsc(iloscMiejsc), typNadwozia(typNadwozia) {}
        
    void wyswietlInformacje()const {
        cout << marka << " " << model << ", " << moc << "KM, " << "ilosc miejsc: " << iloscMiejsc << ", typ nadwozia: " 
		<< typNadwozia << ", Paliwo: " << iloscPaliwa << "/" << pojemnoscBaku << " l, nr katalogowy: " << id <<  endl;
	}
	
	void jedz(float& odleglosc) {
		float zuzycie = odleglosc * 0.18;
		if(iloscPaliwa >= zuzycie) {
			iloscPaliwa -= zuzycie;
			cout << "Przejechales " << odleglosc << " km. Pozostaly poziom paliwa: " << iloscPaliwa << endl;
		}else {
			zwroc();
			cout << "Zabraklo ci paliwa na trasie, samochod zostal odholowany" <<  endl;	
		}
	}
	
	void tankuj(float& ile) {
		iloscPaliwa+=ile;
		if(iloscPaliwa <= pojemnoscBaku) cout << "Zatankowano " << ile << "l paliwa" << endl;
		else {
            cout << "Rozlales " << iloscPaliwa-pojemnoscBaku << "l paliwa" << endl;
        iloscPaliwa=pojemnoscBaku;
        }
	}
};

class Motocykl : public Pojazd {
	private:
		int pojemnosc;
		string typSilnika;
		string rodzaj;
	public:
		Motocykl(string marka, string model, int id, bool dostepny, float iloscPaliwa, float pojemnoscBaku, 
		int pojemnosc, string typSilnika, string rodzaj)
		:Pojazd(marka, model, id, dostepny, iloscPaliwa, pojemnoscBaku), pojemnosc(pojemnosc), typSilnika(typSilnika), rodzaj(rodzaj) {}
		
		void wyswietlInformacje() const {
        cout << marka << " " << model << ", " << pojemnosc << "CC, " << "typ silnika: " << typSilnika << ", typ motocykla: " << rodzaj << ", Paliwo: " << iloscPaliwa << "/" << pojemnoscBaku << " l, nr katalogowy: " << id <<  endl;
    	}
    	void jedz(float& odleglosc) {
		float zuzycie = odleglosc * 0.18;
		if(iloscPaliwa >= zuzycie) {
			iloscPaliwa -= zuzycie;
			cout << "Przejechales " << odleglosc << " km. Pozostaly poziom paliwa: " << iloscPaliwa << endl;
		}else {
			zwroc();
			cout << "Zabraklo ci paliwa na trasie, motocykl zostal odholowany" <<  endl;	
		}
	}
	
	void tankuj(float& ile) {
		iloscPaliwa+=ile;
		if(iloscPaliwa <= pojemnoscBaku) cout << "Zatankowano " << ile << "l paliwa" << endl;
		else {
            cout << "Rozlales " << iloscPaliwa-pojemnoscBaku << "l paliwa" << endl;
            iloscPaliwa=pojemnoscBaku;
        }
	}
};

template <typename T>

void wyswietlDostepnePojazdy(const T pojazdy[], int rozmiar) {
	system("cls");
	dekorujNapis("Dostepne pojazdy", '-', 100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	for (int i = 0; i < rozmiar; i++) {
        if(pojazdy[i].czyDostepny()) {
			pojazdy[i].wyswietlInformacje();
		}
    }
        cout << endl <<  "Aby powrocic wprowadz 0" << endl;
}

void wyswietlWypozyczonePojazdy(Samochod samochody[ ], Motocykl motocykle[]) {
	system("cls");
	dekorujNapis("Wypozyczone pojazdy", '-', 100);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	bool istnieja = false;
	for (int i = 0; i < 5; i++) {
        if(!samochody[i].czyDostepny()) {
        	istnieja= true;
			samochody[i].wyswietlInformacje();
		}
    }
    for (int i = 0; i < 3; i++) {
        if(!motocykle[i].czyDostepny()) {
        	istnieja= true;
			motocykle[i].wyswietlInformacje();
		}
    }
    if(!istnieja) {
    	cout << "Nie posiadasz wypozyczonych pojazdow " << endl;
    	cout << endl << "Aby powrocic wprowadz 0" << endl;
	}
}

void wypozyczPojazd(Samochod samochody[], Motocykl motocykle[],  const int wybor) {
    char decyzja;
    int wyborP;
    do {
        if (wybor == 1) {
            wyswietlDostepnePojazdy(samochody, 5);
            cout << endl << "Wprowadz nr katalogowy samochodu ktory chcesz wypozyczyc: ";
        } else if (wybor == 3) break;
        else {
        	wyswietlDostepnePojazdy(motocykle, 3);
            cout << endl << "Wprowadz nr katalogowy motocykla ktory chcesz wypozyczyc: ";
		}
           
        
        cin >> wyborP;
        if(wyborP == 0) break;
        if (wyborP < 6) samochody[wyborP-1].wypozycz();
        else motocykle[wyborP-6].wypozycz();
        cout << "Czy chesz wypozyczyc kolejny pojazd? (t/n): ";
        cin >> decyzja;
    } while(decyzja == 't');
}

void zwrocPojazd(Samochod samochody[], Motocykl motocykle[]) {
    char decyzja;
    int wyborP;
    do {
        wyswietlWypozyczonePojazdy(samochody, motocykle);
        cout << endl << "Wprowadz nr katalogowy pojazdu ktory chcesz oddac: ";
        cin >> wyborP;
        if(wyborP == 0) break;
        if(wyborP < 6) samochody[wyborP-1].zwroc();
        else motocykle[wyborP-6].zwroc();
        cout << "Czy chesz oddac kolejny pojazd? (t/n): ";
        cin >> decyzja;
    } while(decyzja == 't');
}

void jedzPojazdem(Samochod samochody[], Motocykl motocykle[]) {
    char decyzja;
    int wybor;
    do {
        wyswietlWypozyczonePojazdy(samochody, motocykle);
        cout << endl << "Wprowadz nr katalogowy pojazdu ktorym chcesz jechac: ";
        cin >> wybor;
        if(wybor == 0) break;
        float odleglosc;
        cout << "Podaj odleglosc do przejechania (km): ";
        cin >> odleglosc;
        if(wybor < 6) samochody[wybor-1].jedz(odleglosc);
        else motocykle[wybor-6].jedz(odleglosc);
        cout << "Czy chesz jechac kolejnym pojazdem? (t/n): ";
        cin >> decyzja;
    } while(decyzja == 't');
}

void tankujPojazd(Samochod samochody[], Motocykl motocykle[]) {
    char decyzja;
    int wybor;
    do {
        wyswietlWypozyczonePojazdy(samochody, motocykle);
        cout << endl << "Wprowadz nr katalogowy pojazdu ktory chcesz zatankowac: ";
        cin >> wybor;
        if(wybor == 0) break;
        float ile;
        cout << "Ile paliwa chcesz nalac? (l): ";
        cin >> ile;
        if(wybor < 6) samochody[wybor-1].tankuj(ile);
        else motocykle[wybor-6].tankuj(ile);
        cout << "Czy chesz zatankowac kolejny pojazd? (t/n): ";
        cin >> decyzja;
    } while(decyzja == 't');
}

void walidacjaDanych() {
	cin.clear();
	cin.ignore();
}

int main()
{
	char decyzja;
    Samochod samochody[5] = {
        Samochod("Ford", "Mustang", 1, true, 61, 61, 450, 4, "coupe"),
        Samochod("BMW", "M3", 2, true, 59, 59, 510, 5, "touring"),
        Samochod("Chevrolet", "Camaro", 3, true, 72, 72, 455, 4, "cabriolet"),
        Samochod("BMW", "M5", 4, true, 68, 68, 356, 5, "sedan"),
        Samochod("Nissan", "GTR", 5, true, 74, 74, 680, 4, "coupe")
    };
    Motocykl motocykle[3] = {
		Motocykl("Honda", "CBR500R", 6, true, 17.1, 17.1, 471, "4-SUW", "sportowy"),
        Motocykl("BMW", "R 1250 GS Adventure", 7, true, 33, 33, 1254, "4-SUW", "turystyczny"),
        Motocykl("KTM", "SX250", 8, true, 12.5, 12.5, 249, "2-SUW", "cross")
	};
	
    int wybierzOpcje;
    do {
        system("cls");
        dekorujNapis(NazwaProgramu, '-', 40);
        menuGlowne();
        cout << "Wybierz jedna z dostepnych opcji: ";
        cin >> wybierzOpcje;
        walidacjaDanych();
        switch (wybierzOpcje) {
        case 1:
            wyborPojazdu("Co chcesz wypozyczyc?");
            cin >> wybierzOpcje;
            wypozyczPojazd(samochody, motocykle, wybierzOpcje);
            break;    
        case 2:
            zwrocPojazd(samochody, motocykle);
            break;
        case 3:
            jedzPojazdem(samochody, motocykle);
            break;
        case 4:
        	tankujPojazd(samochody, motocykle);
			break;
		case 5:
            cout << endl << "Do zobaczenia!!" << endl;
            break;
        default:
            cout << "Nie ma takiej opcji\n";
        }

    } while (wybierzOpcje != 5);

    return 0;
}

