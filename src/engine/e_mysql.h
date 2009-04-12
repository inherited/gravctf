#ifndef MYSQL_H
#define MYSQL_H

char *mysql_get_destination_from_id(char *source, int id);
int mysql_is_server_active(char *dest);
void mysql_update_player_location(const char *username, char *dest);

#endif
