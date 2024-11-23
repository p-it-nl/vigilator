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
#include "notifier.h"
#ifdef Q_OS_ANDROID
#include <QtCore/qjniobject.h>
#endif
#include <QtCore/qcoreapplication.h>

Notifier::Notifier(QObject *parent)
    : QObject(parent)
{
    connect(this, &Notifier::notificationChanged,
            this, &Notifier::updateNotification);
}

void Notifier::setNotification(const QString &appName)
{
    if(m_notification == appName) {
        return;
    }

    //! [notification changed signal]
    m_notification = appName + " is kaduuk.";
    emit notificationChanged();
    //! [notification changed signal]
}

QString Notifier::notification() const
{
    return m_notification;
}

//! [Send notification message to Java]
void Notifier::updateNotification()
{
#ifdef Q_OS_ANDROID
    QJniObject javaNotification = QJniObject::fromString(m_notification);
    QJniObject::callStaticMethod<void>(
        "nl/p_it/vigilator/NotificationClient",
        "notify",
        "(Landroid/content/Context;Ljava/lang/String;)V",
        QNativeInterface::QAndroidApplication::context(),
        javaNotification.object<jstring>());
#else
    qDebug() << "show other env notification";
#endif
}
//! [Send notification message to Java]

