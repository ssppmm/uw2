#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
#include <stdlib.h>
#include <hanlib.h>
#include <hanin.h>
#include <hancode.h>
#include "horiedit.h"

FILE *fp;

DEFCODE(CODE_KS)

void userinithan(void);
void hero_abil_edit(void);
void hero_ship_edit(void);
void person_edit(void);
void org_ship_edit(void);
void sel_save(void);
void init_hori(void);
void conferm_hero(void);
void select_menu(void);

struct Ship1 ship1;
struct Ship2 ship2;
struct Ship3 ship3;
struct Ship4 ship4;
struct Ship5 ship5;
struct Init init;
struct Port port;
long offset, offset1, offset2, offset3;
int ship_num=0;
int eXit=0;
char save_flg[10];

void hero_abil_edit(void)
{
    int i, j;
    struct Abil abil;
    int pro, spa, osm, eng, ita, ned;
    unsigned imsi;

    fseek(fp, abil_addr[c_hero]+page, SEEK_SET);
    fread(&abil, sizeof(struct Abil), 1, fp);
    fseek(fp, money_addr+page, SEEK_SET);
    fread(&money, sizeof(money), 1, fp);

    pro=abil.pro-100;
    spa=abil.spa-100;
    osm=abil.osm-100;
    eng=abil.eng-100;
    ita=abil.ita-100;
    ned=abil.ned-100;

    do {
        hclrscr();
        hprintxf(" 0) 저장하고 나가기\n");
        hprintxf(" 1) 교역명성        : $1c%u\n", abil.trade);
        hprintxf(" 2) 해적명성        : $1c%u\n", abil.robber);
        hprintxf(" 3) 모험명성        : $1c%u\n", abil.adven);
        if (pro >=0 )
        hprintxf(" 4) 포르투칼   관계 : $1c%d\n", pro);
        else
        hprintxf(" 4) 포르투칼   관계 : $4c%d\n", pro);
        if (spa >=0 )
        hprintxf(" 5) 에스파니아 관계 : $1c%d\n", spa);
        else
        hprintxf(" 5) 에스파니아 관계 : $4c%d\n", spa);
        if (osm >=0 )
        hprintxf(" 6) 오스만제국 관계 : $1c%d\n", osm);
        else
        hprintxf(" 6) 오스만제국 관계 : $4c%d\n", osm);
        if (eng >=0 )
        hprintxf(" 7) 영국       관계 : $1c%d\n", eng);
        else
        hprintxf(" 7) 영국       관계 : $4c%d\n", eng);
        if (ita >=0 )
        hprintxf(" 8) 이탈리아   관계 : $1c%d\n", ita);
        else
        hprintxf(" 8) 이탈리아   관계 : $4c%d\n", ita);
        if (ned >=0 )
        hprintxf(" 9) 네델란드   관계 : $1c%d\n", ned);
        else
        hprintxf(" 9) 네델란드   관계 : $4c%d\n", ned);
        if (c_hero==5)
        hprintxf("10) 작위            : $1c%s\n", Ipeer[abil.peer]);
        else
        hprintxf("10) 작위            : $1c%s\n", Epeer[abil.peer]);
        hprintxf("11) 돈              : $1c%lu\n", money);
        hprintf("\n고치기를 원하는 번호를 입력해 주세요 => ");
        hscanf("%d", &i);
        switch(i) {
           case  1 : hprintf("교역 명성을 바꿉니다 => "); hscanf("%u", &abil.trade); break;
           case  2 : hprintf("해적 명성을 바꿉니다 => "); hscanf("%u", &abil.robber); break;
           case  3 : hprintf("모험 명성을 바꿉니다 => "); hscanf("%u", &abil.adven); break;
           case  4 : hprintf("포르투칼 관계를 바꿉니다 => "); hscanf("%d", &pro); break;
           case  5 : hprintf("에스파니아 관계를 바꿉니다 => "); hscanf("%d", &spa); break;
           case  6 : hprintf("오스만 제국관계를 바꿉니다 => "); hscanf("%d", &osm); break;
           case  7 : hprintf("영국 관계를 바꿉니다 => "); hscanf("%d", &eng); break;
           case  8 : hprintf("이탈리아 관계를 바꿉니다 => "); hscanf("%d", &ita); break;
           case  9 : hprintf("네델란드 관계를 바꿉니다 => "); hscanf("%d", &ned); break;
           case 10 : do {
                        hclrscr();
                        hprintf(" 0) 고치지 않고 빠져나가기\n");
                        if (c_hero==5) for(j=0; j<10; j++) hprintf("%2d) %s\n", j+1, Ipeer[j]);
                        else for(j=0; j<10; j++) hprintf("%2d) %s\n", j+1, Epeer[j]);
                        hprintf("\n원하시는 작위를 입력해 주세요 => ");
                        hscanf("%u", &imsi);
                     } while(imsi>10);
                     if (imsi==0) break;
                     abil.peer=(unsigned char)(imsi-1);
                     break;
           case 11 : hprintf("돈을 바꿉니다 => "); hscanf("%lu", &money); break;
        }
    } while(i!=0);
    abil.pro=pro+100;
    abil.spa=spa+100;
    abil.osm=osm+100;
    abil.eng=eng+100;
    abil.ita=ita+100;
    abil.ned=ned+100;
    fseek(fp, abil_addr[c_hero]+page, SEEK_SET);
    fwrite(&abil, sizeof(struct Abil), 1, fp);
    fseek(fp, money_addr+page, SEEK_SET);
    fwrite(&money, sizeof(money), 1, fp);
}

