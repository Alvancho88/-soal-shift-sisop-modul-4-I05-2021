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

static const char *directoryPath = "/home/alvancho/Downloads";
// gcc -Wall `pkg-config fuse --cflags` SinSeiFS_I05.c -o SinSeiFS_I05 `pkg-config fuse --libs`
// ./SinSeiFS_I05  test/
// fusermount -u test/

char *key = "SISOP";
char *atoz = "AtoZ_";
char *rx = "RX_";
char *aisa = "A_is_a_";
int x = 0;

void writeLog(char *name, char *fpath)
{
	time_t originaltime;
	struct tm *timeinfo;
	time(&originaltime);
	timeinfo = localtime(&originaltime);

	char systemCallKeep[1000];

	FILE *file;
	file = fopen("/home/alvancho/SinSeiFS.log", "a");

	if (strcmp(name, "RMDIR") == 0 || strcmp(name, "UNLINK") == 0){
		sprintf(systemCallKeep, "WARNING::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, name, fpath);		
	}
	else{
		sprintf(systemCallKeep, "INFO::%.2d%.2d%d-%.2d:%.2d:%.2d::%s::%s\n", timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, name, fpath);		
	}

	fputs(systemCallKeep, file);
	fclose(file);
	return;
}

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

int split_file_id_return(char *path)
{
	int exist = 0;
	for(int i=strlen(path)-1; i>=0; i--){
		if (path[i] == '.'){
			if(exist == 1){
				return i;				
			}
			else{
				exist = 1;				
			}
		}
	}
	return strlen(path);
}

int file_extension_index_return(char *path)
{
	for(int i=strlen(path)-1; i>=0; i--){
		if (path[i] == '.') return i;
	}
	return strlen(path);
}

int slash_id_return(char *path, int finish)
{
	for(int i=0; i<strlen(path); i++){
		if (path[i] == '/'){
			return i + 1;			
		}
	}
	return finish;
}

void encrypt_atbash_cipher_on_atoz(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")){
		return;		
	}
	
	printf("encrypt path Atbash: %s\n", path);
	
	int edge_of_id = split_file_id_return(path);
	if(edge_of_id == strlen(path)) edge_of_id = file_extension_index_return(path);
	int starting_point_of_id = slash_id_return(path, 0);
	
	for (int i = starting_point_of_id; i < edge_of_id; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char temporary = path[i];
			if(isupper(path[i])) temporary -= 'A';
			else temporary -= 'a';
			temporary = 25 - temporary; //Atbash cipher
			if(isupper(path[i])) temporary += 'A';
			else temporary += 'a';
			path[i] = temporary;
		}
	}
}

void decrypt_atbash_cipher_on_not_atoz(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")){
		return;		
	}
	
	printf("decrypt path Atbash: %s\n", path);
	
	int edge_of_id = split_file_id_return(path);
	if(edge_of_id == strlen(path)) edge_of_id = file_extension_index_return(path);
	int starting_point_of_id = slash_id_return(path, edge_of_id);
	
	for (int i = starting_point_of_id; i < edge_of_id; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char temporary = path[i];
			if(isupper(path[i])) temporary -= 'A';
			else temporary -= 'a';
			temporary = 25 - temporary; //Atbash cipher
			if(isupper(path[i])) temporary += 'A';
			else temporary += 'a';
			path[i] = temporary;
		}
	}
}

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

void encrypt_vigenere_on_rx_rename(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")){
		return;		
	}
	
	printf("encrypt path Vigenere: %s\n", path);
	
	int edge_of_id = split_file_id_return(path);
	int starting_point_of_id = slash_id_return(path, 0);
	
	for (int i = starting_point_of_id; i < edge_of_id; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char temporary1 = path[i];
			char temporary2 = key[(i-starting_point_of_id) % strlen(key)];
			if(isupper(path[i])){
				temporary1 -= 'A';
				temporary2 -= 'A';
				temporary1 = (temporary1 + temporary2) % 26; //Vigenere cipher
				temporary1 += 'A';
			}
			else{
				temporary1 -= 'a';
				temporary2 = tolower(temporary2) - 'a';
				temporary1 = (temporary1 + temporary2) % 26; //Vigenere cipher
				temporary1 += 'a';
			}
			path[i] = temporary1;
		}
	}
}

