#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#define RESET   "\033[0m"
#define CYAN    "\033[36m"

const int MAX_USERS = 100;
struct User {
    string ema;
    string pass;
    string nama;
    long long nik; 
    string alamat;
};

struct Admin {
    string email;
    string password;
    string nama;
};

enum JenisKendaraan { MOBIL, MOTOR };

struct Kategori {
    string nama;
    JenisKendaraan jenis;
};

struct Mobil {
    string nama, model, kategori;
    double Harga;
    int stok; 
    Mobil* next;
};

struct Motor {
    string nama, model, kategori;
    double Harga;
    int stok; 
    Motor* next;
};

struct InfoKendaraan {
    string nama;
    string model;
    string kategori;
    double Harga;
};

const int MAX_QUEUE = 100;
struct Booking {
    User userInfo;
    InfoKendaraan infoKendaraan; 
    int rentalDays;
};

struct Queue {
    int depan, belakang;
    Booking data[MAX_QUEUE];
} queue;

//global variable
User users[MAX_USERS];
int jumlahUser = 0;

Admin admin = {"admin@gmail.com", "admin123", "Administrator" };

Mobil* headMobil = nullptr; 
Motor* headMotor = nullptr;

Kategori daftarKategori[] = {
    {"Sport", MOBIL},
    {"SUV", MOBIL},
    {"City Car", MOBIL},
    {"Skuter", MOTOR},
    {"Adventure Motor", MOTOR},
    {"Big Bike", MOTOR}
};

// DEKLARASI FUNGSI 
void TampilkanSemuaMobil();
void TampilkanSemuaMotor();
void displayAllVehicles();
void KategoriKendaraan();
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


int main() {

    // data sementara M untuk demonstrasi
    users[0] = {"naufal123", "123", "Naufal", 1234567890123456, "Jl. Contoh No. 1"};
    jumlahUser = 1; // Inisialisasi satu pengguna

    // Mobil
    Mobil* m1 = new Mobil{"avanza", "2023", "City Car", 300000, 5, nullptr};
    Mobil* m2 = new Mobil{"pajero Sport", "2024", "SUV", 800000, 2, nullptr};
    Mobil* m3 = new Mobil{"ferrari 488", "2022", "Sport", 5000000, 1, nullptr};
    headMobil = m1;
    m1->next = m2;
    m2->next = m3;

    // Motor
    Motor* mt1 = new Motor{"vario 160", "2024", "Skuter", 150000, 10, nullptr};
    Motor* mt2 = new Motor{"ninja ZX-25R", "2023", "Big Bike", 750000, 3, nullptr};
    Motor* mt3 = new Motor{"crf150l", "2023", "Adventure Motor", 250000, 4, nullptr};
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
        cout << "\n==============================" << endl;
        cout << CYAN << "<< SIREN RENTAL KENDARAAN  >>" << RESET << endl;
        cout << "==============================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Login Sebagai Admin" << endl;
        cout << "3. Daftar" << endl;
        cout << "4. Tampilkan Kategori" << endl;
        cout << "5. Tampilkan List Kendaraan" << endl;
        cout << "6. Keluar" << endl;
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
                    getline(cin, password);

                    bool ditemukan = false;
                    for (int i = 0; i < jumlahUser; i++) {
                        if (users[i].ema == email && users[i].pass == password) {
                            userNow = i;
                            cout << "\nLogin berhasil. Selamat datang, " << users[userNow].nama << "!" << endl;
                            loginSuccess = true;
                            ditemukan = true;
                            break;
                        }
                    }

                    if (ditemukan) {
                        break;
                    } else {
                        attempts--;
                        cout << "\nEmail atau password salah. Sisa percobaan: " << attempts << endl;
                        if (attempts == 0) {
                            cout << "Akun terkunci. Silakan hubungi admin." << endl;
                        }
                    }
                }
                
                if(loginSuccess) {
                    int menuUtama;
                    char kembali;
                    bool logout = false;
                    do {
                        cout << "\n========== HOME ==========" << endl;
                        cout << "1. Logout" << endl;
                        cout << "2. Tampilkan Biodata Saya" << endl;
                        cout << "3. Tampilkan Kategori" << endl;
                        cout << "4. Tampilkan List Kendaraan" << endl;
                        cout << "5. Booking Kendaraan" << endl;
                        cout << "6. Struk Transaksi Saya" << endl;
                        cout << "7. Lihat Antrian Booking" << endl;
                        cout << "==========================" << endl;
                        cout << "Masukkan pilihan: ";
                        cin >> menuUtama;
                        cin.ignore();

                        switch (menuUtama) {
                            case 1:
                                cout << "\nLogout berhasil." << endl;
                                logout = true;
                                break;
                            case 2:
                                cout << "\n--- BIODATA SAYA ---" << endl;
                                cout << "Nama   : " << users[userNow].nama << endl;
                                cout << "NIK    : " << users[userNow].nik << endl;
                                cout << "Alamat : " << users[userNow].alamat << endl;
                                cout << "Email  : " << users[userNow].ema << endl;
                                break;
                            case 3:
                                KategoriKendaraan();
                                break;
                            case 4:
                                cout << "\n--- MOBIL ---\n";
                                TampilkanSemuaMobil();
                                cout << "\n--- MOTOR ---\n";
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
                            case 5:
                                BookingKendaraan(userNow);
                                break;
                            case 6:
                                printSelectedBill(userNow);
                                break;
                            case 7:
                                printQueue();
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
            case 2: {
                cout << "Masukkan email admin: ";
                getline(cin, email);
                cout << "Masukkan password admin: ";
                getline(cin, password);
                if (admin.email == email && admin.password == password) {
                    cout << "\nLogin berhasil. Selamat datang, " << admin.nama << "!\n";
                    menuAdmin();
                } else {
                    cout << "Email dan password salah!\n";
                }
                break;
            }
            case 3:
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
                    cout << "Masukkan email: ";
                    getline(cin, users[jumlahUser].ema);
                    cout << "Masukkan password: ";
                    getline(cin, users[jumlahUser].pass);
                    jumlahUser++;
                    cout << "\nPendaftaran berhasil. Silakan login." << endl;
                }
                break;

            case 4:
                KategoriKendaraan();
                break;
            case 5:
                cout << "\n--- MOBIL ---\n";
                TampilkanSemuaMobil();
                cout << "\n--- MOTOR ---\n";
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
            case 6:
                cout << "\nTerima kasih telah menggunakan program." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }

        if (pilihan == 6) break;

        cout << "\nKembali ke menu login? (y/n): ";
        cin >> ulang;
        cin.ignore();
    } while (ulang == 'y' || ulang == 'Y');

    cout << "\nTerima kasih telah menggunakan program." << endl;
    return 0;
}

