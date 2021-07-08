/*
Program name androfetch
Written by ABHacker Official
Version tag 1.4.1
License under MIT
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>

int randS(int num_count)
{

srand(time(0));
  int num = (rand() % (num_count - 1 + 1)) + 1;
  return num;
}

int rand_colors(int a)
{

  int num=randS(7);
  if (num == 1)
  {
    printf("\033[%d;38;2;129;175;239m", a);
  }
  else if (num == 2)
  {
    printf("\e[%d;38;2;224;108;117m", a);
  }
  else if (num == 3)
  {
    printf("\e[%d;38;2;152;195;121m", a);
  }
  else if (num == 4)
  {
    printf("\e[%d;38;2;229;192;123m", a);
  }
  else if (num == 5)
  {
    printf("\e[%d;38;2;198;120;221m", a);
  }
  else if (num == 6)
  {
    printf("\e[%d;38;2;142;200;216m", a);
  }
  else if (num == 7)
  {
    printf("\e[%d;38;2;97;175;239m", a);
  }
  return 0;
}

void logo()
{
  rand_colors(1);
  const char * Art[] = {
"",
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


int programS(char* command, char *name, char *exp)
{

  rand_colors(0);

  FILE *program;
  char cmd[1024];

  /* Open the command for reading. */
  program = popen(command, "r");
  if (program == NULL) {
    exit(1);
  }

  /* Read the output a line at a time - output it. */
  while (fgets(cmd, sizeof(cmd), program) != NULL) {
    printf("%s%s\033[0m : %s",exp, name, cmd);
  }

  pclose(program);
  return 0;
}


void host()
{
  rand_colors(1);
  int system(const char *command);
  char *buf, hostname[HOST_NAME_MAX + 1];
  buf=getlogin();
  gethostname(hostname, HOST_NAME_MAX + 1);

    printf(" %s\033[0m@", buf);
    rand_colors(1);
    printf("%s\033[0m\n -----------------\n", hostname);
  }

void model()
{

  programS("getprop ro.product.model", "Device", " ");

}

void version()
{

  programS("printf 'Android ' && getprop ro.build.version.release", "Version", " ");

}

void arch()
{

  rand_colors(0);
 struct utsname buf1;
   errno =0;

   if(uname(&buf1)!=0)

   {

      perror("uname doesn't return 0, so there is an error");

      exit(EXIT_FAILURE);

   }

  printf(" Arch\033[0m : %s", buf1.machine);

}

void shell()
{

  programS("printf $(basename $SHELL)", "Shell", "\n ");

}

void package()
{
  programS("dpkg -l | wc -l", "Packages", "\n ");

}


void rom()
{

  programS("getprop ro.build.display.id", "Rom", " ");

}


void kernel()
{
  rand_colors(0);
  struct utsname buf1;
   errno =0;

   if(uname(&buf1)!=0)

   {

      perror("uname doesn't return 0, so there is an error");

      exit(EXIT_FAILURE);

   }

  printf(" Kernel\033[0m : %s\n", buf1.release);

}

void cpu()
{

  programS("cat /proc/cpuinfo | grep 'Hardware' | awk '{printf $3 $4 $5 $6}' | sed 's/,/, /g' && printf ' core (' && cat /proc/cpuinfo | grep 'CPU architecture' | awk NR==1 | awk '{printf $3}' && printf ')'", "Cpu", " ");

}

void cpu_freq()
{

  rand_colors(0);
 // include cpu file here.
   double cpu;
   FILE *fptr;

   fptr = fopen("/sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq", "r");

    // read the cpu file
   fscanf(fptr,"%lf", &cpu);

  printf("\n Cpu freq\033[0m : %.f GHz\n",(cpu/1000* 0.100*0.1*0.1));
  fclose(fptr);

}

void memory()
{

  rand_colors(0);
  struct sysinfo sys_info;

  if(sysinfo(&sys_info) != 0)
    perror("sysinfo");
 long int total_ram=sys_info.totalram/1024/1024;
 long int free_ram=sys_info.freeram*10;
 long int justify_ram=free_ram/1024;
 long int calculate_ram=justify_ram/1024;
 long int available_ram=(total_ram-calculate_ram);
 long int ram_percentage=(available_ram*100/total_ram);

  printf(" Memory\033[0m : %ldMib / %ldMib (%ld%%)\n", available_ram, total_ram, ram_percentage);
}

void disk()
{
  rand_colors(0);
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

printf(" Disk space\033[0m : %.1fG / %.1fG (%lu%%)\n", used, disk, (long)percent);
remove("space1024.db");
}
else {                                                                      printf("Couldn't get file system statistics\n");
}

}

void uptime()
{

  rand_colors(0);
  struct sysinfo sys_info;

  int days, hours, mins, x = 1;

  if(sysinfo(&sys_info) != 0)
   perror("sysinfo");

  days = sys_info.uptime / 86400;
  hours = (sys_info.uptime / 3600) - (days * 24);
  mins = (sys_info.uptime / 60) - (days * 1440) - (hours * 60);

  printf(" Uptime\033[0m : %d days, %d hours, %d minutes\n",
  days, hours, mins);
}

void term_size()
{

  rand_colors(0);
   struct winsize w;
   ioctl(0, TIOCGWINSZ, &w);

  printf(" Term size\033[0m : %dx%d\n", w.ws_row, w.ws_col);

}


void root()
{

  rand_colors(0);
  int real = getuid();
  int euid = geteuid();

  if ( real == 0 )
  {
    printf(" Su user\033[0m : (root user)\n");
  }
  else if ( euid == 0 )
  {
    printf(" Su user\033[0m : (root user)\n");
  }

  else
  {
  printf(" Su user\033[0m : non (root user)\n");
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

void help()
{
  printf
    (
     "Androfetch is a CLI system information tool written in C.\n\n"
     "default  : \e[92mandrofetch\e[0m\n"
     "argument : \e[92mandrofetch --stdout\e[0m\n"
     "argument : \e[92mandrofetch --compact\e[0m\n"
    );
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

  else if(argc > 1 && (strcmp(argv[1],"--help") == 0))
  {
    help();
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

