#include <dpp/dpp.h>
#include <iostream>

std::string getToken() {
    // Open a file with C++ and read it
    FILE * fp = fopen("config.txt", "r");
    if (fp == nullptr) {
        printf("The file was not found.\n");
        exit(1);
    }
    // Get the first line
    char line[256];
    fgets(line, sizeof(line), fp);
    // Close the file
    fclose(fp);
    // get everything after the token=
    strtok(line, "=");
    char * token = strtok(nullptr, "=");
    // Return the token
    return token;
}

int main() {
    // Start the program
    dpp::cluster bot(getToken());

    bot.on_ready([&bot](const auto & event) {
        std::cout << "Logged in as " << bot.me.username << "!\n";
    });

    bot.on_message_create([&bot](const auto & event) {
        if (event.msg.content == "!ping") {
            bot.message_create(dpp::message(event.msg.channel_id, "Pong!"));
        }
    });

    bot.start(false);
    return 0;
}
