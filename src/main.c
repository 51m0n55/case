#include <gint/display.h>
#include <gint/display-fx.h>
#include <gint/keyboard.h>
#include <gint/gint.h>
#include <stdlib.h>
#include <stdio.h>
#include <gint/kmalloc.h>
#include <gint/rtc.h>

#include <math.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "cases.h"

extern bopti_image_t 
	S_CZ75, S_DESERT_EAGLE, S_DUAL_BARRETAS, S_FIVE_SEVEN, S_GLOCK_18, S_P2000, S_P250, S_R8_REVOLVER, 
	S_TEC_9, S_USP_S, S_AK_47, S_AUG, S_AWP, S_FAMAS, S_G3SG1, S_GALIL_AR, S_M4A1_S, S_M4A4, S_SCAR_20,
	S_SG553, S_SSG_08, S_MAC_10, S_MPS_SD, S_MP7, S_MP9, S_PP_BIZON, S_P90, S_UMP_45, S_MAG_7, S_NOVA, 
	S_SAWED_OFF, S_XM1014, S_M249, S_NEGEV, S_BAYONET, S_BOWIE_KNIFE, S_BUTTERFLY_KNIFE, S_CLASSIC_KNIFE, 
	S_FALCHION_KNIFE, S_FLIP_KNIFE, S_GUT_KNIFE, S_HUNTSMAN_KNIFE, S_KARAMBIT, S_KUKRI_KNIFE, S_M9_BAYONET, 
	S_NAVAJA_KNIFE, S_NOMAD_KNIFE, S_PARACORD_KNIFE, S_SHADOW_DAGGERS, S_SKELETON_KNIFE, S_STILLETO_KNIFE, 
	S_SURVIVAL_KNIFE, S_TALON_KNIFE, S_URSUS_KNIFE;
static const bopti_image_t *GunSprites[54] = {&S_CZ75, &S_DESERT_EAGLE, &S_DUAL_BARRETAS, &S_FIVE_SEVEN, 
	&S_GLOCK_18, &S_P2000, &S_P250, &S_R8_REVOLVER, &S_TEC_9, &S_USP_S, &S_AK_47, &S_AUG, &S_AWP, &S_FAMAS,
	&S_G3SG1, &S_GALIL_AR, &S_M4A1_S, &S_M4A4, &S_SCAR_20, &S_SG553, &S_SSG_08, &S_MAC_10, &S_MPS_SD, 
	&S_MP7, &S_MP9, &S_PP_BIZON, &S_P90, &S_UMP_45, &S_MAG_7, &S_NOVA, &S_SAWED_OFF, &S_XM1014, &S_M249, &S_NEGEV, 
	&S_BAYONET, &S_BOWIE_KNIFE, &S_BUTTERFLY_KNIFE, &S_CLASSIC_KNIFE, &S_FALCHION_KNIFE, &S_FLIP_KNIFE, &S_GUT_KNIFE, 
	&S_HUNTSMAN_KNIFE, &S_KARAMBIT, &S_KUKRI_KNIFE, &S_M9_BAYONET, &S_NAVAJA_KNIFE, &S_NOMAD_KNIFE, &S_PARACORD_KNIFE, 
	&S_SHADOW_DAGGERS, &S_SKELETON_KNIFE, &S_STILLETO_KNIFE, &S_SURVIVAL_KNIFE, &S_TALON_KNIFE, &S_URSUS_KNIFE};

const float START_SPEED_MIN = 3.5;
const float START_SPEED_MAX = 4.0;
const float DEACCEL_MIN = 0.01;
const float DEACCEL_MAX = 0.015;

static float speed = 0.5;
static float pos = 0.0;
static Skin items[6];

int RollTimer;

static Skin *Inventory;
static int InvSkinCount = 0;

static bool Rolling = false;

static int CursorPos = 0;
/*
void Load(struct Skin *Inventory, int InvItems){
	
	int savef = open("/CaseSim.bin", O_RDONLY);
    if (savef >= 0) {
		Inventory = malloc(savef);
		read(savef, &Inventory, savef);
		close(savef);
	}
}

void Save(struct Skin *Inventory, int InvItems){
	int save = open("/CaseSim.bin", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(save, &Inventory, sizeof(Inventory)); 
	close(save);
}
*/

int Rint(int min, int max){
	return (rand()%(max-min+1))+min;
}
float Ranf(float min, float max){
	return min+((float)rand()/(float)RAND_MAX)*(max - min);
}

Skin RandomSkin(Case Case){
	int *CaseChance = CaseChances[Case.CaseType];
	int DropNumber = Rint(0,100000);

	int ChanceSum = 0.0f;
	int Rarity = 0;
	for(int c=0;c<7;c++){ //always 7 chance %ages
		ChanceSum += CaseChance[c];
		if(ChanceSum>DropNumber){
			Rarity = c;
			break;
		}
	}

	int RarityCount = 0;
	int RarityPositions[50];
	for(int skin=0;skin<Case.SkinCount;skin++){
		if(skinlist[Case.Skins[skin]].Rarity == Rarity){
			RarityPositions[RarityCount] = skin;
			RarityCount++;
		}
	}
	Skin ReturnSkin = skinlist[Case.Skins[RarityPositions[Rint(0,RarityCount-1)]]];
	return ReturnSkin;
}

void ShowSkin(Skin Skin){
	drect_border(33,3,94,54,C_WHITE,1,C_BLACK);
	drect_border(35,11,59,35,C_WHITE,1,C_BLACK);
	dimage(36,12,GunSprites[Skin.Gun]);

	char[50] = strcat(("%s |",Skin.Gun),Skin.SkinName);
	dtext(35,5,C_BLACK,);
	dupdate();
	return;
};

