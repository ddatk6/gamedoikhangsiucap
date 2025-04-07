
#pragma once

namespace Player1Constants {

    enum SpriteSheetIndices {
        SRC_X = 0,
        SRC_Y = 1,
        FRAME_WIDTH = 2,
        FRAME_HEIGHT = 3,
        SPEED = 4,
        FRAME_COUNT = 5,
        ENERGY_COST = 6,
        DAMAGE = 7,
        COOLDOWN = 8
    };


    const int CHARACTER_1_SPRITES[12][9] = {
        // {SRC_X, SRC_Y, FRAME_WIDTH, FRAME_HEIGHT,SPEED, FRAME_COUNT, ENERGY_COST, DAMAGE, COOLDOWN}
            { 0  ,  0   ,    50      ,      48     , 200 ,      6     ,      0     ,   0   ,   1200   },  // CHẠY 0
            { 0  , 50   ,    34      ,      48     , 200 ,      2     ,      0     ,   0   ,   4000   }, // NHẢY 1
	        { 0  , 150  ,    33      ,      48     , 500 ,      6     ,      0     ,    0  ,   3000   },  // THỦ 2
            { 0  , 200  ,    50      ,      48     , 250 ,      4     ,      0     ,   20  ,   1000   },  // ĐẤM THƯỜNG 3
		    { 0  , 150  ,    33      ,      48     , 200 ,      6     ,      0     ,   0   ,    0     },   // ĐỨNG YÊN 4
	        { 0  , 314  ,    42      ,      56     , 250 ,      5     ,      5    ,   40  ,    5000  },  // ĐẤM MÓC NHẢY 5
	        { 0  , 475  ,    42      ,      48     , 250 ,      5     ,      10    ,   30  ,    4000  },  // CHẶT 6
	        { 0  , 525  ,    52      ,      51     , 200 ,      6     ,      300   ,   0   ,    15000 },  // RASENGAN0 7
            { 0  , 600  ,    34      ,      48     , 200 ,      2     ,      0     ,   0   ,    0     },  //RASENGAN1 7
            { 70 , 600  ,    50      ,      48     , 200 ,      6     ,      0     ,   0   ,    0     }, //RASENGAN2 7 
            { 0  , 650  ,    84      ,      50     , 100 ,      8     ,      0     ,   200 ,     0    },  //RASENGAN3 7
            {  0 , 375  ,    47      ,      48     , 300 ,      2     ,      0     ,   0   ,     0    }

    };

  
    const int SPRITE_SCALE = 2;
    const int SPRITE_SPEED = 100;

    const int JUMP_VELOCITY = -10;
    const float GRAVITY = 0.5f;
    const float TERMINAL_VELOCITY = 10.0f;
    const int MOVE_SPEED = 3;

    
}


namespace Player2Constants {
    enum SpriteSheetIndices {
        SRC_X = 0,
        SRC_Y = 1,
        FRAME_WIDTH = 2,
        FRAME_HEIGHT = 3,
        SPEED = 4,
        FRAME_COUNT = 5,
        ENERGY_COST = 6,
        DAMAGE = 7,
        COOLDOWN = 8
    };

    const int CHARACTER_1_SPRITES[10][9] = {
        // {SRC_X, SRC_Y, FRAME_WIDTH, FRAME_HEIGHT,SPEED, FRAME_COUNT, ENERGY_COST, DAMAGE, COOLDOWN}
            { 0  ,  0   ,    66      ,      48     , 200 ,      6     ,      0     ,   0   ,   1200   },  // CHẠY 0
            { 0  , 125  ,    34      ,      48     , 200 ,      2     ,      0     ,   0   ,   4000   }, // NHẢY 1
            { 0  , 800  ,    34      ,      64     , 200 ,      4     ,      0     ,   0   ,   3000   },  // THỦ 2
            { 0  , 400  ,    79      ,      64     , 250 ,      4     ,      0     ,   8   ,   1000   },  // CHÉM THƯỜNG 3
            { 0  , 59   ,    34      ,      48     , 200 ,     12     ,      0     ,   0   ,    0     },  // ĐỨNG YÊN 4
			{ 0  , 475  ,    58      ,      65     , 250 ,      5     ,      5    ,   20  ,   4000   },  // NHẢY CHÉM 5
            { 0  , 325  ,    81      ,      64     , 250 ,      6     ,      10    ,   40  ,   5000   },  // CHÉM NHANH 6
            { 0  , 675  ,    106     ,      77     , 200 ,      8     ,      300    ,   0   ,   15000  },  // CHIDORI0 7
            { 848, 675  ,    106     ,      77     , 200 ,      9     ,      0    ,   200 ,    0     },
            { 0  , 560  ,    42      ,      48     , 200 ,      3     ,      0    ,   0   ,    0     }
            

    };


    const int SPRITE_SCALE = 5;
    const int SPRITE_SPEED = 100;

    const int JUMP_VELOCITY = -10;
    const float GRAVITY = 0.5f;
    const float TERMINAL_VELOCITY = 10.0f;
    const int MOVE_SPEED = 4;
}

    namespace GlobalConstants {
        const int SCREEN_WIDTH = 1400;
        const int SCREEN_HEIGHT = 700;
        const int FPS = 60;
    };