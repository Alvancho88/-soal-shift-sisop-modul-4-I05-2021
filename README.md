# soal-shift-sisop-modul-4-I05-2021

**Rafi Akbar Rafsanjani - 05111942000004**

**Agustinus Aldi Irawan Rahardja - 05111942000010**

**Muhammad Rafi Hayla Arifa - 05111942000014**

Repository for the solution to the module's question :coffee:

```
Notes:
● It is not allowed to use system () and exec * (), unless there are exceptions in the question.
● The work is only done in 1 C program file with the format name SinSeiFS_ [Group] .c.
```

**Built-in Library**
```
#define FUSE_USE_VERSION 28

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
```
**Global Initialization**
```
static const char *dirPath = "/home/alvancho/Downloads";
char *key = "SISOP";
char *atoz = "AtoZ_";
char *rx = "RX_";
char *aisa = "A_is_a_";
int x = 0;
```


# Question 1
In a department, there was a new lab admin who had nothing to do, his name was Sin.
Sin just became an admin exactly 1 month ago. After a month in that lab he finally met
great people, one of them was Sei. Sei and Sin became good friends. Because in the
past few months there was a lot of buzz about data breach, they decided to make a file
system with a robust encode method technique. The file system is as follows :

```
NOTE: 
Every file on the directory must be encoded using menggunakan Atbash cipher(mirror).

For example, for a file named kucinglucu123.jpg on DATA_PENTING directory
“AtoZ_folder/DATA_PENTING/kucinglucu123.jpg” → “AtoZ_folder/WZGZ_KVMGRMT/pfxrmtofxf123.jpg”

Note:
The file system works normally like any linux file system, Mount source (root) of the file system is on /home/[USER]/Downloads directory, when naming a file,  ‘/’ is ignored, and extension of a file doesn’t need to be encoded.

Reference:
https://www.dcode.fr/atbash-cipher
```

**a) If a directory starts with ```AtoZ_```, then that directory will be encoded.**

**b). If you rename a directory to have a prefix ```AtoZ_```, then the directory will be
encoded.**

**c) When encoded directory is renamed to not have encoded name, then the
directory will be decoded**

**d) For every encoding of a directory (mkdir or rename) will be recorded in a log file.
The format is : ```/home/[USER]/Downloads/[Directory Name] →
/home/[USER]/Downloads/AtoZ_[Directory Name]```**

**e) Encoding method is also applied to all other directories inside the encoded
directory.(rekursif)**

# Solution 1
Atbash Cipher is a substitution cipher named from the Hebraic alphabet that substitutes the first letter of the alphabet with the last one, the second letter with the second last one, and so on. Basically, when encoded, an ```A``` becomes a ```Z```, ```B``` turns into ```Y```, etc.

Note: The file system works normally like any linux file system, mount source (root) of the file system is on ```/home/[USER]/Downloads``` directory, when naming a file, ```/``` is ignored, and extension of a file doesn't need to be encoded.

For Example:

For a file named ```kucinglucu123.jpg``` on ```DATA_PENTING``` directory
```AtoZ_folder/DATA_PENTING/kucinglucu123.jpg``` → ```AtoZ_folder/WZGZ_KVMGRMT/pfxrmtofxf123.jpg```


Based on the question asked, we have to make a program where all the files in the created directory and/or renamed with the prefix ```AtoZ_```, then the directory and the entire contents of the directory will be encoded. If a directory is created and/or renamed with a prefix other than ```AtoZ_```, the directory and the entire contents of that directory will be decoded. If an encrypted directory is renamed to be unencoded, the contents of that directory will be decoded.

Based on this explanation. Then we can create some support functions to help us determine whether the directory is an encoded or decoded directory. These are the following support functions that we used:

**1) ```split_file_id_return```**

<img width="1000" alt="Screen Shot 2021-06-13 at 00 32 37" src="https://user-images.githubusercontent.com/74056954/121784571-dc0dc400-cbde-11eb-8fef-f4d13d20cdc2.png">

