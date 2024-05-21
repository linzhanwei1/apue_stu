/* getpwnam函数 */
#include <sys/types.h>
#include <pwd.h>
#include <stddef.h>
#include <string.h>

struct passwd *getpwnam(const char *name)
{
    struct passwd *ptr;

    /* 在程序开始处调用setpwent是保护性的措施，以便在调用者在此之前已经调用过getpwent
     * 的情况下，反绕有关文件使它们定位到文件开始处。
     */
    setpwent();
    while ((ptr = getpwent()) != NULL)
    {
        if (strcmp(name, ptr->pw_name) == 0)
            break;
    }
    endpwent();

    return ptr; // ptr is NULL is no match found
}