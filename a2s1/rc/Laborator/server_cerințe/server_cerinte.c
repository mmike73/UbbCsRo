#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netinet/ip.h>

#include <string.h>
#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <signal.h>

void handle_sigchld(int sig) {
    // Wait for all dead processes.
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

FILE *open_random_file(const char* directory) {
    DIR *dir;
    struct dirent *entry;

    char **file_names = NULL;
    int file_count = 0;
    FILE *file = NULL;

    dir = opendir(directory);
    if (dir == NULL) {
        perror("Unable to open directory");
        return NULL;
    }

    srand(time(NULL));

    while ((entry = readdir(dir)) != NULL) {
        printf("Found entry: %s, type: %d\n", entry->d_name, entry->d_type);
        char file_path[1024];
        snprintf(file_path, sizeof(file_path), "%s/%s", directory, entry->d_name);

        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Try opening the file to verify it's a readable regular file
        FILE *test_file = fopen(file_path, "r");
            if (test_file != NULL) {
                fclose(test_file);  // It's a regular readable file

                file_names = realloc(file_names, sizeof(char*) * (file_count + 1));
                if (file_names == NULL) {
                    perror("Failed to allocate memory for file names");
                    closedir(dir);
                    return NULL;
                }
                
                file_names[file_count] = strdup(entry->d_name);
                if (file_names[file_count] == NULL) {
                    perror("Failed to duplicate file name");
                    closedir(dir);
                    return NULL;
                }
                
                file_count++;
            }
    }

    if (file_count == 0) {
        fprintf(stderr, "No files found in the directory\n");
        closedir(dir);
        return NULL;
    }

    int random_index = rand() % file_count;
    char file_path[1024];
    snprintf(file_path, sizeof(file_path), "%s/%s", directory, file_names[random_index]);

    file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Unable to open file");
    }

    for (int i = 0; i < file_count; ++i) {
        free(file_names[i]);
    }
    free(file_names);
    closedir(dir);

    return file;
}

void handle_client(int c) {
    const char *dir = "/home/deb/lab/server_cerințe/probleme";

    FILE* fd = open_random_file(dir);
    if (fd == NULL) {
        close(c);
        return;
    }

    char* buff = malloc(10001);
    if (buff == NULL) {
        perror("Memory allocation failed for buffer");
        fclose(fd);
        close(c);
        return;
    }

    if (fgets(buff, 10000, fd) == NULL) {
        fprintf(stderr, "Failed to read content from file\n");
        free(buff);
        fclose(fd);
        close(c);
        return;
    }
    fclose(fd);

    uint16_t l = strlen(buff);
    buff[l] = '\0'; // Ensure null-termination
    l = htons(l);

    if (send(c, &l, sizeof(l), 0) == -1) {
        perror("Failed to send length to client");
        free(buff);
        close(c);
        return;
    }
    
    if (send(c, buff, ntohs(l), 0) == -1) {
        perror("Failed to send buffer to client");
    }

    free(buff);
    close(c);
}

int main() {
    signal(SIGCHLD, handle_sigchld); // Prevent zombie processes

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Error creating server socket");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(54321);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Error binding server socket");
        return 1;
    }

    listen(s, 5);

    struct sockaddr_in client;
    socklen_t client_len = sizeof(client);
    memset(&client, 0, sizeof(client));

    while (1) {
        int c = accept(s, (struct sockaddr *) &client, &client_len);
        if (c < 0) {
            perror("Failed to accept client connection");
            continue;
        }

        printf("Client connected.\n");

        if (fork() == 0) {
            close(s); // Child process should close the listening socket
            handle_client(c);
            exit(0);
        }

        close(c); // Parent process closes the connected socket
    }
}