void person_edit(void)
{
    int no=0;
    int i, cmp, j;
    char c=0;
    unsigned imsi;
    char fname[13];
    char lname[13];
    char fname_flag=0;
    char lname_flag=0;
    char fname_exist=0;
    char lname_exist=0;
    long offset;
    struct Person person;

    offset=person_addr;

    for (i=0; i<13; i++) { fname[i]=0x00; lname[i]=0x00;}

    _hangulmode=true;
    hprintf("찾고자 하는 사람의 처음 이름을 입력해 주세요\n => ");
    hgetln(fname, 12);
    hprintf("\n찾고자 하는 사람의 마지막 이름을 입력해 주세요\n => ");
    hgetln(lname, 12);

    _hangulmode=false;
    if(fname[0]==0x00) fname_flag=1;
    else fname_exist=1;
    if(lname[0]==0x00) lname_flag=1;
    else lname_exist=1;
    if(fname_flag && lname_flag) return;

    while(1) {
        fseek(fp, offset+page, SEEK_SET);
        fread(&person, sizeof(struct Person), 1, fp);

        if (person.pos==0xFF) {
            offset1=port_addr+person.port*sizeof(struct Port)+page;
            fseek(fp, offset1, SEEK_SET);
            fread(&port, sizeof(struct Port), 1, fp);
        }

        if(fname_exist) {
            cmp=strcmp(fname, person.fname);
            if (cmp==0) fname_flag=1;
        }
        if (lname_exist) {
            cmp=strcmp(lname, person.lname);
            if (cmp==0) lname_flag=1;
        }
        if (fname_flag && lname_flag) {
            hclrscr();
            hprintxf("인물 번호   : Dec $1c%2d $0cHex $1c%2x \n", no, no);
            hprintxf("처음 이름   : $1c%s\n", person.fname);
            hprintxf("마지막 이름 : $1c%s\n", person.lname);
            hprintxf("통솔        : $1c%u\n", person.command);
            hprintxf("항해        : $1c%u\n", person.sail);
            hprintxf("지식        : $1c%u\n", person.know);
            hprintxf("직감        : $1c%u\n", person.hunch);
            hprintxf("용기        : $1c%u\n", person.tool);
            hprintxf("검술        : $1c%u\n", person.sword);
            hprintxf("매력        : $1c%u\n", person.charm);
            hprintxf("운명        : $1c%u\n", person.death);
            hprintxf("항해 레벨   : $1c%u\n", person.l_sail);
            hprintxf("전투 레벨   : $1c%u\n", person.l_battle);
            hprintxf("항해 경험   : $1c%u\n", person.exp_sail);
            hprintxf("전투 경험   : $1c%u\n", person.exp_battle);
            hprintxf("능력        : 교섭 $1c%u $0c회계 $1c%u $0c포술 $1c%u $0c지도 $1c%u $0c측량 $1c%u\n", \
            person.ability.td, person.ability.ac, person.ability.gu, person.ability.mp, person.ability.me);
//            hprintxf("나이        : $1c%d\n", person.age);
            if (person.pos==0XFF) hprintxf("사는곳      : $1c%s\n\n",port_name[person.port]);
            c=0;
            hprintf("위의 데이타가 맞습니까?(y/n) => ");
            while(c!='n' && c!='N' && c!='y' && c!='Y') c=hgetche();
            if (c=='n' || c=='N') {
                if(fname_exist) fname_flag=0;
                if(lname_exist) lname_flag=0;
            }
            else break;
        }
        offset+=sizeof(struct Person);
        if (offset>(0x1DE7+page)) {
            hprintxf("\n$4c원하시는 데이타를 찾을수가 없습니다.");
            pause();
            return;
        }
        no++;
    }

    while (i!=0) {
        hclrscr();
        hprintxf(" 0) 저장하고 나가기\n");
        hprintxf(" 1) 처음 이름   : $1c%s\n", person.fname);
        hprintxf(" 2) 마지막 이름 : $1c%s\n", person.lname);
        hprintxf(" 3) 통솔        : $1c%u\n", person.command);
        hprintxf(" 4) 항해        : $1c%u\n", person.sail);
        hprintxf(" 5) 지식        : $1c%u\n", person.know);
        hprintxf(" 6) 직감        : $1c%u\n", person.hunch);
        hprintxf(" 7) 용기        : $1c%u\n", person.tool);
        hprintxf(" 8) 검술        : $1c%u\n", person.sword);
        hprintxf(" 9) 매력        : $1c%u\n", person.charm);
        hprintxf("10) 운명        : $1c%u\n", person.death);
        hprintxf("11) 항해 레벨   : $1c%u\n", person.l_sail);
        hprintxf("12) 전투 레벨   : $1c%u\n", person.l_battle);
        hprintxf("13) 항해 경험   : $1c%u\n", person.exp_sail);
        hprintxf("14) 전투 경험   : $1c%u\n", person.exp_battle);
        hprintxf("능력            : 15)교섭 $1c%u $0c16)회계 $1c%u $0c17)포술 $1c%u $0c18)지도 $1c%u $0c19)측량 $1c%u\n", \
        person.ability.td, person.ability.ac, person.ability.gu, person.ability.mp, person.ability.me);
//        hprintxf("20) 나이        : $1c%d\n", person.age);
        if (person.pos==0XFF) hprintxf("20) 거주지(항구): $1c%s\n\n",port_name[person.port]);

        hprintf("고치기를 원하는 데이타를 선택해 주십시오 => ");
        hscanf("%d", &i);

        switch(i) {
            case 1 : hprintf("처음 이름을 바꿉니다.\n=> ");
                     _hangulmode=true;
                     hgetln(person.fname, 12);
                     _hangulmode=false;
                     break;
            case 2 : hprintf("마지막 이름을 바꿉니다.\n=> ");
                     _hangulmode=true;
                     hgetln(person.lname, 12);
                     _hangulmode=false;
                     break;
            case 3 : hprintf("통솔을 바꿉니다. => "); hscanf("%u", &imsi);
                     person.command=(unsigned char)imsi; break;
            case 4 : hprintf("항해를 바꿉니다. => "); hscanf("%u", &imsi);
                     person.sail=(unsigned char)imsi; break;
            case 5 : hprintf("지식을 바꿉니다. => "); hscanf("%u", &imsi);
                     person.know=(unsigned char)imsi; break;
            case 6 : hprintf("직감을 바꿉니다. => "); hscanf("%u", &imsi);
                     person.hunch=(unsigned char)imsi; break;
            case 7 : hprintf("용기를 바꿉니다. => "); hscanf("%u", &imsi);
                     person.tool=(unsigned char)imsi; break;
            case 8 : hprintf("검술을 바꿉니다. => "); hscanf("%u", &imsi);
                     person.sword=(unsigned char)imsi; break;
            case 9 : hprintf("매력을 바꿉니다. => "); hscanf("%u", &imsi);
                     person.charm=(unsigned char)imsi; break;
           case 10 : hprintf("운명을 바꿉니다. (1-100) => "); hscanf("%u", &imsi);
                     person.death=(unsigned char)imsi; break;
           case 11 : hprintf("항해 레벨을 바꿉니다. => "); hscanf("%u", &imsi);
                     person.l_sail=(unsigned char)imsi; break;
           case 12 : hprintf("전투 레벨을 바꿉니다. => "); hscanf("%u", &imsi);
                     person.l_battle=(unsigned char)imsi; break;
           case 13 : hprintf("항해 경험치를 바꿉니다. => "); hscanf("%u", &imsi);
                     person.exp_sail=imsi; break;
           case 14 : hprintf("전투 경험치를 바꿉니다. => "); hscanf("%u", &imsi);
                     person.exp_battle=imsi; break;
           case 15 : hprintf("교섭능력을 바꿉니다. (0-1) => "); hscanf("%u", &imsi);
                     person.ability.td=imsi; break;
           case 16 : hprintf("회계능력을 바꿉니다. (0-1) => "); hscanf("%u", &imsi);
                     person.ability.ac=imsi; break;
           case 17 : hprintf("포술능력을 바꿉니다. (0-1) => "); hscanf("%u", &imsi);
                     person.ability.gu=imsi; break;
           case 18 : hprintf("지도작성 능력을 바꿉니다. (0-1) => "); hscanf("%u", &imsi);
                     person.ability.mp=imsi; break;
           case 19 : hprintf("측량능력을 바꿉니다. (0-1) => "); hscanf("%u", &imsi);
                     person.ability.me=imsi; break;
//           case 20 : hprintf("나이를 바꿉니다. => "); hscanf("%u", &imsi);
//                     person.age=imsi; break;
           case 20 : if (person.pos==0XFF) {
                         do {
                              j=0; hclrscr();
                              while (1) {
                                  hprintf("%3d) %-14s ", j, port_name[j]);
                                  j++;
                                  if (j==130)break;
                                  hprintf("%3d) %-14s ", j, port_name[j]);
                                  j++;
                                  if (j==130)break;
                                  hprintf("%3d) %-14s ", j, port_name[j]);
                                  j++;
                                  if (j==130)break;
                                  hprintf("%3d) %-14s \n", j, port_name[j]);
                                  j++;
                                  if (j==130)break;
                              }
                              hprintf("\n\n\n현재 거주하는 곳을 바꿉니다 => ");
                              hscanf("%u", &imsi);
                         } while(imsi>129);
                         person.port=imsi;
                     }
                     break;
         }
    }

    fseek(fp, offset+page, SEEK_SET);
    fwrite(&person, sizeof(struct Person), 1, fp);

}

