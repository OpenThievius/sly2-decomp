/* SPDX-License-Identifier: GPL-3.0-or-later */
struct TANK;

/* SO::Update (UpdateSo) runs on the tank itself, then its own aim, field of view and fire */
void UpdateSo(struct TANK *ptank);
void UpdateTankAim(struct TANK *ptank);
void UpdateTankFire(struct TANK *ptank);
void UpdateTankFov(struct TANK *ptank);

void UpdateTank(struct TANK *ptank) {
    UpdateSo(ptank);
    UpdateTankAim(ptank);
    UpdateTankFov(ptank);
    UpdateTankFire(ptank);
}
