#include "rtl_dab.hpp"

#include <QTextStream>
#include <QTimer>

RtlDab::RtlDab()
    : dabServer()
    , currentService()
{
}

void RtlDab::scanEnsembles()
{
    if (dabServer.state() != QProcess::NotRunning)
        dabServer.kill();

    dabServer.start("welle-cli", {"-d", "0", "-e", "Auto", "--pcm-output", "pipe"});

    connect(&dabServer, &QProcess::readyReadStandardOutput, [this]() {
        QByteArray data = dabServer.readAllStandardOutput();
        QTextStream stream(data);

        while (!stream.atEnd()) {
            QString line = stream.readLine();

            if (line.startsWith("Ensemble:")) {
                QString ensembleName = line.section(" ", 1, 1);
                QString serviceName = line.section("Service:", 1, 1).section("ID:", 0, 0).trimmed();
                int serviceId = line.section("ID:", 1, 1).section("Logo:", 0, 0).trimmed().toInt();
                QString logoPath = line.section("Logo:", 1, 1).trimmed();

                DabService service{serviceName, ensembleName, serviceId, logoPath};
                services.append(service);
            }
        }
    });

    QTimer::singleShot(5000, [this]() {
        dabServer.kill();
    });
}

QVector<DabService> RtlDab::getServices() const
{
    return services;
}

void RtlDab::selectService(const QString &serviceName)
{
    stop();

    auto it = std::find_if(services.begin(), services.end(),
                           [&serviceName](const DabService &s) { return s.name == serviceName; });
    if (it == services.end())
        return;

    currentService = serviceName;

    dabServer.start("welle-cli", {"-d", "0", "-e", it->ensemble, "--service", it->name, "--pcm-output", "pipe"});
}

void RtlDab::play()
{
    if (currentService.isEmpty() && !services.isEmpty()) {
        selectService(services.first().name);
    }
}

void RtlDab::stop()
{
    if (dabServer.state() != QProcess::NotRunning)
        dabServer.terminate();
}