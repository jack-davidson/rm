/* See LICENSE file for copyright and license details.
 *
 * rr
 *
 * Mini implementation of rm.
 *
 */
#define _XOPEN_SOURCE 700
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

#define PATH_SIZE 512

int
rr(char *path, int recursive)
{
	char new_path[PATH_SIZE];
	struct stat path_stat;
	struct dirent *entry;
	DIR *src_dir;
	int is_dir;

	lstat(path, &path_stat);
	is_dir = S_ISDIR(path_stat.st_mode);

	if (is_dir) {
		if (!recursive) {
			printf("%s is a directory\n", path);
			return -1;
		}
		src_dir = opendir(path);
		if (src_dir == NULL){
			fprintf(stderr, "cannot open %s\n", path);
			return -1;
		}
		while ((entry = readdir(src_dir)) != NULL) {
			if (strcmp(entry->d_name, "..") & strcmp(entry->d_name, ".")) {
				snprintf(new_path, PATH_SIZE,
					 "%s/%s", path,
					 entry->d_name);
				rr(new_path, 1);
			}
		}
		closedir(src_dir);
	}
	remove(path);
	return 0;
}

void usage()
{
	printf("usage: rr [-r] file\n");
}

int main(int argc, char *argv[])
{
	if (argc == 1)
		usage();
	if (argc > 2 && !strcmp(argv[1], "-r"))
		rr(argv[2], 1);
	if (argc == 2)
		rr(argv[1], 0);
	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage();
}
