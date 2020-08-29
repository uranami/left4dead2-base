#pragma once
#include <cstdint>
#include "Misc.h"
struct RecvProp;

struct RecvTable
{
	RecvProp* m_pProps;
	int				m_nProps;
	void* m_pDecoder;
	char* m_pNetTableName;
	bool			m_bInitialized;
	bool			m_bInMainList;
};

struct RecvProp
{
	char* m_pVarName;
	int						m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;
	bool					m_bInsideArray;
	const void* m_pExtraData;
	RecvProp* m_pArrayProp;
	void* m_ArrayLengthProxy;
	void* m_ProxyFn;
	void* m_DataTableProxyFn;
	RecvTable* m_pDataTable;
	int						m_Offset;
	int						m_ElementStride;
	int						m_nElements;
	const char* m_pParentArrayPropName;
};


typedef enum
{
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY, // Only encodes the XY of a vector, ignores Z
	DPT_String,
	DPT_Array,	// An array of the base types (can't be of datatables).
	DPT_DataTable,
#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!
	DPT_Quaternion,
#endif
	DPT_Int64,
	DPT_NUMSendPropTypes
} SendPropType;

class DVariant
{
public:
	DVariant();
	DVariant(float val);

	union
	{
		float	m_Float;
		long	m_Int;
		char* m_pString;
		void* m_pData;	// For DataTables.
#if 0 // We can't ship this since it changes the size of DTVariant to be 20 bytes instead of 16 and that breaks MODs!!!
		float	m_Vector[4];
#else
		float	m_Vector[3];
#endif
		int64_t	m_Int64;
	};
	SendPropType	m_Type;
};


class CRecvProxyData
{
public:
	const RecvProp* m_pRecvProp;		// The property it's receiving.

	DVariant		m_Value;			// The value given to you to store.

	int				m_iElement;			// Which array element you're getting.

	int				m_ObjectID;			// The object being referred to.
};



struct ClientClass
{
	create_interface_fn m_pCreateFn;
	void* m_pCreateEventFn;
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int				m_ClassID;
};


