//////////////////////////////////////////////////////////////////////////////
// Filename    : SkillHandlerManager.cpp 
// Written By  : Elca
// Description : 
//////////////////////////////////////////////////////////////////////////////

#include "SkillHandlerManager.h"
#include "Assert.h"

// ÀÏ¹Ý °ø°Ý
#include "AttackMelee.h"
#include "AttackArms.h"

// °Ë°è¿­
#include "DoubleImpact.h"
#include "TripleSlasher.h"
#include "RainbowSlasher.h"
#include "ThunderSpark.h"
#include "DancingSword.h"
#include "CrossCounter.h"
#include "FlashSliding.h"
#include "LightningHand.h"
#include "SwordWave.h"
#include "SnakeCombo.h"
#include "WindDivider.h"
#include "ThunderBolt.h"
#include "Expansion.h"
#include "MiracleShield.h"
#include "ThunderFlash.h"
#include "ThunderStorm.h"
#include "MentalSword.h"
#include "SwordRay.h"
#include "HitConvert.h"

// µµ°è¿­
#include "SingleBlow.h"
#include "SpiralSlay.h"
#include "TripleBreak.h"
#include "WildSmash.h"
#include "GhostBlade.h"
#include "PotentialExplosion.h"
#include "ShadowWalk.h"
#include "ChargingPower.h"
#include "HurricaneCombo.h"
#include "TornadoSever.h"
#include "Earthquake.h"
#include "Berserker.h"
#include "MoonlightSever.h"
#include "ShadowDancing.h"
#include "Typhoon.h"
#include "AirShield.h"
#include "PowerOfLand.h"
#include "MultiAmputate.h"
#include "WildTyphoon.h"
#include "BatBreak.h"
// ±ºÀÎ °è¿­
#include "QuickFire.h"
#include "DoubleShot.h"
#include "TripleShot.h"
#include "MultiShot.h"
#include "HeadShot.h"
#include "Piercing.h"
#include "Sniping.h"
#include "MindControl.h"
#include "Revealer.h"
#include "CreateBomb.h"
#include "CreateMine.h"
#include "InstallMine.h"
#include "DisarmMine.h"
#include "ObservingEye.h"
#include "BulletOfLight.h"
#include "Concealment.h"
#include "UltimateBlow.h"

// ÀÎÃ¦ °è¿­
#include "CreateHolyWater.h"
#include "Light.h"
#include "DetectHidden.h"
#include "AuraBall.h"
#include "Bless.h"
#include "Bless2.h"
#include "ContinualLight.h"
#include "Flare.h"
#include "Purify.h"
#include "AuraRing.h"
#include "Striking.h"
#include "Striking2.h"
#include "DetectInvisibility.h"
//#include "Identify.h"
#include "AuraShield.h"
//#include "Enchant.h"
#include "Visible.h"
#include "VigorDrop.h"
#include "Sanctuary.h"
#include "Reflection.h"
#include "Hymn.h"
#include "LightBall.h"
#include "Rebuke.h"
#include "SpiritGuard.h"
#include "Requital.h"
#include "Lightness.h"

// Èú¸µ °è¿­
#include "CureLightWounds.h"
#include "CurePoison.h"
#include "ProtectionFromPoison.h"
#include "CauseLightWounds.h"
#include "CureSeriousWounds.h"
#include "RemoveCurse.h"
#include "ProtectionFromCurse.h"
#include "CauseSeriousWounds.h"
#include "CureCriticalWounds.h"
#include "ProtectionFromAcid.h"
#include "Sacrifice.h"
#include "CauseCriticalWounds.h"
#include "CureAll.h"
#include "Regeneration.h"
#include "GloryGround.h"
#include "Resurrect.h"
#include "EnergyDrop.h"
#include "Peace.h"
#include "Activation.h"
#include "HolyBlast.h"
//#include "MassCure.h"
//#include "MassHeal.h"
#include "HolyArrow.h"
#include "TurnUndead.h"
#include "DenialMagic.h"
#include "Illendue.h"


// ¹ìÇÁ °è¿­
#include "BloodDrain.h"

#include "PoisonousHands.h"
#include "GreenPoison.h"
#include "YellowPoison.h"
#include "DarkBluePoison.h"
#include "GreenStalker.h"

#include "AcidTouch.h"
#include "AcidBolt.h"
#include "AcidBall.h"
#include "AcidSwamp.h"

#include "Paralyze.h"
#include "Doom.h"
#include "Seduction.h"
//#include "Blind.h"
//#include "Death.h"

#include "BloodyNail.h"
#include "BloodyKnife.h"
#include "BloodyBall.h"
#include "BloodyWave.h"
#include "BloodyMasterWave.h"
#include "BloodyWarp.h"
#include "BloodySpear.h"
#include "BloodyWall.h"
#include "BloodySnake.h"
#include "BloodyBreaker.h"
#include "RapidGliding.h"

#include "Hide.h"
#include "Darkness.h"
#include "Invisibility.h"
#include "TransformToWolf.h"
#include "TransformToBat.h"

//#include "SummonWolf.h"
#include "SummonCasket.h"
#include "OpenCasket.h"
//#include "RaisingDead.h"
//#include "SummonServant.h"

#include "BloodyMarker.h"
#include "BloodyTunnel.h"

#include "PoisonStrike.h"
#include "AcidStrike.h"
#include "BloodyStrike.h"
#include "PoisonStorm.h"
#include "AcidStorm.h"
#include "BloodySkull.h"
#include "BloodyStorm.h"
#include "Extreme.h"

#include "Unburrow.h"
#include "Untransform.h"

