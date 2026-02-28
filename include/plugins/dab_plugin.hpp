#pragma once

#include "plugins/plugin.hpp"

struct DabService {
    QString name;
    QString ensemble;
    int serviceId;
    QString logoPath;
};

class DabPlugin : public Plugin {
   public:
    DabPlugin() { this->settings.beginGroup("Dab"); }
    virtual ~DabPlugin() = default;
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void scanEnsembles() = 0;
    virtual QVector<DabService> getServices() const = 0;
    virtual void selectService(const QString &serviceName) = 0;
};

#define DabPlugin_iid "openDsh.plugins.DabPlugin"

Q_DECLARE_INTERFACE(DabPlugin, DabPlugin_iid)
