## SafePass
**NOTE: This is not to be used seriously, its just a demo. If you wish to use it seriously then I advise you to edit the code and move the important files (*.aes) to a better location.
### Requirements
[Cryptopp](https://github.com/weidai11/cryptopp)
### Run
To run this program simply clone the repo, cd into it and run make
 ```
 git clone https://github.com/emoney17/safepass.git
 cd safepass
 make
 ```
### Usage
This password manager is my interpretation of [pass](https://www.passwordstore.org/).
It will generate a directory for you to store all of your passwords and seperate them by subject. Each subject will be a directory and the file is the name of the actual website/program you are using. The password will be stored in the file after going through AES-128 encryption. To view any password you will used the "-v/--view" and enter the subject and entry. This will print out a decrypted password for you to copy.
