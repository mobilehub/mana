/*
 *  The Mana Client
 *  Copyright (c) 2009  Aethyra Development Team 
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

#include "gui/widgets/label.h"

#include "resources/theme.h"

Label::Label()
{
    setForegroundColor(Theme::getThemeColor(Theme::TEXT));
}

Label::Label(const std::string &caption) :
    gcn::Label(caption)
{
    setForegroundColor(Theme::getThemeColor(Theme::TEXT));
}

void Label::draw(gcn::Graphics *graphics)
{
    gcn::Label::draw(static_cast<gcn::Graphics*>(graphics));
}
