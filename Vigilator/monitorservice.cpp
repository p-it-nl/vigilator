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
#include "monitorservice.h"
#include "abstractresource.h"
#include "monitoraccessmanager.h"

MonitorService::MonitorService(QObject* parent) : QObject(parent)
{
    m_manager = std::make_shared<MonitorAccessManager>();
}

MonitorAccessManager* MonitorService::network() const
{
    return m_manager.get();
}

void MonitorService::setUrl(const QUrl& url)
{
    if(m_url == url)
        return;
    m_url = url;
    m_manager->setUrl(url);
    emit urlChanged();
}

QUrl MonitorService::url() const
{
    return m_url;
}

QQmlListProperty<AbstractResource> MonitorService::resources()
{
    return {this, &m_resources};
}

void MonitorService::classBegin()
{

}

void MonitorService::componentComplete()
{
    for(const auto resource : std::as_const(m_resources))
        resource->setAccessManager(m_manager);
}
