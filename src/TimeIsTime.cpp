/*
 * Azerothcore Module:     TimeIsTime
 * Author:                 Dunjeon
 * Contributing Author(s): lasyan3, vratam @ RegWorks
 * Version:                20250608
 * License:                GNU Affero General Public License v3.0.
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "GameTime.h"

class TimeIsTime : public PlayerScript {
public:

    TimeIsTime() : PlayerScript("TimeIsTime") { }

    void OnPlayerLogin(Player* player) {
        if (sConfigMgr->GetOption<bool>("TimeIsTime.Enable", true))
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00TimeIsTime |rmodule");
    }

    void OnPlayerSendInitialPacketsBeforeAddToMap(Player* player, WorldPacket& data) override {
        if (!sConfigMgr->GetOption<bool>("TimeIsTime.Enable", true))
            return;

        uint32 hour_offset = GameTime::GetGameTime().count() + sConfigMgr->GetOption<int>("TimeIsTime.HourOffset", 0) * 3600;

        data.Initialize(SMSG_LOGIN_SETTIMESPEED, 4 + 4 + 4);
        data.AppendPackedTime(hour_offset);
        data << float(0.01666667f);
        data << uint32(0);

        player->GetSession()->SendPacket(&data);
    }
};

void AddTimeIsTimeScripts() {
    new TimeIsTime();
}
