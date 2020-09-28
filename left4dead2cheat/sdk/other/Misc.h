#pragma once
#include <Windows.h>
#include <cstdint>
#include <intrin.h>
#include "..\math\vector.h"
typedef void* (*create_interface_fn)(const char* name, int* return_code);
#define IN_ATTACK					(1 << 0)
#define IN_JUMP						(1 << 1)
#define IN_DUCK						(1 << 2)
#define IN_FORWARD					(1 << 3)
#define IN_BACK						(1 << 4)
#define IN_USE						(1 << 5)
#define IN_CANCEL					(1 << 6)
#define IN_LEFT						(1 << 7)
#define IN_RIGHT					(1 << 8)
#define IN_MOVELEFT					(1 << 9)
#define IN_MOVERIGHT				(1 << 10)
#define IN_ATTACK2					(1 << 11)
#define IN_RUN						(1 << 12)
#define IN_RELOAD					(1 << 13)
#define IN_ALT1						(1 << 14)
#define IN_ALT2						(1 << 15)
#define IN_SCORE					(1 << 16)   /**< Used by client.dll for when scoreboard is held down */
#define IN_SPEED					(1 << 17)	/**< Player is holding the speed key */
#define IN_WALK						(1 << 18)	/**< Player holding walk key */
#define IN_ZOOM						(1 << 19)	/**< Zoom key for HUD zoom */
#define IN_WEAPON1					(1 << 20)	/**< weapon defines these bits */
#define IN_WEAPON2					(1 << 21)	/**< weapon defines these bits */
#define IN_BULLRUSH					(1 << 22)
#define IN_GRENADE1					(1 << 23)	/**< grenade 1 */
#define IN_GRENADE2					(1 << 24)	/**< grenade 2 */
#define IN_ATTACK3					(1 << 25)
// Note: these are only for use with GetEntityFlags and SetEntityFlags
//       and may not match the game's actual, internal m_fFlags values.
// PLAYER SPECIFIC FLAGS FIRST BECAUSE WE USE ONLY A FEW BITS OF NETWORK PRECISION
#define	FL_ONGROUND					(1 << 0)	/**< At rest / on the ground */
#define FL_DUCKING					(1 << 1)	/**< Player flag -- Player is fully crouched */
#define	FL_WATERJUMP				(1 << 2)	/**< player jumping out of water */
#define FL_ONTRAIN					(1 << 3)	/**< Player is _controlling_ a train, so movement commands should be ignored on client during prediction. */
#define FL_INRAIN					(1 << 4)	/**< Indicates the entity is standing in rain */
#define FL_FROZEN					(1 << 5)	/**< Player is frozen for 3rd person camera */
#define FL_ATCONTROLS				(1 << 6)	/**< Player can't move, but keeps key inputs for controlling another entity */
#define	FL_CLIENT					(1 << 7)	/**< Is a player */
#define FL_FAKECLIENT				(1 << 8)	/**< Fake client, simulated server side; don't send network messages to them */
// NOTE if you move things up, make sure to change this value
#define PLAYER_FLAG_BITS		9
// NON-PLAYER SPECIFIC (i.e., not used by GameMovement or the client .dll ) -- Can still be applied to players, though
#define	FL_INWATER					(1 << 9)	/**< In water */
#define	FL_FLY						(1 << 10)	/**< Changes the SV_Movestep() behavior to not need to be on ground */
#define	FL_SWIM						(1 << 11)	/**< Changes the SV_Movestep() behavior to not need to be on ground (but stay in water) */
#define	FL_CONVEYOR					(1 << 12)
#define	FL_NPC						(1 << 13)
#define	FL_GODMODE					(1 << 14)
#define	FL_NOTARGET					(1 << 15)
#define	FL_AIMTARGET				(1 << 16)	/**< set if the crosshair needs to aim onto the entity */
#define	FL_PARTIALGROUND			(1 << 17)	/**< not all corners are valid */
#define FL_STATICPROP				(1 << 18)	/**< Eetsa static prop!		 */
#define FL_GRAPHED					(1 << 19)	/**< worldgraph has this ent listed as something that blocks a connection */
#define FL_GRENADE					(1 << 20)
#define FL_STEPMOVEMENT				(1 << 21)	/**< Changes the SV_Movestep() behavior to not do any processing */
#define FL_DONTTOUCH				(1 << 22)	/**< Doesn't generate touch functions, generates Untouch() for anything it was touching when this flag was set */
#define FL_BASEVELOCITY				(1 << 23)	/**< Base velocity has been applied this frame (used to convert base velocity into momentum) */
#define FL_WORLDBRUSH				(1 << 24)	/**< Not moveable/removeable brush entity (really part of the world, but represented as an entity for transparency or something) */
#define FL_OBJECT					(1 << 25)	/**< Terrible name. This is an object that NPCs should see. Missiles, for example. */
#define FL_KILLME					(1 << 26)	/**< This entity is marked for death -- will be freed by game DLL */
#define FL_ONFIRE					(1 << 27)	/**< You know... */
#define FL_DISSOLVING				(1 << 28)	/**< We're dissolving! */
#define FL_TRANSRAGDOLL				(1 << 29)	/**< In the process of turning into a client side ragdoll. */
#define FL_UNBLOCKABLE_BY_PLAYER	(1 << 30)	/**< pusher that can't be blocked by the player */
#define FL_FREEZING					(1 << 31)	/**< We're becoming frozen! */