enum classid
{
	Jockey = 264,
	Spitter = 271,
	Charger = 99,
	Hunter = 262,
	Smoker = 269,
	Boomer = 0,
	Tank = 275,
	Witch = 276,
	Infected = 263,
	CVomitJarProjectile = 251,
	CTerrorWeapon = 234,
	CTerrorMeleeWeapon = 230,
	CTerrorGun = 229,
	CTankClaw = 186,
	CSubMachinegun = 181,
	CSpitterProjectile = 175,
	CSpitterClaw = 174,
	CSniperRifle = 171,
	CSniper_Scout = 170,
	CSniper_Military = 169,
	CSniper_AWP = 168,
	CSmokerClaw = 166,
	CSMG_Silenced = 165,
	CSMG_MP5 = 164,
	CShotgun_SPAS = 162,
	CShotgun_Chrome = 161,
	CRifle_SG552 = 155,
	CRifle_M60 = 154,
	CRifle_Desert = 153,
	CRifle_AK47 = 152,
	CPumpShotgun = 148,
	CPropaneTank = 142,
	CMagnumPistol = 116,
	CPistol = 131,
	CPipeBombProjectile = 130,
	CPipeBomb = 129,
	CPainPills = 121,
	COxygenTank = 120,
	CBaseMountedWeapon = 18,
	CPropMountedGun = 146,
	CMolotovProjectile = 119,
	CMolotov = 118,
	CPropMinigun = 145,
	CJockeyClaw = 112,
	CItem_VomitJar = 106,
	CItemUpgradePackIncendiary = 111,
	CItemUpgradePackExplosive = 110,
	CItemDefibrillator = 109,
	CItemBaseUpgradePack = 108,
	CItemAmmoPack = 107,
	CItem_Adrenaline = 105,
	CHunterClaw = 100,
	CGrenadeLauncher_Projectile = 97,
	CGrenadeLauncher = 96,
	CGnome = 95,
	CGasCan = 94,
	CFirstAidKit = 73,
	CFireworkCrate = 72,
	CColaBottles = 44,
	CClaw = 42,
	CChargerClaw = 41,
	CChainsaw = 39,
	CPointPropUseTarget = 135,
	CTEBullets = 205,
	CBoomerClaw = 34,
	CBaseSniperRifle = 24,
	CBaseShotgun = 23,
	CBaseRifle = 22,
	CBaseBeltItem = 8,
	CBaseBackpackItem = 7,
	CBaseAutoShotgun = 6,
	CAutoShotgun = 2,
	CAssaultRifle = 1,
	SurvivorBot = 274,
	NextBotCombatCharacter = 266,
	CFireCrackerBlast = 69,
	CInsectSwarm = 104,
	CInferno = 101,
	CVomit = 250,
	CTongue = 245,
	CThrow = 244,
	CSpitAbility = 173,
	CSelfDestruct = 159,
	CLunge = 115,
	CLeap = 113,
	CCharge = 40,
	CBaseAbility = 3,
	CTutorLesson = 248,
	CTransitioningPlayer = 246,
	CTerrorViewModel = 233,
	CFuncRagdollFader = 87,
	CTerrorGameRulesProxy = 228,
	CSurvivorPosition = 184,
	CScavengeProgressDisplay = 157,
	CPropHealthCabinet = 144,
	CFinaleTrigger = 68,
	CClientPath = 43,
	CTerrorPlayerResource = 232,
	CTerrorPlayer = 231,
	CSurvivorRescue = 185,
	CSurvivorDeathModel = 183,
	CBaseUpgradeItem = 29,
	CWeaponScavengeItemSpawn = 258,
	CWeaponAmmoSpawn = 255,
	CWeaponSpawn = 259,
	CTeamTrainWatcher = 0,
	CSoundMixLayer = 172,
	CPointScriptUseTarget = 136,
	CEnvWeaponFire = 66,
	CWeaponCSBaseGun = 257,
	CWeaponCSBase = 256,
	CBaseCSGrenade = 12,
	CCSGameRulesProxy = 47,
	CWeaponCubemap = 0,
	CWeaponCycler = 0,
	CPlantedC4 = 0,
	CCSTeam = 50,
	CCSPlayer = 48,
	CCSRagdoll = 49,
	CTEPlayerAnimEvent = 225,
	CBaseCSGrenadeProjectile = 13,
	CTestTraceline = 242,
	CTEWorldDecal = 243,
	CTESpriteSpray = 240,
	CTESprite = 239,
	CTESparks = 238,
	CTESmoke = 237,
	CTEShowLine = 236,
	CTEProjectedDecal = 227,
	CTEPlayerDecal = 226,
	CTEPhysicsProp = 224,
	CTEParticleSystem = 223,
	CTEMuzzleFlash = 222,
	CTELargeFunnel = 220,
	CTEKillPlayerAttachments = 219,
	CTEImpact = 218,
	CTEGlowSprite = 217,
	CTEShatterSurface = 235,
	CTEFootprintDecal = 214,
	CTEFizz = 213,
	CTEExplosion = 212,
	CTEEnergySplash = 211,
	CTEEffectDispatch = 210,
	CTEDynamicLight = 209,
	CTEDecal = 207,
	CTEClientProjectile = 206,
	CTEBubbleTrail = 204,
	CTEBubbles = 203,
	CTEBSPDecal = 202,
	CTEBreakModel = 201,
	CTEBloodStream = 200,
	CTEBloodSprite = 199,
	CTEBeamSpline = 198,
	CTEBeamRingPoint = 197,
	CTEBeamRing = 196,
	CTEBeamPoints = 195,
	CTEBeamLaser = 194,
	CTEBeamFollow = 193,
	CTEBeamEnts = 192,
	CTEBeamEntPoint = 191,
	CTEBaseBeam = 190,
	CTEArmorRicochet = 189,
	CTEMetalSparks = 221,
	CSteamJet = 180,
	CSmokeStack = 167,
	DustTrail = 261,
	CFireTrail = 71,
	SporeTrail = 273,
	SporeExplosion = 272,
	RocketTrail = 268,
	SmokeTrail = 270,
	CPropVehicleDriveable = 147,
	ParticleSmokeGrenade = 267,
	CParticleFire = 122,
	MovieExplosion = 265,
	CTEGaussExplosion = 216,
	CEnvQuadraticBeam = 62,
	CEmbers = 53,
	CEnvWind = 67,
	CPrecipitation = 139,
	CPrecipitationBlocker = 140,
	CBaseTempEntity = 26,
	CHandleTest = 98,
	CTeamplayRoundBasedRulesProxy = 188,
	CSpriteTrail = 179,
	CSpriteOriented = 178,
	CSprite = 177,
	CRagdollPropAttached = 151,
	CRagdollProp = 150,
	CPredictedViewModel = 141,
	CPoseController = 137,
	CGameRulesProxy = 93,
	CFuncSimpleLadder = 90,
	CInfoLadderDismount = 102,
	CFuncLadder = 82,
	CTEFoundryHelpers = 215,
	CEnvDetailController = 57,
	CWorld = 260,
	CWaterLODControl = 254,
	CWaterBullet = 253,
	CVoteController = 252,
	CVGuiScreen = 249,
	CPropJeep = 0,
	CPropVehicleChoreoGeneric = 0,
	CFuncPlayerGhostInfectedClip = 85,
	CFuncPlayerInfectedClip = 86,
	CTriggerPlayerMovement = 247,
	CBaseTrigger = 28,
	CTest_ProxyToggle_Networkable = 241,
	CBaseTeamObjectiveResource = 25,
	CTeam = 187,
	CFlare = 0,
	CSun = 182,
	CParticlePerformanceMonitor = 123,
	CSpotlightEnd = 176,
	CSlideshowDisplay = 163,
	CShadowControl = 160,
	CSceneEntity = 158,
	CRopeKeyframe = 156,
	CRagdollManager = 149,
	CPhysBoxMultiplayer = 126,
	CPropDoorRotatingCheckpoint = 143,
	CBasePropDoor = 21,
	CDynamicProp = 52,
	CPostProcessController = 138,
	CPointCommentaryNode = 134,
	CPlayerResource = 133,
	CPlasma = 132,
	CPhysMagnet = 128,
	CPhysicsProp = 127,
	CBreakable = 35,
	CPhysBox = 125,
	CParticleSystem = 124,
	CMaterialModifyControl = 117,
	CLightGlow = 114,
	CInfoOverlayAccessor = 103,
	CFuncTrackTrain = 92,
	CFuncSmokeVolume = 91,
	CFuncRotating = 89,
	CFuncReflectiveGlass = 88,
	CFuncOccluder = 84,
	CFuncMoveLinear = 83,
	CFuncMonitor = 0,
	CFunc_LOD = 77,
	CFuncElevator = 81,
	CTEDust = 208,
	CFunc_Dust = 76,
	CFuncConveyor = 80,
	CFuncBrush = 79,
	CBreakableSurface = 37,
	CFuncAreaPortalWindow = 78,
	CFish = 74,
	CFireSmoke = 70,
	CEnvTonemapController = 65,
	CEnvScreenEffect = 63,
	CEnvScreenOverlay = 64,
	CEnvProjectedTexture = 61,
	CEnvParticleScript = 59,
	CFogController = 75,
	CEnvDOFController = 58,
	CEnvPhysicsBlocker = 60,
	CEntityParticleTrail = 56,
	CEntityFlame = 55,
	CEntityDissolve = 54,
	CDynamicLight = 51,
	CColorCorrectionVolume = 46,
	CColorCorrection = 45,
	CBreakableProp = 36,
	CBeamSpotlight = 32,
	CButtonTimed = 38,
	CBaseButton = 9,
	CBaseToggle = 27,
	CBasePlayer = 20,
	CBaseFlex = 16,
	CBaseEntity = 15,
	CBaseDoor = 14,
	CBaseCombatCharacter = 10,
	CBaseAnimatingOverlay = 5,
	CBoneFollower = 33,
	CBaseAnimating = 4,
	CAI_BaseNPC = 0,
	CBeam = 31,
	CBaseViewModel = 30,
	CBaseParticleEntity = 19,
	CBaseGrenade = 17,
	CBaseCombatWeapon = 11
};