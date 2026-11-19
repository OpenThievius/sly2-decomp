#include "sw.h"
#include "cref.h"
struct SAVE;
struct ACT;
extern "C" {
SAVEPATH *PsavepathNew(const char *first, ...);
CRef RefSetGameSaveValue(SAVEPATH *path, const CRef &ref, SAVE *psave);
CRef func_001D8B20(const CRef &value, const char *first, ...);
int IdCurrentLevel(void);
int IEpisodeCurrent(void);
int NEpisodeBest(void);
void bevy_camera_follow_activity(ACT *pact, int n, void *p);
extern ACT B_002DEB30;
extern int B_002E1E54;
extern SAVE B_003D4A60;
extern const char RO_002A8968[], RO_002A8970[], RO_002A8980[], RO_002A8990[], RO_002A8998[], RO_002A89A0[], RO_002A89A8[], RO_002A89B0[], RO_002A89C0[], RO_002A89D0[], RO_002A89E0[], RO_002A89F0[], RO_002A8A00[], RO_002A8A10[], RO_002A8A20[], RO_002A8A38[], RO_002A8A48[], RO_002A8A58[], RO_002A8A60[], RO_002A8A78[];
extern const char *RO_002A39E8[];
}
/* local overlay: a CRef built from an s32 in place (cref.h has no such constructor) */
struct CRefS32 : CRef {
    CRefS32(int n)
    {
        m_tagk = TAGK_S32;
        m_tag.m_n = n;
    }
};
static inline void SetSaveValue(SAVEPATH *path, CRef ref)
{
    RefSetGameSaveValue(path, ref, &B_003D4A60);
}
static inline void SetSaveS32(SAVEPATH *path, int n)
{
    CRef ref;
    ref.m_tagk = TAGK_S32;
    ref.m_tag.m_n = n;
    SetSaveValue(path, ref);
}
extern "C" void CreateSwSavePaths(SW *psw)
{
    psw->psavepathDt = PsavepathNew(RO_002A8968, 0);
    psw->psavepathWidCurrent = PsavepathNew(RO_002A8970, 0);
    psw->psavepathEpisodeCurrent = PsavepathNew(RO_002A8980, 0);
    psw->psavepathCcoin = PsavepathNew(RO_002A8990, RO_002A8998, 0);
    psw->psavepathLang = PsavepathNew(RO_002A89A0, RO_002A89A8, 0);
    psw->psavepathMixerMode = PsavepathNew(RO_002A89A0, RO_002A89B0, 0);
    psw->psavepathMusicVolume = PsavepathNew(RO_002A89A0, RO_002A89C0, 0);
    psw->psavepathEffectsVolume = PsavepathNew(RO_002A89A0, RO_002A89D0, 0);
    psw->psavepathUseHeadset = PsavepathNew(RO_002A89A0, RO_002A89E0, 0);
    psw->psavepathDxScreenCenter = PsavepathNew(RO_002A89A0, RO_002A89F0, 0);
    psw->psavepathDyScreenCenter = PsavepathNew(RO_002A89A0, RO_002A8A00, 0);
    psw->psavepathNoVibration = PsavepathNew(RO_002A89A0, RO_002A8A10, 0);
    psw->psavepathReverseLookAround = PsavepathNew(RO_002A89A0, RO_002A8A20, 0);
    psw->psavepathReverseAim = PsavepathNew(RO_002A89A0, RO_002A8A38, 0);
    psw->psavepathAutosaveWarned = PsavepathNew(RO_002A89A0, RO_002A8A48, 0);
    for (int iepisode = 0; iepisode < 9; iepisode++) {
        psw->apsavepathEpisodeDt[iepisode] = PsavepathNew(RO_002A8A58, RO_002A39E8[iepisode], RO_002A8968, 0);
        psw->apsavepathEpisodePercent[iepisode] = PsavepathNew(RO_002A8A58, RO_002A39E8[iepisode], RO_002A8A60, 0);
    }
    SetSaveS32(psw->psavepathLang, B_002E1E54);
    SetSaveS32(psw->psavepathWidCurrent, IdCurrentLevel());
    SetSaveS32(psw->psavepathEpisodeCurrent, IEpisodeCurrent());
    if (IEpisodeCurrent() > NEpisodeBest()) {
        func_001D8B20(CRefS32(IEpisodeCurrent()), RO_002A8A78, 0);
    }
    bevy_camera_follow_activity(&B_002DEB30, 3, 0);
}
