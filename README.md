# s10-3c-keyboard-on-freebsd

Enable lenovo s10-3c's keyboard on FreeBSD/Linux

> The BIOS of Lenovo netbook *s10-3c* is weird, so, after i installed linux or freebsd on it, the keyboard just DOESN'T work.
Solutions are below.
------
### 1. Make sure you have gcc in your system
If not, try this:

On *FreeBSD*, use 
```
# pkg install gcc
```
On *Ubuntu/Debian*, use 
```
# apt-get install gcc
```
On *openSUSE*, use 
```
# zypper in gcc
```

### 2. Save the code to a file
Use your text editor to open a file:

On *FreeBSD*, use `% ee keyboard.c`
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

On *Linux*, use `$ vim keyboard.c`      
and paste the code to the editor:  

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

Then, save the source file.

### 3. Compile the code
Use gcc to compile the code:
```
# gcc keyboard.c -o enable-keyboard
```
If it works fine we can find a file `enable-keyboard`in the current directory. 
Bofore wo use it, we need to fix the permission:
```
# chmod +x enable-keyboard
```

### 4.Use the code
We can test the code to make sure it works, input in CLI:
```
# ./enable-keyboard
```
After doing this, the keyborad of s10-3c finally works!
But if we reboot the system, it doesn't work anymore until we run the code again.
So we need to run the code during startup:
* Move the file to an appropriate directory, for example,
```
# mv enable-keyboard /usr/bin
```
* Add to system startup process, for example,
```
# cd /etc/rc.d
# vi enalbe_keyboard
```
add these lines to the file:

      #!/bin/sh
      /usr/bin/enable-keyboard
 
 and fix the permission:
 ```
 # chmod +x enable_keyboard
 ```
Then, reboot your system and every is done.

------

> Reference links:
> (http:://help.ubuntu.ru/%D1%81%D0%BE%D0%B2%D0%BC%D0%B5%D1%81%D1%82%D0%B8%D0%BC%D0%BE%D1%81%D1%82%D1%8C/s10-3c#%D0%BA%D0%BB%D0%B0%D0%B2%D0%B8%D0%B0%D1%82%D1%83%D1%80%D0%B0)
> 











