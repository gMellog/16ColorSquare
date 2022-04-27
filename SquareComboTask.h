#pragma once
#include <iostream>
#include <array>
#include <map>

const std::size_t size = 4;
enum class Color { WHITE, BLACK, RED, BLUE, NONE };
using Square = std::array<std::array<Color, size>, size>;

class SquareComboTask
{

public:

    SquareComboTask();

    std::size_t getNums() const;

private:
    mutable Square square;

    mutable std::size_t squareNums;

    void makeSquareFullNones();
    void startGuessing(std::size_t i, std::size_t j) const;
    bool isGuessGood() const;
    bool isHorizontalGood(const Square& squareCheck) const;
    bool isVerticalGood() const;
    bool squareIsFull() const;

    void showSquare() const;

    Square transposeSquare() const;

};
