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

#include "qcoreevent.h"
#include <QBasicTimer>
#include <QObject>
#include <qnetworkaccessmanager.h>
#include <qthread.h>
#include <src/monitor.h>

class MonitorBridge: public QObject
{
    Q_OBJECT
    QBasicTimer monitorTimer;
    Monitor* monitor;
    int count;

    const int DEFAULT_UPDATE_FREQUENCY = 5;

    void wait();

protected:
    void timerEvent(QTimerEvent *ev) override;

public:
    explicit MonitorBridge(QObject *parent = {});

};

#endif // MONITORBRIDGE_H
