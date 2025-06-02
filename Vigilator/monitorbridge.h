/**
 * Copyright (c) p-it
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef MONITORBRIDGE_H
#define MONITORBRIDGE_H

#include "notifier.h"
#include "qcoreevent.h"
#include <QBasicTimer>
#include <QObject>
#include <qnetworkaccessmanager.h>
#include <qthread.h>
#include "src/monitor/monitor.h"
#include "src/statusupdater.h"

class MonitorBridge: public QObject
{
    Q_OBJECT
    QBasicTimer updateTimer;
    StatusUpdater* updater;
    Notifier* notifier;
    int count;

    const int DEFAULT_UPDATE_FREQUENCY = 10;

    void wait();
    void validate();

protected:
    void timerEvent(QTimerEvent *ev) override;

public:
    explicit MonitorBridge(QObject *parent = {});

    void connnectUpdater(StatusUpdater* statusUpdater);

public slots:
    void startTimer();

};

#endif // MONITORBRIDGE_H
