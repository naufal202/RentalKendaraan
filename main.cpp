#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_USERS = 100;

struct User {
    string ema;
    string pass;
    string nama;
    int nik;
    string alamat;
};


User users[MAX_USERS];
int userCount = 0;

int login(const string& email, const string& password) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].ema == email && users[i].pass == password) { 
            cout << "Login berhasil. Selamat datang, " << users[i].nama << "!" << endl;
            return i;
        }
    }
    return -1;
}

struct Admin {
    char email[100];
    char password[100];
    string nama;
};

Admin admin = {"admin@gmail.com", "admin123", "Administrator" };

bool loginAdmin(string email, string password) {
    if (admin.email == email && admin.password == password) {
        return true;
    }
    return false;
}

enum JenisKendaraan { MOBIL, MOTOR };

struct Kategori {
    string nama;
    JenisKendaraan jenis;
};

struct Mobil {
    string name, model, kategori;
    double pricePerDay;
    Mobil* next;
};

struct Motor {
    string name, model, kategori;
    double pricePerDay;
    Motor* next;
};

struct Customer {
    string name, address;
};

struct Booking {
    User userInfo;
    Mobil carInfo;
    int rentalDays;
};
const int MAX_QUEUE = 100;

struct Queue {
    int depan, belakang;
    Booking data[MAX_QUEUE];
} queue;

// global variabel
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


//deklarasi fungsi
void displayAllVehicles();
void KategoriKendaraan();
void addVehicle();
void bookACar(int userIndex);
void printNextBill();
void hapusKendaraan();
void menuAdmin();
void printSelectedBill(int UserIndex);
void inisialisasi();
bool isEmpty();
bool isFull();
void enqueue(Booking data);
void dequeue();
void clear();
void printQueue();



int main() {
    int pilihan;
    char ulang;
    string email, password;
    int UserNow;

    do {
        cout << "==============================" << endl;
        cout << "<< SIREN RENTAL KENDARAAN  >>" << endl;
        cout << "==============================" << endl;
        cout << "1. Login" << endl;
        cout << "2. Login Sebagai Admin" << endl;
        cout << "3. Daftar" << endl;
        cout << "4. tampilkan kategori" << endl;
        cout << "5. tampilkan list kendaraan" << endl;
        cout << "6. Keluar" << endl;
        cout << "==============================" << endl;
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: {
                int attempts = 3;
                while (attempts > 0) {
                    cout << "Masukkan email: ";
                    getline(cin, email);
                    cout << "Masukkan password: ";
                    getline(cin, password);

                    UserNow = login(email, password);
                    if (UserNow != -1) {
                        int menuUtama;
                        char kembali;
                        do {
                            cout << "\n========== HOME ==========" << endl;
                            cout << "1. Logout" << endl;
                            cout << "2. Tampilkan biodata saya" << endl;
                            cout << "3. tampilkan kategori" << endl;
                            cout << "4. tampilkan list kendaraan" << endl;
                            cout << "5. Booking kendaraan" << endl;
                            cout << "6. Struk transaksi" << endl;
                            cout << "7. Lihat antrian booking" << endl;
                            cout << "==========================" << endl;
                            cout << "Masukkan pilihan: ";
                            cin >> menuUtama;
                            cin.ignore();

                            switch (menuUtama) {
                                case 1:
                                    cout << "Logout berhasil.\n" << endl;
                                    goto keluarMenuUtama;
                                case 2:
                                    cout << "Nama   : " << users[UserNow].nama << endl;
                                    cout << "NIK    : " << users[UserNow].nik << endl;
                                    cout << "Alamat : " << users[UserNow].alamat << endl;
                                    cout << "Email  : " << users[UserNow].ema << endl;
                                    break;
                                case 3:
                                    KategoriKendaraan();
                                    break;
                                case 4:
                                    displayAllVehicles();
                                    break;
                                case 5:
                                    bookACar(UserNow);
                                    break;
                                case 6:
                                    printSelectedBill(UserNow);
                                    break;
                                case 7:
                                    printQueue();
                                    break;
                                default:
                                    cout << "Pilihan tidak valid." << endl;
                            }

                            cout << "Kembali ke menu utama? (y/n): ";
                            cin >> kembali;
                            cin.ignore();
                        } while (kembali == 'y' || kembali == 'Y');
                        keluarMenuUtama:
                        break;
                    } else {
                        attempts--;
                        cout << "Email atau password salah. Sisa percobaan: " << attempts << endl;
                        if (attempts == 0) {
                            cout << "Akun terkunci. Silakan coba lagi nanti." << endl;
                        }
                    }
                }
                break;
            }
            case 2: {
                cout << "Masukkan email admin: ";
                getline(cin, email);
                cout << "Masukkan password admin: ";
                getline(cin, password);

                if (loginAdmin(email, password)) {
                cout << "Login berhasil. Selamat datang, " << admin.nama << "!\n";
                menuAdmin(); 
                } else {
                cout << "Email dan password salah!\n";
                }
                break;
            }

            case 3:
                if (userCount >= MAX_USERS) {
                    cout << "Pendaftaran gagal. Kapasitas penuh." << endl;
                    break;
                }
                cout << "Masukkan nama: ";
                getline(cin, users[userCount].nama);
                cout << "Masukkan NIK: ";
                cin >> users[userCount].nik;
                cin.ignore();
                cout << "Masukkan alamat: ";
                getline(cin, users[userCount].alamat);
                cout << "Masukkan email: ";
                getline(cin, users[userCount].ema);
                cout << "Masukkan password: ";
                getline(cin, users[userCount].pass);
                userCount++;
                cout << "Pendaftaran berhasil. Silakan login.\n \n" << endl;
                
                break;

            case 4:
                KategoriKendaraan();
                break;
            case 5:
                displayAllVehicles();
                break;

            case 6:
                cout << "Terima kasih telah menggunakan program. \n \n" << endl;
                return 0;
                

            default:
                cout << "Pilihan tidak valid." << endl;
                break;
        }

        cout << "Kembali ke menu login? (y/n): ";
        cin >> ulang;
        cin.ignore();
    } while (ulang == 'y' || ulang == 'Y');

    return 0;
}

