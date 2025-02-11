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
#include "monitorbridge.h"

#include <notifier.h>

MonitorBridge::MonitorBridge(QObject *parent) : QObject(parent)
{
    count = 0;
    monitorTimer.start(0, this);

    monitor = Monitor::getInstance();
    monitor->setUp(this);
    notifier = new Notifier();
}

void MonitorBridge::timerEvent(QTimerEvent *ev)
{
    if (ev->timerId() != monitorTimer.timerId())
        return;

    monitor->execute();

    wait();
    validate();
    wait();
}

void MonitorBridge::wait()
{
    // TODO: For somereason the QNetworkAccessManager does not reply the first two `get`s but will respond with the third and subsequent `get`s
    if(count < 2) {
        qDebug() << "winding up...";
        QThread::sleep(1);
        count++;
    } else {
        qDebug() << "waiting";
        QThread::sleep(DEFAULT_UPDATE_FREQUENCY/2);
    }
}

void MonitorBridge::validate() {
    std::list<std::shared_ptr<MonitoredResource>> resources = monitor->getResources();
    for(std::shared_ptr<MonitoredResource>& resource : resources) {
        if(resource->isHealthy()) {
            qDebug() << resource->getName() << " healthy";
        } else {
            qDebug() << resource->getName() << " unhealthy";
        }

        for(std::string error : resource->getErrors()) {
            notifier->setNotification(resource->getName() + " " + error);
        }
        for(std::string warning : resource->getWarnings()) {
            notifier->setNotification(resource->getName() + " " + warning);
        }
    }

    emit updateReady("test");
}

