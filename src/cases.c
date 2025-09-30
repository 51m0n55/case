typedef enum GunNM{
	CZ75,DESERT_EAGLE,DUAL_BARRETAS,FIVE_SEVEN,GLOCK_18,P2000,P250,R8_REVOLVER,TEC_9,USP_S,
	AK_47,AUG,AWP,FAMAS,G3SG1,GALIL_AR,M4A1_S,M4A4,SCAR_20,SG_553,SSG_08,MAC_10,MPS_SD,MP7,MP9,PP_BIZON,P90,UMP_45,
	MAG_7,NOVA,SAWED_OFF,XM1014,M249,NEGEV,
	BAYONET,BOWIE_KNIFE,BUTTERFLY_KNIFE,CLASSIC_KNIFE,FALCHION_KNIFE,FLIP_KNIFE,GUT_KNIFE,HUNTSMAN_KNIFE,KARAMBIT,KUKRI_KNIFE,M9_BAYONET,NAVAJA_KNIFE,
	NOMAD_KNIFE,PARACORD_KNIFE,SHADOW_DAGGERS,SKELETON_KNIFE,STILLETO_KNIFE,SURVIVAL_KNIFE,TALON_KNIFE,URSUS_KNIFE
}GunNM;

typedef enum RarityNM{
	WHITE,LIBLUE,BLUE,PURPLE,PINK,RED,GOLD
}RarityNM;

typedef enum CaseNM{
	WEAPON_CASE
}CaseNM;

typedef enum SkinNM{
    AWP_LIGHTNING_STRIKE, AK_47_CASE_HARDENED, DESERT_EAGLE_HYPNOTIC, GLOCK_18_DRAGON_TATTOO, M4A1_S_DARK_WATER, USP_S_DARK_WATER, 
    SG_553_ULTRAVIOLET, MP7_SKULLS, AUG_WINGS
}SkinNM;

typedef enum CaseTypes{ //chance setups
	NormalCase
}CaseTypes;

//------------------------------
typedef struct Skin{
	GunNM Gun;
	char SkinName[50];
	RarityNM Rarity;
	float Float;
}Skin;

typedef struct Case{
	int *Skins;
	int SkinCount;
	CaseTypes CaseType;
}Case;

//-----------------------------



Skin skinlist[100] = {
    {AWP, "Lightning Strike", RED},{AK_47, "Case Hardened", PINK},{DESERT_EAGLE, "Hypnotic", PINK},{GLOCK_18, "Dragon Tattoo", PURPLE},
	{M4A1_S, "Dark Water", PURPLE},{USP_S, "Dark Water", PURPLE},{SG_553, "Ultraviolet", BLUE},{MP7, "Skulls", BLUE},{AUG, "Wings", BLUE}

};

int weapon_case_skinlist[9] = {
	AWP_LIGHTNING_STRIKE, AK_47_CASE_HARDENED, DESERT_EAGLE_HYPNOTIC, GLOCK_18_DRAGON_TATTOO,
	M4A1_S_DARK_WATER, USP_S_DARK_WATER, SG_553_ULTRAVIOLET, MP7_SKULLS, AUG_WINGS
};

int CaseChances[10][7] = {
	{0,0,79923,15985,3197,639,256}
};


#define CaseCount 1

char CaseNames[CaseCount][22] = {"WEAPON 1"};

Case Cases[CaseCount] = {{weapon_case_skinlist,9,NormalCase}};