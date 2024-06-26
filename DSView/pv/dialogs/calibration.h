/*
 * This file is part of the DSView project.
 * DSView is based on PulseView.
 *
 * Copyright (C) 2016 DreamSourceLab <support@dreamsourcelab.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */


#ifndef DSVIEW_PV_CALIBRATION_H
#define DSVIEW_PV_CALIBRATION_H

#include <QDialogButtonBox>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QSlider>
#include <vector> 
#include <QKeyEvent>
#include "../toolbars/titlebar.h"
#include "dsdialog.h"
#include "../ui/uimanager.h"

class DeviceAgent;
struct sr_channel;

namespace pv {

namespace dialogs {

class Calibration : public DSDialog, public IUiWindow
{
	Q_OBJECT

    struct ui_param_info
    {
        QLabel *lable;
        QSlider *slider;
    };

    struct channel_param_widget
    {
        ui_param_info gain;
        ui_param_info off;
        ui_param_info comp;
        sr_channel *probe;
    };

public:
    Calibration(QWidget *parent);
    ~Calibration();

    void update_device_info();
    
signals:
    void sig_closed();
    
private: 
    void reject();
    void keyPressEvent(QKeyEvent *event) override;
    void retranslateUi();

    //IUiWindow
    void UpdateLanguage() override;
    void UpdateTheme() override;
    void UpdateFont() override;

    void updateLangText();
    void BuildUI();

private slots:
    void set_value(int value);
    void on_save();
    void on_abort();
    void on_reset();
    void reload_value();

private:  
    QPushButton *_save_btn;
    QPushButton *_abort_btn;
    QPushButton *_reset_btn;
    QPushButton *_exit_btn;
    QFormLayout *_flayout;
    std::vector<channel_param_widget> _params;

    DeviceAgent *_device_agent;
    bool    _is_setting;
};

} // namespace dialogs
} // namespace pv

#endif // DSVIEW_PV_CALIBRATION_H