void load(int sel)
{
    offset1=ship1_addr[c_hero]+page+(sel*sizeof(struct Ship1));
    offset2=ship2_addr+page+(sel*sizeof(struct Ship2));
    fseek(fp, offset1, SEEK_SET);
    fread(&ship1, sizeof(struct Ship1), 1, fp);
    fseek(fp, offset2, SEEK_SET);
    fread(&ship2, sizeof(struct Ship2), 1, fp);
    offset3=ship3_addr+page+(ship1.select*sizeof(struct Ship3));
    fseek(fp, offset3, SEEK_SET);
    fread(&ship3, sizeof(struct Ship3), 1, fp);
}

void store(void)
{
    fseek(fp, offset1, SEEK_SET);
    fwrite(&ship1, sizeof(struct Ship1), 1, fp);
    fseek(fp, offset2, SEEK_SET);
    fwrite(&ship2, sizeof(struct Ship2), 1, fp);
    fseek(fp, offset3, SEEK_SET);
    fwrite(&ship3, sizeof(struct Ship3), 1, fp);
}


void load4(int sel)
{
    offset=page+ship4_addr+sizeof(struct Ship4)*sel;
    fseek(fp, offset, SEEK_SET);
    fread(&ship4, sizeof(struct Ship4), 1, fp);
}

