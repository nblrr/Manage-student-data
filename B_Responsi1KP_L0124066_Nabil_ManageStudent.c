// Nama : Nabil Rizki Wardana
// NIM  : L0124066

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

// Struktur data untuk menyimpan data mahasiswa
typedef struct
{
    char fname[50];
    char lname[50];
    float ipk;
    int nim;
} student;

// Function ini berfungsi untuk clear screen
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function untuk memuat data dari file student.txt
void load(student *st, int *i)
{
    // Membuka file student.txt
    FILE *file = fopen("student.txt", "r");
    // Jika file tidak ditemukan maka akan menampilkan pesan error
    if (file == NULL)
    {
        printf("ERROR!! NO DATA AVAILABLE!!!\n");
        return;
    }

    int j = 0;
    // Membaca data dari file student.txt
    while (fscanf(file, "%s %s %f %d", st[j].fname, st[j].lname, &st[j].ipk, &st[j].nim) == 4)
    {
        j++;
    }

    *i = j;
    fclose(file);
}

// Function untuk menyimpan data ke dalam file student.txt
void save(student *st, int *i)
{
    // Membuka file student.txt dan menulis data
    FILE *file = fopen("student.txt", "w");
    for (int j = 0; j < *i; j++)
    {
        // Menulis data ke dalam file student.txt
        fprintf(file, "%s %s %.2f %d\n", st[j].fname, st[j].lname, st[j].ipk, st[j].nim);
    }
    fclose(file);
}

// Function untuk menambahkan data mahasiswa
void add(student *st, int *i)
{
    printf("Add the Students Details\n");
    printf("-------------------------\n");
    printf("Enter the first name of student\n");
    // Mengambil input dari user untuk first name
    scanf("%s", st[*i].fname);
    // Loop yang digunakan untuk mengubah semua huruf menjadi kapital
    for (int j = 0; j < strlen(st[*i].fname); j++)
    {
        st[*i].fname[j] = toupper(st[*i].fname[j]);
    }

    printf("Enter the last name of student\n");
    // Mengambil input dari user untuk last name
    scanf("%s", st[*i].lname);
    // Loop yang digunakan untuk mengubah semua huruf menjadi kapital
    for (int j = 0; j < strlen(st[*i].lname); j++)
    {
        st[*i].lname[j] = toupper(st[*i].lname[j]);
    }

    printf("Enter your NIM Number (only the last 3 digits)\n");
    // Mengambil input dari user untuk NIM
    scanf("%d", &st[*i].nim);
    printf("Enter the IPK you obtained (Example : 3.50)\n");
    // Mengambil input dari user untuk IPK
    scanf("%f", &st[*i].ipk);

    // Looping yang digunakan untuk memeriksa apakah NIM sudah ada di database
    for (int j = 0; j < *i; j++)
    {
        // Mengecek kondisi jika nim yang dimasukkan sudah ada atau belum
        if (st[j].nim == st[*i].nim)
        {
            printf("Data sudah ada di database\n");
            return;
        }
    }
    // Menambah iterasi total student
    (*i)++;
    // Menyimpan data ke dalam file
    save(st, i);
}

// Function untuk mengupdate data mahasiswa
void update_st(student *st, int *i)
{
    printf("Enter NIM that you want to update the entry : ");
    long int x;
    // Mengambil input dari user
    scanf("%ld", &x);

    // Looping yang akan berjalan sampai nilai i tercapai
    for (int j = 0; j < *i; j++)
    {
        // Mengecek apakah NIM yang dimasukkan sama dengan NIM pada database
        if (st[j].nim == x)
        {
            printf("1. first name\n"
                   "2. last name\n"
                   "3. NIM\n"
                   "4. IPK\n");
            int z;
            // Mengambil input dari user
            scanf("%d", &z);
            // Switch case untuk memilih data yang ingin diupdate
            switch (z)
            {
            // Case jika data yang ingin diupdate adalah first name
            case 1:
                printf("Enter the new first name : \n");
                // Mengambil input dari user
                scanf("%s", st[j].fname);
                // Looping yang digunakan untuk mengubah semua huruf menjadi kapital
                for (int k = 0; k < strlen(st[j].fname); k++)
                {
                    st[j].fname[k] = toupper(st[j].fname[k]);
                }
                break;

            // Case jika data yang ingin diupdate adalah last name
            case 2:
                printf("Enter the new last name : \n");
                // Mengambil input dari user
                scanf("%s", st[j].lname);
                // Looping yang digunakan untuk mengubah semua huruf menjadi kapital
                for (int k = 0; k < strlen(st[j].lname); k++)
                {
                    st[j].lname[k] = toupper(st[j].lname[k]);
                }
                break;

            // Case jika data yang ingin diupdate adalah NIM
            case 3:
                printf("Enter the new NIM : \n");
                // Mengambil input dari user
                scanf("%d", &st[j].nim);
                break;

            // Case jika data yang ingin diupdate adalah IPK
            case 4:
                printf("Enter the new IPK : \n");
                // Mengambil input dari user
                scanf("%f", &st[j].ipk);
                break;
            }
            // Menyimpan data ke dalam file student.txt
            save(st, i);
            printf("UPDATED SUCCESSFULLY.\n");
        }
    }
}

