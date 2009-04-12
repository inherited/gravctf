#ifndef MYSQL_H
#define MYSQL_H

#ifdef __cplusplus
extern "C" {
#endif

const char *mysql_get_destination_from_id(const char *source, int id);
int mysql_is_server_active(const char *dest);
void mysql_update_player_location(const char *username, const char *dest);

#ifdef __cplusplus
}
#endif
#endif