int RollAnimateMove(){ 
	pos -= speed;
	speed -= Ranf(DEACCEL_MIN,DEACCEL_MAX);
	if(speed<=0){
		Skin DroppedSkin;
		InvSkinCount++;
		if(pos<=-18.0){
			DroppedSkin = items[2];
		}
		else{
			DroppedSkin = items[3];
		}
		char text[100];
		drect(0,0,128,20,C_WHITE);
		sprintf(text,"COUNT: %d",InvSkinCount);
		dprint(0,0,C_BLACK,text);
		dupdate();
		//getkey();
		Inventory = krealloc(Inventory,sizeof(Skin)*InvSkinCount);

		DroppedSkin.Float = Ranf(0.0,1.0);

		Inventory[InvSkinCount-1] = DroppedSkin;

		ShowSkin(DroppedSkin);
		Rolling = false;
		return TIMER_STOP;
	}
	if(pos < -26){
		pos = 0;
		
		for(int s=1; s<=5; s++){
			items[s-1] = items[s];
		}
		items[5] = RandomSkin(Cases[WEAPON_CASE]);
	}

	dclear(C_WHITE);
	for(int i=0; i<=5; i++){
		drect_border(i*25+pos+i*2,20,i*25+pos+25+i*2,45, C_WHITE,1,C_BLACK);
		dimage(i*25+pos+i*2+1,21,GunSprites[items[i].Gun]);
		dvline(64,C_BLACK);
	}
	dupdate();
}

void RollAnimate(){
	Rolling = true;
	speed = Ranf(START_SPEED_MIN,START_SPEED_MAX);
	pos = 0.0;
	for(int i=0; i<=5; i++){
		items[i] = RandomSkin(Cases[WEAPON_CASE]);
		
	}
	RollTimer = timer_configure(TIMER_ANY, 20000, GINT_CALL(RollAnimateMove));
	timer_start(RollTimer);
	return;
}

void DrawCaseMenu(){
	dclear(C_WHITE);
	int PageStart = (int)(CursorPos/10); //
	for(int cn = PageStart;cn<=PageStart+10; cn++){
		if(cn<CaseCount){
			dtext(4,cn*5+1,C_BLACK,CaseNames[cn]);
		}
		else{
			break;
		}
	}
	dtext(1,CursorPos*5+1,C_BLACK,">");
	dupdate();
}

void DrawCase(){
	dclear(C_WHITE);
	dtext(1,1,C_BLACK,CaseNames[CursorPos]);
	dupdate();
	while(1){
		cleareventflips();
		clearevents();
		if(keypressed(KEY_EXE) && !Rolling){
			RollAnimate();
		}
		if(keypressed(KEY_EXIT)){
			timer_stop(RollTimer);
			DrawCaseMenu();
			return;
		}
	}
}

void DrawInvMenu(){
	dclear(C_WHITE);
	
}

enum EMenu{
	CaseMenu,
	InvMenu
}EMenu;
static int CurrentMenu = CaseMenu;

int main(void)
{
	extern font_t font;
	dfont(&font);

	rtc_time_t time;
	rtc_get_time(&time);
	srand(time.ticks*time.seconds/time.hours);

	Inventory = kmalloc(0, NULL);
	
	//gint_world_switch(GINT_CALL(Load, (void *)Inventory,(void *)InvItems));
	bool ArrowsPressed = false;

	gint_setrestart(1);

	while(1){
		cleareventflips();
		clearevents();
		if(keypressed(KEY_MENU)){
			//gint_world_switch(GINT_CALL(Load, (void *)Inventory));
			return 1;
        }
		if(keypressed(KEY_EXE)){
			DrawCase();
		}
		if(keypressed(KEY_F6) && CurrentMenu != InvMenu){
			CursorPos = 0;
			CurrentMenu = InvMenu;
			DrawInvMenu();
		}
		if(keydown_any(KEY_UP,KEY_RIGHT,KEY_LEFT,KEY_DOWN,0) && !ArrowsPressed){
			ArrowsPressed = true;
			
			int CursorPosAdd = 0;
			if(keydown(KEY_UP)){
				CurrentMenu == CaseMenu ? CursorPosAdd = -1 : -5;
			}
			if(keydown(KEY_DOWN)){
				CurrentMenu == CaseMenu ? CursorPosAdd = 1 : 5;
			}
			if(keydown(KEY_LEFT)){
				CurrentMenu == CaseMenu ? CursorPosAdd = -10 : -1;
			}
			if(keydown(KEY_RIGHT)){
				CurrentMenu == CaseMenu ? CursorPosAdd = 10 : 1;
			}
			//out of bounds check
			if(CursorPos+CursorPosAdd>0 && CursorPosAdd<0){
				CursorPos += CursorPosAdd;
			}
			else{
				CursorPos = 0;
			}

			if(CursorPos+CursorPosAdd<CaseCount && CursorPosAdd>0){
				CursorPos += CursorPosAdd;
			}
			else{
				CursorPos = CaseCount-1;
			}

			if(CursorPos+CursorPosAdd<InvSkinCount && CursorPosAdd>0){
				CursorPos += CursorPosAdd;
			}
			else{
				CursorPos = InvSkinCount-1;
			}
			//------------

			if(CurrentMenu==CaseMenu){
				DrawCaseMenu();
			}
			else if(CurrentMenu==InvMenu){
				DrawInvMenu();
			}
		}
		else{
			ArrowsPressed = false;
		}
	}
}
