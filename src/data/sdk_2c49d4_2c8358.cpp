// SPDX-License-Identifier: GPL-3.0-or-later
// Typed by hand (make_data_files.py keeps this file)
// Retail .data 0X2C8358-0X2C8914 (piece data/sdk_2c49d4), one global per Splat label as scripts/build/make_data_files.py writes them,
// but for D_002C8374: sceScfGetLanguage reads it as one byte (lbu), so it is a u8 and retail's 3 bytes after it are the padding before
// D_002C8378. Written as the generator's `unsigned char[4]`, the compiler aligns that array to 8 and every later global moves by 8
// (its .data was 0x5c8 bytes, retail's 0x5bc).

extern "C" void AddRefSharedSlotheaps_thunk();
extern "C" void CreateSharedSlotheaps_114680_thunk();
extern "C" void CreateSharedSlotheaps_1be240_thunk();
extern "C" void CreateSharedSlotheaps_1befb8_thunk();
extern "C" void CreateSharedSlotheaps_1ea410_thunk();
extern "C" void CreateSharedSlotheaps_2289f0_thunk();
extern "C" void CreateSharedSlotheaps_thunk();
extern "C" void GlobalCtorBasic();
extern "C" void GlobalCtorBbmark();
extern "C" void GlobalCtorBentley();
extern "C" void GlobalCtorBlend();
extern "C" void GlobalCtorFrameCopy();
extern "C" void GlobalCtorGuardLook();
extern "C" void GlobalCtorGuardPools_171f38();
extern "C" void GlobalCtorGuardPools_173138();
extern "C" void GlobalCtorGuardPools_174878();
extern "C" void GlobalCtorJtPools();
extern "C" void GlobalCtorMark();
extern "C" void GlobalCtorMpeg();
extern "C" void GlobalCtorMurray();
extern "C" void GlobalCtorSensor();
extern "C" void GlobalCtorSensorSight();
extern "C" void GlobalCtorSharedSlotheaps();
extern "C" void GlobalCtorSlotheaps_144618();
extern "C" void GlobalCtorSlotheaps_144b08();
extern "C" void GlobalCtorSlotheaps_14d3b8();
extern "C" void GlobalCtorSlotheaps_1a02e0();
extern "C" void GlobalCtorSlotheaps_1a0af8();
extern "C" void GlobalCtorSlotheaps_1a74f8();
extern "C" void GlobalCtorSlotheaps_1a7bf8();
extern "C" void GlobalCtorSlotheaps_1ae7b0();
extern "C" void GlobalCtorSlotheaps_1ae908();
extern "C" void GlobalCtorSlotheaps_1b2800();
extern "C" void GlobalCtorSlotheaps_1d93b8();
extern "C" void GlobalCtorSlotheaps_1e5d60();
extern "C" void GlobalCtorSlotheaps_1ed788();
extern "C" void GlobalCtorStgSwitch();
extern "C" void GlobalCtorSw();
extern "C" void GlobalCtor_14b640();
extern "C" void GlobalCtor_14b7d8();
extern "C" void GlobalInitSlotheaps();
extern "C" void GlobalInitSpliceFrameSlotheaps();
extern "C" void GlobalInitSpliceSlotheaps_126168();
extern "C" void GlobalInitSpliceSlotheaps_1262c0();
extern "C" void GlobalInitSpliceSlotheaps_126418();
extern "C" void InitArcTrailStatics_thunk();
extern "C" void InitDynamicTextStatics_thunk();
extern "C" void InitSharedSlotheaps_2_thunk();
extern "C" void InitSharedSlotheaps_3_thunk();
extern "C" void InitSharedSlotheaps_thunk();
extern "C" void InitStaticBitmapA_thunk();
extern "C" void InitStaticBitmapB_thunk();
extern "C" void InitStaticSlotheaps_frm2_thunk();
extern "C" void InitStaticSlotheaps_frm_thunk();
extern "C" void StaticInitCarryFile_thunk();
extern "C" void StaticInitCloneFile_thunk();
extern "C" void StaticInitDestroySndbank_thunk();
extern "C" void StaticInitKeypadFile_thunk();
extern "C" void StaticInitLoadingLogo_thunk();
extern "C" void StaticInitMemory_thunk();
extern "C" void StaticInitMenus_thunk();
extern "C" void StaticInitPipeFile_thunk();
extern "C" void StaticInitSharedSlotheaps_thunk();
extern "C" void StaticInitSlotheapsAlo_thunk();
extern "C" void StaticInitSlotheapsSwarm_thunk();
extern "C" void StaticInitSlotheaps_11ce08_thunk();
extern "C" void StaticInitSlotheaps_128b60_thunk();
extern "C" void StaticInitSlotheaps_12ef98_thunk();
extern "C" void StaticInitSlotheaps_12f0f0_thunk();
extern "C" void StaticInitSlotheaps_1329a8_thunk();
extern "C" void StaticInitSlotheaps_1498f8_thunk();
extern "C" void StaticInitSlotheaps_149eb0_thunk();
extern "C" void StaticInitSlotheaps_170850_thunk();
extern "C" void StaticInitSlotheaps_184750_thunk();
extern "C" void StaticInitSlotheaps_1864b8_thunk();
extern "C" void StaticInitSlotheaps_186ed8_thunk();
extern "C" void StaticInitSlotheaps_190f38_thunk();
extern "C" void StaticInitSlotheaps_1df980_thunk();
extern "C" void StaticInitSlotheaps_20d878_thunk();
extern "C" void StaticInitSlotheaps_thunk_1d5130();
extern "C" void StaticInitSly_thunk();
extern "C" void StaticInitSwSlotheaps_2_thunk();
extern "C" void StaticInitSwSlotheaps_3_thunk();
extern "C" void StaticInitSwSlotheaps_thunk();
extern "C" void StaticInit_Cnvo();
extern "C" void StaticInit_Steppipe();
extern "C" void StaticInitializeRefSlotheaps_thunk();
extern "C" void StaticInitializeSidebagSlotheaps_thunk();
extern "C" void _GLOBAL_I_bis();
extern "C" void _GLOBAL__I_button();
extern "C" void asega__static_initialization_and_destruction_0_thunk();
extern "C" void asegbl__static_initialization_and_destruction_0_thunk();
extern "C" void barrier__static_initialization_and_destruction_0_thunk();
extern "C" void bif__GLOBAL__I_slotheaps();
extern "C" void difficulty__static_initialization_and_destruction_0_thunk();
extern "C" void font__static_initialization_and_destruction_0_thunk();
extern "C" void frame__static_initialization_and_destruction_0_thunk();
extern "C" void func_00117010();
extern "C" void func_00117788();
extern "C" void func_00118648();
extern "C" void func_001195C0();
extern "C" void func_00119BA0();
extern "C" void func_00119D80();
extern "C" void func_00119ED8();
extern "C" void func_0011A030();
extern "C" void func_0011A530();
extern "C" void func_0011AFC0();
extern "C" void func_0011B188();
extern "C" void func_0011B2E0();
extern "C" void func_0011CC88();
extern "C" void func_0011E178();
extern "C" void func_001258D0();
extern "C" void func_0012ADF8();
extern "C" void func_0012B0C8();
extern "C" void func_0012B390();
extern "C" void func_0012EB28();
extern "C" void func_00130888();
extern "C" void func_001378B8();
extern "C" void func_00137A10();
extern "C" void func_00138EE8();
extern "C" void func_0013A9C8();
extern "C" void func_0013BDD0();
extern "C" void func_0013D538();
extern "C" void func_0013E348();
extern "C" void func_0014BE88();
extern "C" void func_0014C528();
extern "C" void func_0014C680();
extern "C" void func_0014FA88();
extern "C" void func_0014FC88();
extern "C" void func_001520A8();
extern "C" void func_00153988();
extern "C" void func_00153AE8();
extern "C" void func_001571E0();
extern "C" void func_001578D8();
extern "C" void func_00157A30();
extern "C" void func_001585B8();
extern "C" void func_001590F8();
extern "C" void func_0015CD48();
extern "C" void func_0015DC60();
extern "C" void func_0015E360();
extern "C" void func_00161388();
extern "C" void func_00166250();
extern "C" void func_00166900();
extern "C" void func_001672F0();
extern "C" void func_00185110();
extern "C" void func_00188468();
extern "C" void func_0018F8E8();
extern "C" void func_0019F088();
extern "C" void func_0019F3C8();
extern "C" void func_001A2BB0();
extern "C" void func_001A3000();
extern "C" void func_001A3240();
extern "C" void func_001A4DE8();
extern "C" void func_001A5250();
extern "C" void func_001AE110();
extern "C" void func_001B0B58();
extern "C" void func_001B1D98();
extern "C" void func_001BC030();
extern "C" void func_001C2900();
extern "C" void func_001C2A58();
extern "C" void func_001C2D00();
extern "C" void func_001C3D50();
extern "C" void func_001C4E30();
extern "C" void func_001CD5D0();
extern "C" void func_001CDCB0();
extern "C" void func_001D1350();
extern "C" void func_001D5788();
extern "C" void func_001D6828();
extern "C" void func_001D7218();
extern "C" void func_001D7A10();
extern "C" void func_001D7B68();
extern "C" void func_001EEC40();
extern "C" void func_001EF830();
extern "C" void func_001EFA70();
extern "C" void func_001F1748();
extern "C" void func_001F20E8();
extern "C" void func_001F8DB8();
extern "C" void func_001FAF50();
extern "C" void func_001FF7C8();
extern "C" void func_001FFCD8();
extern "C" void func_00201600();
extern "C" void func_00203928();
extern "C" void func_00205E50();
extern "C" void func_0020B820();
extern "C" void func_0020CE08();
extern "C" void func_0020D5B0();
extern "C" void func_0021D258();
extern "C" void func_0021D618();
extern "C" void func_00223F50();
extern "C" void func_002259B8();
extern "C" void func_00226530();
extern "C" void func_00226A98();
extern "C" void func_00226BF0();
extern "C" void func_00227330();
extern "C" void func_00227598();
extern "C" void func_00227B98();
extern "C" void func_00227FC8();
extern "C" void func_00229ED0();
extern "C" void func_0022B020();
extern "C" void func_0022B700();
extern "C" void func_0022C7F8();
extern "C" void func_002310E0();
extern "C" void func_002319C8();
extern "C" void func_00252788();
extern "C" void func_00252800();
extern "C" void func_00252898();
extern "C" void func_00252950();
extern "C" void func_00252A20();
extern "C" void func_00252AD0();
extern "C" void func_00252B88();
extern "C" void func_00252C80();
extern "C" void func_00252D80();
extern "C" void func_00252E20();
extern "C" void func_00252ED0();
extern "C" void func_00252FB0();
extern "C" void func_00253098();
extern "C" void func_00253170();
extern "C" void func_00253240();
extern "C" void func_00253360();
extern "C" void func_00254ED8();
extern "C" void gc__static_initialization_and_destruction_0_thunk();
extern "C" void guardposts__static_initialization_and_destruction_0_thunk();
extern "C" void pair__static_initialization_and_destruction_0_thunk();
extern "C" void proc__static_initialization_and_destruction_0_thunk();
extern "C" void static_initialization_and_destruction_0_1c3238_thunk();

