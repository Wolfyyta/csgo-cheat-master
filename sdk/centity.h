#pragma once
#include "../utils/utils.h"
#include "../utils/netvars/netvars.h"

#include "cclientclass.h"
#include "cvector.h"
#include "cmatrix.h"

class CEntity;
class IClientUnknown
{
public:
	constexpr CEntity* GetBaseEntity() noexcept
	{
		return utils::Call<CEntity*>(this, 7);
	}
};

class IClientRenderable
{
public:
	constexpr IClientUnknown* GetIClientUnknown() noexcept
	{
		return utils::Call<IClientUnknown*>(this, 0);
	}
};

class CModel;
class CEntity
{
public:
	enum EFlags : std::int32_t
	{
		FL_ONGROUND = (1 << 0),
		FL_DUCKING = (1 << 1),
		FL_ANIMDUCKING = (1 << 2),
		FL_WATERJUMP = (1 << 3),
		FL_ONTRAIN = (1 << 4),
		FL_INRAIN = (1 << 5),
		FL_FROZEN = (1 << 6),
		FL_ATCONTROLS = (1 << 7),
		FL_CLIENT = (1 << 8),
		FL_FAKECLIENT = (1 << 9),
		FL_INWATER = (1 << 10),
		FL_FLY = (1 << 11),
		FL_SWIM = (1 << 12),
		FL_CONVEYOR = (1 << 13),
		FL_NPC = (1 << 14),
		FL_GODMODE = (1 << 15),
		FL_NOTARGET = (1 << 16),
		FL_AIMTARGET = (1 << 17),
		FL_PARTIALGROUND = (1 << 18),
		FL_STATICPROP = (1 << 19),
		FL_GRAPHED = (1 << 20),
		FL_GRENADE = (1 << 21),
		FL_STEPMOVEMENT = (1 << 22),
		FL_DONTTOUCH = (1 << 23),
		FL_BASEVELOCITY = (1 << 24),
		FL_WORLDBRUSH = (1 << 25),
		FL_OBJECT = (1 << 26),
		FL_KILLME = (1 << 27),
		FL_ONFIRE = (1 << 28),
		FL_DISSOLVING = (1 << 29),
		FL_TRANSRAGDOLL = (1 << 30),
		FL_UNBLOCKABLE_BY_PLAYER = (1 << 31)
	};

	enum EWeaponType : int
	{
		WEAPONTYPE_KNIFE = 0,
		WEAPONTYPE_PISTOL = 1,
		WEAPONTYPE_SUBMACHINEGUN = 2,
		WEAPONTYPE_RIFLE = 3,
		WEAPONTYPE_SHOTGUN = 4,
		WEAPONTYPE_SNIPER = 5,
		WEAPONTYPE_MACHINEGUN = 6,
		WEAPONTYPE_C4 = 7,
		WEAPONTYPE_PLACEHOLDER = 8,
		WEAPONTYPE_GRENADE = 9,
		WEAPONTYPE_HEALTHSHOT = 11,
		WEAPONTYPE_FISTS = 12,
		WEAPONTYPE_BREACHCHARGE = 13,
		WEAPONTYPE_BUMPMINE = 14,
		WEAPONTYPE_TABLET = 15,
		WEAPONTYPE_MELEE = 16
	};

