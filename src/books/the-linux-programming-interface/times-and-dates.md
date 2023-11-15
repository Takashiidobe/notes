---
title: times-and-dates
---

# The Linux Programming Interface

Prev: [process-credentials](process-credentials.md)
Next: [system-limits-and-options](system-limits-and-options.md)

Within a program, there are two kinds of time:

- **Real Time** The amount of time measured from some standard point (calendar time) or from the start of a process (wall clock time)
- **Process Time** The amount of CPU time used by a process.

## Calendar Time

Unix systems represent time internally as a measure of seconds since the unix epoch, starting at 1/1/1970. Calendar time is stored in variables of type `time_t`.

```c
#include <sys/time.h>
int gettimeofday(struct timeval *tv, struct timezone *tz); // Returns 0 on success, or –1 on error
```

The `tv` argument is a pointer to a structure:

```c
struct timeval {
    time_t tv_sec; /* Seconds since 00:00:00, 1 Jan 1970 UTC */
    suseconds_t tv_usec; /* Additional microseconds (long int) */
};
```

`tv_usec` has microsecond precision, but the accuracy is architecture independent. The `tz` argument should always be specified as NULL.

The `time` system call returns the number of seconds since the Epoch.


```c
#include <time.h>
time_t time(time_t *timep); // Returns number of seconds since the Epoch,or (time_t) –1 on error
```

If `timep` is not null, then the number of seconds is also placed in `timep`.

`time` is a historical artifact, since `gettimeofday` does more.

## Time-Conversion Functions

To convert time to a printable format:

```c
#include <time.h>
char *ctime(const time_t *timep); // Returns pointer to statically allocated string terminated by newline and \0 on success, or NULL on error
```

This returns a 26-byte string containing the date and time in a standard format.
Since this returns a pointer to a statically allocated structure, a reentrant version is provided, `ctime_r`.

### Converting Between `time_t` and Broken-Down Time

```c
#include <time.h>
struct tm *gmtime(const time_t *timep);
struct tm *localtime(const time_t *timep); // Both return a pointer to a statically allocated broken-down time structure on success, or NULL on error
```

`gmtime` converts a calendar time into a broken down time corresponding to UTC. `localtime` takes into account local timezone and DST settings to give a time corresponding to the local time. `gmtime_r` and `localtime_r` are reentrant version.

```c
struct tm {
    int tm_sec; /* Seconds (0-60) */
    int tm_min; /* Minutes (0-59) */
    int tm_hour; /* Hours (0-23) */
    int tm_mday; /* Day of the month (1-31) */
    int tm_mon; /* Month (0-11) */
    int tm_year; /* Year since 1900 */
    int tm_wday; /* Day of the week (Sunday = 0)*/
    int tm_yday; /* Day in the year (0-365; 1 Jan = 0)*/
    int tm_isdst; /* Daylight saving time flag
                   > 0: DST is in effect;
                   = 0: DST is not effect;
                   < 0: DST information not available */
};
```

`tm_sec` can be up to 60 to account for leap seconds.

If `_BSD_SOURCE` is set, then `tm_gmtoff` and `tm_zone` are also included in the struct. `tm_gmtoff` contains the number of seconds that the represented time falls east of UTC, and `tm_zone` is the abbreviated timezone name.

`mktime` translates a local time into a `time_t` value.

```c
#include <time.h>
time_t mktime(struct tm *timeptr); // Returns seconds since the Epoch corresponding to timeptr on success, or (time_t) –1 on error
```

### Converting Between Broken-Down Time and Printable Form

To convert from broken down time to printable form, use `asctime`.

```c
#include <time.h>
char *asctime(const struct tm *timeptr); // Returns pointer to statically allocated string terminated by newline and \0 on success, or NULL on error
```

A reentrant version is provided by `asctime_r`.

To provide more control, `strftime` can be used:

```c
#include <time.h>
size_t strftime(char *outstr, size_t maxsize, const char *format,
const struct tm *timeptr); // Returns number of bytes placed in outstr (excluding terminating null byte) on success, or 0 on error
```

This takes a format string similar to printf's format string that changes the output.

### Converting from printable form to broken-down time

To convert from printable time to broken-down time, `strptime` can be thought of as the opposite of `strftime`.

```c
#define _XOPEN_SOURCE
#include <time.h>
char *strptime(const char *str, const char *format, struct tm *timeptr); // Returns pointer to next unprocessed character in str on success, or NULL on error
```

## Timezones

### Timezone definitions

Timezone definitions are held in `/usr/share/zoneinfo`, which contains information about each timezone regime in a country or region. Subdirectories are used to group timezones together. `/etc/localtime` defines the system's local time.

### Specifying the timezone for a program

To specify a timezone for a program, the `TZ` environment variable can be set to a string consisting of a colon followed by one of the timezone names defined in `/usr/share/zoneinfo`.

`tzset` can be used to set the timezone to some value.

## Locales

A locale is the subset of a user's environment that depends on language and cultural conventions.

### Locale definitions

Locale information is maintained under `/usr/share/locale`, which contains information about a locale. Programs may put their messages corresponding to various locales in files here.
There is a locale, `C`, which matches historical unix.

### Specifying the locale for a program

The `setlocale` function is used to set and query a locale.

```c
#include <locale.h>
char *setlocale(int category, const char *locale); // Returns pointer to a (usually statically allocated) string identifying the new or current locale on success, or NULL on error
```

## Updating the System Clock

To adjust the system call, `settimeofday` and `adjtime` can be used. These are mainly set by NTP daemons, since they require the caller have `CAP_SYS_TIME`.

```c
#define _BSD_SOURCE
#include <sys/time.h>
int settimeofday(const struct timeval *tv, const struct timezone *tz); // Returns 0 on success, or –1 on error
```

As with `gettimeofday`, `tz` is obsolete, so it should be passed `NULL`.

Since `settimeofday` immediately changes the system clock, which can cause applications like `make` or any application that uses timestamped logs to break, `adjtime` can be used, which causes the system clock to gradually adjust to the desired value.

```c
#define _BSD_SOURCE
#include <sys/time.h>
int adjtime(struct timeval *delta, struct timeval *olddelta); // Returns 0 on success, or –1 on error
```

This takes a `timeval` struct, which specifies the number of seconds to change the time. If it is positive, it adds time to the system clock each second. If negative, it removes a small amount of time each second. If there is a clock adjustment in progress, that is returned in `olddelta`.

## The Software Clock (Jiffies)

The accuracy of clocks in software is limited by the hardware, as well as the OS' idea of time, called jiffies. The software clock in linux is configurable to take a jiffy precision.

## Process Time

Process time is the amount of CPU time used by a process since its creation. The kernel separates this into two values, `User CPU time`, the amount of time spent executing in user mode, and `System CPU time`, the amount spent executing in kernel mode. The `times` system call can be used for this:

```c
#include <sys/times.h>
clock_t times(struct tms *buf); // Returns number of clock ticks (sysconf(_SC_CLK_TCK)) since “arbitrary” time in past on success, or (clock_t) –1 on error
```

`tms` looks like the following:

```c
struct tms {
    clock_t tms_utime; /* User CPU time used by caller */
    clock_t tms_stime; /* System CPU time used by caller */
    clock_t tms_cutime; /* User CPU time of all (waited for) children */
    clock_t tms_cstime; /* System CPU time of all (waited for) children */
}
```

For a simpler breakdown, with the User + System Time, `clock` is provided:

```c
#include <time.h>
clock_t clock(void); // Returns total CPU time used by calling process measured in CLOCKS_PER_SEC, or (clock_t) –1 on error
```



Prev: [process-credentials](process-credentials.md)
Next: [system-limits-and-options](system-limits-and-options.md)