#include "EatCorpse.h"
#include "Howl.h"
#include "ThrowHolyWater.h"

#include "Restore.h"

#include "Uninvisibility.h"
#include "Death.h"
#include "Transfusion.h"
#include "Mephisto.h"


// ±âÅ¸ °è¿­
#include "CriticalGround.h"
#include "SummonMonsters.h"
#include "GroundAttack.h"
#include "MeteorStrike.h"

#include "Hallucination.h"
#include "DuplicateSelf.h"

// 2002.10.23
#include "SoulChain.h"

// 2002.12.26
#include "SharpShield.h"
#include "WideLightning.h"
#include "GunShotGuidance.h"

#include "HandsOfWisdom.h"
#include "Armageddon.h"

// ¼ºÁö½ºÅ³
#include "MagicElusion.h"
#include "PoisonMesh.h"
#include "ChainOfDemon.h"
#include "IllusionOfAvenge.h"
#include "WillOfLife.h"

// ¾Æ¿ì½ºÅÍÁî ½ºÅ³
#include "Flourish.h"
#include "Evade.h"
#include "SharpRound.h"
#include "BackStab.h"
#include "Blunting.h"
#include "GammaChop.h"
#include "CrossGuard.h"
#include "KasasArrow.h"
#include "HandsOfFire.h"
#include "Prominence.h"
#include "RingOfFlare.h"
#include "BlazeBolt.h"
#include "IceField.h"
#include "WaterBarrier.h"
#include "NymphRecovery.h"
#include "Liberty.h"
#include "Tendril.h"

#include "StoneAuger.h"
#include "EarthsTeeth.h"
#include "AbsorbSoul.h"
#include "GnomesWhisper.h"
#include "HandsOfNizie.h"
#include "RefusalEther.h"

#include "EmissionWater.h"
#include "BeatHead.h"
#include "DivineSpirits.h"

#include "BlitzSliding.h"
#include "JabbingVein.h"
#include "GreatHeal.h"
#include "GreatHeal2.h"
#include "DivineGuidance.h"
#include "BlazeWalk.h"
#include "BloodyZenith.h"

#include "Rediance.h"
#include "LarSlash.h"
#include "Trident.h"
#include "HeartCatalyst.h"
#include "ProtectionFromBlood.h"

#include "MoleShot.h"
#include "Eternity.h"
#include "InstallTrap.h"
#include "HolyArmor.h"
#include "HolyArmor2.h"
#include "MercyGround.h"
#include "CreateHolyPotion.h"

#include "TransformToWerwolf.h"
#include "GrayDarkness.h"
#include "StoneSkin.h"
#include "TalonOfCrow.h"
#include "BiteOfDeath.h"
#include "AcidEruption.h"
#include "Teleport.h"
#include "FirePiercing.h"
#include "SoulRebirth.h"
#include "IceLance.h"
#include "ExplosionWater.h"
#include "FrozenArmor.h"
#include "ReactiveArmor.h"
#include "MagnumSpear.h"
#include "HellFire.h"
#include "GroundBless.h"

#include "SharpChakram.h"
#include "DestructionSpear.h"
#include "ShiftBreak.h"
#include "FatalSnick.h"
#include "ChargingAttack.h"
#include "DuckingWallop.h"
#include "DistanceBlitz.h"
#include "SummonGroundElemental.h"
#include "SummonFireElemental.h"
#include "SummonWaterElemental.h"
#include "MeteorStorm.h"
#include "WideIceField.h"

#include "Glacier1.h"
#include "Glacier2.h"
#include "IceAuger.h"
#include "IceHail.h"
#include "WideIceHail.h"
#include "IceWave.h"

#include "LandMineExplosion.h"
#include "ClaymoreExplosion.h"
#include "PleasureExplosion.h"
#include "DeleoEfficio.h"
#include "ReputoFactum.h"

#include "SwordOfThor.h"
#include "BurningSolCharging.h"
#include "BurningSolLaunch.h"
#include "SweepVice.h"
#include "Whitsuntide.h"
#include "ViolentPhantom.h"
#include "InstallTurret.h"
#include "TurretFire.h"
#include "SummonGoreGland.h"
#include "GoreGlandFire.h"
#include "ThrowingAxe.h"
#include "ChoppingFirewood.h"
#include "ChainThrowingAxe.h"
#include "MultiThrowingAxe.h"
#include "PlayingWithFire.h"

#include "InfinityThunderbolt.h"
#include "SpitStream.h"
#include "PlasmaRocketLauncher.h"
#include "BombingStar.h"
#include "IntimateGrail.h"
#include "NooseOfWraith.h"
#include "SetAfire.h"

// ¾Æ¿ì½ºÅÍÁî 140·¹º§ ½ºÅ³
#include "SharpHail.h"
#include "IceHorizon.h"
#include "FuryOfGnome.h"
#include "SummonMiga.h"
#include "SummonMigaAttack.h"
#include "Cannonade.h"
#include "SelfDestruction.h"
#include "ARAttack.h"
#include "SMGAttack.h"
#include "GrenadeAttack.h"

// ½ÂÁ÷ ½ºÅ³
#include "Halo.h"
#include "Destinies.h"
#include "FierceFlame.h"
#include "ShadowOfStorm.h"
#include "WildWolf.h"
#include "Aberration.h"
#include "DragonTornado.h"
#include "BikeCrash.h"
#include "HarpoonBomb.h"
#include "PassingHeal.h"
#include "PassingHeal2.h"
#include "RottenApple.h"
// add by coffee 2007-3-1
#include "BloodyScarify.h"		//ÑªÖ®ÀÓÓ¡
#include "BloodCurse.h"			//ÑªÖ®?Öä