int jumlahKategori = sizeof(daftarKategori) / sizeof(daftarKategori[0]);

void KategoriKendaraan() {
//    int pilihan;
    char kembali;;
//    cout << "pilih kategori \n 1. Mobil \n 2. Motor \n pilih 1/2 : ";
//    cin >> pilihan;
//    cin.ignore();
    int jumlahKategori = sizeof(daftarKategori) / sizeof(daftarKategori[0]);
//    if(pilihan == 1) {
        cout << "\n=== Kategori Mobil ===" << endl;
        for (int i = 0; i < jumlahKategori; i++) {
        if (daftarKategori[i].jenis == MOBIL) {
            cout << i + 1 << ". " << daftarKategori[i].nama << endl;
        }
    }
//    }
//    if (pilihan == 2) {
        cout << "\n=== Kategori Motor ===" << endl;
        for (int i = 0; i < jumlahKategori; i++) {
            if (daftarKategori[i].jenis == MOTOR) {
                cout << i - 2 << ". " << daftarKategori[i].nama << endl;
            }
        }
 //   }

    // Tanyakan apakah ingin kembali ke menu kategori
    cout << "Kembali ke menu kategori? (y/n): ";
    cin >> kembali;
    cin.ignore();
    if (kembali == 'y' || kembali == 'Y') {
        KategoriKendaraan();
    }
}

void displayAllVehicles() {
    int pilihan;
    cout << "pilih jenis kendaraan \n 1. Mobil \n 2. Motor \n pilih 1/2 : ";
    cin >> pilihan;
    cin.ignore();
    cout << "\n--- Semua Kendaraan yang Tersedia ---\n";
    if (pilihan == 1) {
        if (!headMobil) {
            cout << "Tidak Ada Kendaraan yang tersedia \n \n";
            return;
        }

    cout << "+----------------------+-----------------+-----------------+-------------+\n";
    cout << "| Nama Kendaraan       | Model           | Kategori        | Harga/Day   |\n";
    cout << "+----------------------+-----------------+-----------------+-------------+\n";

        Mobil* temp = headMobil;
        while (temp) {
            cout << "| " << left << setw(21) << temp->name
                 << "| " << setw(16) << temp->model
                 << "| " << setw(16) << temp->kategori
                 << "| Rp." << setw(16) << temp->pricePerDay << "|\n";
            temp = temp->next;
        }
     cout << "+----------------------+-----------------+-----------------+-------------+\n";
    } else if (pilihan == 2) {
        if (!headMotor) {
            cout << "Tidak Ada Kendaraan yang tersedia \n\n";
            return;
        }
        Motor* temp = headMotor;
        while (temp) {
            cout << "Name: " << temp->name << " | Model: " << temp->model << " | kategori: " << temp->kategori
                << " | Price: Rp." << temp->pricePerDay << "/day\n";
            temp = temp->next;
        }
        cout << "-----------------------------\n\n";
    } else {
        cout << "Pilihan tidak valid.\n\n" << endl;
}

}