void KategoriKendaraan() {
    int jumlahKategori = sizeof(daftarKategori) / sizeof(daftarKategori[0]);
    int nomorMobil = 1;
    int nomorMotor = 1;

    cout << "\n=== Kategori Mobil ===" << endl;
    for (int i = 0; i < jumlahKategori; i++) {
        if (daftarKategori[i].jenis == MOBIL) {
            cout << nomorMobil++ << ". " << daftarKategori[i].nama << endl;
        }
    }

    cout << "\n=== Kategori Motor ===" << endl;
    for (int i = 0; i < jumlahKategori; i++) {
        if (daftarKategori[i].jenis == MOTOR) {
            cout << nomorMotor++ << ". " << daftarKategori[i].nama << endl;
        }
    }
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
    cout << "\n+----------------------+-----------------+-----------------+------------------+-------+\n";
    cout << "| Nama Kendaraan       | Model           | Kategori        | Harga/Hari       | Stok  |\n";
    cout << "+----------------------+-----------------+-----------------+------------------+-------+\n";
    Mobil* temp = headMobil;
    while (temp) {
        cout << "| " << left << setw(21) << temp->nama
             << "| " << setw(16) << temp->model
             << "| " << setw(16) << temp->kategori
             << "| Rp." << right << setw(13) << fixed << setprecision(0) << temp->Harga
             << " | " << setw(5) << temp->stok << " |\n";
        temp = temp->next;
    }
    cout << "+----------------------+-----------------+-----------------+------------------+-------+\n";
}

void TampilkanSemuaMotor() {
    if (!headMotor) {
        cout << "\nTidak ada motor yang tersedia.\n";
        return;
    }
    cout << "\n+----------------------+-----------------+-----------------+------------------+-------+\n";
    cout << "| Nama Kendaraan       | Model           | Kategori        | Harga/Hari       | Stok  |\n";
    cout << "+----------------------+-----------------+-----------------+------------------+-------+\n";
    Motor* temp = headMotor;
    while (temp) {
        cout << "| " << left << setw(21) << temp->nama
             << "| " << setw(16) << temp->model
             << "| " << setw(16) << temp->kategori
             << "| Rp." << right << setw(13) << fixed << setprecision(0) << temp->Harga
             << " | " << setw(5) << temp->stok << " |\n";
        temp = temp->next;
    }
    cout << "+----------------------+-----------------+-----------------+------------------+-------+\n";
}