template<typename Fn>
Fn callvtable(void* Base, std::int32_t Index)
{
	std::uintptr_t** uVTablePtr = static_cast<std::uintptr_t**>(Base);
	std::uintptr_t* uVTableFnBase = *uVTablePtr;
	std::uintptr_t uAddress = uVTableFnBase[Index];
	return reinterpret_cast<Fn>(uAddress);
}

struct mstudiobbox_t
{
	int bone;
	int group;
	Vector bbmin;
	Vector bbmax;
	int szhitboxnameindex;
	int m_iPad01[3];
	float m_flRadius;
	int m_iPad02[4];
};

struct mstudiohitboxset_t
{
	int	sznameindex;
	inline char* const GetName(void) const { return ((char*)this) + sznameindex; }
	int	numhitboxes;
	int	hitboxindex;
	inline mstudiobbox_t* GetHitbox(int i) const { return (mstudiobbox_t*)(((BYTE*)this) + hitboxindex) + i; };
};

struct mstudiobone_t
{
	int sznameindex;
	inline char* const GetName(void) const { return ((char*)this) + sznameindex; }
	int parent;
	int bonecontroller[6];
	Vector pos;
	float quat[4];
	Vector rot;
	Vector posscale;
	Vector rotscale;
	matrix3x4 poseToBone;
	float qAlignment[4];
	int	flags;
	int	proctype;
	int	procindex;			  // procedural rule
	mutable int	physicsbone;	// index into physically simulated bone
	inline void* GetProcedure() const { if (procindex == 0) return NULL; else return  (void*)(((BYTE*)this) + procindex); };
	int	surfacepropidx; // index into string tablefor property name
	inline char* const GetSurfaceProps(void) const { return ((char*)this) + surfacepropidx; }
	int contents;			   // See BSPFlags.h for the contents flags
	int	unused[8];			  // remove as appropriate
};

enum paintmode_t
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
	PAINT_CURSOR = (1 << 2), // software cursor, if appropriate
};

