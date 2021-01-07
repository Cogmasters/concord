#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <liborca.h>

int main(void)
{
    FILE *f_bot_token = fopen("bot_token","rb");
    assert(NULL != f_bot_token);

    char bot_token[100];
    fgets(bot_token, 99, f_bot_token);
    fclose(f_bot_token);

    orca_global_init();
    orca_t *client = orca_init(bot_token);
    assert(NULL != client);

    orca_user_t *user = orca_user_init(); 
    assert(NULL != user);

    orca_get_client(client, &user);
    printf("Greetings, %s#%s!\n", user->username, user->discriminator);

    orca_user_cleanup(user);

    orca_cleanup(client);
    orca_global_cleanup();
}
