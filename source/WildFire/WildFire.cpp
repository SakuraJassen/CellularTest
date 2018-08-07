#include "WildFire.h"

#include <iostream>
#include <random>
#include "../Util/Random.h"
#include "../App.h"


WildFire::WildFire(const Config & config, const App& app)
    : CellularAutomaton(config, app)
    , m_cells(config.simSize.x * config.simSize.y)
    , m_cellColor{{
            { 139, 69, 19 },    //Dirt
            { 0, 255, 0 },      //Tree
            { 255, 0, 0 },      //Fire
            { 126, 0, 0 } } }   //DeadTree
{
    canGrow = true;
    canBurn = false;

    std::mt19937 rng((unsigned)std::time(nullptr));
    Cell c;
    c.m_ct = CellType::Tree;
    c.m_life = 0;
    std::fill(m_cells.begin(), m_cells.end(), c);

    cellForEach([&](unsigned x, unsigned y)
    {
        unsigned index = getCellIndex(x, y);
        std::uniform_int_distribution<int> dist(0, 0);

        auto& cell = m_cells[index];
        cell.m_ct = (CellType)dist(rng);
        CellularAutomaton::setCellColour(x, y, m_cellColor[(int)m_cells[getCellIndex(x, y)].m_ct]);
    });
    setCell(config.simSize.x/2, config.simSize.y/2, CellType::Fire);
}

void WildFire::input(const sf::Event& e)
{
    if (e.type == sf::Event::KeyReleased) {
        if (e.key.code == sf::Keyboard::Q) {
            std::cout << "Toggled SIM/EDIT mode" << '\n';
            m_isInEditMode = !m_isInEditMode;
        }
    }

    auto cellLocation = getMouseInputPosition();
    if (!cellLocation) {
        return;
    }
    auto cellInfo = getCellPointInfo(*cellLocation);

    if (e.type == sf::Event::MouseButtonReleased) {
        if (e.mouseButton.button == sf::Mouse::Left) {
            setCell(cellInfo.x, cellInfo.y,
                (int)(cellInfo.cell->m_ct) == (int)CellType::Tree ?
                CellType::Fire :
                CellType::Tree);
        } else if (e.mouseButton.button == sf::Mouse::Right) {
            setCell(cellInfo.x, cellInfo.y, CellType::Dirt);
        }
    }
    else if (e.type == sf::Event::MouseButtonPressed) {
    }
}

void WildFire::update()
{
    if (m_isInEditMode) {
        /*auto cellLocation = getMouseInputPosition();
        if (!cellLocation) {
            return;
        }
        auto cellInfo = getCellPointInfo(*cellLocation);*/
    }
    else {
        std::vector<std::pair<sf::Vector2i, CellType>> updates;
        cellForEach([&](unsigned x, unsigned y)
        {
            sf::Vector2i loc(x, y);
            int index = getCellIndex(x, y);
            auto cell = m_cells[index];
            switch (cell.m_ct)
            {
                case CellType::Dirt:
                    if (canGrow &&
                        Random::get().intInRange(1,10000) > (9925))
                    {
                        updates.emplace_back(loc, CellType::Tree);
                    }
                    break;
                case CellType::Tree:
                    if (canBurn &&
                        Random::get().intInRange(1,10000) > (9999))
                    {
                        updates.emplace_back(loc, CellType::Fire);
                    }
                    break;
                case CellType::Fire:
                    switch(cell.m_life)
                    {
                        case 0:
                            for (int nX = -1; nX <= 1; nX++)    //check neighbours
                                for (int nY = -1; nY <= 1; nY++)
                                {
                                    int newX = nX + x;
                                    int newY = nY + y;

                                    if (newX == -1 || newX == (int)m_pConfig->simSize.x ||
                                        newY == -1 || newY == (int)m_pConfig->simSize.y || //out of bounds
                                        (nX == 0 && nY == 0)) //Cell itself
                                    {
                                        continue;
                                    }

                                    auto cell = m_cells[getCellIndex(newX, newY)];
                                    if (cell.m_ct == CellType::Tree)
                                        updates.emplace_back(sf::Vector2i(newX, newY), CellType::Fire);
                                }
                            break;
                        case 1:
                            break;
                        case 2:
                            updates.emplace_back(loc, CellType::DeadTree);
                            break;
                        default:
                            break;
                    }
                    break;
                case CellType::DeadTree:
                    if(cell.m_life > 60)
                        updates.emplace_back(loc, CellType::Dirt);
                    break;
            }
        });
        cellForEach([&](unsigned x, unsigned y)
        {
            m_cells[getCellIndex(x, y)].m_life++;
            updateCellColor(x, y);
        });
        for (auto& update : updates) {
            m_cells[getCellIndex(update.first.x, update.first.y)].m_ct = update.second;
            m_cells[getCellIndex(update.first.x, update.first.y)].m_life = 0;

            updateCellColor(update.first.x, update.first.y);
        }
    }
}

