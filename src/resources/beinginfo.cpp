/*
 *  The Mana Client
 *  Copyright (C) 2004-2009  The Mana World Development Team
 *  Copyright (C) 2009-2010  The Mana Developers
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

#include "resources/beinginfo.h"

#include "log.h"

#include "utils/dtor.h"
#include "utils/gettext.h"

BeingInfo *BeingInfo::Unknown = new BeingInfo;

BeingInfo::BeingInfo():
        mName(_("unnamed")),
        mTargetCursorSize(ActorSprite::TC_MEDIUM),
        mWalkMask(Map::BLOCKMASK_WALL | Map::BLOCKMASK_CHARACTER
                  | Map::BLOCKMASK_MONSTER),
        mBlockType(Map::BLOCKTYPE_CHARACTER)
{
    SpriteDisplay display;
    display.sprites.push_back(SpriteReference::Empty);

    setDisplay(display);
}

BeingInfo::~BeingInfo()
{
    delete_all(mSounds);
    delete_all(mAttacks);
    mSounds.clear();
}

void BeingInfo::setDisplay(SpriteDisplay display)
{
    mDisplay = display;
}

void BeingInfo::setTargetCursorSize(const std::string &size)
{
    if (size == "small")
        setTargetCursorSize(ActorSprite::TC_SMALL);
    else if (size == "medium")
        setTargetCursorSize(ActorSprite::TC_MEDIUM);
    else if (size == "large")
        setTargetCursorSize(ActorSprite::TC_LARGE);
    else
    {
        logger->log("Unknown target cursor type \"%s\" for %s - using medium "
                    "sized one", size.c_str(), getName().c_str());
        setTargetCursorSize(ActorSprite::TC_MEDIUM);
    }
}

void BeingInfo::addSound(SoundEvent event, const std::string &filename)
{
    if (mSounds.find(event) == mSounds.end())
    {
        mSounds[event] = new std::vector<std::string>;
    }

    mSounds[event]->push_back("sfx/" + filename);
}

const std::string &BeingInfo::getSound(SoundEvent event) const
{
    static std::string empty("");

    SoundEvents::const_iterator i = mSounds.find(event);
    return (i == mSounds.end()) ? empty :
                                  i->second->at(rand() % i->second->size());
}

const Attack *BeingInfo::getAttack(int id) const
{
    static Attack *empty = new Attack(SpriteAction::ATTACK, -1, std::string());

    Attacks::const_iterator i = mAttacks.find(id);
    return (i == mAttacks.end()) ? empty : (*i).second;
}

void BeingInfo::addAttack(int id, std::string action, int effectId,
                          const std::string &missileParticleFilename)
{
    if (mAttacks[id])
        delete mAttacks[id];

    mAttacks[id] = new Attack(action, effectId, missileParticleFilename);
}
