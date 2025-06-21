#!/bin/sh
# HELP: Retroarch User Manager
# ICON: dingux

. /opt/muos/script/var/func.sh

if pgrep -f "playbgm.sh" >/dev/null; then
	killall -q "playbgm.sh" "mpg123"
fi

echo app >/tmp/act_go

USERMGR_DIR="$(GET_VAR "device" "storage/rom/mount")/MUOS/application/rausermgr"
GPTOKEYB="$(GET_VAR "device" "storage/rom/mount")/MUOS/emulator/gptokeyb/gptokeyb2.armhf"

export SDL_GAMECONTROLLERCONFIG_FILE="/usr/lib/gamecontrollerdb.txt"

cd "$USERMGR_DIR" || exit
SET_VAR "system" "foreground_process" "rausermgr"

$GPTOKEYB "rausermgr" -c "./keys.gptk" &
./rausermgr
kill -9 "$(pidof gptokeyb2.armhf)"
