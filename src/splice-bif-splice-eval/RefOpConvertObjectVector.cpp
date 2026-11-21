#include "types.h"
#include "cref.h"
extern "C" {
QW bevy_camera_follow_track_heading_weight(void *, void *, QW);
CRef RefOpConvertObjectVector(int count, CRef *args)
{
    CRef temp;
    temp.SetTag(TAGK_Vector);
    QW *dest = (QW *)temp.m_tag.m_pvector;
    *dest = bevy_camera_follow_track_heading_weight(args[0].m_tag.m_pbasic, args[1].m_tag.m_pbasic, *(QW *)args[2].m_tag.m_pvector);
    return temp;
}
}