void addVehicle() {
    int pilihan;
    char kembali;
    cout << "pilih jenis kendaraan yang akan ditambahkan\n 1. Mobil \n 2. Motor \n pilih 1/2 : ";
    cin >> pilihan;
    cin.ignore();
    if (pilihan ==1) {
    Mobil* newMobil = new Mobil();
    cout << "Masukkan nama Mobil: ";
    getline(cin, newMobil->name);
    cout << "Masukkan model Mobil: ";
    getline(cin, newMobil->model);
    cout << "Masukkan Kategori Mobil: ";
    getline(cin, newMobil->kategori);
    cout << "Masukkan harga sewa /Hari: Rp.";
    cin >> newMobil->pricePerDay;
    cin.ignore();

    newMobil->next = nullptr;

    if (!headMobil)
        headMobil = newMobil;
    else {
        Mobil* temp = headMobil;
        while (temp->next)
            temp = temp->next;
        temp->next = newMobil;
    }

    cout << "\n[+] Kendaraan telah ditambahkan!\n"; 
    } else if (pilihan == 2) {
        Motor* newMotor = new Motor();
        cout << "Masukkan nama Motor: ";
        getline(cin, newMotor->name);
        cout << "Masukkan model Motor: ";
        getline(cin, newMotor->model);
        cout << "Masukkan Kategori Motor: ";
        getline(cin, newMotor->kategori);
        cout << "Masukkan Harga sewa Motor per Hari: Rp.";
        cin >> newMotor->pricePerDay;
        cin.ignore();

        newMotor->next = nullptr;

        if (!headMotor)
            headMotor = newMotor;
        else {
            Motor* temp = headMotor;
            while (temp->next)
                temp = temp->next;
            temp->next = newMotor;
        }

        cout << "\n[+] Kendaraan telah ditambahkan!\n"; 
    } else {
        cout << "Pilihan tidak valid.\n\n" << endl;
    }  cout << "Kembali ke menu tambah kendaraan? (y/n): ";
        cin >> kembali;
        cin.ignore();
        if (kembali == 'y' || kembali == 'Y') {
            addVehicle();
}}

void bookACar(int userIndex) {
    int pilihan;
    cout << "Pilih jenis kendaraan:\n 1. Mobil \n 2. Motor \n Pilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        if (!headMobil) {
            cout << "\n Maaf, tidak ada mobil tersedia.\n";
            return;
        }

        displayAllVehicles();
        string carNameToBook;
        cout << "Masukkan Nama Mobil yang ingin dibooking: ";
        getline(cin, carNameToBook);

        Mobil* carToBook = nullptr;
        for (Mobil* temp = headMobil; temp; temp = temp->next) {
            if (temp->name == carNameToBook) {
                carToBook = temp;
                break;
            }
        }

        if (!carToBook) {
            cout << "\n Gagal booking karena Mobil tidak ditemukan\n";
            return;
        }

        Booking booking;
        booking.carInfo = *carToBook;
        booking.userInfo = users[userIndex];
        cout << "Berapa hari ingin disewa?: ";
        cin >> booking.rentalDays;
        cin.ignore();

        if (booking.rentalDays <= 0) {
            cout << "\nGagal booking karena Durasi sewa tidak valid\n";
            return;
        }

        enqueue(booking);
    }

    else if (pilihan == 2) {
        if (!headMotor) {
            cout << "\n[!] Maaf, tidak ada motor tersedia.\n";
            return;
        }

        displayAllVehicles();  
        string motorNameToBook;
        cout << "Masukkan NAMA motor yang ingin dibooking: ";
        getline(cin, motorNameToBook);

        Motor* motorToBook = nullptr;
        for (Motor* temp = headMotor; temp; temp = temp->next) {
            if (temp->name == motorNameToBook) {
                motorToBook = temp;
                break;
            }
        }

        if (!motorToBook) {
            cout << "\n[!] Motor tidak ditemukan. Gagal booking.\n";
            return;
        }

        Booking booking;
        booking.carInfo.name = motorToBook->name;
        booking.carInfo.model = motorToBook->model;
        booking.carInfo.kategori = motorToBook->kategori;
        booking.carInfo.pricePerDay = motorToBook->pricePerDay;
        booking.userInfo = users[userIndex];
        cout << "Berapa hari ingin disewa?: ";
        cin >> booking.rentalDays;
        cin.ignore();

        if (booking.rentalDays <= 0) {
            cout << "[!] Durasi sewa tidak valid. Gagal booking.\n";
            return;
        }

        enqueue(booking);
    }
}

