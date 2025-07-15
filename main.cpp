#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <windows.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <conio.h>

using namespace std;

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

const int MAX_USERS = 100;
struct User {
    string userid;
    string ema;
    string pass;
    string nama;
    long long nik; 
    string alamat;
    string telepon;
};

struct Admin {
    string email;
    string password;
    string nama;
};

struct Mobil {
    string nama, model, kategori;
    double Harga;
    int stok; 
    Mobil* next;
    string id;
};

struct Motor {
    string nama, model, kategori;
    double Harga;
    int stok; 
    Motor* next;
    string id;
};

struct InfoKendaraan {
    string nama;
    string model;
    string kategori;
    double Harga;
};

const int MAX_QUEUE = 100;
struct Booking {
    string idTransaksi; // tambahkan ini
    User userInfo;
    InfoKendaraan infoKendaraan; 
    int rentalDays;
    string tanggalBooking;
};

int tax = 11;

struct Queue {
    int depan, belakang;
    Booking data[MAX_QUEUE];
} queue;

//global variable
User users[MAX_USERS];
int jumlahUser = 0;
Mobil* headMobil = nullptr;
Motor* headMotor = nullptr;

Admin admin = {"admin@gmail.com", "admin123", "Administrator" };

// DEKLARASI FUNGSI 
void enableVirtualTerminalProcessing();
void TampilkanSemuaMobil();
void TampilkanSemuaMotor();
void displayAllVehicles();
void TambahKendaaraan();
void BookingKendaraan(int userIndex);
void printNextBill();
void hapusKendaraan();
void menuAdmin();
void printSelectedBill(int userIndex);
void inisialisasiQueue();
bool isQueueEmpty();
bool isQueueFull();
void enqueue(Booking data);
void dequeue();
void clearQueue();
void printQueue();
void insertionSortMobil(bool ascending);
void insertionSortMotor(bool ascending);
void updateKendaraan();
void searchKendaraan();
string generateRandomId();
void loadingBar();
string generateTransaksiId();
string hitungTanggalKembali(const string& tanggalBooking, int rentalDays);
string inputPassword();
void printAllBookedVehicles();


int main() {
    
    enableVirtualTerminalProcessing(); // Perubahan kecil agar warna berfungsi di Windows

    // data sementara M untuk demonstrasi
    users[0] = {"ID0001", "naufal123", "123", "Naufal", 1234567890123456, "Jl. kementiran No. 1, Yogyakarta", "08123456789"};
    jumlahUser = 1;
    users[1] = {"ID0002", "amikom123", "123", "amikom", 9876543210987654, "Jl. kebonagung No. 2, Yogyakarta", "08234567890"};
    jumlahUser = 2;

    // Mobil
    Mobil* m1 = new Mobil{"avanza", "2023", "City Car", 300000, 5, nullptr, "av1234"};
    Mobil* m2 = new Mobil{"pajero Sport", "2024", "SUV", 800000, 2, nullptr, "ps5678"};
    Mobil* m3 = new Mobil{"ferrari", "2022", "Sport", 5000000, 1, nullptr, "f48890"};
    headMobil = m1;
    m1->next = m2;
    m2->next = m3;

    // Motor
    Motor* mt1 = new Motor{"vario 160", "2024", "Skuter", 150000, 10, nullptr, "va1234"};
    Motor* mt2 = new Motor{"ninja ZX-25R", "2023", "Big Bike", 750000, 3, nullptr, "nz5678"};
    Motor* mt3 = new Motor{"crf150", "2023", "Adventure Motor", 250000, 4, nullptr, "cr1122"};
    headMotor = mt1;
    mt1->next = mt2;
    mt2->next = mt3;



    inisialisasiQueue();
    int pilihan;
    char ulang;
    string email, password;
    int userNow;
    char pilihansorting;
    
    do {
        loadingBar() ;
        system("cls");
        cout << RED << "\n==============================" <<RESET<< endl;
        cout << CYAN << "<< SIREN RENTAL KENDARAAN  >>" << RESET << endl;
        cout << RED <<"==============================" <<RESET<< endl;
        cout << "1. Login" << endl;
        cout << "2. Daftar" << endl;
        cout << "3. Login Sebagai Admin" << endl;
        cout << "4. Keluar" << endl;
        cout << "==============================" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                int attempts = 3;
                bool loginSuccess = false;
                while (attempts > 0) {
                    cout << "Masukkan email: ";
                    getline(cin, email);
                    cout << "Masukkan password: ";
                    password = inputPassword();

                    bool ditemukan = false;
                    for (int i = 0; i < jumlahUser; i++) {
                        if (users[i].ema == email && users[i].pass == password) {
                            userNow = i;
                            cout << GREEN << "\nLogin berhasil. Selamat datang, " << users[userNow].nama << "!" << RESET << endl;
                            loginSuccess = true;
                            ditemukan = true;
                            break;
                        }
                    }

                    if (ditemukan) {
                        break;
                    } else {
                        attempts--;
                        cout << RED << "\nEmail atau password salah. Sisa percobaan: " << attempts << RESET << endl;
                        if (attempts == 0) {
                            cout << RED << "Akun terkunci. Silakan hubungi admin." << RESET << endl;
                        }
                    }
                }
                
                if(loginSuccess) {
                    int menuUtama;
                    char kembali;
                    bool logout = false;
                    do {
                        loadingBar();
                        system("cls");
                        cout << RED << "\n==============================" <<RESET<< endl;
                        cout << CYAN << "<< SIREN RENTAL KENDARAAN  >>" << RESET << endl;
                        cout << RED  <<"==============================" <<RESET<< endl;
                        cout <<"========= MENU UTAMA =========" << endl;
                        cout << "1. Tampilkan Biodata Saya" << endl;
                        cout << "2. Tampilkan List Kendaraan" << endl;
                        cout << "3. Cari Kendaraan" << endl;
                        cout << "4. Booking Kendaraan" << endl;
                        cout << "5. Riwayat Transaksi Saya" << endl;
                        cout << "6. Logout" << endl;
                        cout << RED  <<"==============================" <<RESET<< endl;
                        cout << "Masukkan pilihan: ";
                        cin >> menuUtama;
                        cin.ignore();

                        switch (menuUtama) {
                            case 1:
                                cout << "\n--- BIODATA SAYA ---" << endl;
                                cout << "ID     : " << users[userNow].userid << endl;
                                cout << "Nama   : " << users[userNow].nama << endl;
                                cout << "NIK    : " << users[userNow].nik << endl;
                                cout << "Alamat : " << users[userNow].alamat << endl;
                                cout << "Telepon: " << users[userNow].telepon << endl; // Tambahkan ini
                                cout << "Email  : " << users[userNow].ema << endl;
                                break;
                            case 2:
                                system("cls");
                                cout << "\n===============================================================================================\n";
                                cout <<CYAN "                                     CV. SIREN RENTAL KENDARAAN                                \n"<<RESET;
                                cout << "               Jl. kebonagung km12, sendangsari, Minggir, Sleman, daerah istimewa yogyakarta              \n";
                                cout << "                       email: sirenretalken@gmail.com | Phone: 08123456789\n";
                                cout << "===============================================================================================\n";
                                cout << "\n-------------------------------------- MOBIL --------------------------------------------------\n";
                                TampilkanSemuaMobil();
                                cout << "\n-------------------------------------- MOTOR --------------------------------------------------\n";
                                TampilkanSemuaMotor();
                                cout << "\nApakah Anda ingin mengurutkan kendaraan? (y/n): ";
                                cin >> pilihansorting;
                                cin.ignore();
                                if (pilihansorting == 'y' || pilihansorting == 'Y') {
                                    int sortOption;
                                    cout << "Sorting Menurut?:\n1. Harga terendah \n2. harga tertinggi\nPilihan: ";
                                    cin >> sortOption;
                                    cin.ignore();
                                    if (sortOption == 1) {
                                        insertionSortMobil(true);
                                        insertionSortMotor(true);
                                    } else if (sortOption == 2) {
                                        insertionSortMobil(false);
                                        insertionSortMotor(false);
                                    } else {
                                        cout << "Pilihan tidak valid." << endl;
                                    }
                                }
                                break;
                            case 3:
                                system("cls"); 
                                searchKendaraan();
                                cout << "\nTekan ENTER untuk kembali ke menu utama...";
                                cin.get(); // Mengganti cin.ignore() dengan cin.get() agar berfungsi
                                break;
                            case 4:
                                system("cls");
                                BookingKendaraan(userNow);
                                break;
                            case 5:
                                system("cls");
                                printSelectedBill(userNow);
                                break;
                            case 6:
                                cout << "\nLogout berhasil." << endl;
                                logout = true;
                                break;
                            default:
                                cout << "Pilihan tidak valid." << endl;
                        }

                        if(logout){
                            break; // Keluar dari do-while menu utama
                        }
                        
                        cout << "\nKembali ke menu utama? (y/n): ";
                        cin >> kembali;
                        cin.ignore();
                    } while (kembali == 'y' || kembali == 'Y');
                }
                break;
            }
            case 2:
                if (jumlahUser >= MAX_USERS) {
                    cout << "Pendaftaran gagal. Kapasitas penuh." << endl;
                } else {
                    cout << "Masukkan nama: ";
                    getline(cin, users[jumlahUser].nama);
                    cout << "Masukkan NIK: ";
                    cin >> users[jumlahUser].nik;
                    cin.ignore();
                    cout << "Masukkan alamat: ";
                    getline(cin, users[jumlahUser].alamat);
                    cout << "Masukkan telepon: ";
                    getline(cin, users[jumlahUser].telepon);
                    cout << "Masukkan email: ";
                    getline(cin, users[jumlahUser].ema);
                    cout << "Masukkan password: ";
                    getline(cin, users[jumlahUser].pass);

                    // Generate dan cek ID unik
                    string idBaru;
                    bool idSama;
                    do {
                        idSama = false;
                        idBaru = generateRandomId();
                        for (int i = 0; i < jumlahUser; i++) {
                            if (users[i].userid == idBaru) {
                                idSama = true;
                                break;
                            }
                        }
                    } while (idSama);
                    users[jumlahUser].userid = idBaru;

                    jumlahUser++;
                    cout << "\nPendaftaran berhasil. Silakan login." << endl;
                }
                break;
            case 3: {
                cout << "Masukkan email admin: ";
                getline(cin, email);
                cout << "Masukkan password admin: ";
                password = inputPassword();
                if (admin.email == email && admin.password == password) {
                    cout << "\nLogin berhasil. Selamat datang, " << admin.nama << "!\n";
                    menuAdmin();
                } else {
                    cout << "Email dan password salah!\n";
                }
                break;
            }
            case 4:
                cout << "\nTerima kasih telah menggunakan program." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }

        if (pilihan == 4) break;

        cout << "\nKembali ke menu login? (y/n): ";
        cin >> ulang;
        cin.ignore();
    } while (ulang == 'y' || ulang == 'Y');

    cout << "\nTerima kasih telah menggunakan program." << endl;
    return 0;
}

