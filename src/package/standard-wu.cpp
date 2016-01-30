/********************************************************************
    Copyright (c) 2013-2015 - Mogara

    This file is part of QSanguosha.

    This game engine is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 3.0
    of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

    See the LICENSE file for more details.

    Mogara
*********************************************************************/

#include "card.h"
#include "gamelogic.h"
#include "general.h"
#include "serverplayer.h"
#include "skill.h"
#include "standardpackage.h"
#include "standard-trickcard.h"
#include "structs.h"

namespace {

class Zhiheng : public ProactiveSkill
{
public:
    Zhiheng() : ProactiveSkill("zhiheng")
    {
    }

    bool isAvailable(const Player *self, const QString &pattern) const override
    {
        return ProactiveSkill::isAvailable(self, pattern) && self->skillHistory(this) <= 0;
    }

    bool cardFilter(const QList<const Card *> &, const Card *, const Player *, const QString &) const override
    {
        return true;
    }

    bool cardFeasible(const QList<const Card *> &selected, const Player *) const override
    {
        return selected.length() > 0;
    }

    bool playerFilter(const QList<const Player *> &, const Player *, const Player *) const override
    {
        return false;
    }

    bool playerFeasible(const QList<const Player *> &selected, const Player *) const override
    {
        return selected.isEmpty();
    }

    void effect(GameLogic *logic, ServerPlayer *from, const QList<ServerPlayer *> &, const QList<Card *> &cards) const override
    {
        CardsMoveStruct move;
        move.cards = cards;
        move.to.type = CardArea::DiscardPile;
        move.isOpen = true;
        logic->moveCards(move);

        from->drawCards(cards.length());
    }
};

class Qixi : public OneCardViewAsSkill
{
public:
    Qixi() : OneCardViewAsSkill("qixi")
    {
    }

    bool viewFilter(const Card *card, const Player *, const QString &) const override
    {
        return card->color() == Card::Black;
    }

    Card *viewAs(Card *card, const Player *) const override
    {
        Dismantlement *dismantlement = new Dismantlement(card->suit(), card->number());
        dismantlement->addSubcard(card);
        dismantlement->setSkill(this);
        return dismantlement;
    }
};

}

void StandardPackage::addWuGenerals()
{
    //WU 001
    General *sunquan = new General("sunquan", "wu", 4);
    sunquan->setLord(true);
    sunquan->addSkill(new Zhiheng);
    addGeneral(sunquan);

    //WU 002
    General *ganning = new General("ganning", "wu", 4);
    ganning->addSkill(new Qixi);
    addGeneral(ganning);

    //WU 003
    General *lvmeng = new General("lvmeng", "wu", 4);
    addGeneral(lvmeng);

    //WU 004
    General *huanggai = new General("huanggai", "wu", 4);
    addGeneral(huanggai);

    //WU 005
    General *zhouyu = new General("zhouyu", "wu", 3);
    addGeneral(zhouyu);

    //WU 006
    General *daqiao = new General("daqiao", "wu", 3, General::Female);
    addGeneral(daqiao);

    //WU 007
    General *luxun = new General("luxun", "wu", 3);
    addGeneral(luxun);

    //WU 008
    General *sunshangxiang = new General("sunshangxiang", "wu", 3, General::Female);
    addGeneral(sunshangxiang);
}