// Function untuk menghapus data mahasiswa
void delete_st(student *st, int *i)
{
    int a;
    printf("Enter the NIM which you want to delete\n");
    // Mengambil input dari user
    scanf("%d", &a);
    // Looping untuk mencari data yang ingin dihapus
    for (int j = 0; j < *i; j++)
    {
        // Mengecek apakah NIM ada pada file student.txt
        if (a == st[j].nim)
        {
            for (int k = j; k < *i - 1; k++)
            {
                st[k] = st[k + 1];
            }
            // Mengurangi iterasi total mahasiswa
            (*i)--;
            // Menyimpan data ke dalam file
            save(st, i);
            printf("NIM %d is removed Successfully\n", a);
            return;
        }
    }
    printf("Not found\n");
}

// Function untuk mencari data mahasiswa berdasarkan NIM
void find_nim(student *st, int i)
{
    int x;
    printf("Enter the NIM Number of the student (Only the last 3 digits)\n");
    // Mengambil input dari user
    scanf("%d", &x);
    // Looping untuk mencari data berdasarkan NIM
    for (int j = 0; j < i; j++)
    {
        // Mengecek apakah NIM ada pada file student.txt
        if (x == st[j].nim)
        {
            printf("\n");
            printf("------Students Details------\n");
            // Menampilkan data nama dan IPK
            printf("This student name is %s %s\n", st[j].fname, st[j].lname);
            printf("The IPK is %.2f\n", st[j].ipk);
            return;
        }
    }
    printf("This NIM Number is not found\n");
}

// Function untuk mencari data mahasiswa berdasarkan nama depan
void find_name(student *st, int i)
{
    char a[50];
    printf("Enter the First Name of the student\n");
    // Mengambil input dari user
    scanf("%s", a);
    // Looping yang digunakan untuk mengubah input user menjadi kapital
    for (int j = 0; j < strlen(a); j++)
    {
        a[j] = toupper(a[j]);
    }

    int c = 0;
    for (int j = 0; j < i; j++)
    {
        // Mengecek apakah nama depan ada pada file student.txt
        if (!strcmp(st[j].fname, a))
        {
            printf("\n");
            printf("------Students Details------\n");
            // Menampilkan data Nama, NIM, dan IPK
            printf("The First name is %s\n", st[j].fname);
            printf("The Last name is %s\n", st[j].lname);
            printf("The NIM is %d\n", st[j].nim);
            printf("The IPK is %.2f\n", st[j].ipk);
            c = 1;
        }
    }

    // Jika nama depan tidak ditemukan
    if (!c)
    {
        printf("This Name is Not Found in the Database\n");
    }
}

void printName(student *st, int i)
{
    if (i > 0)
    {
        printf("Nama Mahasiswa: %s %s\n", st[i - 1].fname, st[i - 1].lname);
        printName(st, i - 1);
    }
}

// Function untuk menampilkan jumlah total mahasiswa
void total(student *st, int i)
{
    int total = 0;
    for (int j = 0; j < i; j++)
    {
        total++;
    }
    printf("Total Students: %d\n", i);
    printName(st, i);
}

// Fungsi main program
int main()
{
    // Array untuk menyimpan data mahasiswa
    student st[100];
    int i = 0;
    // Memanggil function load
    load(st, &i);
    int pilihan;
    do
    {
        printf("Hello!! what do you want to do?\n");
        printf("1. Add Student\n");
        printf("2. Removed Student\n");
        printf("3. Find Total Students\n");
        printf("4. Find Student by Name\n");
        printf("5. Find Student by NIM\n");
        printf("6. Update Student Data\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        // Mengambil input dari user
        scanf("%d", &pilihan);

        // Switch case berdasarkan input user
        switch (pilihan)
        {
        case 1:
            // Memanggil function add
            add(st, &i);
            // Layar akan menunggu selama 1 detik
            Sleep(1000);
            // Memanggil function clearScreen
            clearScreen();
            // Keluar dari loop
            break;
        case 2:
            // Memanggil function delete_st
            delete_st(st, &i);
            // Layar akan menunggu selama 1 detik
            Sleep(1000);
            // Memanggil function clearScreen
            clearScreen();
            // Keluar dari loop
            break;
        case 3:
            // Memanggil function total
            total(st, i);
            // Layar akan menunggu selama 3 detik
            Sleep(5000);
            // Memanggil function clearScreen
            clearScreen();
            // Keluar dari loop
            break;
        case 4:
            // Memanggil function find_name
            find_name(st, i);
            // Layar akan menunggu selama 4 detik
            Sleep(4000);
            // Memanggil function clearScreen
            clearScreen();
            // Keluar dari loop
            break;
        case 5:
            // Memanggil function find_nim
            find_nim(st, i);
            // Layar akan menunggu selama 4 detik
            Sleep(4000);
            // Memanggil function clearScreen
            clearScreen();
            // Keluar dari loop
            break;
        case 6:
            // Memanggil function update_st
            update_st(st, &i);
            // Layar akan menunggu selama 2 detik
            Sleep(2000);
            // Memanggil function clearScreen
            clearScreen();
            // Keluar dari loop
            break;
        case 7:
            printf("Goodbye!\n");
            Sleep(500);
            clearScreen();
            // Keluar dari program
            exit(0);
            break;
            // Jika pilihan tidak sesuai dengan case yang ada
        default:
            printf("Invalid choice. Please try again.\n");
            Sleep(500);
            clearScreen();
        }
    }
    // Loop akan terus dijalankan selama input user tidak sama dengan 7
    while (pilihan != 7);
    return 0;
}