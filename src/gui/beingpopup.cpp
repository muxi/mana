/*
 *  The Mana Client
 *  Copyright (C) 2010  The Mana Developers
 *
 *  This file is part of The Mana Client.
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
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gui/beingpopup.h"

#include "graphics.h"
#include "player.h"
#include "units.h"

#include "gui/gui.h"
#include "gui/palette.h"

#include "gui/widgets/textbox.h"

#include "utils/gettext.h"
#include "utils/stringutils.h"

#include <guichan/font.hpp>


BeingPopup::BeingPopup():
    Popup("BeingPopup")
{
    // Item Name
    mBeingName = new TextBox();
    mBeingName->setFont(boldFont);
    mBeingName->setPosition(getPadding(), getPadding());

    const int fontHeight = getFont()->getHeight();

    // Item Description
    mBeingParty = new TextBox();
    mBeingParty->setPosition(getPadding(), fontHeight);

    add(mBeingName);
    add(mBeingParty);

    loadPopupConfiguration();
}

BeingPopup::~BeingPopup()
{
}

void BeingPopup::show(int x, int y, Player *p)
{
    if (!p)
    {
        setVisible(false);
        return;
    }

    if (!(p->getPartyName().empty()))
    {
        mBeingName->setTextWrapped(p->getName(), 196);
        mBeingParty->setTextWrapped(strprintf(_("Party: %s"),
                                        p->getPartyName().c_str()), 196);

        int minWidth = std::max(mBeingName->getMinWidth(),
                                mBeingParty->getMinWidth());

        const int height = getFont()->getHeight();

        setContentSize(minWidth + 10, (height * 2) + 10);

        position(x, y);
        return;
    }

    setVisible(false);
}

gcn::Color BeingPopup::getColor()
{
    return guiPalette->getColor(Palette::GENERIC);
}