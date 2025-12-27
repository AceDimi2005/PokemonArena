#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <exception>
#include <string>

class GameException : public std::exception {
protected:
    std::string mesaj;

public:
    explicit GameException(std::string msg) : mesaj(std::move(msg)) {}
    const char* what() const noexcept override {
        return mesaj.c_str();
    }
};

class InvalidPokemonException : public GameException {
public:
    InvalidPokemonException()
        : GameException("Pokemon invalid!") {}
};

class AbilityException : public GameException {
public:
    AbilityException()
        : GameException("Eroare la abilitate!") {}
};

class ArenaException : public GameException {
public:
    ArenaException()
        : GameException("Eroare in arena!") {}
};

#endif