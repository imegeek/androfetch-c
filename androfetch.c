/*
Program name androfetch
Written by ABHacker Official
Version tag 1.3.4
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

void host()
{
  int system(const char *command);
  char *buf, hostname[HOST_NAME_MAX + 1];
  buf=getlogin();
  gethostname(hostname, HOST_NAME_MAX + 1);

    printf(" \033[38;2;97;175;239m%s\033[0m@\033[38;2;97;175;239m%s\033[0m\n -----------------\n"
,buf, hostname);
  }

void model()
{

  system("printf ' \033[38;2;97;175;239mDevice\033[0m : '");
  system("getprop ro.product.model");

}

void version()
{

  system("printf ' \033[38;2;97;175;239mVersion\033[0m : '");
  system("printf 'Android ' && getprop ro.build.version.release");

}

void arch()
{

 struct utsname buf1;
   errno =0;

   if(uname(&buf1)!=0)

   {

      perror("uname doesn't return 0, so there is an error");

      exit(EXIT_FAILURE);

   }

  printf(" \033[38;2;97;175;239mArch\033[0m : %s\n", buf1.machine);

}

void shell()
{

  system("printf ' \033[38;2;97;175;239mShell\033[0m : '");
  system("printf $(basename $SHELL)");

}

void package()
{

  system("echo && printf ' \033[38;2;97;175;239mPackages\033[0m : '");
  system("dpkg -l | wc -l");

}


void rom()
{

  system("printf ' \033[38;2;97;175;239mRom\033[0m : '");
  system("getprop ro.build.display.id");

}


void kernel()
{

  struct utsname buf1;
   errno =0;

   if(uname(&buf1)!=0)

   {

      perror("uname doesn't return 0, so there is an error");

      exit(EXIT_FAILURE);

   }

  printf(" \033[38;2;97;175;239mKernel\033[0m : %s\n", buf1.release);

}

void cpu()
{

  system("printf ' \033[38;2;97;175;239mCpu\033[0m : '");
  system("cat /proc/cpuinfo | grep 'Hardware' | awk '{printf $3 $4 $5 $6}' | sed 's/,/, /g' && printf ' core (' && cat /proc/cpuinfo | grep 'CPU architecture' | awk NR==1 | awk '{printf $3}' && printf ')'");

}

void cpu_freq()
{

 // include cpu file here.
   double cpu;
   FILE *fptr;

   fptr = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");

    // read the cpu file
   fscanf(fptr,"%lf", &cpu);

  printf("\n \033[38;2;97;175;239mCpu freq\033[0m : %.f GHz\n",(cpu/1000* 0.100*0.1*0.1));
  fclose(fptr);

}

void memory()
{

 system("printf ' \033[38;2;97;175;239mMemory\033[0m : '");
 system("free_ram=$(free -m | awk NR==2 | awk '{printf $3}') && total_ram=$(free -m | awk NR==2 | awk '{printf $2}') && printf \"${free_ram}Mib / ${total_ram}Mib\"  && printf \" ($((free_ram*100/total_ram))%%)\n\"");

}

void disk()
{

  struct statvfs buf2;

system("sh -c /sys/bin/df -h > space1024.db");
char *filename = "space1024.db";
if (!statvfs(filename, &buf2)) {

  float free, disk, used, percent, blksize, blocks, freeblks, disk_size, used_size, free_size;

blksize = buf2.f_bsize;
blocks = buf2.f_blocks;
freeblks = buf2.f_bfree;

disk_size = blocks * blksize;
free_size = freeblks * blksize;
used_size = disk_size - free_size;

used = used_size/1024/1024/1024;
disk = disk_size/1024/1024/1024;
free = free_size/1024/1024/1024;
percent = used*100/disk;

printf(" \033[38;2;97;175;239mDisk space\033[0m : %.1fG / %.1fG (%lu%%)\n", used, disk, (long)percent);
remove("space1024.db");
}
else {                                                                      printf("Couldn't get file system statistics\n");
}

}

void uptime()
{

  system("printf ' \033[38;2;97;175;239mUptime\033[0m : '");
  system("uptime -p | cut -c 4-");

}

void term_size()
{

   struct winsize w;
   ioctl(0, TIOCGWINSZ, &w);

  printf(" \033[38;2;97;175;239mTerm size\033[0m : %dx%d\n", w.ws_row, w.ws_col);

}


void root()
{

  int real = getuid();
  int euid = geteuid();

  if ( real == 0 )
  {
    printf(" \033[38;2;97;175;239mSu user\033[0m : (root user)\n");
  }
  else if ( euid == 0 )
  {
    printf(" \033[38;2;97;175;239mSu user\033[0m : (root user)\n");
  }

  else
  {
  printf(" \033[38;2;97;175;239mSu user\033[0m : non (root user)\n");
  }

}


void color_buff()
{
  int a=0, b=0;

    //printf(" \033[38;2;97;175;239mTerm colors\033[0m :  ");

      printf(" ");
    for (; a <= 7;)
    {
        printf( "\033[3%dm▄▄▄", a);
        a=a+1;
        if (a==8)
        {
            printf("\n ");
           // break;
            for (; b<=7;)
            {
                printf( "\033[9%dm▀▀▀", b);
                b=b+1;
            }
            printf("\n");
            break;
        }
    }
  }

void instructions()
{
  host();
  model();
  version();
  arch();
  shell();
  package();
  rom();
  kernel();
  cpu();
  cpu_freq();
  memory();
  disk();
  uptime();
  root();
  term_size();
}

int main(int argc, char *argv[] ) {
  #if __ANDROID__

  if(argc > 1 && (strcmp(argv[1],"--compact") == 0))
  {
    logo();
    instructions();
  }

  else if(argc > 1 && (strcmp(argv[1],"--stdout") == 0))
  {
    instructions();
  }
  else {
    logo();
    instructions();
    color_buff();
  }

#else

    printf("Sorry, the system are not listed above.\n");
#endif
  return EXIT_SUCCESS;
}