	enum EItemDefinitionIndex : short
	{
		WEAPON_NONE = 0,
		WEAPON_DEAGLE = 1,
		WEAPON_ELITE = 2,
		WEAPON_FIVESEVEN = 3,
		WEAPON_GLOCK = 4,
		WEAPON_AK47 = 7,
		WEAPON_AUG = 8,
		WEAPON_AWP = 9,
		WEAPON_FAMAS = 10,
		WEAPON_G3SG1 = 11,
		WEAPON_GALILAR = 13,
		WEAPON_M249 = 14,
		WEAPON_M4A1 = 16,
		WEAPON_MAC10 = 17,
		WEAPON_P90 = 19,
		WEAPON_ZONE_REPULSOR = 20,
		WEAPON_MP5SD = 23,
		WEAPON_UMP45 = 24,
		WEAPON_XM1014 = 25,
		WEAPON_BIZON = 26,
		WEAPON_MAG7 = 27,
		WEAPON_NEGEV = 28,
		WEAPON_SAWEDOFF = 29,
		WEAPON_TEC9 = 30,
		WEAPON_TASER = 31,
		WEAPON_HKP2000 = 32,
		WEAPON_MP7 = 33,
		WEAPON_MP9 = 34,
		WEAPON_NOVA = 35,
		WEAPON_P250 = 36,
		WEAPON_SHIELD = 37,
		WEAPON_SCAR20 = 38,
		WEAPON_SG556 = 39,
		WEAPON_SSG08 = 40,
		WEAPON_KNIFE_GG = 41,
		WEAPON_KNIFE = 42,
		WEAPON_FLASHBANG = 43,
		WEAPON_HEGRENADE = 44,
		WEAPON_SMOKEGRENADE = 45,
		WEAPON_MOLOTOV = 46,
		WEAPON_DECOY = 47,
		WEAPON_INCGRENADE = 48,
		WEAPON_C4 = 49,
		WEAPON_HEALTHSHOT = 57,
		WEAPON_KNIFE_T = 59,
		WEAPON_M4A1_SILENCER = 60,
		WEAPON_USP_SILENCER = 61,
		WEAPON_CZ75A = 63,
		WEAPON_REVOLVER = 64,
		WEAPON_TAGRENADE = 68,
		WEAPON_FISTS = 69,
		WEAPON_BREACHCHARGE = 70,
		WEAPON_TABLET = 72,
		WEAPON_MELEE = 74,
		WEAPON_AXE = 75,
		WEAPON_HAMMER = 76,
		WEAPON_SPANNER = 78,
		WEAPON_KNIFE_GHOST = 80,
		WEAPON_FIREBOMB = 81,
		WEAPON_DIVERSION = 82,
		WEAPON_FRAG_GRENADE = 83,
		WEAPON_SNOWBALL = 84,
		WEAPON_BUMPMINE = 85,
		WEAPON_KNIFE_BAYONET = 500,
		WEAPON_KNIFE_CSS = 503,
		WEAPON_KNIFE_FLIP = 505,
		WEAPON_KNIFE_GUT = 506,
		WEAPON_KNIFE_KARAMBIT = 507,
		WEAPON_KNIFE_M9_BAYONET = 508,
		WEAPON_KNIFE_TACTICAL = 509,
		WEAPON_KNIFE_FALCHION = 512,
		WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
		WEAPON_KNIFE_BUTTERFLY = 515,
		WEAPON_KNIFE_PUSH = 516,
		WEAPON_KNIFE_CORD = 517,
		WEAPON_KNIFE_CANIS = 518,
		WEAPON_KNIFE_URSUS = 519,
		WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
		WEAPON_KNIFE_OUTDOOR = 521,
		WEAPON_KNIFE_STILETTO = 522,
		WEAPON_KNIFE_WIDOWMAKER = 523,
		WEAPON_KNIFE_SKELETON = 525,
		GLOVE_STUDDED_BROKENFANG = 4725,
		GLOVE_STUDDED_BLOODHOUND = 5027,
		GLOVE_T = 5028,
		GLOVE_CT = 5029,
		GLOVE_SPORTY = 5030,
		GLOVE_SLICK = 5031,
		GLOVE_LEATHER_HANDWRAPS = 5032,
		GLOVE_MOTORCYCLE = 5033,
		GLOVE_SPECIALIST = 5034,
		GLOVE_STUDDED_HYDRA = 5035,
		SPECIAL_AGENT_BLUEBERRIES_BUCKSHOT = 4619,
		SPECIAL_AGENT_TWO_TIMES_MCCOY_TACP = 4680,
		SPECIAL_AGENT_COMMANDOR_MAE_JAMISON = 4711,
		SPECIAL_AGENT_1ST_LIEUTENANT_FARLOW,
		SPECIAL_AGENT_JOHN_KASK,
		SPECIAL_AGENT_BIO_HAZ_SPECIALIST,
		SPECIAL_AGENT_SERGEANT_BOMBSON,
		SPECIAL_AGENT_CHEM_HAZ_SPECIALIST,
		SPECIAL_AGENT_REZAN_THE_REDSHIRT = 4718,
		SPECIAL_AGENT_SIR_BLOODY_MIAMI_DARRYL = 4726,
		SPECIAL_AGENT_SAFECRACKER_VOLTZMANN,
		SPECIAL_AGENT_LITTLE_KEV,
		SPECIAL_AGENT_GETAWAY_SALLY = 4730,
		SPECIAL_AGENT_NUMBER_K = 4732,
		SPECIAL_AGENT_SIR_BLOODY_SILENT_DARRYL = 4733,
		SPECIAL_AGENT_SIR_BLOODY_SKULLHEAD_DARRYL,
		SPECIAL_AGENT_SIR_BLOODY_DARRYL_ROYALE,
		SPECIAL_AGENT_SIR_BLOODY_LOUDMOUTH_DARRYL,
		SPECIAL_AGENT_T = 5036,
		SPECIAL_AGENT_CT = 5037,
		SPECIAL_AGENT_GROUND_REBEL = 5105,
		SPECIAL_AGENT_OSIRIS,
		SPECIAL_AGENT_SHAHMAT,
		SPECIAL_AGENT_MUHLIK,
		SPECIAL_AGENT_SOLDIER = 5205,
		SPECIAL_AGENT_ENFORCER,
		SPECIAL_AGENT_SLINGSHOT,
		SPECIAL_AGENT_STREET_SOLDIER,
		SPECIAL_AGENT_OPERATOR = 5305,
		SPECIAL_AGENT_MARKUS_DELROW,
		SPECIAL_AGENT_MICHAEL_SYFERS,
		SPECIAL_AGENT_AVA,
		SPECIAL_AGENT_3RD_COMMANDO_COMPANY = 5400,
		SPECIAL_AGENT_SEAL_TEAM_6_SOLDIER,
		SPECIAL_AGENT_BUCKSHOT,
		SPECIAL_AGENT_TWO_TIMES_MCCOY_USAF,
		SPECIAL_AGENT_RICKSAW,
		SPECIAL_AGENT_DRAGOMIR = 5500,
		SPECIAL_AGENT_MAXIMUS,
		SPECIAL_AGENT_REZAN_THE_READY,
		SPECIAL_AGENT_BLACKWOLF = 5503,
		SPECIAL_AGENT_THE_DOCTOR,
		SPECIAL_AGENT_DRAGOMIR_FOOTSOLDIERS,
		SPECIAL_AGENT_B_SQUADRON_OFFICER = 5601
	};

