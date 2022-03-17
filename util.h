struct Config{
    char password_hash[100] ;
    char programs[100][100]; 
    int no_of_programs;
};

int is_in_blocklist(char *cmdline, struct Config *c);

void lock_app(int, char *password_hash);
void read_config_file(struct Config *c);