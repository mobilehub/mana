/*
 *  The Mana World
 *  Copyright (C) 2004  The Mana World Development Team
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

#ifndef NPC_TEXT_H
#define NPC_TEXT_H

#include "gui/widgets/window.h"

#include "npc.h"

#include <guichan/actionlistener.hpp>

#include <string>

class TextBox;

/**
 * The npc text dialog.
 *
 * \ingroup Interface
 */
class NpcTextDialog : public Window, public gcn::ActionListener
{
    public:
        /**
         * Constructor.
         *
         * @see Window::Window
         */
        NpcTextDialog();

        /**
         * Called when receiving actions from the widgets.
         */
        void action(const gcn::ActionEvent &event);

        /**
         * Clears the text shown in the dialog.
         */
        void clearText();

        /**
         * Sets the text shows in the dialog.
         *
         * @param string The new text.
         */
        void setText(const std::string &string);

        /**
         * Adds the text to the text shows in the dialog. Also adds a newline
         * to the end.
         *
         * @param string The text to add.
         */
        void addText(const std::string &string);

        void showNextButton();

        void showCloseButton();

        /**
         * Notifies the server that the client has performed a next action.
         */
        void nextDialog(int npcID = current_npc);

        /**
         * Notifies the server that the client has performed a close action.
         */
        void closeDialog(int npcID = current_npc);

        /**
         * Called when resizing the window.
         *
         * @param event The calling event
         */
        void widgetResized(const gcn::Event &event);

    private:
        gcn::ScrollArea *mScrollArea;
        TextBox *mTextBox;
        gcn::Button *mButton;

        std::string mText;

        enum NPCTextState {
            NPC_TEXT_STATE_WAITING,
            NPC_TEXT_STATE_NEXT,
            NPC_TEXT_STATE_CLOSE
        };
        NPCTextState mState;
};

extern NpcTextDialog *npcTextDialog;

#endif // NPC_TEXT_H