void displayAllVehicles() {
    int pilihan;
    cout << "\nPilih jenis kendaraan yang ingin ditampilkan:\n 1. Mobil\n 2. Motor\n 3. Semua Kendaraan\n Pilih 1/2/3: ";
    cin >> pilihan;
    if (pilihan == 1 || pilihan == 3) {
        cout << "\n\n--- MOBIL ---";
        TampilkanSemuaMobil();
    } 
    
     if (pilihan == 2 || pilihan == 3) {
        cout << "\n\n--- MOTOR ---";
        TampilkanSemuaMotor();
    }
}

void TampilkanSemuaMobil(){
    if (!headMobil) {
        cout << "\nTidak ada mobil yang tersedia.\n";
        return;
    }
    cout << "\n+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
    cout << "| ID     | Nama Kendaraan       | Model           | Kategori        | Harga/Hari       | Stok  |\n";
    cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
    Mobil* temp = headMobil;
    
    while (temp) {
        cout << "| " << setw(7) << left << temp->id 
             << "| " << setw(21) << left << temp->nama
             << "| " << setw(16) << left << temp->model
             << "| " << setw(16) << left << temp->kategori
             << "| Rp." << setw(13) << right << fixed << setprecision(0) << temp->Harga
             << " | " << setw(5) << right << temp->stok << " |\n";
        temp = temp->next;
        
    }
    cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
}

void TampilkanSemuaMotor() {
    if (!headMotor) {
        cout << "\nTidak ada motor yang tersedia.\n";
        return;
    }
    cout << "\n+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
    cout << "| ID     | Nama Kendaraan       | Model           | Kategori        | Harga/Hari       | Stok  |\n";
    cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
    Motor* temp = headMotor;
    
    while (temp) {
        cout << "| " << setw(7) << left << temp->id 
             << "| " << setw(21) << left << temp->nama
             << "| " << setw(16) << left << temp->model
             << "| " << setw(16) << left << temp->kategori
             << "| Rp." << setw(13) << right << fixed << setprecision(0) << temp->Harga
             << " | " << setw(5) << right << temp->stok << " |\n";
        temp = temp->next;
        
    }
    cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
}

