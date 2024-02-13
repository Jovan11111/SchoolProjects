#include <iostream>
#include <cmath>

#define brojreci 2000

using namespace std;

/*Potprogram koji računa da li je parametar stepen broja 2. Koristi se više puta u zadataku*/
bool stepen2(int n) {
    int lol = 1;
    while (lol < n) {
        lol *= 2;
    }
    if (lol == n) return true;
    else return false;
}

/*Potprogram koji računa k za dato n. Važi da je n = k+z, gde je z broj kontrolnih bita. Broj kontrolnih bita se računa kao
 * prvi veći ceo broj od log2(n). Pošto C++ decimalni broj konvertuje u celobrojni tako što ignoriše sve iza decimalnog zareza,
 * potrebno je dodati 1. z = log2(n)+1 ^ n = k+z -> k = n-(log2(n)+1)*/
inline int racunanje_k(int n) {
    return n - (int(log2(n)) + 1);
}

/*Potprogram za unos nasumičnih nula i jedinica. Koristi se ugrađena rand() funkcija, pa se računa njen ostatak pri deljenju
 * sa 2*/
void generisanje_unosnog_niza(int unos[], int max) {
    for (int i = 0; i < max; i++) {
        unos[i] = rand() % 2;
    }
}

/*Potprogram za pravljenje "niza polozaja". Potprogram kao parametar dobija niz "inf" koji predstavlja unesenu kodnu reč
 * dužine k bita, i na osnovu nje pravi niz dužine n koji će na odgovarajućim pozicijama imati informacione bite. Tamo gde
 * treba da budu kontrolni biti je vrednost -1*/
void pravljenje_niza_polozaja(int niz[], int n, int const inf[]) {
    int br = 0;
    for (int i = 1; i < n + 1; i++) {
        if (stepen2(i)) niz[i - 1] = -1;
        else niz[i - 1] = inf[br++];
    }
}

/*Potprogram za popunjavanje celog "niza polozaja". Potprogram najpre pronađe poziciju kojoj je potrebno promeniti vrednost.
 * Inicijalizuju se "br" koji predstavlja redni broj kontrolnog bita koji se generise, i z koji će zameniti -1 u nizu položaja.
 * Zatim potprogram pronalazi koje informacione bite treba da sabere da bi se dobila vrednost odgovarajućeg kontrolong
 * bita na jako zanimljiv način (linija 56 je ključna za red celog programa, i verovatno najbolja formula koju sam smislio).
 * Sabira informacione bite, određuje kontrolni bit, i postavlja ga na pravo mesto u nizu polozaja.*/
void racunanje_z(int pol[], int n) {
    int br = 0;
    for (int i = 0; i < n; i++) {
        if (pol[i] == -1) {
            br++;
            int z = 0;
            for (int j = 1; j < n + 1; j++) {
                if (j % int(pow(2, br)) >= int(pow(2, br - 1))) {
                    if (pol[j - 1] != -1) {
                        z = (z + pol[j - 1]) % 2;
                    }
                }
            }
            pol[i] = z;
        }
    }
}

/*Potprogram za generisanje celog hemingovog niza, koji ce imati brojreci*n bita (broj reci je konstanta definisana na pocetku
 * programa). "siroki" i "kratki" predstavljaju indeks do kog je potprogram stigao u generisanju hemingovog niza, i obradi
 * unosnog niza. Prva petlja iterira "brojreci" puta, i u njenom telu se određuje niz polozaja za tu kodnu rec, a zatim se
 * niz polozaja prepise u hemingov kod.*/
void generisanje_hemingovog_niza(int const unos[], int hemingov[], int k, int n) {
    int siroki = 0;
    int kratki = 0;
    for (int i = 0; i < brojreci; i++) {
        int inf[k];
        for (int j = 0; j < k; j++)inf[j] = unos[kratki++];
        int pol[n];
        pravljenje_niza_polozaja(pol, n, inf);
        racunanje_z(pol, n);
        for (int j = 0; j < n; j++) hemingov[siroki++] = pol[j];
    }
}

/*Potprogram koji pomaže u generisanju niza greški. Pošto se "p" unosi u procentima, inicijalizuje se broj "k" koji će biti
 * nasumičan broj od 1 do 100. Ako je on veći od p, potrebno je vratiti 1, u suprotnom je potrebno vratiti 0*/
int random_sa_verovatnocom(double p) {
    double k = (float) rand() / (float) (RAND_MAX / 100);
    if (k < p) return 1;
    else return 0;
}

/*Potprogram koji generiše niz greški dužine "n*duzinareci". To se radi uz pomoc potprograma "random_sa_verovatnocom".
 * Program takođe određuje u koliko će se kodnih reči pojaviti više od jedne greške. Ovaj broj predstavlja pomoć u proveri
 * programa. Ako program radi, ovaj broj biće jednak broju kodnih reči koji se razlikuje u poređenju ulaznog i izlaznog
 * signala.*/
void generisanje_niza_greski(int niz[], int n, int duzinareci, double p) {
    for (int i = 0; i < duzinareci; i++) {
        niz[i] = random_sa_verovatnocom(p);
    }
    int br1 = 0;
    for (int i = 0; i < brojreci; i++) {
        int br2 = 0;
        for (int j = i * n; j < i * n + n; j++) {
            if (niz[j] == 1) br2++;
        }
        if (br2 > 1)br1++;
    }
    cout << "U kodu greske se " << br1 << " puta pojavila jedinica vise od jednom u istoj kodnoj reci" << endl;
}

