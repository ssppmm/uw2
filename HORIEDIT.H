#ifndef _HORIEDIT_H_
#define _HORIEDIT_H_

#define JOAN  0X00             /* 조안의 등록번호     */
#define CAT   0X01             /* 카탈리나의 등록번호 */
#define OTTO  0X02             /* 오토의 등록번호     */
#define ROPEZ 0X03             /* 로페즈의 등록번호   */
#define PIET  0X04             /* 피에트로의 등록번호 */
#define AAL   0X05             /* 알의 등록번호       */

const long c_addr=0X06A8L;

char hero[6][26];

/* 조안, 카탈리나등 6명 주인공의 능력치 초기 테이블 주소 */
long abil_addr[6]={0X064D, 0X065B, 0X0669, 0X0677, 0X0685, 0X0693};

struct Abil {
    unsigned trade;            /* 교역 명성                 */
    unsigned robber;           /* 해적 명성                 */
    unsigned adven;            /* 모험 명성                 */
    unsigned char pro;         /* 포르투칼과의 적대치       */
    unsigned char spa;         /* 에스파니아와의 적대치     */
    unsigned char osm;         /* 오스만제국과의 적대치     */
    unsigned char eng;         /* 영국과의 적대치           */
    unsigned char ita;         /* 이탈리아와의 적대치       */
    unsigned char ned;         /* 네델란드와의 적대치       */
    unsigned char none;        /* 어떤 데이타가 있는지 모름 */
    unsigned char peer;        /* 작위 (공작, 후작, 백작등) */
};

char Epeer[10][7]={
    "없음",
    "기사",
    "준훈작",
    "훈작",
    "준남작",
    "남작",
    "자작",
    "백작",
    "후작",
    "공작"};

char Ipeer[10][7]={
    "없음",
    "사족",
    "감찰관",
    "군수",
    "지사",
    "영주",
    "대영주",
    "군후",
    "재상",
    "대재상"};

#define BALS  0X00             /* 발사          */
#define HANJ  0X01             /* 한자 콕       */
#define DAWO  0X02             /* 다우          */
#define BUS   0X03             /* 버스          */
#define TARE  0X04             /* 타렛테        */
#define RATI  0X05             /* 카라벨 라티나 */
#define REDO  0X06             /* 카라벨 레돈다 */
#define BRIG  0X07             /* 브리간틴      */
#define NAO   0X08             /* 나오          */
#define KARA  0X09             /* 카락          */
#define GAL   0X0A             /* 갤리온        */
#define JEBE  0X0B             /* 지벡          */
#define PANE  0X0C             /* 파네스        */
#define SLOO  0X0D             /* 슬루프        */
#define PREG  0X0E             /* 프리게이트    */
#define BAG   0X0F             /* 바그          */
#define SHIP  0X10             /* 쉽            */
#define JUNK  0X11             /* 정크          */
#define LGAL  0X12             /* 경갤리        */
#define PGAL  0X13             /* 플랜더스 갤리 */
#define BGAL  0X14             /* 베네치안 갤리 */
#define RA    0X15             /* 라 레아르     */
#define CHEO  0X16             /* 철갑선        */
#define AN    0X17             /* 안택선        */
#define GWAN  0X18             /* 관선          */

char ship_name[25][18];

#define CANO  0X11             /* 캐논       */
#define DCAN  0X12             /* 데미캐논   */
#define CANP  0X13             /* 캐논페드로 */
#define KBR   0X14             /* 컬버린     */
#define DKBR  0X15             /* 데미컬버린 */
#define SEKE  0X16             /* 세이커     */
#define KND   0X17             /* 카로네이드 */

char weapon_name[8][13]={
        "없음",
        "캐논",
        "데미캐논",
        "캐논페드로",
        "컬버린",
        "데미컬버린",
        "세이커",
        "카로네이드"};

#define  JAGU  0X01            /* 바다표범 */
#define  ADMI  0X02            /* 제독     */
#define  UNIC  0X03            /* 유니콘   */
#define  LION  0X04            /* 사자     */
#define  EAGL  0X05            /* 독수리   */
#define  PERS  0X06            /* 위인     */
#define  POSE  0X07            /* 포세이돈 */
#define  DRAG  0X08            /* 용       */
#define  ANGE  0X09            /* 천사     */
#define  GOD   0X0A            /* 여신     */

char form_name[11][11]={
         "없음",
         "바다표범",
         "제독",
         "유니콘",
         "사자",
         "독수리",
         "위인",
         "포세이돈",
         "용",
         "천사",
         "여신"};

