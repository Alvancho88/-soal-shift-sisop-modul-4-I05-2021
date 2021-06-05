#define FUSE_USE_VERSION 28

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <stdbool.h>

static const char *dirpath = "/home/alvancho/Documents";
static const char *needle = "/A_is_a_";
static const char *needle_2 = "/“AtoZ_";
static const char *needle_3 = "/RX_";
static const char *replacement = "/";

//char dir_list[ 256 ][ 256 ];
//int curr_dir_idx = -1;
//
//char files_list[ 256 ][ 256 ];
//int curr_file_idx = -1;
//
//char files_content[ 256 ][ 256 ];
//int curr_file_content_idx = -1;

//int shifit;
//int buka = 0;

static int xmp_getattr(const char *path, struct stat *stbuf);
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
static int xmp_mkdir(const char *path, mode_t mode);
static int xmp_rename(const char *from, const char *to);
//static int xmp_access(const char *path, int mask);
static int xmp_unlink(const char *path);
static int xmp_rmdir(const char *path);
static void str_replace(char *target);
//static add_dir( const char *dir_name );
//static int is_dir( const char *path );
//static bool isA_is_a(const char *path);
//static bool isLowerCase(char character);
//static bool isUpperCase(char character);
//void decryptit(char *fromthis);
//void encryptit(char *this);

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.mkdir		= xmp_mkdir,
	.rename		= xmp_rename,
	.read		= xmp_read,
//	.access		= xmp_access,
	.unlink		= xmp_unlink,
	.rmdir		= xmp_rmdir,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}

//static void add_dir( const char *dir_name )
//{
//	curr_dir_idx++;
//	strcpy( dir_list[ curr_dir_idx ], dir_name );
//}
//
//static int is_dir( const char *path )
//{
//	path++; // Eliminating "/" in the path
//	
//	for ( int curr_idx = 0; curr_idx <= curr_dir_idx; curr_idx++ )
//		if ( strcmp( path, dir_list[ curr_idx ] ) == 0 )
//			return 1;
//	
//	return 0;
//}

//void logging(FILE* log,int tipe, char nama[]){
//    char result[1024];
//    if(tipe == 1){
//        sprintf(result,"Tambah : %s (%s)\n",nama,user);//warning
//        fputs(result,log);
//    } else if(tipe == 2){
//        sprintf(result,"Hapus : %s (%s)\n",nama,user);//warning
//        fputs(result,log);
//    }
//}

static bool isA_is_a(const char *path){
    if(strlen(path) < 6) return false;

    char A_is_a[6] = "A_is_a";

    int count;
    for(count = 0; count <= 4; count++){
        if(A_is_a[count] != path[count]) return false;
    }
    return true;
}

static bool isLowerCase(char character){
    return (character > 96 && character < 123);
}

static bool isUpperCase(char character){
    return (character > 64 && character < 91);
}

static void str_replace(char *target)
{
    char buffer[1000] = { 0 };
    char *insert_point = &buffer[0];
    const char *tmp = target;
    size_t needle_len = strlen(needle);
    size_t repl_len = strlen(replacement);
 
    while (1) {
        const char *p = strstr(tmp, needle);
 
        // walked past last occurrence of needle; copy remaining part
        if (p == NULL) {
            strcpy(insert_point, tmp);
            break;
        }
 
        // copy part before needle
        memcpy(insert_point, tmp, p - tmp);
        insert_point += p - tmp;
 
        // copy replacement string
        memcpy(insert_point, replacement, repl_len);
        insert_point += repl_len;
 
        // adjust pointers, move on
        tmp = p + needle_len;
    }
 
    // return altered string with traget variable
    strcpy(target, buffer);
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
    int res;
    char fpath[1000];
 
    str_replace(path);
    sprintf(fpath, "%s%s", dirpath, path);
 
    res = lstat(fpath, stbuf);
 
    if (res == -1)
        return -errno;
 
    return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
	char fpath[1000], temp[1000];
	
	if (strcmp(path, "/") == 0)
    {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else {
        str_replace(path);
        sprintf(fpath, "%s%s", dirpath, path);
    }
    
    int res = 0;
    
	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(path);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		
		struct stat st;
		
		memset(&st, 0, sizeof(st));
		
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..")) {
//            strcpy(temp, de->d_name);
//            sprintf(de->d_name, "Jago_%s", temp);
        }
        res = (filler(buf, de->d_name, &st, 0));
 
        if (res != 0)
            break;
	}

	closedir(dp);
	return 0;
}

static int xmp_mkdir(const char *path, mode_t mode)
{
	int res;
	char fpath[1000];

	str_replace(path);
	sprintf(fpath, "%s%s", dirpath, path);
	res = mkdir(path, mode);
	//if(strcmp
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_rename(const char *from, const char *to)
{
	int res;
//	char fpath[1000];
//
//	str_replace(fpath);
//	sprintf(fpath, "%s%s", dirpath, path);

	res = rename(from, to);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    char fpath[1000];
    
    if (strcmp(path, "/") == 0) {
        path = dirpath;
        sprintf(fpath, "%s", path);
    }
    else {
        str_replace(path);
        sprintf(fpath, "%s%s", dirpath, path);
    }
 
    int res = 0;
    int fd = 0;
 
    (void)fi;
 
    fd = open(fpath, O_RDONLY);
 
    if (fd == -1)
        return -errno;
 
    res = pread(fd, buf, size, offset);
 
    if (res == -1)
        res = -errno;
 
    close(fd);
 
    return res;
}

//static int xmp_access(const char *path, int mask)
//{
//	int res;
//	char fpath[1000];
//
//	str_replace(path);
//	sprintf(fpath, "%s%s", dirpath, path);
//
//	res = access(path, mask);
//	if (res == -1)
//		return -errno;
//
//	return 0;
//}

static int xmp_unlink(const char *path)
{
	int res;
	char fpath[1000];

	str_replace(path);
	sprintf(fpath, "%s%s", dirpath, path);

	res = unlink(path);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_rmdir(const char *path)
{
	int res;
	char fpath[1000];

	str_replace(path);
	sprintf(fpath, "%s%s", dirpath, path);

	res = rmdir(path);
	if (res == -1)
		return -errno;

	return 0;
}

//void encryptit(char *this)
//{
//  int x = 0;
//  int whichchar;
//  
//  while(this[x] != '\0')
//  {
//      if (this[x] != '/')
//      {
//          whichchar = strchr(charlist, this[x]) - charlist;
//          this[x] = list[whichchar];
//      }
//
//      x++;
//  }
//
//}
//
//void decryptit(char *fromthis)
//{
//  int x = 0;
//  int whichlist;
//
//  while(fromthis[x] != '\0')
//  {
//      if(fromthis[x] != '/')
//      {
//          whichlist = strchr(list, fromthis[x]) - list;
//          fromthis[x] = charlist[whichlist];
//      }
//
//      x++;
//  }
//}