void load5(int sel)
{
    fseek(fp, s_addr+page+sizeof(struct Ship5)*sel, SEEK_SET);
    fread(&ship5, sizeof(struct Ship5), 1, fp);
}


void hero_ship_edit(void)
{
    int i, sel, j;
    unsigned imsi;
    unsigned char bitmask1, bitmask2;

    if (ship_num==0) {
        hprintxf("$4c소유하고 있는 배가 한척도 없습니다.");
        pause();
        return;
    }

    while(1) {
        sel=99;
        hclrscr();
        hprintf("0) 나가기\n");
        for (i=0; i<ship_num; i++) {
            hprintf("%d) 제 %d함선의 데이터\n", i+1, i+1);
        }

        do {
            hprintf("고치기를 원하는 함선을 골라주세요 => ");
            hscanf("%d", &sel);
        } while(sel>ship_num);
        if (sel==0) break;
        sel--;
        i=1;

        load(sel);
        load4(ship3.ship_select);

        while( i!=0 ) {
            do {
                hclrscr();
                hprintxf(" 0) 저장하고 나가기\n");
                hprintxf(" 1) 현재 선원수      : $1c%u\n",ship1.ccrew);
                hprintxf(" 2) 현재 내구력      : $1c%u\n",ship1.chull);
                hprintxf(" 3) 최대 내구력      : $1c%u\n",ship1.lhull);
                hprintxf(" 4) 현재 선회력      : $1c%u\n",ship1.crudder);
                hprintxf(" 5) 현재 추진력      : $1c%u\n",ship1.csail);
                hprintxf(" 6) 현재 포문수      : $1c%u\n",ship1.cnowea);
                hprintxf(" 7) 현재 컨디션      : $1c%u\n",ship2.condition);
                hprintxf("    카르고           : $1c%u\n", ship3.cargo);
                hprintxf(" 8) 최대 선원 적재율 : $1c%u\n", ship3.f_crew);
                hprintxf(" 9) 최대 무장 적재율 : $1c%u\n", ship3.f_weap);
                hprintxf("10) 현재 무장        : $1c%s\n",weapon_name[ship1.cselwea-16]);
                hprintxf("11) 현재 선수상      : $1c%s\n",form_name[ship2.ship_form]);
                hprintxf("12) 선박 종류        : $1c%s\n", ship_name[ship3.ship_select], sel);
                hprintxf("13) 선박 이름        : $1c%s\n\n\n",ship3.ship_name);
                hprintf("고치기를 원하는 데이타를 선택해 주십시오 => ");
                hscanf("%d",&i);
            } while( i > 13);
            switch(i) {
               case  1 : hprintxf("이 메뉴의 수치는 $1c8) 최대 선원 적재율$0c의 수치를 초과할 수 없습니다.\n\n");
                         hprintf("현재 선원수를 고칩니다. => "); hscanf("%u",&imsi);
                         ship1.ccrew=imsi;
                         if (ship1.ccrew>ship3.f_crew) ship1.ccrew=ship3.f_crew;
                         break;
               case  2 : hprintxf("이 메뉴의 수치는 $1c3) 최대 내구력$0c의 수치를 초과할 수 없습니다.\n\n");
                         hprintf("현재 내구력을 고칩니다. => "); hscanf("%u",&imsi);
                         ship1.chull=(unsigned char)imsi;
                         if (ship1.chull>ship1.lhull) ship1.chull=ship1.lhull;
                         break;
               case  3 : hprintf("최대 내구력을 고칩니다. => "); hscanf("%u",&imsi);
                         ship1.lhull=(unsigned char)imsi;
                         if (ship1.chull>ship1.lhull) ship1.chull=ship1.lhull;
                         break;
               case  4 : hprintxf("이 메뉴의 수치는 $1c%s$0c의 $1c최고 선회력 $0c수치를 초과할 수 없습니다.\n\n", ship_name[ship3.ship_select]);
                         hprintf("현재 선회력을 고칩니다. => "); hscanf("%u",&imsi);
                         ship1.crudder=(unsigned char)imsi;
                         if (ship1.crudder>ship4.lrudder) ship1.crudder=ship4.lrudder;
                         break;
               case  5 : hprintxf("이 메뉴의 수치는 $1c%s$0c의 $1c최고 추진력 $0c수치를 초과할 수 없습니다.\n\n", ship_name[ship3.ship_select]);
                         hprintf("현재 추진력을 고칩니다. => "); hscanf("%u",&imsi);
                         ship1.csail=(unsigned char)imsi;
                         if (ship1.csail>ship4.lsail) ship1.csail=ship4.lsail;
                         break;
               case  6 : hprintxf("이곳은 $1c10) 현재 무장$0c에서 무장을 선택하지 않으면 에디트가 되지 않습니다.\n");
                         hprintxf("또한 $1c9) 최대 무장 적재율$0c의 수치를 초과할 수 없습니다.\n\n");
                         hprintf("현재 포문수를 고칩니다. => "); hscanf("%u",&imsi);
                         ship1.cnowea=(unsigned char)imsi;
                         if (ship1.cnowea>ship3.f_weap) ship1.cnowea=ship3.f_weap;
                         if (ship1.cselwea==0x10) ship1.cnowea=0;
                         break;
               case  7 : hprintf("선박 컨디션을 고칩니다. => "); hscanf("%u",&imsi);
                         ship2.condition=(unsigned char)imsi;
                         break;
               case  8 : hprintxf("이 메뉴의 수치는 $1c%s$0c의 $1c최고 선원수 $0c수치를 초과할 수 없습니다.\n\n", ship_name[ship3.ship_select]);
                         hprintf("최대 선원 적재율을 고칩니다. => "); hscanf("%u",&imsi);
                         ship3.f_crew=imsi;
                         if (ship3.f_crew>(unsigned int)(ship4.lcrew*10)) ship3.f_crew=(ship4.lcrew*10);
                         if (ship1.ccrew>ship3.f_crew) ship1.ccrew=ship3.f_crew;
                         break;
               case  9 : hprintxf("이 메뉴의 수치는 $1c%s$0c의 $1c최대 포문수 $0c수치를 초과할 수 없습니다.\n\n", ship_name[ship3.ship_select]);
                         hprintf("최대 무장 적재율을 고칩니다. => "); hscanf("%u",&imsi);
                         ship3.f_weap=(unsigned char)imsi;
                         if (ship3.f_weap>ship4.lnowea) ship3.f_weap=ship4.lnowea;
                         if (ship1.cnowea>ship3.f_weap) ship1.cnowea=ship3.f_weap;
                         break;
               case 10  : do {
                             hclrscr();
                             hprintf("0) 고치지 않고 빠져 나가기\n");
                             for (j=0; j<8; j++) hprintf("%d) %s\n", j+1, weapon_name[j]); hprintf("\n\n");
                             hprintf("현재 무장을 고칩니다. => "); hscanf("%u", &imsi);
                             if (imsi==0) break;
                             imsi+=16; if(imsi<=(8+16)) ship1.cselwea=(unsigned char)(imsi-1);
                             if (ship1.cselwea==0x10) ship1.cnowea=0;
                         } while (imsi>(8+16)); break;
               case 11 : do {
                             hclrscr();
                             hprintf("0) 고치지 않고 빠져 나가기\n");
                             for (j=0; j<11; j++) hprintf("%d) %s\n", j+1, form_name[j]); hprintf("\n\n");
                             hprintf("현재 선수상을 고칩니다. => "); hscanf("%u", &imsi);
                             if (imsi==0) break;
                             if (imsi<=11) ship2.ship_form=(unsigned char)(imsi-1);
                         } while (imsi>11); break;
               case 12 : do {
                             hclrscr();
                             hprintf(" 0) 고치지 않고 빠져 나가기\n");
                             for (j=0; j<13; j++) {
                                if (j==0) hprintf("%2d) %-30s %2d) %-30s\n", j+1, ship_name[j], j+2, ship_name[j+1]);
                                else if (j<12)
                                         if (j==8 || j==11 )
                                         hprintxf("%2d) $1c%-30s $0c%2d) %-30s\n", j*2+1, ship_name[j*2], j*2+2, ship_name[j*2+1]);
                                         else
                                         hprintf("%2d) %-30s %2d) %-30s\n", j*2+1, ship_name[j*2], j*2+2, ship_name[j*2+1]);
                                else if (j==12) hprintf("%2d) %-30s\n", j*2+1, ship_name[j*2]);
                             }
                             hprintf("선박 종류를 고칩니다. => "); hscanf("%u",&imsi);
                             if(imsi==0) break;
                             if(imsi<=25) ship3.ship_select=(unsigned char)(imsi-1);
                         } while(imsi>25);
                         load4(ship3.ship_select);
                         load5(ship3.ship_select);
                         bitmask1=ship5.bform;
                         bitmask1&=0xf0;
                         bitmask2=ship3.bform;
                         bitmask2&=0x0f;
                         bitmask1|=bitmask2;
                         ship3.bform=bitmask1;
                         if (ship1.crudder>ship4.lrudder) ship1.crudder=ship4.lrudder;
                         if (ship1.csail>ship4.lsail) ship1.csail=ship4.lsail;
                         if (ship1.cnowea>ship4.lnowea) ship1.cnowea=ship4.lnowea;
                         if (ship3.f_crew>(unsigned int)(ship4.lcrew*10)) ship3.f_crew=(ship4.lcrew*10);
                         if (ship1.ccrew>ship3.f_crew) ship1.ccrew=ship3.f_crew;
                         ship3.cargo=ship4.capacity-(unsigned int)ship3.f_weap-ship3.f_crew;
                         break;
               case 13 : hprintf("선박의 이름을 고칩니다. => ");
                         _hangulmode=true;
                         hgetln(ship3.ship_name, 14);
                         _hangulmode=false;
               break;
            }
            ship3.cargo=ship4.capacity-(unsigned int)ship3.f_weap-ship3.f_crew;
        }

        store();

    }

}

