#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <shadow.h>
#include <crypt.h>

int main(int argc, char *argv[])
{
    char *crypted_pass;
    char *input_pass;
    struct spwd *shadow_line;
    if (argc < 2)
    {
        fprintf(stderr, "Usage...\n");
        exit(1);
    }

    input_pass = getpass("PassWord:"); // 需要管理员权限
    shadow_line = getspnam(argv[1]);
    crypted_pass = crypt(input_pass, shadow_line->sp_pwdp);
    if (strcmp(shadow_line->sp_pwdp, crypted_pass) == 0)
        puts("ok!");
    else
        puts("failed");

    exit(0);
}