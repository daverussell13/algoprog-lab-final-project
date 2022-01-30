/**
 * KELOMPOK 1 :
 * - Dave Russell - 2501973400
 * - Richard Senjaya Johan - 2501964245
 * - Hansen Faldores - 2501965430
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Macro
#define STR_MAX 50
#define ull unsigned long long

// crossplatform clearscreen
#if defined (_WIN32) || defined (_WIN64)
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct {
  char nama[STR_MAX];
  char password[STR_MAX];
  char contact[STR_MAX];
  char time[STR_MAX];
  ull balance;
} User;

// Global variable
User currUser;

// Prototype
void clearBuff();
void enterToContinue();
void getTime(char*);
int isUniqueName(const char*);
void pushNewRecord(User);
void regist();
void login();
void mainMenu();
void atmMenu();
int accountValidation(const char*);
int nameValidation(const char*);
int passwordValidation(const char*);
void menu_deposito();
void deposit();
void menu();
void withdrawal();
void deleteAccount();

/**
 * Description : Dynamic array untuk menyimpan user sementara
 * Author : Dave russell - 2501973400
 */
typedef struct {
  User *array;
  int used;
  int size;
} Array;

/**
 * Input : Array* a(parameter), integer initialSize(parameter)
 * Description : inisialisasi array pertama dengan jumlah tertentu
 * Author : Dave russell - 2501973400
 */
void initArray(Array *a, int initialSize) {
  a->array = (User*)malloc(initialSize * sizeof(User));
  a->used = 0;
  a->size = initialSize;
}

/**
 * Input : Array* a(parameter), User newUser(parameter)
 * Description : memasukan data user ke dalam array
 * Author : Dave russell - 2501973400
 */
void insertArray(Array *a, User newUser) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (User*)realloc(a->array, a->size * sizeof(User));
  }
  a->array[a->used++] = newUser;
}

/**
 * Input : Array* a(parameter)
 * Description : membebaskan memory array (menghapus alokasi memory array)
 * Author : Dave russell - 2501973400
 */
void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

/**
 * Description : membersihkan char yang tertinggal di buffer
 * Author : Dave russell - 2501973400
 */
void clearBuff() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF) {};
}

/**
 * Description : membekukan prompt agar user dapat melihat pesan
 * Author : Dave russell - 2501973400
 */
void enterToContinue() {
  printf("Tekan enter untuk melanjutkan..");
  clearBuff();
}

/**
 * Input : String filename(parameter)
 * Description : jika file yang di cek tidak ada maka akan membuat file tersebut
 * Author : Dave russell - 2501973400
 */
void checkFile(const char* filename) {
  FILE* fp = fopen(filename,"rb");
  if (fp == NULL) {
    fp = fopen(filename,"wb");
    if (fp == NULL) {
      printf("Gagal membuat file...");
      exit(1);
    }
  }
  fclose(fp);
}

/**
 * Description : mendapatkan current time dengan format ww Mmm dd hh:mm:ss yyyy
 * Author : Dave russell - 2501973400
 */
void getTime(char* charArgs) {
  time_t currentTime = time(NULL);
  strcpy(charArgs,ctime(&currentTime));
}

/**
 * Input : String nama(parameter)
 * Ouput : integer
 * Description : mengembalikan 1 jika argumen nama yang dikirim tidak ada dalam file,
 *               dan mengembalikan 0 untuk sebaliknya
 * Author : Dave russell - 2501973400
 */
int isUniqueName(const char* nama) {
  checkFile("database.bin");
  FILE* fp = fopen("database.bin","rb");
  User temp;
  while (fread(&temp,sizeof(User),1,fp)) {
    if (!strcmp(nama,temp.nama)) {
      return 0;
    }
  }
  return 1;
}

/**
 * Input : User newUser(parameter)
 * Description : menulis user baru pada file
 * Author : Dave russell - 2501973400
 */
void pushNewRecord(User newUser) {
  checkFile("database.bin");
  FILE* fp = fopen("database.bin","ab");
  fwrite(&newUser,sizeof(User),1,fp);
  fclose(fp);
}

/**
 * Input : String nama(parameter)
 * Ouput : Integer
 * Description : mengembalikan 1 jika nama unik, tidak lebih dari 20 karakter,
 *               dan tidak kosong, mengembalikan 0 untuk sebaliknya
 * Author : Dave russell - 2501973400
 */
int nameValidation(const char* nama) {
  if (!isUniqueName(nama)) {
    puts("Nama telah digunakan!!!");
    enterToContinue();
    return 0;
  }
  else if (strlen(nama) > 20) {
    puts("Nama tidak boleh lebih dari 20 karakter!!!");
    enterToContinue();
    return 0;
  }
  else if (strlen(nama) == 0) {
    puts("Nama tidak boleh kosong!!!");
    enterToContinue();
    return 0;
  }
  return 1;
}