void TambahKendaaraan() {
    int pilihan;
    cout << "\nPilih jenis kendaraan yang akan ditambahkan:\n 1. Mobil\n 2. Motor\nPilih 1/2: ";
    cin >> pilihan;
    cin.ignore(); 

    if (pilihan == 1) {
        Mobil* newMobil = new Mobil();
        cout << "Masukkan ID Mobil: ";
        cin >> newMobil->id;
        cin.ignore();
        cout << "Masukkan nama Mobil: ";
        getline(cin, newMobil->nama);
        cout << "Masukkan model Mobil: ";
        getline(cin, newMobil->model);
        cout << "Masukkan Kategori Mobil: ";
        getline(cin, newMobil->kategori);
        cout << "Masukkan harga sewa /Hari: Rp.";
        cin >> newMobil->Harga;
        cout << "Masukkan stok mobil: ";
        cin >> newMobil->stok;
        cin.ignore();
        newMobil->next = nullptr;
        if (!headMobil) headMobil = newMobil;
        else {
            Mobil* temp = headMobil;
            while (temp->next) temp = temp->next;
            temp->next = newMobil;
        }
        cout << "\n[+] Mobil telah ditambahkan!\n";
    } else if (pilihan == 2) {
        Motor* newMotor = new Motor();
        cout << "Masukkan ID Motor: ";
        cin >> newMotor->id;
        cin.ignore();
        cout << "Masukkan nama Motor: ";
        getline(cin, newMotor->nama);
        cout << "Masukkan model Motor: ";
        getline(cin, newMotor->model);
        cout << "Masukkan Kategori Motor: ";
        getline(cin, newMotor->kategori);
        cout << "Masukkan Harga sewa Motor per Hari: Rp.";
        cin >> newMotor->Harga;
        cout << "Masukkan stok motor: ";
        cin >> newMotor->stok;
        cin.ignore();
        newMotor->next = nullptr;
        if (!headMotor) headMotor = newMotor;
        else {
            Motor* temp = headMotor;
            while (temp->next) temp = temp->next;
            temp->next = newMotor;
        }
        cout << "\n[+] Motor telah ditambahkan!\n";
    } else {
        cout << "Pilihan tidak valid.\n";
    }
}
void BookingKendaraan(int userIndex) {
    vector<Mobil*> chosenCars;
    vector<int> carRentalDurations;
    vector<Motor*> chosenMotors;
    vector<int> motorRentalDurations;

    char addAnother;
    do {
        int pilihan;
        cout << "\nPilih jenis kendaraan:\n 1. Mobil\n 2. Motor\nPilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            TampilkanSemuaMobil();
            string carIdToBook;
            cout << "Masukkan ID mobil yang ingin dibooking: ";
            getline(cin, carIdToBook);

            Mobil* carToBook = nullptr;
            for (Mobil* temp = headMobil; temp; temp = temp->next) {
                if (temp->id == carIdToBook) {
                    carToBook = temp;
                    break;
                }
            }

            if (!carToBook) {
                cout << "Gagal menambah keranjang karena Mobil tidak ditemukan.\n";
            } else if (carToBook->stok <= 0) {
                cout << "Stok mobil habis, tidak bisa dipesan.\n";
            } else if (find(chosenCars.begin(), chosenCars.end(), carToBook) != chosenCars.end()) {
                cout << "Mobil ini sudah ada di keranjang booking Anda.\n";
            } else {
                int days;
                cout << "Berapa hari ingin disewa?: ";
                cin >> days;
                cin.ignore();
                if (days <= 0) {
                    cout << "Durasi sewa tidak valid.\n";
                } else {
                    chosenCars.push_back(carToBook);
                    carRentalDurations.push_back(days);
                    carToBook->stok--;
                    cout << "Mobil '" << carToBook->nama << "' telah ditambahkan ke keranjang.\n";
                }
            }
        } else if (pilihan == 2) {
            TampilkanSemuaMotor();
            string motorIdToBook;
            cout << "Masukkan ID motor yang ingin dibooking: ";
            getline(cin, motorIdToBook);

            Motor* motorToBook = nullptr;
            for (Motor* temp = headMotor; temp; temp = temp->next) {
                if (temp->id == motorIdToBook) {
                    motorToBook = temp;
                    break;
                }
            }

            if (!motorToBook) {
                cout << "Gagal menambah keranjang karena Motor tidak ditemukan.\n";
            } else if (motorToBook->stok <= 0) {
                cout << "Stok motor habis, tidak bisa dipesan.\n";
            } else if (find(chosenMotors.begin(), chosenMotors.end(), motorToBook) != chosenMotors.end()) {
                cout << "Motor ini sudah ada di keranjang booking Anda.\n";
            } else {
                int days;
                cout << "Berapa hari ingin disewa?: ";
                cin >> days;
                cin.ignore();
                if (days <= 0) {
                    cout << "Durasi sewa tidak valid.\n";
                } else {
                    chosenMotors.push_back(motorToBook);
                    motorRentalDurations.push_back(days);
                    motorToBook->stok--;
                    cout << "Motor '" << motorToBook->nama << "' telah ditambahkan ke keranjang.\n";
                }
            }
        } else {
            cout << "Pilihan tidak valid.\n";
        }

        cout << "\nApakah Anda ingin menambah kendaraan lain? (y/n): ";
        cin >> addAnother;
        cin.ignore();
        system("cls");

    } while (addAnother == 'y' || addAnother == 'Y');

    // --- FINALIZE BOOKING AND PRINT RECEIPT ---
    if (chosenCars.empty() && chosenMotors.empty()) {
        cout << "Keranjang booking kosong. Tidak ada transaksi yang dibuat.\n";
        return;
    }

    Booking baseBooking;
    baseBooking.userInfo = users[userIndex];
    baseBooking.idTransaksi = generateTransaksiId();

    cout << "Masukkan tanggal booking (DD-MM-YYYY): ";
    getline(cin, baseBooking.tanggalBooking);

    // --- Struk Generation & Output di Tengah ---
    auto printHeader = [&](ostream& os) {
        os << "\n================================================================================\n";
        os << "                        CV. SIREN RENTAL KENDARAAN                                  \n";
        os << "   Jl. kebonagung km12, sendangsari, Minggir, Sleman, daerah istimewa yogyakarta             \n";
        os << "                 email: sirenretalken@gmail.com | Phone: 08123456789                      \n";
        os << "================================================================================\n";
        os << "=============================== STRUK PENYEWAAN ================================\n";
        os << "Tanggal Booking: " << baseBooking.tanggalBooking << "\n";
        os << "ID Transaksi   : " << baseBooking.idTransaksi << endl;
        os << "CustomerID     : " << baseBooking.userInfo.userid << "\n";
        os << "Customer       : " << baseBooking.userInfo.nama << "\n";
        os << "Email          : " << baseBooking.userInfo.ema << "\n";
        os << "Telepon        : " << baseBooking.userInfo.telepon << "\n";
        os << "--------------------------------------------------------------------------------\n";
        os << "DETAIL PESANAN: ";
    };

    ofstream struk("struk_booking.txt");
    if (!struk.is_open()) {
        cout << "Gagal membuka file struk untuk ditulis.\n";
        return;
    }
    printHeader(cout);
    printHeader(struk);

    double total = 0;

    // Cetak detail mobil
    for (size_t i = 0; i < chosenCars.size(); ++i) {
        Mobil* car = chosenCars[i];
        int days = carRentalDurations[i];
        double subTotal = car->Harga * days;
        total += subTotal;
        string tanggalKembali = hitungTanggalKembali(baseBooking.tanggalBooking, days);

        auto printVehicleDetails = [&](ostream& os) {
            os << "\n  Kendaraan    : " << car->nama << " (" << car->model << ")\n";
            os << "  Kategori     : " << car->kategori << "\n";
            os << "  Harga/Hari   : Rp." << fixed << setprecision(0) << car->Harga << "\n";
            os << "  Lama Sewa    : " << days << " hari\n";
            os << "  Tgl. Kembali : " << tanggalKembali << "\n";
            os << "  Subtotal     : Rp." << fixed << setprecision(0) << subTotal << "\n";
        };
        printVehicleDetails(cout);
        printVehicleDetails(struk);
    }
    
    // Cetak detail motor
    for (size_t i = 0; i < chosenMotors.size(); ++i) {
        Motor* motor = chosenMotors[i];
        int days = motorRentalDurations[i];
        double subTotal = motor->Harga * days;
        total += subTotal;
        string tanggalKembali = hitungTanggalKembali(baseBooking.tanggalBooking, days);

        auto printVehicleDetails = [&](ostream& os) {
            os << "\n  Kendaraan    : " << motor->nama << " (" << motor->model << ")\n";
            os << "  Kategori     : " << motor->kategori << "\n";
            os << "  Harga/Hari   : Rp." << fixed << setprecision(0) << motor->Harga << "\n";
            os << "  Lama Sewa    : " << days << " hari\n";
            os << "  Tgl. Kembali : " << tanggalKembali << "\n";
            os << "  Subtotal     : Rp." << fixed << setprecision(0) << subTotal << "\n";
        };
        printVehicleDetails(cout);
        printVehicleDetails(struk);
    }

    // Footer
    double pajak = total * tax / 100;
    double grandTotal = total + pajak;
    auto printFooter = [&](ostream& os) {
        os << "--------------------------------------------------------------------------------\n";
        os <<right << setw(73) << fixed << setprecision(0) << "TOTAL         : Rp." << total << "\n";
        os << right << setw(59) << fixed << setprecision(0)<< "PPN (" << tax << "%)     : Rp. "  << pajak << "\n";
        os << "--------------------------------------------------------------------------------\n";
        os << right << setw(73) << fixed << setprecision(0) << "GRAND TOTAL   : Rp." << grandTotal << "\n";
        os << "================================================================================\n";
    };
    printFooter(cout);
    printFooter(struk);

    struk.close();
    cout << "\nStruk Penyewaan telah berhasil dicetak ke file 'struk_booking.txt'.\n";
    cout << "Booking berhasil!\n";

    // ENQUEUE semua mobil yang dibooking
    for (size_t i = 0; i < chosenCars.size(); ++i) {
        Mobil* car = chosenCars[i];
        int days = carRentalDurations[i];
        Booking finalCarBooking = baseBooking;
        finalCarBooking.infoKendaraan = {car->nama, car->model, car->kategori, car->Harga};
        finalCarBooking.rentalDays = days;
        finalCarBooking.tanggalBooking = baseBooking.tanggalBooking;
        // Pastikan userInfo diisi lengkap!
        finalCarBooking.userInfo = users[userIndex];
        enqueue(finalCarBooking);
    }

    // ENQUEUE semua motor yang dibooking
    for (size_t i = 0; i < chosenMotors.size(); ++i) {
        Motor* motor = chosenMotors[i];
        int days = motorRentalDurations[i];
        Booking finalMotorBooking = baseBooking;
        finalMotorBooking.infoKendaraan = {motor->nama, motor->model, motor->kategori, motor->Harga};
        finalMotorBooking.rentalDays = days;
        finalMotorBooking.tanggalBooking = baseBooking.tanggalBooking;
        // Pastikan userInfo diisi lengkap!
        finalMotorBooking.userInfo = users[userIndex];
        enqueue(finalMotorBooking);
    }
}
void printNextBill() {
    if (isQueueEmpty()) {
        cout << "\n=============================== DAFTAR BOOKING ====================================\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << "| No | ID Transaksi | Nama Kendaraan       | Model           | Hari  | Total Harga  |\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << "|                                                                                   |\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << RED << "\booking kosong.\n" << RESET;
        return;
    }
    // Ambil idTransaksi booking paling depan
    string idTransaksiDiproses = queue.data[queue.depan].idTransaksi;

    // Kumpulkan semua booking dengan idTransaksi yang sama
    vector<Booking> detail;
    for (int i = queue.depan; i <= queue.belakang; ++i) {
        if (queue.data[i].idTransaksi == idTransaksiDiproses) {
            detail.push_back(queue.data[i]);
        }
    }

    // Cetak struk detail (mirip proses booking)
    double total = 0;
    cout << "\n===============================================================================================\n"
         << "                                     CV. SIREN RENTAL KENDARAAN                                \n"
         << "               Jl. kebonagung km12, sendangsari, Minggir, Sleman, daerah istimewa yogyakarta   \n"
         << "                       email: sirenretalken@gmail.com | Phone: 08123456789\n"
         << "===============================================================================================\n"
         << "Tanggal Booking : " << detail[0].tanggalBooking << "\n"
         << "ID Transaksi    : " << idTransaksiDiproses << "\n"
         << "CustomerID      : " << detail[0].userInfo.userid << "\n"
         << "Customer        : " << detail[0].userInfo.nama << "\n"
         << "Email           : " << detail[0].userInfo.ema << "\n"
         << "Telepon         : " << detail[0].userInfo.telepon << "\n"
         << "--------------------------------------------------------------------------------\n"
         << "DETAIL PESANAN:\n";

    for (const auto& b : detail) {
        double subtotal = b.infoKendaraan.Harga * b.rentalDays;
        total += subtotal;
        string tanggalKembali = hitungTanggalKembali(b.tanggalBooking, b.rentalDays);
        cout << "\n  Kendaraan    : " << b.infoKendaraan.nama << " (" << b.infoKendaraan.model << ")\n";
        cout << "  Kategori     : " << b.infoKendaraan.kategori << "\n";
        cout << "  Harga/Hari   : Rp." << fixed << setprecision(0) << b.infoKendaraan.Harga << "\n";
        cout << "  Lama Sewa    : " << b.rentalDays << " hari\n";
        cout << "  Tgl. Kembali : " << tanggalKembali << "\n";
        cout << "  Subtotal     : Rp." << fixed << setprecision(0) << subtotal << "\n";
    }
    double pajak = total * tax / 100;
    double grandTotal = total + pajak;
    cout << "--------------------------------------------------------------------------------\n";
    cout << right << setw(73) << fixed << setprecision(0) << "TOTAL         : Rp." << total << "\n";
    cout << right << setw(59) << fixed << setprecision(0)<< "PPN (" << tax << "%)     : Rp. "  << pajak << "\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout << right << setw(73) << fixed << setprecision(0) << "GRAND TOTAL   : Rp." << grandTotal << "\n";
    cout << "================================================================================\n";

    // Hapus semua booking dengan idTransaksi yang sama dari queue (dequeue berulang)
    while (!isQueueEmpty() && queue.data[queue.depan].idTransaksi == idTransaksiDiproses) {
        dequeue();
    }
}


