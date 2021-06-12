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

```
a. If a directory starts with “AtoZ_”, then that directory will be encoded.
b. If you rename a directory to have a prefix “AtoZ_”, then the directory will be
encoded.
c. When encoded directory is renamed to not have encoded name, then the
directory will be decoded
d. For every encoding of a directory (mkdir or rename) will be recorded in a log file.
The format is : /home/[USER]/Downloads/[Directory Name] →
/home/[USER]/Downloads/AtoZ_[Directory Name]
e. Encoding method is also applied to all other directories inside the encoded
directory.(rekursif)

** **

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

	sprintf(frompath, "%s%s", dirPath, from);
	sprintf(topath, "%s%s", dirPath, to);

	res = rename(frompath, topath);
	if (res == -1) return -errno;

	tulisLog2("RENAME", frompath, topath);
	
	...
	
	if (strstr(to, aisa) != NULL){
		encryptBinary(topath);
		tulisLog2("ENCRYPT3", from, to);
	}
	
	if (strstr(from, aisa) != NULL && strstr(to, aisa) == NULL){
		decryptBinary(topath);
		tulisLog2("DECRYPT3", from, to);
	}

	return 0;
}
```
**If A_is_a_ is detected in the destination path, it means the directory was renamed by adding A_is_a_. Then proceed with changing the file name to lowercase and adding the decimal value as a new extension to the encryptBinary function.**

```
void getBinary(char *fname, char *bin, char *lowercase){
	int endid = ext_id(fname);
	int startid = slash_id(fname, 0);
	int i;
	
	for(i=startid; i<endid; i++){
		if(isupper(fname[i])){
			bin[i] = '1';
			lowercase[i] = fname[i] + 32;
		}
		else{
			bin[i] = '0';
			lowercase[i] = fname[i];
		}
	}
	bin[endid] = '\0';
	
	for(; i<strlen(fname); i++){
		lowercase[i] = fname[i];
	}
	lowercase[i] = '\0';
}
```

```
int bin_to_dec(char *bin){
	int tmp = 1, res = 0;
	for(int i=strlen(bin)-1; i>=0; i--){
		if(bin[i] == '1') res += tmp;
		tmp *= 2;
	}
	return res;
}
```

```
void encryptBinary(char *fpath)
{
	chdir(fpath);
	DIR *dp;
	struct dirent *dir;
	struct stat lol;
	dp = opendir(".");
	if(dp == NULL) return;
	
	char dirPath[1000];
	char filePath[1000];
	char filePathBinary[1000];
	
	while ((dir = readdir(dp)) != NULL){
		if (stat(dir->d_name, &lol) < 0);
		else if (S_ISDIR(lol.st_mode)){
			if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0) continue;
			sprintf(dirPath,"%s/%s",fpath, dir->d_name);
			encryptBinary(dirPath);
		}
		else{
			sprintf(filePath,"%s/%s",fpath, dir->d_name);
			char bin[1000], lowercase[1000];
			getBinary(dir->d_name, bin, lowercase);
			int dec = bin_to_dec(bin);
			sprintf(filePathBinary,"%s/%s.%d",fpath,lowercase,dec);
			rename(filePath, filePathBinary);
		}
	}
	closedir(dp);
}
```

**If ```A_is_a_ is``` detected in the origin path and ```A_is_a_``` is not detected in the destination path, it means that the directory is renamed by removing ```A_is_a_```. Then proceed with changing the file name to the original with the help of the decimal value in the decryptBinary function.**
```
int convertDec(char *ext){
	int dec = 0, pengali = 1;
	for(int i=strlen(ext)-1; i>=0; i--){
		dec += (ext[i]-'0')*pengali;
		pengali *= 10;
	}
	return dec;
}
```

```
void dec_to_bin(int dec, char *bin, int len){
	int idx = 0;
	while(dec){
		if(dec & 1) bin[idx] = '1';
		else bin[idx] = '0';
		idx++;
		dec /= 2;
	}
	while(idx < len){
		bin[idx] = '0';
		idx++;
	}
	bin[idx] = '\0';
	
	for(int i=0; i<idx/2; i++){
		char tmp = bin[i];
		bin[i] = bin[idx-1-i];
		bin[idx-1-i] = tmp;
	}
}
```

