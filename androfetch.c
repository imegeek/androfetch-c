/*
Program name androfetch
Written by ABHacker Official
Version tag 1.3.1
License under MIT
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>

void logo();
int main(int argc, char *argv[] ) {
  #if __ANDROID__

  if(argc > 1 && (strcmp(argv[1],"--stdout") == 0))
  {
    NULL;
  }

  else {
    logo();
  }


  int real = getuid();
  int euid = geteuid();

  struct sysinfo info;
    long total_ram = sysconf(_SC_PAGESIZE);
    long free_ram = (info.totalram/1024/1024/1024);
  struct utsname buf1;
  struct statvfs buf2;

   errno =0;

   if(uname(&buf1)!=0)

   {

      perror("uname doesn't return 0, so there is an error");

      exit(EXIT_FAILURE);

   }

   struct winsize w;
   ioctl(0, TIOCGWINSZ, &w);

   // include cpu file here.
   double cpu;
   FILE *fptr;

   fptr = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");

    // read the cpu file
   fscanf(fptr,"%lf", &cpu);

  int system(const char *command);
  char *buf, hostname[HOST_NAME_MAX + 1];
  buf=getlogin();
  gethostname(hostname, HOST_NAME_MAX + 1);

  printf("   \033[38;2;97;175;239m%s\033[0m@\033[38;2;97;175;239m%s\033[0m\n   -----------------\n"
,buf, hostname);
  system("printf ' \033[38;2;97;175;239mDevice\033[0m : '");
  system("getprop ro.product.model");

  system("printf ' \033[38;2;97;175;239mVersion\033[0m : '");
  system("printf 'Android ' && getprop ro.build.version.release");

  printf(" \033[38;2;97;175;239mArch\033[0m : %s\n", buf1.machine);

  system("printf ' \033[38;2;97;175;239mShell\033[0m : '");
  system("printf $(basename $SHELL)");

  system("echo && printf ' \033[38;2;97;175;239mPackages\033[0m : '");
  system("dpkg -l | wc -l");

  system("printf ' \033[38;2;97;175;239mRom\033[0m : '");
  system("getprop ro.build.display.id");

  printf(" \033[38;2;97;175;239mKernel\033[0m : %s\n", buf1.release);

  system("printf ' \033[38;2;97;175;239mCpu\033[0m : '");
  system("cat /proc/cpuinfo | grep 'Hardware' | awk '{printf $3 $4 $5 $6}' | sed 's/,/, /g' && printf ' core (' && cat /proc/cpuinfo | grep 'CPU architecture' | awk NR==1 | awk '{printf $3}' && printf ')'");

  printf("\n \033[38;2;97;175;239mCpu freq\033[0m : %.f GHz\n",(cpu/1000* 0.100*0.1*0.1));
  fclose(fptr);

 system("printf ' \033[38;2;97;175;239mMemory\033[0m : '");
 system("free -m | awk NR==2 | awk '{printf $3}' && printf 'Mib / ' && free -m | awk NR==2 | awk '{printf $2}' && printf 'Mib'");

/*  printf(" \033[38;2;97;175;239mMemory :\033[0m %ldMib / %ldMib\n", total_ram, total_ram-free_ram);

system("df > space1024.db");
char *filename = "space1024.db";
if (!statvfs(filename, &buf2)) {

  unsigned long free, disk, used, percent, blksize, blocks, freeblks, disk_size, used_size, free_size;

blksize = buf2.f_bsize;
blocks = buf2.f_blocks;
freeblks = buf2.f_bfree;

disk_size = blocks * blksize;
free_size = freeblks * blksize;
used_size = disk_size - free_size;

used = used_size/1024/1024/1024;                                            disk = disk_size/1024/1024/1024;
free = free_size/1024/1024/1024;                                            percent = used*100/disk;
                                                                            printf(" \033[38;2;97;175;239mDisk space\033[0m : %luG / %luG (%lu%%)\n", disk, used, percent);                                                         remove("space1024.db");
}                                                                           
else {                                                                      printf("Couldn't get file system statistics\n");
}*/

/*  system("printf ' \033[38;2;97;175;239mDisk space\033[0m : '");
  system("df -h | grep /data | awk NR==1 | awk '{printf $2}' && printf ' / ' && df -h | grep /data | awk NR==1 | awk '{printf $3}' && printf ' (' && df -h | grep /data | awk NR==1 | awk '{printf $5}' && printf ')'");*/

  system("echo && printf ' \033[38;2;97;175;239mUptime\033[0m : '");
  system("uptime -p | cut -c 4-");

  if ( real == 0 )
  {
    printf(" \033[38;2;97;175;239mUser\033[0m : (root user)\n");
  }
  else if ( euid == 0 )
  {
    printf(" \033[38;2;97;175;239mUser\033[0m : (root user)\n");
  }

  else
  {
  printf(" \033[38;2;97;175;239mUser\033[0m : non (root user)\n");
  }

  printf(" \033[38;2;97;175;239mTerm size\033[0m : %dx%d\n", w.ws_row, w.ws_col);

  if(argc > 1 && (strcmp(argv[1],"--compact") == 0))
  {
    NULL;
  }

  else if(argc > 1 && (strcmp(argv[1],"--stdout") == 0))
  {
    NULL;
  }
  else {
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
  }
#else

    printf("Sorry, the system are not listed above.\n");
#endif
  return EXIT_SUCCESS;
}

void logo()
{
  const char * Art[] = {
"\033[1;38;2;129;175;239m",
"      ╲ ▁▂▂▂▁ ╱",
"      ▄███████▄",
"     ▄██ ███ ██▄",                                                   "    ▄███████████▄",
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
}