void decrypt_vigenere_on_not_rx_rename(char *path)
{
	if (!strcmp(path, ".") || !strcmp(path, "..")){
		return;		
	}
	
	printf("decrypt path Vigenere: %s\n", path);
	
	int edge_of_id = split_file_id_return(path);
	int starting_point_of_id = slash_id_return(path, edge_of_id);
	
	for (int i = starting_point_of_id; i < edge_of_id; i++){
		if (path[i] != '/' && isalpha(path[i])){
			char temporary1 = path[i];
			char temporary2 = key[(i-starting_point_of_id) % strlen(key)];
			if(isupper(path[i])){
				temporary1 -= 'A';
				temporary2 -= 'A';
				temporary1 = (temporary1 - temporary2 + 26) % 26; //Vigenere cipher
				temporary1 += 'A';
			}
			else{
				temporary1 -= 'a';
				temporary2 = tolower(temporary2) - 'a';
				temporary1 = (temporary1 - temporary2 + 26) % 26; //Vigenere cipher
				temporary1 += 'a';
			}
			path[i] = temporary1;
		}
	}
}

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

int binary_to_decimal_converter(char *bin){
	int temporary = 1, res = 0;
	for(int i=strlen(bin)-1; i>=0; i--){
		if(bin[i] == '1') res += temporary;
		temporary *= 2;
	}
	return res;
}

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

int convert_decimal(char *ext){
	int dec = 0, multiplier = 1;
	for(int i=strlen(ext)-1; i>=0; i--){
		dec += (ext[i]-'0')*multiplier;
		multiplier *= 10;
	}
	return dec;
}

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

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = lstat(fpath, stbuf);
	if (res == -1) return -errno;
	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
	char fpath[1000];
	//int rot13 = 0;
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime)){
			decrypt_rot13_on_not_rx(b);
			decrypt_atbash_cipher_on_not_atoz(b);
		//	rot13 = 1;
		//}
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	if (x != 24) x++;
	else writeLog("READDIR", fpath);

	int res = 0;
	DIR *dp;
	struct dirent *de;

	(void)offset;
	(void)fi;

	dp = opendir(fpath);
	//printf("lalalal %s\n", fpath);
	if (dp == NULL) return -errno;

	while ((de = readdir(dp)) != NULL){
		if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;

		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;

		//printf("before: %s\n", de->d_name);
		//printf("a: %s\n", a);
		if (a != NULL) encrypt_atbash_cipher_on_atoz(de->d_name);
		//printf("b: %s\n", b);
		if (b != NULL){
			//if(rot13)
			encrypt_atbash_cipher_on_atoz(de->d_name);
			encrypt_rot13_on_rx(de->d_name);
			//else
			//encrypt_vigenere_on_rx_rename(de->d_name);
		}
		//printf("after: %s\n", de->d_name);

		res = (filler(buf, de->d_name, &st, 0));
		if (res != 0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	int res = 0;
	int fd = 0;

	(void)fi;
	writeLog("READ", fpath);

	fd = open(fpath, O_RDONLY);
	if (fd == -1) return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1) res = -errno;

	close(fd);
	return res;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = mkdir(fpath, mode);
	writeLog("MKDIR", fpath);

	if (res == -1) return -errno;
	return 0;
}

static int xmp_rmdir(const char *path)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = rmdir(fpath);
	writeLog("RMDIR", fpath);

	if (res == -1) return -errno;
	return 0;
}

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

static int xmp_truncate(const char *path, off_t size)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	writeLog("TRUNC", fpath);
	res = truncate(fpath, size);
	
	if (res == -1) return -errno;
	return 0;
}

static int xmp_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	(void)fi;
	writeLog("WRITE", fpath);

	fd = open(fpath, O_WRONLY);
	if (fd == -1) return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1) res = -errno;

	close(fd);
	return res;
}

static int xmp_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	(void)fi;
	writeLog("CREATE", fpath);
	
	res = creat(fpath, mode);	
	if (res == -1) return -errno;

	close(res);
	return 0;
}