/**
 * Input : String pass(parameter)
 * Output : integer
 * Description : mengembalikan nilai 1 jika password memilki panjang 5 - 20 karakter, dan 0 untuk sebaliknya
 * Author : Dave russell - 2501973400
 */
int passwordValidation(const char* pass) {
  if (strlen(pass) < 5 || strlen(pass) > 20) {
    puts("Password minimal memiliki 5 karakter dan maksimal 20 karakter");
    enterToContinue();
    return 0;
  }
  return 1;
}

/**
 * Input : String nama(stdin), String password(stdin), String contact(stdin)
 * Description : registrasi user baru
 * Author : Dave russell - 2501973400
 */
void regist() {
  User newUser;
  // memastikan nama, password, contact kosong (terkadang berisi random value)
  strcpy(newUser.nama,"\0");
  strcpy(newUser.password,"\0");
  strcpy(newUser.contact,"\0");

  int valid = 0;
  while (!valid) {
    system(CLEAR);
    puts("Register");
    puts("============");
    printf("Masukan nama anda : ");
    scanf("%[^\n]",newUser.nama);
    clearBuff();
    valid = nameValidation(newUser.nama);
  }

  valid = 0;
  while (!valid) {
    printf("Masukan password : ");
    scanf("%[^\n]",newUser.password);
    clearBuff();
    valid = passwordValidation(newUser.password);
  }

  puts("User berhasil dibuat..");
  enterToContinue();

  system(CLEAR);
  puts("Register");
  puts("============");

  printf("Masukan nomor telephone anda : ");
  scanf("%s",newUser.contact);
  clearBuff();

  getTime(newUser.time);
  newUser.balance = 0;
  pushNewRecord(newUser);

  puts("Akun anda telah terdaftar..");
  enterToContinue();
}

/**
 * Input : String nama(parameter), String password(stdin)
 * Ouput : Integer
 * Description : mengembalikan 0 jika nama user belum didaftarkan,
 *               mengembalikan 1 jika nama password yang diberikan salah,
 *               mengembalikan 2 jika data login user valid
 * Author : Dave russell - 2501973400
 */
int accountValidation(const char* nama) {
  checkFile("database.bin");
  FILE* fp = fopen("database.bin","rb");
  User temp;
  while (fread(&temp,sizeof(User),1,fp)) {
    if (!strcmp(temp.nama,nama)) {
      char password[STR_MAX];
      printf("Masukan password anda : ");
      scanf("%[^\n]",password);
      clearBuff();
      if (!strcmp(temp.password,password)) {
        currUser = temp;
        return 2;
      }
      return 1;
    }
  }
  return 0;
  fclose(fp);
}

/**
 * Input : String nama(stdin)
 * Description : login kedalam akun
 * Author : Dave russell - 2501973400
 */
void login() {
  system(CLEAR);
  puts("Login");
  puts("============");

  char nama[STR_MAX];
  printf("Masukan nama anda : ");
  scanf("%[^\n]",nama);
  clearBuff();

  switch (accountValidation(nama)) {
    case 0:
      puts("Nama yang anda masukan tidak terdaftar");
      enterToContinue();
      break;
    case 1:
      puts("Password yang anda masukan salah");
      enterToContinue();
      break;
    case 2:
      atmMenu();
      break;
  }
}

/**
 * Input : String nama(parameter)
 * Output : Display User (nama), User (balance)
 * Description : Fungsi ini akan melihat satu - persatu nama yang ada difile dengan nama yang diinginkan.
 *               Hasil dari fungsi ini berupa data nama dan total uang yang telah didepositkan.
 * Author : Richard Senjaya Johan - 2501964245
 */
void showMoney(const char* name) {
  FILE* fp = fopen("database.bin","rb");
  User u;
  while (fread(&u,sizeof(User),1,fp)) {
    if (!strcmp(name,u.nama)) {
      printf("Nama : %s\nBalance : %llu\n",u.nama,u.balance);
    }
  }
  fclose(fp);
}

/**
 * Description : Pilihan ATM menu prompt
 * Author : Richard Senjaya Johan - 2501964245
 */
void menu() {
	puts("ATM");
  puts("=========================");
	puts("1. Deposit");
	puts("2. Withdrawal");
	puts("3. Check Saldo");
	puts("4. Delete account");
  puts("5. Kembali ke menu utama");
  puts("=========================");
  printf("Masukan pilihan anda : ");
}

