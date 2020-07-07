This is my encryped cloud project.

I call is fog, because fog is like a cloud, but you can't see 
anything. Get it? Its funny. 

Fog is a cloud storage system like dropbox or drive however 
it will use client side encrpytion. 
No keys or encryption will be done on the sever. I was 
influenced how git works, however each file is synced on the 
client side separtely at the discretion of the user. Unlike a 
git pull which will update the entire repo, you can make a 
downpour of speific files. Think of it just scp'ing files but
before an upload, the file is encrypted and after a download 
the file is decrypted.

Since this is made more for my own personal use, space 
optimaization is not really going to be a factor. I suppose I 
could eventually perform an inplace encption/deccrption but I 
don't want to focus on that atm.

The only plaintext (although I may runtime to make it 
encrypted) information on the server should be file and 
folder names. This will make scp'ing them easier, although I 
may just use a hash on the names.

commands
  forecast, remote --will list the files stored on the server
  predict, local -- will list files that are not uploaded yet
  clear, push -- will encrypt then upload the following files
              -r will upload a directory
  rain, pull -- will download the files or folder then decrypt
  sync -- will encrypt then upload all files not on cloud yet
        -f flag -- will also download then decrypt everything
                   not found locally.
  list --will list all the files stored on server and all
         files found locally with markings on things found on
         one and not the other
  configre --will run the setup script. Since this works by 
             accesing a server you need to provide a few bits
             of information. It will make the current directory
             a fog repository.

Setup

Run the configure command and automated setup will begin. 
There are two modes you can fun fog in: secure mode or trusted
mode.
  Secure Mode -You enter your username or password   
               or both each time you send or recieve
               a file
  Trusted Mode -No user authentication is needed
                after first time setup.
The configure script will ask for the following information
  Domain or IP address of server
  path to ssh key (can leave blank if NA)

If using trusted mode, the following will aslo be prompted
  password for ssh key (or user is key is blank)
  Username: username for the user on server (if applicable)