void org_ship_edit(void)
{
    int i, j, sel;
    unsigned imsi;
    long offset;
    char name[18];

    while (1) {
        hclrscr();
        do {
            hclrscr();
            hprintf(" 0) 나가기\n");
            for (j=0; j<13; j++) {
                if (j==0) hprintf("%2d) %-30s %2d) %-30s\n", j+1, ship_name[j], j+2, ship_name[j+1]);
                else if (j<12)
                     if (j==8 || j==11 )
                         hprintxf("%2d) $1c%-30s $0c%2d) %-30s\n", j*2+1, ship_name[j*2], j*2+2, ship_name[j*2+1]);
                     else
                         hprintf("%2d) %-30s %2d) %-30s\n", j*2+1, ship_name[j*2], j*2+2, ship_name[j*2+1]);
                     else if (j==12) hprintf("%2d) %-30s\n\n\n", j*2+1, ship_name[j*2]);
                         }
            hprintf("어떤배를 에디트 하시겠습니까? => ");
            hscanf("%d", &sel);
        } while(sel<0 || sel>25);
        if (sel==0) break;

        sel--;
        offset=page+ship4_addr+sizeof(struct Ship4)*sel;
        fseek(fp, offset, SEEK_SET);
        fread(&ship4, sizeof(struct Ship4), 1, fp);
        fseek(fp, s_addr+page+sizeof(struct Ship5)*sel, SEEK_SET);
        fread(&ship5, sizeof(struct Ship5), 1, fp);
        while(1) {
            do {
                hclrscr();
                hprintf("0) 저장하고 나가기\n");
                hprintxf("1) 최대 선회력 : $1c%u\n", ship4.lrudder);
                hprintxf("2) 최대 추진력 : $1c%u\n", ship4.lsail);
                hprintxf("3) 최대 선원수 : $1c%u\n", (ship4.lcrew*10));
                hprintxf("4) 필요 선원수 : $1c%u\n", ship4.dcrew);
                hprintxf("5) 최대 적재량 : $1c%u\n", ship4.capacity);
                hprintxf("6) 최대 포문수 : $1c%u\n", ship4.lnowea);
                hprintxf("7) 배이름      : $1c%s\n\n",ship5.name);

                hprintf("고치기를 원하시는 데이타를 선택해 주세요 => ");
                hscanf("%d", &i);
            } while (i>7);
            if (i==0) break;

            switch(i) {
                case 1 : hprintf("최대 선회력을 고칩니다. => "); hscanf("%u", &imsi);
                         ship4.lrudder=(unsigned char)imsi;
                         for (i=0; i<ship_num; i++) {
                            load(i);
                            if (ship3.ship_select==sel) {
                                if (ship1.crudder>ship4.lrudder) {
                                    ship1.crudder=ship4.lrudder;
                                    store();
                                }
                            }
                         }
                         break;
                case 2 : hprintf("최대 추진력을 고칩니다. => "); hscanf("%u", &imsi);
                         ship4.lsail=(unsigned char)imsi;
                         for (i=0; i<ship_num; i++) {
                            load(i);
                            if (ship3.ship_select==sel) {
                                if (ship1.csail>ship4.lsail) {
                                    ship1.csail=ship4.lsail;
                                    store();
                                }
                            }
                         }
                         break;
                case 3 : hprintf("최대 선원수를 고칩니다. => "); hscanf("%u", &imsi);
                         ship4.lcrew=(unsigned char)(imsi/10);
                         for (i=0; i<ship_num; i++) {
                            load(i);
                            if (ship3.ship_select==sel) {
                                if (ship3.f_crew>(unsigned int)(ship4.lcrew*10)) {
                                    ship3.f_crew=(unsigned int)(ship4.lcrew*10);
                                    if (ship1.ccrew>ship3.f_crew) ship1.ccrew=ship3.f_crew;
                                    ship3.cargo=ship4.capacity-(unsigned int)ship3.f_weap-ship3.f_crew;
                                    store();
                                }
                            }
                         }
                         break;
                case 4 : hprintf("필요 선원수를 고칩니다. => "); hscanf("%u", &imsi);
                         ship4.dcrew=(unsigned char)imsi;
                         break;
                case 5 : hprintf("최대 적재량을 고칩니다. => "); hscanf("%u", &imsi);
                         ship4.capacity=imsi;
                         for (i=0; i<ship_num; i++) {
                            load(i);
                            if (ship3.ship_select==sel) {
                                    ship3.cargo=ship4.capacity-(unsigned int)ship3.f_weap-ship3.f_crew;
                                    store();
                            }
                         }
                         break;
                case 6 : hprintf("최대 포문수를 고칩니다. => "); hscanf("%u", &imsi);
                         ship4.lnowea=(unsigned char)imsi;
                         for (i=0; i<ship_num; i++) {
                            load(i);
                            if (ship3.ship_select==sel) {
                                if (ship3.f_weap>ship4.lnowea) {
                                    ship3.f_weap=ship4.lnowea;
                                    if (ship1.cnowea>ship3.f_weap) ship1.cnowea=ship3.f_weap;
                                    ship3.cargo=ship4.capacity-(unsigned int)ship3.f_weap-ship3.f_crew;
                                    store();
                                }
                            }
                         }
                         break;
                case 7 : hprintf("배의 이름을 고칩니다. => ");
                         _hangulmode=true;
                         hgetln(name, 18);
                         _hangulmode=false;
                         strcpy(ship5.name, name);
                         fseek(fp, s_addr+page+sizeof(struct Ship5)*sel, SEEK_SET);
                         fwrite(&ship5, sizeof(struct Ship5), 1, fp);
                         strcpy(ship_name[sel], ship5.name);
                         break;
            }
        }
        fseek(fp, offset, SEEK_SET);
        fwrite(&ship4, sizeof(struct Ship4), 1, fp);
    }
}
void select_menu(void)
{
    char select=99;

    while(select!=0) {
	hclrscr();
        hprintf("0) 나가기\n");
        hprintf("1) 주인공 데이타 에디트\n");
	hprintf("2) 인물 데이타 에디트\n");
	hprintf("3) 주인공 선박 에디트\n");
        hprintf("4) 원래의 선박 에디트\n");
        hprintf("5) 다른 세이브번호 선택\n\n");
        hprintf("원하시는 메뉴를 선택해 주세요(0-4) => ");
	hscanf("%d", &select);
	switch(select) {
            case 0 : return;
            case 1 : hero_abil_edit(); break;
            case 2 : person_edit(); break;
            case 3 : hero_ship_edit(); break;
            case 4 : org_ship_edit(); break;
            case 5 : sel_save(); break;
        }
    }
}

