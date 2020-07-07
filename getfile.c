#include "libssh2_config.h"
#include <libssh2.h>
#include "getfile.h"

#ifdef HAVE_WINSOCK2_H
# include <winsock2.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
# ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef HAVE_ARPA_INET_H
# include <arpa/inet.h>
#endif
#ifdef HAVE_SYS_TIME_H
# include <sys/time.h>
#endif

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>

int get_file(Config config, const char *filename){
    int sock, i, auth_pw = 1;
    struct sockaddr_in sin;
    const char *fingerprint;
    FILE *fp = fopen("testing.txt", "ab+");
    LIBSSH2_SESSION *session;
    LIBSSH2_CHANNEL *channel;
    libssh2_struct_stat fileinfo;
    int rc;
    libssh2_struct_stat_size got = 0;

#ifdef WIN32
    WSADATA wsadata;
    int err;
    err = WSAStartup(MAKEWORD(2, 0), &wsadata);
    if(err != 0) {
        fprintf(stderr, "WSAStartup failed with error: %d\n", err);
        return 1;
    }
#endif
    rc = libssh2_init(0);
    if(rc) {
        fprintf(stderr, "libssh2 initialization failed (%d)\n", rc);
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);

    sin.sin_family = AF_INET;
    sin.sin_port = htons(22);
    sin.sin_addr.s_addr = inet_addr(hostaddr);
    if(connect(sock, (struct sockaddr*)(&sin),
               sizeof(struct sockaddr_in)) != 0) {
        fprintf(stderr, "failed to connect!\n");
        return -1;
    }

    session = libssh2_session_init();
    if(!session)
        return -1;

    rc = libssh2_session_handshake(session, sock);
    if(rc) {
        fprintf(stderr, "Failure establishing SSH session: %d\n", rc);
        return -1;
    }

    fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);
    fprintf(stderr, "Fingerprint: ");
    for(i = 0; i < 20; i++) {
        fprintf(stderr, "%02X ", (unsigned char)fingerprint[i]);
    }
    fprintf(stderr, "\n");

    if(0) {
        if(libssh2_userauth_password(session, username, password)) {
            fprintf(stderr, "Authentication by password failed.\n");
            goto shutdown;
        }
    }
    else {
#define HOME_DIR "/home/HOME_DIR/"
        if(libssh2_userauth_publickey_fromfile(session, username,NULL,
            HOME_DIR ".ssh/PRIVATEKEY",NULL)) {
            fprintf(stderr, "\tAuthentication by public key failed\n");
            goto shutdown;
        }
    }

    /* Request a file via SCP */
    channel = libssh2_scp_recv2(session, scppath, &fileinfo);

    if(!channel) {
        fprintf(stderr, "Unable to open a session: %d\n",
                libssh2_session_last_errno(session));
        goto shutdown;
    }


    while(got < fileinfo.st_size) {
        char mem[1024];
        int amount = sizeof(mem);

        if((fileinfo.st_size -got) < amount) {
            amount = (int)(fileinfo.st_size -got);
        }

        rc = libssh2_channel_read(channel, mem, amount);
        if(rc > 0) {
            write(1, mem, rc);
            fwrite(mem, sizeof(char), rc, fp);
        }
        else if(rc < 0) {
            fprintf(stderr, "libssh2_channel_read() failed: %d\n", rc);
            break;
        }
        got += rc;
    }

    libssh2_channel_free(channel);
    channel = NULL;

 shutdown:

    libssh2_session_disconnect(session,
                               "Normal Shutdown, Thank you for playing");
    libssh2_session_free(session);

#ifdef WIN32
    closesocket(sock);
#else
    close(sock);
#endif
    fprintf(stderr, "all done\n");

    libssh2_exit();
    fclose(fp);
    return 0;
}
