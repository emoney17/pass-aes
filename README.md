## SafePass
**NOTE: This is just a demo. If you wish to use it seriously then I advise you to edit the code and move the important files (*.aes) to a better location, move the temp, etc.**
**Also, this program works but it is still a work in progress**
### Requirements
[Cryptopp](https://github.com/weidai11/cryptopp)

If you need help installing the library check out the [Wiki](https://www.cryptopp.com/wiki/Linux#Build_and_Install_the_Library)
### Build and Init
To build this program simply clone the repo, cd into it and run make
You should also use the ```--init``` command to generate all the necessary files and directories
You can do all of this by copying and pasting this into your terminal
 ```bash
 git clone https://github.com/emoney17/safepass.git
 cd safepass
 make
 ./safepass --init
 ```
### Usage
This password manager is my interpretation of [pass](https://www.passwordstore.org/).
It will generate a directory for you to store all of your passwords and seperate them by subject. Each subject will be a directory and the file is the name of the actual website/program you will be using the password for. The password will encrypted using AES-128 and stored in the file. To view any password you will used the "-v/--view" and enter the subject and entry. This will print out a decrypted password for you to copy.
### Commands
```bash
$ ./safepass -h
A CLI password manager!
Usage: ./safepass [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -i,--init                   First time users generate necessary files
  -v,--view TEXT              View all entries with 'all' or a specific entry with 'Subject/Entry'
  -g,--generate INT           Generate a password when adding an entry and pick the length
  -s,--nosymbols              Generate a password without special characters
  -a,--add TEXT               Add a new entry with the format 'Subject/Entry' and enter a password
  -r,--remove TEXT            Remove a 'Subject/' or a 'Subject/Entry'
```
### Example
```bash
$ ./safepass -a Personal/Shopping
Enter password for this entry: password123
Password: password123

$ ./safepass -a Personal/Email -g 30 -s

$ ./safepass -v all
temp
 ├── Personal
 │   ├── Email
 │   └── Shopping
 ├── School
 │   └── Email
 └── Work
     ├── Email
     └── Website

$ ./safepass -v Personal/Shopping
Recovered password: password123

$ ./safepass -v Personal/Email
Recovered password: Z5swY6721pw2ZbMD9vLes8eZ41Q2Ua
```