// data-ok: retail's bytes at 0X2C8358
unsigned int D_002C8358[7] = {0xffffffff, 0, 0x49497350, 0x7362696c, 0x20206663, 0x30303033, 0x21c};

// data-ok: typed from sceScfGetLanguage (lbu), retail's bytes at 0X2C8374
unsigned char D_002C8374 = 0;

// data-ok: retail's bytes at 0X2C8378
unsigned char D_002C8378[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 80, 115, 73, 73, 108, 105, 98, 109, 112, 101, 103, 32, 51, 48, 48, 48};

// data-ok: retail's bytes at 0X2C8398
unsigned int D_002C8398[16] = {2, 0, 2, 0, 2, 3, 2, 3, 0, 0, 0, 0, 2, 4, 0, 6};

// data-ok: retail's bytes at 0X2C83D8
unsigned int D_002C83D8[40] = {0, 224, 0, 255, 0xffc00000, 189, 0xffffffff, 255, 0xffa00000, 189, 0xffffffff, 255, 0xffa10000, 189, 0xffffffff, 255, 0xff900000, 189, 0xffffffff, 255, 0, 192, 0, 255, 0x80000000, 189, 0xff000000, 255, 0xa0000000, 189, 0xff000000, 255, 0x88000000, 189, 0xff000000, 255, 0x90000000, 189, 0xff000000, 255};

