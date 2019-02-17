#pragma once
#include "GUI\GUI.h"
#include <filesystem>
#include "Utils\GlobalVars.h"
#include <fstream>
#include <iostream>
#include <functional>
#include <ShlObj.h>
#include "Hooks.h"

using namespace ui;
namespace fs = std::experimental::filesystem;

class Settings : public MenuMain
{
public:
    void Initialize(MenuMain* pMenuObj);

    void SaveSettings(const std::string& strFileName, MenuMain* pMenuObj);
    void LoadSettings(const std::string& strFileName, MenuMain* pMenuObj);

private:
    void UpdateDirectoryContent(const fs::path& fsPath);
    inline fs::path GetFolderPath();

    fs::path                 fsPath{};
    std::vector<std::string> vecFileNames{};

public:
    /* All our settings variables will be here  *
    * The best would be if they'd get          *
    * initialized in the class itself.         */

	int   iAlpha;

    bool  bCheatActive = true;
    bool  bMenuOpened  = false;
	bool  bMenuFullFade = false;

	class rage {
	public:

		/* Legit */

		/* Checkboxes */
		bool  bBacktrack;
		/* Checkboxes */

		/* legit */

		int   lbot_hitbox = 1;
		int   lbot_smooth = 1;
		bool  lbot_silentaim = false;
		bool  lbot_enable = false;
		bool  lbot_smoothbox = false;
		float lbot_fov = 1.f;

		/* fakelag */

		bool flag_when[3];
		int  flag_type;
		int  flag_packets = 1;

		/* slowwalk */

		bool slowwalk = false;
		int  slowwalktype = 0;

		/* ragebot */

		bool Aimbot = false;
		int Hitchance = false;
		int HitchanceValue = 1.f;
		int Mindmg = 1.f;
		bool Resolver = false;
		int BodyScale = 1.f;
		int HeadScale = 1.f;
		bool MultiPoint = false;
		bool DelayShot = false;
		bool IgnoreLimbs = false;
		bool Autostop = false;
		bool FixShotPitch = false;
		bool PosBacktrack = false;
		bool ShotBacktrack = false;
		bool BaimLethal = false;
		bool BaimPitch = false;
		bool BaimInAir = false;

		/* anti-aim */

		int JitterRange = 0;
		bool RandJitterInRange = false;
		int aapitch = 0;
		int aayaw = 0;
	};

	class visuals {
	public:

		/* Players */

		/* Colors */
		Color cBox            = { 255, 255, 255, 255 };
		Color cName           = { 255, 255, 255, 255 };
		Color cWeaponIcon     = { 255, 255, 255, 255 };
		Color cWeaponName     = { 255, 255, 255, 255 };
		Color cWeaponAmmo     = { 66, 182, 244, 255 };
		Color cSound          = { 233, 88, 243, 255 };
		Color cOffscreenESP   = { 255, 255, 255, 255 };
		Color cGlow			  = { 255, 255, 255, 255 };
		Color cSkeleton		  = { 255, 255, 255, 255 };
		/* Colors */

		/* Checkboxes */
		bool  bBox;
		bool  bDynamic;
		bool  bName;
		bool  bHealth;
		bool  bWeaponIcon;
		bool  bWeaponName;
		bool  bWeaponAmmo;
		bool  bSound;
		bool  bOffscreenESP;
		bool  bGlow;
		bool  bSkeleton;
		bool  bDormant;
		/* Checkboxes */

		/* Multibox */
		bool  bFlags[5];
		/* Multibox */

		/* Players */

		/* Player Models */

		/* Colors */
		Color cBackTrack  = { 255, 255, 255, 255 };
		Color cChams      = { 244, 241, 66, 255 };
		Color cChamsZ     = { 229, 66, 244, 255 };
		Color cLocalChams = { 66, 244, 137, 255 };
		/* Colors */

		/* Checkboxes */
		bool bChams;
		bool bChamsZ;
		bool bLocalChams;
		bool bBlend;
		bool bChamsWhileScoped;
		bool bBackTrackChams;
		/* Checkboxes */

		/* Comboboxes */
		int iTransparency = 100;
		int iMaterial;
		int iMaterialLocal;
		/* Comboboxes */

		/* Player Models */


		/* Effects */

		/*Checkboxes*/
		bool  bNoFlash;
		bool  bRemoveSmoke;
		bool  bRemoveRecoil;
		bool  bRemoveScope;
		bool  bDisablePostProcessing;
		/*Checkboxes*/

		/* Effects */

		
		/* World */

		/* Colors */
		Color cItems = { 255, 255, 255, 255 };
		Color cProjectiles = { 255, 255, 255, 255 };
		Color cBomb = { 255, 255, 255, 255 };
		/* Colors */

		/* Checkboxes */
		bool  bItems;
		bool  bProjectiles;
		bool  bBomb;
		bool  bNightmode;
		bool  bFullBright;
		/* Checkboxes */

		/* World */


		/* Other */

		/* Sliders */
		int iTracerTime;
		int iThirdpersonDistance;
		int iFov;
		int iThirdpersonFov;
		/* Sliders */

		/* Modes */
		int iThirdpersonKeybind = 2;
		/* Modes */

		/* Keybinds */
		ButtonCode_t btThirdperonKeybind;
		/* Keybinds */
		
		/* Colors */
		Color cLocalTracer = { 233, 88, 243, 255 };
		Color cLocalHurt   = { 244, 158, 66, 255 };
		Color cEnemyTracer = { 0, 255, 255, 255 };
		Color cGrenadePred = { 255, 255, 255, 255 };
		/* Colors */

		/*Checkboxes*/
		bool  bBulletTracer;
		bool  bHitmarker;
		bool  bGrenadePrediction;
		bool  bForceCrosshair;
		bool  bHitmarkerSound;
		bool  bSpecThirdperson;
		/*Checkboxes*/

		/* Other */
	};

	class misc {
	public:
		/* Checkboxes */
		bool  bWatermark = true;
		bool  bEventLogs[2];
		bool  bBhopEnabled;
		bool  bAutoStrafer;
		/* Checkboxes */
	};

	class config {
	public:
		/* Colors */
		Color cMenuColor = { 255, 255, 255, 255 };
		/* Colors */

		/* Combo Boxes */
		int cfgNumber;
		/* Combo Boxes */


	};

	class test { // delete me!
	public:
		bool bCheckbox;
		bool bMulti[3];

		int  iCombo;
		int  iList;
		int  iSlider;
		int  iKeybind;

		ButtonCode_t btKeybind;

		std::string strTextField;
	};

	rage     rage;
	visuals  visuals;
	misc     misc;
	config   config;
	test     test;
};

extern Settings g_Settings;