void printNextBill() {
    if (isEmpty()) {
        cout << "[!] Tidak ada booking dalam antrian.\n";
        return;
    }

    Booking b = queue.data[queue.depan];
    dequeue();

    double total = b.carInfo.pricePerDay * b.rentalDays;

    cout << "\n======= BOOKING INVOICE =======\n"
         << "Customer: " << b.userInfo.nama << "\n"
         << "Email   : " << b.userInfo.ema << "\n"
         << "Alamat  : " << b.userInfo.alamat << "\n"
         << "Car     : " << b.carInfo.name << " (" << b.carInfo.model << ")\n"
         << "Days    : " << b.rentalDays << "\n"
         << "Rate    : Rp." << b.carInfo.pricePerDay << "/day\n"
         << "-------------------------------\n"
         << "TOTAL   : Rp." << total << "\n"
         << "===============================\n";
}

void hapusKendaraan() {
    int pilihan;
    cout << "Pilih jenis kendaraan yang ingin dihapus:\n1. Mobil\n2. Motor\nPilihan: ";
    cin >> pilihan;
    cin.ignore();

    string nama;
    cout << "Masukkan nama kendaraan yang ingin dihapus: ";
    getline(cin, nama);

    if (pilihan == 1) {
        Mobil* current = headMobil;
        Mobil* prev = nullptr;

        while (current != nullptr && current->name != nama) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "[!] Mobil tidak ditemukan.\n";
            return;
        }

        if (prev == nullptr) {
            headMobil = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        cout << "[+] Mobil berhasil dihapus.\n";
    }
    else if (pilihan == 2) {
        Motor* current = headMotor;
        Motor* prev = nullptr;

        while (current != nullptr && current->name != nama) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "[!] Motor tidak ditemukan.\n";
            return;
        }

        if (prev == nullptr) {
            headMotor = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        cout << "[+] Motor berhasil dihapus.\n";
    } else {
        cout << "[!] Pilihan tidak valid.\n";
    }
}

void menuAdmin() {
    int menuAdmin;
    char kembali;

    do {
        cout << "\n=== MENU ADMIN ===\n";
        cout << "1. Tampilkan Semua Kendaraan\n";
        cout << "2. Manage Kendaraan\n";
        cout << "3. Lihat Antrian Booking\n";
        cout << "4. cetak pesanan\n";
        cout << "5. Logout\n";
        cout << "Masukkan pilihan: ";
        cin >> menuAdmin;
        cin.ignore();

        switch (menuAdmin) {
            case 1:
                displayAllVehicles(); 
                break;
            case 2:
                char pilihanmage;
                cout << "1. Tambah kendaraan\n";
                cout << "2. hapus kendaraan \n";
                cout << "Masukkan pilihan: ";
                cin >> pilihanmage;

                if (pilihanmage == '1') {
                    addVehicle();
                } else if (pilihanmage == '2') {
                    hapusKendaraan();
                } else {
                    cout << "Pilihan tidak valid." << endl;
                    }
                break;
            case 3:
                void printQueue();
                break;
            case 4:
                printNextBill(); 
                break;
            case 5:
                cout << "Logout admin berhasil.\n"; return;
            default:
                cout << "Pilihan tidak valid.\n";
        }

        cout << "Kembali ke menu admin? (y/n): ";
        cin >> kembali;
        cin.ignore();
    } while (kembali == 'y' || kembali == 'Y');
}