#include "ShineSword.h"			 //ÉÁÒ«Ö®½£ (ÈËÀà ½£¼¼ÄÜ)]
#include "BombCrashWalk.h"		//¾ÞÅÚºäÕ¨
#include "SatelliteBomb.h"		//ÎÀÐÇºä»÷ (ÈËÀàÇ¹ÐÂ¼¼ÄÜ)
#include "IllusionInversion.h"	//¿Ö²À»Ã¾õ(ÈËÀàÒ½Éú)
#include "HeavenGround.h"		//ÌìÉñ½µÁÙ
// Ä§Áé
#include "DummyDrake.h"			// µÂÀ×¿Ë¿þÀÜ(»ð·¨)
#include "HydroConvergence.h"   // ¸´ºÏË®ÁÆ(Ë®·¨)
#include "SummonClay.h"			// Õ³ÍÁÕÙ»½(ÍÁ·¨)
#include "HeterChakram.h"		// ÏÄ²¼Àû»ùÒò(ÃôÕ½)
#include "SkyFire.h"                                               //386 ÌìÀ×»ð»¨ ADD BY RALLSER
#include "CutStorm.h"                                        //387 ADD BY RALLSER
#include "XRLMissile.h"                                        //388 ADD BY RALLSER
#include "SacredStamp.h"                                  //389 ADD BY RALLSER
#include "BrambleHalo.h"                                   //390 ADD BY RALLSER
#include "DeadlyClaw.h"                                                                    //391ÖÂÉËÁÑ×¦ add by rallser
#include "VoodooRing.h"                            //392 ADD BY RALLSER
#include "PenetrateWheel.h"                   //393 ADD BY RALLSER
#include "FireMeteor.h"                           //394 ADD BY RALLSER
#include "BigRockfall.h"                       //395 ADD BY RALLSER
#include "RapidFreeze.h"                        //396 ADD BY RALLSER
#include "EaglesEye1.h"                        //396 ADD BY RALLSER
#include "EaglesEye2.h"                        //396 ADD BY RALLSER
#include "MagicShield1.h"
#include "MagicShield2.h"
#include "BloodyShout1.h"
#include "BloodyShout2.h"
#include "RageOfBlood.h"
#include "BloodyWings.h"
#include "FreezeRing1.h"
#include "FreezeRing2.h"
#include "CurseOfBlood1.h"
#include "CurseOfBlood2.h"
#include "MistOfSoul1.h"
#include "MistOfSoul2.h"
#include "EnergyBurst.h"
#include "BatStorm.h"
#include "BatStorm2.h"
#include "SquallyBarrier1.h"
#include "SquallyBarrier2.h"
#include "MagmaDetonation1.h"
#include "MagmaDetonation2.h"
#include "BlazeWalk2.h"
#include "Gladiator.h"
#include "CrushingStorm.h"
#include "SatelliteBomb2.h"		//ÎÀÐÇºä»÷ (ÈËÀàÇ¹ÐÂ¼¼ÄÜ)
#include "IntimateGrail2.h"		//ÎÀÐÇºä»÷ (ÈËÀàÇ¹ÐÂ¼¼ÄÜ)
#include "AllysterWind.h"		//ÎÀÐÇºä»÷ (ÈËÀàÇ¹ÐÂ¼¼ÄÜ)
#include "FlameSight.h"		//ÎÀÐÇºä»÷ (ÈËÀàÇ¹ÐÂ¼¼ÄÜ)
#include "LifeAquaofRadchia.h"
#include "SpiralMegalith.h"

// ´©Æ®±â ºÎÅÍ ÀÏ´Ü Ãß°¡.
#include "ChaosSplitter.h"
#include "SummonDeadlyGland.h"

// ¾Æ¿ì½ºÅÍÁî ´©Æ®±â
#include "SuddenBlast.h"
#include "TorrentialLife.h"
#include "MeteoBlaze.h"
#include "CyclingWarRock.h"

// ½½·¹ ´©Æ®±â
#include "LightingShock.h"
#include "SolaFlare.h"
#include "ViaCrucis.h"
#include "MagmaticEruption.h"

// ¾Æ¿ì ¿À½Ã±â
#include "ChakramHail.h"

#include "GaeBolt.h"

// ¸Å³×±×·Î½º ¸ó½ºÅÍ ½ºÅ³
#include "Cerberus.h"
#include "Manticoret.h"
#include "BogleB.h"
#include "BogleH.h"
#include "MassacreMenegroth.h"
#include "PlumyBoar.h"
#include "Cabracam.h"

// ¹«µÎÁú¿ë
#include "Tanning.h"

// Æ¼Æ÷Áê

#include "TiffaugesBalberithBlue.h"
#include "TiffaugesBalberithRed.h"
#include "TiffaugesBerithBlue.h"
#include "TiffaugesBerithRed.h"
#include "TiffaugesGomoryABlue.h"
#include "TiffaugesGomoryARed.h"
#include "TiffaugesGomoryBBlue.h"
#include "TiffaugesGomoryBRed.h"
#include "TiffaugesKrsnikABlue.h"
#include "TiffaugesKrsnikARed.h"
#include "TiffaugesKrsnikBBlue.h"
#include "TiffaugesKrsnikBRed.h"
#include "TiffaugesValkyrjaBlue.h"
#include "TiffaugesValkyrjaRed.h"
#include "TiffaugesPaimonBlue.h"
#include "TiffaugesPaimonRed.h"
#include "TiffaugesMorgothABlue.h"
#include "TiffaugesMorgothARed.h"
#include "TiffaugesMorgothBBlue.h"
#include "TiffaugesMorgothBRed.h"
#include "TiffaugesMorgothCBlue.h"
#include "TiffaugesMorgothCRed.h"
#include "TiffaugesGusionABlue.h"
#include "TiffaugesGusionARed.h"
#include "TiffaugesGusionBBlue.h"
#include "TiffaugesGusionBRed.h"
#include "TiffaugesGusionCBlue.h"
#include "TiffaugesGusionCRed.h"

