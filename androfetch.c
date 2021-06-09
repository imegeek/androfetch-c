/*
Program Name androfetch
Written by ABHacker Official
License under MIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/utsname.h>

int main(void) {

#if __ANDROID__
  const char * Art[] = {
"\033[1;38;2;129;175;239m",
"      ╲ ▁▂▂▂▁ ╱",
"      ▄███████▄",
"     ▄██ ███ ██▄",
"    ▄███████████▄",
" ▄█ ▄▄▄▄▄▄▄▄▄▄▄▄▄ █▄",
" ██ █████████████ ██",
" ██ █████████████ ██",
" ██ █████████████ ██",
" ██ █████████████ ██",
"    █████████████",
"     ███████████",
"      ██     ██",
"      ██     ██\033[0m\n"
    };
    for (int i = 0; i < sizeof(Art) / sizeof(Art[0]); ++i) {
        puts(Art[i]);
    }

    struct utsname buf1;

   errno =0;

   if(uname(&buf1)!=0)

   {

      perror("uname doesn't return 0, so there is an error");

      exit(EXIT_FAILURE);

   }

   // include cpu file here.
   double cpu;
   FILE *fptr;

   fptr = fopen("/sys/devices/system/cpu/cpufreq/policy6/cpuinfo_max_freq", "r");

    // read the cpu file
   fscanf(fptr,"%lf", &cpu);

  int system(const char *command);
  char *buf, hostname[HOST_NAME_MAX + 1];
  buf=getlogin();
  gethostname(hostname, HOST_NAME_MAX + 1);

  printf("   \033[38;2;97;175;239m%s\033[0m@\033[38;2;97;175;239m%s\033[0m\n   -----------------\n"
,buf, hostname);
  system("printf ' \033[38;2;97;175;239mDevice\033[0m : ' && getprop ro.product.model");
  system("printf ' \033[38;2;97;175;239mVersion\033[0m : ' && printf 'Android ' && getprop ro.build.version.release");
  printf(" \033[38;2;97;175;239mArch\033[0m :  %s\n", buf1.machine);
  system("printf ' \033[38;2;97;175;239mShell\033[0m : ' && printf $(basename $SHELL)");
  system("echo && printf ' \033[38;2;97;175;239mPackages\033[0m : ' && dpkg -l | wc -l");
  system("printf ' \033[38;2;97;175;239mRom\033[0m : ' && getprop ro.build.display.id");
  printf(" \033[38;2;97;175;239mKernel\033[0m : %s\n", buf1.release);
  system("printf ' \033[38;2;97;175;239mCpu\033[0m : ' && cat /proc/cpuinfo | grep 'Hardware' | awk '{printf $3 $4 $5 $6}' | sed 's/,/, /g' && printf ' core (' && cat /proc/cpuinfo | grep 'CPU architecture' | awk NR==1 | awk '{printf $3}' && printf ')'");
  printf("\n \033[38;2;97;175;239mCpu freq\033[0m : %f GHz\n",(cpu/1000* 0.100*0.1*0.1));
  fclose(fptr);

  // system("echo && printf ' \033[38;2;97;175;239mCpu freq\033[0m : ' && printf 'max ' && cat /sys/devices/system/cpu/cpufreq/policy6/cpuinfo_max_freq");

  system("printf ' \033[38;2;97;175;239mMemory\033[0m : ' && free -m | awk NR==2 | awk '{printf $3}' && printf 'Mib / ' && free -m | awk NR==2 | awk '{printf $2}' && printf 'Mib'");
  system("echo && printf ' \033[38;2;97;175;239mUptime\033[0m : ' && uptime -p | cut -c 4-");

int a=0, b=0;

    printf(" \033[38;2;97;175;239mTerm colors\033[0m :  ");
    for (; a <= 7;)
    {
        printf( "\033[3%dm▄▄", a);
        a=a+1;
        if (a==8)
        {
            printf("\n\t\t");
           // break;
            for (; b<=7;)
            {
                printf( "\033[9%dm▀▀", b);
                b=b+1;
            }
            printf("\n");
            break;
        }
    }
#else

    printf("Sorry, the system are not listed above.\n");
#endif
  return EXIT_SUCCESS;
}

