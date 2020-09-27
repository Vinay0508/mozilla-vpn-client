#ifndef DUMMYCONTROLLER_H
#define DUMMYCONTROLLER_H

#include "controllerimpl.h"

class DummyController final : public ControllerImpl
{
public:
    void initialize(const Device *device, const Keys *keys) override
    {
        Q_UNUSED(device);
        Q_UNUSED(keys);

        emit initialized(true, Controller::StateOff, QDateTime());
    }

    void activate(const Server &data,
                  const Device *device,
                  const Keys *keys,
                  bool forSwitching) override;

    void deactivate(bool forSwitching) override;

    void checkStatus() override;

private:
    int32_t m_txBytes = 0;
    int32_t m_rxBytes = 0;
};

#endif // DUMMYCONTROLLER_H