void conferm_hero(void)
{
    fseek(fp, c_addr+page, SEEK_SET);
    fread(&c_hero, 1, 1, fp);

    ship_num=0;
    while(1) {
        offset1=ship1_addr[c_hero]+page+(ship_num*sizeof(struct Ship1));
        fseek(fp, offset1, SEEK_SET);
        fread(&ship1, sizeof(struct Ship1), 1, fp);
        if (ship1.select!=0xff) {
            offset2=ship2_addr+page+(ship_num*sizeof(struct Ship2));
            fseek(fp, offset2, SEEK_SET);
            fread(&ship2, sizeof(struct Ship2), 1, fp);
            offset3=ship3_addr+page+(ship1.select*sizeof(struct Ship3));
            fseek(fp, offset3, SEEK_SET);
            fread(&ship3, sizeof(struct Ship3), 1, fp);
            if (ship3.ship_select==0xff) break;
            ship_num++;
        }
        else if(ship1.select==0xff) break;
    }
}

void init_hori(void)
{
    int i;
    struct Person ps;

    offset=person_addr;

    fseek(fp, offset+page, SEEK_SET);
    for (i=0; i<6; i++) {
        fread(&ps, sizeof(struct Person), 1, fp);
        strcpy(hero[i], ps.fname);
        strcat(hero[i], " ");
        strcat(hero[i], ps.lname);
    }

    fseek(fp, page+s_addr, SEEK_SET);
    for (i=0; i<25; i++) {
        fread(&ship5, sizeof(struct Ship5), 1, fp);
        strcpy(ship_name[i], ship5.name);
    }
}