/* 조안, 카탈리나등 6명 주인공의 선박 데이타가 있는 테이블의 초기주소 */
const long ship1_addr[6]={0X2244, 0X2776, 0X31DA, 0x3C3E, 0X370C, 0X2CA8};
const long ship2_addr=0X4692L;
const long ship3_addr=0X4C35L;
const long ship4_addr=0X5291;  /* 각 배의 초기 데이터가 있는 주소의 첫부분 */
const long s_addr=0X501DL;

struct Init {
    char memo[12];             /* 흠냐.. 그냥 메모 */
    unsigned char port;        /* 항구 번호        */
    unsigned char ending;     /* 비어있는 부분    */
    unsigned char none;
};

const long port_addr=0X53bf;

struct Port {
    char name[15];             /* 항구 이름 */
    unsigned char none[5];
};

char port_name[130][15];

struct Ship1 {
    unsigned ccrew;            /* 현재의 선원수               */
    unsigned char chull;       /* 현재의 내구력               */
    unsigned char lhull;       /* 최대 내구력                 */
    unsigned char crudder;     /* 현재의 선회력               */
    unsigned char csail;       /* 현재의 추진력               */
    unsigned char cnowea;      /* 현재의 포문수               */
    unsigned char select;      /* 선박의 데이터가 있는 테이블 */
    unsigned char cselwea;     /* 현재 무기의 종류            */
};

struct Ship2 {
    unsigned char captin;      /* 선장명                    */
    unsigned char condition;   /* 선박의 컨디션             */
    unsigned char ship_form;   /* 선박의 선수상             */
    unsigned char none[27];    /* 어떤 데이터가 있는지 모름 */
};

struct Ship3 {
    char ship_name[14];        /* 선박의 이름                     */
    unsigned char none[4];     /* 어떤 데이터가 있는지 모름       */
    unsigned char ship_select; /* 선박의 종류. 쉽, 정크. 그런거   */
    unsigned char bform;       /* 선박의 형태(싸울때 나오는 모습) */
    unsigned char f_weap;      /* 무기 적재율                     */
    unsigned int  f_crew;      /* 선원 적재율                     */
    unsigned int  cargo;       /* 실제 최대 적재율                */
};

struct Ship4 {
    unsigned char lrudder;     /* 최대 선회력               */
    unsigned char lsail;       /* 최대 추진력               */
    unsigned char lcrew;       /* 최대 선원수               */
    unsigned char dcrew;       /* 필요 선원수               */
    unsigned int  capacity;    /* 최대 적재량               */
    unsigned char lnowea;      /* 최대 포문수               */
    unsigned char none[5];     /* 어떤 데이터가 있는지 모름 */
};

struct Ship5 {
    char name[18];             /* 배의 이름              */
    unsigned char sform;       /* 배의 모습 (정보란의)   */
    unsigned char bform;       /* 배의 모습 (싸울때의)   */
    char none[5];              /* 중고선을 살때의 데이타 */
};

/* 각 세이브 데이터별 간격 */
#define PAGE 33340L;

long page=0;

struct babil {
    unsigned char td: 1;
    unsigned char ac: 1;
    unsigned char gu: 1;
    unsigned char mp: 1;
    unsigned char me: 1;
    unsigned char   : 1;
    unsigned char   : 1;
    unsigned char   : 1;
};


struct Person {
    char fname[13];            /* first name           */
    char lname[13];            /* last  name           */
    char none[2];              /* 어떤 데이터인지 모름 */
    unsigned char command;     /* 통솔                 */
    unsigned char sail;        /* 항해                 */
    unsigned char know;        /* 지식                 */
    unsigned char hunch;       /* 직감                 */
    unsigned char tool;        /* 용기                 */
    unsigned char sword;       /* 검술                 */
    unsigned char charm;       /* 매력                 */
    unsigned char death;       /* 운명                 */
    unsigned char l_sail;      /* 항해 레벨            */
    unsigned char l_battle;    /* 전투 레벨            */
    unsigned int  exp_sail;    /* 항해 경험            */
    unsigned int  exp_battle;  /* 전투 경험            */
    unsigned char age;         /* 나이                 */
    unsigned char none1;       /* 어떤 데이터인지 모름 */
    unsigned char pos;         /* 소속                 */
    unsigned char port;        /* 현재 있는 항구       */
    unsigned char none2[2];    /* 어떤 데이터인지 모름 */
    struct babil  ability;     /* 능력치               */
    char none3;                /* 어떤 데이터인지 모름 */
};

#define person_addr 0X06A9L;

unsigned c_hero;

unsigned long money;

#define money_addr 0X06A1L

#endif
