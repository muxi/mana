/*
 *  The Mana World
 *  Copyright (C) 2008  The Mana World Development Team
 *
 *  This file is part of The Mana World.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <string>

class ChatTab;

extern ChatTab *localChatTab;

/**
 * A class to parse and handle user commands
 */
class CommandHandler
{
    public:
        /**
         * Constructor
         */
        CommandHandler();

        /**
         * Destructor
         */
        ~CommandHandler() {}

        /**
         * Parse and handle the given command.
         */
        void handleCommand(const std::string &command, ChatTab *tab = localChatTab);

    private:
        /**
         * Handle an announce command.
         */
        void handleAnnounce(const std::string &args, ChatTab *tab);

        /**
         * Handle a help command.
         */
        void handleHelp(const std::string &args, ChatTab *tab);

        /**
         * Handle a where command.
         */
        void handleWhere(const std::string &args, ChatTab *tab);

        /**
         * Handle a who command.
         */
        void handleWho(const std::string &args, ChatTab *tab);

        /**
         * Handle a msg command.
         */
        void handleMsg(const std::string &args, ChatTab *tab);

        /**
         * Handle a join command.
         */
        void handleJoin(const std::string &args, ChatTab *tab);

        /**
         * Handle a listchannels command.
         */
        void handleListChannels(const std::string &args, ChatTab *tab);

        /**
         * Handle a listusers command.
         */
        void handleListUsers(const std::string &args, ChatTab *tab);

        /**
         * Handle a topic command.
         */
        void handleTopic(const std::string &args, ChatTab *tab);

        /**
         * Handle a quit command.
         */
        void handleQuit(const std::string &args, ChatTab *tab);

        /**
         * Handle a clear command.
         */
        void handleClear(const std::string &args, ChatTab *tab);

        /**
         * Handle a party command.
         */
        void handleParty(const std::string &args, ChatTab *tab);

        /**
         * Handle a op command.
         */
        void handleOp(const std::string &args, ChatTab *tab);

        /**
         * Handle a kick command.
         */
        void handleKick(const std::string &args, ChatTab *tab);

        /**
         * Handle a me command.
         */
        void handleMe(const std::string &args, ChatTab *tab);

        /**
         * Handle a record command.
         */
        void handleRecord(const std::string &args, ChatTab *tab);

        /**
         * Handle a toggle command.
         */
        void handleToggle(const std::string &args, ChatTab *tab);

        /**
         * Handle a present command.
         */
        void handlePresent(const std::string &args, ChatTab *tab);
};

extern CommandHandler *commandHandler;

#endif // COMMANDHANDLER_H