void hapusKendaraan() {
    int pilihan;
    cout << "\nPilih jenis kendaraan yang ingin dihapus:\n1. Mobil\n2. Motor\nPilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan != 1 && pilihan != 2) {
        cout << "[!] Pilihan tidak valid.\n";
        return;
    }

    if (pilihan == 1) TampilkanSemuaMobil();
    else TampilkanSemuaMotor();

    string nama;
    cout << "Masukkan NAMA kendaraan yang ingin dihapus: ";
    getline(cin, nama);

    if (pilihan == 1) {
        Mobil* current = headMobil;
        Mobil* prev = nullptr;
        while (current != nullptr && current->nama != nama) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Mobil tidak ditemukan.\n";
            return;
        }
        if (prev == nullptr) headMobil = current->next;
        else prev->next = current->next;
        delete current;
        cout << "Mobil berhasil dihapus.\n";
    } else { 
        Motor* current = headMotor;
        Motor* prev = nullptr;
        while (current != nullptr && current->nama != nama) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            cout << "[!] Motor tidak ditemukan.\n";
            return;
        }
        if (prev == nullptr) headMotor = current->next;
        else prev->next = current->next;
        delete current;
        cout << "[+] Motor berhasil dihapus.\n";
    }
}

void menuAdmin() {
    int pilihan;
    char kembali;

    do {
        system("cls");
        cout << "\n==============================" << endl;
        cout << "<< SIREN RENTAL KENDARAAN  >>" << endl;
        cout <<"==============================" << endl;
        cout << "\n========= MENU ADMIN =========\n";
        cout << "1. Tampilkan Semua Kendaraan\n";
        cout << "2. Tambah Kendaraan\n";
        cout << "3. Hapus Kendaraan\n";
        cout << "4. Perbarui Data Kendaraan\n";
        cout << "5. Lihat Antrian Booking\n";
        cout << "6. Proses Booking Berikutnya\n";
        cout << "7. tampilkan kendaraan yang diboking\n";
        cout << "8. Logout\n";
        cout <<"==============================" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                system("cls");
                displayAllVehicles();
                break;
            case 2:
                system("cls");
                TambahKendaaraan();
                break;
            case 3:
                system("cls");
                hapusKendaraan();
                break;
            case 4:
                system("cls");
                updateKendaraan();
                break;
            case 5:
                system("cls");
                printQueue(); 
                break;
            case 6:
                system("cls");
                printNextBill();
                break;
            case 7:
                system("cls");
                printAllBookedVehicles();
                break;
            case 8:
                cout << "Logout admin berhasil.\n";
                return;
            default:
                cout << "Pilihan tidak valid.\n";
        }

        cout << "\nKembali ke menu admin? (y/n): ";
        cin >> kembali;
        cin.ignore();
    } while (kembali == 'y' || kembali == 'Y');
}

