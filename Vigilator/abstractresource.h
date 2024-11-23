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
#ifndef ABSTRACTRESOURCE_H
#define ABSTRACTRESOURCE_H

#include "monitoraccessmanager.h"
#include <QtQml/qqml.h>
#include <QtCore/qobject.h>

class AbstractResource : public QObject
{
    Q_OBJECT
    QML_ANONYMOUS

public:
    explicit AbstractResource(QObject* parent = nullptr) : QObject (parent)
    {}

    virtual ~AbstractResource() = default;
    void setAccessManager(std::shared_ptr<MonitorAccessManager> manager)
    {
        m_manager = manager;
    }

protected:
    std::shared_ptr<MonitorAccessManager> m_manager;
};

#endif // ABSTRACTRESOURCE_H
