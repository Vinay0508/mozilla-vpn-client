/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef PurchaseWebHandler_H
#define PurchaseWebHandler_H

#include "purchasehandler.h"

class PurchaseWebHandler final : public PurchaseHandler {
  Q_OBJECT
  Q_DISABLE_COPY_MOVE(PurchaseWebHandler)

 public:
  explicit PurchaseWebHandler(QObject* parent);
  ~PurchaseWebHandler();

 protected:
  void nativeRegisterProducts() override;
  void nativeStartSubscription(Product* product) override;
  void nativeRestoreSubscription() override;
  void startSubscription(const QString& productIdentifier);
};

#endif  // PurchaseWebHandler_H
