#ifndef DUDU_H
#define DUDU_H
#pragma once
// qt class
#include "./qtdudu.h"

// common class
#include "./TypeDefine.h"
#include "./JsonLite.h"
#include "../logic/clogic.h"
#include "./commondata.h"
#include "./CAppDataBase.h"


// network class
#include "../app/onlinemusic/cnetworkonlineserver.h"
#include "../app/onlinemusic/cnetworkmanager.h"

// system class
#ifdef OS_WIN
#include <windows.h>
#endif

// app class
#include "../playlist/TreeModel.h"
#include "../playlist/TreeItem.h"

#include "../app/localmusic/localmusic.h"
#include "../app/localmusic/localmusicmodel.h"

// onlinemusic class
#include "../app/onlinemusic/JConNetRspData.h"
#include "../app/onlinemusic/CAppOnlineMusic.h"
#include "../app/onlinemusic/CModelOnlineMusicCollect.h"
#include "../app/onlinemusic/CModelOnlineMusicEmotion.h"
#include "../app/onlinemusic/CModelOnlineMusicHistory.h"
#include "../app/onlinemusic/CModelOnlineMusicLanguage.h"
#include "../app/onlinemusic/CModelOnlineMusicSearched.h"
#include "../app/onlinemusic/CModelOnlineMusicSence.h"
#include "../app/onlinemusic/CModelOnlineMusicStyle.h"
#include "../app/onlinemusic/CModelOnlineMusicTopName.h"
#include "../app/onlinemusic/CModelOnlineMusicType.h"
#include "../app/onlinemusic/CModelOnlineMusicYears.h"

// video class
#include "../app/video/dudumediaplayer.h"
#endif // DUDU_H
