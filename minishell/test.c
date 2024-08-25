#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_color(const char *text, const char *color_code) {
    printf("%s%s\033[0m", color_code, text);
}

void print_passed() {
    print_color("PASSED\n", "\033[0;32m");
}

void print_failed() {
    print_color("FAILED\n", "\033[0;31m");
}

char* execute_system_shell(const char* command) {
    FILE *fp;
    char *result = malloc(1024);
    if (result == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen failed");
        exit(EXIT_FAILURE);
    }
    fgets(result, 1024, fp);
    pclose(fp);
    return result;
}

char* execute_custom_shell(const char* command) {
    char full_command[1024];
    snprintf(full_command, sizeof(full_command), "./minishell %s", command);
    return execute_system_shell(full_command);
}

void compare_results(const char* command) {
    char* result_system_shell = execute_system_shell(command);
    char* result_custom_shell = execute_custom_shell(command);

    printf("Testing command: %s\n", command);
    printf("System Shell Output: %s\n", result_system_shell);
    printf("Custom Shell Output: %s\n", result_custom_shell);

    if (strcmp(result_system_shell, result_custom_shell) == 0) {
        print_passed();
    } else {
        print_failed();
    }

    free(result_system_shell);
    free(result_custom_shell);
}

int main() {
    const char* commands[] = {
        "echo",
        "echo hola",
        "echo \"\"",
        "echo \"\" hola",
        "echo -n hola",
        "echo -n -n hola",
        "echo -n -nh -n hola",
        "echo -nnnnnnnnn hola",
        "echo $?hcudshfuewrf ew wr 4ew\"\"\"\"",
        "echo \"\"uhjkhnkj\"hjbmb\"'''' defdjhfkjb \"iujiouhj\"f'f'f'f'f''f'f'f'f'f'f'",
        "echo \"\"uhjkhnkj\"hjbmb\"'''' defdjhfkjb \"iujiouhj\"f'f'a'j'o''i'w'q''q",
        "echo \"\"aaaaaaaa\"bbbbb\"'''' ccccccccc \"dddddddd\"e'e'e",
        "echo \"ho   $USER\"  'la   $LESS'   $USER$TERM",
        "echo \"ho   $USER\"'la   $LESS'$USER$TERM",
        "echo\"ho   $USER\"",
        "echo\"ho   $USE$LESS\"",
        "\"echo ho   $USER\"",
        "\"echo\" \"ho   $USER\"",
        "e\"cho\" \"ho   $USER\"",
        "echo \"ho   $USER\"",
        "echo \"$HOME '$LESS' $USER\"",
        "echo '$HOME \"$LESS\" $USER'",
        "echo \"$HOME '$LESS \"pa $TERM\" na' $USER\"",
        "echo '$HOME \"$LESS 'pa $TERM' na\" $USER'",
        "echo '$'\"HOME\"",
        "export a=b",
        "export b=wawa",
        "export b=lala",
        "export c=lala=kaka",
        "export a",
        "export a=",
        "export a= b=o",
        "export a===",
        "export a3=l",
        "export 2a=lala",
        "export !a=ma",
        "export $USER=la",
        "export $USER=$TERM",
        "export $USER=$TERM$HOME",
        "export $USER=$TERM$HOM",
        "export $HOME=$USER",
        "export $USER$SHLVL",
        "export",
        "export \"\"",
        "export a b=$LESS $USER $HOME=la $COLORTERM=pa c=d",
        "cd /tmp",
        "cd nonexistentdir",
        "cd existingfile",
        "cd",
        "cd -",
        "cd ~",
        "unset HOME; cd $HOME",
        "cd /dir_with_permissions",
        "env",
        "env lalal",
        "env /directory",
        "pwd",
        "unset HOME; pwd",
        "unset a",
        "unset a b c",
        "exit",
        "exit 0",
        "exit 1",
        "exit 42",
        "exit lalal",
        "ls | wc",
        "ls|wc",
        "sort colors.txt | uniq | sort -r | wc",
        "ls || wc",
        "ls |   | wc",
        "ls |   >/>>/</<< wc",
        "ls | wc |",
        "| ls | wc",
        "echo hola >>>>>>> file",
        "echo hola <<<<<<< file",
        "echo hola > file",
        "echo hola </<</>/>>   </<</>/>> file",
        "echo hola </<</>/>>   | file",
        "echo hola > file </<</>/>>",
        "echo hola > file > file2 > file3",
        "echo hola > file > file2 > file3 | ls",
        "wc < colors.txt",
        "wc < colors.txt > file",
        "cat colors.txt | wc",
        "echo hola > file << EOF",
        "cat << EOF > file",
        "<< EOF",
        "cat << hola << que << tal",
        "cat << hola << que << tal -> aplicarle señales a heredoc",
        "cat << EOF | ls",
        "echo hola | cat | cat | cat | cat | cat | cat | cat",
        "echo $?",
        "unset PATH; ls; /bin/ls",
        "unset HOME; cd"
    };

    int num_tests = sizeof(commands) / sizeof(commands[0]);

    for (int i = 0; i < num_tests; i++) {
        compare_results(commands[i]);
    }

    return 0;
}