static int xmp_utimens(const char *path, const struct timespec ts[2])
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	struct timeval tv[2];

	tv[0].tv_sec = ts[0].tv_sec;
	tv[0].tv_usec = ts[0].tv_nsec / 1000;
	tv[1].tv_sec = ts[1].tv_sec;
	tv[1].tv_usec = ts[1].tv_nsec / 1000;

	res = utimes(fpath, tv);
	if (res == -1) return -errno;
	return 0;
}

static int xmp_access(const char *path, int mask)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = access(fpath, mask);
	if (res == -1) return -errno;
	return 0;
}

static int xmp_open(const char *path, struct fuse_file_info *fi)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = open(fpath, fi->flags);

	writeLog("OPEN", fpath);
	if (res == -1) return -errno;

	close(res);
	return 0;
}

static int xmp_unlink(const char *path)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = unlink(fpath);
	writeLog("UNLINK", fpath);

	if (res == -1) return -errno;
	return 0;
}

static int xmp_readlink(const char *path, char *buf, size_t size)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = readlink(fpath, buf, size - 1);
	writeLog("READLINK", fpath);
	if (res == -1) return -errno;

	buf[res] = '\0';
	return 0;
}

static int xmp_mknod(const char *path, mode_t mode, dev_t rdev)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	writeLog("MKNOD", fpath);
	
	/* On Linux this could just be 'mknod(path, mode, rdev)' but this is more portable */
	if (S_ISREG(mode)){
		res = open(fpath, O_CREAT | O_EXCL | O_WRONLY, mode);
		if (res >= 0) res = close(res);
	}
	else if (S_ISFIFO(mode)) res = mkfifo(fpath, mode);
	else res = mknod(fpath, mode, rdev);
	
	if (res == -1) return -errno;
	return 0;
}

static int xmp_symlink(const char *from, const char *to)
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

	res = symlink(frompath, topath);
	writeLog2("SYMLINK", frompath, topath);
	
	if (res == -1) return -errno;
	return 0;
}

static int xmp_link(const char *from, const char *to)
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

	res = link(frompath, topath);
	writeLog2("LINK", frompath, topath);

	if (res == -1) return -errno;
	return 0;
}

static int xmp_chmod(const char *path, mode_t mode)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = chmod(fpath, mode);
	writeLog("CHMOD", fpath);

	if (res == -1) return -errno;
	return 0;
}

static int xmp_chown(const char *path, uid_t uid, gid_t gid)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = lchown(fpath, uid, gid);
	writeLog("CHOWN", fpath);
	
	if (res == -1) return -errno;
	return 0;
}

static int xmp_statfs(const char *path, struct statvfs *stbuf)
{
	int res;
	char fpath[1000];
	
	char *a = strstr(path, atoz);
	if (a != NULL) decrypt_atbash_cipher_on_not_atoz(a);
	
	char *b = strstr(path, rx);
	if (b != NULL){
		//struct stat stats;
		//stat(path, &stats);
		//if(ctime(&stats.st_ctime) == ctime(&stats.st_mtime))
		decrypt_rot13_on_not_rx(b);
		decrypt_atbash_cipher_on_not_atoz(b);
		//else
		//decrypt_vigenere_on_not_rx_rename(b);
	}

	if (strcmp(path, "/") == 0){
		path = directoryPath;
		sprintf(fpath, "%s", path);
	}
	else{
		sprintf(fpath, "%s%s", directoryPath, path);
	}

	res = statvfs(fpath, stbuf);
	writeLog("STATFS", fpath);
	
	if (res == -1) return -errno;
	return 0;
}

static struct fuse_operations xmp_oper = {
	.getattr = xmp_getattr,
	.readdir = xmp_readdir,
	.read = xmp_read,
	.mkdir = xmp_mkdir,
	.rmdir = xmp_rmdir,
	.rename = xmp_rename,
	.truncate = xmp_truncate,
	.write = xmp_write,
	.create = xmp_create,
	.utimens = xmp_utimens,
	.access = xmp_access,
	.open = xmp_open,
	.unlink = xmp_unlink,
	.readlink = xmp_readlink,
	.mknod = xmp_mknod,
	.symlink = xmp_symlink,
	.link = xmp_link,
	.chmod = xmp_chmod,
	.chown = xmp_chown,
	.statfs = xmp_statfs,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
