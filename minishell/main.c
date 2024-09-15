#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include"libft/get_next_line_bonus.h"

#define MAIN_BUFFER_SIZE 1024
#define MAX_HEREDOC_SIZE 4096  // Tamaño máximo del contenido en memoria

void process_heredoc(const char *delimiter) {
    char *line;
    int fd_temp;
    char temp_filename[] = "/tmp/heredocXXXXXX";  // Nombre del archivo temporal
    int bytes_written;
    int bytes_read;
    char buffer[MAIN_BUFFER_SIZE];
    
    if (!delimiter) {
        fprintf(stderr, "Delimiter cannot be NULL\n");
        exit(EXIT_FAILURE);
    }

    // Crear un archivo temporal
    fd_temp = open(temp_filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd_temp == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Enter heredoc content (end with '%s'):\n", delimiter);

    while ((line = get_next_line(STDIN_FILENO))) {
        if (strncmp(line, delimiter, strlen(delimiter)) == 0 &&
            (line[strlen(delimiter)] == '\n' || line[strlen(delimiter)] == '\0')) {
            free(line);
            break;
        }

        // Escribir la línea en el archivo
        bytes_written = write(fd_temp, line, strlen(line));
        if (bytes_written == -1) {
            perror("write");
            close(fd_temp);
            exit(EXIT_FAILURE);
        }

        free(line);
    }

    close(fd_temp);  // Cerrar el archivo temporal

    // Abrir el archivo temporal para lectura
    fd_temp = open(temp_filename, O_RDONLY);
    if (fd_temp == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Leer y mostrar el contenido del heredoc
    printf("\nHeredoc content:\n");
    while ((bytes_read = read(fd_temp, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("read");
    }

    close(fd_temp);  // Cerrar el archivo temporal

    // Eliminar el archivo temporal
    if (unlink(temp_filename) == -1) {
        perror("unlink");
    }
}

int main() {
    char *delimiter = "EOF";

    process_heredoc(delimiter);

    return 0;
}
