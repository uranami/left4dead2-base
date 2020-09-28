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
	Jockey = 265,
	Spitter = 272,
	Charger = 99,
	Hunter = 263,
	Smoker = 270,
	Boomer = 0,
	Tank = 276,
	Witch = 277,
	Infected = 264,
	CVomitJarProjectile = 252,
	CTerrorWeapon = 235,
	CTerrorMeleeWeapon = 231,
	CTerrorGun = 230,
	CTankClaw = 187,
	CSubMachinegun = 182,
	CSpitterProjectile = 176,
	CSpitterClaw = 175,
	CSniperRifle = 172,
	CSniper_Scout = 171,
	CSniper_Military = 170,
	CSniper_AWP = 169,
	CSmokerClaw = 167,
	CSMG_Silenced = 166,
	CSMG_MP5 = 165,
	CShotgun_SPAS = 163,
	CShotgun_Chrome = 162,
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
	CTEBullets = 206,
	CBoomerClaw = 34,
	CBaseSniperRifle = 24,
	CBaseShotgun = 23,
	CBaseRifle = 22,
	CBaseBeltItem = 8,
	CBaseBackpackItem = 7,
	CBaseAutoShotgun = 6,
	CAutoShotgun = 2,
	CAssaultRifle = 1,
	SurvivorBot = 275,
	NextBotCombatCharacter = 267,
	CFireCrackerBlast = 69,
	CInsectSwarm = 104,
	CInferno = 101,
	CVomit = 251,
	CTongue = 246,
	CThrow = 245,
	CSpitAbility = 174,
	CSelfDestruct = 160,
	CLunge = 115,
	CLeap = 113,
	CCharge = 40,
	CBaseAbility = 3,
	CTutorLesson = 249,
	CTransitioningPlayer = 247,
	CTerrorViewModel = 234,
	CFuncRagdollFader = 87,
	CTerrorGameRulesProxy = 229,
	CSurvivorPosition = 185,
	CScavengeProgressDisplay = 157,
	CPropHealthCabinet = 144,
	CFinaleTrigger = 68,
	CClientPath = 43,
	CTerrorPlayerResource = 233,
	CTerrorPlayer = 232,
	CSurvivorRescue = 186,
	CSurvivorDeathModel = 184,
	CBaseUpgradeItem = 29,
	CWeaponScavengeItemSpawn = 259,
	CWeaponAmmoSpawn = 256,
	CWeaponSpawn = 260,
	CTeamTrainWatcher = 0,
	CSoundMixLayer = 173,
	CPointScriptUseTarget = 136,
	CEnvWeaponFire = 66,
	CWeaponCSBaseGun = 258,
	CWeaponCSBase = 257,
	CBaseCSGrenade = 12,
	CCSGameRulesProxy = 47,
	CWeaponCubemap = 0,
	CWeaponCycler = 0,
	CPlantedC4 = 0,
	CCSTeam = 50,
	CCSPlayer = 48,
	CCSRagdoll = 49,
	CTEPlayerAnimEvent = 226,
	CBaseCSGrenadeProjectile = 13,
	CTestTraceline = 243,
	CTEWorldDecal = 244,
	CTESpriteSpray = 241,
	CTESprite = 240,
	CTESparks = 239,
	CTESmoke = 238,
	CTEShowLine = 237,
	CTEProjectedDecal = 228,
	CTEPlayerDecal = 227,
	CTEPhysicsProp = 225,
	CTEParticleSystem = 224,
	CTEMuzzleFlash = 223,
	CTELargeFunnel = 221,
	CTEKillPlayerAttachments = 220,
	CTEImpact = 219,
	CTEGlowSprite = 218,
	CTEShatterSurface = 236,
	CTEFootprintDecal = 215,
	CTEFizz = 214,
	CTEExplosion = 213,
	CTEEnergySplash = 212,
	CTEEffectDispatch = 211,
	CTEDynamicLight = 210,
	CTEDecal = 208,
	CTEClientProjectile = 207,
	CTEBubbleTrail = 205,
	CTEBubbles = 204,
	CTEBSPDecal = 203,
	CTEBreakModel = 202,
	CTEBloodStream = 201,
	CTEBloodSprite = 200,
	CTEBeamSpline = 199,
	CTEBeamRingPoint = 198,
	CTEBeamRing = 197,
	CTEBeamPoints = 196,
	CTEBeamLaser = 195,
	CTEBeamFollow = 194,
	CTEBeamEnts = 193,
	CTEBeamEntPoint = 192,
	CTEBaseBeam = 191,
	CTEArmorRicochet = 190,
	CTEMetalSparks = 222,
	CSteamJet = 181,
	CSmokeStack = 168,
	DustTrail = 262,
	CFireTrail = 71,
	SporeTrail = 274,
	SporeExplosion = 273,
	RocketTrail = 269,
	SmokeTrail = 271,
	CPropVehicleDriveable = 147,
	ParticleSmokeGrenade = 268,
	CParticleFire = 122,
	MovieExplosion = 266,
	CTEGaussExplosion = 217,
	CEnvQuadraticBeam = 62,
	CEmbers = 53,
	CEnvWind = 67,
	CPrecipitation = 139,
	CPrecipitationBlocker = 140,
	CBaseTempEntity = 26,
	CHandleTest = 98,
	CTeamplayRoundBasedRulesProxy = 189,
	CSpriteTrail = 180,
	CSpriteOriented = 179,
	CSprite = 178,
	CRagdollPropAttached = 151,
	CRagdollProp = 150,
	CPredictedViewModel = 141,
	CPoseController = 137,
	CGameRulesProxy = 93,
	CFuncSimpleLadder = 90,
	CInfoLadderDismount = 102,
	CFuncLadder = 82,
	CTEFoundryHelpers = 216,
	CEnvDetailController = 57,
	CWorld = 261,
	CWaterLODControl = 255,
	CWaterBullet = 254,
	CVoteController = 253,
	CVGuiScreen = 250,
	CPropJeep = 0,
	CPropVehicleChoreoGeneric = 0,
	CFuncPlayerGhostInfectedClip = 85,
	CFuncPlayerInfectedClip = 86,
	CTriggerPlayerMovement = 248,
	CBaseTrigger = 28,
	CTest_ProxyToggle_Networkable = 242,
	CBaseTeamObjectiveResource = 25,
	CTeam = 188,
	CFlare = 0,
	CSun = 183,
	CParticlePerformanceMonitor = 123,
	CSpotlightEnd = 177,
	CSlideshowDisplay = 164,
	CShadowControl = 161,
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
	CTEDust = 209,
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
	CScriptBaseButton = 159,
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
	CBaseCombatWeapon = 11,
};