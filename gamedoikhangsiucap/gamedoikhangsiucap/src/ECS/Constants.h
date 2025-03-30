
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
        TIMEDELAY = 8
    };


    const int CHARACTER_1_SPRITES[11][9] = {
        // {SRC_X, SRC_Y, FRAME_WIDTH, FRAME_HEIGHT,SPEED, FRAME_COUNT, ENERGY_COST, DAMAGE, TIMEDELAY}
            { 0  ,  0   ,    50      ,      48     , 200 ,      6     ,      0     ,   0   ,   1200   },  // CHẠY 0
            { 0  , 50   ,    34      ,      48     , 200 ,      2     ,      0     ,   0   ,   4000   }, // NHẢY 1
	        { 0  , 150  ,    33      ,      48     , 200 ,      6     ,      0     ,    0  ,   3000   },  // THỦ 2
            { 0  , 200  ,    50      ,      48     , 200 ,      4     ,      0     ,   20  ,   1000   },  // ĐẤM THƯỜNG 3
		    { 0  , 250  ,    50      ,      64     , 200 ,      8     ,      0     ,   0   ,    0     },   // ĐỨNG YÊN 4
	        { 0  , 314  ,    42      ,      56     , 200 ,      5     ,      30    ,   40  ,    5000  },  // ĐẤM MÓC NHẢY 5
	        { 0  , 475  ,    42      ,      48     , 200 ,      5     ,      20    ,   30  ,    4000  },  // CHẶT 6
	        { 0  , 525  ,    52      ,      51     , 200 ,      6     ,      70    ,   0   ,    15000 },  // RASENGAN0 7
            { 0  , 600  ,    34      ,      48     , 200 ,      2     ,      0     ,   0   ,    0     },  //RASENGAN1 7
            { 70 , 600  ,    50      ,      48     , 200 ,      6     ,      0     ,   0   ,    0     }, //RASENGAN2 7 
            { 0  , 650  ,    84      ,      50     , 100 ,      8     ,      0     ,   100 ,     0    }  //RASENGAN3 7

    };

  
    const int SPRITE_SCALE = 2;
    const int SPRITE_SPEED = 100;

    const int JUMP_VELOCITY = -10;
    const float GRAVITY = 0.5f;
    const float TERMINAL_VELOCITY = 10.0f;
    const int MOVE_SPEED = 3;

    
}

// Constants for Player 2 (Sasuke)
namespace Player2Constants {
    // Thông tin chung về sprite sheet

    // Định nghĩa các chỉ số cho mảng CHARACTER_2_SPRITES
     // Định nghĩa các chỉ số cho mảng CHARACTER_1_SPRITES
    enum SpriteSheetIndices {
        SRC_X = 0,
        SRC_Y = 1,
        FRAME_WIDTH = 2,
        FRAME_HEIGHT = 3,
        SPEED = 4,
        FRAME_COUNT = 5,
        ENERGY_COST = 6,
        DAMAGE = 7,
        TIMEDELAY = 8
    };

    // Mảng 2 chiều lưu trữ thông tin về sprite sheet
    const int CHARACTER_1_SPRITES[9][9] = {
        // {SRC_X, SRC_Y, FRAME_WIDTH, FRAME_HEIGHT,SPEED, FRAME_COUNT, ENERGY_COST, DAMAGE, TIMEDELAY}
            { 0  ,  0   ,    66      ,      48     , 200 ,      6     ,      0     ,   0   ,   1200   },  // CHẠY 0
            { 0  , 125  ,    34      ,      48     , 200 ,      2     ,      0     ,   0   ,   4000   }, // NHẢY 1
            { 0  , 800  ,    34      ,      64     , 200 ,      4     ,      0     ,   0   ,   3000   },  // THỦ 2
            { 0  , 400  ,    79      ,      64     , 200 ,      4     ,      0     ,   8   ,   1000   },  // CHÉM THƯỜNG 3
            { 0  , 59   ,    34      ,      48     , 200 ,     12     ,      0     ,   0   ,    0     },  // ĐỨNG YÊN 4
			{ 0  , 475  ,    58      ,      65     , 200 ,      5     ,      30    ,   20  ,   4000   },  // NHẢY CHÉM 5
            { 0  , 325  ,    81      ,      64     , 200 ,      6     ,      40    ,   40  ,   5000   },  // CHÉM NHANH 6
            { 0  , 675  ,    106     ,      77     , 200 ,      8     ,      70    ,   0   ,   15000  },  // CHIDORI0 7
            { 848, 675  ,    106     ,      77     , 200 ,      9     ,      00    ,   100 ,    0     },
            

    };

    // Các hằng số khác
    const int SPRITE_SCALE = 5;
    const int SPRITE_SPEED = 100;

    const int JUMP_VELOCITY = -10;
    const float GRAVITY = 0.5f;
    const float TERMINAL_VELOCITY = 10.0f;
    const int MOVE_SPEED = 4;
}
// Global Constants
    namespace GlobalConstants {
        const int SCREEN_WIDTH = 1200;
        const int SCREEN_HEIGHT = 600;
        const int FPS = 60;
    };