void WildFire::setCell(unsigned x, unsigned y, Cell cell)
{
    Cell& c = m_cells[getCellIndex(x, y)];
    c = cell;
    CellularAutomaton::setCellColour(x, y, m_cellColor[(int)c.m_ct]);
}

void WildFire::setCell(unsigned x, unsigned y, CellType celltype)
{
    Cell& c = m_cells[getCellIndex(x, y)];
    c.m_ct = celltype;
    c.m_life = 0;
    updateCellColor(x, y);
}

WildFire::Cell WildFire::getCell(int x, int y)
{
    return m_cells[getCellIndex(x, y)];
}

WildFire::CellPointInfo WildFire::getCellPointInfo(const sf::Vector2i & cellPoint)
{
    CellPointInfo info;
    info.x = cellPoint.x;
    info.y = cellPoint.y;
    info.index = getCellIndex(info.x, info.y);
    info.cell = &m_cells[info.index];
    return info;
}


const Config & WildFire::getConfig() const
{
    return *m_pConfig;
}

void WildFire::onRenderCells(sf::RenderWindow & window)
{
}

void WildFire::updateCellColor(unsigned x, unsigned y)
{
    //TODO: bottleneck?
    sf::Color updateColor = { 255, 165, 200 };
    int index = getCellIndex(x, y);
    auto cell = m_cells[index];
    switch (cell.m_ct)
    {
        case CellType::Dirt:
            updateColor = { 139, 69, 19 };
            break;
        case CellType::Tree:
            updateColor = { 0, 255, 0 };
            break;
        case CellType::Fire:
            switch(cell.m_life)
            {
                case 0:
                    updateColor = { 255, 0, 0 };
                    break;
                case 1:
                    updateColor = { 255, 165, 0 };
                    break;
                case 2:
                    updateColor = { 126, 0, 0 };
                    break;
                default:
                    updateColor = { 255, 165, 200 };
                    break;
            }
            break;
        case CellType::DeadTree:
            updateColor = { 44, 44, 44 };
            break;
    }

    CellularAutomaton::setCellColour(x, y, updateColor);
}

std::optional<sf::Vector2i> WildFire::getMouseInputPosition() const
{
    auto mousePosition = sf::Mouse::getPosition(m_pApplication->getWindow());
    auto convertedPosition = m_pApplication->getWindow().mapPixelToCoords({ (int)mousePosition.x, (int)mousePosition.y });
    auto x = convertedPosition.x;
    auto y = convertedPosition.y;

    if (x < 0 || x >(int)m_pConfig->windowSize.x ||
        y < 0 || y >(int)m_pConfig->windowSize.y) {
        return {};
    }

    return sf::Vector2i{
        (int)(x / m_pConfig->cellSize),
        (int)(y / m_pConfig->cellSize)
    };
}
