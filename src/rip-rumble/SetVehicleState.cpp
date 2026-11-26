#include "types.h"
#include "vehicle.h"
#include "blot.h"
#include "clock.h"
/* the audio words SetVehicleState reads past the ammunition slots: vehicle.h's aammo[4] reaches over them (a slot count that is a guess), so a local view */
struct VEHICLEAUDIOVIEW {
    u8 unknown_0x0[0x598];
    void *pamb; int sfxid;
};
extern "C" {
void func_00213B00(BLOT *, int);
void UpdateVehicleHpBlot(VEHICLE *);
void *NewEmitter(int);
void SetEmitterUnpositioned(void *, VEHICLE *);
void VirtualRefPtr_Assign(void *, void *);
void SetAmbRange(void *, float, float);
void PauseAmb(void *);
void StopAmb(void *, float);
void SetVehicleAiState(VEHICLE *, int);
void SetSmaGoalIfReachable(SMA *, int);
extern int D_002C2208[];
}

void SetVehicleState(VEHICLE *veh, int state)
{
    VEHICLEAUDIOVIEW *audio = (VEHICLEAUDIOVIEW *)veh;
    if (state == veh->state)
        return;
    switch (veh->state) {
    case 0:
        if (veh->pblot != 0) {
            BLOT *blot = veh->pblot;
            blot->Select(-1);
            func_00213B00(veh->pblot, 0x34F);
            UpdateVehicleHpBlot(veh);
        }
        if (audio->sfxid != -1) {
            void *pamb = NewEmitter(audio->sfxid);
            SetEmitterUnpositioned(pamb, veh);
            VirtualRefPtr_Assign(&audio->pamb, pamb);
            SetAmbRange(audio->pamb, 500.0f, 1500.0f);
            PauseAmb(audio->pamb);
        }
        veh->state = state;
        break;
    case 1:
        SetVehicleAiState(veh, -1);
        veh->state = state;
        break;
    default:
        veh->state = state;
        break;
    }
    veh->tState = g_2dded0.t;
    void **ppamb;
    switch (state) {
    case 0:
        if (veh->pblot != 0) {
            BLOT *blot = veh->pblot;
            blot->Hide();
        }
        ppamb = &audio->pamb;
        if (*ppamb != 0) {
            StopAmb(*ppamb, 0.0f);
            VirtualRefPtr_Assign(ppamb, 0);
        }
        break;
    case 1:
        SetVehicleAiState(veh, 0);
        break;
    case 3:
        veh->HandleSpliceEvent(5, 0, 0, 0, 0);
        break;
    }
    if (veh->psma != 0 && veh->state != -1)
        SetSmaGoalIfReachable(veh->psma, D_002C2208[veh->state]);
}
