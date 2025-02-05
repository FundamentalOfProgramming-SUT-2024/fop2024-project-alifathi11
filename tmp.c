#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <time.h>

void insert_random_players(sqlite3 *db) {
    const char *sql = "INSERT INTO players (username, email, password, score, gold, finished_games, last_game_exists, last_game_last_level) "
                      "VALUES (?, ?, ?, ?, ?, ?, ?, ?);";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        return;
    }

    srand(time(NULL)); // Seed random number generator

    for (int i = 0; i < 40; i++) {
        char username[20], email[30], password[15];
        sprintf(username, "User%d", rand() % 10000);
        sprintf(email, "user%d@example.com", rand() % 10000);
        sprintf(password, "pass%d", rand() % 10000);

        int score = rand() % 1000;
        int gold = rand() % 500;
        int finished_games = rand() % 50;
        int last_game_exists = rand() % 2;
        int last_game_last_level = rand() % 20;

        // Bind parameters
        sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, email, -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, password, -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 4, score);
        sqlite3_bind_int(stmt, 5, gold);
        sqlite3_bind_int(stmt, 6, finished_games);
        sqlite3_bind_int(stmt, 7, last_game_exists);
        sqlite3_bind_int(stmt, 8, last_game_last_level);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            printf("Error inserting player: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_reset(stmt); // Reset statement for next execution
    }

    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open("players.db", &db) != SQLITE_OK) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    insert_random_players(db);
    
    sqlite3_close(db);
    return 0;
}