struct studiohdr_t
{
	int id;
	int version;
	int checksum;
	char name[64];
	int length;
	Vector eyeposition;
	Vector illumposition;
	Vector hull_min;
	Vector hull_max;
	Vector view_bbmin;
	Vector view_bbmax;
	int flags;
	int numbones;
	int boneindex;
	inline mstudiobone_t* GetBone(int i) const { return (mstudiobone_t*)(((BYTE*)this) + boneindex) + i; };
	int numbonecontrollers;
	int bonecontrollerindex;
	int numhitboxsets;
	int hitboxsetindex;
	mstudiohitboxset_t* GetHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((BYTE*)this) + hitboxsetindex) + i;
	}
	inline mstudiobbox_t* GetHitbox(int i, int set) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet(set);

		if (!s)
			return NULL;

		return s->GetHitbox(i);
	}
	inline int GetHitboxCount(int set) const
	{
		mstudiohitboxset_t const* s = GetHitboxSet(set);
		if (!s)
			return 0;
		return s->numhitboxes;
	}
	int numlocalanim;
	int localanimindex;
	int numlocalseq;
	int localseqindex;
	mutable int activitylistversion;
	mutable int eventsindexed;
	int numtextures;
	int textureindex;
	int numcdtextures;
	int cdtextureindex;
	int numskinref;
	int numskinfamilies;
	int skinindex;
	int numbodyparts;
	int bodypartindex;
	int numlocalattachments;
	int localattachmentindex;
	int numlocalnodes;
	int localnodeindex;
	int localnodenameindex;
	int numflexdesc;
	int flexdescindex;
	int numflexcontrollers;
	int flexcontrollerindex;
	int numflexrules;
	int flexruleindex;
	int numikchains;
	int ikchainindex;
	int nummouths;
	int mouthindex;
	int numlocalposeparameters;
	int localposeparamindex;
	int surfacepropindex;
	int keyvalueindex;
	int keyvaluesize;
	int numlocalikautoplaylocks;
	int localikautoplaylockindex;
	float mass;
	int contents;
	int numincludemodels;
	int includemodelindex;
	mutable void* virtualModel;
	int szanimblocknameindex;
	int numanimblocks;
	int animblockindex;
	mutable void* animblockModel;
	int bonetablebynameindex;
	void* pVertexBase;
	void* pIndexBase;
	BYTE constdirectionallightdot;
	BYTE rootLOD;
	BYTE numAllowedRootLODs;
	BYTE unused[1];
	int unused4;
	int numflexcontrollerui;
	int flexcontrolleruiindex;
	float flVertAnimFixedPointScale;
	int unused3[1];
	int studiohdr2index;
	int unused2[1];
};


enum GROUP
{
	GROUP_INVALID = 0,
	GROUP_BOSS,
	GROUP_SPECIAL,
	GROUP_INFECTED,
	GROUP_PLAYER
};

enum MoveType_t
{
	MOVETYPE_NONE = 0,			/**< never moves */
	MOVETYPE_ISOMETRIC,			/**< For players */
	MOVETYPE_WALK,				/**< Player only - moving on the ground */
	MOVETYPE_STEP,				/**< gravity, special edge handling -- monsters use this */
	MOVETYPE_FLY,				/**< No gravity, but still collides with stuff */
	MOVETYPE_FLYGRAVITY,		/**< flies through the air + is affected by gravity */
	MOVETYPE_VPHYSICS,			/**< uses VPHYSICS for simulation */
	MOVETYPE_PUSH,				/**< no clip to world, push and crush */
	MOVETYPE_NOCLIP,			/**< No gravity, no collisions, still do velocity/avelocity */
	MOVETYPE_LADDER,			/**< Used by players only when going onto a ladder */
	MOVETYPE_OBSERVER,			/**< Observer movement, depends on player's observer mode */
	MOVETYPE_CUSTOM				/**< Allows the entity to describe its own physics */
};

class weaponinfo_t
{
public:
	char pad_0000[344]; //0x0000
	int32_t m_slot; //0x0158
	int32_t m_position; //0x015C
	int32_t m_maxchip1; //0x0160
	int32_t m_maxchip2; //0x0164
	int32_t m_defchip1; //0x0168
	int32_t m_defchip2; //0x016C
	int32_t m_weight; //0x0170
	int32_t m_rumble; //0x0174
	bool N000000AD; //0x0178
	char pad_0179[3]; //0x0179
	bool N000000AE; //0x017C
	char pad_017D[2123]; //0x017D
};

