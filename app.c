#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Macro
#define STR_MAX 50
#define ull unsigned long long

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
void clearScreen();
void enterToContinue();
void getTime(char*);
int isUniqueName(const char*);
void pushNewRecord(User);
void regist();
void login();
void mainMenu();

/**
 * Description : membersihkan char yang tertinggal di buffer
 * Author : Dave russell - 2501973400
 */
void clearBuff() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF) {};
}

/**
 * Description : membersihkan prompt dengan regex
 * Author : Dave russell - 2501973400
 */
void clearScreen() {
  printf("\e[1;1H\e[2J");
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
 * Input : String nama(stdin), String password(stdin), String contact(stdin)
 * Description : melakukan registrasi
 * Author : Dave russell - 2501973400
 */
void regist() {
  User newUser;
  int valid = 0;
  while (!valid) {
    clearScreen();
    puts("Register");
    puts("============");

    printf("Masukan nama anda : ");
    scanf("%s",newUser.nama);
    clearBuff();

    printf("Masukan password anda : ");
    scanf("%s",newUser.password);
    clearBuff();

    valid = isUniqueName(newUser.nama);
    if (!valid) {
      puts("Nama telah digunakan...");
      enterToContinue();
    }
  }

  puts("User berhasil dibuat..");
  enterToContinue();

  clearScreen();
  puts("Register");
  puts("============");
  printf("Masukan nomor telephone anda : ");
  scanf("%s",newUser.contact);
  clearBuff();
  getTime(newUser.time);

  pushNewRecord(newUser);
}

int accountVerification(const char* nama) {
  checkFile("database.bin");
  FILE* fp = fopen("database.bin","rb");
  User temp;
  while (fread(&temp,sizeof(User),1,fp)) {
    if (!strcmp(temp.nama,nama)) {
      char password[STR_MAX];
      printf("Masukan password anda : ");
      scanf("%s",password);
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

void login() {
  puts("Login");
  puts("============");

  char nama[STR_MAX];
  printf("Masukan nama anda : ");
  scanf("%s",nama);
  clearBuff();

  switch (accountVerification(nama)) {
    case 0:
      puts("Nama yang anda masukan tidak terdaftar");
      break;
    case 1:
      puts("Password yang anda masukan salah");
      break;
    case 2:
      puts("Berhasil login!!!");
      break;
  }
  enterToContinue();
}

/**
 * Description : main menu prompt
 * Author :
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

int main() {
  int exit = 0;
  while (!exit) {
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
        puts("Invalid input");
        break;
    }
  }
  return 0;
}