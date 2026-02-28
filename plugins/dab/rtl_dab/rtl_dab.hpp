#pragma once

#include <QObject>
#include <QProcess>
#include <QString>
#include <QVector>

#include "plugins/dab_plugin.hpp"

class RtlDab : public QObject, DabPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID DabPlugin_iid FILE "rtl_dab.json")
    Q_INTERFACES(DabPlugin)

public:
    RtlDab();

    void play() override;                  
    void stop() override;           
    void scanEnsembles() override;                  
    QVector<DabService> getServices() const override; 
    void selectService(const QString &serviceName) override; 

private:
    QProcess dabServer;       
    QString currentService;   
    QVector<DabService> services; 
};