void printSelectedBill(int userIndex) {
    if (isQueueEmpty()) {
        cout << "\n======================= DAFTAR BOOKING ANDA =======================\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << "| No | ID Transaksi | Nama Kendaraan       | Model           | Hari  | Total Harga  |\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << "|                                                                                   |\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << RED << "\nAnda belum memiliki booking.\n" << RESET;
        return;
    }

    // --- Group bookings by idTransaksi ---
    struct GroupedBooking {
        string idTransaksi;
        string namaKendaraan;
        string model;
        string hariList;      // <-- untuk daftar hari sewa, dipisah koma
        double totalHarga;
        Booking firstBooking; // Untuk detail
        int count;
    };

    vector<GroupedBooking> grouped;
    for (int i = queue.depan; i <= queue.belakang; ++i) {
        if (queue.data[i].userInfo.ema == users[userIndex].ema) {
            // Cek apakah idTransaksi sudah ada di grouped
            bool found = false;
            for (auto& g : grouped) {
                if (g.idTransaksi == queue.data[i].idTransaksi) {
                    g.namaKendaraan += ", " + queue.data[i].infoKendaraan.nama;
                    g.model += ", " + queue.data[i].infoKendaraan.model;
                    g.hariList += ", " + to_string(queue.data[i].rentalDays); // <-- tambahkan hari dengan koma
                    g.totalHarga += queue.data[i].infoKendaraan.Harga * queue.data[i].rentalDays;
                    g.count++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                GroupedBooking g;
                g.idTransaksi = queue.data[i].idTransaksi;
                g.namaKendaraan = queue.data[i].infoKendaraan.nama;
                g.model = queue.data[i].infoKendaraan.model;
                g.hariList = to_string(queue.data[i].rentalDays); // <-- hari pertama
                g.totalHarga = queue.data[i].infoKendaraan.Harga * queue.data[i].rentalDays;
                g.firstBooking = queue.data[i];
                g.count = 1;
                grouped.push_back(g);
            }
        }
    }

    if (grouped.empty()) {
        cout << "\n======================= DAFTAR BOOKING ANDA =======================\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << "| No | ID Transaksi | Nama Kendaraan       | Model           | Hari  | Total Harga  |\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << "|                                                                                   |\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << RED << "\nAnda belum memiliki booking.\n" << RESET;
        return;
    }

    // --- Tabel daftar booking (satu baris per transaksi) ---
    cout << "\n======================= DAFTAR BOOKING ANDA =======================\n";
    cout << "+----+--------------+----------------------+-----------------+-------+--------------------+\n";
    cout << "| No | ID Transaksi | Nama Kendaraan       | Model           | Hari  | Total Harga        |\n";
    cout << "+----+--------------+----------------------+-----------------+-------+--------------------+\n";
    for (size_t i = 0; i < grouped.size(); ++i) {
        cout << "| " << setw(2) << left << (i + 1)
             << " | " << setw(12) << left << grouped[i].idTransaksi
             << " | " << setw(21) << left << grouped[i].namaKendaraan.substr(0, 20)
             << "| " << setw(16) << left << grouped[i].model.substr(0, 15)
             << "| " << setw(5) << right << grouped[i].hariList.substr(0, 5) << " "   // <-- tampilkan hariList
             << "| Rp." << setw(15) << right << fixed << setprecision(0) << grouped[i].totalHarga << "|\n";
    }
    cout << "+----+--------------+----------------------+-----------------+-------+--------------------+\n";

    int pilihan;
    cout << "Pilih nomor booking yang ingin ditampilkan: ";
    cin >> pilihan;
    cin.ignore();
    system("cls");
    if (pilihan <= 0 || pilihan > (int)grouped.size()) {
        cout << "Pilihan tidak valid atau dibatalkan.\n";
        return;
    }

    // --- Tampilkan detail booking (ambil idTransaksi terpilih) ---
    string idTerpilih = grouped[pilihan - 1].idTransaksi;
    // Ambil semua booking dengan idTransaksi ini
    vector<Booking> detail;
    for (int i = queue.depan; i <= queue.belakang; ++i) {
        if (queue.data[i].userInfo.ema == users[userIndex].ema &&
            queue.data[i].idTransaksi == idTerpilih) {
            detail.push_back(queue.data[i]);
        }
    }

    // Tampilkan struk detail (format sama seperti struk booking)
    double total = 0;
    cout << "\n================================================================================\n";
    cout << "                                 CV. SIREN RENTAL KENDARAAN                                  \n";
    cout << "           Jl. kebonagung km12, sendangsari, Minggir, Sleman, daerah istimewa yogyakarta             \n";
    cout << "                         email: sirenretalken@gmail.com | Phone: 08123456789                      \n";
    cout << "================================================================================\n";
    cout << "=============================== STRUK PENYEWAAN ================================\n";
    cout << "Tanggal Booking : " << grouped[pilihan - 1].firstBooking.tanggalBooking << "\n";
    cout << "ID Transaksi    : " << grouped[pilihan - 1].idTransaksi << endl;
    cout << "CustomerID      : " << grouped[pilihan - 1].firstBooking.userInfo.userid << "\n";
    cout << "Customer        : " << grouped[pilihan - 1].firstBooking.userInfo.nama << "\n";
    cout << "Email           : " << grouped[pilihan - 1].firstBooking.userInfo.ema << "\n";
    cout << "Telepon         : " << grouped[pilihan - 1].firstBooking.userInfo.telepon << "\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout << "DETAIL PESANAN:\n";
    for (const auto& b : detail) {
        double subtotal = b.infoKendaraan.Harga * b.rentalDays;
        total += subtotal;
        string tanggalKembali = hitungTanggalKembali(b.tanggalBooking, b.rentalDays);
        cout << "\n  Kendaraan    : " << b.infoKendaraan.nama << " (" << b.infoKendaraan.model << ")\n";
        cout << "  Kategori     : " << b.infoKendaraan.kategori << "\n";
        cout << "  Harga/Hari   : Rp." << fixed << setprecision(0) << b.infoKendaraan.Harga << "\n";
        cout << "  Lama Sewa    : " << b.rentalDays << " hari\n";
        cout << "  Tgl. Kembali : " << tanggalKembali << "\n";
        cout << "  Subtotal     : Rp." << fixed << setprecision(0) << subtotal << "\n";
    }
    double pajak = total * tax / 100;
    double grandTotal = total + pajak;
    cout << "--------------------------------------------------------------------------------\n";
    cout <<right << setw(73) << fixed << setprecision(0) << "TOTAL         : Rp." << total << "\n";
    cout << right << setw(59) << fixed << setprecision(0)<< "PPN (" << tax << "%)     : Rp. "  << pajak << "\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout << right << setw(73) << fixed << setprecision(0) << "GRAND TOTAL   : Rp." << grandTotal << "\n";
    cout << "================================================================================\n";
    
}   

void printQueue() {
    if (isQueueEmpty()) {
        cout << "\n================================ DAFTAR BOOKING =================================\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << "| No | ID Transaksi | Nama Kendaraan       | Model           | Hari  | Total Harga  |\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << "|                                                                                   |\n";
        cout << "+----+--------------+----------------------+-----------------+-------+--------------+\n";
        cout << RED << "\nbooking kosong.\n" << RESET;
        return;
    }
    // --- Group bookings by idTransaksi ---
    struct GroupedBooking {
        string idTransaksi;
        string namaCustomer;
        string namaKendaraan;
        string model;
        string hariList;
        double totalHarga;
        Booking firstBooking;
        int count;
    };

    vector<GroupedBooking> grouped;
    for (int i = queue.depan; i <= queue.belakang; ++i) {
        Booking& b = queue.data[i];
        // Cek apakah idTransaksi sudah ada di grouped
        bool found = false;
        for (auto& g : grouped) {
            if (g.idTransaksi == b.idTransaksi) {
                g.namaKendaraan += ", " + b.infoKendaraan.nama;
                g.model += ", " + b.infoKendaraan.model;
                g.hariList += ", " + to_string(b.rentalDays);
                g.totalHarga += b.infoKendaraan.Harga * b.rentalDays;
                g.count++;
                found = true;
                break;
            }
        }
        if (!found) {
            GroupedBooking g;
            g.idTransaksi = b.idTransaksi;
            g.namaCustomer = b.userInfo.nama;
            g.namaKendaraan = b.infoKendaraan.nama;
            g.model = b.infoKendaraan.model;
            g.hariList = to_string(b.rentalDays);
            g.totalHarga = b.infoKendaraan.Harga * b.rentalDays;
            g.firstBooking = b;
            g.count = 1;
            grouped.push_back(g);
        }
    }

    cout << "\n====================================== ANTRIAN BOOKING SAAT INI ==========================================\n";
    cout << "No. | ID Transaksi | Nama Customer        | Kendaraan            | Model           | Hari | Total Harga\n";
    cout << "----+--------------+----------------------+----------------------+-----------------+------+----------------\n";
    for (size_t i = 0; i < grouped.size(); ++i) {
        cout << right << setw(3) << (i + 1) << " | ";
        cout << setw(12) << left << grouped[i].idTransaksi << " | ";
        cout << setw(20) << left << grouped[i].namaCustomer.substr(0, 19) << " | ";
        cout << setw(20) << left << grouped[i].namaKendaraan.substr(0, 20) << " | ";
        cout << setw(15) << left << grouped[i].model.substr(0, 15) << " | ";
        cout << setw(4) << right << grouped[i].hariList.substr(0, 9) << " | ";
        cout << "Rp." << fixed << setprecision(0) << grouped[i].totalHarga << endl;
    }
    cout << "============================================================================================================\n";

    // Pilih transaksi untuk lihat struk detail
    int pilih;
    cout << "Pilih nomor booking untuk lihat detail struk (0 untuk batal): ";
    cin >> pilih;
    cin.ignore();
    if (pilih <= 0 || pilih > (int)grouped.size()) return;

    // --- Tampilkan struk detail (seperti BookingKendaraan) ---
    string idTerpilih = grouped[pilih - 1].idTransaksi;
    vector<Booking> detail;
    for (int i = queue.depan; i <= queue.belakang; ++i) {
        if (queue.data[i].idTransaksi == idTerpilih) {
            detail.push_back(queue.data[i]);
        }
    }

    // Tampilkan struk detail (format sama seperti struk booking)
    double total = 0;
    cout << "\n================================================================================\n";
    cout << "                                 CV. SIREN RENTAL KENDARAAN                                  \n";
    cout << "           Jl. kebonagung km12, sendangsari, Minggir, Sleman, daerah istimewa yogyakarta             \n";
    cout << "                         email: sirenretalken@gmail.com | Phone: 08123456789                      \n";
    cout << "================================================================================\n";
    cout << "=============================== STRUK PENYEWAAN ================================\n";
    cout << "Tanggal Booking : " << grouped[pilih - 1].firstBooking.tanggalBooking << "\n";
    cout << "ID Transaksi    : " << grouped[pilih - 1].idTransaksi << endl;
    cout << "CustomerID      : " << grouped[pilih - 1].firstBooking.userInfo.userid << "\n";
    cout << "Customer        : " << grouped[pilih - 1].firstBooking.userInfo.nama << "\n";
    cout << "Email           : " << grouped[pilih - 1].firstBooking.userInfo.ema << "\n";
    cout << "Telepon         : " << grouped[pilih - 1].firstBooking.userInfo.telepon << "\n";
    cout << "--------------------------------------------------------------------------------\n";
    cout << "DETAIL PESANAN:\n";
    for (const auto& b : detail) {
        double subtotal = b.infoKendaraan.Harga * b.rentalDays;
        total += subtotal;
        string tanggalKembali = hitungTanggalKembali(b.tanggalBooking, b.rentalDays);
        cout << "\n  Kendaraan    : " << b.infoKendaraan.nama << " (" << b.infoKendaraan.model << ")\n";
        cout << "  Kategori     : " << b.infoKendaraan.kategori << "\n";
        cout << "  Harga/Hari   : Rp." << fixed << setprecision(0) << b.infoKendaraan.Harga << "\n";
        cout << "  Lama Sewa    : " << b.rentalDays << " hari\n";
        cout << "  Tgl. Kembali : " << tanggalKembali << "\n";
        cout << "  Subtotal     : Rp." << fixed << setprecision(0) << subtotal << "\n";
    }
    double pajak = total * tax / 100;
    double grandTotal = total + pajak;
    cout << "--------------------------------------------------------------------------------\n";
    cout << setw(50) << right << "TOTAL         : Rp." << setw(15) << fixed << setprecision(0) << total << "\n";
    cout << setw(50) << right << "PPN (" << tax << "%)     : Rp." << setw(15) << fixed << setprecision(0) << pajak << "\n";
    cout << "------------------------------------------------------------------------------------------ +\n";
    cout << setw(50) << right << "GRAND TOTAL   : Rp." << setw(15) << fixed << setprecision(0) << grandTotal << "\n";
    cout << "================================================================================\n";
}   
 
void inisialisasiQueue() {
    queue.depan = -1;
    queue.belakang = -1;
}

bool isQueueEmpty() {
    return queue.belakang == -1 || queue.depan > queue.belakang;
}

bool isQueueFull() {
    return queue.belakang >= MAX_QUEUE - 1;
}

void enqueue(Booking data) {
    if (isQueueFull()) {
        cout << "Antrian booking penuh.\n";
        return;
    }
    if (isQueueEmpty()) queue.depan = 0;
    queue.belakang++;
    queue.data[queue.belakang] = data;
}

void dequeue() {
    if (isQueueEmpty()) {
        // Hapus pesan "Antrian kosong" agar tidak muncul saat proses bill
        return;
    }
    // Menggunakan circular queue logic sederhana
    if (queue.depan == queue.belakang) {
        inisialisasiQueue(); // Reset queue jika ini elemen terakhir
    } else {
        queue.depan++; // Cukup majukan pointer depan
    }
}

void clearQueue() {
    inisialisasiQueue();
    cout << "\n[+] Antrian telah dikosongkan.\n";
}

// ==================================================================
// == BAGIAN YANG DITAMBAHKAN AGAR PROGRAM BISA BERJALAN (MINIMAL) ==
// ==================================================================

void enableVirtualTerminalProcessing() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        return;
    }
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        return;
    }
}