struct MaterialVideoMode_t 
{
	int m_Width;
	int m_Height;
	int m_Format;
	int m_RefreshRate;
};
struct mat_sys_t
{
	// control panel stuff
	MaterialVideoMode_t m_VideoMode;
	float m_fMonitorGamma;
	float m_fGammaTVRangeMin;
	float m_fGammaTVRangeMax;
	float m_fGammaTVExponent;
	bool m_bGammaTVEnabled;

	int m_nAASamples;
	int m_nForceAnisotropicLevel;
	int skipMipLevels;
	int dxSupportLevel;
	unsigned int m_Flags;
	bool bEditMode;				// true if in Hammer.
	unsigned char proxiesTestMode;	// 0 = normal, 1 = no proxies, 2 = alpha test all, 3 = color mod all
	bool bCompressedTextures;
	bool bFilterLightmaps;
	bool bFilterTextures;
	bool bReverseDepth;
	bool bBufferPrimitives;
	bool bDrawFlat;
	bool bMeasureFillRate;
	bool bVisualizeFillRate;
	bool bNoTransparency;
	bool bSoftwareLighting;
	bool bAllowCheats;
	char nShowMipLevels;
	bool bShowLowResImage;
	bool bShowNormalMap;
	bool bMipMapTextures;
	unsigned char nFullbright;
	bool m_bFastNoBump;
	bool m_bSuppressRendering;

	// debug modes
	bool bShowSpecular; // This is the fast version that doesn't require reloading materials
	bool bShowDiffuse;  // This is the fast version that doesn't require reloading materials

	// misc
	int m_nReserved;	// Currently unused

	// No depth bias
	float m_SlopeScaleDepthBias_Normal;
	float m_DepthBias_Normal;

	// Depth bias for rendering decals closer to the camera
	float m_SlopeScaleDepthBias_Decal;
	float m_DepthBias_Decal;

	// Depth bias for biasing shadow depth map rendering away from the camera
	float m_SlopeScaleDepthBias_ShadowMap;
	float m_DepthBias_ShadowMap;

	int m_WindowedSizeLimitWidth;
	int m_WindowedSizeLimitHeight;
	int m_nAAQuality;
	bool m_bShadowDepthTexture;
	bool m_bMotionBlur;
	bool m_bSupportFlashlight;
};


enum WeaponID_t
{
	WeaponCSBase = 0,
	AssaultRifle = 5,
	AutoShotgun = 4,
	BaseBackpackItem = 0,
	BoomerClaw = 41,
	Chainsaw = 20,
	ChargerClaw = 40,
	ColaBottles = 28,
	FireworkCrate = 29,
	FirstAidKit = 12,
	GasCan = 16,
	Gnome = 27,
	GrenadeLauncher = 21,
	HunterClaw = 39,
	Adrenaline = 23,
	ItemAmmoPack = 22,
	ItemDefibrillator = 24,
	ItemUpgradePackExplosive = 31,
	ItemUpgradePackIncendiary = 30,
	VomitJar = 25,
	JockeyClaw = 44,
	Molotov = 13,
	OxygenTank = 18,
	PainPills = 15,
	PipeBomb = 14,
	Pistol = 1,
	MagnumPistol = 32,
	PropaneTank = 17,
	PumpShotgun = 3,
	AK47 = 26,
	Desert = 9,
	M60 = 37,
	SG552 = 34,
	Chrome = 8,
	SPAS = 11,
	MP5 = 33,
	Silenced = 7,
	SmokerClaw = 42,
	SniperRifle = 6,
	AWP = 35,
	Military = 10,
	Scout = 36,
	SpitterClaw = 43,
	SubMachinegun = 2,
	TankClaw = 38,
	TerrorMeleeWeapon = 19,
	WeaponSpawn = 8,
};