void sel_save(void)
{
    int i;
    struct Person ps;
    char name_c[26];

    do {
        hclrscr();
        hprintxf("\n                    $1c대항해시대 에디터 $0cVer $4c1.4\n\n");
        hprintf(" 0) 그냥 빠져 나가기\n");
        hprintf("    %-11s  %-14s %-26s\n", "날    자", " 항   구", "이    름");
        for (i=0; i<10; i++) {
            fseek(fp, 1+sizeof (struct Init)*i, SEEK_SET);
            fread(&init, sizeof (struct Init), 1, fp);
            if(init.memo[0]==NULL) {
                hprintxf("%2d) $1cNo data\n", i+1);
                save_flg[i]=0;
            }
            else {
                hprintf("%2d) %s ", i+1, init.memo);
                save_flg[i]=1;
                if (init.port==0XFF) {
                    if(init.ending!=0) hprintxf("$1c*"); else hprintf(" ");
                    hprintf("%-14s ", "해상");
                }
                else {
                    if(init.ending!=0) hprintxf("$1c*"); else hprintf(" ");
                    offset=i*33340+init.port*sizeof(struct Port)+port_addr;
                    fseek(fp, offset, SEEK_SET);
                    fread(&port, sizeof(struct Port), 1, fp);
                    hprintf("%-14s ", port.name);
                }
                fseek(fp, c_addr+i*33340, SEEK_SET);
                fread(&c_hero, 1, 1, fp);
                offset=person_addr;
                offset+=(long)sizeof(struct Person)*(long)c_hero;
                offset+=(long)i*33340L;
                fseek(fp, offset, SEEK_SET);
                fread(&ps, sizeof(struct Person), 1, fp);
                strcpy(name_c, ps.fname);
                strcat(name_c, " ");
                strcat(name_c, ps.lname);
                hprintf("%-26s \n", name_c);
            }
        }

        hprintf("\n\n원하시는 세이브 번호를 선택해 주세요 => ");
        hscanf("%d", &i);
        if (i!=0 && i<11 && save_flg[i-1]==0) {
            hprintxf("\n$4c데이타가 없는 번호는 선택하실 수 없습니다.\n");
            hprintxf("$4c다른 번호를 선택해 주십시오");
            pause();
            i=11;
        }

    } while(i>10);

    if (i==0 || save_flg[i-1]==0) {
        eXit=1;
        return;
    }

    page = PAGE;
    page*=(i-1);
    init_hori();
    conferm_hero();
    offset=page+port_addr;
    fseek(fp, offset, SEEK_SET);
    for (i=0; i<130; i++)
    {
        fread(&port, sizeof(struct Port), 1, fp);
        strcpy(port_name[i], port.name);
    }
}

void main(void)
{
    if((fp=fopen("koukai2.dat","r+b"))==NULL) {
	printf("I don't find save file..");
	exit(-1);
    }

    userinithan();
    hsetbkcolor(7);
    hsetcolor(0);
    registerkssfont(KSS1);
    hallowautoscroll(true);
    _hangulmode=false;

    sel_save();
    if (eXit==1) { fclose(fp); exit(0);}

    select_menu();
    fclose(fp);
}