// data-ok: retail's bytes at 0X2C8478
void *D_002C8478[8] = {(void *)func_00252788, (void *)func_00252898, (void *)func_00252A20, (void *)func_00252B88, (void *)func_00252D80, (void *)func_00252ED0, (void *)func_00253098, (void *)func_00253240};

// data-ok: retail's bytes at 0X2C8498
void *D_002C8498[10] = {(void *)func_00252800, (void *)func_00252950, (void *)func_00252AD0, (void *)func_00252C80, (void *)func_00252E20, (void *)func_00252FB0, (void *)func_00253170, (void *)func_00253360, 0, 0};

// data-ok: retail's bytes at 0X2C84C0
unsigned int D_002C84C0[16] = {0x13101008, 0x16161310, 0x16161616, 0x1b1a181a, 0x1a1a1b1b, 0x1b1b1a1a, 0x1d1d1d1b, 0x1d222222, 0x1b1b1d1d, 0x20201d1d, 0x26252222, 0x22232325, 0x28262623, 0x30302828, 0x38382e2e, 0x5345453a};

// data-ok: retail's bytes at 0X2C8500
unsigned int D_002C8500[20] = {0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x49497350, 0x6962696c, 0x20207570, 0x30303033};

// data-ok: retail's bytes at 0X2C8550
unsigned int D_002C8550[20] = {0x13101008, 0x16161310, 0x16161616, 0x1b1a181a, 0x1a1a1b1b, 0x1b1b1a1a, 0x1d1d1d1b, 0x1d222222, 0x1b1b1d1d, 0x20201d1d, 0x26252222, 0x22232325, 0x28262623, 0x30302828, 0x38382e2e, 0x5345453a, 0x10101010, 0x10101010, 0x10101010, 0x10101010};

