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
#include "monitorprocess.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QNetworkReply>
#include <QSslSocket>
#include <QtQml/qqmlapplicationengine.h>
#include <QtQml/qqmlcontext.h>
#include <QtGui/qguiapplication.h>
#include <QtGui/qicon.h>
#include <monitorbridge.h>
#include <iostream>
#ifdef Q_OS_ANDROID
#include <QtCore/qjniobject.h>
#endif
#include <QQmlContext>
#include "resourceslist.h"
#include "resourceitemmodel.h"
#include <src/statusupdater.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QGuiApplication::setApplicationName("Vigilator");
    QGuiApplication::setOrganizationName("p-it");
    QIcon::setThemeName("vigilator");

    // Register types with QML (only needed if instantiated in QML)
    qmlRegisterUncreatableType<ResourcesList>("ResourceItem", 1, 0, "ResourcesList",
                                              QStringLiteral("ResourcesList should not be created in QML"));

    // Instantiate backend objects
    ResourcesList resourcesList;
    ResourceItemModel resourceModel;
    resourceModel.setList(&resourcesList);  // If applicable

    qDebug() << "Device supports OpenSSL:" << QSslSocket::supportsSsl();

    // Setup QML engine and context properties
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("resourcesList", &resourcesList);
    engine.rootContext()->setContextProperty("resourceModel", &resourceModel);

    // Load QML
    const QUrl url(u"qrc:/Vigilator/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

#ifdef Q_OS_ANDROID
    qDebug() << "Configuring for android";
    QJniObject::callStaticMethod<void>(
        "nl/p_it/vigilator/MonitorService",
        "scheduleMonitorJobs",
        "(Landroid/content/Context;)V",
        QNativeInterface::QAndroidApplication::context());
#endif

    StatusUpdater* statusUpdater = new StatusUpdater();
    MonitorBridge monitorBridge;
    monitorBridge.connnectUpdater(statusUpdater);
    MonitorProcess* workThread = new MonitorProcess();
    workThread->takeObject(&monitorBridge);
    workThread->takeObject(statusUpdater);
    resourcesList.connect(statusUpdater, &StatusUpdater::updateReady, &resourcesList, &ResourcesList::handleUpdate);
    workThread->connect(workThread, &MonitorProcess::started, &monitorBridge, &MonitorBridge::startTimer);
    workThread->start();

    int exit = app.exec();

    std::cout << "quit" << std::endl;

  // delete workThread;

    return exit;
}