	NETVAR(GetFlags, "CBasePlayer->m_fFlags", std::int32_t);
	NETVAR(IsScoped, "CCSPlayer->m_bIsScoped", bool);
	NETVAR(IsDefusing, "CCSPlayer->m_bIsDefusing", bool);
	NETVAR(HasGunGameImmunity, "CCSPlayer->m_bGunGameImmunity", bool);
	NETVAR(GetClip, "CBaseCombatWeapon->m_iClip1", int);
	NETVAR(GetItemDefinitionIndex, "CBaseAttributableItem->m_iItemDefinitionIndex", short);
	NETVAR(Account, "CCSPlayer->m_iAccount", int);
	//NETVAR(GetPoseParameter, "CBaseAnimating->m_flPoseParameter", std::array<float, 24>&);

	inline std::array<float, 24>& GetPoseParams() noexcept
	{
		static const std::uint32_t offset = netvars::data[hash::CompileTime("CBaseAnimating->m_flPoseParameter")];
		return *reinterpret_cast<std::add_pointer_t<std::array<float, 24>&>>(std::uintptr_t(this) + offset);
	}

	constexpr void UpdateClientSideAnimations() noexcept
	{
		utils::Call<void>(this, 224);
	}

	constexpr void UpdateCollisionBounds() noexcept
	{
		utils::Call<void>(this, 340);
	}

	constexpr CModel* GetModel() noexcept
	{
		return utils::Call<CModel*>(this + 0x4, 8);
	}

	constexpr bool SetupBones(CMatrix3x4* out, std::int32_t max, std::int32_t mask, float currentTime) noexcept
	{
		return utils::Call<bool>(this + 0x4, 13, out, max, mask, currentTime);
	}

	constexpr CClientClass* GetClientClass() noexcept
	{
		return utils::Call<CClientClass*>(this + 0x8, 2);
	}

	constexpr bool IsDormant() noexcept
	{
		return utils::Call<bool>(this + 0x8, 9);
	}

	constexpr std::int32_t GetIndex() noexcept
	{
		return utils::Call<std::int32_t>(this + 0x8, 10);
	}

	constexpr const CVector& GetAbsOrigin() noexcept
	{
		return utils::Call<const CVector&>(this, 10);
	}

	constexpr std::int32_t GetTeam() noexcept 
	{
		return utils::Call<std::int32_t>(this, 88);
	}

	constexpr std::int32_t GetHealth() noexcept
	{
		return utils::Call<std::int32_t>(this, 122);
	}

	constexpr bool IsAlive() noexcept 
	{
		return utils::Call<bool>(this, 156);
	}

	constexpr bool IsPlayer() noexcept 
	{
		return utils::Call<bool>(this, 158);
	}

	constexpr bool IsWeapon() noexcept
	{
		return utils::Call<bool>(this, 166);
	}

	constexpr CEntity* GetActiveWeapon() noexcept
	{
		return utils::Call<CEntity*>(this, 268);
	}

	constexpr void GetEyePosition(CVector& eyePosition) noexcept
	{
		utils::Call<void>(this, 285, std::ref(eyePosition));
	}

	constexpr CEntity* GetObserverTarget() noexcept
	{
		return utils::Call<CEntity*>(this, 295);
	}

	constexpr void GetAimPunch(CVector& aimPunch) noexcept
	{
		utils::Call<void>(this, 346, std::ref(aimPunch));
	}

	constexpr int GetWeaponType() noexcept
	{
		return utils::Call<int>(this, 455);
	}
};