void printSelectedBill(int userIndex) {
    if (isEmpty()) {
        cout << "\n[!] Tidak ada booking dalam antrian.\n";
        return;
    }

    Booking userBookings[MAX_QUEUE]; // Temp array untuk booking user
    int count = 0;

    // Menyalin booking milik user dari queue.data
    for (int i = queue.depan; i <= queue.belakang; ++i) {
        if (queue.data[i].userInfo.ema == users[userIndex].ema) {
            userBookings[count++] = queue.data[i];
        }
    }

    if (count == 0) {
        cout << "[!] Anda belum memiliki booking.\n";
        return;
    }

    // Tampilkan daftar booking user
    cout << "\n======= DAFTAR BOOKING ANDA =======\n";
    for (int i = 0; i < count; ++i) {
        cout << (i + 1) << ". " << userBookings[i].carInfo.name << " - " << userBookings[i].carInfo.model << endl;
    }

    // Pilih salah satu booking
    int pilihan;
    cout << "Masukkan nomor booking yang ingin ditampilkan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan < 1 || pilihan > count) {
        cout << "[!] Nomor tidak valid.\n";
        return;
    }

    Booking b = userBookings[pilihan - 1];
    double total = b.carInfo.pricePerDay * b.rentalDays;

    // Cetak struk
    cout << "\n======= DETAIL BOOKING =======\n"
         << "Customer: " << b.userInfo.nama << "\n"
         << "Email   : " << b.userInfo.ema << "\n"
         << "Alamat  : " << b.userInfo.alamat << "\n"
         << "Kendaraan: " << b.carInfo.name << " (" << b.carInfo.model << ")\n"
         << "Hari    : " << b.rentalDays << "\n"
         << "Harga   : Rp." << b.carInfo.pricePerDay << "/day\n"
         << "-------------------------------\n"
         << "TOTAL   : Rp." << total << "\n"
         << "===============================\n";
}



void inisialisasi() {
    queue.depan = queue.belakang = -1;
}

bool isEmpty() {
    return queue.belakang == -1;
}

bool isFull() {
    return queue.belakang >= MAX_QUEUE - 1;
}

void enqueue(Booking data) {
    if (isFull()) {
        cout << "[!] Antrian penuh.\n";
        return;
    }
    if (isEmpty()) queue.depan = 0;
    queue.belakang++;
    queue.data[queue.belakang] = data;
    cout << "[+] Booking berhasil dimasukkan ke antrian.\n";
}

void dequeue() {
    if (isEmpty()) {
        cout << "[!] Antrian kosong.\n";
        return;
    }
    cout << "[+] Booking untuk " << queue.data[queue.depan].userInfo.nama << " telah diproses dan dihapus.\n";
    for (int i = queue.depan; i < queue.belakang; i++) {
        queue.data[i] = queue.data[i + 1];
    }
    queue.belakang--;
    if (queue.belakang < queue.depan) queue.depan = queue.belakang = -1;
}

void clear() {
    queue.depan = queue.belakang = -1;
    cout << "[+] Antrian telah dikosongkan.\n";
}

void printQueue() {
    if (isEmpty()) {
        cout << "\n[!] Antrian kosong.\n";
        return;
    }

    cout << "\n======= CURRENT BOOKING QUEUE =======\n";
    cout << "No. | Customer Name       | Vehicle          | Days | Total Price\n";
    cout << "----+---------------------+------------------+------+-------------\n";

    for (int i = queue.depan; i <= queue.belakang; ++i) {
        Booking b = queue.data[i];
        double total = b.carInfo.pricePerDay * b.rentalDays;

        cout << setw(3) << (i - queue.depan + 1) << " | ";
        cout << setw(19) << left << b.userInfo.nama << " | ";
        cout << setw(16) << left << b.carInfo.name << " | ";
        cout << setw(4) << b.rentalDays << " | ";
        cout << "Rp." << fixed << setprecision(0) << total << endl;
    }

    cout << "=====================================\n";
    cout << "Total bookings in queue: " << (queue.belakang - queue.depan + 1) << endl;
}