This ```split_file_id_return``` function is to return the index file extension to the file that has been split.

**2) ```file_extension_index_return```**

<img width="1000" alt="Screen Shot 2021-06-13 at 00 36 41" src="https://user-images.githubusercontent.com/74056954/121784675-6d7d3600-cbdf-11eb-8736-318412b4122e.png">

This ```file_extension_index_return``` function is to return the index file extension.

**3) ```slash_id_return```**

<img width="1000" alt="Screen Shot 2021-06-13 at 00 21 18" src="https://user-images.githubusercontent.com/74056954/121784339-b3d19580-cbdd-11eb-84ed-8b6b8ba226c4.png">

Last but not least is the ```slash_id_return``` function. The purpose of this function is to check whether the directory prefix contains ```AtoZ_``` or not. Because as we all know, directory names start after a slash. So by creating this function, we can start checking the prefix of the directory.

To perform the encryption and decryption process using the Atbash Cipher method we also need these 2 functions:

**1) ```encrypt_atbash_cipher_on_atoz```**

<img width="1000" alt="Screen Shot 2021-06-13 at 01 02 07" src="https://user-images.githubusercontent.com/74056954/121785259-fb0e5500-cbe2-11eb-9ff7-1c34b40572b5.png">

**2) ```decrypt_atbash_cipher_on_not_atoz```**

<img width="1000" alt="Screen Shot 2021-06-13 at 01 10 34" src="https://user-images.githubusercontent.com/74056954/121785482-29406480-cbe4-11eb-85d1-4bd5cfce43e0.png">


**Screenshots**

**a.)**

