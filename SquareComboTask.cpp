
#include "SquareComboTask.h"

SquareComboTask::SquareComboTask()
    :
    squareNums{}
{
    makeSquareFullNones();
}

void SquareComboTask::makeSquareFullNones()
{
    for (auto& row : square)
        for (auto& col : row)
            col = Color::NONE;
}

void SquareComboTask::startGuessing(std::size_t i, std::size_t j) const
{

    if (i >= size || j >= size || square[i][j] != Color::NONE)
    {
        std::cerr << "Something went wrong, check it out\n";
        return;
    }

    std::array<Color, size> cases = { Color::WHITE, Color::BLACK, Color::RED, Color::BLUE };

    Square copy;

    for (const auto color : cases)
    {
        square[i][j] = color;
        if (isGuessGood())
        {
            std::size_t curr_i = (j + 1) < size ? i : i + 1;;
            std::size_t curr_j = (j + 1) < size ? j + 1 : 0;

            if (curr_i >= size)
                break;

            copy = square;
            startGuessing(curr_i, curr_j);
            square = copy;
        }
    }

    if (squareIsFull())
    {
        #ifdef _DEBUG
                std::cout << "\nSquare constructed!!!\n\n";
                showSquare();
                std::cout << std::endl;
        #endif

        ++squareNums;
    }
}


bool SquareComboTask::isGuessGood() const
{
    return isHorizontalGood(square) && isVerticalGood();
}

bool SquareComboTask::isHorizontalGood(const Square& squareCheck) const
{

    for (const auto& row : squareCheck)
    {
        std::array<Color, size> a_colors = { Color::WHITE, Color::BLACK, Color::RED, Color::BLUE };
        std::map<Color, std::size_t> m_colors;

        for (const auto color : a_colors)
            m_colors.insert(std::make_pair(color, 0));

        for (const auto color : row)
        {
            const auto it = m_colors.find(color);
            if (it != m_colors.end())
            {
                ++it->second;
            }
        }

        for (const auto& colorsMatch : m_colors)
            if (colorsMatch.second > 1)
                return false;
    }

    return true;
}

bool SquareComboTask::isVerticalGood() const
{
    return isHorizontalGood(transposeSquare());
}

bool SquareComboTask::squareIsFull() const
{
    for (const auto& row : square)
        for (const auto color : row)
            if (color == Color::NONE)
                return false;

    return true;
}

void SquareComboTask::showSquare() const
{
    for (const auto& row : square)
    {
        for (const auto color : row)
        {
            if (color == Color::WHITE)
            {
                std::cout << "W ";
            }
            else if (color == Color::BLACK)
            {
                std::cout << "B ";
            }
            else if (color == Color::RED)
            {
                std::cout << "R ";
            }
            else
            {
                std::cout << "S ";
            }
        }

        std::cout << std::endl;
    }
}

Square SquareComboTask::transposeSquare() const
{
    auto r = square;

    for (std::size_t i{}; i < size; ++i)
        for (std::size_t j{}; j < size; ++j)
            r[j][i] = square[i][j];

    return r;
}


std::size_t SquareComboTask::getNums() const
{
    startGuessing(0ul, 0ul);

    return squareNums;
}