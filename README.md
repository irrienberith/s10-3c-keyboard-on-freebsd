# s10-3c-keyboard-on-freebsd

Enable lenovo s10-3c's keyboard on FreeBSD /Linux


The bios of Lenovo netbook s10-3c is weird, so, after i installed linux or freebsd on it, the keyboard just DOESN'T work.
Solutions are below.

### 1. Make sure you have gcc in your system
if not ,try these:

on FreeBSD,`# pkg install gcc`

on Ubuntu/Debian,`# apt-get install gcc`

on openSUSE,`# zypper in gcc`

### 2. Use these code
use your text editor to open a file from `/home/yourusername`:

on FreeBSD,`% ee keyboard.c`
and paste the code to the editor:
    
      #include<unistd.h>
      #include<machine/cpufunc.h> //putb()
      #include<sys/cdefs.h>
      __FBSDID("$FreeBSD$");

      #include<machine/sysarch.h> //i386_set_ioperm
      #define I8042_COMMAND_REG 0x64
      int main(int argc, char *argv[]){
        char data = 0xae; //enable keyboard

        struct i386_ioperm_args p;
        p.start = I8042_COMMAND_REG;
        p.length = 1;
        p.enable = 1;

        sysarch(I386_SET_IOPERM, &p);

        if(argc == 2 && argv[1][0] == '0')
          data = 0xad; //disable keyboard
        outb(I8042_COMMAND_REG, data);

        return 0;
      }




on Linux,`$ vim keyboard.c`









