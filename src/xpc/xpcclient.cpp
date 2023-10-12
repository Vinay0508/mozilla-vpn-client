/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "xpcclient.h"

#include <CoreFoundation/CoreFoundation.h>
#include <xpc/xpc.h>

#include <QCoreApplication>
#include <QObject>
#include <QScopedPointer>
#include <QtLogging>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

XPCClient::XPCClient() : QObject() {
  auto h = std::hash<std::thread::id>{}(std::this_thread::get_id());
  qWarning() << "[XPCClient::Constructor] - Thread "
             << qUtf8Printable(QString::number(h));
}

void XPCClient::send(const QString aMessage) {
  if (isXPCThread()) {
    sendInternal(aMessage);
    return;
  }
  // Dispatch onto our thread if not there.
  QMetaObject::invokeMethod(this, "send", Qt::QueuedConnection, aMessage);
};

void XPCClient::handleServerEvent(xpc_object_t event) {
  auto h = std::hash<std::thread::id>{}(std::this_thread::get_id());
  qWarning() << "[XPCClient::handleServerEvent] - Thread "
             << qUtf8Printable(QString::number(h));

  // We cannot assert the thread, as that is called by apple.
  // Q_ASSERT(isXPCThread());
  xpc_type_t type = xpc_get_type(event);
  if (type == XPC_TYPE_ERROR) {
    auto maybeError = getXPCError(event);
    Q_ASSERT(!maybeError.isNull());
    emit onConnectionError(maybeError);
    return;
  }
  auto message = getQStringFromXPCDict(event, defaultDictKey);

  emit messageReceived(message);
}

void XPCClient::sendInternal(const QString aMessage) {
  auto message = xpc_dictionary_create(NULL, NULL, 0);
  auto xpc_string = xpc_string_create(aMessage.toLocal8Bit().constData());
  xpc_dictionary_set_value(message, defaultDictKey, xpc_string);
  xpc_connection_send_message(m_serverConnection, xpc_string);
}

void XPCClient::connectService(QString service) {
  auto h = std::hash<std::thread::id>{}(std::this_thread::get_id());
  qWarning() << "[XPCClient::connectService] - Thread "
             << qUtf8Printable(QString::number(h));

  qWarning("[XPCClient] - connectService ");
  if (isXPCThread()) {
    qWarning("[XPCClient] - in thread ");
    connectServiceInternal(service);
    return;
  }
  qWarning("[XPCClient] - not in thread dispatch");
  // Dispatch onto our thread if not there.
  QMetaObject::invokeMethod(this, "connectService", Qt::QueuedConnection,
                            service);
}

// private
void XPCClient::connectServiceInternal(const QString service) {
  qWarning() << "[XPCClient]"
             << "Connect to: " << qUtf8Printable(service);
  m_serverConnection =
      xpc_connection_create_mach_service(qUtf8Printable(service), NULL, 0);
  xpc_connection_set_event_handler(m_serverConnection, ^(xpc_object_t event) {
    handleServerEvent(event);
  });
  xpc_connection_resume(m_serverConnection);
  // Emit a run of the apple event loop to handle the new connection.
}
