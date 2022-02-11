#include <dpp/dpp.h>
#include <iostream>
#include <utility>
#include "main.h"

int main() {
    // Start the program
    dpp::cluster bot(getToken());

    bot.on_ready([&bot](const auto &event) {
        std::cout << "Logged in as " << bot.me.username << "!\n";
    });

    /* Create command handler, and specify prefixes */
    dpp::commandhandler command_handler(&bot);
    /* Specifying a prefix of "/" tells the command handler it should also expect slash commands */
    command_handler.add_prefix("B%^");

    bot.on_ready([&command_handler](const dpp::ready_t &event) {
        command_handler.add_command("ping", {},
            [&command_handler](const std::string &command, const dpp::parameter_list_t &parameters, dpp::command_source src) {
                std::string got_param;
                if (!parameters.empty()) {
                    got_param = std::get<std::string>(parameters[0].second);
                }
                command_handler.reply(dpp::message("Pong! -> " + got_param), std::move(src));
            },
            "A test ping command",
            148195924567392257
        );

        /**
         * NOTE: We must call this to ensure slash commands are registered.
         * This does a bulk register, which will replace other commands
         * that are registered already!
         */
        command_handler.register_commands();

    });

    bot.start(false);
    return 0;
}

std::string getToken() {
    // Open the config.txt file with C++ and read it
    FILE *fp = fopen("config.txt", "r");
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
    char *token = strtok(nullptr, "=");
    // Return the token
    return token;
}