  #include <unistd.h>
  #include <sys/io.h>

  #define I8042_COMMAND_REG 0x64
  int main(int argc, char *argv[]) {
    char data = 0xae; // enable keyboard

    ioperm(I8042_COMMAND_REG, 1, 1);

    if (argc == 2 && argv[1][0] == '0')
      data = 0xad; // disable keyboard
    outb(data, I8042_COMMAND_REG);
    return 0;
  }
