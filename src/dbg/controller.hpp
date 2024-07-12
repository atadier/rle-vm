#pragma once
#include <qobject.h>
#include <qstring.h>

#include "../vm/vm.hpp"

class VmController: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString programSource READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(size_t pc READ getPc WRITE setPc NOTIFY pcChanged)
    Q_PROPERTY(size_t sp READ getSp WRITE setSp NOTIFY spChanged)

    Q_SIGNALS:
        void sourceChanged(QString programSource);
        void pcChanged(size_t pc);
        void spChanged(size_t sp);

    public slots:
        void step();
        void run();
        void reload();
        void loadModuleSource(const QString& source);

    public:
        explicit VmController(QObject *parent = nullptr);
        void setVirtualMachine(Vm* machine);

        QString getSource();
        void setSource(const QString& source);

        size_t getPc();
        void setPc(size_t pc);

        size_t getSp();
        void setSp(size_t sp);

    private:
        QString _source{};
        size_t _pc = 0;
        size_t _sp = 0;
        Vm* _machine = nullptr;

        void update_state();
};