void insertionSortMobil(bool ascending) {
        if (!headMobil || !headMobil->next) return;

    Mobil* sortedHead = nullptr;
    Mobil* current = headMobil;
    while (current != nullptr) {
        Mobil* nextNode = current->next;

        if (sortedHead == nullptr || (ascending ? current->Harga <= sortedHead->Harga : current->Harga >= sortedHead->Harga)) {
            current->next = sortedHead;
            sortedHead = current;
        } else {
            Mobil* temp = sortedHead;
            while (temp->next != nullptr && (ascending ? temp->next->Harga < current->Harga : temp->next->Harga > current->Harga)) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = nextNode;
    }
    headMobil = sortedHead;

    TampilkanSemuaMobil();
}

void insertionSortMotor(bool ascending) {
        if (!headMotor || !headMotor->next) return;

    Motor* sortedHead = nullptr;
    Motor* current = headMotor;
    while (current != nullptr) {
        Motor* nextNode = current->next;

        if (sortedHead == nullptr || (ascending ? current->Harga <= sortedHead->Harga : current->Harga >= sortedHead->Harga)) {
            current->next = sortedHead;
            sortedHead = current;
        } else {
            Motor* temp = sortedHead;
            while (temp->next != nullptr && (ascending ? temp->next->Harga < current->Harga : temp->next->Harga > current->Harga)) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = nextNode;
    }
    headMotor = sortedHead;

    TampilkanSemuaMotor();
}

void updateKendaraan() {
        int pilihan;
    cout << "\nPilih jenis kendaraan yang ingin diperbarui:\n1. Mobil\n2. Motor\nPilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        TampilkanSemuaMobil();
        if (!headMobil) return;
        string nama;
        cout << "Masukkan NAMA mobil yang ingin diperbarui: ";
        getline(cin, nama);

        Mobil* current = headMobil;
        while (current && current->nama != nama) {
            current = current->next;
        }
        if (!current) {
            cout << "Mobil tidak ditemukan.\n";
            return;
        }

        cout << "\nData:\n";
        cout << "ID: "<<current->id << "\nNama: " << current->nama << "\nModel: " << current->model << "\nKategori: " << current->kategori
             << "\nHarga: Rp." << current->Harga << "\nStok: " << current->stok << endl;

        cout << "\nMasukkan data baru (tekan ENTER jika tidak diubah):\n";
        string input;
        cout << "ID baru : ";
        getline(cin, input);
        cout << "Nama baru: ";
        getline(cin, input);
        if (!input.empty()) current->nama = input;

        cout << "Model baru: ";
        getline(cin, input);
        if (!input.empty()) current->model = input;

        cout << "Kategori baru: ";
        getline(cin, input);
        if (!input.empty()) current->kategori = input;

        cout << "Harga baru (Rp.): ";
        getline(cin, input);
        if (!input.empty()) current->Harga = stod(input);

        cout << "Stok baru: ";
        getline(cin, input);
        if (!input.empty()) current->stok = stoi(input);

        cout << "Data mobil berhasil diperbarui.\n";
    } else if (pilihan == 2) {
        TampilkanSemuaMotor();
        if (!headMotor) return;
        string nama;
        cout << "Masukkan NAMA motor yang ingin diperbarui: ";
        getline(cin, nama);

        Motor* current = headMotor;
        while (current && current->nama != nama) {
            current = current->next;
        }
        if (!current) {
            cout << "[!] Motor tidak ditemukan.\n";
            return;
        }

        cout << "\nData lama:\n";
        cout << "Nama: " << current->nama << "\nModel: " << current->model << "\nKategori: " << current->kategori
             << "\nHarga: Rp." << current->Harga << "\nStok: " << current->stok << endl;

        cout << "\nMasukkan data baru (tekan ENTER untuk skip):\n";
        string input;
        cout << "Nama baru: ";
        getline(cin, input);
        if (!input.empty()) current->nama = input;

        cout << "Model baru: ";
        getline(cin, input);
        if (!input.empty()) current->model = input;

        cout << "Kategori baru: ";
        getline(cin, input);
        if (!input.empty()) current->kategori = input;

        cout << "Harga baru (Rp.): ";
        getline(cin, input);
        if (!input.empty()) current->Harga = stod(input);

        cout << "Stok baru: ";
        getline(cin, input);
        if (!input.empty()) current->stok = stoi(input);

        cout << "[+] Data motor berhasil diperbarui.\n";
    } else {
        cout << "[!] Pilihan tidak valid.\n";
    }
}

void searchKendaraan() {
        
    cout << "\n==================================== CARI KENDARAAN =================================\n";
             
    string namaCari;
    cout << "Masukkan nama kendaraan yang dicari: ";
    getline(cin, namaCari);

    bool ditemukan = false;

    Mobil* tempMobil = headMobil;
    int indexMobil = 0;
    while (tempMobil != nullptr) {
        if (tempMobil->nama == namaCari) {
            cout << "\n Data ditemukan di kategori MOBIL " << endl;
            cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
            cout << "| ID     | Nama Kendaraan       | Model           | Kategori        | Harga/Hari       | Stok  |\n";
            cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
            cout 
                 << "| " << setw(7) << tempMobil->id
                 << "| " << left << setw(21) << tempMobil->nama
                 << "| " << setw(16) << tempMobil->model
                 << "| " << setw(16) << tempMobil->kategori
                 << "| Rp." << right << setw(13) << fixed << setprecision(0) << tempMobil->Harga
                 << " | " << setw(5) << tempMobil->stok << " |\n";
            cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
            ditemukan = true;
            break; 
        }
        tempMobil = tempMobil->next;
        indexMobil++;
    }
    if (!ditemukan) {
        Motor* tempMotor = headMotor;
        int indexMotor = 0;
        while (tempMotor != nullptr) {
            if (tempMotor->nama == namaCari) {
                cout << "\n Data ditemukan di kategori MOTOR "<< endl;
                cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
                cout << "| ID     | Nama Kendaraan       | Model           | Kategori        | Harga/Hari       | Stok  |\n";
                cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
                cout << "| " << setw(7) << tempMotor->id
                     << "| " << left << setw(21) << tempMotor->nama
                     << "| " << setw(16) << tempMotor->model
                     << "| " << setw(16) << tempMotor->kategori
                     << "| Rp." << right << setw(13) << fixed << setprecision(0) << tempMotor->Harga
                     << " | " << setw(5) << tempMotor->stok << " |\n";
                cout << "+--------+----------------------+-----------------+-----------------+------------------+-------+\n";
                ditemukan = true;
                break;
            }
            tempMotor = tempMotor->next;
            indexMotor++;
        }
    }

    // Statement jika data tidak ditemukan di kedua kategori
    if (!ditemukan) {
        cout << "\n kendaraan dengan nama \"" << namaCari << "\" tidak ditemukan pada data kami." << endl;
    }
}

string generateRandomId() {
    // Fungsi sederhana untuk menghasilkan ID acak
    srand(time(NULL));
    return "ID" + to_string(rand() % 1000);
}

void loadingBar() {
        cout << "LOADING =";
    for (int i = 0; i < 22; ++i) {
        cout << "=";
        cout.flush();
        Sleep(100); // 100 ms per titik (total 1 detik)
    }
    cout << endl;
} 

string generateTransaksiId() {
    // Fungsi sederhana untuk menghasilkan ID Transaksi acak
    srand(time(NULL));
    return "TRX" + to_string(rand() % 9000 + 1000);
}

string hitungTanggalKembali(const string& tanggalBooking, int rentalDays) {
    // Format tanggalBooking: "DD-MM-YYYY"
    int dd, mm, yyyy;
    char dash1, dash2;
    istringstream iss(tanggalBooking);
    iss >> dd >> dash1 >> mm >> dash2 >> yyyy;
    if (iss.fail()) return tanggalBooking; // fallback jika parsing gagal

    tm t = {};
    t.tm_mday = dd;
    t.tm_mon = mm - 1; // bulan mulai dari 0
    t.tm_year = yyyy - 1900;

    // Tambahkan hari sewa
    time_t waktu = mktime(&t);
    waktu += rentalDays * 24 * 60 * 60; // tambah hari dalam detik

    tm* kembali = localtime(&waktu);

    // Format kembali ke DD-MM-YYYY
    ostringstream oss;
    oss << setfill('0') << setw(2) << kembali->tm_mday << "-"
        << setfill('0') << setw(2) << (kembali->tm_mon + 1) << "-"
        << (kembali->tm_year + 1900);
    return oss.str();
}


string inputPassword() {
    string pass;
    int ch; // Change to int to handle extended ASCII codes
    while (true) {
        ch = _getch(); // baca karakter tanpa echo
        if (ch == 13) { // Enter
            cout << endl;
            break;
        } else if (ch == 8) { // Backspace
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else if (ch == 0 || ch == 224) {
            _getch(); // abaikan karakter spesial
        } else {
            pass += static_cast<char>(ch);
            cout << '*';
        }
    }
    return pass;
}
void printAllBookedVehicles() {
    if (isQueueEmpty()) {
        cout << "\n============================================= DAFTAR KENDARAAN YANG DIBOOKING ========================================================\n";
        cout << "+----------------------+---------------+---------------+----------------------+---------------+------+---------------+---------------+\n";
        cout << "| Nama Kendaraan       | Model         | Kategori      | Nama Penyewa         | ID Transaksi  | Hari | Tgl Booking   | Tgl Kembali   |\n";
        cout << "+----------------------+---------------+---------------+----------------------+---------------+------+---------------+---------------+\n";
        cout << "|                      |               |               |                      |               |      |               |               |\n";
        cout << "+----------------------+---------------+---------------+----------------------+---------------+------+---------------+---------------+\n";
        cout << RED << "\nTidak ada kendaraan yang sedang dibooking.\n" << RESET;
        return;
    }
    cout << "\n============================================= DAFTAR KENDARAAN YANG DIBOOKING ========================================================\n";
    cout << "+----------------------+---------------+---------------+----------------------+---------------+------+---------------+---------------+\n";
    cout << "| Nama Kendaraan       | Model         | Kategori      | Nama Penyewa         | ID Transaksi  | Hari | Tgl Booking   | Tgl Kembali   |\n";
    cout << "+----------------------+---------------+---------------+----------------------+---------------+------+---------------+---------------+\n";

    for (int i = queue.depan; i <= queue.belakang; ++i) {
        const Booking& b = queue.data[i];
        string tglKembali = hitungTanggalKembali(b.tanggalBooking, b.rentalDays);
        cout << "| " << setw(21) << left << b.infoKendaraan.nama.substr(0,20)
             << "| " << setw(14) << left << b.infoKendaraan.model.substr(0,13)
             << "| " << setw(14) << left << b.infoKendaraan.kategori.substr(0,13)
             << "| " << setw(21) << left << b.userInfo.nama.substr(0,20)
             << "| " << setw(14) << left << b.idTransaksi.substr(0,13)
             << "| " << setw(4)  << right << b.rentalDays << " "
             << "| " << setw(14) << left << b.tanggalBooking.substr(0,13)
             << "| " << setw(14) << left << tglKembali.substr(0,13)
             << "|\n";
    }
    cout << "+----------------------+---------------+---------------+----------------------+---------------+------+---------------+---------------+\n";
}
