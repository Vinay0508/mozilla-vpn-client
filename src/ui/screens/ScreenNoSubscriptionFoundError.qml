/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

import QtQuick 2.5
import QtQuick.Controls 2.14

import Mozilla.VPN 1.0
import components 0.1

VPNStackView {
    id: stackView

    Component.onCompleted: function() {
       VPNNavigator.addStackView(VPNNavigator.ScreenNoSubscriptionFoundError, stackView)

       stackView.push("qrc:/ui/sharedViews/ViewErrorFullScreen.qml", {
           // Problem confirming subscription...
           headlineText: VPNl18n.GenericPurchaseErrorGenericPurchaseErrorHeader,

           // Sorry, we were unable to confirm your subscription.
           // Please try again or contact our support team for help.
           errorMessage: VPNl18n.RestorePurchaseGenericPurchaseErrorRestorePurchaseGenericPurchaseErrorText,

           // Try again
           primaryButtonText: VPNl18n.GenericPurchaseErrorGenericPurchaseErrorButton,
           primaryButtonObjectName: "errorTryAgainButton",
           primaryButtonOnClick: stackView.pop,
           secondaryButtonIsSignOff: true,
           getHelpLinkVisible: true,
           popWhenSignOff: true
       });
    }
}
