#include "user.h"
#include "platform.h"
#include "defaults.h"

#include <util/generic/yexception.h>

#ifdef _win_
#   include "winint.h"
#else
#   include <errno.h>
#   include <pwd.h>
#   include <unistd.h>
#endif

Stroka GetUsername() {
    TTempBuf nameBuf;
    for (;;) {
#if defined(_win_)
        DWORD len = (DWORD)Min(nameBuf.Size(), size_t(32767));
        if (!GetUserNameA(nameBuf.Data(), &len)) {
            DWORD err = GetLastError();
            if ((err == ERROR_INSUFFICIENT_BUFFER) && (nameBuf.Size() <= 32767))
                nameBuf = TTempBuf((size_t)len);
            else
                ythrow TSystemError(err) << " GetUserName failed";
        } else {
            return Stroka(nameBuf.Data(), (size_t)(len - 1));
        }
#else
        passwd pwd;
        passwd* tmpPwd;
        int err = getpwuid_r(geteuid(), &pwd, nameBuf.Data(), nameBuf.Size(), &tmpPwd);
        if (err) {
            if (err == ERANGE)
                nameBuf = TTempBuf(nameBuf.Size() * 2);
            else
                ythrow TSystemError(err) << " getpwuid_r failed";
        } else {
            return Stroka(pwd.pw_name);
        }
#endif
    }
}