void TambahKendaaraan() {
    int pilihan;
    cout << "\nPilih jenis kendaraan yang akan ditambahkan:\n 1. Mobil\n 2. Motor\nPilih 1/2: ";
    cin >> pilihan;
    cin.ignore(); 

    if (pilihan == 1) {
        Mobil* newMobil = new Mobil();
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
    int pilihan;
    cout << "\nPilih jenis kendaraan:\n 1. Mobil\n 2. Motor\nPilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        TampilkanSemuaMobil();
        if (!headMobil) return;

        string carNameToBook;
        cout << "Masukkan NAMA mobil yang ingin dibooking: ";
        getline(cin, carNameToBook);

        Mobil* carToBook = nullptr;
        for (Mobil* temp = headMobil; temp; temp = temp->next) {
            if (temp->nama == carNameToBook) {
                carToBook = temp;
                break;
            }
        }

        if (!carToBook) {
            cout << "Gagal booking karena Mobil tidak ditemukan\n";
            return;
        }
        if (carToBook->stok <= 0) {
            cout << "Stok mobil habis, tidak bisa dipesan.\n";
            return;
        }

        Booking booking;
        booking.userInfo = users[userIndex];
        booking.infoKendaraan.nama = carToBook->nama;
        booking.infoKendaraan.model = carToBook->model;
        booking.infoKendaraan.kategori = carToBook->kategori;
        booking.infoKendaraan.Harga = carToBook->Harga;
        
        cout << "Berapa hari ingin disewa?: ";
        cin >> booking.rentalDays;
        cin.ignore();

        if (booking.rentalDays <= 0) {
            cout << "Gagal booking karena Durasi sewa tidak valid\n";
            return;
        }
        carToBook->stok--; 
        enqueue(booking);
    } else if (pilihan == 2) {
        TampilkanSemuaMotor();
        if (!headMotor) return;

        string motorNameToBook;
        cout << "Masukkan NAMA motor yang ingin dibooking: ";
        getline(cin, motorNameToBook);

        Motor* motorToBook = nullptr;
        for (Motor* temp = headMotor; temp; temp = temp->next) {
            if (temp->nama == motorNameToBook) {
                motorToBook = temp;
                break;
            }
        }

        if (!motorToBook) {
            cout << "\n[!] Motor tidak ditemukan. Gagal booking.\n";
            return;
        }
        if (motorToBook->stok <= 0) {
            cout << "\n[!] Stok motor habis, tidak bisa dipesan.\n";
            return;
        }

        Booking booking;
        booking.userInfo = users[userIndex];
        booking.infoKendaraan.nama = motorToBook->nama;
        booking.infoKendaraan.model = motorToBook->model;
        booking.infoKendaraan.kategori = motorToBook->kategori;
        booking.infoKendaraan.Harga = motorToBook->Harga;

        cout << "Berapa hari ingin disewa?: ";
        cin >> booking.rentalDays;
        cin.ignore();

        if (booking.rentalDays <= 0) {
            cout << "[!] Durasi sewa tidak valid. Gagal booking.\n";
            return;
        }
        motorToBook->stok--;
        enqueue(booking);
    } else {
        cout << "[!] Pilihan tidak valid.\n";
    }
}