/**
 * Input : ull value(parameter)
 * Description : Validasi ketika value lebih kecil dari 100rb akan keluar pesan ,jika tidak akan dilanjutkan prosesnya
 * Author : Richard Senjaya Johan - 2501964245
 */
int depositValidation(ull value) {
  if (value < 100000) {
		puts("Maaf, deposito yang anda berikan tidak memenuhi persyaratan minimum");
    enterToContinue();
    return 0;
  }
  return 1;
}

/**
 * Input : String nama(parameter), ull value(parameter)
 * Description : Untuk mengecek apakah nama user yang ditambahkan jumlah depositnya benar apa tidak dan mengupdate total uang yang telah didepositkan ke dalam file
 * Author : Richard Senjaya Johan - 2501964245
 */
void addBalance(const char* nama, ull value) {
  FILE* fp = fopen("database.bin","rb+");
  User u;
  while (fread(&u,sizeof(User),1,fp)) {
    if (!strcmp(nama,u.nama)) {
      u.balance += value;
      fseek(fp,-sizeof(u),SEEK_CUR);
      fwrite(&u,sizeof(u),1,fp);
      break;
    }
  }
  fclose(fp);
}

/**
 * Input : ull value
 * Description : Untuk menambahkan jumlah deposito ke user yang bersangkutan
 * Author : Richard Senjaya Johan - 2501964245
 */
void deposit() {
  int valid = 0;
  ull value;
  while (!valid) {
    system(CLEAR);
    printf("Masukan jumlah uang : ");
    scanf("%llu",&value);
    clearBuff();
    valid = depositValidation(value);
  }
  addBalance(currUser.nama,value);
  currUser.balance += value;
}

/**
 * Description : Untuk memanggil function yang diperlukan dalam mengupdate total uang deposito
 * Author : Richard Senjaya Johan - 2501964245
 */
void menu_deposito(){
  system(CLEAR);
  printf("Check Saldo\n");
  showMoney(currUser.nama);
  enterToContinue();
}

/**
 * Input : User currentUser(parameter)
 * Output : return 1 jika nama dan password currentUser kosong, return 0 jika tidak
 * Description : mengecek apakah currentUser kosong atau tidak
 * Author : Dave Russell - 2501973400
 */
int isEmptyData(User currentUser) {
  return (!strlen(currentUser.nama) && !strlen(currentUser.password));
}

/**
 * Output : Menu ATM (stdout)
 * Description : Menu ATM
 * Author : Richard Senjaya Johan - 2501964245
 */
void atmMenu() {
  while (!isEmptyData(currUser)) {
    system(CLEAR);
    int option = 0;
    menu();
    scanf("%d",&option);
    clearBuff();
    switch (option) {
      case 1:
        deposit();
        break;
      case 2:
      	withdrawal();
        break;
      case 3:
      	menu_deposito();
        break;
      case 4:
        deleteAccount();
        break;
      case 5:
        strcpy(currUser.nama,"\0");
        strcpy(currUser.password,"\0");
        break;
      default:
    	  break;
      }
  }
}

/**
 * input: ull uang(parameter)
 * Description : validasi ketika uang lebih besar dari 5juta maka akan mengeluarkan pesan, jika tidak maka prosesnya akan berlanjut
 * Author : Hansen Faldores - 2501965430
*/
int withdrawalValidation(ull uang){
  if (uang > 5000000){
    puts("Mohon Maaf, withdrawal yang anda berikan telah melewati persyaratan maksimum");
    enterToContinue();
    return 0;
  }
  else if (currUser.balance < uang) {
    puts("Mohon Maaf, saldo anda tidak mencukupi...");
    enterToContinue();
    return 0;
  }
	return 1;
}

/**
 * input: string nama(parameter), ull uang(parameter)
 * Description : untuk mengecek apakah nama user yang dikurangkan jumlah withdraw benar apa tidak dan mengupdate total uang yang telah diwithdrawalkan ke dalam file
 * Author: Hansen Faldores - 2501965430
*/
void cutBalance(const char* nama,ull uang){
	FILE* fp = fopen("database.bin","rb+");
	User u;
	while(fread(&u,sizeof(User),1,fp)){
		 if (!strcmp(nama,u.nama)) {
      u.balance-=uang;
      fseek(fp,-sizeof(u),SEEK_CUR);
      fwrite(&u,sizeof(u),1,fp);
      break;
    }
  }
  fclose(fp);
}

