#include "sly2.h"
#include "jt.h"
#include "sw.h"
#include "job.h"
#include "memcard.h"
struct CRefX_161A58 { int tagk; union { float g; int n; }; int p2; int p3; };
struct JOBMGR_161A58 { u8 unknown_0x0[0x10]; int oidJob; int oidTask; int oidRestart; };
struct CTaskHold_161A58 {
    TASK *pother;
    TASK *ptask;
    int saveF4;
    int saveF8;
    CTaskHold_161A58(TASK *task, int value)
    {
        pother = 0;
        ptask = task;
        if (ptask != 0) {
            saveF4 = ptask->cause;
            ptask->cause = value;
            saveF8 = ptask->causeArg;
            ptask->causeArg = 0;
        }
    }
    ~CTaskHold_161A58()
    {
        if (pother != 0) {
            pother->pending = saveF4;
            pother->cause = saveF8;
        }
        if (ptask != 0) {
            ptask->cause = saveF4;
            ptask->causeArg = saveF8;
        }
    }
};
extern "C" {
extern SW B_003DD490;
extern SAVE B_002E65E0;
extern LEVELID B_003E1088;
extern const LEVELID RO_002A37E8;
extern int B_003D4A60;
void ApplyOptionsFromSave(void *);
void ApplyPendingSave();
void CRef_Destruct(CRefX_161A58 *);
void CStackFrame_Construct(void *);
void CStackFrame_Destructor(void *, int);
int CploFindSwObjectsByClass(SW *, int, int, int, int, JT **);
void EnterTask(int);
int IEpisodeCurrent();
void JobMgr_Construct(JOBMGR_161A58 *);
int LootId(LOOT *);
void OrderTasks(int *, TASK ***);
void *PloFindSwObject_thunk(SW *, int, int, void *);
void PostTaskJobEvent(int);
void RefGetGameSaveValue(CRefX_161A58 *, void *, void *);
void RequestTransition(SW *, int, int, int, int, int);
void RestoreTaskStateFromSave(TASK *);
void SaveTaskVariables(TASK *);
void SetSwCurrentJob(SW *, void *);
void SetSwCurrentTask(SW *, void *);
void SetSwRestartTask(SW *, void *);
void StartJob(JOB *);
void func_00143AF0(JT *, int);
void func_00165280(JOBMGR_161A58 *);
void func_001AB630(SAVE *);
}
static inline float GetSaveFloat_161A58(void *root, void *path)
{
    CRefX_161A58 ref;
    RefGetGameSaveValue(&ref, root, path);
    float g = ref.g;
    CRef_Destruct(&ref);
    return g;
}
static inline int FCidEqual_161A58(const LEVELID *a, const LEVELID *b)
{
    if (a == b)
        return 1;
    if (a == 0 || b == 0)
        return 0;
    return (a->field_0x8 ^ a->field_0x38) == (b->field_0x8 ^ b->field_0x38);
}
extern "C" void bevy_game_app_job_level_loaded(JOBMGR_161A58 *pjobmgr, int msg)
{
    switch (msg) {
    case 1:
        if (FCidEqual_161A58(&B_003E1088, &RO_002A37E8)) {
            JT *apobj[3];
            int cobj = CploFindSwObjectsByClass(&B_003DD490, 5, 0x34, 0, 3, apobj);
            for (int index = 0; index < cobj; index++) {
                JT *pobj = apobj[index];
                if (pobj->plootHeld != 0)
                    func_00143AF0(pobj, LootId(pobj->plootHeld));
            }
        }
        break;
    case 3:
        if (B_003DD490.loadreq.grf & 1) {
            JobMgr_Construct(pjobmgr);
            B_002E65E0.pslotCur = 0;
        } else if (B_003DD490.loadreq.grf & 0x40) {
            ApplyPendingSave();
        }
        func_001AB630(&B_002E65E0);
        if (IEpisodeCurrent() == 0 && B_002E65E0.state == 6 && B_002E65E0.pslotCur == 0 && B_002E65E0.pslotNewest != 0) {
            if (GetSaveFloat_161A58(B_003DD490.psavepathDt, &B_003D4A60) == 0.0f) {
                if (GetSaveFloat_161A58(B_003DD490.psavepathDt, B_002E65E0.pslotNewest) != 0.0f)
                    ApplyOptionsFromSave(B_002E65E0.pslotNewest);
            }
        }
        break;
    case 4:
        func_00165280(pjobmgr);
        break;
    case 5: {
        int frame;
        int ctask;
        TASK **aptask;
        CStackFrame_Construct(&frame);
        OrderTasks(&ctask, &aptask);
        for (int index = 0; index < ctask; index++) {
            TASK *ptask = aptask[index];
            CTaskHold_161A58 hold(ptask, 1);
            RestoreTaskStateFromSave(ptask);
        }
        SetSwCurrentJob(&B_003DD490, PloFindSwObject_thunk(&B_003DD490, 0x105, pjobmgr->oidJob, 0));
        SetSwCurrentTask(&B_003DD490, PloFindSwObject_thunk(&B_003DD490, 0x105, pjobmgr->oidTask, 0));
        SetSwRestartTask(&B_003DD490, PloFindSwObject_thunk(&B_003DD490, 0x105, pjobmgr->oidRestart, 0));
        if (B_003DD490.pjobCurrent != 0)
            StartJob(B_003DD490.pjobCurrent);
        if (B_003DD490.ptaskCurrent != 0)
            EnterTask((int)B_003DD490.ptaskCurrent);
        if (B_003DD490.loadreq.grf & 4) {
            if ((int)B_003DD490.ptaskRestart != 0)
                PostTaskJobEvent((int)B_003DD490.ptaskRestart);
            else if (B_003DD490.pjobCurrent != 0)
                PostTaskJobEvent((int)B_003DD490.pjobCurrent->ptaskStart);
        }
        for (int index = 0; index < ctask; index++) {
            TASK *ptask = aptask[index];
            CTaskHold_161A58 hold(ptask, 0);
            SaveTaskVariables(ptask);
        }
        CStackFrame_Destructor(&frame, 2);
        break;
    }
    case 16:
        if (B_003DD490.pjobCurrent == 0)
            RequestTransition(&B_003DD490, 0, B_003DD490.field_0x3C88, B_003DD490.field_0x3C8C, B_003DD490.field_0x3E38 != 0 ? 0x20 : 0, 0x30A);
        break;
    }
}