void printNextBill() {
    if (isQueueEmpty()) {
        cout << "\nTidak ada booking dalam antrian.\n";
        return;
    }
    Booking b = queue.data[queue.depan];
    double total = b.infoKendaraan.Harga * b.rentalDays;

    cout << "\n======= INVOICE BOOKING BERIKUTNYA =======\n"
         << "Customer: " << b.userInfo.nama << "\n"
         << "Email   : " << b.userInfo.ema << "\n"
         << "Kendaraan: " << b.infoKendaraan.nama << " (" << b.infoKendaraan.model << ")\n"
         << "Hari    : " << b.rentalDays << "\n"
         << "Harga   : Rp." << b.infoKendaraan.Harga << "/day\n"
         << "------------------------------------------\n"
         << "TOTAL   : Rp." << total << "\n"
         << "==========================================\n";
    
    dequeue(); 
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
        cout << "\n======== MENU ADMIN =======\n";
        cout << "1. Logout\n";
        cout << "2. Tampilkan Semua Kendaraan\n";
        cout << "3. Tambah Kendaraan\n";
        cout << "4. Hapus Kendaraan\n";
        cout << "5. Lihat Antrian Booking\n";
        cout << "6. Proses Booking Berikutnya\n";
        cout << "7. Perbarui Data Kendaraan\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                cout << "Logout admin berhasil.\n";
                return;
            case 2:
                displayAllVehicles();
                break;
            case 3:
                TambahKendaaraan();
                break;
            case 4:
                hapusKendaraan();
                break;
            case 5:
                printQueue(); 
                break;
            case 6:
                printNextBill();
                break;
            case 7:
                updateKendaraan();
                break;
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
        cout << "\nAnda belum memiliki booking.\n";
        return;
    }

    Booking userBookings[MAX_QUEUE];
    int count = 0;

    for (int i = queue.depan; i <= queue.belakang; ++i) {
        if (queue.data[i].userInfo.ema == users[userIndex].ema) {
            userBookings[count++] = queue.data[i];
        }
    }

    if (count == 0) {
        cout << "\nAnda belum memiliki booking.\n";
        return;
    }

    cout << "\n======= DAFTAR BOOKING ANDA =======\n";
    for (int i = 0; i < count; ++i) {
        cout << (i + 1) << ". " << userBookings[i].infoKendaraan.nama << " - " << userBookings[i].infoKendaraan.model << endl;
    }

    int pilihan;
    cout << "Pilih nomor booking yang ingin ditampilkan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan <= 0 || pilihan > count) {
        cout << "Pilihan tidak valid atau dibatalkan.\n";
        return;
    }

    Booking b = userBookings[pilihan - 1];
    double total = b.infoKendaraan.Harga * b.rentalDays;

    cout << "\n======= DETAIL BOOKING =======\n"
         << "Customer : " << b.userInfo.nama << "\n"
         << "Email    : " << b.userInfo.ema << "\n"
         << "Alamat   : " << b.userInfo.alamat << "\n"
         << "Kendaraan: " << b.infoKendaraan.nama << " (" << b.infoKendaraan.model << ")\n"
         << "Hari     : " << b.rentalDays << "\n"
         << "Harga    : Rp." << b.infoKendaraan.Harga << "/day\n"
         << "------------------------------\n"
         << "TOTAL    : Rp." << total << "\n"
         << "==============================\n";
}

void inisialisasiQueue() {
    queue.depan = -1;
    queue.belakang = -1;
}

bool isQueueEmpty() {
    return queue.belakang == -1;
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
    cout << "\nBooking berhasil! Kendaraan telah dimasukkan ke dalam antrian.\n";
}

void dequeue() {
    if (isQueueEmpty()) {
        cout << "Antrian kosong.\n";
        return;
    }
    cout << "\nBooking untuk " << queue.data[queue.depan].userInfo.nama << " telah diproses dan dihapus dari antrian\n";
    for (int i = queue.depan; i < queue.belakang; i++) {
        queue.data[i] = queue.data[i + 1];
    }
    queue.belakang--;
    if (queue.belakang < queue.depan) inisialisasiQueue();
}

void clearQueue() {
    inisialisasiQueue();
    cout << "\n[+] Antrian telah dikosongkan.\n";
}

void printQueue() {
    if (isQueueEmpty()) {
        cout << "\n[!] Antrian booking kosong.\n";
        return;
    }
    cout << "\n========================= ANTRIAN BOOKING SAAT INI =========================\n";
    cout << "No. | Nama Customer        | Kendaraan            | Hari | Total Harga\n";
    cout << "----+----------------------+----------------------+------+----------------\n";

    for (int i = queue.depan; i <= queue.belakang; ++i) {
        Booking b = queue.data[i];
        double total = b.infoKendaraan.Harga * b.rentalDays;

        cout << right << setw(3) << (i - queue.depan + 1) << " | ";
        cout << left << setw(20) << b.userInfo.nama << " | ";
        cout << left << setw(20) << b.infoKendaraan.nama << " | ";
        cout << right << setw(4) << b.rentalDays << " | ";
        cout << "Rp." << fixed << setprecision(0) << total << endl;
    }
    cout << "============================================================================\n";
    cout << "Total booking dalam antrian: " << (queue.belakang - queue.depan + 1) << endl;
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
        cout << "Nama: " << current->nama << "\nModel: " << current->model << "\nKategori: " << current->kategori
             << "\nHarga: Rp." << current->Harga << "\nStok: " << current->stok << endl;

        cout << "\nMasukkan data baru (tekan ENTER jika tidak diubah):\n";
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