```
void getDecimal(char *fname, char *bin, char *normalcase){
	int endid = ext_id(fname);
	int startid = slash_id(fname, 0);
	int i;
	
	for(i=startid; i<endid; i++){
		if(bin[i-startid] == '1') normalcase[i-startid] = fname[i] - 32;
		else normalcase[i-startid] = fname[i];
	}
	
	for(; i<strlen(fname); i++){
		normalcase[i-startid] = fname[i];
	}
	normalcase[i-startid] = '\0';
}
```

```
void decryptBinary(char *fpath)
{
	chdir(fpath);
	DIR *dp;
	struct dirent *dir;
	struct stat lol;
	dp = opendir(".");
	if(dp == NULL) return;
	
	char dirPath[1000];
	char filePath[1000];
	char filePathDecimal[1000];
	
	while ((dir = readdir(dp)) != NULL){
		if (stat(dir->d_name, &lol) < 0);
		else if (S_ISDIR(lol.st_mode)){
			if (strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name,"..") == 0) continue;
			sprintf(dirPath,"%s/%s",fpath, dir->d_name);
			decryptBinary(dirPath);
		}
		else{
			sprintf(filePath,"%s/%s",fpath, dir->d_name);
			char fname[1000], bin[1000], normalcase[1000], clearPath[1000];
			
			strcpy(fname, dir->d_name);
			char *ext = strrchr(fname, '.');
			int dec = convertDec(ext+1);
			for(int i=0; i<strlen(fname)-strlen(ext); i++) clearPath[i] = fname[i];
			
			char *ext2 = strrchr(clearPath, '.');
			dec_to_bin(dec, bin, strlen(clearPath)-strlen(ext2));
			getDecimal(clearPath, bin, normalcase);
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
**For this matter we are asked to create a system log which aims to make it easier to monitor activities on the file system. Here we create two functions in making this system log, namely the ```tulisLog``` and ```tulisLog2``` functions, the difference is in the DESC (additional information and parameters) that need to be included in the format for logging. In writing the system log according to the existing format we need to find the current time to be included in the system log later. In the ```tulisLog``` function we also enter the parameter ```char *nama``` which is the System Call and char ```*fpath``` is a description of the existing file.**
```
void tulisLog(char *nama, char *fpath)
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
```

**Next we initialize an array of char or string ```haha``` to later save the system call commands that have been executed on the filesystem and record them in the ```SinSeiFS.log``` file. Then we need to open the ```SinSeiFS.log``` file in the user's home directory with mode ```a``` (append) so that a new log can be written later and if the file does not exist, a new file will be created.**
```
	char haha[1000];
	
	FILE *file;
	file = fopen("/home/alvancho/SinSeiFS.log", "a");
```

**Next we can check the syscall in the parameter. If the syscall is ```RMDIR``` or ```UNLINK``` then the log level will be logged ```WARNING```. But if not, then the log level will be recorded ```INFO```. And will also note the current time along with other information.**
```
	if (strcmp(nama, "RMDIR") == 0 || strcmp(nama, "UNLINK") == 0)
		sprintf(haha, "WARNING::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, nama, fpath);
	else
		sprintf(haha, "INFO::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, nama, fpath);
```

**The last step is to write down the existing logs into the ```SinSeiFS.log``` file and close the file.**
```
	fputs(haha, file);
	fclose(file);
	return;
}
```

**For the second function, ```tulisLog2``` is actually more or less the same as the ```tulisLog``` function described earlier, but there are differences in the parameters given and in the recording. For the parameters there is a ```char *name``` which is a syscall, ```const char *from``` is a file description before the system call command is executed by the file system and a ```const char *to``` file description after the system call command is executed by the file system. Then the recording is more or less the same as the previous one but added information according to the parameters given.**
```
void tulisLog2(char *nama, const char *from, const char *to)
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	char haha[1000];

	FILE *file;
	file = fopen("/home/alvancho/SinSeiFS.log", "a");

	if (strcmp(nama, "RMDIR") == 0 || strcmp(nama, "UNLINK") == 0)
		sprintf(haha, "WARNING::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, nama, from, to);
	else
		sprintf(haha, "INFO::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, nama, from, to);

	fputs(haha, file);
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

