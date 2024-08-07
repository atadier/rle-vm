#pragma once
#include <qobject.h>
#include <qstring.h>

#include "../vm/vm.hpp"

class VmController: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString programSource READ getSource WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(size_t pc READ getPc WRITE setPc NOTIFY pcChanged)
    Q_PROPERTY(size_t sp READ getSp WRITE setSp NOTIFY spChanged)
    Q_PROPERTY(unsigned int flags READ getFlags WRITE setFlags NOTIFY flagsChanged)
    Q_PROPERTY(QList<int> stack READ getStack WRITE setStack NOTIFY stackChanged)

    Q_SIGNALS:
        void sourceChanged(QString programSource);
        void pcChanged(size_t pc);
        void spChanged(size_t sp);
        void flagsChanged(unsigned int flags);
        void stackChanged(QList<int> stack);

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

        unsigned int getFlags();
        void setFlags(unsigned int flags);

        QList<int> getStack();
        void setStack(QList<int> stack);

    private:
        QString _source{};
        size_t _pc = 0;
        size_t _sp = 0;
        unsigned int _flags = 0;
        QList<int> _stack{};
        Vm* _machine = nullptr;

        void update_state();
};