![Kondisi_1](https://user-images.githubusercontent.com/61174498/121777602-2bdb9380-cbbd-11eb-9f62-91b20dd9c523.png)

![Screenshot from 2021-06-12 14-55-44](https://user-images.githubusercontent.com/61174498/121777622-3d24a000-cbbd-11eb-8c52-4eaa736c1b02.png)

**b.)**

![Screenshot from 2021-06-12 14-57-44](https://user-images.githubusercontent.com/61174498/121777626-457cdb00-cbbd-11eb-891f-8a88826ed12a.png)

![Screenshot from 2021-06-12 14-57-52](https://user-images.githubusercontent.com/61174498/121777651-6a714e00-cbbd-11eb-85a5-25a53005b0fd.png)

![Screenshot from 2021-06-12 14-58-21](https://user-images.githubusercontent.com/61174498/121777655-70ffc580-cbbd-11eb-9287-920d4a561ce4.png)

**c.)**

![Screenshot from 2021-06-12 14-58-48](https://user-images.githubusercontent.com/61174498/121777666-7c52f100-cbbd-11eb-8d77-365e39111509.png)

![Screenshot from 2021-06-12 14-59-08](https://user-images.githubusercontent.com/61174498/121777667-82e16880-cbbd-11eb-8751-10b526e516ea.png)


**d.)**

![Screenshot from 2021-06-12 15-24-25](https://user-images.githubusercontent.com/61174498/121777714-b58b6100-cbbd-11eb-9a36-f7de1c2fc790.png)

**e.)**

![Screenshot from 2021-06-12 14-59-45](https://user-images.githubusercontent.com/61174498/121777687-942a7500-cbbd-11eb-91f6-78e85db42921.png)

# Question 2
Other than that, Sei proposed to create additional encryption methods to increase the
security of their computer data . The following is the additional encryption method
designed by Sei
a. If a directory is created starting with “RX_[Nama]”, then that directory and its
contents will be encoded with a rename according to problem 1 with an additional
ROT13 algorithm (Atbash + ROT13).
b. If a directory is renamed starting with “RX_[Nama]”, then that directory and its
contents will be encoded with a rename according to problem 1 with an additional
Vigenere Cipher algorithm with “SISOP” as it's key (Case-sensitive, Atbash +
Vigenere).
c. If an encoded directory is renamed (Removing the “RX_”), then that folder will
become unencoded and it's directory contents will be decoded based on it's real
name.
d. Every encoded directory created (mkdir or rename) will be noted to a log file with
it's methods (whether it's mkdir or rename).
e. For this encryption method, files in the original directory will be split into smaller,
1024 byte files. While if accessed via the file system designed by Sin and Sei,
files will become normal. Example, Suatu_File.txt sized 3 kiloBytes in its original
directory will become 3 smaller files::
Suatu_File.txt.0000
Suatu_File.txt.0001
Suatu_File.txt.0002
When accessed via the file system, file will appear as Suatu_File.txt
** **

**Screenshots**
**a.)**

![Screenshot from 2021-06-12 15-02-54](https://user-images.githubusercontent.com/61174498/121777923-ab1d9700-cbbe-11eb-8b5b-575562c607e4.png)

![Screenshot from 2021-06-12 15-03-03](https://user-images.githubusercontent.com/61174498/121777941-bd97d080-cbbe-11eb-999f-088b10197bcc.png)

**b.)**

![Screenshot from 2021-06-12 15-06-44](https://user-images.githubusercontent.com/61174498/121777944-c38db180-cbbe-11eb-8d23-37693f43483c.png)

![Screenshot from 2021-06-12 15-07-18](https://user-images.githubusercontent.com/61174498/121777948-d1433700-cbbe-11eb-889d-d9b1cd85f638.png)

**c.)**

![Screenshot from 2021-06-12 15-08-13](https://user-images.githubusercontent.com/61174498/121777973-f041c900-cbbe-11eb-87fd-0a67ffea7e24.png)

![Screenshot from 2021-06-12 15-08-18](https://user-images.githubusercontent.com/61174498/121777978-f5067d00-cbbe-11eb-8a8b-044a7b13e39e.png)

![Screenshot from 2021-06-12 15-08-42](https://user-images.githubusercontent.com/61174498/121777982-f89a0400-cbbe-11eb-9dcb-d73abad988e5.png)

**d.)**

![Screenshot from 2021-06-12 15-11-44](https://user-images.githubusercontent.com/61174498/121777987-fdf74e80-cbbe-11eb-9230-f7508e0a339f.png)

**e.)**

![Screenshot from 2021-06-12 15-07-18](https://user-images.githubusercontent.com/61174498/121777951-d7391800-cbbe-11eb-95c7-430786e329d8.png)

#Solution 2
**The ```RENAME``` utility checks whether the directory is renamed by adding ```RX_``` or removing ```RX_``` with the strstr() function.**
```
static int xmp_rename(const char *from, const char *to)
{
	int res;
	char frompath[1000], topath[1000];
	
	char *a = strstr(to, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(from, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(from, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}
	
	char *c = strstr(to, rx);
	if (c != NULL){
		//struct stat stats;
		//stat(from, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(c);
		decrypt_atbash_cipher_on_not_atoz(c);
		//else
		//decrypt_vigenere_on_not_rx_rename(c);
	}

	sprintf(frompath, "%s%s", directoryPath, from);
	sprintf(topath, "%s%s", directoryPath, to);

	res = rename(frompath, topath);
	if (res == -1) return -errno;

	writeLog2("RENAME", frompath, topath);
	
	if (c != NULL){
		encryption_utility_function(topath);
		writeLog2("ENCRYPT2", from, to);
	}

	if (b != NULL && c == NULL){
		decryption_utility_function(topath);
		writeLog2("DECRYPT2", from, to);
	}
	
	if (strstr(to, aisa) != NULL){
		encrypt_binary_from_difference(topath);
		writeLog2("ENCRYPT3", from, to);
	}
	
	if (strstr(from, aisa) != NULL && strstr(to, aisa) == NULL){
		decrypt_binary_to_normal_from_difference(topath);
		writeLog2("DECRYPT3", from, to);
	}

	return 0;
}
```

**If ```RX_``` is detected in the destination path, it means the directory is renamed by adding ```RX_``` and followed by cracking the file in the encryption function2.**
```
void encryption_utility_function(char *fpath)
{
	chdir(fpath);
	DIR *dp;
	struct dirent *dir;
	
	dp = opendir(".");
	if(dp == NULL) return;
	struct stat lol;
	char directoryPath[1000];
	char filePath[1000];
	
    while ((dir = readdir(dp)) != NULL){
		printf("dirname %s\n", dir->d_name);
		printf("%s/%s\n", fpath, dir->d_name);
		if (stat(dir->d_name, &lol) < 0);
		else if (S_ISDIR(lol.st_mode)){
			if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0){
				continue;				
			}
			sprintf(directoryPath,"%s/%s",fpath, dir->d_name);
			encryption_utility_function(directoryPath);
			printf("directoryPath %s\n", directoryPath);
		}
		else{
			sprintf(filePath,"%s/%s",fpath,dir->d_name);
			FILE *input = fopen(filePath, "r");
			if (input == NULL){
				return;				
			}
			int bytes_read, count = 0;
			void *buffer = malloc(1024);
			while((bytes_read = fread(buffer, 1, 1024, input)) > 0){
				char newFilePath[1000];
				sprintf(newFilePath, "%s.%04d", filePath, count);
				count++;
				FILE *output = fopen(newFilePath, "w+");
				if(output == NULL) return;
				fwrite(buffer, 1, bytes_read, output);
				fclose(output);
				memset(buffer, 0, 1024);
			}
			fclose(input);
			printf("filepath %s\n", filePath);
			remove(filePath);
		}
	}
    closedir(dp);
}
```
**If ```RX_``` is detected in the origin path and no ```RX_``` is detected in the destination path, it means that the directory is renamed by removing ```RX_``` and continued by merging files in the decryption function2.**
```
void decryption_utility_function(char *dir)
{
	chdir(dir);
	DIR *dp;
	struct dirent *de;
	struct stat lol;
	dp = opendir(".");
	if (dp == NULL) return;
	
	char directoryPath[1000];
	char filePath[1000];
	
	while ((de = readdir(dp)) != NULL){
		if (stat(de->d_name, &lol) < 0);
		else if (S_ISDIR(lol.st_mode)){
			if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0){
				continue;				
			}
			sprintf(directoryPath, "%s/%s", dir, de->d_name);
			decryption_utility_function(directoryPath);
		}
		else{
			sprintf(filePath, "%s/%s", dir, de->d_name);
			filePath[strlen(filePath) - 5] = '\0';
			FILE *check = fopen(filePath, "r");
			if (check != NULL){
				return;				
			}
			FILE *file = fopen(filePath, "w");
			int count = 0;
			char topath[1000];
			sprintf(topath, "%s.%04d", filePath, count);
			void *buffer = malloc(1024);
			while (1){
				FILE *op = fopen(topath, "rb");
				if (op == NULL){
					break;	
				}
				size_t readSize = fread(buffer, 1, 1024, op);
				fwrite(buffer, 1, readSize, file);
				fclose(op);
				remove(topath);
				count++;
				sprintf(topath, "%s.%04d", filePath, count);
			}
			free(buffer);
			fclose(file);
		}
	}
	closedir(dp);
}
```
**To perform encryption and decryption using the ROT13 cipher, a separate function will be created.**
```
void encrypt_rot13_on_rx(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")){
		return;		
	}
	
	printf("encrypt path ROT13: %s\n", path);
	
	int edge_of_id = split_file_id_return(path);
	int starting_point_of_id = slash_id_return(path, 0);
	
	for (int i = starting_point_of_id; i < edge_of_id; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char temporary = path[i];
			if(isupper(path[i])) temporary -= 'A';
			else temporary -= 'a';
			temporary = (temporary + 13) % 26; //ROT13 cipher
			if(isupper(path[i])) temporary += 'A';
			else temporary += 'a';
			path[i] = temporary;
		}
	}
}

void decrypt_rot13_on_not_rx(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")){
		return;		
	}
	
	printf("decrypt path ROT13: %s\n", path);
	
	int edge_of_id = split_file_id_return(path);
	int starting_point_of_id = slash_id_return(path, edge_of_id);
	
	for (int i = starting_point_of_id; i < edge_of_id; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char temporary = path[i];
			if(isupper(path[i])) temporary -= 'A';
			else temporary -= 'a';
			temporary = (temporary + 13) % 26; //ROT13 cipher
			if(isupper(path[i])) temporary += 'A';
			else temporary += 'a';
			path[i] = temporary;
		}
	}
}
```
The decryption function calls are performed on each utility function getattr, mkdir, rename, rmdir, create, and other functions that we think are essential in the FUSE synchronization process and mount folders. The decryption and encryption functions are carried out in the readdir utility function because FUSE will decrypt the mount folder and then encrypt it in FUSE during readdir. The call is done by checking whether the string RX_ is in the string path in each utility function by using the strstr() function. If yes, then the encryption and decryption functions will be called for that string with RX_ as the starting point of the passed string. Logging will be explained in question number 4.

# Question 3
Because Sin still feels exceptionally empty, he finally adds another feature to their file system.
a. If a directory is created with the prefix ```A_is_a_```, it will become a special directory.
b. If a directory is renamed with the prefix ```A_is_a_```, it will become a special directory.
c. If the encrypted directory is renamed by deleting ```A_is_a_``` at the beginning of the folder name, that directory becomes a normal directory.
d. Special directories are directories that return encryption/encoding to the ```AtoZ_``` or ```RX_``` directories but their respective rules still run in the directory within them
(```AtoZ_``` and ```RX_``` recursive properties still run in subdirectories).
e. In the special directory, all filenames (excluding extensions) in the fuse will be changed to lowercase (insensitive) and will be given a new extension in the form
of a decimal value from the binary value that comes from the difference in character between filenames.
For example, if in the original directory the filename is ```FiLe_CoNtoH.txt``` then in the fuse it will be ```file_contoh.txt.1321```. 1321 comes from binary 10100101001.

# Solution 3
**In the ```RENAME``` utility functions, it is checked whether the directory is renamed by adding ```A_is_a_``` or removing ```A_is_a_``` with the strstr() function.**
```
static int xmp_rename(const char *from, const char *to)
{
	int res;
	char frompath[1000], topath[1000];
	
	...
	
	sprintf(frompath, "%s%s", directoryPath, from);
	sprintf(topath, "%s%s", directoryPath, to);

	res = rename(frompath, topath);
	if (res == -1) return -errno;

	writeLog2("RENAME", frompath, topath);
	
	...
	
	if (strstr(to, aisa) != NULL){
		encrypt_binary_from_difference(topath);
		writeLog2("ENCRYPT3", from, to);
	}
	
	if (strstr(from, aisa) != NULL && strstr(to, aisa) == NULL){
		decrypt_binary_to_normal_from_difference(topath);
		writeLog2("DECRYPT3", from, to);
	}

	return 0;
}
```
**If A_is_a_ is detected in the destination path, it means the directory was renamed by adding A_is_a_. Then proceed with changing the file name to lowercase and adding the decimal value as a new extension to the encryptBinary function.**

```
void get_binary_from_difference(char *fname, char *bin, char *lowercase){
	int edge_of_id = file_extension_index_return(fname);
	int starting_point_of_id = slash_id_return(fname, 0);
	int i;
	
	for(i=starting_point_of_id; i<edge_of_id; i++){
		if(isupper(fname[i])){
			bin[i] = '1';
			lowercase[i] = fname[i] + 32;
		}
		else{
			bin[i] = '0';
			lowercase[i] = fname[i];
		}
	}
	bin[edge_of_id] = '\0';
	
	for(; i<strlen(fname); i++){
		lowercase[i] = fname[i];
	}
	lowercase[i] = '\0';
}
```

```
int binary_to_decimal_converter(char *bin){
	int temporary = 1, res = 0;
	for(int i=strlen(bin)-1; i>=0; i--){
		if(bin[i] == '1') res += temporary;
		temporary *= 2;
	}
	return res;
}
```

```
void encrypt_binary_from_difference(char *fpath)
{
	chdir(fpath);
	DIR *dp;
	struct dirent *dir;
	struct stat lol;
	dp = opendir(".");
	if(dp == NULL) return;
	
	char directoryPath[1000];
	char filePath[1000];
	char filePathBinary[1000];
	
    while ((dir = readdir(dp)) != NULL){
		if (stat(dir->d_name, &lol) < 0);
		else if (S_ISDIR(lol.st_mode)){
			if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0){
				continue;	
			}
			sprintf(directoryPath,"%s/%s",fpath, dir->d_name);
			encrypt_binary_from_difference(directoryPath);
		}
		else{
			sprintf(filePath,"%s/%s",fpath, dir->d_name);
			char bin[1000], lowercase[1000];
			get_binary_from_difference(dir->d_name, bin, lowercase);
			int dec = binary_to_decimal_converter(bin);
			sprintf(filePathBinary,"%s/%s.%d",fpath,lowercase,dec);
			rename(filePath, filePathBinary);
		}
	}
    closedir(dp);
}
```

**If ```A_is_a_ is``` detected in the origin path and ```A_is_a_``` is not detected in the destination path, it means that the directory is renamed by removing ```A_is_a_```. Then proceed with changing the file name to the original with the help of the decimal value in the decryptBinary function.**
```
int convert_decimal(char *ext){
	int dec = 0, multiplier = 1;
	for(int i=strlen(ext)-1; i>=0; i--){
		dec += (ext[i]-'0')*multiplier;
		multiplier *= 10;
	}
	return dec;
}
```

```
void decimal_to_binary_converter(int dec, char *bin, int len){
	int idx = 0;
	while(dec){
		if(dec & 1){
			bin[idx] = '1';	
		}
		else{
			bin[idx] = '0';
		}
		idx++;
		dec /= 2;
	}
	while(idx < len){
		bin[idx] = '0';
		idx++;
	}
	bin[idx] = '\0';
	
	for(int i=0; i<idx/2; i++){
		char temporary = bin[i];
		bin[i] = bin[idx-1-i];
		bin[idx-1-i] = temporary;
	}
}
```

```
void get_decimal(char *fname, char *bin, char *normalcase){
	int edge_of_id = file_extension_index_return(fname);
	int starting_point_of_id = slash_id_return(fname, 0);
	int i;
	
	for(i=starting_point_of_id; i<edge_of_id; i++){
		if(bin[i-starting_point_of_id] == '1') normalcase[i-starting_point_of_id] = fname[i] - 32;
		else normalcase[i-starting_point_of_id] = fname[i];
	}
	
	for(; i<strlen(fname); i++){
		normalcase[i-starting_point_of_id] = fname[i];
	}
	normalcase[i-starting_point_of_id] = '\0';
}
```

```
void decrypt_binary_to_normal_from_difference(char *fpath)
{
	chdir(fpath);
	DIR *dp;
	struct dirent *dir;
	struct stat lol;
	dp = opendir(".");
	if(dp == NULL){
		return;		
	}
	
	char directoryPath[1000];
	char filePath[1000];
	char filePathDecimal[1000];
	
    while ((dir = readdir(dp)) != NULL){
		if (stat(dir->d_name, &lol) < 0);
		else if (S_ISDIR(lol.st_mode)){
			if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0){
				continue;	
			}
			sprintf(directoryPath,"%s/%s",fpath, dir->d_name);
			decrypt_binary_to_normal_from_difference(directoryPath);
		}
		else{
			sprintf(filePath,"%s/%s",fpath, dir->d_name);
			char fname[1000], bin[1000], normalcase[1000], clearPath[1000];
			
			strcpy(fname, dir->d_name);
			char *ext = strrchr(fname, '.');
			int dec = convert_decimal(ext+1);
			for(int i=0; i<strlen(fname)-strlen(ext); i++){
				clearPath[i] = fname[i];	
			}
			
			char *ext2 = strrchr(clearPath, '.');
			decimal_to_binary_converter(dec, bin, strlen(clearPath)-strlen(ext2));
			get_decimal(clearPath, bin, normalcase);
			sprintf(filePathDecimal,"%s/%s",fpath,normalcase);
			rename(filePath, filePathDecimal);
		}
	}
    closedir(dp);
}
```

**Problems**
```
A bit confused by the meaning of the special directory.
A little confused when decrypting because you need to take the decimal value that is at the end of the file name.
Binary uses the array of char data type because of the fear of integer overflow. 
This causes the conversion of binary to decimal and vice versa a bit of a problem.
```
**Screenshots**

**a.)**

![Screenshot from 2021-06-12 15-32-59](https://user-images.githubusercontent.com/61174498/121778913-5f212100-cbc3-11eb-9e93-640629bdfe30.png)

![Screenshot from 2021-06-12 15-36-18](https://user-images.githubusercontent.com/61174498/121778916-647e6b80-cbc3-11eb-950b-4bf591f3938f.png)

**b.)**

![Screenshot from 2021-06-12 15-31-49](https://user-images.githubusercontent.com/61174498/121778878-38fb8100-cbc3-11eb-92f1-980a037ed901.png)

![Screenshot from 2021-06-12 15-31-40](https://user-images.githubusercontent.com/61174498/121778884-3dc03500-cbc3-11eb-81e9-56b794113878.png)

**c.)**

![Screenshot from 2021-06-12 15-32-01](https://user-images.githubusercontent.com/61174498/121778889-44e74300-cbc3-11eb-95d3-eb2ad33a595c.png)

**d.)**

![Screenshot from 2021-06-12 15-48-41](https://user-images.githubusercontent.com/61174498/121778928-72cc8780-cbc3-11eb-91ab-82a16473fb0b.png)

![Screenshot from 2021-06-12 15-48-46](https://user-images.githubusercontent.com/61174498/121778940-82e46700-cbc3-11eb-8f17-f26920587844.png)

![Screenshot from 2021-06-12 15-49-12](https://user-images.githubusercontent.com/61174498/121778961-97c0fa80-cbc3-11eb-81fd-7e9f20b8e2e3.png)

![Screenshot from 2021-06-12 15-49-17](https://user-images.githubusercontent.com/61174498/121778964-9b548180-cbc3-11eb-8e91-d55ed68a688c.png)

**e.)**

![Screenshot from 2021-06-12 15-49-07](https://user-images.githubusercontent.com/61174498/121778949-8c6dcf00-cbc3-11eb-862d-567298de399a.png)

# Question 4
To make it easier to monitor activities on their filesystem, Sin and Sei created a log system with the following specifications.
a. The system log that will be created is named ```SinSeiFS.log``` in the user's home directory (/home/[user]/SinSeiFS.log). 
This system log maintains a list of system call commands that have been executed on the filesystem..
b. Because Sin and Sei like tidiness, the logs that are made will be divided into two levels,INFO and WARNING.
c. For the WARNING level log, it is used to log the rmdir and unlink syscalls.
d. The rest will be recorded at the INFO level.
e. The format for logging is:
```
[Level]::[dd][mm][yyyy]-[HH]:[MM]:[SS]:[CMD]::[DESC :: DESC]
Level : Level logging, dd : 2 digit date, mm : 2 digit month, yyyy : 4 digit year, HH
: 2 digit hour (24 Hour format),MM : 2 digit minute, SS : 2 digit second, CMD :
Called System Call, DESC : additional information and parameters
INFO::28052021-10:00:00:CREATE::/test.txt
INFO::28052021-10:01:00:RENAME::/test.txt::/rename.txt
```
# Solution 4
**For this matter we are asked to create a system log which aims to make it easier to monitor activities on the file system. Here we create two functions in making this system log, namely the ```writeLog``` and ```writeLog2``` functions, the difference is in the DESC (additional information and parameters) that need to be included in the format for logging. In writing the system log according to the existing format we need to find the current time to be included in the system log later. In the ```writeLog``` function we also enter the parameter ```char *name``` which is the System Call and char ```*fpath``` is a description of the existing file.**
```
void writeLog(char *name, char *fpath)
{
	time_t originaltime;
	struct tm *timeinfo;
	time(&originaltime);
	timeinfo = localtime(&originaltime);
```

**Next we initialize an array of char or string ```systemCallKeep``` to later save the system call commands that have been executed on the filesystem and record them in the ```SinSeiFS.log``` file. Then we need to open the ```SinSeiFS.log``` file in the user's home directory with mode ```a``` (append) so that a new log can be written later and if the file does not exist, a new file will be created.**
```
	char systemCallKeep[1000];
	
	FILE *file;
	file = fopen("/home/alvancho/SinSeiFS.log", "a");
```

**Next we can check the syscall in the parameter. If the syscall is ```RMDIR``` or ```UNLINK``` then the log level will be logged ```WARNING```. But if not, then the log level will be recorded ```INFO```. And will also note the current time along with other information.**
```
	if (strcmp(name, "RMDIR") == 0 || strcmp(name, "UNLINK") == 0){
		sprintf(systemCallKeep, "WARNING::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, name, fpath);		
	}
	else{
		sprintf(systemCallKeep, "INFO::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, name, fpath);		
	}
```

**The last step is to write down the existing logs into the ```SinSeiFS.log``` file and close the file.**
```
	fputs(systemCallKeep, file);
	fclose(file);
	return;
}
```

**For the second function, ```writeLog2``` is actually more or less the same as the ```writeLog``` function described earlier, but there are differences in the parameters given and in the recording. For the parameters there is a ```char *name``` which is a syscall, ```const char *from``` is a file description before the system call command is executed by the file system and a ```const char *to``` file description after the system call command is executed by the file system. Then the recording is more or less the same as the previous one but added information according to the parameters given.**
```
void writeLog2(char *name, const char *from, const char *to)
{
	time_t originaltime;
	struct tm *timeinfo;
	time(&originaltime);
	timeinfo = localtime(&originaltime);

	char systemCallKeep[1000];

	FILE *file;
	file = fopen("/home/alvancho/SinSeiFS.log", "a");

	if (strcmp(name, "RMDIR") == 0 || strcmp(name, "UNLINK") == 0){
		sprintf(systemCallKeep, "WARNING::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, name, from, to);		
	}
	else{
		sprintf(systemCallKeep, "INFO::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, name, from, to);		
	}

	fputs(systemCallKeep, file);
	fclose(file);
	return;
}
```

**Problems**
```
There was a problem when recording the file because it was different from the given format.
There is difficulty in taking real time and keeping track of it.
Was confused to record the System Call because some have 1 or 2 arguments. Finally we split it into 2 functions for logging.
```
**Screenshots**
**a.), b.), c.), d.), e.)**

![Screenshot from 2021-06-12 15-41-45](https://user-images.githubusercontent.com/61174498/121778987-b4f5c900-cbc3-11eb-98ba-de827f57a30b.png)