/*Potprogram koji vraća vrednost suprotnu onoj koju je dobio. Potprogram je napravljen da bi kod bio čitljiviji*/
inline void zameni(int &x) {
    if (x) x = 0;
    else x = 1;
}

/*Potprogram koji namerno pravi greške u hemingovom kodu, na osnovu pozicija na kojima se nalaze jedinice u nizu greski.*/
void generisanje_greski_u_zasticenom_nizu(int hemingov[], int const greske[], int n) {
    for (int i = 0; i < n; i++) {
        if (greske[i])
            zameni(hemingov[i]);
    }
}

/*Potprogram koji na osnovu kodne reči računa sindrom. Ovde se takođe pojavljuje uslov korišćen u potprogramu
 * "racunanje_z".*/
int nalazenje_sindroma(int sindrom[], int const kodnarec[], int n, int k) {
    for (int i = 0; i < n - k; i++) {
        int z = 0;
        for (int j = 1; j < n + 1; j++) {
            if (j % int(pow(2, i + 1)) >= int(pow(2, i))) {
                z = (z + kodnarec[j - 1]) % 2;
            }
        }
        sindrom[i] = z;
    }
    int Sindrom = 0;
    for (int i = 0; i < n - k; i++) {
        Sindrom += sindrom[i] * int(pow(2, i));
    }
    return Sindrom;
}

/*Potprogram koji dekoduje hemingov niz i generiše izlazni niz duzine "k*brojreci". "siroki" i "kratki" predstavljaju
 * polozaj u kom se program nalazi. for petlja iterira "brojreci" puta. U njenom telu se izdvaja kodna reč, pa se
 * racuna sindrom, i greska se ispravlja. Posto nema bita parnosti, uzima se pretpostavka da uvek ima samo jedna greška
 * koja se uvek ispravlja. Kako god, kodna reč će biti različita kako god da se radi.*/
void dekodovanje_zasticenog_koda(int const hemingov[], int k, int n, int izlazni[]) {
    int siroki = 0;
    int kratki = 0;
    for (int i = 0; i < brojreci; i++) {
        int sindrom[n - k];
        int kodnarec[n];
        for (int j = 0; j < n; j++) kodnarec[j] = hemingov[siroki++];
        int greska = nalazenje_sindroma(sindrom, kodnarec, n, k);
        if (greska) zameni(kodnarec[greska - 1]);
        for (int j = 0; j < n; j++) {
            if (not stepen2(j + 1)) izlazni[kratki++] = kodnarec[j];
        }
    }
}

/*Potprogram koji određuje za koliko bita se razlikuju ulazni i izlazni niz*/
void bitno_poredjenje_ulaznog_i_izlaznog(int const ulazni[], int const izlazni[], int n) {
    int br = 0;
    for (int i = 0; i < n; i++) {
        if (ulazni[i] != izlazni[i]) br++;
    }
    cout << "Ulazni i izlazni kod se razlikuju za " << br << " bitova" << endl;
}

/*Potprogram koji određuje za koliko se kodnih reči razlikuju ulazni i izlazni kod*/
void poredjenje_reci_ulaznog_i_izlaznog(int const ulazni[], int const izlazni[], int k) {
    int br = 0;
    for (int i = 0; i < brojreci; i++) {
        for (int j = i * k; j < (i * k) + k; j++) {
            if (ulazni[j] != izlazni[j]) {
                br++;
                break;
            }
        }
    }
    double procenat = double(br) / brojreci;
    procenat *= 100;
    cout << "Ulazni i izlazni kod se razlikuju za " << br << " kodnih reci" << endl;
    cout << "Greska nakon Hemingovog koda je " << procenat << fixed << endl;
}

int main() {
    int n;
    double p;
    cout << "Koliko treba da bude broj bita prosirene kodne reci??" << endl;
    cin >> n;
    cout << "Koliko treba da bude verovatnoca pojavljivanja greske?" << endl;
    cin >> p;
    int k = racunanje_k(n);
    cout << "k je " << k << endl;
    int duzina_ulaznog_koda = brojreci * k;
    int duzina_zasticenog_koda = brojreci * n;
    int ulazni[duzina_ulaznog_koda];
    int hemingov[duzina_zasticenog_koda];
    int niz_greski[duzina_zasticenog_koda];
    int izlazni[duzina_ulaznog_koda];
    generisanje_unosnog_niza(ulazni, duzina_ulaznog_koda);
    generisanje_hemingovog_niza(ulazni, hemingov, k, n);
    generisanje_niza_greski(niz_greski, n, duzina_zasticenog_koda, p);
    generisanje_greski_u_zasticenom_nizu(hemingov, niz_greski, duzina_zasticenog_koda);
    dekodovanje_zasticenog_koda(hemingov, k, n, izlazni);
    bitno_poredjenje_ulaznog_i_izlaznog(ulazni, izlazni, duzina_ulaznog_koda);
    poredjenje_reci_ulaznog_i_izlaznog(ulazni, izlazni, k);
}
