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

#include "gui/partywindow.h"

#include "gui/widgets/chattab.h"

#include "net/net.h"
#ifdef TMWSERV_SUPPORT
#include "net/tmwserv/chatserver/party.h"
#else
#include "net/ea/partyhandler.h"
#endif

#include "utils/gettext.h"
#include "utils/strprintf.h"

PartyWindow::PartyWindow() : Window(_("Party"))
{
    setWindowName("Party");
    setVisible(false);
    setResizable(false);
    setCaption(_("Party"));
    setCloseButton(true);
    setMinWidth(110);
    setMinHeight(200);
    setDefaultSize(620, 300, 110, 200);

    loadWindowState();
}

PartyWindow::~PartyWindow()
{
    mMembers.clear();
}

void PartyWindow::draw(gcn::Graphics *graphics)
{
    Window::draw(graphics);
}

PartyMember *PartyWindow::findMember2(int id)
{
    PartyMember *member = findMember(id);

    if (!member)
    {
        member = new PartyMember;
        member->avatar = new Avatar("");
        add(member->avatar, 0, (mMembers.size() - 1) * 14);
        mMembers[id] = member;
    }

    return member;
}

int PartyWindow::findMember(const std::string &name)
{
    PartyList::iterator itr = mMembers.begin(),
                        itr_end = mMembers.end();

    while (itr != itr_end)
    {
        if ((*itr).second->name == name)
        {
            return (*itr).first;
        }
        ++itr;
    }

    return -1;
}

void PartyWindow::updateMember(int id, const std::string &memberName,
                                 bool leader, bool online)
{
    // create new party member
    PartyMember *player = findMember2(id);
    player->id = id;
    player->name = memberName;
    player->leader = leader;
    player->online = online;
    player->avatar->setName(memberName);
    player->avatar->setOnline(online);

    // show the window
    if (mMembers.size() > 0)
    {
        setVisible(true);
    }
}

void PartyWindow::removeMember(int id)
{
    mMembers.erase(id);

    // if no-one left, remove the party window
    if (mMembers.size() < 1)
    {
        setVisible(false);
    }
}

void PartyWindow::removeMember(const std::string &name)
{
    removeMember(findMember(name));
}

void PartyWindow::updateOnlne(int id, bool online)
{
    PartyMember *player = findMember(id);

    if (!player)
        return;

    player->online = online;
    player->avatar->setOnline(online);
}

void PartyWindow::showPartyInvite(const std::string &inviter,
                                  const std::string &partyName)
{
    // check there isnt already an invite showing
    if (mPartyInviter != "")
    {
        localChatTab->chatLog("Received party request, but one already exists",
                            BY_SERVER);
        return;
    }

    std::string msg;
    // log invite
    if (partyName.empty())
        msg = strprintf("%s has invited you to join their party",
                                    inviter.c_str());
    else
        msg = strprintf("%s has invited you to join the %s party",
                                    inviter.c_str(), partyName.c_str());

    localChatTab->chatLog(msg, BY_SERVER);

    // show invite
    acceptDialog = new ConfirmDialog("Accept Party Invite", msg, this);
    acceptDialog->addActionListener(this);

    mPartyInviter = inviter;
}

void PartyWindow::action(const gcn::ActionEvent &event)
{
    const std::string &eventId = event.getId();

    // check if they accepted the invite
    if (eventId == "yes")
    {
        localChatTab->chatLog("Accepted invite from " + mPartyInviter);
        // Net::getPartyHandler()->inviteResponse(true);
#ifdef TMWSERV_SUPPORT
        Net::ChatServer::Party::acceptInvite(mPartyInviter);
#else
        partyHandler->inviteResponse(true);
#endif
        mPartyInviter = "";
    }
    else if (eventId == "no")
    {
        localChatTab->chatLog("Rejected invite from " + mPartyInviter);
        // Net::getPartyHandler()->inviteResponse(false);
#ifdef TMWSERV_SUPPORT
        // TODO
#else
        partyHandler->inviteResponse(false);
#endif
        mPartyInviter = "";
    }
}