/**
 * Input: int pilihan, ull uang
 * Description: untuk mengurangi jumlah deposito ke user yang berkaitan dan menu penarikan saldo
 * Author: Hansen Faldores - 2501965430
*/
void withdrawal(){
	ull uang;
	ull total = 0;
	int pilihan;
	int validasi=0;
	while(!validasi){
    system(CLEAR);
    printf("Menu Penarikan Saldo Deposit\n");
    printf("===========================\n");
		printf("1. 100.000\n");
		printf("2. 200.000\n");
		printf("3. 300.000\n");
		printf("4. 500.000\n");
		printf("5. 1.000.000\n");
		printf("6. 1.500.00\n");
		printf("7. 2.000.000\n");
		printf("8. Transaksi lain\n");
		printf("===========================\n");
		printf("Masukkan nomor yang adan inginkan : ");
		scanf("%d",&pilihan);
    clearBuff();

    switch(pilihan){
      case 1:
        uang=100000;
        break;
      case 2:
        uang=200000;
        break;
      case 3:
        uang=300000;
        break;
      case 4:
        uang=500000;
        break;
      case 5:
        uang=1000000;
        break;
      case 6:
        uang=1500000;
        break;
      case 7:
        uang=2000000;
        break;
      case 8:
        printf("Masukan nominal yang akan diambil : \n");
        scanf("%llu",&uang);
        clearBuff();
        break;
      default:
        printf("Mohon maaf, Input yang diberikan salah\n");
        break;
    }
    validasi = withdrawalValidation(uang);
	}
  cutBalance(currUser.nama,uang);
  currUser.balance -= uang;
}

/**
 * Output : Detail akun (stdout)
 * Description : menampilkan detail dari akun yang telah login
 * Author : Dave Russell - 2501973400
 */
void accountDetail() {
  puts("Account Detail");
  puts("===================");
  printf("Nama         : %s\n",currUser.nama);
  printf("Contact      : %s\n",currUser.contact);
  printf("Date created : %s",currUser.time);
  printf("Balance      : %llu\n",currUser.balance);
  puts("===================");
}

/**
 * Input : String nama (parameter)
 * Description : menghapus record yang berdasarkan nama
 * Author : Dave Russell - 2501973400
 */
void deleteRecords(const char* nama) {
  checkFile("database.bin");
  FILE* dataStream = fopen("database.bin","rb");
  User u;
  Array temp;
  initArray(&temp,10);
  while (fread(&u,sizeof(u),1,dataStream)) {
    if (!strcmp(nama,u.nama)) continue;
    insertArray(&temp,u);
  }
  fclose(dataStream);
  FILE* fp = fopen("database.bin","wb");
  if (fp == NULL) {
    printf("Gagal menghapus data...");
    enterToContinue();
    return;
  }
  for (int i = 0; i < temp.used; i++) {
    fwrite(&(temp.array[i]),sizeof(User),1,fp);
  }
  fclose(fp);
  freeArray(&temp);
}

/**
 * Input : String nama (parameter)
 * Description : Menghapus record akun dari file database.bin
 * Author : Dave Russell - 2501973400
 */
void deleteAccount() {
  int valid = 0;
  char input[STR_MAX] = "\0";
  while (!valid) {
    system(CLEAR);
    accountDetail();
    printf("Apakah anda yakin ingin menghapus akun ini ? [y/n] : ");
    scanf("%s",input);
    clearBuff();
    valid = (!strcmp(input,"y") || !strcmp(input,"n"));
  }
  if (!strcmp(input,"y")) {
    puts("PERINGATAN!!! Semua data dalam akun ini akan hilang");
    printf("Apakah anda yakin ingin melanjutkan proses penghapusan akun ? [y/n] : ");
    scanf("%s",input);
    clearBuff();
    if (!strcmp(input,"y")) {
      deleteRecords(currUser.nama);
      strcpy(currUser.nama,"\0");
      strcpy(currUser.password,"\0");
    }
  }
}

/**
 * Output : Main menu display (stdout)
 * Description : main menu prompt
 * Author : Dave Russell - 2501973400
 */
void mainMenu() {
  puts("Main menu :");
  puts("============");
  puts("1. Login");
  puts("2. Register");
  puts("3. Exit");
  puts("============");
  printf("Masukan pilihan anda : ");
}

/**
 * Output : Menu utama (stdout)
 * Description: tampilan menu utama
 * Author: Dave Russell - 2501973400
*/
int main() {
  int exit = 0;
  while (!exit) {
    system(CLEAR);
    mainMenu();
    int option;
    scanf("%d",&option);
    clearBuff();
    switch (option) {
      case 1:
        login();
        break;
      case 2:
        regist();
        break;
      case 3:
        exit = 1;
        break;
      default:
        puts("Input tidak valid!!!");
        enterToContinue();
        break;
    }
  }
  return 0;
}
