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
#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>

//! [Qt Notifictaion Class]
class Notifier : public QObject
{
    Q_OBJECT
public:
    explicit Notifier(QObject *parent = 0);

    void setNotification(const QString &appName);
    QString notification() const;

signals:
    void notificationChanged();

private slots:
    void updateNotification();

private:
    QString m_notification;
};
//! [Qt Notification Class]
#endif // NOTIFICATIONCLIENT_H