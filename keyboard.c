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