// ¿À½Ã±â ½ºÅ³
#include "ViciousGuidance.h"
#include "SpectorInverse.h"
#include "LarStroke.h"
#include "FlameSpike.h"
#include "Blizzard.h"
#include "Demolisher.h"
#include "DragonHurricane.h"
#include "ShadyDouple.h"

// ´©Æ®±â ±âº»½ºÅ³
#include "TrueColorofVampLoad.h"
#include "TheRoarOfAwakenWarrior.h"
#include "TheRageofGuardianSpirit.h"

// end
#include "MonsterRangeSkill.h"

// global variable declaration
SkillHandlerManager * g_pSkillHandlerManager = NULL;

// ¸ó½ºÅÍ ·¹ÀÎÁö ½ºÅ³µé
MonsterRangeSkill
	g_TraslaAttack(SKILL_TRASLA_ATTACK, false),
	g_PuscaAttack(SKILL_PUSCA_ATTACK, false),
	g_NodCopilaAttack(SKILL_NOD_COPILA_ATTACK, false),
	g_NodCopilaAttack2(SKILL_NOD_COPILA_ATTACK_2, false);

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SkillHandlerManager::SkillHandlerManager () 
	
: m_SkillHandlers(NULL) , m_Size(SKILL_MAX)
{
	__BEGIN_TRY

	Assert(m_Size > 0);
	
	// ½ºÅ³ ÇÚµé·¯ ¹è¿­À» »ý¼ºÇÑ´Ù.
	m_SkillHandlers = new SkillHandler*[ m_Size ];
	
	// ½ºÅ³ ÇÚµé·¯ÀÇ ¹è¿­À» ÃÊ±âÈ­ÇÑ´Ù.
	for (int i = 0 ; i < m_Size ; i ++) 
		m_SkillHandlers[i] = NULL;
			
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SkillHandlerManager::~SkillHandlerManager () 
	
{
	__BEGIN_TRY
		
	Assert(m_SkillHandlers != NULL);

	// ½ºÅ³ ÇÚµé·¯¸¦ °¢°¢ »èÁ¦ÇÑ´Ù.
	for (int i = 0 ; i < m_Size ; i ++) 
	{
		SAFE_DELETE(m_SkillHandlers[i]);
	}
	
	// ½ºÅ³ÇÚµé·¯ ¹è¿­À» »èÁ¦ÇÑ´Ù.
	SAFE_DELETE_ARRAY(m_SkillHandlers);
			
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void SkillHandlerManager::init ()
	 
{
	__BEGIN_TRY
		
	// ±âº» °ø°Ý
	addSkillHandler(&g_AttackMelee);
	addSkillHandler(&g_AttackArms);

	// °Ë °è¿­
	addSkillHandler(&g_DoubleImpact);
	addSkillHandler(&g_TripleSlasher);
	addSkillHandler(&g_RainbowSlasher);
	addSkillHandler(&g_ThunderSpark);
	addSkillHandler(&g_DancingSword);
	addSkillHandler(&g_CrossCounter);
	addSkillHandler(&g_FlashSliding);
	addSkillHandler(&g_LightningHand);
	addSkillHandler(&g_SwordWave);
	addSkillHandler(&g_SnakeCombo);
	addSkillHandler(&g_WindDivider);
	addSkillHandler(&g_ThunderBolt);
	addSkillHandler(&g_Expansion);
	addSkillHandler(&g_MiracleShield);
	addSkillHandler(&g_ThunderFlash);
	addSkillHandler(&g_ThunderStorm);
	addSkillHandler(&g_MentalSword);

	//addSkillHandler(&g_DragonRising);
	//addSkillHandler(&g_FiveStormCrash);
	//addSkillHandler(&g_HeavensSword);

	// µµ°è¿­
	addSkillHandler(&g_SingleBlow);
	addSkillHandler(&g_SpiralSlay);
	addSkillHandler(&g_TripleBreak);
	addSkillHandler(&g_WildSmash);
	addSkillHandler(&g_GhostBlade);
	addSkillHandler(&g_PotentialExplosion);
	addSkillHandler(&g_ShadowWalk);
	addSkillHandler(&g_ChargingPower);
	addSkillHandler(&g_HurricaneCombo);
	addSkillHandler(&g_TornadoSever);
	addSkillHandler(&g_Earthquake);
	addSkillHandler(&g_Berserker);
	addSkillHandler(&g_MoonlightSever);
	addSkillHandler(&g_ShadowDancing);
	addSkillHandler(&g_Typhoon);

	// ±ºÀÎ °è¿­
	addSkillHandler(&g_QuickFire);
	addSkillHandler(&g_DoubleShot);
	addSkillHandler(&g_TripleShot);
	addSkillHandler(&g_MultiShot);
	addSkillHandler(&g_HeadShot);
	addSkillHandler(&g_Piercing);
	addSkillHandler(&g_Sniping);
	addSkillHandler(&g_MindControl);
	addSkillHandler(&g_Revealer);
	//addSkillHandler(&g_DetectMine);
	addSkillHandler(&g_InstallMine);
	addSkillHandler(&g_CreateBomb);
	addSkillHandler(&g_CreateMine);
	addSkillHandler(&g_ObservingEye);

	// ÀÎÃ¦ °è¿­
	addSkillHandler(&g_CreateHolyWater);
	addSkillHandler(&g_Light);
	addSkillHandler(&g_DetectHidden);
	addSkillHandler(&g_AuraBall);
	addSkillHandler(&g_Bless);
	addSkillHandler(&g_ContinualLight);
	addSkillHandler(&g_Flare);
	addSkillHandler(&g_Purify);
	addSkillHandler(&g_AuraRing);
	addSkillHandler(&g_Striking);
	addSkillHandler(&g_DetectInvisibility);
	//addSkillHandler(&g_Identify);
	addSkillHandler(&g_AuraShield);
	addSkillHandler(&g_VigorDrop);
	//addSkillHandler(&g_Enchant);
	addSkillHandler(&g_Visible);
	addSkillHandler(&g_Sanctuary);
	addSkillHandler(&g_Reflection);
	addSkillHandler(&g_Hymn);

	// Èú¸µ °è¿­
	addSkillHandler(&g_CureLightWounds);
	addSkillHandler(&g_CurePoison);
	addSkillHandler(&g_ProtectionFromPoison);
	addSkillHandler(&g_CauseLightWounds);
	addSkillHandler(&g_CureSeriousWounds);
	addSkillHandler(&g_RemoveCurse);
	addSkillHandler(&g_ProtectionFromCurse);
	addSkillHandler(&g_CauseSeriousWounds);
	addSkillHandler(&g_CureCriticalWounds);
	addSkillHandler(&g_ProtectionFromAcid);
	addSkillHandler(&g_Sacrifice);
	addSkillHandler(&g_CauseCriticalWounds);
	addSkillHandler(&g_Resurrect);
	addSkillHandler(&g_EnergyDrop);
	addSkillHandler(&g_CureAll);
	addSkillHandler(&g_Peace);
	addSkillHandler(&g_Activation);
	addSkillHandler(&g_HolyBlast);
	//addSkillHandler(&g_RegenerationSkill);
	//addSkillHandler(&g_MassCure);
	//addSkillHandler(&g_MassHeal);

	// ¹ìÇÁ °è¿­
	addSkillHandler(&g_BloodDrain);

	addSkillHandler(&g_PoisonousHands);
	addSkillHandler(&g_GreenPoison);
	addSkillHandler(&g_YellowPoison);
	addSkillHandler(&g_DarkBluePoison);
	addSkillHandler(&g_GreenStalker);

	addSkillHandler(&g_AcidTouch);
	addSkillHandler(&g_AcidBolt);
	addSkillHandler(&g_AcidBall);
	addSkillHandler(&g_AcidSwamp);

	addSkillHandler(&g_Paralyze);
	addSkillHandler(&g_Doom);
	addSkillHandler(&g_Seduction);
	//addSkillHandler(&g_Blind);
	addSkillHandler(&g_Death);

	addSkillHandler(&g_BloodyNail);
	addSkillHandler(&g_BloodyKnife);
	addSkillHandler(&g_BloodyBall);
	addSkillHandler(&g_BloodyWave);
	addSkillHandler(&g_BloodyMasterWave);
	addSkillHandler(&g_BloodyWarp);
	addSkillHandler(&g_BloodySpear);
	addSkillHandler(&g_BloodyWall);
	addSkillHandler(&g_BloodySnake);
	addSkillHandler(&g_BloodyBreaker);
	addSkillHandler(&g_RapidGliding);

	addSkillHandler(&g_Transfusion);
	addSkillHandler(&g_Mephisto);

	addSkillHandler(&g_Hide);
	addSkillHandler(&g_Darkness);
	addSkillHandler(&g_Invisibility);
	addSkillHandler(&g_TransformToWolf);
	addSkillHandler(&g_TransformToBat);

	//addSkillHandler(&g_SummonWolf);
	addSkillHandler(&g_SummonCasket);
	addSkillHandler(&g_OpenCasket);
	//addSkillHandler(&g_RaisingDead);
	//addSkillHandler(&g_SummonServant);
	
	addSkillHandler(&g_BloodyMarker);
	addSkillHandler(&g_BloodyTunnel);

	addSkillHandler(&g_PoisonStrike);
	addSkillHandler(&g_AcidStrike);
	addSkillHandler(&g_BloodyStrike);
	addSkillHandler(&g_PoisonStorm);
	addSkillHandler(&g_AcidStorm);
	addSkillHandler(&g_BloodyStorm);
	addSkillHandler(&g_Extreme);

	addSkillHandler(&g_Unburrow);
	addSkillHandler(&g_Untransform);
	addSkillHandler(&g_Uninvisibility);

	addSkillHandler(&g_EatCorpse);
	addSkillHandler(&g_Howl);
	addSkillHandler(&g_ThrowHolyWater);

	addSkillHandler(&g_Restore);
	
	addSkillHandler(&g_CriticalGround);
	addSkillHandler(&g_SummonMonsters);
	addSkillHandler(&g_GroundAttack);
	addSkillHandler(&g_MeteorStrike);
	addSkillHandler(&g_Hallucination);
	addSkillHandler(&g_DuplicateSelf);

	addSkillHandler(&g_SoulChain);

	addSkillHandler(&g_SharpShield);
	addSkillHandler(&g_WideLightning);
	addSkillHandler(&g_GunShotGuidance);

	addSkillHandler(&g_AirShield);
	addSkillHandler(&g_BulletOfLight);
	addSkillHandler(&g_HandsOfWisdom);
	addSkillHandler(&g_LightBall);
	addSkillHandler(&g_HolyArrow);
	addSkillHandler(&g_Rebuke);
	addSkillHandler(&g_SpiritGuard);
	addSkillHandler(&g_Regeneration);
	addSkillHandler(&g_PowerOfLand);
	addSkillHandler(&g_TurnUndead);
	addSkillHandler(&g_Armageddon);

	addSkillHandler(&g_MagicElusion);
	addSkillHandler(&g_PoisonMesh);
	addSkillHandler(&g_IllusionOfAvenge);
	addSkillHandler(&g_WillOfLife);

	addSkillHandler(&g_DenialMagic);
	addSkillHandler(&g_SwordRay);
	addSkillHandler(&g_Concealment);
	addSkillHandler(&g_Requital);
	addSkillHandler(&g_MultiAmputate);

	addSkillHandler(&g_HitConvert);
	addSkillHandler(&g_WildTyphoon);
	addSkillHandler(&g_UltimateBlow);
	addSkillHandler(&g_Illendue);
	addSkillHandler(&g_Lightness);

	addSkillHandler(&g_Flourish);
	addSkillHandler(&g_Evade);
	addSkillHandler(&g_SharpRound);
	addSkillHandler(&g_BackStab);
	addSkillHandler(&g_Blunting);
	addSkillHandler(&g_GammaChop);
	addSkillHandler(&g_CrossGuard);
	addSkillHandler(&g_KasasArrow);
	addSkillHandler(&g_HandsOfFire);
	addSkillHandler(&g_Prominence);
	addSkillHandler(&g_RingOfFlare);
	addSkillHandler(&g_BlazeBolt);
	addSkillHandler(&g_IceField);
	addSkillHandler(&g_WaterBarrier);
	addSkillHandler(&g_NymphRecovery);
	addSkillHandler(&g_Liberty);
	addSkillHandler(&g_Tendril);
	addSkillHandler(&g_StoneAuger);

	addSkillHandler(&g_EarthsTeeth);
	addSkillHandler(&g_AbsorbSoul);
	addSkillHandler(&g_GnomesWhisper);
	addSkillHandler(&g_HandsOfNizie);
	addSkillHandler(&g_RefusalEther);

	addSkillHandler(&g_EmissionWater);
	addSkillHandler(&g_BeatHead);

	addSkillHandler(&g_DivineSpirits);
	addSkillHandler(&g_BlitzSliding);
	addSkillHandler(&g_JabbingVein);
	addSkillHandler(&g_GreatHeal);
	addSkillHandler(&g_DivineGuidance);
	addSkillHandler(&g_BlazeWalk);
	addSkillHandler(&g_BloodyZenith);

	addSkillHandler(&g_Rediance);
	addSkillHandler(&g_LarSlash);
	addSkillHandler(&g_Trident);

	addSkillHandler(&g_HeartCatalyst);
	addSkillHandler(&g_ProtectionFromBlood);
	addSkillHandler(&g_MoleShot);
	addSkillHandler(&g_Eternity);

	addSkillHandler(&g_InstallTrap);
	addSkillHandler(&g_HolyArmor);
	addSkillHandler(&g_MercyGround);
	addSkillHandler(&g_CreateHolyPotion);

	addSkillHandler(&g_TransformToWerwolf);
	addSkillHandler(&g_GrayDarkness);
	addSkillHandler(&g_StoneSkin);
	addSkillHandler(&g_TalonOfCrow);
	addSkillHandler(&g_BiteOfDeath);
	addSkillHandler(&g_AcidEruption);

	addSkillHandler(&g_Teleport);
	addSkillHandler(&g_FirePiercing);
	addSkillHandler(&g_SoulRebirth);
	addSkillHandler(&g_IceLance);
	addSkillHandler(&g_ExplosionWater);
	addSkillHandler(&g_FrozenArmor);
	addSkillHandler(&g_ReactiveArmor);
	addSkillHandler(&g_MagnumSpear);
	addSkillHandler(&g_HellFire);
	addSkillHandler(&g_GroundBless);

	addSkillHandler(&g_SharpChakram);
	addSkillHandler(&g_DestructionSpear);
	addSkillHandler(&g_ShiftBreak);
	addSkillHandler(&g_FatalSnick);
	addSkillHandler(&g_ChargingAttack);
	addSkillHandler(&g_DuckingWallop);
	addSkillHandler(&g_DistanceBlitz);
	addSkillHandler(&g_SummonGroundElemental);
	addSkillHandler(&g_SummonFireElemental);
	addSkillHandler(&g_SummonWaterElemental);
	addSkillHandler(&g_MeteorStorm);
	addSkillHandler(&g_WideIceField);

	addSkillHandler(&g_Glacier1);
	addSkillHandler(&g_Glacier2);
	addSkillHandler(&g_IceAuger);
	addSkillHandler(&g_IceHail);
	addSkillHandler(&g_WideIceHail);
	addSkillHandler(&g_IceWave);

	addSkillHandler(&g_LandMineExplosion);
	addSkillHandler(&g_ClaymoreExplosion);
	addSkillHandler(&g_PleasureExplosion);

	addSkillHandler(&g_DeleoEfficio);
	addSkillHandler(&g_ReputoFactum);
	addSkillHandler(&g_SwordOfThor);
	addSkillHandler(&g_BurningSolCharging);
	addSkillHandler(&g_BurningSolLaunch);
	addSkillHandler(&g_SweepVice1);
	addSkillHandler(&g_SweepVice3);
	addSkillHandler(&g_SweepVice5);
	addSkillHandler(&g_Whitsuntide);
	addSkillHandler(&g_ViolentPhantom);
	addSkillHandler(&g_InstallTurret);
	addSkillHandler(&g_TurretFire);
	addSkillHandler(&g_SummonGoreGland);
	addSkillHandler(&g_GoreGlandFire);
	addSkillHandler(&g_ThrowingAxe);
	addSkillHandler(&g_ChoppingFirewood);
	addSkillHandler(&g_ChainThrowingAxe);
	addSkillHandler(&g_MultiThrowingAxe);
	addSkillHandler(&g_PlayingWithFire);

	addSkillHandler(&g_InfinityThunderbolt);
	addSkillHandler(&g_SpitStream);
	addSkillHandler(&g_PlasmaRocketLauncher);
	addSkillHandler(&g_IntimateGrail);
	addSkillHandler(&g_BombingStar);
	addSkillHandler(&g_SetAfire);
	addSkillHandler(&g_NooseOfWraith);

	addSkillHandler(&g_SharpHail);
	addSkillHandler(&g_IceHorizon);
	addSkillHandler(&g_FuryOfGnome);
	addSkillHandler(&g_SummonMiga);
	addSkillHandler(&g_SummonMigaAttack);
	addSkillHandler(&g_Cannonade);
	addSkillHandler(&g_SelfDestruction);
	addSkillHandler(&g_ARAttack);
	addSkillHandler(&g_SMGAttack);
	addSkillHandler(&g_GrenadeAttack);
	addSkillHandler(&g_Halo);
	addSkillHandler(&g_Destinies);
	addSkillHandler(&g_FierceFlame);
	addSkillHandler(&g_ShadowOfStorm);
	addSkillHandler(&g_WildWolf);
	addSkillHandler(&g_Aberration);
	addSkillHandler(&g_DragonTornado);
	addSkillHandler(&g_BikeCrash);
	addSkillHandler(&g_HarpoonBomb);
	addSkillHandler(&g_PassingHeal);
	addSkillHandler(&g_RottenApple);
	addSkillHandler(&g_TraslaAttack);
	addSkillHandler(&g_PuscaAttack);
	addSkillHandler(&g_NodCopilaAttack);
	addSkillHandler(&g_NodCopilaAttack2);
	// add by coffee 2007-2-17 start
	// ÎüÑª¹íÐÂ¼¼ÄÜ
	addSkillHandler(&g_BloodyScarify);
	addSkillHandler(&g_BloodCurse);
	//ÈËÀà¼¼ÄÜ
	addSkillHandler(&g_ShineSword);
	addSkillHandler(&g_BombCrashWalk);
	addSkillHandler(&g_SatelliteBomb);
	addSkillHandler(&g_IllusionInversion);
	addSkillHandler(&g_HeavenGround);
	// Ä§ÁéÐÂ¼¼ÄÜ
	addSkillHandler(&g_DummyDrake);
	addSkillHandler(&g_HydroConvergence);
	addSkillHandler(&g_SummonClay);
	addSkillHandler(&g_HeterChakram);	
        addSkillHandler(&g_SkyFire);
        addSkillHandler(&g_CutStorm);
        addSkillHandler(&g_XRLMissile);
        addSkillHandler(&g_SacredStamp);
        addSkillHandler(&g_BrambleHalo);
        addSkillHandler(&g_DeadlyClaw);
        addSkillHandler(&g_VoodooRing);
        addSkillHandler(&g_PenetrateWheel);
        addSkillHandler(&g_FireMeteor);
        addSkillHandler(&g_BigRockfall);
        addSkillHandler(&g_RapidFreeze);
        addSkillHandler(&g_EaglesEye1);
        addSkillHandler(&g_EaglesEye2);
        addSkillHandler(&g_MagicShield1);
        addSkillHandler(&g_MagicShield2);
        addSkillHandler(&g_BloodyShout1);
        addSkillHandler(&g_BloodyShout2);
        addSkillHandler(&g_BloodyWings);
        addSkillHandler(&g_FreezeRing1);
        addSkillHandler(&g_FreezeRing2);
        addSkillHandler(&g_CurseOfBlood1);
        addSkillHandler(&g_CurseOfBlood2);
           addSkillHandler(&g_MistOfSoul1);
           addSkillHandler(&g_MistOfSoul2);
           addSkillHandler(&g_EnergyBurst);
           addSkillHandler(&g_BatStorm);
           addSkillHandler(&g_BatStorm2);
	addSkillHandler(&g_SquallyBarrier1);
	addSkillHandler(&g_SquallyBarrier2);
	addSkillHandler(&g_MagmaDetonation1);
	addSkillHandler(&g_MagmaDetonation2);
	addSkillHandler(&g_BlazeWalk2);
	addSkillHandler(&g_Gladiator);
	addSkillHandler(&g_CrushingStorm);
	addSkillHandler(&g_SatelliteBomb2);
	addSkillHandler(&g_IntimateGrail2);
	addSkillHandler(&g_HolyArmor2);
	addSkillHandler(&g_Bless2);
	addSkillHandler(&g_Striking2);
	addSkillHandler(&g_GloryGround);
	addSkillHandler(&g_GreatHeal2);
	addSkillHandler(&g_PassingHeal2);
	addSkillHandler(&g_BloodySkull);
        addSkillHandler(&g_RageOfBlood);
	addSkillHandler(&g_ChainOfDemon);
	addSkillHandler(&g_AllysterWind);
	addSkillHandler(&g_FlameSight);
	addSkillHandler(&g_LifeAquaofRadchia);
	addSkillHandler(&g_SpiralMegalith);
	addSkillHandler(&g_BatBreak);
	addSkillHandler(&g_ChaosSplitter);
	addSkillHandler(&g_SummonDeadlyGland);
	addSkillHandler(&g_SuddenBlast);
	addSkillHandler(&g_CyclingWarRock);
	addSkillHandler(&g_MeteoBlaze);
	addSkillHandler(&g_TorrentialLife);
	addSkillHandler(&g_LightingShock);
	addSkillHandler(&g_SolaFlare);
	addSkillHandler(&g_ViaCrucis);
	addSkillHandler(&g_MagmaticEruption);
	addSkillHandler(&g_ChakramHail);

	addSkillHandler(&g_Cerberus);
	addSkillHandler(&g_Manticoret);
	addSkillHandler(&g_BogleB);
	addSkillHandler(&g_BogleH);
	addSkillHandler(&g_MassacreMenegroth);
	addSkillHandler(&g_PlumyBoar);
	addSkillHandler(&g_Cabracam);
	addSkillHandler(&g_GaeBolt);
	addSkillHandler(&g_Tanning);
	addSkillHandler(&g_TiffaugesBalberithBlue);
	addSkillHandler(&g_TiffaugesBalberithRed);
	addSkillHandler(&g_TiffaugesBerithBlue);
	addSkillHandler(&g_TiffaugesBerithRed);
	addSkillHandler(&g_TiffaugesValkyrjaBlue);
	addSkillHandler(&g_TiffaugesValkyrjaRed);
	addSkillHandler(&g_TiffaugesGomoryABlue);
	addSkillHandler(&g_TiffaugesGomoryARed);
	addSkillHandler(&g_TiffaugesGomoryBBlue);
	addSkillHandler(&g_TiffaugesGomoryBRed);
	addSkillHandler(&g_TiffaugesKrsnikABlue);
	addSkillHandler(&g_TiffaugesKrsnikARed);
	addSkillHandler(&g_TiffaugesKrsnikBBlue);
	addSkillHandler(&g_TiffaugesKrsnikBRed);
	addSkillHandler(&g_TiffaugesMorgothABlue);
	addSkillHandler(&g_TiffaugesMorgothARed);
	addSkillHandler(&g_TiffaugesMorgothBBlue);
	addSkillHandler(&g_TiffaugesMorgothBRed);
	addSkillHandler(&g_TiffaugesMorgothCBlue);
	addSkillHandler(&g_TiffaugesMorgothCRed);
	addSkillHandler(&g_TiffaugesGusionABlue);
	addSkillHandler(&g_TiffaugesGusionARed);
	addSkillHandler(&g_TiffaugesGusionBBlue);
	addSkillHandler(&g_TiffaugesGusionBRed);
	addSkillHandler(&g_TiffaugesGusionCBlue);
	addSkillHandler(&g_TiffaugesGusionCRed);
	addSkillHandler(&g_TiffaugesPaimonBlue);
	addSkillHandler(&g_TiffaugesPaimonRed);

	addSkillHandler(&g_Blizzard);
	addSkillHandler(&g_Demolisher);
	addSkillHandler(&g_FlameSpike);
	addSkillHandler(&g_ShadyDouple);
	addSkillHandler(&g_DragonHurricane);
	addSkillHandler(&g_LarStroke);
	addSkillHandler(&g_SpectorInverse);
	addSkillHandler(&g_ViciousGuidance);

	addSkillHandler(&g_TrueColorofVampLoad);
	addSkillHandler(&g_TheRageofGuardianSpirit);
	addSkillHandler(&g_TheRoarOfAwakenWarrior);
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void SkillHandlerManager::addSkillHandler (SkillHandler * pSkillHandler) 
	 
{
	__BEGIN_TRY
		
	if (m_SkillHandlers[ pSkillHandler->getSkillType() ] != NULL) {
		StringStream msg;
		msg << "duplicate Skill Handler, " << pSkillHandler->getSkillHandlerName () ;
		throw Error(msg.toString());
	}
	
	// ½ºÅ³ÇÚµé·¯¸¦ µî·ÏÇÑ´Ù.
	m_SkillHandlers[ pSkillHandler->getSkillType() ] = pSkillHandler;
			
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
SkillHandler * SkillHandlerManager::getSkillHandler (SkillType_t SkillType)
	
{
	__BEGIN_TRY

	// Wide Storm À» °¡Áö°í ÀÖÀ» °æ¿ì, Wide Ã³¸®´Â ?ø·?±â¼ú ¾È¿¡¼­ Ã³¸®ÇÑ´Ù.
/*	if ( SkillType == SKILL_DARKNESS_WIDE )
	{
		SkillType = SKILL_DARKNESS;
	}
	else if ( SkillType == SKILL_POISON_STORM_WIDE )
	{
		SkillType = SKILL_POISON_STORM;
	}
	else if ( SkillType == SKILL_ACID_STORM_WIDE )
	{
		SkillType = SKILL_ACID_STORM;
	}
*/
	if (m_SkillHandlers[SkillType]  == NULL) 
	{
		StringStream msg;
		msg << "None Skill Handler (Type : " << (int)SkillType << ")";
		throw Error(msg.toString());
	}
	else if (SkillType > SKILL_MAX) 
	{
		StringStream msg;
		msg << "Skill Handler Upper Bound";
		throw Error(msg.toString());
	}

	return m_SkillHandlers[SkillType];
	
	__END_CATCH
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
string SkillHandlerManager::toString () const
	
{
	__BEGIN_TRY

	StringStream msg;
	msg << "SkillHandlerManager(\n";
	for (int i = 0 ; i < m_Size ; i ++)
	{
		msg << "SkillHandlers[" << i << "] == ";
		msg	<< (m_SkillHandlers[i] == NULL ? "NULL" : m_SkillHandlers[i]->getSkillHandlerName());
		msg << "\n";
	}
	msg << ")";
	return msg.toString();

	__END_CATCH
}
	
