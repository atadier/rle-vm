#include "controller.hpp"

#include <QMessageBox>
#include <iostream>
#include <lexer.hpp>


Module* compile_vm_module(const string& source) {
    std::istringstream in(source);
    Tokenizer tokenizer(&in);
    Lexer lexer(tokenizer);
    return lexer.build_module();
}

void error_messagebox(const QString& title, const QString& message) {
    QMessageBox message_box;
    message_box.setWindowTitle(title);
    message_box.setText(message);
    message_box.setIcon(QMessageBox::Critical);
    message_box.exec();
}


VmController::VmController(QObject* parent): QObject(parent) {

}

void VmController::update_state() {
    if (_machine) {
        setPc(_machine->pc);
        setSp(_machine->sp);
        setFlags(_machine->flags);
    }
}


void VmController::setVirtualMachine(Vm* machine) {
    _machine = machine;
    update_state();
}


QString VmController::getSource() {
    return _source;
}

void VmController::setSource(const QString& source) {
    if (source != _source) {
        _source = source;
        printf("source updated\n");
        emit sourceChanged(source);
    }
}

size_t VmController::getPc() {
    return _pc;
}

void VmController::setPc(size_t pc) {
    if (pc != _pc) {
        _pc = pc;
        emit pcChanged(pc);
    }
}

size_t VmController::getSp() {
    return _sp;
}

void VmController::setSp(size_t sp) {
    if (sp != _sp) {
        _sp = sp;
        emit spChanged(sp);
    }
}

unsigned int VmController::getFlags() {
    return _flags;
}

void VmController::setFlags(unsigned int flags) {
    if (flags != _flags) {
        _flags = flags;
        emit flagsChanged(flags);
    }
}


void VmController::step() {
    if (!_machine) return;
    _machine->step();
    update_state();
}

void VmController::run() {
    if (!_machine) return;
    _machine->run();
    update_state();
}

void VmController::loadModuleSource(const QString& source) {
    Module* module;
    try {
        module = compile_vm_module(source.toStdString());
    } catch (runtime_error& err) {
        error_messagebox(QString("Compilation Failed"),  err.what());
        return;
    }

    auto machine = new Vm(module);
    setVirtualMachine(machine);
    setSource(source);
}

void VmController::reload() {
    _machine->pc = 0;
    _machine->sp = 0;
    _machine->flags = 0;
    update_state();
}
