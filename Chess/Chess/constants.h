#pragma once

#define BLenght 8
#define white 1
#define black 0

#define Enpassant 3
#define EnpassantKill 4
#define Kill 2
#define ValidMove 1
#define NotValid 0

#define Castle 5

#define PassSpecialArr EnpassantArr, KingMove, RookMove
#define IncludeSpecialArr int EnpassantArr[][2], bool KingMove[], bool RookMove[][2]