// data-ok: retail's bytes at 0X2C85A0
unsigned int D_002C85A0[8] = {0x4210000, 0x3e00842, 0x14a51084, 0x1ce718c6, 0x2529001f, 0x7c00294a, 0x35ad318c, 0x39ce7fff};

// data-ok: retail's bytes at 0X2C85C0
void *D_002C85C0[213] = {(void *)210, (void *)CreateSharedSlotheaps_114680_thunk, (void *)InitStaticBitmapA_thunk, (void *)InitStaticBitmapB_thunk, (void *)StaticInitMemory_thunk, (void *)func_00117010, (void *)func_00117788, (void *)func_00118648, (void *)func_001195C0, (void *)func_00119BA0, (void *)func_00119D80, (void *)func_00119ED8, (void *)func_0011A030, (void *)func_0011A530, (void *)func_0011AFC0, (void *)func_0011B188, (void *)func_0011B2E0, (void *)func_0011CC88, (void *)StaticInitSlotheaps_11ce08_thunk, (void *)func_0011E178, (void *)bif__GLOBAL__I_slotheaps, (void *)func_001258D0, (void *)GlobalInitSpliceSlotheaps_126168, (void *)GlobalInitSpliceSlotheaps_1262c0, (void *)GlobalInitSpliceSlotheaps_126418, (void *)GlobalInitSpliceFrameSlotheaps, (void *)frame__static_initialization_and_destruction_0_thunk, (void *)gc__static_initialization_and_destruction_0_thunk, (void *)StaticInitSlotheaps_128b60_thunk, (void *)pair__static_initialization_and_destruction_0_thunk, (void *)proc__static_initialization_and_destruction_0_thunk, (void *)StaticInitializeRefSlotheaps_thunk, (void *)StaticInitializeSidebagSlotheaps_thunk, (void *)func_0012ADF8, (void *)func_0012B0C8, (void *)func_0012B390, (void *)CreateSharedSlotheaps_thunk, (void *)func_0012EB28, (void *)StaticInitSlotheaps_12ef98_thunk, (void *)StaticInitSlotheaps_12f0f0_thunk, (void *)func_00130888, (void *)asega__static_initialization_and_destruction_0_thunk, (void *)asegbl__static_initialization_and_destruction_0_thunk, (void *)barrier__static_initialization_and_destruction_0_thunk, (void *)StaticInitSlotheaps_1329a8_thunk, (void *)GlobalCtorBasic, (void *)GlobalCtorBbmark, (void *)GlobalCtorBentley, (void *)func_001378B8, (void *)func_00137A10, (void *)func_00138EE8, (void *)func_0013A9C8, (void *)func_0013BDD0, (void *)func_0013D538, (void *)GlobalCtorSharedSlotheaps, (void *)func_0013E348, (void *)GlobalCtorJtPools, (void *)GlobalCtorSlotheaps_144618, (void *)GlobalCtorSlotheaps_144b08, (void *)StaticInitSwSlotheaps_thunk, (void *)StaticInitSwSlotheaps_2_thunk, (void *)StaticInitSwSlotheaps_3_thunk, (void *)StaticInitSlotheaps_1498f8_thunk, (void *)StaticInitSlotheaps_149eb0_thunk, (void *)GlobalCtor_14b640, (void *)GlobalCtor_14b7d8, (void *)func_0014BE88, (void *)func_0014C528, (void *)func_0014C680, (void *)StaticInitSharedSlotheaps_thunk, (void *)GlobalCtorSlotheaps_14d3b8, (void *)func_0014FA88, (void *)func_0014FC88, (void *)func_001520A8, (void *)func_00153988, (void *)func_00153AE8, (void *)GlobalCtorSensor, (void *)GlobalCtorSensorSight, (void *)difficulty__static_initialization_and_destruction_0_thunk, (void *)guardposts__static_initialization_and_destruction_0_thunk, (void *)func_001571E0, (void *)func_001578D8, (void *)func_00157A30, (void *)func_001585B8, (void *)func_001590F8, (void *)func_0015CD48, (void *)func_0015DC60, (void *)func_0015E360, (void *)font__static_initialization_and_destruction_0_thunk, (void *)InitStaticSlotheaps_frm_thunk, (void *)InitStaticSlotheaps_frm2_thunk, (void *)func_00161388, (void *)func_00166250, (void *)func_00166900, (void *)func_001672F0, (void *)GlobalCtorFrameCopy, (void *)GlobalCtorBlend, (void *)StaticInitSlotheaps_170850_thunk, (void *)GlobalCtorGuardPools_171f38, (void *)GlobalCtorGuardPools_173138, (void *)GlobalCtorGuardPools_174878, (void *)StaticInitSlotheapsAlo_thunk, (void *)StaticInitSlotheapsSwarm_thunk, (void *)StaticInitSlotheaps_184750_thunk, (void *)_GLOBAL_I_bis, (void *)func_00185110, (void *)StaticInitSlotheaps_1864b8_thunk, (void *)StaticInitSlotheaps_186ed8_thunk, (void *)func_00188468, (void *)StaticInitSly_thunk, (void *)func_0018F8E8, (void *)StaticInitSlotheaps_190f38_thunk, (void *)GlobalInitSlotheaps, (void *)StaticInit_Cnvo, (void *)StaticInit_Steppipe, (void *)func_0019F088, (void *)func_0019F3C8, (void *)GlobalCtorSlotheaps_1a02e0, (void *)GlobalCtorSlotheaps_1a0af8, (void *)func_001A2BB0, (void *)func_001A3000, (void *)func_001A3240, (void *)func_001A4DE8, (void *)func_001A5250, (void *)GlobalCtorSlotheaps_1a74f8, (void *)GlobalCtorSlotheaps_1a7bf8, (void *)GlobalCtorMark, (void *)func_001AE110, (void *)GlobalCtorSlotheaps_1ae7b0, (void *)GlobalCtorSlotheaps_1ae908, (void *)func_001B0B58, (void *)func_001B1D98, (void *)GlobalCtorSlotheaps_1b2800, (void *)GlobalCtorMpeg, (void *)GlobalCtorMurray, (void *)GlobalCtorGuardLook, (void *)GlobalCtorStgSwitch, (void *)func_001BC030, (void *)CreateSharedSlotheaps_1be240_thunk, (void *)CreateSharedSlotheaps_1befb8_thunk, (void *)func_001C2900, (void *)func_001C2A58, (void *)func_001C2D00, (void *)static_initialization_and_destruction_0_1c3238_thunk, (void *)func_001C3D50, (void *)func_001C4E30, (void *)StaticInitKeypadFile_thunk, (void *)StaticInitLoadingLogo_thunk, (void *)StaticInitCloneFile_thunk, (void *)StaticInitPipeFile_thunk, (void *)StaticInitCarryFile_thunk, (void *)func_001CD5D0, (void *)func_001CDCB0, (void *)func_001D1350, (void *)StaticInitSlotheaps_thunk_1d5130, (void *)func_001D5788, (void *)func_001D6828, (void *)func_001D7218, (void *)func_001D7A10, (void *)func_001D7B68, (void *)GlobalCtorSlotheaps_1d93b8, (void *)StaticInitMenus_thunk, (void *)StaticInitSlotheaps_1df980_thunk, (void *)GlobalCtorSlotheaps_1e5d60, (void *)CreateSharedSlotheaps_1ea410_thunk, (void *)GlobalCtorSlotheaps_1ed788, (void *)AddRefSharedSlotheaps_thunk, (void *)func_001EEC40, (void *)func_001EF830, (void *)func_001EFA70, (void *)func_001F1748, (void *)func_001F20E8, (void *)func_001F8DB8, (void *)func_001FAF50, (void *)StaticInitDestroySndbank_thunk, (void *)_GLOBAL__I_button, (void *)func_001FF7C8, (void *)func_001FFCD8, (void *)func_00201600, (void *)0x201d58, (void *)func_00203928, (void *)func_00205E50, (void *)func_0020B820, (void *)func_0020CE08, (void *)func_0020D5B0, (void *)StaticInitSlotheaps_20d878_thunk, (void *)GlobalCtorSw, (void *)InitDynamicTextStatics_thunk, (void *)InitArcTrailStatics_thunk, (void *)func_0021D258, (void *)func_0021D618, (void *)InitSharedSlotheaps_thunk, (void *)InitSharedSlotheaps_2_thunk, (void *)InitSharedSlotheaps_3_thunk, (void *)func_00223F50, (void *)func_002259B8, (void *)func_00226530, (void *)func_00226A98, (void *)func_00226BF0, (void *)func_00227330, (void *)func_00227598, (void *)func_00227B98, (void *)func_00227FC8, (void *)CreateSharedSlotheaps_2289f0_thunk, (void *)func_00229ED0, (void *)func_0022B020, (void *)func_0022B700, (void *)func_0022C7F8, (void *)func_002310E0, (void *)func_002319C8, (void *)func_00254ED8, 0, (void *)6};
