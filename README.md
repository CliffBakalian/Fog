# FOG

This is my pre-cloud encryption project.  

What that means is when you upload a file to Google drive, 
or to dropbox or some other place, you are sending your data to a server which
will decrypt the end-to-end encryption and store your files on *someone else's* 
server in plaintext. I do not like that. So why not encrypt everything before 
you send it, and then decrypt everything when you recieve it? That way, Google 
or Dropbox or whatever service you are using cannot see your files.  

I call is Fog, because fog is like a cloud, but you can't see 
anything. Get it? Its funny. 

Fog is a pre-cloud storage system and it will use client side encrpytion. 
No keys or encryption will be done on the sever. I was 
influenced how git works, however each file is synced on the 
client side separtely at the discretion of the user. Unlike a 
git pull which will update the entire repo, you can make a 
downpour of speific files. Think of it just scp'ing files but
before an upload, the file is encrypted and after a download 
the file is decrypted.
## Resources

I will be using libgcrypt for my encrpytion and libssh2 for my ssh/scp activities.

## Background 
Since this is made more for my own personal use, space 
optimaization is not really going to be a factor. I suppose I 
could eventually perform an inplace encption/deccrption but I 
don't want to focus on that. Additonally, I use linux webservers to store my 
data so I will be focusing on using the SCP protocol. I suppose I could later 
I could work on integration with Google Drive or dropbox or other services.
Though that might just mean, me writing a program to encrypt a file and then 
having the user upload that encrpyted file.  

## The Process

Its really a simple process.  
##### Uploading  
+ Take the file and encrypt the file using whatever key you passed in
+ Upload 

##### Downloading
+ Download the requested file
+ Decrypt it

I plan on having no plain text on the server. This means that Fog will map file
names to hash names. Unfortunately I do not know how I could obfuscate folder 
structure.  

commands  
```
  predict  : will list files that are not uploaded yet  
  clear    : will encrypt then upload the following files  
               -r will upload a directory  
  rain     : will download the following files or folder then decrypt  
  downpour : will encrypt then upload all files not on cloud yet and also will 
             download then decrypt everything not found locally.
  list     : will list all the files stored on server and all files found 
             locally with markings on things found on one and not the other
  configure : will run the setup script. Since this works by accesing a server 
             you need to provide a few bits of information. It will make the 
             current directory a Fog repository.
```
Setup

Run the configure command and automated setup will begin. 
There are two modes you can fun Fog in: secure mode or trusted
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
  password for ssh key (can be left blank if NA) (Warning, will be stored in plaintext)
  Username: username for the user on server 
